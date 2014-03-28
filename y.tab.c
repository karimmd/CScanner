/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "y.y"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SafeLib.h"
#include<sys/time.h>

FILE *outFile_p;
FILE *outFile_p1;

extern FILE *yyin;
int counter=0;
int pointer[500];
int pointer2;
char *temp[500];
char *temp2;
int i=0;

extern "C" 
{

int yylex(void);
int yyparse(void);
void yyerror(const char* str)

{fprintf(stderr,"error: %s in line: %d please check your function arguments!\n*** NOW: if you are sure your code is correct, \n please insert// before your function call\nin orderto ignore this syntax error\n",str,counter+1); }

int yywrap()
{
return 1;
}
}



/* Line 268 of yacc.c  */
#line 107 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHAR = 258,
     STRCPY = 259,
     STRCAT = 260,
     BCOPY = 261,
     MEMCPY = 262,
     MEMCHR = 263,
     MEMCCPY = 264,
     MEMMOVE = 265,
     MEMSET = 266,
     SPRINTF = 267,
     VSPRINTF = 268,
     GETS = 269,
     SCANF = 270,
     GETOPT = 271,
     STRECPY = 272,
     STREADD = 273,
     STRCCPY = 274,
     STRTRNS = 275,
     WCSCPY = 276,
     WCSCAT = 277,
     GETPASS = 278,
     REALPATH = 279,
     NEW = 280,
     COM = 281,
     TAB = 282,
     EOL = 283,
     SIMICOL = 284,
     PERCENT = 285,
     LBRAK = 286,
     RBRAK = 287,
     ANY = 288,
     PLUS = 289,
     NUMBER = 290,
     MUL = 291,
     TCOM = 292,
     WORD = 293,
     LB = 294,
     RB = 295,
     WHITE = 296
   };
#endif
/* Tokens.  */
#define CHAR 258
#define STRCPY 259
#define STRCAT 260
#define BCOPY 261
#define MEMCPY 262
#define MEMCHR 263
#define MEMCCPY 264
#define MEMMOVE 265
#define MEMSET 266
#define SPRINTF 267
#define VSPRINTF 268
#define GETS 269
#define SCANF 270
#define GETOPT 271
#define STRECPY 272
#define STREADD 273
#define STRCCPY 274
#define STRTRNS 275
#define WCSCPY 276
#define WCSCAT 277
#define GETPASS 278
#define REALPATH 279
#define NEW 280
#define COM 281
#define TAB 282
#define EOL 283
#define SIMICOL 284
#define PERCENT 285
#define LBRAK 286
#define RBRAK 287
#define ANY 288
#define PLUS 289
#define NUMBER 290
#define MUL 291
#define TCOM 292
#define WORD 293
#define LB 294
#define RB 295
#define WHITE 296




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 76 "y.y"

int number;
char *string;



/* Line 293 of yacc.c  */
#line 232 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 244 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   154

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNRULES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    15,    18,
      23,    30,    33,    36,    38,    40,    45,    49,    53,    57,
      62,    68,    74,    81,    88,    90,    93,    98,   104,   110,
     117,   124,   126,   129,   134,   141,   147,   149,   152,   156,
     161,   167,   174,   179,   185,   192,   197,   203,   208,   214,
     219,   225,   230,   232,   237,   242,   248,   254,   257,   260,
     263,   266,   269,   272,   275,   278,   281,   283,   285,   287,
     289,   291,   293,   295,   297,   299,   301,   303,   305,   307,
     309
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    -1,    43,    44,    -1,    47,    -1,    48,
      -1,    45,    -1,    46,    -1,     3,    38,    -1,     3,    38,
      39,    38,    -1,     3,    38,    39,    38,    29,    46,    -1,
      25,    38,    -1,    25,     3,    -1,    25,    -1,     3,    -1,
       3,    38,    39,    40,    -1,    38,    39,    40,    -1,    38,
      39,    34,    -1,    38,    39,    38,    -1,     4,    31,    38,
      29,    -1,     4,    31,    38,    41,    29,    -1,     4,    31,
      38,    32,    29,    -1,     4,    31,    38,    41,    32,    29,
      -1,     4,    31,    38,    34,    38,    29,    -1,     4,    -1,
       4,    31,    -1,     5,    31,    38,    29,    -1,     5,    31,
      38,    41,    29,    -1,     5,    31,    38,    32,    29,    -1,
       5,    31,    38,    41,    32,    29,    -1,     5,    31,    38,
      34,    38,    29,    -1,     5,    -1,     5,    31,    -1,     6,
      31,    38,    29,    -1,     6,    31,    38,    34,    38,    29,
      -1,     6,    31,    38,    41,    29,    -1,     6,    -1,     6,
      31,    -1,     6,    31,    33,    -1,     7,    31,    38,    29,
      -1,     7,    31,    38,    41,    29,    -1,     7,    31,    38,
      34,    38,    29,    -1,     8,    31,    38,    29,    -1,     8,
      31,    38,    41,    29,    -1,     8,    31,    38,    34,    38,
      29,    -1,     9,    31,    38,    29,    -1,     9,    31,    38,
      41,    29,    -1,    10,    31,    38,    29,    -1,    10,    31,
      38,    41,    29,    -1,    11,    31,    38,    29,    -1,    11,
      31,    38,    41,    29,    -1,    12,    31,    38,    29,    -1,
      12,    -1,    14,    31,    38,    32,    -1,    13,    31,    38,
      29,    -1,    15,    31,    37,    30,    38,    -1,    15,    31,
      37,    30,    35,    -1,    16,    31,    -1,    23,    31,    -1,
      20,    31,    -1,    24,    31,    -1,    17,    31,    -1,    18,
      31,    -1,    19,    31,    -1,    21,    31,    -1,    22,    31,
      -1,    38,    -1,    41,    -1,    27,    -1,    28,    -1,    31,
      -1,    32,    -1,    29,    -1,    30,    -1,    34,    -1,    33,
      -1,    37,    -1,    36,    -1,    26,    -1,    39,    -1,    40,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    98,   101,   102,   103,   104,   107,   108,
     117,   127,   130,   133,   136,   139,   142,   145,   149,   158,
     168,   178,   188,   198,   207,   210,   213,   222,   231,   239,
     248,   256,   259,   262,   271,   281,   290,   293,   296,   299,
     308,   318,   327,   336,   346,   355,   364,   374,   383,   393,
     402,   412,   423,   426,   436,   448,   453,   456,   461,   466,
     471,   476,   481,   486,   491,   496,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "STRCPY", "STRCAT", "BCOPY",
  "MEMCPY", "MEMCHR", "MEMCCPY", "MEMMOVE", "MEMSET", "SPRINTF",
  "VSPRINTF", "GETS", "SCANF", "GETOPT", "STRECPY", "STREADD", "STRCCPY",
  "STRTRNS", "WCSCPY", "WCSCAT", "GETPASS", "REALPATH", "NEW", "COM",
  "TAB", "EOL", "SIMICOL", "PERCENT", "LBRAK", "RBRAK", "ANY", "PLUS",
  "NUMBER", "MUL", "TCOM", "WORD", "LB", "RB", "WHITE", "$accept",
  "commands", "command", "search3", "search4", "search1", "search2", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    43,    44,    44,    44,    44,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    46,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     2,     4,
       6,     2,     2,     1,     1,     4,     3,     3,     3,     4,
       5,     5,     6,     6,     1,     2,     4,     5,     5,     6,
       6,     1,     2,     4,     6,     5,     1,     2,     3,     4,
       5,     6,     4,     5,     6,     4,     5,     4,     5,     4,
       5,     4,     1,     4,     4,     5,     5,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    14,    24,    31,    36,     0,     0,     0,
       0,     0,    52,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    13,    78,    68,    69,    72,
      73,    70,    71,    75,    74,    77,    76,    66,    79,    80,
      67,     3,     6,     7,     4,     5,     8,    25,    32,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57,
      61,    62,    63,    59,    64,    65,    58,    60,    12,    11,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,    18,    16,     9,    15,
      19,     0,     0,     0,    26,     0,     0,     0,    33,     0,
       0,    39,     0,     0,    42,     0,     0,    45,     0,    47,
       0,    49,     0,    51,    54,    53,     0,     0,    21,     0,
      20,     0,    28,     0,    27,     0,     0,    35,     0,    40,
       0,    43,    46,    48,    50,    56,    55,     0,    10,    23,
      22,    30,    29,    34,    41,    44,     0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    41,    42,    43,    44,    45
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -38
static const yytype_int8 yypact[] =
{
     -38,     0,   -38,   -37,   -29,    48,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    32,   -38,   -38,   -38,   -38,
     -38,   -38,   -38,   -38,   -38,   -38,   -38,    69,   -38,   -38,
     -38,   -38,   -38,   -38,   -38,   -38,    70,    72,    73,    28,
      74,    75,    76,    77,    78,    79,    80,    81,    83,   -38,
     -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,
      34,    29,    13,    14,   -38,    15,    23,    24,    21,    22,
      30,    31,    71,    89,    92,   -38,   -38,   -38,    94,   -38,
     -38,    95,    87,    44,   -38,    97,    90,    46,   -38,    91,
      98,   -38,    93,   101,   -38,    96,   103,   -38,   104,   -38,
     106,   -38,   107,   -38,   -38,   -38,    42,    99,   -38,   109,
     -38,   110,   -38,   111,   -38,   112,   113,   -38,   114,   -38,
     115,   -38,   -38,   -38,   -38,   -38,   -38,   108,   -38,   -38,
     -38,   -38,   -38,   -38,   -38,   -38,   116
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -38,   -38,   -38,   -38,   -16,   -38,   -38
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       2,    46,    47,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    68,    35,    36,    37,    38,
      39,    40,    90,    94,    98,    91,    95,    92,    96,    99,
     107,   109,   101,   104,    93,    97,   100,   102,   105,   111,
     113,    74,   108,   110,   103,   106,    75,    88,    85,    89,
      69,   112,    86,   120,    87,   124,   121,   135,   125,    48,
     136,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
     114,   138,     0,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    76,    77,    78,    79,    80,    81,    82,    83,
      84,   115,   116,   117,   118,   119,   122,   127,   123,   126,
     129,   128,   131,   132,   130,   133,   134,   137,   139,   140,
     141,   142,   143,   144,   145,     0,     0,   146,     0,     0,
       0,     0,     0,     0,    86
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-38))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       0,    38,    31,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,     3,    36,    37,    38,    39,
      40,    41,    29,    29,    29,    32,    32,    34,    34,    34,
      29,    29,    29,    29,    41,    41,    41,    34,    34,    29,
      29,    33,    41,    41,    41,    41,    38,    38,    34,    40,
      38,    41,    38,    29,    40,    29,    32,    35,    32,    31,
      38,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      29,   117,    -1,    -1,    -1,    -1,    -1,    -1,    39,    39,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      37,    32,    30,    29,    29,    38,    29,    29,    38,    38,
      29,    38,    29,    29,    38,    29,    29,    38,    29,    29,
      29,    29,    29,    29,    29,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    43,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    36,    37,    38,    39,    40,
      41,    44,    45,    46,    47,    48,    38,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,     3,    38,
      39,    39,    38,    38,    33,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    37,    34,    38,    40,    38,    40,
      29,    32,    34,    41,    29,    32,    34,    41,    29,    34,
      41,    29,    34,    41,    29,    34,    41,    29,    41,    29,
      41,    29,    41,    29,    29,    32,    30,    29,    29,    38,
      29,    32,    29,    38,    29,    32,    38,    29,    38,    29,
      38,    29,    29,    29,    29,    35,    38,    38,    46,    29,
      29,    29,    29,    29,    29,    29,    39
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 97 "y.y"
    {fprintf(outFile_p,"%s","#include \"SafeLib.h\"\n");}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 107 "y.y"
    {fprintf(outFile_p,"%s%s","char",(yyvsp[(2) - (2)].string));}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 109 "y.y"
    {printf("pointer_before=%d",pointer);temp[i]=(yyvsp[(2) - (4)].string);
       printf("\ni=%d\n",i);
       if(!strcmp((yyvsp[(4) - (4)].string),"4"))
       {pointer[i]=1;printf("pointer=%d",pointer[i]);}
       else
       {pointer[i]=0;printf("pointer=%d",pointer[i]);}i++;
       fprintf(outFile_p,"%s%s%s%s","char",(yyvsp[(2) - (4)].string),(yyvsp[(3) - (4)].string),(yyvsp[(4) - (4)].string));
       printf("\ntemp=%s\n",temp[i-1]);}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 118 "y.y"
    {printf("pointer_before=%d",pointer);temp[i]=(yyvsp[(2) - (6)].string);
       printf("\ni=%d\n",i);
       if (!strcmp((yyvsp[(4) - (6)].string),"4"))
       {pointer[i]=1;printf("pointer=%d",pointer[i]);}
       else
       {pointer[i]=0;printf("pointer=%d",pointer[i]);}i++;
       fprintf(outFile_p,"%s%s%s%s","char",(yyvsp[(2) - (6)].string),(yyvsp[(3) - (6)].string),(yyvsp[(4) - (6)].string));
       printf("\ntemp=%s\n",temp[i-1]);}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 128 "y.y"
    {fprintf(outFile_p,"%s%s","new ",(yyvsp[(2) - (2)].string));}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 131 "y.y"
    {fprintf(outFile_p,"%s%s","new ","char");}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 134 "y.y"
    {fprintf(outFile_p,"new");}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 137 "y.y"
    {fprintf(outFile_p,"char");}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 140 "y.y"
    {fprintf(outFile_p,"%s%s%s%s","char ",(yyvsp[(2) - (4)].string),(yyvsp[(3) - (4)].string),(yyvsp[(4) - (4)].string));}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 143 "y.y"
    {fprintf(outFile_p,"%s%s%s",(yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].string),(yyvsp[(3) - (3)].string));}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 146 "y.y"
    {fprintf(outFile_p,"%s%s%s",(yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].string),(yyvsp[(3) - (3)].string));}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 150 "y.y"
    {printf("pointer_before=%d",pointer);temp[i]=(yyvsp[(1) - (3)].string);
       printf("\ni=%d\n",i); 
       if (!strcmp((yyvsp[(3) - (3)].string),"4")) {pointer[i]=1;printf("pointer=%d",pointer[i]);}
       else {pointer[i]=0;printf("pointer=%d",pointer[i]);}i++;
       fprintf(outFile_p,"%s%s%s",(yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].string),(yyvsp[(3) - (3)].string));
       printf("\ntemp=%s\n",temp[i-1]);}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 159 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (4)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~strcpy(",(yyvsp[(3) - (4)].string),",");
        fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_strcpy","(sizeof(",(yyvsp[(3) - (4)].string),"),",(yyvsp[(3) - (4)].string),",");
        fprintf(outFile_p1,"\nThere is a strcpy() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 169 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (5)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
	for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~strcpy(",(yyvsp[(3) - (5)].string),",");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_strcpy","(sizeof(",(yyvsp[(3) - (5)].string),"),",(yyvsp[(3) - (5)].string),",");
        fprintf(outFile_p1,"\nThere is a strcpy() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 179 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (5)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
	for(j=0;j<i;j++)
	{if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s%s","_~strcpy",(yyvsp[(2) - (5)].string),(yyvsp[(3) - (5)].string),"),");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s%s","_strcpy",(yyvsp[(2) - (5)].string),"sizeof(",(yyvsp[(3) - (5)].string),")),",(yyvsp[(3) - (5)].string),",");
        fprintf(outFile_p1,"\nThere is a strcpy() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 189 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (6)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for (j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~strcpy(",(yyvsp[(3) - (6)].string),",");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_strcpy","(sizeof(",(yyvsp[(3) - (6)].string),"),",(yyvsp[(3) - (6)].string),",");
        fprintf(outFile_p1,"\nThere is a strcpy() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 199 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (6)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s%s%s%s%s%s%s","~+~strcpy(","4","-",(yyvsp[(5) - (6)].string),",",(yyvsp[(3) - (6)].string),"+",(yyvsp[(5) - (6)].string),",");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s%s%s%s%s%s","_strcpy",(yyvsp[(2) - (6)].string),"sizeof(",(yyvsp[(3) - (6)].string),")-",(yyvsp[(5) - (6)].string),",",(yyvsp[(3) - (6)].string),"+",(yyvsp[(5) - (6)].string),",");
        fprintf(outFile_p1,"\nThere is a strcpy() rewrite process in line %d\n",counter+1);}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 208 "y.y"
    {fprintf(outFile_p,"%s","strcpy");}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 211 "y.y"
    {fprintf(outFile_p,"%s","strcpy");}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 214 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (4)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~strcat(",(yyvsp[(3) - (4)].string),",");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_strcat","(sizeof(",(yyvsp[(3) - (4)].string),"),",(yyvsp[(3) - (4)].string),",");
        fprintf(outFile_p1,"\nThere is a strcat() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 223 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (5)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for (j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~strcat(",(yyvsp[(3) - (5)].string),",");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_strcat","(sizeof(",(yyvsp[(3) - (5)].string),"),",(yyvsp[(3) - (5)].string),",");
        fprintf(outFile_p1,"\nThere is a strcat() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 232 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (5)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
	for (j=0;j<i;j++)
	{if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s%s","_~strcat",(yyvsp[(2) - (5)].string),(yyvsp[(3) - (5)].string),"),");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s%s","_strcat",(yyvsp[(2) - (5)].string),"sizeof(",(yyvsp[(3) - (5)].string),")),",(yyvsp[(3) - (5)].string),",");printf("\nfals=%d\n",fals);
        fprintf(outFile_p1,"\nThere is a strcat() rewrite process in line %d\n",counter+1);}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 240 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (6)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for (j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~strcat(",(yyvsp[(3) - (6)].string),",");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_strcat","(sizeof(",(yyvsp[(3) - (6)].string),"),",(yyvsp[(3) - (6)].string),",");
        fprintf(outFile_p1,"\nThere is a strcat() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 249 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (6)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for (j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s%s%s%s%s%s%s","~+~strcat(","4","-",(yyvsp[(5) - (6)].string),",",(yyvsp[(3) - (6)].string),"+",(yyvsp[(5) - (6)].string),",");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s%s%s%s%s%s","_strcat",(yyvsp[(2) - (6)].string),"sizeof(",(yyvsp[(3) - (6)].string),")-",(yyvsp[(5) - (6)].string),",",(yyvsp[(3) - (6)].string),"+",(yyvsp[(5) - (6)].string),",");
        fprintf(outFile_p1,"\nThere is a strcat() rewrite process in line %d\n",counter+1);}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 257 "y.y"
    {fprintf(outFile_p,"%s","strcat");}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 260 "y.y"
    {fprintf(outFile_p,"%s","strcat");}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 263 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (4)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for (j=0;j<i;j++)
        {if (!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~bcopy(",(yyvsp[(3) - (4)].string),",");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_bcopy","(sizeof(",(yyvsp[(3) - (4)].string),"),",(yyvsp[(3) - (4)].string),",");
        fprintf(outFile_p1,"\nThere is a bcopy() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 272 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (6)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for (j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s%s%s%s%s%s%s%s","~+~bcopy","$2","4","-",(yyvsp[(5) - (6)].string),",",(yyvsp[(3) - (6)].string),"+",(yyvsp[(5) - (6)].string),",");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s%s%s%s%s%s","_bcopy",(yyvsp[(2) - (6)].string),"sizeof(",(yyvsp[(3) - (6)].string),")-",(yyvsp[(5) - (6)].string),",",(yyvsp[(3) - (6)].string),"+",(yyvsp[(5) - (6)].string),",");
        fprintf(outFile_p1,"\nThere is a bcopy() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 282 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (5)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for (j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~bcopy(",(yyvsp[(3) - (5)].string),",");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_bcopy","(sizeof(",(yyvsp[(3) - (5)].string),"),",(yyvsp[(3) - (5)].string),",");
        fprintf(outFile_p1,"\nThere is a bcopy() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 291 "y.y"
    {fprintf(outFile_p,"%s","_bcopy");}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 294 "y.y"
    {fprintf(outFile_p,"%s%s","_bcopy",(yyvsp[(2) - (2)].string));}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 297 "y.y"
    {fprintf(outFile_p,"%s%s%s","_bcopy",(yyvsp[(2) - (3)].string),(yyvsp[(3) - (3)].string));}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 300 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (4)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~memcpy(",(yyvsp[(3) - (4)].string),",");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_memcpy","(sizeof(",(yyvsp[(3) - (4)].string),"),",(yyvsp[(3) - (4)].string),",");
        fprintf(outFile_p1,"\nThere is a memcpy() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 309 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (5)].string),printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~memcpy(",(yyvsp[(3) - (5)].string),",");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_memcpy","(sizeof(",(yyvsp[(3) - (5)].string),"),",(yyvsp[(3) - (5)].string),",");
        fprintf(outFile_p1,"\nThere is a memcpy() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 319 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (6)].string),printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s%s%s%s%s%s%s","~+~memcpy(","4","-",(yyvsp[(5) - (6)].string),",",(yyvsp[(3) - (6)].string),"+",(yyvsp[(5) - (6)].string),",");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s%s%s%s%s%s","_memcpy",(yyvsp[(2) - (6)].string),"sizeof(",(yyvsp[(3) - (6)].string),")-",(yyvsp[(5) - (6)].string),",",(yyvsp[(3) - (6)].string),"+",(yyvsp[(5) - (6)].string),",");
        fprintf(outFile_p1,"\nThere is a memcpy() rewrite process in line %d\n",counter+1);}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 328 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (4)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~memchr(",(yyvsp[(3) - (4)].string),",");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_memchr","(sizeof(",(yyvsp[(3) - (4)].string),"),",(yyvsp[(3) - (4)].string),",");
        fprintf(outFile_p1,"\nThere is a memchr() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 337 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (5)].string),printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~memchr(",(yyvsp[(3) - (5)].string),",");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_memchr","(sizeof(",(yyvsp[(3) - (5)].string),"),",(yyvsp[(3) - (5)].string),",");
        fprintf(outFile_p1,"\nThere is a memchr() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 347 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (6)].string),printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s%s%s%s%s%s%s","~+~memchr(","4","-",(yyvsp[(5) - (6)].string),",",(yyvsp[(3) - (6)].string),"+",(yyvsp[(5) - (6)].string),",");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s%s%s%s%s%s","_memchr",(yyvsp[(2) - (6)].string),"sizeof(",(yyvsp[(3) - (6)].string),")-",(yyvsp[(5) - (6)].string),",",(yyvsp[(3) - (6)].string),"+",(yyvsp[(5) - (6)].string),",");
        fprintf(outFile_p1,"\nThere is a memchr() rewrite process in line %d\n",counter+1);}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 356 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (4)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~memccpy(",(yyvsp[(3) - (4)].string),",");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_memccpy","(sizeof(",(yyvsp[(3) - (4)].string),"),",(yyvsp[(3) - (4)].string),",");
        fprintf(outFile_p1,"\nThere is a memccpy() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 365 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (5)].string),printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~memccpy(",(yyvsp[(3) - (5)].string),",");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_memccpy","(sizeof(",(yyvsp[(3) - (5)].string),"),",(yyvsp[(3) - (5)].string),",");
        fprintf(outFile_p1,"\nThere is a memccpy() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 375 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (4)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~memmove(",(yyvsp[(3) - (4)].string),",");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_memmove","(sizeof(",(yyvsp[(3) - (4)].string),"),",(yyvsp[(3) - (4)].string),",");
        fprintf(outFile_p1,"\nThere is a memmove() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 384 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (5)].string),printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~memmove(",(yyvsp[(3) - (5)].string),",");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_memmove","(sizeof(",(yyvsp[(3) - (5)].string),"),",(yyvsp[(3) - (5)].string),",");
        fprintf(outFile_p1,"\nThere is a memmove() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 394 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (4)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~memset(",(yyvsp[(3) - (4)].string),",");fals=1;break;}k++;}if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_memset","(sizeof(",(yyvsp[(3) - (4)].string),"),",(yyvsp[(3) - (4)].string),",");
        fprintf(outFile_p1,"\nThere is a memset() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 403 "y.y"
    {int fals=0;temp2=(yyvsp[(3) - (5)].string),printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2)&& pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s","_~memset(",(yyvsp[(3) - (5)].string),",");fals=1;break;}k++;}
        if(fals==0)
        fprintf(outFile_p,"%s%s%s%s%s%s","_memset","(sizeof(",(yyvsp[(3) - (5)].string),"),",(yyvsp[(3) - (5)].string),",");
        fprintf(outFile_p1,"\nThere is a memset() rewrite process in line %d\n",counter+1);
        printf("\nfals=%d\n",fals);}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 413 "y.y"
    {int flipper1=0;int fals=0;temp2=(yyvsp[(3) - (4)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for (j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s%s","/*warning: This function sprintf() has a buffer overflow security problem*/","sprintf(",(yyvsp[(3) - (4)].string),",");
        fprintf(outFile_p1,"\n High-Risk Warning::There is a sprintf() buffer overflow security problem in line %d::It is recommended to use snprintf() instead of sprintf()....\n snprintf is not exist in the standard library\n",counter+1);flipper1=1;fals=1;break;}
        if(!strcmp(temp[k],temp2))
        {fprintf(outFile_p,"%s%s%s%s","/*warning: This function sprintf() has a buffer overflow security problem*/","sprintf(",(yyvsp[(3) - (4)].string),",");
        fprintf(outFile_p1,"\n High-Risk Warning::There is a sprintf() buffer overflow security problem in line %d::It is recommended to use snprintf() instead of sprintf()....\n",counter+1);flipper1=1;break;}k++;}
        if(flipper1==0)fprintf(outFile_p,"%s%s%s","sprintf(",(yyvsp[(3) - (4)].string),",");}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 424 "y.y"
    {fprintf(outFile_p,"%s","sprintf");}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 427 "y.y"
    {int flipper1=0;int fals=0;temp2=(yyvsp[(3) - (4)].string);printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for (j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s%s","/*warning: This function gets() has a buffer overflow security problem*/","gets(",(yyvsp[(3) - (4)].string),")");
        fprintf(outFile_p1,"\n Very High-Risk Warning::There is a gets() buffer overflow security problem in line %d::It is recommended to use fgets() instead....\n",counter+1);flipper1=1;fals=1;break;}
        if(!strcmp(temp[k],temp2))
        {fprintf(outFile_p,"%s%s%s%s","/*warning: This function gets() has a buffer overflow security problem*/","gets(",(yyvsp[(3) - (4)].string),")");fprintf(outFile_p1,"\n Very High-Risk Warning::There is a gets() buffer overflow security problem in line %d::It is recommended to use fgets() instead....\n",counter+1);flipper1=1;break;}k++;}if(flipper1==0)
        fprintf(outFile_p,"%s%s%s","gets(",(yyvsp[(3) - (4)].string),")");}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 437 "y.y"
    {int flipper1=0;int fals=0;temp2=(yyvsp[(3) - (4)].string);
        printf("\ntemp2=%s\n",temp2);int j=0;int k=0;
        for(j=0;j<i;j++)
        {if(!strcmp(temp[k],temp2) && pointer[k]==1)
        {fprintf(outFile_p,"%s%s%s%s","/*warning: This function vsprintf()has a buffer overflow security problem*/","vsprintf(",(yyvsp[(3) - (4)].string),",");
	fprintf(outFile_p1,"\n High-Risk Warning::There is a vsprintf() buffer overflow security problem in line %d::It is recommended to use vsnprintf() instead of vsprintf()....\n vsnprintf is not exist in the standard library\n",counter+1);flipper1=1;fals=1;break;}
        if(!strcmp(temp[k],temp2))
        {fprintf(outFile_p,"%s%s%s%s","/*warning: This function vsprintf() has a buffer overflow security problem*/","vsprintf(",(yyvsp[(3) - (4)].string),",");
	fprintf(outFile_p1,"\n High-Risk Warning::There is a vsprintf() buffer overflow security problem in line %d::It is recommended to use vsnprintf() instead of vsprintf()....\n",counter+1);flipper1=1;break;}k++;}
        if(flipper1==0)fprintf(outFile_p,"%s%s%s","vsprintf(",(yyvsp[(3) - (4)].string),",");}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 449 "y.y"
    {fprintf(outFile_p,"%s%s%s%s","\n/*There is a buffer overflow security problem using the following SCANF()*/\nscanf(","\"","%",(yyvsp[(5) - (5)].string));
	fprintf(outFile_p1,"\n High-Risk Warning::There is a scanf() buffer overflow security problem \n in line= %d,make sure that \%%s is given\n a defined value(i,e,\%%32s)\n",counter +1); 
	printf ("High-Risk Warning::There is a scanf() buffer overflow security problem in line=%d\n",counter+1);}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 454 "y.y"
    {fprintf(outFile_p,"%s%s%s%s","scanf(","\"","%",(yyvsp[(5) - (5)].string));}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 457 "y.y"
    {fprintf(outFile_p,"\n/*There is a buffer overflow security problem using the following GETOPT()*/\ngetopt()");
	fprintf(outFile_p1,"\n High-Risk Warning::There is a getopt() buffer overflow security problem in line %d\n",counter+1); 
        printf ("Warning:buffer overflow problem in line=%d\n",counter+1);}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 462 "y.y"
    {fprintf(outFile_p,"\n/*There is a buffer overflow security problem using the following GETPASS()*/\ngetpass()");
        fprintf(outFile_p1,"\n High-Risk Warning::There is a getpass() buffer overflow security problem in line %d\n",counter+1); 
        printf ("Warning:buffer overflow problem in line=%d\n",counter+1);}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 467 "y.y"
    {fprintf(outFile_p,"/*There is a buffer overflow security problem using the following STRTRNS()*/strtrns()");
        fprintf(outFile_p1,"\n Medium-Risk Warning::There is a buffer overflow security problem in line %d\n",counter+1); 
        printf ("Warning:buffer overflow problem in line=%d\n",counter+1);}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 472 "y.y"
    {fprintf(outFile_p,"\n/*Warning::There is buffer overflow security problem using the following REALPATH()*/\nrealpath()");
	fprintf(outFile_p1,"\n Medium-Risk Warning::There is a realpath() buffer overflow security problem in line %d\n",counter+1);
	printf("Warning:buffer overflow problem in line =%d\n",counter+1);}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 477 "y.y"
    {fprintf(outFile_p,"\n/*Warning::There is buffer overflow security problem using the following STRECPY()*/\nstrecpy()");
	fprintf(outFile_p1,"\n Medium-Risk Warning::There is a strecpy() buffer overflow security problem in line %d\n",counter+1);
	printf("Warning:buffer overflow problem in line =%d\n",counter+1);}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 482 "y.y"
    {fprintf(outFile_p,"\n/*Warning::There is buffer overflow security problem using the following STREADD()*/\nstreadd()");
	fprintf(outFile_p1,"\n Medium-Risk Warning::There is a streadd() buffer overflow security problem in line %d\n",counter+1);
	printf("Warning:buffer overflow problem in line =%d\n",counter+1);}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 487 "y.y"
    {fprintf(outFile_p,"\n/*Warning::There is buffer overflow security problem using the following STRCCPY()*/\nstrccpy()");
	fprintf(outFile_p1,"\n Medium-Risk Warning::There is a strccpy() buffer overflow security problem in line %d\n",counter+1);
	printf("Warning:buffer overflow problem in line =%d\n",counter+1);}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 492 "y.y"
    {fprintf(outFile_p,"\n/*Warning::There is buffer overflow security problem using the following WCSCPY()*/\nwcscpy()");
	fprintf(outFile_p1,"\n Medium-Risk Warning::There is a wcscpy() buffer overflow security problem in line %d\n",counter+1);
	printf("Warning:buffer overflow problem in line =%d\n",counter+1);}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 497 "y.y"
    {fprintf(outFile_p,"\n/*Warning::There is buffer overflow security problem using the following WCSCAT()*/\nwcscat()");
	fprintf(outFile_p1,"\n Medium-Risk Warning::There is a wcscat() buffer overflow security problem in line %d\n",counter+1);
	printf("Warning:buffer overflow problem in line =%d\n",counter+1);}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 505 "y.y"
    {fprintf(outFile_p,(yyvsp[(1) - (1)].string));}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 506 "y.y"
    {fprintf(outFile_p,(yyvsp[(1) - (1)].string));}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 507 "y.y"
    {fprintf(outFile_p,"\t");}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 508 "y.y"
    {counter=counter+1;fprintf(outFile_p,"\n");}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 509 "y.y"
    {fprintf(outFile_p,(yyvsp[(1) - (1)].string));}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 510 "y.y"
    {fprintf(outFile_p,(yyvsp[(1) - (1)].string));}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 511 "y.y"
    {fprintf(outFile_p,",");}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 512 "y.y"
    {fprintf(outFile_p,"%%");}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 513 "y.y"
    {fprintf(outFile_p,"+");}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 514 "y.y"
    {fprintf(outFile_p,(yyvsp[(1) - (1)].string));}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 515 "y.y"
    {fprintf(outFile_p,"\"");}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 516 "y.y"
    {fprintf(outFile_p,(yyvsp[(1) - (1)].string));}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 517 "y.y"
    {fprintf(outFile_p,";");}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 518 "y.y"
    {fprintf(outFile_p,"[");}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 519 "y.y"
    {fprintf(outFile_p,"]");}
    break;



/* Line 1806 of yacc.c  */
#line 2340 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 521 "y.y"

     
     int main(int argc,char*argv[])  
     {
       
         int line_count = 0;
         FILE *fp;
         char ch;
         fp=fopen(argv[1],"r");
         while ((ch = fgetc(fp)) != EOF)
         {
         if (ch  ==  '\n')
         {
         line_count++;
         }
         }     
         
         if(argc<3)
         {
             printf("please specify the input and out file \n");
             exit(0);
             }
         
         fp=fopen(argv[1],"r");
          if(!fp)
             {
                 printf("couldn't open file for reading \n");
                 exit(0);
              }
         outFile_p=fopen(argv[2],"w");
         outFile_p1=fopen(argv[3],"w");
         if(!outFile_p)
             {
                 printf("couldn't open temp for writing outfile_p \n");
                 exit(0);
                 }
         if(!outFile_p1)
             {
                 printf("couldn't open temp for writing outfile_p1 \n");
                 exit(0);
                 }
        
    struct timeval tim; 
    gettimeofday(&tim, NULL);  
    double t1=tim.tv_sec+(tim.tv_usec/1000000.0);                   
    yyin=fp;
    yyparse();
    gettimeofday(&tim, NULL);  
    double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
    double fsecs;  
    fclose(fp);
    fclose(outFile_p);
    fsecs=t2 - t1;
    printf("\n###########SCANNING ANALYSIS###################\n");
    printf("\nTOTAL LINES ANALYZED: %d\n", line_count);
    printf("\nTOTAL TIMES TO SCAN :%.6lf seconds\n", fsecs);
    printf("\nSCANNED LINES PER SECOND:%d\n", (int)(line_count/fsecs));
    printf("\n################################################\n");
    return 0;
  }

