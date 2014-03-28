%{
extern "C"
{
int yylex(void);
}


#include <stdio.h>
#include <string.h>
#include "y.tab.h"


extern YYSTYPE yylval;

%}

%%

char[256]*            {return CHAR;}


strcpy[256]*          {return STRCPY;}
strcat[256]*          {return STRCAT;}
bcopy[256]*           {return BCOPY;}
memcpy[256]*          {return MEMCPY;}
memchr[256]*          {return MEMCHR;}
memccpy[256]*         {return MEMCCPY;}
memmove[256]*         {return MEMMOVE;}
memset[256]*          {return MEMSET;}


sprintf[256]*         {return SPRINTF;}
vsprintf[256]*        {return VSPRINTF;}
gets[256]*            {return GETS;}
scanf[256]*           {return SCANF;}
getopt[256]*          {return GETOPT;}
strecpy[256]*         {return STRECPY;}
streadd[256]*         {return STREADD;}
strccpy[256]*         {return STRCCPY;}
strtrns[256]*         {return STRTRNS;}
wcscpy[256]*          {return WCSCPY;}
wcscat[256]*          {return WCSCAT;}


getpass[256]*         {return GETPASS;}
realpath[256]*        {return REALPATH;}

new[256]*             {return NEW;}
\;                    {return COM;}
[\(][\(]*             {yylval.string=strdup(yytext);return LBRAK;}
[,][256]*             {return SIMICOL;}
[\)][\)]*             {yylval.string=strdup(yytext);return RBRAK;}
"%"                   {return PERCENT;}
\"                    {return TCOM;}
\+                    {yylval.string=strdup(yytext);return PLUS;}
\*                    {yylval.string=strdup(yytext);return MUL;}
[\[256][256]*         {yylval.string=strdup(yytext);return LB;}
\]                    {yylval.string=strdup(yytext);return RB;}
["\-\/\_\!\&\'a-zA-Z0-9][a-zA-Z0-9\-\>.\!\'\_\/\\\"]*   {yylval.string=strdup(yytext);return WORD;}   
[][]*                 {yylval.string=strdup(yytext);return WHITE;}
\t                    {return TAB;}
\n                    {return EOL;}
.                     {yylval.string=strdup(yytext);return ANY;}


%%
