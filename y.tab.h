/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     STRCPY = 258,
     STRCAT = 259,
     GETS = 260,
     SPRINTF = 261,
     VSPRINTF = 262,
     BCOPY = 263,
     SCANF = 264,
     TAB = 265,
     EOL = 266,
     SIMICOL = 267,
     COM = 268,
     PERCENT = 269,
     GETOPT = 270,
     GETPASS = 271,
     STRECPY = 272,
     STREADD = 273,
     STRNCPY = 274,
     STRTRNS = 275,
     STRPCPY = 276,
     WCSCPY = 277,
     WCPCPY = 278,
     WCSCAT = 279,
     GETWD = 280,
     REALPATH = 281,
     MEMCPY = 282,
     MEMCHR = 283,
     MEMCCPY = 284,
     MEMMOVE = 285,
     MEMSET = 286,
     CHAR = 287,
     NEW = 288,
     LBRAK = 289,
     RBRAK = 290,
     ANY = 291,
     PLUS = 292,
     NUMBER = 293,
     MUL = 294,
     TCOM = 295,
     WORD = 296,
     LB = 297,
     RB = 298,
     WHITE = 299
   };
#endif
/* Tokens.  */
#define STRCPY 258
#define STRCAT 259
#define GETS 260
#define SPRINTF 261
#define VSPRINTF 262
#define BCOPY 263
#define SCANF 264
#define TAB 265
#define EOL 266
#define SIMICOL 267
#define COM 268
#define PERCENT 269
#define GETOPT 270
#define GETPASS 271
#define STRECPY 272
#define STREADD 273
#define STRNCPY 274
#define STRTRNS 275
#define STRPCPY 276
#define WCSCPY 277
#define WCPCPY 278
#define WCSCAT 279
#define GETWD 280
#define REALPATH 281
#define MEMCPY 282
#define MEMCHR 283
#define MEMCCPY 284
#define MEMMOVE 285
#define MEMSET 286
#define CHAR 287
#define NEW 288
#define LBRAK 289
#define RBRAK 290
#define ANY 291
#define PLUS 292
#define NUMBER 293
#define MUL 294
#define TCOM 295
#define WORD 296
#define LB 297
#define RB 298
#define WHITE 299




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 66 "y.y"

int number;
char *string;



/* Line 2068 of yacc.c  */
#line 145 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


