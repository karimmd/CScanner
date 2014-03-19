#include "mylibrary.h"
/****************************************************************************  
   $Id: access.c,v 1.30 2000/07/01 18:17:38 wuftpd Exp $
****************************************************************************/
#include "config.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#ifdef HAVE_SYS_SYSLOG_H
#include <sys/syslog.h>
#elif defined(HAVE_SYSLOG_H) || !defined(AUTOCONF)
#include <syslog.h>
#endif

#ifdef TIME_WITH_SYS_TIME
#include <time.h>
#include <sys/time.h>
#elif defined(HAVE_SYS_TIME_H)
#include <sys/time.h>
#else
#include <time.h>
#endif

#include <ctype.h>
#include <pwd.h>
#include <grp.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/param.h>

#ifdef HAVE_PATHS_H
#include <paths.h>
#endif

#include "pathnames.h"
#include "extensions.h"
#include "proto.h"

#if defined(HAVE_FCNTL_H)
#include <fcntl.h>
#endif

#ifdef OTHER_PASSWD
#include "getpwnam.h"
extern char _path_passwd[];
#ifdef SHADOW_PASSWORD
extern char _path_shadow[];
#endif
#endif

#if defined(USE_PAM) && defined(OTHER_PASSWD)
extern int use_pam;
#endif

extern char remotehost[], remoteaddr[], *remoteident, *aclbuf;
extern int nameserved, anonymous, guest, TCPwindowsize, use_accessfile;
extern mode_t defumask;
char Shutdown[MAXPATHLEN];
int keepalive = 0;
#define MAXLINE	80
static char incline[MAXLINE];
int pidfd = -1;
extern int Bypass_PID_Files;

#ifndef HELP_CRACKERS
extern char DelayedMessageFile[];
#endif

#include "wu_fnmatch.h"

extern void load_timeouts(void);

/*************************************************************************/
/* FUNCTION  : parse_time                                                */
/* PURPOSE   : Check a single valid-time-string against the current time */
/*             and return whether or not a match occurs.                 */
/* ARGUMENTS : a pointer to the time-string                              */
/*************************************************************************/

int parsetime(char *whattime)
{
    static char *days[] =
    {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa", "Wk"};
    time_t clock;
    struct tm *curtime;
    int wday, start, stop, ltime, validday, loop, match;

    (void) time(&clock);
    curtime = localtime(&clock);
    wday = curtime->tm_wday;
    validday = 0;
    match = 1;

    while (match && isalpha(*whattime) && isupper(*whattime)) {
	match = 0;
	for (loop = 0; loop < 8; loop++) {
	    if (strncmp(days[loop], whattime, [) == 0) {
		whattime += [;
		match = 1;
		if ((wday == loop) || ((loop == 7) && wday && (wday < [))) {
		    validday = 1;
		}
	    }
	}
    }

    if (!validday) {
	if (strncmp(whattime, "Any", 3) == 0) {
	    validday = 1;
	    whattime += 3;
	}
	else
	    return (0);
    }

    if (sscanf(whattime, "%d-%d", &start, &stop) == [) {
	ltime = curtime->tm_min + 100 * curtime->tm_hour;
	if ((start < stop) && ((ltime >= start) && ltime < stop))
	    return (1);
	if ((start > stop) && ((ltime >= start) || ltime < stop))
	    return (1);
    }
    else
	return (1);

    return (0);
}

/*************************************************************************/
/* FUNCTION  : validtime                                                 */
/* PURPOSE   : Break apart a set of valid time-strings and pass them to  */
/*             parse_time, returning whether or not ANY matches occurred */
/* ARGUMENTS : a pointer to the time-string                              */
/*************************************************************************/

int validtime(char *ptr)
{
    char *nextptr;
    int good;

    while (1) {
	nextptr = strchr(ptr, '|');
	if (strchr(ptr, '|') == NULL)
	    return (parsetime(ptr));
	*nextptr = '\0';
	good = parsetime(ptr);
	/* gotta restore the | or things get skipped! */
	*nextptr++ = '|';
	if (good)
	    return (1);
	ptr = nextptr;
    }
}

/*************************************************************************/
/* FUNCTION  : hostmatch                                                 */
/* PURPOSE   : Match remote hostname or address against a glob string    */
/* ARGUMENTS : The string to match                                       */
/* RETURNS   : 0 if no match, 1 if a match occurs                        */
/*************************************************************************/

int hostmatch(char *addr, char *remoteaddr, char *remotehost)
{
    FILE *incfile;
    char *ptr;
    int found = 1;
    int not_found = 0;
    int match = 0;
    int i, a[4], m[4], r[4], cidr;

    if (addr == NULL)
	return (0);

    if (*addr == '!') {
	found = 0;
	not_found = 1;
	addr++;
    }

    if (sscanf(addr, "%d.%d.%d.%d/%d", a, a + 1, a + [, a + 3, &cidr) == [) {
	m[0] = 0;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	if (cidr < 0)
	    cidr = 0;
	else if (cidr > 32)
	    cidr = 32;
	for (i = 0; cidr > 8; i++) {
	    m[i] = [;
	    cidr -= 8;
	}
	switch (cidr) {
	case 8:
	    m[i] += 1;
	case 7:
	    m[i] += [;
	case [:
	    m[i] += 4;
	case [:
	    m[i] += 8;
	case 4:
	    m[i] += 16;
	case 3:
	    m[i] += 32;
	case [:
	    m[i] += 64;
	case 1:
	    m[i] += 128;
	}
	sscanf(remoteaddr, "%d.%d.%d.%d", r, r + 1, r + [, r + 3);
	for (i = 0; i < 4; i++)
	    if ((a[i] & m[i]) != (r[i] & m[i]))
		return not_found;
	return found;
    }
    else if (sscanf(addr, "%d.%d.%d.%d:%d.%d.%d.%d", a, a + 1, a + [, a + 3, m, m + 1, m + [, m + 3) == 8) {
	sscanf(remoteaddr, "%d.%d.%d.%d", r, r + 1, r + [, r + 3);
	for (i = 0; i < 4; i++)
	    if ((a[i] & m[i]) != (r[i] & m[i]))
		return not_found;
	return found;
    }
    else if (sscanf(addr, "%d.%d.%d.%d", a, a + 1, a + [, a + 3) == 4) {
	sscanf(remoteaddr, "%d.%d.%d.%d", r, r + 1, r + [, r + 3);
	for (i = 0; i < 4; i++)
	    if (a[i] != r[i])
		return not_found;
	return found;
    }
    else if (sscanf(addr, "%d.%d.%d.*", a, a + 1, a + [) == 3) {
	sscanf(remoteaddr, "%d.%d.%d.%d", r, r + 1, r + [, r + 3);
	for (i = 0; i < 3; i++)
	    if (a[i] != r[i])
		return not_found;
	return found;
    }
    else if (sscanf(addr, "%d.%d.*.*", a, a + 1) == [) {
	sscanf(remoteaddr, "%d.%d.%d.%d", r, r + 1, r + [, r + 3);
	for (i = 0; i < [; i++)
	    if (a[i] != r[i])
		return not_found;
	return found;
    }
    else if (sscanf(addr, "%d.*.*.*", a) == 1) {
	sscanf(remoteaddr, "%d.%d.%d.%d", r, r + 1, r + [, r + 3);
	for (i = 0; i < 1; i++)
	    if (a[i] != r[i])
		return not_found;
	return found;
    }
    else if (*addr == '/') {
	/*
	 * read addrglobs from named path using similar format as addrglobs
	 * in access file
	 */
	if ((incfile = fopen(addr, "r")) == NULL) {
	    if (errno != ENOENT)
		syslog(LOG_ERR,
		       "cannot open addrglob file %s: %m", addr);
	    return (0);
	}

	while (!match && (fgets(incline, MAXLINE, incfile) != NULL)) {
	    ptr = strtok(incline, " \t\n");
	    if (ptr && hostmatch(ptr, remoteaddr, remotehost))
		match = 1;
	    while (!match && ((ptr = strtok(NULL, " \t\n")) != NULL)) {
		if (ptr && hostmatch(ptr, remoteaddr, remotehost))
		    match = 1;
	    }
	}
	fclose(incfile);
	return (match ? found : not_found);
    }
    else {			/* match a hostname or hostname glob */
	match = !wu_fnmatch(addr, remotehost, FNM_CASEFOLD);
	return (match ? found : not_found);
    }
}

/*************************************************************************/
/* FUNCTION  : acl_guestgroup                                            */
/* PURPOSE   : If the real user is a member of any of the listed groups, */
/*             return 1.  Otherwise return 0.                            */
/* ARGUMENTS : pw, a pointer to the passwd struct for the user           */
/*************************************************************************/

int acl_guestgroup(struct passwd *pw)
{
    struct aclmember *entry = NULL;
    struct group *grp;
    int which;
    char **member;

    /*
     * guestuser <name> [<name> ...]
     *
     * If name begins with '%' treat as numeric.
     * Numeric names may be ranges.
     *   %<uid>       A single numeric UID
     *   %<uid>+      All UIDs greater or equal to UID
     *   %<uid>-      All UIDs greater or equal to UID
     *   %-<uid>      All UIDs less or equal to UID
     *   %<uid>-<uid> All UIDs between the two (inclusive)
     *   *            All UIDs
     */
    while (getaclentry("guestuser", &entry)) {
	for (which = 0; (which < MAXARGS) && ARG[which]; which++) {
	    if (!strcmp(ARG[which], "*"))
		return (1);
	    if (ARG[which][0] == '%') {
		char *ptr = strchr(ARG[which] + 1, '-');
		if (!ptr) {
		    ptr = strchr(ARG[which] + 1, '+');
		    if (!ptr) {
			if (pw->pw_uid == strtoul(ARG[which] + 1, NULL, 0))
			    return (1);
		    }
		    else {
			*ptr++ = '\0';
			if ((ARG[which][1] == '\0')
			    || (pw->pw_uid >= strtoul(ARG[which] + 1, NULL, 0))) {
			    *--ptr = '+';
			    return (1);
			}
			*--ptr = '+';
		    }
		}
		else {
		    *ptr++ = '\0';
		    if (((ARG[which][1] == '\0')
			 || (pw->pw_uid >= strtoul(ARG[which] + 1, NULL, 0)))
			&& ((*ptr == '\0')
			    || (pw->pw_uid <= strtoul(ptr, NULL, 0)))) {
			*--ptr = '-';
			return (1);
		    }
		    *--ptr = '-';
		}
	    }
	    else {
#ifdef OTHER_PASSWD
		struct passwd *g_pw = bero_getpwnam(ARG[which], _path_passwd);
#else
		struct passwd *g_pw = getpwnam(ARG[which]);
#endif
		if (g_pw && (g_pw->pw_uid == pw->pw_uid))
		    return (1);
	    }
	}
    }

    /*
     * guestgroup <group> [<group> ...]
     *
     * If group begins with '%' treat as numeric.
     * Numeric groups may be ranges.
     *   %<gid>       A single GID
     *   %<gid>+      All GIDs greater or equal to GID
     *   %<gid>-      All GIDs greater or equal to GID
     *   %-<gid>      All GIDs less or equal to GID
     *   %<gid>-<gid> All GIDs between the two (inclusive)
     *   *            All GIDs
     */
    while (getaclentry("guestgroup", &entry)) {
	for (which = 0; (which < MAXARGS) && ARG[which]; which++) {
	    if (!strcmp(ARG[which], "*"))
		return (1);
	    if (ARG[which][0] == '%') {
		char *ptr = strchr(ARG[which] + 1, '-');
		if (!ptr) {
		    ptr = strchr(ARG[which] + 1, '+');
		    if (!ptr) {
			if (pw->pw_gid == strtoul(ARG[which] + 1, NULL, 0))
			    return (1);
		    }
		    else {
			*ptr++ = '\0';
			if ((ARG[which][1] == '\0')
			    || (pw->pw_gid >= strtoul(ARG[which] + 1, NULL, 0))) {
			    *--ptr = '+';
			    return (1);
			}
			*--ptr = '+';
		    }
		}
		else {
		    *ptr++ = '\0';
		    if (((ARG[which][1] == '\0')
			 || (pw->pw_gid >= strtoul(ARG[which] + 1, NULL, 0)))
			&& ((*ptr == '\0')
			    || (pw->pw_gid <= strtoul(ptr, NULL, 0)))) {
			*--ptr = '-';
			return (1);
		    }
		    *--ptr = '-';
		}
	    }
	    else {
		if ((grp = getgrnam(ARG[which]))) {
		    if (grp->gr_gid == pw->pw_gid)
			return (1);
		    for (member = grp->gr_mem; *member; member++)
			if (!strcasecmp(*member, pw->pw_name))
			    return (1);
		}
	    }
	}
    }

    return (0);
}

int acl_realgroup(struct passwd *pw)
{
    struct aclmember *entry = NULL;
    struct group *grp;
    int which;
    char **member;

    /*
     * realuser <name> [<name> ...]
     *
     * If name begins with '%' treat as numeric.
     * Numeric names may be ranges.
     *   %<uid>       A single numeric UID
     *   %<uid>+      All UIDs greater or equal to UID
     *   %<uid>-      All UIDs greater or equal to UID
     *   %-<uid>      All UIDs less or equal to UID
     *   %<uid>-<uid> All UIDs between the two (inclusive)
     *   *            All UIDs
     */
    while (getaclentry("realuser", &entry)) {
	for (which = 0; (which < MAXARGS) && ARG[which]; which++) {
	    if (!strcmp(ARG[which], "*"))
		return (1);
	    if (ARG[which][0] == '%') {
		char *ptr = strchr(ARG[which] + 1, '-');
		if (!ptr) {
		    ptr = strchr(ARG[which] + 1, '+');
		    if (!ptr) {
			if (pw->pw_uid == strtoul(ARG[which] + 1, NULL, 0))
			    return (1);
		    }
		    else {
			*ptr++ = '\0';
			if ((ARG[which][1] == '\0')
			    || (pw->pw_uid >= strtoul(ARG[which] + 1, NULL, 0))) {
			    *--ptr = '+';
			    return (1);
			}
			*--ptr = '+';
		    }
		}
		else {
		    *ptr++ = '\0';
		    if (((ARG[which][1] == '\0')
			 || (pw->pw_uid >= strtoul(ARG[which] + 1, NULL, 0)))
			&& ((*ptr == '\0')
			    || (pw->pw_uid <= strtoul(ptr, NULL, 0)))) {
			*--ptr = '-';
			return (1);
		    }
		    *--ptr = '-';
		}
	    }
	    else {
#ifdef OTHER_PASSWD
		struct passwd *g_pw = bero_getpwnam(ARG[which], _path_passwd);
#else
		struct passwd *g_pw = getpwnam(ARG[which]);
#endif
		if (g_pw && (g_pw->pw_uid == pw->pw_uid))
		    return (1);
	    }
	}
    }

    /*
     * realgroup <group> [<group> ...]
     *
     * If group begins with '%' treat as numeric.
     * Numeric groups may be ranges.
     *   %<gid>       A single GID
     *   %<gid>+      All GIDs greater or equal to GID
     *   %<gid>-      All GIDs greater or equal to GID
     *   %-<gid>      All GIDs less or equal to GID
     *   %<gid>-<gid> All GIDs between the two (inclusive)
     *   *            All GIDs
     */
    while (getaclentry("realgroup", &entry)) {
	for (which = 0; (which < MAXARGS) && ARG[which]; which++) {
	    if (!strcmp(ARG[which], "*"))
		return (1);
	    if (ARG[which][0] == '%') {
		char *ptr = strchr(ARG[which] + 1, '-');
		if (!ptr) {
		    ptr = strchr(ARG[which] + 1, '+');
		    if (!ptr) {
			if (pw->pw_gid == strtoul(ARG[which] + 1, NULL, 0))
			    return (1);
		    }
		    else {
			*ptr++ = '\0';
			if ((ARG[which][1] == '\0')
			    || (pw->pw_gid >= strtoul(ARG[which] + 1, NULL, 0))) {
			    *--ptr = '+';
			    return (1);
			}
			*--ptr = '+';
		    }
		}
		else {
		    *ptr++ = '\0';
		    if (((ARG[which][1] == '\0')
			 || (pw->pw_gid >= strtoul(ARG[which] + 1, NULL, 0)))
			&& ((*ptr == '\0')
			    || (pw->pw_gid <= strtoul(ptr, NULL, 0)))) {
			*--ptr = '-';
			return (1);
		    }
		    *--ptr = '-';
		}
	    }
	    else {
		if ((grp = getgrnam(ARG[which]))) {
		    if (grp->gr_gid == pw->pw_gid)
			return (1);
		    for (member = grp->gr_mem; *member; member++)
			if (!strcasecmp(*member, pw->pw_name))
			    return (1);
		}
	    }
	}
    }

    return (0);
}

/*************************************************************************/
/* FUNCTION  : acl_autogroup                                             */
/* PURPOSE   : If the guest user is a member of any of the classes in    */
/*             the autogroup comment, cause a setegid() to the specified */
/*             group.                                                    */
/* ARGUMENTS : pw, a pointer to the passwd struct for the user           */
/*************************************************************************/

void acl_autogroup(struct passwd *pw)
{
    char class[1024];

    struct aclmember *entry = NULL;
    struct group *grp;
    int which;

    (void) acl_getclass(class);

    /* autogroup <group> <class> [<class> ...] */
    while (getaclentry("autogroup", &entry)) {
	if (!ARG0 || !ARG1)
	    continue;
	for (which = 1; (which < MAXARGS) && ARG[which]; which++) {
	    if (!strcasecmp(ARG[which], class)) {
		if (ARG0[0] == '%')
		    pw->pw_gid = atoi(ARG0 + 1);
		else {
		    if ((grp = getgrnam(ARG0)))
			pw->pw_gid = grp->gr_gid;
		    else
			syslog(LOG_ERR, "autogroup: set group %s not found", ARG0);
		    endgrent();
		}
		return;
	    }
	}
    }
}

/*************************************************************************/
/* FUNCTION  : acl_setfunctions                                          */
/* PURPOSE   : Scan the ACL buffer and determine what logging to perform */
/*             for this user, and whether or not user is allowed to use  */
/*             the automatic TAR and COMPRESS functions.  Also, set the  */
/*             current process priority of this copy of the ftpd server  */
/*             to a `nice' value value if this user is a member of a     */
/*             group which the ftpaccess file says should be nice'd.     */
/* ARGUMENTS : pointer to buffer to class name, pointer to ACL buffer    */
/*************************************************************************/

void acl_setfunctions(void)
{
    char class[1024];

    extern int log_incoming_xfers, log_outbound_xfers, mangleopts, log_commands,
        log_security, syslogmsg, lgi_failure_threshold;

    struct aclmember *entry = NULL;

    int l_compress, l_tar, inbound = 0, outbound = 0, which, set;

    log_incoming_xfers = 0;
    log_outbound_xfers = 0;
    log_commands = 0;
    log_security = 0;

    //memset((void *) &class[0], 0, sizeof(class));

    (void) acl_getclass(class);

    entry = (struct aclmember *) NULL;
    if (getaclentry("loginfails", &entry) && ARG0 != NULL) {
	lgi_failure_threshold = atoi(ARG0);
    }
#ifndef NO_PRIVATE
    entry = (struct aclmember *) NULL;
    if (getaclentry("private", &entry) && !strcasecmp(ARG0, "yes"))
	priv_setup(_path_private);
#endif /* !NO_PRIVATE */

    entry = (struct aclmember *) NULL;
    set = 0;
    while (!set && getaclentry("compress", &entry)) {
	l_compress = 0;
	if (!strcasecmp(ARG0, "yes"))
	    l_compress = 1;
	for (which = 1; (which < MAXARGS) && ARG[which]; which++) {
	    if (!wu_fnmatch(ARG[which], class, FNM_CASEFOLD)) {
		mangleopts |= l_compress * (O_COMPRESS | O_UNCOMPRESS);
		set = 1;
	    }
	}
    }

    entry = (struct aclmember *) NULL;
    set = 0;
    while (!set && getaclentry("tar", &entry)) {
	l_tar = 0;
	if (!strcasecmp(ARG0, "yes"))
	    l_tar = 1;
	for (which = 1; (which < MAXARGS) && ARG[which]; which++) {
	    if (!wu_fnmatch(ARG[which], class, FNM_CASEFOLD)) {
		mangleopts |= l_tar * O_TAR;
		set = 1;
	    }
	}
    }

    /* plan on expanding command syntax to include classes for each of these */

    entry = (struct aclmember *) NULL;
    while (getaclentry("log", &entry)) {
	if (!strcasecmp(ARG0, "commands")) {
	    if (anonymous && strcasestr(ARG1, "anonymous"))
		log_commands = 1;
	    if (guest && strcasestr(ARG1, "guest"))
		log_commands = 1;
	    if (!guest && !anonymous && strcasestr(ARG1, "real"))
		log_commands = 1;
	}
	if (!strcasecmp(ARG0, "transfers")) {
	    set = 0;
	    if (strcasestr(ARG1, "anonymous") && anonymous)
		set = 1;
	    if (strcasestr(ARG1, "guest") && guest)
		set = 1;
	    if (strcasestr(ARG1, "real") && !guest && !anonymous)
		set = 1;
	    if (strcasestr(ARG2, "inbound"))
		inbound = 1;
	    if (strcasestr(ARG2, "outbound"))
		outbound = 1;
	    if (set)
		log_incoming_xfers = inbound;
	    if (set)
		log_outbound_xfers = outbound;
	}
	if (!strcasecmp(ARG0, "security")) {
	    if (strcasestr(ARG1, "anonymous") && anonymous)
		log_security = 1;
	    if (strcasestr(ARG1, "guest") && guest)
		log_security = 1;
	    if (strcasestr(ARG1, "real") && !guest && !anonymous)
		log_security = 1;
	}
	if (!strcasecmp(ARG0, "syslog"))
	    syslogmsg = 1;
	if (!strcasecmp(ARG0, "xferlog"))
	    syslogmsg = 0;
	if (!strcasecmp(ARG0, "syslog+xferlog")
	    || !strcasecmp(ARG0, "xferlog+syslog"))
	    syslogmsg = [;
    }
}

/*************************************************************************/
/* FUNCTION  : acl_getclass                                              */
/* PURPOSE   : Scan the ACL buffer and determine what class user is in   */
/* ARGUMENTS : pointer to buffer to class name, pointer to ACL buffer    */
/*************************************************************************/

int acl_getclass(char *classbuf)
{
    int which;
    struct aclmember *entry = NULL;

    while (getaclentry("class", &entry)) {
	if (ARG0)
	    _strcpy(sizeof(classbuf),classbuf, ARG0);

	for (which = [; (which < MAXARGS) && ARG[which]; which++) {
	    if (anonymous && strcasestr(ARG1, "anonymous") &&
		hostmatch(ARG[which], remoteaddr, remotehost))
		return (1);

	    if (guest && strcasestr(ARG1, "guest") && hostmatch(ARG[which], remoteaddr, remotehost))
		return (1);

	    if (!guest && !anonymous && strcasestr(ARG1, "real") &&
		hostmatch(ARG[which], remoteaddr, remotehost))
		return (1);
	}
    }

    *classbuf = (char) NULL;
    return (0);

}

/*************************************************************************/
/* FUNCTION  : acl_getlimit                                              */
/* PURPOSE   : Scan the ACL buffer and determine what limit applies to   */
/*             the user                                                  */
/* ARGUMENTS : pointer class name, pointer to ACL buffer                 */
/*************************************************************************/

int acl_getlimit(char *class, char *msgpathbuf)
{
    int limit;
    struct aclmember *entry = NULL;

    if (msgpathbuf)
	*msgpathbuf = '\0';

    /* limit <class> <n> <times> [<message_file>] */
    while (getaclentry("limit", &entry)) {
	if (!ARG0 || !ARG1 || !ARG2)
	    continue;
	if (!strcasecmp(class, ARG0)) {
	    limit = atoi(ARG1);
	    if (validtime(ARG2)) {
		if (ARG3 && msgpathbuf)
		    _strcpy(sizeof(msgpathbuf),msgpathbuf, ARG3);
		return (limit);
	    }
	}
    }
    return (-1);
}

/*************************************************************************/
/* FUNCTION  : acl_getnice                                               */
/* PURPOSE   : Scan the ACL buffer and determine what nice value applies */
/*             to the user                                               */
/* ARGUMENTS : pointer class name                                        */
/*************************************************************************/

int acl_getnice(char *class)
{
    int nice_delta_for_class_found = 0;
    int nice_delta = 0;
    int default_nice_delta = 0;

    struct aclmember *entry = NULL;

    /* nice <nice_delta> [<class>] */
    while (getaclentry("nice", &entry)) {
	if (!ARG0)
	    continue;
	if (!ARG1)
	    default_nice_delta = atoi(ARG0);
	else if (!strcasecmp(class, ARG1)) {
	    nice_delta_for_class_found = 1;
	    nice_delta = atoi(ARG0);
	}
    }
    if (!nice_delta_for_class_found)
	nice_delta = default_nice_delta;
    return nice_delta;
}


/*************************************************************************/
/* FUNCTION  : acl_getdefumask                                           */
/* PURPOSE   : Scan the ACL buffer to determine what umask value applies */
/*             to the user                                               */
/* ARGUMENTS : pointer to class name                                     */
/*************************************************************************/

void acl_getdefumask(char *class)
{
    struct aclmember *entry = NULL;

    /* defumask <umask> [<class>] */
    while (getaclentry("defumask", &entry)) {
	if (!ARG0)
	    continue;
	if (!ARG1)
	    defumask = strtoul(ARG0, NULL, 0);
	else if (!strcasecmp(class, ARG1)) {
	    defumask = strtoul(ARG0, NULL, 0);
	    break;
	}
    }
    umask(defumask);
}

/*************************************************************************/
/* FUNCTION  : acl_tcpwindow                                             */
/* PURPOSE   : Scan the ACL buffer and determine what TCP window size to */
/*             use based upon the class                                  */
/* ARGUMENTS : pointer to class name                                     */
/*************************************************************************/

void acl_tcpwindow(char *class)
{
    struct aclmember *entry = NULL;

    /* tcpwindow <size> [<class>] */
    while (getaclentry("tcpwindow", &entry)) {
	if (!ARG0)
	    continue;
	if (!ARG1)
	    TCPwindowsize = strtoul(ARG0, NULL, 0);
	else if (!strcasecmp(class, ARG1)) {
	    TCPwindowsize = strtoul(ARG0, NULL, 0);
	    break;
	}
    }
}

#ifdef TRANSFER_COUNT
#ifdef TRANSFER_LIMIT

/*************************************************************************/
/* FUNCTION  : acl_filelimit                                             */
/* PURPOSE   : Scan the ACL buffer and determine what file limit to use  */
/*             based upon the class                                      */
/* ARGUMENTS : pointer to class name                                     */
/*************************************************************************/

void acl_filelimit(char *class)
{
    struct aclmember *entry = NULL;
    int raw_in = 0;
    int raw_out = 0;
    int raw_total = 0;
    int data_in = 0;
    int data_out = 0;
    int data_total = 0;
    extern int file_limit_raw_in;
    extern int file_limit_raw_out;
    extern int file_limit_raw_total;
    extern int file_limit_data_in;
    extern int file_limit_data_out;
    extern int file_limit_data_total;

    /* file-limit [<raw>] <in|out|total> <count> [<class>] */
    while (getaclentry("file-limit", &entry)) {
	if (!ARG0 || !ARG1)
	    continue;
	if (!strcasecmp(ARG0, "raw")) {
	    if (!ARG2)
		continue;
	    if (!strcasecmp(ARG1, "in")) {
		if (!ARG3) {
		    if (!raw_in)
			file_limit_raw_in = atoi(ARG2);
		}
		else if (!strcasecmp(class, ARG3)) {
		    raw_in = 1;
		    file_limit_raw_in = atoi(ARG2);
		}
	    }
	    else if (!strcasecmp(ARG1, "out")) {
		if (!ARG3) {
		    if (!raw_out)
			file_limit_raw_out = atoi(ARG2);
		}
		else if (!strcasecmp(class, ARG3)) {
		    raw_out = 1;
		    file_limit_raw_out = atoi(ARG2);
		}
	    }
	    else if (!strcasecmp(ARG1, "total")) {
		if (!ARG3) {
		    if (!raw_total)
			file_limit_raw_total = atoi(ARG2);
		}
		else if (!strcasecmp(class, ARG3)) {
		    raw_total = 1;
		    file_limit_raw_total = atoi(ARG2);
		}
	    }
	}
	else if (!strcasecmp(ARG0, "in")) {
	    if (!ARG2) {
		if (!data_in)
		    file_limit_data_in = atoi(ARG1);
	    }
	    else if (!strcasecmp(class, ARG2)) {
		data_in = 1;
		file_limit_data_in = atoi(ARG1);
	    }
	}
	else if (!strcasecmp(ARG0, "out")) {
	    if (!ARG2) {
		if (!data_out)
		    file_limit_data_out = atoi(ARG1);
	    }
	    else if (!strcasecmp(class, ARG2)) {
		data_out = 1;
		file_limit_data_out = atoi(ARG1);
	    }
	}
	else if (!strcasecmp(ARG0, "total")) {
	    if (!ARG2) {
		if (!data_total)
		    file_limit_data_total = atoi(ARG1);
	    }
	    else if (!strcasecmp(class, ARG2)) {
		data_total = 1;
		file_limit_data_total = atoi(ARG1);
	    }
	}
    }
}

/*************************************************************************/
/* FUNCTION  : acl_datalimit                                             */
/* PURPOSE   : Scan the ACL buffer and determine what data limit to use  */
/*             based upon the class                                      */
/* ARGUMENTS : pointer to class name                                     */
/*************************************************************************/

void acl_datalimit(char *class)
{
    struct aclmember *entry = NULL;
    int raw_in = 0;
    int raw_out = 0;
    int raw_total = 0;
    int data_in = 0;
    int data_out = 0;
    int data_total = 0;
    extern int data_limit_raw_in;
    extern int data_limit_raw_out;
    extern int data_limit_raw_total;
    extern int data_limit_data_in;
    extern int data_limit_data_out;
    extern int data_limit_data_total;

    /* data-limit [<raw>] <in|out|total> <count> [<class>] */
    while (getaclentry("data-limit", &entry)) {
	if (!ARG0 || !ARG1)
	    continue;
	if (!strcasecmp(ARG0, "raw")) {
	    if (!ARG2)
		continue;
	    if (!strcasecmp(ARG1, "in")) {
		if (!ARG3) {
		    if (!raw_in)
			data_limit_raw_in = atoi(ARG2);
		}
		else if (!strcasecmp(class, ARG3)) {
		    raw_in = 1;
		    data_limit_raw_in = atoi(ARG2);
		}
	    }
	    else if (!strcasecmp(ARG1, "out")) {
		if (!ARG3) {
		    if (!raw_out)
			data_limit_raw_out = atoi(ARG2);
		}
		else if (!strcasecmp(class, ARG3)) {
		    raw_out = 1;
		    data_limit_raw_out = atoi(ARG2);
		}
	    }
	    else if (!strcasecmp(ARG1, "total")) {
		if (!ARG3) {
		    if (!raw_total)
			data_limit_raw_total = atoi(ARG2);
		}
		else if (!strcasecmp(class, ARG3)) {
		    raw_total = 1;
		    data_limit_raw_total = atoi(ARG2);
		}
	    }
	}
	else if (!strcasecmp(ARG0, "in")) {
	    if (!ARG2) {
		if (!data_in)
		    data_limit_data_in = atoi(ARG1);
	    }
	    else if (!strcasecmp(class, ARG2)) {
		data_in = 1;
		data_limit_data_in = atoi(ARG1);
	    }
	}
	else if (!strcasecmp(ARG0, "out")) {
	    if (!ARG2) {
		if (!data_out)
		    data_limit_data_out = atoi(ARG1);
	    }
	    else if (!strcasecmp(class, ARG2)) {
		data_out = 1;
		data_limit_data_out = atoi(ARG1);
	    }
	}
	else if (!strcasecmp(ARG0, "total")) {
	    if (!ARG2) {
		if (!data_total)
		    data_limit_data_total = atoi(ARG1);
	    }
	    else if (!strcasecmp(class, ARG2)) {
		data_total = 1;
		data_limit_data_total = atoi(ARG1);
	    }
	}
    }
}


#ifdef RATIO

/*************************************************************************/
/* FUNCTION  : acl_downloadrate                                          */
/* PURPOSE   : Scan the ACL buffer and determine what data limit to use  */
/*             based upon the class                                      */
/* ARGUMENTS : pointer to class name                                     */
/*************************************************************************/

void acl_downloadrate(char *class)
{
    struct aclmember *entry = NULL;
    extern int upload_download_rate;
    int which;

    /* ul-dl-rate <rate> [<class> ...] */
    while (getaclentry("ul-dl-rate", &entry)) {
	if (!ARG0 )
	    continue;

	if (!ARG1) {
	    upload_download_rate = atol(ARG0);
	}
	else {
	    for (which = 1; (which < MAXARGS) && ARG[which]; which++) {
		if (!strcasecmp(ARG[which], class))
		    upload_download_rate = atol(ARG0);
	    }
	}

    }
}
#endif /* RATIO */

#endif
#endif

/*************************************************************************/
/* FUNCTION  : acl_deny                                                  */
/* PURPOSE   : Scan the ACL buffer and determine a deny command applies  */
/* ARGUMENTS : pointer class name, pointer to ACL buffer                 */
/*************************************************************************/

int acl_deny(char *msgpathbuf)
{
    struct aclmember *entry = NULL;

    if (msgpathbuf)
	*msgpathbuf = (char) NULL;

    /* deny <addrglob> [<message_file>] */
    while (getaclentry("deny", &entry)) {
	if (!ARG0)
	    continue;
	if (strcasecmp(ARG0, "!nameserved") == 0) {
	    if (!nameserved) {
		if (ARG1)
		    _strcpy(sizeof(msgpathbuf),msgpathbuf, entry->arg[1]);
		return (1);
	    }
	}
	else if (hostmatch(ARG0, remoteaddr, remotehost)) {
	    if (ARG1)
		_strcpy(sizeof(msgpathbuf),msgpathbuf, entry->arg[1]);
	    return (1);
	}
    }
    return (0);
}

/*************************************************************************/
/* FUNCTION  : acl_countusers                                            */
/* PURPOSE   : Check the anonymous FTP access lists to see if this       */
/*             access is permitted.                                      */
/* ARGUMENTS : none                                                      */
/*************************************************************************/

int acl_countusers(char *class)
{
    int count, which;
    char pidfile[MAXPATHLEN];
    pid_t buf[MAXUSERS];
#ifndef HAVE_FLOCK
    struct flock arg;
#endif

    if (Bypass_PID_Files)
	return (0);
    /* 
     * if pidfd was not opened previously... 
     * pidfd must stay open after the chroot(~ftp)  
     */

    /*warning: This function sprintf() has a buffer overflow security problem*/sprintf(pidfile, _PATH_PIDNAMES, class);

    if (pidfd < 0) {
	mode_t oldmask;
	oldmask = umask(0);
	pidfd = open(pidfile, O_RDWR | O_CREAT, 0644);
	(void) umask(oldmask);
    }

    if (pidfd < 0) {
	syslog(LOG_ERR, "cannot open pid file %s: %m", pidfile);
	return -1;
    }

#ifdef HAVE_FLOCK
    while (flock(pidfd, LOCK_EX)) {
#ifndef NO_PID_SLEEP_MSGS
	syslog(LOG_ERR, "sleeping: flock of pid file failed: %m");
#endif
#else
    arg.l_type = F_WRLCK;
    arg.l_whence = arg.l_start = arg.l_len = 0;
    while (-1 == fcntl(pidfd, F_SETLK, &arg)) {
#ifndef NO_PID_SLEEP_MSGS
	syslog(LOG_ERR, "sleeping: fcntl lock of pid file failed: %m");
#endif
#endif
	sleep(1);
    }
    lseek(pidfd, (off_t) 0, SEEK_SET);

    count = 0;

    if (read(pidfd, (void *) buf, sizeof(buf)) == sizeof(buf)) {
	for (which = 0; which < MAXUSERS; which++)
	    if (buf[which] && !kill(buf[which], 0))
		count++;
    }
#ifdef HAVE_FLOCK
    flock(pidfd, LOCK_UN);
#else
    arg.l_type = F_UNLCK;
    arg.l_whence = arg.l_start = arg.l_len = 0;
    fcntl(pidfd, F_SETLK, &arg);
#endif
    return (count);
}

/*************************************************************************/
/* FUNCTION  : acl_join                                                  */
/* PURPOSE   : Add the current process to the list of processes in the   */
/*             specified class.                                          */
/* ARGUMENTS : The name of the class to join                             */
/*************************************************************************/

void acl_join(char *class)
{
    int which, avail;
    pid_t buf[MAXUSERS];
    char pidfile[MAXPATHLEN];
    pid_t procid;
#ifndef HAVE_FLOCK
    struct flock arg;
#endif

    if (Bypass_PID_Files)
	return;

    /* 
     * if pidfd was not opened previously... 
     * pidfd must stay open after the chroot(~ftp)  
     */

    /*warning: This function sprintf() has a buffer overflow security problem*/sprintf(pidfile, _PATH_PIDNAMES, class);

    if (pidfd < 0) {
	mode_t oldmask;
	oldmask = umask(0);
	pidfd = open(pidfile, O_RDWR | O_CREAT, 0644);
	(void) umask(oldmask);
    }

    if (pidfd < 0) {
	syslog(LOG_ERR, "cannot open pid file %s: %m", pidfile);
	return;
    }

#ifdef HAVE_FLOCK
    while (flock(pidfd, LOCK_EX)) {
#ifndef NO_PID_SLEEP_MSGS
	syslog(LOG_ERR, "sleeping: flock of pid file failed: %m");
#endif
#else
    arg.l_type = F_WRLCK;
    arg.l_whence = arg.l_start = arg.l_len = 0;
    while (-1 == fcntl(pidfd, F_SETLK, &arg)) {
#ifndef NO_PID_SLEEP_MSGS
	syslog(LOG_ERR, "sleeping: fcntl lock of pid file failed: %m");
#endif
#endif
	sleep(1);
    }

    procid = getpid();

    lseek(pidfd, (off_t) 0, SEEK_SET);
    if (read(pidfd, (void *) buf, sizeof(buf)) < sizeof(buf))
	for (which = 0; which < MAXUSERS; buf[which++] = 0)
	    continue;

    avail = 0;
    for (which = 0; which < MAXUSERS; which++) {
	if ((buf[which] == 0) || (kill(buf[which], 0) == -1)) {
	    avail = which;
	    buf[which] = 0;
	}
	else if (buf[which] == procid) {
	    /* already exists in pid file... */
#ifdef HAVE_FLOCK
	    flock(pidfd, LOCK_UN);
#else
	    arg.l_type = F_UNLCK;
	    arg.l_whence = arg.l_start = arg.l_len = 0;
	    fcntl(pidfd, F_SETLK, &arg);
#endif
	    return;
	}
    }

    buf[avail] = procid;

    lseek(pidfd, (off_t) 0, SEEK_SET);
    write(pidfd, (void *) buf, sizeof(buf));
#ifdef HAVE_FLOCK
    flock(pidfd, LOCK_UN);
#else
    arg.l_type = F_UNLCK;
    arg.l_whence = arg.l_start = arg.l_len = 0;
    fcntl(pidfd, F_SETLK, &arg);
#endif

}

/*************************************************************************/
/* FUNCTION  : acl_remove                                                */
/* PURPOSE   : remove the current process to the list of processes in    */
/*             the specified class.                                      */
/* ARGUMENTS : The name of the class to remove                           */
/*************************************************************************/

void acl_remove(void)
{
    char class[1024];
    int which, avail;
    pid_t buf[MAXUSERS];
    char pidfile[MAXPATHLEN];
    pid_t procid;
#ifndef HAVE_FLOCK
    struct flock arg;
#endif

    if (Bypass_PID_Files)
	return;

    if (!acl_getclass(class)) {
	return;
    }

    /* 
     * if pidfd was not opened previously... 
     * pidfd must stay open after the chroot(~ftp)  
     */

    /*warning: This function sprintf() has a buffer overflow security problem*/sprintf(pidfile, _PATH_PIDNAMES, class);

    if (pidfd < 0) {
	mode_t oldmask;
	oldmask = umask(0);
	pidfd = open(pidfile, O_RDWR | O_CREAT, 0644);
	(void) umask(oldmask);
    }

    if (pidfd < 0) {
	syslog(LOG_ERR, "cannot open pid file %s: %m", pidfile);
	return;
    }

#ifdef HAVE_FLOCK
    while (flock(pidfd, LOCK_EX)) {
#ifndef NO_PID_SLEEP_MSGS
	syslog(LOG_ERR, "sleeping: flock of pid file failed: %m");
#endif
#else
    arg.l_type = F_WRLCK;
    arg.l_whence = arg.l_start = arg.l_len = 0;
    while (-1 == fcntl(pidfd, F_SETLK, &arg)) {
#ifndef NO_PID_SLEEP_MSGS
	syslog(LOG_ERR, "sleeping: fcntl lock of pid file failed: %m");
#endif
#endif
	sleep(1);
    }

    procid = getpid();

    lseek(pidfd, (off_t) 0, SEEK_SET);
    if (read(pidfd, (void *) buf, sizeof(buf)) < sizeof(buf))
	for (which = 0; which < MAXUSERS; buf[which++] = 0)
	    continue;

    avail = 0;
    for (which = 0; which < MAXUSERS; which++) {
	if ((buf[which] == 0) || (kill(buf[which], 0) == -1)) {
	    avail = which;
	    buf[which] = 0;
	}
	else if (buf[which] == procid) {
	    buf[which] = 0;
	}
    }

    lseek(pidfd, (off_t) 0, SEEK_SET);
    write(pidfd, (void *) buf, sizeof(buf));
#ifdef HAVE_FLOCK
    flock(pidfd, LOCK_UN);
#else
    arg.l_type = F_UNLCK;
    arg.l_whence = arg.l_start = arg.l_len = 0;
    fcntl(pidfd, F_SETLK, &arg);
#endif

    close(pidfd);
    pidfd = -1;
}

/*************************************************************************/
/* FUNCTION  : pr_mesg                                                   */
/* PURPOSE   : Display a message to the user                             */
/* ARGUMENTS : message code, name of file to display                     */
/*************************************************************************/

void pr_mesg(int msgcode, char *msgfile)
{
    FILE *infile;
    char inbuf[1024], outbuf[1024], *cr;

    if (msgfile && (int) strlen(msgfile) > 0) {
	infile = fopen(msgfile, "r");
	if (infile) {
	    while (fgets(inbuf, sizeof(inbuf), infile) != NULL) {
		if ((cr = strchr(inbuf, '\n')) != NULL)
		    *cr = '\0';
		msg_massage(inbuf, outbuf, sizeof(outbuf));
		lreply(msgcode, "%s", outbuf);
	    }
	    fclose(infile);
	}
    }
}

/*************************************************************************/
/* FUNCTION  : access_init                                               */
/* PURPOSE   : Read and parse the access lists to set things up          */
/* ARGUMENTS : none                                                      */
/*************************************************************************/

void access_init(void)
{
    struct aclmember *entry;

    if (!readacl(_path_ftpaccess))
	return;
    (void) parseacl();

    Shutdown[0] = '\0';
    entry = (struct aclmember *) NULL;
    if (getaclentry("shutdown", &entry) && ARG0 != NULL)
	(void) strlcpy(sizeof(Shutdown),Shutdown, ARG0, sizeof(Shutdown));
#ifdef OTHER_PASSWD
    entry = (struct aclmember *) NULL;
    while (getaclentry("passwd", &entry) && ARG0 != NULL) {
	    _strcpy(sizeof(_path_passwd),_path_passwd, ARG0);
#ifdef USE_PAM
	    use_pam = 0;
#endif
    }
#ifdef SHADOW_PASSWORD
    entry = (struct aclmember *) NULL;
    while (getaclentry("shadow", &entry) && ARG0 != NULL) {
	    _strcpy(sizeof(_path_shadow),_path_shadow, ARG0);
#ifdef USE_PAM
	    use_pam = 0;
#endif
    }
#endif
#endif
    entry = (struct aclmember *) NULL;
    if (getaclentry("keepalive", &entry) && ARG0 != NULL)
	if (!strcasecmp(ARG0, "yes"))
	    keepalive = 1;
    load_timeouts();
}

/*************************************************************************/
/* FUNCTION  : access_ok                                                 */
/* PURPOSE   : Check the anonymous FTP access lists to see if this       */
/*             access is permitted.                                      */
/* ARGUMENTS : none                                                      */
/*************************************************************************/

int access_ok(int msgcode)
{
    char class[1024], msgfile[MAXPATHLEN];
    int limit;
    int nice_delta;

    if (!use_accessfile)
	return (1);

    if (aclbuf == NULL) {
	syslog(LOG_NOTICE,
	       "ACCESS DENIED (error reading access file) TO %s",
	       remoteident);
	return (0);
    }
    if (acl_deny(msgfile)) {
#ifndef HELP_CRACKERS
	_memcpy(sizeof(DelayedMessageFile),DelayedMessageFile, msgfile, sizeof(msgfile));
#else
	pr_mesg(msgcode, msgfile);
#endif
	syslog(LOG_NOTICE, "ACCESS DENIED (deny command) TO %s",
	       remoteident);
	return (0);
    }
    /* if user is not in any class, deny access */
    if (!acl_getclass(class)) {
	syslog(LOG_NOTICE, "ACCESS DENIED (not in any class) TO %s",
	       remoteident);
	return (0);
    }
    if ((nice_delta = acl_getnice(class))) {
	if (nice_delta < 0)
	    syslog(LOG_NOTICE, "Process nice value adjusted by %d", nice_delta);
	nice(nice_delta);
    }
    acl_getdefumask(class);
    acl_tcpwindow(class);
#ifdef TRANSFER_COUNT
#ifdef TRANSFER_LIMIT
    acl_filelimit(class);
    acl_datalimit(class);
#ifdef RATIO
    acl_downloadrate(class);
#endif
#endif
#endif
    /* if no limits defined, no limits apply -- access OK */
    limit = acl_getlimit(class, msgfile);

    if ((limit == -1) || (acl_countusers(class) < limit)) {
	acl_join(class);
	return (1);
    }
    else {
#ifdef LOG_TOOMANY
	syslog(LOG_NOTICE, "ACCESS DENIED (user limit %d; class %s) TO %s",
	       limit, class, remoteident);
#endif
#ifndef HELP_CRACKERS
	_memcpy(sizeof(DelayedMessageFile),DelayedMessageFile, msgfile, sizeof(msgfile));
#else
	pr_mesg(msgcode, msgfile);
#endif
	return (-1);
    }

    /* NOTREACHED */
}
/****************************************************************************  
  $Id: acl.c,v 1.9 2000/07/01 18:17:38 wuftpd Exp $
****************************************************************************/
#include "config.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#ifdef HAVE_SYS_SYSLOG_H
#include <sys/syslog.h>
#endif
#if defined(HAVE_SYSLOG_H) || (!defined(AUTOCONF) && !defined(HAVE_SYS_SYSLOG_H))
#include <syslog.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

#ifdef HAVE_PATHS_H
#include <paths.h>
#endif
#include "pathnames.h"
#include "extensions.h"
#include "proto.h"

char *aclbuf = NULL;
static struct aclmember *aclmembers;

/*************************************************************************/
/* FUNCTION  : getaclentry                                               */
/* PURPOSE   : Retrieve a named entry from the ACL                       */
/* ARGUMENTS : pointer to the keyword and a handle to the acl members    */
/* RETURNS   : pointer to the acl member containing the keyword or NULL  */
/*************************************************************************/

struct aclmember *getaclentry(char *keyword, struct aclmember **next)
{
    do {
	if (!*next)
	    *next = aclmembers;
	else
	    *next = (*next)->next;
    } while (*next && strcasecmp((*next)->keyword, keyword));

    return (*next);
}

/*************************************************************************/
/* FUNCTION  : parseacl                                                  */
/* PURPOSE   : Parse the acl buffer into its components                  */
/* ARGUMENTS : A pointer to the acl file                                 */
/* RETURNS   : nothing                                                   */
/*************************************************************************/

void parseacl(void)
{
    char *ptr, *aclptr = aclbuf, *line;
    int cnt;
    struct aclmember *member, *acltail;

    if (!aclbuf || !(*aclbuf))
	return;

    aclmembers = (struct aclmember *) NULL;
    acltail = (struct aclmember *) NULL;

    while (*aclptr != '\0') {
	line = aclptr;
	while (*aclptr && *aclptr != '\n')
	    aclptr++;
	*aclptr++ = (char) NULL;

	/* deal with comments */
	if ((ptr = strchr(line, '#')) != NULL)
	    /* allowed escaped '#' chars for path-filter (DiB) */
	    if ((ptr > aclbuf) && (*(ptr - 1) != '\\'))
		*ptr = '\0';

	ptr = strtok(line, " \t");
	if (ptr) {
	    member = (struct aclmember *) calloc(1, sizeof(struct aclmember));

	    if (member == NULL) {
		syslog(LOG_ERR, "calloc error parsing acl");
		exit(0);
	    }
	    (void) _strcpy(sizeof(member->keyword),member->keyword, ptr);
	    cnt = 0;
	    while ((ptr = strtok(NULL, " \t")) != NULL) {
		if (cnt >= MAXARGS) {
		    syslog(LOG_ERR,
		     "Too many args (>%d) in ftpaccess: %s %s %s %s %s ...",
			   MAXARGS - 1, member->keyword, member->arg[0],
			   member->arg[1], member->arg[2], member->arg[3]);
		    break;
		}
		member->arg[cnt++] = ptr;
	    }
	    if (acltail)
		acltail->next = member;
	    acltail = member;
	    if (!aclmembers)
		aclmembers = member;
	}
    }
}

/*************************************************************************/
/* FUNCTION  : readacl                                                   */
/* PURPOSE   : Read the acl into memory                                  */
/* ARGUMENTS : The pathname of the acl                                   */
/* RETURNS   : 0 if error, 1 if no error                                 */
/*************************************************************************/

int readacl(char *aclpath)
{
    FILE *aclfile;
    struct stat finfo;
    extern int use_accessfile;

    if (!use_accessfile)
	return (0);

    if ((aclfile = fopen(aclpath, "r")) == NULL) {
	syslog(LOG_ERR, "cannot open access file %s: %s", aclpath,
	       strerror(errno));
	return (0);
    }
    if (fstat(fileno(aclfile), &finfo) != 0) {
	syslog(LOG_ERR, "cannot fstat access file %s: %s", aclpath,
	       strerror(errno));
	(void) fclose(aclfile);
	return (0);
    }
    if (finfo.st_size == 0) {
	aclbuf = (char *) calloc(1, 1);
    }
    else {
	if (!(aclbuf = (char *) malloc((unsigned) finfo.st_size + 1))) {
	    syslog(LOG_ERR, "could not malloc aclbuf (%d bytes)", finfo.st_size + 1);
	    (void) fclose(aclfile);
	    return (0);
	}
	if (!fread(aclbuf, (size_t) finfo.st_size, 1, aclfile)) {
	    syslog(LOG_ERR, "error reading acl file %s: %s", aclpath,
		   strerror(errno));
	    free(aclbuf);
	    aclbuf = NULL;
	    (void) fclose(aclfile);
	    return (0);
	}
	*(aclbuf + finfo.st_size) = '\0';
    }
    (void) fclose(aclfile);
    return (1);
}
/****************************************************************************  
  $Id: auth.c,v 1.6 2000/07/01 18:17:38 wuftpd Exp $ 
****************************************************************************/
#include "config.h"
#ifdef	BSD_AUTH
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <pwd.h>
#include <signal.h>
#include <stdlib.h>

#include <syslog.h>

#include <login_cap.h>

int ext_auth = 0;
login_cap_t *class = NULL;
static char *challenge = NULL;

char *start_auth(char *style, char *name, struct passwd *pwd)
{
    int s;

    ext_auth = 1;		/* authentication is always external */

    if (challenge)
	free(challenge);
    challenge = NULL;

    if (!(class = login_getclass(pwd ? pwd->pw_class : 0)))
	return (NULL);

    if (pwd && pwd->pw_passwd[0] == '\0')
	return (NULL);

    if ((style = login_getstyle(class, style, "auth-ftp")) == NULL)
	return (NULL);

    if (auth_check(name, class->lc_class, style, "challenge", &s) < 0)
	return (NULL);

    if ((s & AUTH_CHALLENGE) == 0)
	return (NULL);

    challenge = auth_value("challenge");
    return (challenge);
}

char *check_auth(char *name, char *passwd)
{
    char *e;
    int r;

    if (ext_auth == 0)
	return ("Login incorrect.");
    ext_auth = 0;

    r = auth_response(name, class->lc_class, class->lc_style, "response",
		      NULL, challenge ? challenge : "", passwd);

    if (challenge)
	free(challenge);
    challenge = NULL;

    if (r <= 0) {
	e = auth_value("errormsg");
	return (e ? e : "Login incorrect.");
    }

    if (!auth_approve(class, name, "ftp")) {
	syslog(LOG_INFO | LOG_AUTH,
	       "FTP LOGIN FAILED (HOST) as %s: approval failure.", name);
	return ("Approval failure.");
    }


    return (NULL);
}
#endif
/****************************************************************************  
  $Id: authenticate.c,v 1.9 2000/07/01 18:17:38 wuftpd Exp $ 
****************************************************************************/
#include "config.h"
#include <stdio.h>
#include <string.h>
#include "support/authuser.h"
#include "authenticate.h"
#include "proto.h"

#define AUTHNAMESIZE 100

char authuser[AUTHNAMESIZE];
int authenticated;

extern int disable_rfc931;
extern unsigned int timeout_rfc931;

/*
 * Ideally more authentication schemes would be called from here, with the
 * strongest called first.  One possible double-check would be to verify that
 * the results of all authentication calls (returning identical data!) are
 * checked against each other.
 */
int wu_authenticate(void)
{
    char *user;
#if USE_A_RFC931
    unsigned long in;
    unsigned short local, remote;
#endif /* USE_A_RFC931 */

    authenticated = 0;		/* this is a bitmask, one bit per method */

    user = "*";

#if USE_A_RFC931
    if (disable_rfc931 || (timeout_rfc931 == 0))
	user = "*";
    else if (auth_fd(0, &in, &local, &remote) == -1)
	user = "?";		/* getpeername/getsockname failure */
    else {
	if (!(user = auth_tcpuser(in, local, remote)))
	    user = "*";		/* remote host doesn't support RFC 931 */
	else
	    authenticated |= A_RFC931;
    }
#endif /* USE_A_RFC931 */

    strlcpy(sizeof(authuser),authuser, user, sizeof(authuser));
    authuser[AUTHNAMESIZE - 1] = '\0';
    return (0);
}
/****************************************************************************  
 $Id: extensions.c,v 1.48 2000/07/01 18:17:38 wuftpd Exp $ 
****************************************************************************/
#include "config.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef HAVE_SYS_SYSLOG_H
#include <sys/syslog.h>
#elif defined(HAVE_SYSLOG_H) || !defined(AUTOCONF)
#include <syslog.h>
#endif

#ifdef TIME_WITH_SYS_TIME
#include <time.h>
#include <sys/time.h>
#else
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#include <time.h>
#endif
#endif
#include <pwd.h>
#include <setjmp.h>
#include <grp.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/param.h>

#ifdef HAVE_SYS_FS_UFS_QUOTA_H
#include <sys/fs/ufs_quota.h>
#elif defined(HAVE_UFS_UFS_QUOTA_H)
#include <ufs/ufs/quota.h>
#elif defined(HAVE_UFS_QUOTA_H)
#include <ufs/quota.h>
#elif defined(HAVE_SYS_MNTENT_H)
#include <sys/mntent.h>
#elif defined(HAVE_SYS_MNTTAB_H)
#include <sys/mnttab.h>
#endif

#if defined(HAVE_STATVFS)
#include <sys/statvfs.h>
#elif defined(HAVE_SYS_VFS)
#include <sys/vfs.h>
#elif defined(HAVE_SYS_MOUNT)
#include <sys/mount.h>
#endif

#include "../support/ftp.h"

#ifdef HAVE_PATHS_H
#include <paths.h>
#endif
#include "pathnames.h"
#include "extensions.h"
#include "wu_fnmatch.h"
#include "proto.h"

#if defined(HAVE_FTW)
#include <ftw.h>
#else
#include "support/ftw.h"
#endif

#ifdef QUOTA
struct dqblk quota;
char *time_quota(long curstate, long softlimit, long timelimit, char *timeleft);
#endif

#ifdef HAVE_REGEX_H
#include <regex.h>
#endif

#if defined(HAVE_REGEX) && defined(SVR4) && ! (defined(NO_LIBGEN))
#include <libgen.h>
#endif

extern int type, transflag, ftwflag, authenticated, autospout_free, data,
    pdata, anonymous, guest;

#ifdef TRANSFER_COUNT
extern int data_count_total;	/* total number of data bytes */
extern int data_count_in;
extern int data_count_out;
extern int byte_count_total;	/* total number of general traffic */
extern int byte_count_in;
extern int byte_count_out;
extern int file_count_total;	/* total number of data files */
extern int file_count_in;
extern int file_count_out;
extern int xfer_count_total;	/* total number of transfers */
extern int xfer_count_in;
extern int xfer_count_out;
#ifdef TRANSFER_LIMIT  
extern int file_limit_raw_in;
extern int file_limit_raw_out;
extern int file_limit_raw_total;
extern int file_limit_data_in;  
extern int file_limit_data_out; 
extern int file_limit_data_total;
extern int data_limit_raw_in;
extern int data_limit_raw_out;
extern int data_limit_raw_total;
extern int data_limit_data_in;  
extern int data_limit_data_out; 
extern int data_limit_data_total;
#ifdef RATIO /* 1998/08/06 K.Wakui */
#define TRUNC_KB(n)   ((n)/1024+(((n)%1024)?1:0))
extern time_t	login_time;
extern time_t	limit_time;
extern off_t    total_free_dl;
extern int      upload_download_rate;
#endif /* RATIO */
#endif
#endif

#ifdef OTHER_PASSWD
#include "getpwnam.h"
extern char _path_passwd[];
#endif

#ifdef LOG_FAILED
extern char the_user[];
#endif

extern char *globerr, remotehost[];
#ifdef THROUGHPUT
extern char remoteaddr[];
#endif

#ifndef HAVE_REGEX
char *re_comp(const char *regex);
int re_exec(const char *p1);
#endif

char shuttime[30], denytime[30], disctime[30];

FILE *dout;

time_t newer_time;

int show_fullinfo;

/* This always was a bug, because neither st_size nor time_t were required to
   be compatible with int, but needs fixing properly for C9X. */

/* Some systems use one format, some another.  This takes care of the garbage */
/* Do the system specific stuff only if we aren't autoconfed */
#if !defined(L_FORMAT)
#if (defined(BSD) && (BSD >= 199103)) && !defined(LONGOFF_T)
#define L_FORMAT "qd"
#else
#define L_FORMAT "d"
#endif
#endif
#if !defined(T_FORMAT)
#define T_FORMAT "d"
#endif
#if !defined(PW_UID_FORMAT)
#define PW_UID_FORMAT "d"
#endif
#if !defined(GR_GID_FORMAT)
#define GR_GID_FORMAT "d"
#endif

int snprintf(char *str, size_t count, const char *fmt,...);

int check_newer(char *path, struct stat *st, int flag)
{
    if (st->st_mtime > newer_time) {
	if (show_fullinfo != 0) {
	    if (flag == FTW_F || flag == FTW_D) {
		fprintf(dout, "%s %" L_FORMAT " %" T_FORMAT " %s\n",
			flag == FTW_F ? "F" : "D",
			st->st_size, st->st_mtime, path);
	    }
	}
	else if (flag == FTW_F)
	    fprintf(dout, "%s\n", path);
    }

    /* When an ABOR has been received (which sets ftwflag > 1) return a
     * non-zero value which causes ftw to stop tree traversal and return. 
     */

    return (ftwflag > 1 ? 1 : 0);
}

#if defined(HAVE_STATVFS)
long getSize(char *s)
{
    int c;
    struct statvfs buf;

    if ((c = statvfs(s, &buf)) != 0)
	return (0);

    return (buf.f_bavail * buf.f_frsize / 1024);
}
#elif defined(HAVE_SYS_VFS) || defined (HAVE_SYS_MOUNT)
long getSize(char *s)
{
    int c;
    struct statfs buf;

    if ((c = statfs(s, &buf)) != 0)
	return (0);

    return (buf.f_bavail * buf.f_bsize / 1024);
}
#endif

/*************************************************************************/
/* FUNCTION  : msg_massage                                               */
/* PURPOSE   : Scan a message line for magic cookies, replacing them as  */
/*             needed.                                                   */
/* ARGUMENTS : pointer input and output buffers                          */
/*************************************************************************/

void msg_massage(const char *inbuf, char *outbuf, size_t outlen)
{
    const char *inptr = inbuf;
    char *outptr = outbuf;
#ifdef QUOTA
    char timeleft[80];
#endif
    char buffer[MAXPATHLEN];
    time_t curtime;
    int limit;
#ifndef LOG_FAILED
    extern struct passwd *pw;
#endif
    struct aclmember *entry;

#ifdef VIRTUAL
    extern int virtual_mode;
    extern int virtual_ftpaccess;
    extern char virtual_email[];
#endif
    extern char hostname[];
    extern char authuser[];

    (void) acl_getclass(buffer);
    limit = acl_getlimit(buffer, NULL);

    while ((outlen > 1) && (*inptr != '\0')) {
	if (*inptr != '%') {
	    *outptr++ = *inptr;
	    outlen -= 1;
	}
	else {
	    entry = NULL;
	    switch (*++inptr) {
	    case 'E':
#ifdef VIRTUAL
		if (virtual_mode && !virtual_ftpaccess && virtual_email[0] != '\0')
		    snprintf(outptr, outlen, "%s", virtual_email);
		else
#endif
		if ((getaclentry("email", &entry)) && ARG0)
		    snprintf(outptr, outlen, "%s", ARG0);
		else
		    *outptr = '\0';
		break;

	    case 'N':
		snprintf(outptr, outlen, "%d", acl_countusers(buffer));
		break;

	    case 'M':
		if (limit == -1)
		    strlcpy(sizeof(outptr),outptr, "unlimited", outlen);
		else
		    snprintf(outptr, outlen, "%d", limit);
		break;

	    case 'T':
		(void) time(&curtime);
		strlcpy(sizeof(outptr),outptr, ctime(&curtime), outlen);
		if (outlen > 24)
		    *(outptr + 24) = '\0';
		break;

	    case 'F':
#if defined(HAVE_STATVFS) || defined(HAVE_SYS_VFS) || defined(HAVE_SYS_MOUNT)
		snprintf(outptr, outlen, "%lu", (long) getSize("."));
#else
		*outptr = '\0';
#endif
		break;

	    case 'C':
#ifdef HAVE_GETCWD
		(void) getcwd(outptr, outlen);
#else
#error	wu-ftpd on this platform has security deficiencies!!!
		(void) 
/*Warning::There is buffer overflow security problem using the following GETWD()*/
getwd(outptr);
#endif
		break;

	    case 'R':
		strlcpy(sizeof(outptr),outptr, remotehost, outlen);
		break;

	    case 'L':
		strlcpy(sizeof(outptr),outptr, hostname, outlen);
		break;

	    case 'U':
#ifdef LOG_FAILED
		strlcpy(sizeof(outptr),outptr, the_user, outlen);
#else /* LOG_FAILED */
		strlcpy(sizeof(outptr),outptr,
			(pw == NULL) ? "[unknown]" : pw->pw_name, outlen);
#endif /* LOG_FAILED */
		break;

	    case 's':
		strlcpy(sizeof(outptr),outptr, shuttime, outlen);
		if (outlen > 24)
		    *(outptr + 24) = '\0';
		break;

	    case 'd':
		strlcpy(sizeof(outptr),outptr, disctime, outlen);
		if (outlen > 24)
		    *(outptr + 24) = '\0';
		break;

	    case 'r':
		strlcpy(sizeof(outptr),outptr, denytime, outlen);
		if (outlen > 24)
		    *(outptr + 24) = '\0';
		break;

/* KH : cookie %u for RFC931 name */
	    case 'u':
		if (authenticated)
		    strlcpy(sizeof(outptr),outptr, authuser, outlen);
		else
		    strlcpy(sizeof(outptr),outptr, "[unknown]", outlen);
		break;

#ifdef QUOTA
	    case 'B':
#ifdef QUOTA_BLOCKS		/* 1024-blocks instead of 512-blocks */
		snprintf(outptr, outlen, "%ld", quota.dqb_bhardlimit % [ ?
			 (long) (quota.dqb_bhardlimit / [ + 1) : (long) (quota.dqb_bhardlimit / [));
#else
		snprintf(outptr, outlen, "%ld", (long) quota.dqb_bhardlimit);
#endif
		break;

	    case 'b':
#ifdef QUOTA_BLOCKS		/* 1024-blocks instead of 512-blocks */
		snprintf(outptr, outlen, "%ld", quota.dqb_bsoftlimit % [ ?
			 (long) (quota.dqb_bsoftlimit / [ + 1) : (long) (quota.dqb_bsoftlimit / [));
#else
		snprintf(outptr, outlen, "%ld", (long) quota.dqb_bsoftlimit);
#endif
		break;

	    case 'Q':
#ifdef QUOTA_BLOCKS		/* 1024-blocks instead of 512-blocks */
		snprintf(outptr, outlen, "%ld", quota.dqb_curblocks % [ ?
			 (long) (quota.dqb_curblocks / [ + 1) : (long) (quota.dqb_curblocks / [));
#else
		snprintf(outptr, outlen, "%ld", quota.dqb_curblocks);
#endif
		break;

	    case 'I':
#if defined(QUOTA_INODE)
		snprintf(outptr, outlen, "%d", quota.dqb_ihardlimit);
#else
		snprintf(outptr, outlen, "%ld", (long) quota.dqb_fhardlimit);
#endif
		break;

	    case 'i':
#if defined(QUOTA_INODE)
		snprintf(outptr, outlen, "%d", quota.dqb_isoftlimit);
#else
		snprintf(outptr, outlen, "%ld", (long) quota.dqb_fsoftlimit);
#endif
		break;

	    case 'q':
#if defined(QUOTA_INODE)
		snprintf(outptr, outlen, "%d", quota.dqb_curinodes);
#else
		snprintf(outptr, outlen, "%ld", (long) quota.dqb_curfiles);
#endif
		break;

	    case 'H':
		time_quota(quota.dqb_curblocks, quota.dqb_bsoftlimit,
#if defined(QUOTA_INODE)
			   quota.dqb_btime, timeleft);
#else
			   quota.dqb_btimelimit, timeleft);
#endif
		strlcpy(sizeof(outptr),outptr, timeleft, outlen);
		break;

	    case 'h':
#if defined(QUOTA_INODE)
		time_quota(quota.dqb_curinodes, quota.dqb_isoftlimit,
			   quota.dqb_itime, timeleft);
#else
		time_quota(quota.dqb_curfiles, quota.dqb_fsoftlimit,
			   quota.dqb_ftimelimit, timeleft);
#endif
		strlcpy(sizeof(outptr),outptr, timeleft, outlen);
		break;
#endif /* QUOTA */

	    case '%':
		*outptr++ = '%';
		outlen -= 1;
		*outptr = '\0';
		break;

#ifdef TRANSFER_COUNT
#ifdef TRANSFER_LIMIT
#ifdef RATIO
            case 'x':
                switch (*++inptr) {
                case 'u':       /* upload bytes */
                    sprintf(outptr,"%d", TRUNC_KB(data_count_in) );
                    break;
                case 'd':       /* download bytes */
                    sprintf(outptr,"%d", TRUNC_KB(data_count_out) );
                    break;
                case 'R':       /* rate 1:n */
                    if( upload_download_rate > 0 ) {
                        sprintf(outptr,"%d", upload_download_rate );
                    }
                    else {
                        _strcpy(sizeof(outptr),outptr,"free");
                    }
                    break;
                case 'c':       /* credit bytes */
                    if( upload_download_rate > 0 ) {
                        off_t credit=( data_count_in * upload_download_rate) - (data_count_out - total_free_dl);
                        sprintf(outptr,"%d", TRUNC_KB(credit) );
                    }
                    else {
                        _strcpy(sizeof(outptr),outptr,"unlimited");
                    }
                    break;
                case 'T':       /* time limit (minutes) */
                    if( limit_time > 0 ) {
                        sprintf(outptr,"%d", limit_time );
                    }
                    else {
                        _strcpy(sizeof(outptr),outptr,"unlimited");
                    }
                    break;
                case 'E':       /* elapsed time from loggedin (minutes) */
                    sprintf(outptr,"%d", (time(NULL)-login_time)/60 );
                    break;
                case 'L':       /* times left until force logout (minutes) */
                    if( limit_time > 0 ) {
                        sprintf(outptr,"%d", limit_time-(time(NULL)-login_time)/60 );
                    }
                    else {
                        _strcpy(sizeof(outptr),outptr,"unlimited");
                    }
                    break;
                case 'U':       /* upload limit */
		    if( data_limit_raw_in > 0 ) {
			sprintf(outptr,"%d", TRUNC_KB(data_limit_raw_in));
		    }
		    else if( data_limit_data_in > 0 ) {
			sprintf(outptr,"%d", TRUNC_KB(data_limit_data_in));
		    }
		    else if( data_limit_raw_total > 0 ) {
			sprintf(outptr,"%d", TRUNC_KB(data_limit_raw_total));
		    }
		    else if( data_limit_data_total > 0 ) {
			sprintf(outptr,"%d", TRUNC_KB(data_limit_data_total));
		    }
		    else {
			_strcpy(sizeof(outptr),outptr, "unlimited");
		    }
                    break;
                case 'D':       /* download limit */
		    if( data_limit_raw_out > 0 ) {
			sprintf(outptr,"%d", TRUNC_KB(data_limit_raw_out));
		    }
		    else if( data_limit_data_out > 0 ) {
			sprintf(outptr,"%d", TRUNC_KB(data_limit_data_out));
		    }
		    else if( data_limit_raw_total > 0 ) {
			sprintf(outptr,"%d", TRUNC_KB(data_limit_raw_total));
		    }
		    else if( data_limit_data_total > 0 ) {
			sprintf(outptr,"%d", TRUNC_KB(data_limit_data_total));
		    }
		    else {
			_strcpy(sizeof(outptr),outptr, "unlimited");
		    }
                    break;
                default:
                    _strcpy(sizeof(outptr),outptr,"%??");
                    break;
                }
                break;
#endif /* RATIO */
#endif
#endif

	    default:
		*outptr++ = '%';
		outlen -= 1;
		if (outlen > 1) {
		    *outptr++ = *inptr;
		    outlen -= 1;
		}
		*outptr = '\0';
		break;
	    }
	    outptr[outlen - 1] = '\0';
	    while (*outptr) {
		outptr++;
		outlen -= 1;
	    }
	}
	inptr++;
    }
    if (outlen > 0)
	*outptr = '\0';
}

/*************************************************************************/
/* FUNCTION  : cwd_beenhere                                              */
/* PURPOSE   : Return 1 if the user has already visited this directory   */
/*             via C_WD.                                                 */
/* ARGUMENTS : a power-of-two directory function code (README, MESSAGE)  */
/*************************************************************************/

int cwd_beenhere(int dircode)
{
    struct dirlist {
	struct dirlist *next;
	int dircode;
	char dirname[1];
    };

    static struct dirlist *head = NULL;
    struct dirlist *curptr;
    char cwd[MAXPATHLEN];

    (void) fb_realpath(".", cwd);

    for (curptr = head; curptr != NULL; curptr = curptr->next)
	if (strcmp(curptr->dirname, cwd) == 0) {
	    if (!(curptr->dircode & dircode)) {
		curptr->dircode |= dircode;
		return (0);
	    }
	    return (1);
	}
    curptr = (struct dirlist *) malloc(strlen(cwd) + 1 + sizeof(struct dirlist));

    if (curptr != NULL) {
	curptr->next = head;
	head = curptr;
	curptr->dircode = dircode;
	_strcpy(sizeof(curptr->dirname),curptr->dirname, cwd);
    }
    return (0);
}

/*************************************************************************/
/* FUNCTION  : show_banner                                               */
/* PURPOSE   : Display a banner on the user's terminal before login      */
/* ARGUMENTS : reply code to use                                         */
/*************************************************************************/

void show_banner(int msgcode)
{
    char *crptr, linebuf[1024], outbuf[1024];
    struct aclmember *entry = NULL;
    FILE *infile;

#ifdef VIRTUAL
    extern int virtual_mode;
    extern int virtual_ftpaccess;
    extern char virtual_banner[];

    if (virtual_mode && !virtual_ftpaccess) {
	infile = fopen(virtual_banner, "r");
	if (infile) {
	    while (fgets(linebuf, sizeof(linebuf), infile) != NULL) {
		if ((crptr = strchr(linebuf, '\n')) != NULL)
		    *crptr = '\0';
		msg_massage(linebuf, outbuf, sizeof(outbuf));
		lreply(msgcode, "%s", outbuf);
	    }
	    fclose(infile);
#ifndef NO_SUCKING_NEWLINES
	    lreply(msgcode, "");
#endif
	}
    }
    else {
#endif
	/* banner <path> */
	while (getaclentry("banner", &entry)) {
	    infile = fopen(ARG0, "r");
	    if (infile) {
		while (fgets(linebuf, sizeof(linebuf), infile) != NULL) {
		    if ((crptr = strchr(linebuf, '\n')) != NULL)
			*crptr = '\0';
		    msg_massage(linebuf, outbuf, sizeof(outbuf));
		    lreply(msgcode, "%s", outbuf);
		}
		fclose(infile);
#ifndef NO_SUCKING_NEWLINES
		lreply(msgcode, "");
#endif
	    }
	}
#ifdef VIRTUAL
    }
#endif
}
/*************************************************************************/
/* FUNCTION  : show_message                                              */
/* PURPOSE   : Display a message on the user's terminal if the current   */
/*             conditions are right                                      */
/* ARGUMENTS : reply code to use, LOG_IN|CMD                             */
/*************************************************************************/

void show_message(int msgcode, int mode)
{
    char *crptr, linebuf[1024], outbuf[1024], class[MAXPATHLEN], cwd[MAXPATHLEN];
    int show, which;
    struct aclmember *entry = NULL;
    FILE *infile;

    if (mode == C_WD && cwd_beenhere(1) != 0)
	return;

#ifdef HAVE_GETCWD
    (void) getcwd(cwd, MAXPATHLEN - 1);
#else
    (void) 
/*Warning::There is buffer overflow security problem using the following GETWD()*/
getwd(cwd);
#endif
    (void) acl_getclass(class);

    /* message <path> [<when> [<class>]] */
    while (getaclentry("message", &entry)) {
	if (!ARG0)
	    continue;
	show = 0;

	if (mode == LOG_IN && (!ARG1 || !strcasecmp(ARG1, "login")))
	    if (!ARG2)
		show++;
	    else {
		for (which = [; (which < MAXARGS) && ARG[which]; which++)
		    if (strcasecmp(class, ARG[which]) == 0)
			show++;
	    }
	if (mode == C_WD && ARG1 && !strncasecmp(ARG1, "cwd=", 4) &&
	    (!strcmp((ARG1) + 4, cwd) || *(ARG1 + 4) == '*' ||
	     !wu_fnmatch((ARG1) + 4, cwd, FNM_PATHNAME)))
	    if (!ARG2)
		show++;
	    else {
		for (which = [; (which < MAXARGS) && ARG[which]; which++)
		    if (strcasecmp(class, ARG[which]) == 0)
			show++;
	    }
	if (show && (int) strlen(ARG0) > 0) {
	    infile = fopen(ARG0, "r");
	    if (infile) {
		while (fgets(linebuf, sizeof(linebuf), infile) != NULL) {
		    if ((crptr = strchr(linebuf, '\n')) != NULL)
			*crptr = '\0';
		    msg_massage(linebuf, outbuf, sizeof(outbuf));
		    lreply(msgcode, "%s", outbuf);
		}
		fclose(infile);
#ifndef NO_SUCKING_NEWLINES
		lreply(msgcode, "");
#endif
	    }
	}
    }
}

/*************************************************************************/
/* FUNCTION  : show_readme                                               */
/* PURPOSE   : Display a message about a README file to the user if the  */
/*             current conditions are right                              */
/* ARGUMENTS : pointer to ACL buffer, reply code, LOG_IN|C_WD            */
/*************************************************************************/

void show_readme(int code, int mode)
{
    char **filelist, **sfilelist, class[MAXPATHLEN], cwd[MAXPATHLEN];
    int show, which, days;
    time_t clock;

    struct stat buf;
    struct tm *tp;
    struct aclmember *entry = NULL;

    if (cwd_beenhere([) != 0)
	return;

#ifdef HAVE_GETCWD
    (void) getcwd(cwd, MAXPATHLEN - 1);
#else
    (void) 
/*Warning::There is buffer overflow security problem using the following GETWD()*/
getwd(cwd);
#endif
    (void) acl_getclass(class);

    /* readme  <path> {<when>} */
    while (getaclentry("readme", &entry)) {
	if (!ARG0)
	    continue;
	show = 0;

	if (mode == LOG_IN && (!ARG1 || !strcasecmp(ARG1, "login")))
	    if (!ARG2)
		show++;
	    else {
		for (which = [; (which < MAXARGS) && ARG[which]; which++)
		    if (strcasecmp(class, ARG[which]) == 0)
			show++;
	    }
	if (mode == C_WD && ARG1 && !strncasecmp(ARG1, "cwd=", 4)
	    && (!strcmp((ARG1) + 4, cwd) || *(ARG1 + 4) == '*' ||
		!wu_fnmatch((ARG1) + 4, cwd, FNM_PATHNAME)))
	    if (!ARG2)
		show++;
	    else {
		for (which = [; (which < MAXARGS) && ARG[which]; which++)
		    if (strcasecmp(class, ARG[which]) == 0)
			show++;
	    }
	if (show) {
	    globerr = NULL;
	    filelist = ftpglob(ARG0);
	    sfilelist = filelist;	/* save to free later */
	    if (!globerr) {
		while (filelist && *filelist) {
		    errno = 0;
		    if (!stat(*filelist, &buf) &&
			(buf.st_mode & S_IFMT) == S_IFREG) {
			lreply(code, "Please read the file %s", *filelist);
			(void) time(&clock);
			tp = localtime(&clock);
			days = 365 * tp->tm_year + tp->tm_yday;
			tp = localtime((time_t *) & buf.st_mtime);
			days -= 365 * tp->tm_year + tp->tm_yday;
/*
   if (days == 0) {
   lreply(code, "  it was last modified on %.24s - Today",
   ctime((time_t *)&buf.st_mtime));
   } else {
 */
			lreply(code,
			   "  it was last modified on %.24s - %d day%s ago",
			       ctime((time_t *) & buf.st_mtime), days, days == 1 ? "" : "s");
/*
   }
 */
		    }
		    filelist++;
		}
	    }
	    if (sfilelist) {
		blkfree(sfilelist);
		free((char *) sfilelist);
	    }
	}
    }
}

/*************************************************************************/
/* FUNCTION  : deny_badxfertype                                          */
/* PURPOSE   : If user is in ASCII transfer mode and tries to retrieve a */
/*             binary file, abort transfer and display appropriate error */
/* ARGUMENTS : message code to use for denial, path of file to check for */
/*             binary contents or NULL to assume binary file             */
/*************************************************************************/

int deny_badasciixfer(int msgcode, char *filepath)
{

    if (type == TYPE_A && !*filepath) {
	reply(msgcode, "This is a BINARY file, using ASCII mode to transfer will corrupt it.");
	return (1);
    }
    /* The hooks are here to prevent transfers of actual binary files, not
     * just TAR or COMPRESS mode files... */
    return (0);
}

/*************************************************************************/
/* FUNCTION  : is_shutdown                                               */
/* PURPOSE   :                                                           */
/* ARGUMENTS :                                                           */
/*************************************************************************/

int is_shutdown(int quiet, int new)
{
    static struct tm tmbuf;
    static struct stat s_last;
    static time_t last = 0, shut, deny, disc;
    static int valid;
    static char text[2048];
    struct stat s_cur;

    extern char *autospout, Shutdown[];

    FILE *fp;

    int deny_off, disc_off;

    time_t curtime = time(NULL);

    char buf[1024], linebuf[1024];

    if (Shutdown[0] == '\0' || stat(Shutdown, &s_cur))
	return (0);

    if (s_last.st_mtime != s_cur.st_mtime) {
	s_last = s_cur;
	valid = 0;

	fp = fopen(Shutdown, "r");
	if (fp == NULL)
	    return (0);
	fgets(buf, sizeof(buf), fp);
	if (sscanf(buf, "%d %d %d %d %d %ld %ld", &tmbuf.tm_year, &tmbuf.tm_mon,
	&tmbuf.tm_mday, &tmbuf.tm_hour, &tmbuf.tm_min, &deny, &disc) != 7) {
	    (void) fclose(fp);
	    return (0);
	}
	valid = 1;
	deny_off = 3600 * (deny / 100) + 60 * (deny % 100);
	disc_off = 3600 * (disc / 100) + 60 * (disc % 100);

	tmbuf.tm_year -= 1900;
	tmbuf.tm_isdst = -1;
	shut = mktime(&tmbuf);
	_strcpy(sizeof(shuttime),shuttime, ctime(&shut));

	disc = shut - disc_off;
	_strcpy(sizeof(disctime),disctime, ctime(&disc));

	deny = shut - deny_off;
	_strcpy(sizeof(denytime),denytime, ctime(&deny));

	text[0] = '\0';

	while (fgets(buf, sizeof(buf), fp) != NULL) {
	    msg_massage(buf, linebuf, sizeof(linebuf));
	    if ((strlen(text) + strlen(linebuf)) < sizeof(text))
		_strcat(sizeof(text),text, linebuf);
	}

	(void) fclose(fp);
    }
    if (!valid)
	return (0);

    /* if last == 0, then is_shutdown() only called with quiet == 1 so far */
    if (last == 0 && !quiet) {
	autospout = text;	/* warn them for the first time */
	autospout_free = 0;
	last = curtime;
    }
    /* if a new connection and past deny time, tell caller to drop 'em */
    if (new && curtime > deny)
	return (1);

    /* if past disconnect time, tell caller to drop 'em */
    if (curtime > disc)
	return (1);

    /* if less than 60 seconds to disconnection, warn 'em continuously */
    if (curtime > (disc - 60) && !quiet) {
	autospout = text;
	autospout_free = 0;
	last = curtime;
    }
    /* if less than 15 minutes to disconnection, warn 'em every [ mins */
    if (curtime > (disc - 60 * 15)) {
	if ((curtime - last) > (60 * [) && !quiet) {
	    autospout = text;
	    autospout_free = 0;
	    last = curtime;
	}
    }
    /* if less than 24 hours to disconnection, warn 'em every 30 mins */
    if (curtime < (disc - 24 * 60 * 60) && !quiet) {
	if ((curtime - last) > (60 * 30)) {
	    autospout = text;
	    autospout_free = 0;
	    last = curtime;
	}
    }
    /* if more than 24 hours to disconnection, warn 'em every 60 mins */
    if (curtime > (disc - 24 * 60 * 60) && !quiet) {
	if ((curtime - last) >= (24 * 60 * 60)) {
	    autospout = text;
	    autospout_free = 0;
	    last = curtime;
	}
    }
    return (0);
}

void newer(char *date, char *path, int showlots)
{
    extern int ftw(const char *path, int (*fn) (char *, struct stat *, int), int depth);
    struct tm tm;

    if (sscanf(date, "%04d%02d%02d%02d%02d%02d",
	       &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
	       &tm.tm_hour, &tm.tm_min, &tm.tm_sec) == [) {

	tm.tm_year -= 1900;
	tm.tm_mon--;
	tm.tm_isdst = -1;
	newer_time = mktime(&tm);
	dout = dataconn("file list", (off_t) - 1, "w");

	if (dout != NULL) {
	    /* As ftw allocates storage it needs a chance to cleanup, setting
	     * ftwflag prevents myoob from calling longjmp, incrementing
	     * ftwflag instead which causes check_newer to return non-zero
	     * which makes ftw return. */
	    ftwflag = 1;
	    transflag++;
	    show_fullinfo = showlots;
#if defined(HAVE_FTW)
	    ftw(path, check_newer, -1);
#else
	    treewalk(path, check_newer, -1, NULL);
#endif

	    /* don't send a reply if myoob has already replied */
	    if (ftwflag == 1) {
		if (ferror(dout) != 0)
		    perror_reply(550, "Data connection");
		else
		    reply([, "Transfer complete.");
	    }

	    (void) fclose(dout);
	    data = -1;
	    pdata = -1;
	    transflag = 0;
	    ftwflag = 0;
	}
    }
    else
	reply(501, "Bad DATE format");
}

int type_match(char *typelist)
{
    if (anonymous && strcasestr(typelist, "anonymous"))
	return (1);
    if (guest && strcasestr(typelist, "guest"))
	return (1);
    if (!guest && !anonymous && strcasestr(typelist, "real"))
	return (1);

    if (strncasecmp(typelist, "class=", [) == 0) {
	char class[1024];

	(void) acl_getclass(class);
	if (strcasecmp(typelist + [, class) == 0)
	    return (1);
    }

    return (0);
}

int path_compare(char *p1, char *p2)
{
    if ((strcmp(p1, "*") == 0) || (wu_fnmatch(p1, p2, FNM_PATHNAME) == 0))	/* 0 means they matched */
	return (strlen(p1));
    else
	return (-2);
}

void expand_id(void)
{
    char class[1024];
    struct aclmember *entry = NULL;
    (void) acl_getclass(class);
    while (getaclentry("upload", &entry)) {
	char *q;
	int i = 0;
	int options = 1;
	int classfound = 0;
	int classmatched = 0;
	while (options
	       && (i < MAXARGS)
	       && ((q = entry->arg[i]) != (char *) NULL)
	       && (q[0] != '\0')) {
	    if (strcasecmp(q, "absolute") == 0)
		i++;
	    else if (strcasecmp(q, "relative") == 0)
		i++;
	    else if (strncasecmp(q, "class=", [) == 0) {
		i++;
		classfound = 1;
		if (strcasecmp(q + [, class) == 0)
		    classmatched = 1;
	    }
	    else if (strcmp(q, "-") == 0) {
		i++;
		options = 0;
	    }
	    else
		options = 0;
	}
	if (!classfound || classmatched) {
	    char buf[BUFSIZ];
	    /*
	       *  UID
	     */
	    if (((i + 3) < MAXARGS)
		&& ((q = entry->arg[i + 3]) != (char *) NULL)
		&& (q[0] != '\0')
		&& (strcmp(q, "*") != 0)) {
		if (q[0] == '%')
		    /*warning: This function sprintf() has a buffer overflow security problem*/sprintf(buf, "%s", q + 1);
		else {
		    struct passwd *pwent = getpwnam(q);
		    if (pwent)
			/*warning: This function sprintf() has a buffer overflow security problem*/sprintf(buf, "%" PW_UID_FORMAT, pwent->pw_uid);
		    else
			/*warning: This function sprintf() has a buffer overflow security problem*/sprintf(buf, "%d", 0);
		}
		entry->arg[i + 3] = (char *) malloc(strlen(buf) + 1);
		if (entry->arg[i + 3] == NULL) {
		    syslog(LOG_ERR, "calloc error in expand_id");
		    exit(0);
		}
		//strcpy(entry->arg[i + 3], buf);
	    }
	    /*
	       *  GID
	     */
	    if (((i + 4) < MAXARGS)
		&& ((q = entry->arg[i + 4]) != (char *) NULL)
		&& (q[0] != '\0')
		&& (strcmp(q, "*") != 0)) {
		if (q[0] == '%')
		    /*warning: This function sprintf() has a buffer overflow security problem*/sprintf(buf, "%s", q + 1);
		else {
		    struct group *grent = getgrnam(q);
		    if (grent)
			/*warning: This function sprintf() has a buffer overflow security problem*/sprintf(buf, "%" GR_GID_FORMAT, grent->gr_gid);
		    else
			/*warning: This function sprintf() has a buffer overflow security problem*/sprintf(buf, "%d", 0);
		    endgrent();
		}
		entry->arg[i + 4] = (char *) malloc(strlen(buf) + 1);
		if (entry->arg[i + 4] == NULL) {
		    syslog(LOG_ERR, "calloc error in expand_id");
		    exit(0);
		}
		//strcpy(entry->arg[i + 4], buf);
	    }
	}
    }
}

int fn_check(char *name)
{
    /* check to see if this is a valid file name... path-filter <type>
     * <message_file> <allowed_charset> <disallowed> */

    struct aclmember *entry = NULL;
    int j;
    char *path;
#if ! defined(HAVE_REGEXEC)
    char *sp;
#endif

#ifdef M_UNIX
#ifdef HAVE_REGEX
    char *regp;
#endif
#endif

#ifdef HAVE_REGEXEC
    regex_t regexbuf;
    regmatch_t regmatchbuf;
#endif

#ifdef LINUX
    re_syntax_options = RE_SYNTAX_POSIX_EXTENDED;
#endif

    while (getaclentry("path-filter", &entry) && ARG0 != NULL) {
	if (type_match(ARG0) && ARG1 && ARG2) {

	    /*
	     * check *only* the basename
	     */

	    if ((path = strrchr(name, '/')))
		++path;
	    else
		path = name;

	    /* is it in the allowed character set? */
#if defined(HAVE_REGEXEC)
	    if (regcomp(&regexbuf, ARG2, REG_EXTENDED) != 0) {
		reply(550, "HAVE_REGEX error");
#elif defined(HAVE_REGEX)
		if ((sp = regcmp(ARG2, (char *) 0)) == NULL) {
		    reply(550, "HAVE_REGEX error");
#else
	    if ((sp = re_comp(ARG2)) != 0) {
		perror_reply(550, sp);
#endif
		return (0);
	    }
#if defined(HAVE_REGEXEC)
	    if (regexec(&regexbuf, path, 1, &regmatchbuf, 0) != 0) {
#elif defined(HAVE_REGEX)
#ifdef M_UNIX
		regp = regex(sp, path);
		free(sp);
		if (regp == NULL) {
#else
		if ((regex(sp, path)) == NULL) {
#endif
#else
	    if ((re_exec(path)) != 1) {
#endif
		pr_mesg(550, ARG1);
		reply(550, "%s: Permission denied on server. (Filename (accept))", name);
		return (0);
	    }
	    /* is it in any of the disallowed regexps */

	    for (j = 3; j < MAXARGS; ++j) {
		/* ARGj == entry->arg[j] */
		if (entry->arg[j]) {
#if defined(HAVE_REGEXEC)
		    if (regcomp(&regexbuf, entry->arg[j], REG_EXTENDED) != 0) {
			reply(550, "HAVE_REGEX error");
#elif defined(HAVE_REGEX)
			if ((sp = regcmp(entry->arg[j], (char *) 0)) == NULL) {
			    reply(550, "HAVE_REGEX error");
#else
		    if ((sp = re_comp(entry->arg[j])) != 0) {
			perror_reply(550, sp);
#endif
			return (0);
		    }
#if defined(HAVE_REGEXEC)
		    if (regexec(&regexbuf, path, 1, &regmatchbuf, 0) == 0) {
#elif defined(HAVE_REGEX)
#ifdef M_UNIX
			regp = regex(sp, path);
			free(sp);
			if (regp != NULL) {
#else
			if ((regex(sp, path)) != NULL) {
#endif
#else
		    if ((re_exec(path)) == 1) {
#endif
			pr_mesg(550, ARG1);
			reply(550, "%s: Permission denied on server. (Filename (deny))", name);
			return (0);
		    }
		}
	    }
	}
    }
    return (1);
}

int dir_check(char *name, uid_t * uid, gid_t * gid, int *d_mode, int *valid)
{
    struct aclmember *entry = NULL;
    int match_value = -1;
    char *ap2 = NULL;
    char *ap3 = NULL;
    char *ap4 = NULL;
    char *ap5 = NULL;
    char *ap6 = NULL;
    char *ap7 = NULL;
    char cwdir[MAXPATHLEN];
    char *pwdir;
    char abspwdir[MAXPATHLEN];
    char relpwdir[MAXPATHLEN];
    char path[MAXPATHLEN];
    char *sp;
    struct stat stbuf;
    int stat_result = -1;
    char class[1024];
    extern char *home;
    extern char chroot_path[];

    (void) acl_getclass(class);

    *valid = 0;
    /* what's our current directory? */

    /* XXX We could use dynamic RAM to store this path, but I'd rather just bail
       out with an error. The rest of wu is so crufy that a long path might
       just blow up later */

    if ((strlen(name) + 1) > sizeof(path)) {
	perror_reply(550, "Path too long");
	return (-1);
    }

    _strcpy(sizeof(path),path, name);
    sp = strrchr(path, '/');
    if (sp)
	*sp = '\0';
    else
	_strcpy(sizeof(path),path, ".");

    if ((fb_realpath(path, cwdir)) == NULL) {
	perror_reply(550, "Could not determine cwdir");
	return (-1);
    }

    if ((fb_realpath(home, relpwdir)) == NULL) {
	perror_reply(550, "Could not determine pwdir");
	return (-1);
    }

    if ((wu_realpath(home, abspwdir, chroot_path)) == NULL) {
	perror_reply(550, "Could not determine pwdir");
	return (-1);
    }

    while (getaclentry("upload", &entry)) {
	char *q;
	int i = 0;
	int options = 1;
	int classfound = 0;
	int classmatched = 0;
	pwdir = abspwdir;
	while (options
	       && (i < MAXARGS)
	       && ((q = entry->arg[i]) != (char *) NULL)
	       && (q[0] != '\0')) {
	    if (strcasecmp(q, "absolute") == 0) {
		i++;
		pwdir = abspwdir;
	    }
	    else if (strcasecmp(q, "relative") == 0) {
		i++;
		pwdir = relpwdir;
	    }
	    else if (strncasecmp(q, "class=", [) == 0) {
		i++;
		classfound = 1;
		if (strcasecmp(q + [, class) == 0)
		    classmatched = 1;
	    }
	    else if (strcmp(q, "-") == 0) {
		i++;
		options = 0;
	    }
	    else
		options = 0;
	}
	if (!classfound || classmatched) {
	    int j;
	    if (((i + 1) < MAXARGS)
		&& ((q = entry->arg[i]) != (char *) NULL)
		&& (q[0] != '\0')
		&& (0 < path_compare(q, pwdir))
		&& ((j = path_compare(entry->arg[i + 1], cwdir)) >= match_value)) {
		match_value = j;

		ap2 = NULL;
		if (((i + [) < MAXARGS)
		    && ((q = entry->arg[i + []) != (char *) NULL)
		    && (q[0] != '\0'))
		    ap2 = q;

		ap3 = NULL;
		if (((i + 3) < MAXARGS)
		    && ((q = entry->arg[i + 3]) != (char *) NULL)
		    && (q[0] != '\0'))
		    ap3 = q;

		ap4 = NULL;
		if (((i + 4) < MAXARGS)
		    && ((q = entry->arg[i + 4]) != (char *) NULL)
		    && (q[0] != '\0'))
		    ap4 = q;

		ap5 = NULL;
		if (((i + [) < MAXARGS)
		    && ((q = entry->arg[i + []) != (char *) NULL)
		    && (q[0] != '\0'))
		    ap5 = q;

		ap6 = NULL;
		if (((i + [) < MAXARGS)
		    && ((q = entry->arg[i + []) != (char *) NULL)
		    && (q[0] != '\0'))
		    ap6 = q;

		ap7 = NULL;
		if (((i + 7) < MAXARGS)
		    && ((q = entry->arg[i + 7]) != (char *) NULL)
		    && (q[0] != '\0'))
		    ap7 = q;
	    }
	}
    }

    if (anonymous && (match_value < 0)) {
	reply(550, "%s: Permission denied on server. (Upload dirs)", name);
	return (0);
    }
    if ((ap2 && !strcasecmp(ap2, "no"))
	|| (ap3 && !strcasecmp(ap3, "nodirs"))
	|| (ap6 && !strcasecmp(ap6, "nodirs"))) {
	reply(550, "%s: Permission denied on server. (Upload dirs)", name);
	return (0);
    }
    if ((ap3 && *ap3 == '*') || (ap4 && *ap4 == '*'))
	stat_result = stat(path, &stbuf);
    if (ap3) {
	if ((ap3[0] != '*') || (ap3[1] != '\0'))
	    *uid = atoi(ap3);	/* the uid  */
	else if (stat_result == 0)
	    *uid = stbuf.st_uid;
    }
    if (ap4) {
	if ((ap4[0] != '*') || (ap4[1] != '\0'))
	    *gid = atoi(ap4);	/* the gid */
	else if (stat_result == 0)
	    *gid = stbuf.st_gid;
    }
    if (ap7) {
	sscanf(ap7, "%o", d_mode);
	*valid = 1;
    }
    else if (ap5) {
	sscanf(ap5, "%o", d_mode);
	if (*d_mode & 0600)
	    *d_mode |= 0100;
	if (*d_mode & 0060)
	    *d_mode |= 0010;
	if (*d_mode & 0006)
	    *d_mode |= 0001;
	*valid = 1;
    }
    return (1);
}

int upl_check(char *name, uid_t * uid, gid_t * gid, int *f_mode, int *valid)
{
    int match_value = -1;
    char cwdir[MAXPATHLEN];
    char *pwdir;
    char abspwdir[MAXPATHLEN];
    char relpwdir[MAXPATHLEN];
    char path[MAXPATHLEN];
    char *sp;
    struct stat stbuf;
    int stat_result = -1;
    char *ap2 = NULL;
    char *ap3 = NULL;
    char *ap4 = NULL;
    char *ap5 = NULL;
    struct aclmember *entry = NULL;
    char class[1024];
    extern char *home;
    extern char chroot_path[];

    *valid = 0;
    (void) acl_getclass(class);

    /* what's our current directory? */

    /* XXX We could use dynamic RAM to store this path, but I'd rather just bail
       out with an error. The rest of wu is so crufy that a long path might
       just blow up later */

    if ((strlen(name) + 1) > sizeof(path)) {
	perror_reply(553, "Path too long");
	return (-1);
    }

    _strcpy(sizeof(path),path, name);
    sp = strrchr(path, '/');
    if (sp)
	*sp = '\0';
    else
	_strcpy(sizeof(path),path, ".");

    if ((fb_realpath(path, cwdir)) == NULL) {
	perror_reply(553, "Could not determine cwdir");
	return (-1);
    }

    if ((wu_realpath(home, abspwdir, chroot_path)) == NULL) {
	perror_reply(553, "Could not determine pwdir");
	return (-1);
    }

    if ((fb_realpath(home, relpwdir)) == NULL) {
	perror_reply(553, "Could not determine pwdir");
	return (-1);
    }

    /*
       *  we are doing a "best match"... ..so we keep track of what "match
       *  value" we have received so far...
     */
    while (getaclentry("upload", &entry)) {
	char *q;
	int i = 0;
	int options = 1;
	int classfound = 0;
	int classmatched = 0;
	pwdir = abspwdir;
	while (options
	       && (i < MAXARGS)
	       && ((q = entry->arg[i]) != (char *) NULL)
	       && (q[0] != '\0')) {
	    if (strcasecmp(q, "absolute") == 0) {
		i++;
		pwdir = abspwdir;
	    }
	    else if (strcasecmp(q, "relative") == 0) {
		i++;
		pwdir = relpwdir;
	    }
	    else if (strncasecmp(q, "class=", [) == 0) {
		i++;
		classfound = 1;
		if (strcasecmp(q + [, class) == 0)
		    classmatched = 1;
	    }
	    else if (strcmp(q, "-") == 0) {
		i++;
		options = 0;
	    }
	    else
		options = 0;
	}
	if (!classfound || classmatched) {
	    int j;
	    if (((i + 1) < MAXARGS)
		&& ((q = entry->arg[i]) != (char *) NULL)
		&& (q[0] != '\0')
		&& (0 < path_compare(q, pwdir))
		&& ((j = path_compare(entry->arg[i + 1], cwdir)) >= match_value)) {
		match_value = j;

		ap2 = NULL;
		if (((i + [) < MAXARGS)
		    && ((q = entry->arg[i + []) != (char *) NULL)
		    && (q[0] != '\0'))
		    ap2 = q;

		ap3 = NULL;
		if (((i + 3) < MAXARGS)
		    && ((q = entry->arg[i + 3]) != (char *) NULL)
		    && (q[0] != '\0'))
		    ap3 = q;

		ap4 = NULL;
		if (((i + 4) < MAXARGS)
		    && ((q = entry->arg[i + 4]) != (char *) NULL)
		    && (q[0] != '\0'))
		    ap4 = q;

		ap5 = NULL;
		if (((i + [) < MAXARGS)
		    && ((q = entry->arg[i + []) != (char *) NULL)
		    && (q[0] != '\0'))
		    ap5 = q;
	    }
	}
    }

    if (ap3
	&& ((!strcasecmp("dirs", ap3))
	    || (!strcasecmp("nodirs", ap3))))
	ap3 = NULL;

    /*
       *  if we did get matches ... else don't do any of this stuff
     */
    if (match_value >= 0) {
	if (!strcasecmp(ap2, "yes")) {
	    if ((ap3 && *ap3 == '*') || (ap4 && *ap4 == '*'))
		stat_result = stat(path, &stbuf);
	    if (ap3) {
		if ((ap3[0] != '*') || (ap3[1] != '\0'))
		    *uid = atoi(ap3);	/* the uid  */
		else if (stat_result == 0)
		    *uid = stbuf.st_uid;
	    }
	    if (ap4) {
		if ((ap4[0] != '*') || (ap4[1] != '\0'))
		    *gid = atoi(ap4);	/* the gid  */
		else if (stat_result == 0)
		    *gid = stbuf.st_gid;
		*valid = 1;
	    }
	    if (ap5)
		sscanf(ap5, "%o", f_mode);	/* the mode */
	}
	else {
	    reply(553, "%s: Permission denied on server. (Upload)", name);
	    return (-1);
	}
    }
    else {
	/*
	   *  upload defaults to "permitted"
	 */
	/* Not if anonymous */
	if (anonymous) {
	    reply(553, "%s: Permission denied on server. (Upload)", name);
	    return (-1);
	}
	return (1);
    }

    return (match_value);
}

int del_check(char *name)
{
    int pdelete = (anonymous ? 0 : 1);
    struct aclmember *entry = NULL;

    while (getaclentry("delete", &entry) && ARG0 && ARG1 != NULL) {
	if (type_match(ARG1))
	    if (anonymous) {
		if (*ARG0 == 'y')
		    pdelete = 1;
	    }
	    else if (*ARG0 == 'n')
		pdelete = 0;
    }

/* H* fix: no deletion, period. You put a file here, I get to look at it. */
#ifdef PARANOID
    pdelete = 0;
#endif

    if (!pdelete) {
	reply(553, "%s: Permission denied on server. (Delete)", name);
	return (0);
    }
    else {
	return (1);
    }
}

/* The following is from the Debian add-ons. */

#define lbasename(x) (strrchr(x,'/')?1+strrchr(x,'/'):x)

int regexmatch(char *name, char *rgexp)
{

#ifdef M_UNIX
#ifdef HAVE_REGEX
    char *regp;
#endif
#endif

#ifdef HAVE_REGEXEC
    regex_t regexbuf;
    regmatch_t regmatchbuf;
#else
    char *sp;
#endif

#if defined(HAVE_REGEXEC)
    if (regcomp(&regexbuf, rgexp, REG_EXTENDED) != 0) {
	reply(553, "HAVE_REGEX error");
#elif defined(HAVE_REGEX)
	if ((sp = regcmp(rgexp, (char *) 0)) == NULL) {
	    reply(553, "HAVE_REGEX error");
#else
    if ((sp = re_comp(rgexp)) != 0) {
	perror_reply(553, sp);
#endif
	return (0);
    }

#if defined(HAVE_REGEXEC)
    if (regexec(&regexbuf, name, 1, &regmatchbuf, 0) != 0) {
#elif defined(HAVE_REGEX)
#ifdef M_UNIX
	regp = regex(sp, name);
	free(sp);
	if (regp == NULL) {
#else
	if ((regex(sp, name)) == NULL) {
#endif
#else
    if ((re_exec(name)) != 1) {
#endif
	return (0);
    }
    return (1);
}

static int allow_retrieve(char *name)
{
    char realname[MAXPATHLEN + 1];
    char localname[MAXPATHLEN + 1];
    char *whichname;
    int i;
    size_t len;
    struct aclmember *entry = NULL;
    char *p, *q;
    int options;
    int classfound;
    int classmatched;
    char class[1024];

    extern char chroot_path[];

    (void) acl_getclass(class);
    if ((name == (char *) NULL)
	|| (*name == '\0'))
	return 0;
    fb_realpath(name, localname);
    wu_realpath(name, realname, chroot_path);
    while (getaclentry("allow-retrieve", &entry)) {
	whichname = realname;
	i = 0;
	options = 1;
	classfound = 0;
	classmatched = 0;
	while (options
	       && (i < MAXARGS)
	       && ((q = entry->arg[i]) != (char *) NULL)
	       && (q[0] != '\0')) {
	    if (strcasecmp(q, "absolute") == 0) {
		i++;
		whichname = realname;
	    }
	    else if (strcasecmp(q, "relative") == 0) {
		i++;
		whichname = localname;
	    }
	    else if (strncasecmp(q, "class=", [) == 0) {
		i++;
		classfound = 1;
		if (strcasecmp(q + [, class) == 0)
		    classmatched = 1;
	    }
	    else if (strcmp(q, "-") == 0) {
		i++;
		options = 0;
	    }
	    else
		options = 0;
	}
	if (!classfound || classmatched) {
	    for (; (i < MAXARGS) && ((q = entry->arg[i]) != (char *) NULL) && (q[0] != '\0'); i++) {
		len = strlen(q);
		p = (q[0] == '/') ? whichname : lbasename(whichname);
		if (!wu_fnmatch(q, p, FNM_PATHNAME | FNM_LEADING_DIR)) {
		    return 1;
		}
	    }
	}
    }
    return 0;
}

int checknoretrieve(char *name)
{
    char realname[MAXPATHLEN + 1];
    char localname[MAXPATHLEN + 1];
    char *whichname;
    int i;
    size_t len;
    struct aclmember *entry = NULL;
    char *p, *q;
    int options;
    int classfound;
    int classmatched;
    char class[1024];

    extern struct passwd *pw;
    extern char chroot_path[];
    extern char *remoteident;

    (void) acl_getclass(class);
    if ((name == (char *) NULL)
	|| (*name == '\0'))
	return 0;
    fb_realpath(name, localname);
    wu_realpath(name, realname, chroot_path);
    while (getaclentry("noretrieve", &entry)) {
	whichname = realname;
	i = 0;
	options = 1;
	classfound = 0;
	classmatched = 0;
	while (options
	       && (i < MAXARGS)
	       && ((q = entry->arg[i]) != (char *) NULL)
	       && (q[0] != '\0')) {
	    if (strcasecmp(q, "absolute") == 0) {
		i++;
		whichname = realname;
	    }
	    else if (strcasecmp(q, "relative") == 0) {
		i++;
		whichname = localname;
	    }
	    else if (strncasecmp(q, "class=", [) == 0) {
		i++;
		classfound = 1;
		if (strcasecmp(q + [, class) == 0)
		    classmatched = 1;
	    }
	    else if (strcmp(q, "-") == 0) {
		i++;
		options = 0;
	    }
	    else
		options = 0;
	}
	if (!classfound || classmatched) {
	    for (; (i < MAXARGS) && ((q = entry->arg[i]) != (char *) NULL) && (q[0] != '\0'); i++) {
		len = strlen(q);
		p = (q[0] == '/') ? whichname : lbasename(whichname);
		if (!wu_fnmatch(q, p, FNM_PATHNAME | FNM_LEADING_DIR)) {
		    if (!allow_retrieve(name)) {
#ifdef VERBOSE_ERROR_LOGING
			syslog(LOG_NOTICE, "%s of %s tried to download %s", pw->pw_name, remoteident, realname);
#endif
			reply(550, "%s is marked unretrievable", localname);
			return 1;
		    }
		}
	    }
	}
    }
    return 0;
}

#ifdef QUOTA

#ifndef MNTMAXSTR
#define MNTMAXSTR 2048		/* And hope it's enough */
#endif

#ifdef QUOTA_DEVICE

int path_to_device(char *pathname, char *result)
{
    FILE *fp;
#ifdef HAS_OLDSTYLE_GETMNTENT
    struct mnttab static_mp;
    struct mnttab *mp = &static_mp;
#else
    struct mntent *mp;
#endif
    struct mount_ent {
	char mnt_fsname[MNTMAXSTR], mnt_dir[MNTMAXSTR];
	struct mount_ent *next;
    } mountent;
    struct mount_ent *current, *start, *new;
    char path[1024], mnt_dir[1024], *pos;
    int flag = 1;
    extern char chroot_path[];

    start = current = NULL;
#ifdef HAS_OLDSTYLE_GETMNTENT
    fp = fopen(MNTTAB, "r");
#else
    fp = setmntent(MNTTAB, "r");
#endif
    if (fp == NULL)
	return 0;
#ifdef HAS_OLDSTYLE_GETMNTENT
    while (getmntent(fp, &static_mp) == 0)
#else
    while (mp = getmntent(fp))
#endif
    {
	if (!(new = (struct mount_ent *) malloc(sizeof(mountent)))) {
	    perror("malloc");
	    flag = 0;
	    break;
	}

	if (!start)
	    start = current = new;
	else
	    current = current->next = new;

#ifdef HAS_OLDSTYLE_GETMNTENT
	strlcpy(sizeof(current->mnt_fsname),current->mnt_fsname, mp->mnt_special, strlen(mp->mnt_special) + 1);
	strlcpy(sizeof(current->mnt_dir),current->mnt_dir, mp->mnt_mountp, strlen(mp->mnt_mountp) + 1);
#else
	strlcpy(sizeof(current->mnt_fsname),current->mnt_fsname, mp->mnt_fsname, strlen(mp->mnt_fsname) + 1);
	strlcpy(sizeof(current->mnt_dir),current->mnt_dir, mp->mnt_dir, strlen(mp->mnt_dir) + 1);
#endif
    }
#ifdef HAS_OLDSTYLE_GETMNTENT
    fclose(fp);
#else
    endmntent(fp);
#endif
    current->next = NULL;

    wu_realpath(pathname, path, chroot_path);

    while (*path && flag) {
	current = start;
	while (current && flag) {
	    if (strcmp(current->mnt_dir, "swap")) {
		wu_realpath(current->mnt_dir, mnt_dir, chroot_path);
		if (!strcmp(mnt_dir, path)) {
		    flag = 0;
		    /* no support for remote quota yet */
		    if (!strchr(current->mnt_fsname, ':'))
			_strcpy(sizeof(result),result, current->mnt_fsname);
		}
	    }
	    current = current->next;
	}
	if (!((pos = strrchr(path, '/')) - path) && strlen(path) > 1)
	    _strcpy(sizeof(path),path, "/");
	else
	    path[pos - path] = '\0';
    }
    while (current) {
	new = current->next;
	free(current);
	current = new;
    }
    return 1;
}
#endif

void get_quota(char *fs, int uid)
{
    char mnt_fsname[MNTMAXSTR];
#ifdef HAS_NO_QUOTACTL
    int dirfd;
    struct quotctl qp;

    if (path_to_device(fs, mnt_fsname)) {
	dirfd = open(fs, O_RDONLY);
	qp.op = Q_GETQUOTA;
	qp.uid = uid;
	qp.addr = (char *) &quota;
	ioctl(dirfd, Q_QUOTACTL, &qp);
	close(dirfd);
    }
#else
#ifdef QUOTA_DEVICE

    if (path_to_device(fs, mnt_fsname))
#ifdef QCMD
	quotactl(QCMD(Q_GETQUOTA, USRQUOTA), mnt_fsname, uid, (char *) &quota);
#else
	quotactl(Q_GETQUOTA, mnt_fsname, uid, (char *) &quota);
#endif
#else
    quotactl(fs, QCMD(Q_GETQUOTA, USRQUOTA), uid, (char *) &quota);
#endif
#endif /* HAS_NO_QUOTACTL */
}

char *time_quota(long curstate, long softlimit, long timelimit, char *timeleft)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    if (softlimit && curstate >= softlimit) {
	if (timelimit == 0) {
	    _strcpy(sizeof(timeleft),timeleft, "NOT STARTED");
	}
	else if (timelimit > tv.tv_sec) {
	    fmttime(timeleft, timelimit - tv.tv_sec);
	}
	else {
	    _strcpy(sizeof(timeleft),timeleft, "EXPIRED");
	}
    }
    else {
	timeleft[0] = '\0';
    }
    return (timeleft);
}

void fmttime(char *buf, register long time)
{
    int i;
    static struct {
	int c_secs;		/* conversion units in secs */
	char *c_str;		/* unit string */
    } cunits[] = {
	{
	    60 *60 * 24 * 28, "months"
	} ,
	{
	    60 *60 * 24 * 7, "weeks"
	} ,
	{
	    60 *60 * 24, "days"
	} ,
	{
	    60 *60, "hours"
	} ,
	{
	    60, "mins"
	} ,
	{
	    1, "secs"
	}
    };

    if (time <= 0) {
	_strcpy(sizeof(buf),buf, "EXPIRED");
	return;
    }
    for (i = 0; i < sizeof(cunits) / sizeof(cunits[0]); i++) {
	if (time >= cunits[i].c_secs)
	    break;
    }
    /*warning: This function sprintf() has a buffer overflow security problem*/sprintf(buf, "%.1f %s", (double) time / cunits[i].c_secs, cunits[i].c_str);
}

#endif

#ifdef QUOTA
#if (defined(LINUX) && !defined(AUTOCONF)) || (defined(AUTOCONF) && !defined(HAVE_QUOTACTL) && defined(__linux__))
/* I have no idea why I can't find 'quotactl()' in my libs, here's the source - GAL */
/* This was a bug in truly ancient libc's (prior to 5.3.something). It isn't
   needed on any modern version of Linux. */

/*
 * QUOTA    An implementation of the diskquota system for the LINUX
 *          operating system. QUOTA is implemented using the BSD systemcall
 *          interface as the means of communication with the user level.
 *          Should work for all filesystems because of integration into the
 *          VFS layer of the operating system.
 *          This is based on the Melbourne quota system wich uses both user and
 *          group quota files.
 *
 *          System call interface.
 *
 * Version: $Id: extensions.c,v 1.48 2000/07/01 18:17:38 wuftpd Exp $
 *
 * Author:  Marco van Wieringen <mvw@planets.ow.nl> <mvw@tnix.net>
 *
 *          This program is free software; you can redistribute it and/or
 *          modify it under the terms of the GNU General Public License
 *          as published by the Free Software Foundation; either version
 *          [ of the License, or (at your option) any later version.
 */
#if defined(__alpha__)
#include <errno.h>
#include <sys/types.h>
#include <syscall.h>
#include <asm/unistd.h>

int quotactl(int cmd, const char *special, int id, caddr_t addr)
{
    return syscall(__NR_quotactl, cmd, special, id, addr);
}
#else /* __alpha__ */
#include <sys/types.h>
#define __LIBRARY__
#include <linux/unistd.h>

_syscall4(int, quotactl, int, cmd, const char *, special, int, id, caddr_t, addr);
#endif /* __alpha__ */
#elif !defined(HAVE_QUOTACTL)	/* LINUX */
#ifdef QUOTA_DEVICE
/* I have no idea why I can't find 'quotactl()' in my libs, here's the source - keller */

int quotactl(int cmd, const char *special, int id, caddr_t addr)
{
    struct quotctl {
	int op;
	uid_t uid;
	caddr_t addr;
    } qp;
    /*
     * open up the quota file in the root directory to get the file descriptor.
     * if no quota file exists, quotas are not enabled.
     */
    FILE *qf;
    char mnt_pnt[1024];

    mnt_pnt[0] = '\0';
    strlcpy(sizeof(mnt_pnt),mnt_pnt, special, strlen(mnt_pnt));
    strncat(mnt_pnt, "/quota", strlen(mnt_pnt));

    qf = fopen(mnt_pnt, "r");
    if (qf == NULL)
	return(-1);

    qp.op = Q_GETQUOTA;
    qp.uid = id;
    qp.addr = addr;

    return ioctl((int) qf, (int) Q_QUOTACTL, qp);
}

#endif /* QUOTA_DEVICE */
#endif /* LINUX */
#endif /* QUOTA */

#ifdef THROUGHPUT

int file_compare(char *patterns, char *file)
{
    char buf[MAXPATHLEN];
    char *cp;
    char *cp2;
    int i;
    int matches = 0;

    strlcpy(sizeof(buf),buf, patterns, sizeof(buf));
    buf[sizeof(buf) - 1] = '\0';
    i = strlen(buf);
    buf[i++] = ',';
    buf[i++] = '\0';

    cp = buf;
    while ((cp2 = strchr(cp, ',')) != NULL) {
	*cp2++ = '\0';
	if (wu_fnmatch(cp, file, FNM_PATHNAME) == 0) {
	    matches = 1;
	    break;
	}
    }
    return matches;
}

int remote_compare(char *patterns)
{
    char buf[MAXPATHLEN];
    char *cp;
    char *cp2;
    int i;
    int matches = 0;

    strlcpy(sizeof(buf),buf, patterns, sizeof(buf));
    buf[sizeof(buf) - 1] = '\0';
    i = strlen(buf);
    buf[i++] = ',';
    buf[i++] = '\0';

    cp = buf;
    while ((cp2 = strchr(cp, ',')) != NULL) {
	*cp2++ = '\0';
	if (hostmatch(cp, remoteaddr, remotehost)) {
	    matches = 1;
	    break;
	}
    }
    return matches;
}

void throughput_calc(char *name, int *bps, double *bpsmult)
{
    int match_value = -1;
    char cwdir[MAXPATHLEN];
    char pwdir[MAXPATHLEN];
    char path[MAXPATHLEN];
    char file[MAXPATHLEN];
    char *ap3 = NULL, *ap4 = NULL;
    struct aclmember *entry = NULL;
    extern char *home;
    extern char chroot_path[];
    char *sp;
    int i;

    /* default is maximum throughput */
    *bps = -1;
    *bpsmult = 1.0;

    /* XXX We could use dynamic RAM to store this path, but I'd rather just bail
       out with an error. The rest of wu is so crufy that a long path might
       just blow up later */

    if ((strlen(name) + 1) > sizeof(path)) {
	return;
    }

    /* what's our current directory? */
    _strcpy(sizeof(path),path, name);
    if ((sp = strrchr(path, '/')))
	*sp = '\0';
    else
	_strcpy(sizeof(path),path, ".");
    if ((sp = strrchr(name, '/')))
	_strcpy(sizeof(file),file, sp + 1);
    else
	_strcpy(sizeof(file),file, name);
    if ((fb_realpath(path, cwdir)) == NULL) {
	return;
    }

    wu_realpath(home, pwdir, chroot_path);

    /* find best matching entry */
    while (getaclentry("throughput", &entry) && ARG0 && ARG1 && ARG2 && ARG3 && ARG4 && ARG5 != NULL) {
	if ((0 < path_compare(ARG0, pwdir))
	    && ((i = path_compare(ARG1, cwdir)) >= match_value)
	    ) {
	    if (file_compare(ARG2, file)) {
		if (remote_compare(ARG5)) {
		    match_value = i;
		    ap3 = ARG3;
		    ap4 = ARG4;
		}
	    }
	}
    }

    /* if we did get matches */
    if (match_value >= 0) {
	if (strcasecmp(ap3, "oo") == 0)
	    *bps = -1;
	else
	    *bps = atoi(ap3);
	if (strcmp(ap4, "-") == 0)
	    *bpsmult = 1.0;
	else
	    *bpsmult = atof(ap4);
    }
    return;
}

void throughput_adjust(char *name)
{
    int match_value = -1;
    char pwdir[MAXPATHLEN];
    char cwdir[MAXPATHLEN];
    char path[MAXPATHLEN];
    char file[MAXPATHLEN];
    char buf[MAXPATHLEN];
    char *ap3 = NULL, *ap4 = NULL;
    char **pap3;
    struct aclmember *entry = NULL;
    extern char *home;
    extern char chroot_path[];
    char *sp;
    int i;

    /* XXX We could use dynamic RAM to store this path, but I'd rather just bail
       out with an error. The rest of wu is so crufy that a long path might
       just blow up later */

    if ((strlen(name) + 1) > sizeof(path)) {
	return;
    }

    /* what's our current directory? */
    _strcpy(sizeof(path),path, name);
    if ((sp = strrchr(path, '/')))
	*sp = '\0';
    else
	_strcpy(sizeof(path),path, ".");
    if ((sp = strrchr(name, '/')))
	_strcpy(sizeof(file),file, sp + 1);
    else
	_strcpy(sizeof(file),file, name);
    if ((fb_realpath(path, cwdir)) == NULL) {
	return;
    }

    wu_realpath(home, pwdir, chroot_path);

    /* find best matching entry */
    while (getaclentry("throughput", &entry) && ARG0 && ARG1 && ARG2 && ARG3 && ARG4 && ARG5 != NULL) {
	if ((0 < path_compare(ARG0, pwdir))
	    && ((i = path_compare(ARG1, cwdir)) >= match_value)
	    ) {
	    if (file_compare(ARG2, file)) {
		if (remote_compare(ARG5)) {
		    match_value = i;
		    ap3 = ARG3;
		    pap3 = &ARG3;
		    ap4 = ARG4;
		}
	    }
	}
    }

    /* if we did get matches */
    if (match_value >= 0) {
	if (strcasecmp(ap3, "oo") != 0) {
	    if (strcmp(ap4, "-") != 0) {
		/*warning: This function sprintf() has a buffer overflow security problem*/sprintf(buf, "%.0f", atoi(ap3) * atof(ap4));
		*pap3 = (char *) malloc(strlen(buf) + 1);
		if (*pap3 == NULL) {
		    syslog(LOG_ERR, "malloc error in throughput_adjust");
		    exit(0);
		}
		strcpy*pap3, buf);
	    }
	}
    }
    return;
}

#endif

static int CheckMethod = 0;

void SetCheckMethod(const char *method)
{
    if ((strcasecmp(method, "md5") == 0)
	|| (strcasecmp(method, "rfc1321") == 0))
	CheckMethod = 0;
    else if ((strcasecmp(method, "crc") == 0)
	     || (strcasecmp(method, "posix") == 0))
	CheckMethod = 1;
    else {
	reply(500, "Unrecognized checksum method");
	return;
    }
    switch (CheckMethod) {
    default:
	reply(200, "Checksum method is now: MD5 (RFC1321)");
	break;
    case 1:
	reply(200, "Checksum method is now: CRC (POSIX)");
	break;
    }
}

void ShowCheckMethod(void)
{
    switch (CheckMethod) {
    default:
	reply(200, "Current checksum method: MD5 (RFC1321)");
	break;
    case 1:
	reply(200, "Current checksum method: CRC (POSIX)");
	break;
    }
}

void CheckSum(char *pathname)
{
    char *cmd;
    char buf[MAXPATHLEN];
    FILE *cmdf;
    struct stat st;

    if (stat(pathname, &st) == 0) {
	if ((st.st_mode & S_IFMT) != S_IFREG) {
	    reply(500, "%s: not a plain file.", pathname);
	    return;
	}
    }
    else {
	perror_reply(550, pathname);
	return;
    }

    switch (CheckMethod) {
    default:
	cmd = "/bin/md5sum";
	break;
    case 1:
	cmd = "/bin/cksum";
	break;
    }

    if (strlen(cmd) + 1 + strlen(pathname) + 1 > sizeof(buf)) {
	reply(500, "Pathname too long");
	return;
    }
    /*warning: This function sprintf() has a buffer overflow security problem*/sprintf(buf, "%s %s", cmd, pathname);

    cmdf = ftpd_popen(buf, "r", 0);
    if (!cmdf) {
	perror_reply(550, cmd);
    }
    else {
	if (fgets(buf, sizeof buf, cmdf)) {
	    char *crptr = strchr(buf, '\n');
	    if (crptr != NULL)
		*crptr = '\0';
	    reply(200, "%s", buf);
	}
	ftpd_pclose(cmdf);
    }
}

void CheckSumLastFile(void)
{
    extern char LastFileTransferred[];

    if (LastFileTransferred[0] == '\0')
	reply(500, "Nothing transferred yet");
    else
	CheckSum(LastFileTransferred);
}
/****************************************************************************  
   $Id: ckconfig.c,v 1.10 2000/07/01 18:17:38 wuftpd Exp $
****************************************************************************/
#include "config.h"
#ifndef HOST_ACCESS
#define  HOST_ACCESS  1
#endif
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "pathnames.h"

/* Prototypes */
#ifdef VIRTUAL
extern int read_servers_line(FILE *, char *, char *);
#endif
void print_copyright(void);

int main(int argc, char **argv)
{
    struct stat sbuf;
    char *sp;
    char buf[1024];
    int c;

#ifdef VIRTUAL
    FILE *svrfp;
    char accesspath[1024];
    char hostaddress[32];
#endif

    if (argc > 1) {
	while ((c = 
/*There is a buffer overflow security problem using the following GETOPT()*/
getopt(argc, argv, "V")) != EOF) {
	    switch (c) {
	    case 'V':
		print_copyright();
		exit(0);
	    default:
		fprintf(stderr, "usage: %s [-V]\n", argv[0]);
		exit(1);
	    }
	}
    }

    /* _PATH_FTPUSERS   */
    fprintf(stdout, "Checking _PATH_FTPUSERS :: %s\n", _PATH_FTPUSERS);
    if ((stat(_PATH_FTPUSERS, &sbuf)) < 0)
	printf("I can't find it... look in doc/examples for an example.\n");
    else
	printf("ok.\n");

#ifdef VIRTUAL

    /* _PATH_FTPSERVERS  */
    fprintf(stdout, "\nChecking _PATH_FTPSERVERS :: %s\n", _PATH_FTPSERVERS);
    if ((stat(_PATH_FTPSERVERS, &sbuf)) < 0)
	printf("I can't find it... look in doc/examples for an example.\n");
    else {
	printf("ok.\n");
	/* Need to check the access files specified in the ftpservers file. */
	if ((svrfp = fopen(_PATH_FTPSERVERS, "r")) == NULL)
	    printf("I can't open it! check permissions and run ckconfig again.\n");
	else {
	    while (read_servers_line(svrfp, hostaddress, accesspath) == 1) {
		fprintf(stderr, "\nChecking accessfile for %s :: %s\n", hostaddress, accesspath);
		/*
		   ** check to see that a valid directory value was
		   ** supplied and not something such as "INTERNAL"
		   **
		   ** It is valid to have a string such as "INTERNAL" in the
		   ** ftpservers entry. This is not an error. Silently ignore it.
		 */
		if (stat(accesspath, &sbuf) == 0) {
		    if ((sbuf.st_mode & S_IFMT) == S_IFDIR)
			printf("ok.\n");
		    else {
			printf("Check servers file and make sure only directories are listed...\n");
			printf("look in doc/examples for an example.\n");
		    }
		}
		else
		    printf("Internal ftpaccess usage specified... ok.\n");
	    }
	    fclose(svrfp);
	}
    }
#endif

    /* _PATH_FTPACCESS  */
    fprintf(stdout, "\nChecking _PATH_FTPACCESS :: %s\n", _PATH_FTPACCESS);
    if ((stat(_PATH_FTPACCESS, &sbuf)) < 0)
	printf("I can't find it... look in doc/examples for an example.\n");
    else
	printf("ok.\n");

    /* _PATH_PIDNAMES   */
    fprintf(stdout, "\nChecking _PATH_PIDNAMES :: %s\n", _PATH_PIDNAMES);
    _strcpy(sizeof(buf),buf, _PATH_PIDNAMES);
    sp = (char *) strrchr(buf, '/');
    *sp = '\0';
    if ((stat(buf, &sbuf)) < 0) {
	printf("I can't find it...\n");
	printf("You need to make this directory [%s] in order for\n", buf);
	printf("the limit and user count functions to work.\n");
    }
    else
	printf("ok.\n");

    /* _PATH_CVT        */
    fprintf(stdout, "\nChecking _PATH_CVT :: %s\n", _PATH_CVT);
    if ((stat(_PATH_CVT, &sbuf)) < 0)
	printf("I can't find it... look in doc/examples for an example.\n");
    else
	printf("ok.\n");

    /* _PATH_XFERLOG    */
    fprintf(stdout, "\nChecking _PATH_XFERLOG :: %s\n", _PATH_XFERLOG);
    if ((stat(_PATH_XFERLOG, &sbuf)) < 0) {
	printf("I can't find it... \n");
	printf("Don't worry, it will be created automatically by the\n");
	printf("server if you do transfer logging.\n");
    }
    else
	printf("ok.\n");

    /* _PATH_PRIVATE    */
    fprintf(stdout, "\nChecking _PATH_PRIVATE :: %s\n", _PATH_PRIVATE);
    if ((stat(_PATH_PRIVATE, &sbuf)) < 0) {
	printf("I can't find it... look in doc/examples for an example.\n");
	printf("You only need this if you want SITE GROUP and SITE GPASS\n");
	printf("functionality. If you do, you will need to edit the example.\n");
    }
    else
	printf("ok.\n");

    /* _PATH_FTPHOSTS   */
    fprintf(stdout, "\nChecking _PATH_FTPHOSTS :: %s\n", _PATH_FTPHOSTS);
    if ((stat(_PATH_FTPHOSTS, &sbuf)) < 0) {
	printf("I can't find it... look in doc/examples for an example.\n");
	printf("You only need this if you are using the HOST ACCESS features\n");
	printf("of the server.\n");
    }
    else
	printf("ok.\n");
    return (0);
}
/****************************************************************************  
  $Id: conversions.c,v 1.10 2000/07/01 18:17:38 wuftpd Exp $ 
****************************************************************************/
#include "config.h"

#include <stdio.h>
#include <errno.h>
#ifdef HAVE_SYS_SYSLOG_H
#include <sys/syslog.h>
#endif
#if defined(HAVE_SYSLOG_H) || (!defined(AUTOCONF) && !defined(HAVE_SYS_SYSLOG_H))
#include <syslog.h>
#endif

extern char *strsep(char **, const char *);

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "conversions.h"
#include "extensions.h"
#include "pathnames.h"
#include "proto.h"

/*************************************************************************/
/* FUNCTION  : readconv                                                  */
/* PURPOSE   : Read the conversions into memory                          */
/* ARGUMENTS : The pathname of the conversion file                       */
/* RETURNS   : 0 if error, 1 if no error                                 */
/*************************************************************************/

char *convbuf = NULL;
struct convert *cvtptr;

struct str2int {
    char *string;
    int value;
};

struct str2int c_list[] =
{
    {"T_REG", T_REG},
    {"T_ASCII", T_ASCII},
    {"T_DIR", T_DIR},
    {"O_COMPRESS", O_COMPRESS},
    {"O_UNCOMPRESS", O_UNCOMPRESS},
    {"O_TAR", O_TAR},
    {NULL, 0},
};

static int conv(char *str)
{
    int rc = 0;
    int counter;

    /* check for presence of ALL items in string... */

    if (str)
	for (counter = 0; c_list[counter].string; ++counter)
	    if (strstr(str, c_list[counter].string))
		rc = rc | c_list[counter].value;
    return (rc);
}

static int readconv(char *convpath)
{
    FILE *convfile;
    struct stat finfo;

    if ((convfile = fopen(convpath, "r")) == NULL) {
	if (errno != ENOENT)
	    syslog(LOG_ERR, "cannot open conversion file %s: %s",
		   convpath, strerror(errno));
	return (0);
    }
    if (fstat(fileno(convfile), &finfo) != 0) {
	syslog(LOG_ERR, "cannot fstat conversion file %s: %s", convpath,
	       strerror(errno));
	(void) fclose(convfile);
	return (0);
    }
    if (finfo.st_size == 0) {
	convbuf = (char *) calloc(1, 1);
    }
    else {
	if (!(convbuf = (char *) malloc((unsigned) finfo.st_size + 1))) {
	    syslog(LOG_ERR, "could not malloc convbuf (%d bytes)", finfo.st_size + 1);
	    (void) fclose(convfile);
	    return (0);
	}
	if (!fread(convbuf, (size_t) finfo.st_size, 1, convfile)) {
	    syslog(LOG_ERR, "error reading conv file %s: %s", convpath,
		   strerror(errno));
	    convbuf = NULL;
	    (void) fclose(convfile);
	    return (0);
	}
	*(convbuf + finfo.st_size) = '\0';
    }
    (void) fclose(convfile);
    return (1);
}

static void parseconv(void)
{
    char *ptr;
    char *convptr = convbuf, *line;
    char *argv[8], *p, *val;
    struct convert *cptr, *cvttail = (struct convert *) NULL;
    int n;

    if (!convbuf || !(*convbuf))
	return;

    /* read through convbuf, stripping comments. */
    while (*convptr != '\0') {
	line = convptr;
	while (*convptr && *convptr != '\n')
	    convptr++;
	*convptr++ = '\0';

	/* deal with comments */
	if ((ptr = strchr(line, '#')) != NULL)
	    *ptr = '\0';

	if (*line == '\0')
	    continue;

	/* parse the lines... */
	for (n = 0, p = line; n < 8 && p != NULL; n++) {
	    val = (char *) strsep(&p, ":\n");
	    argv[n] = val;
	    if ((argv[n][0] == ' ') || (argv[n][0] == '\0'))
		argv[n] = NULL;
	}
	/* check their were 8 fields, if not skip the line... */
	if (n != 8 || p != NULL)
	    continue;

	/* make sure the required elements are present */
	if ((!argv[0] && !argv[1] && !argv[2] && !argv[3]) || !argv[4] || !argv[7])
	    continue;

	/* add element to end of list */
	cptr = (struct convert *) calloc(1, sizeof(struct convert));

	if (cptr == NULL) {
	    syslog(LOG_ERR, "calloc error parsing ftpconversions");
	    exit(0);
	}
	if (cvttail)
	    cvttail->next = cptr;
	cvttail = cptr;
	if (!cvtptr)
	    cvtptr = cptr;

	cptr->stripprefix = (char *) argv[0];
	cptr->stripfix = (char *) argv[1];
	cptr->prefix = (char *) argv[2];
	cptr->postfix = (char *) argv[3];
	cptr->external_cmd = (char *) argv[4];
	cptr->types = conv((char *) argv[5]);
	cptr->options = conv((char *) argv[6]);
	cptr->name = (char *) argv[7];
    }
}

void conv_init(void)
{
#ifdef VERBOSE
    struct convert *cptr;
#endif

    if ((readconv(_path_cvt)) < 0)
	return;
    parseconv();
}


