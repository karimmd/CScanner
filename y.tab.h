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

/* Line 2068 of yacc.c  */
#line 76 "y.y"

int number;
char *string;



/* Line 2068 of yacc.c  */
#line 139 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


