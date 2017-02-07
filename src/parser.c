/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include "def.h"

#define YYSTYPE pnode
extern char *yytext;
extern Value lexval;
extern int line;
extern FILE *yyin;
extern pnode root;
int yylex();
void yyerror();

#line 79 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ASSIGN = 258,
    EQUAL = 259,
    NE = 260,
    GT = 261,
    GE = 262,
    KT = 263,
    KE = 264,
    PLUS = 265,
    MINUS = 266,
    MUL = 267,
    DIV = 268,
    PROGRAM = 269,
    TYPE = 270,
    VAR = 271,
    CONST = 272,
    PROC = 273,
    FUNC = 274,
    IN = 275,
    OUT = 276,
    INOUT = 277,
    T_BEGIN = 278,
    END = 279,
    BREAK = 280,
    EXIT = 281,
    IF = 282,
    THEN = 283,
    ELSE = 284,
    ELSIF = 285,
    WHILE = 286,
    DO = 287,
    REPEAT = 288,
    UNTIL = 289,
    FOR = 290,
    TO = 291,
    INPUT = 292,
    OUTPUT = 293,
    AND = 294,
    OR = 295,
    NOT = 296,
    INTEGER = 297,
    STRING = 298,
    BOOLEAN = 299,
    INTCONST = 300,
    BOOLCONST = 301,
    STRCONST = 302,
    ID = 303,
    ERROR = 304,
    ARRAY = 305,
    OF = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 182 "parser.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  223

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      58,    59,     2,     2,    55,     2,    52,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    54,    53,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    56,     2,    57,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    67,    67,    67,    83,    84,    87,    88,    91,    94,
      94,    95,    98,    99,   100,   103,   104,   105,   108,   108,
     111,   112,   115,   116,   119,   120,   123,   126,   127,   128,
     129,   132,   135,   136,   139,   140,   143,   144,   147,   148,
     151,   151,   161,   161,   170,   171,   174,   175,   178,   181,
     182,   183,   186,   186,   186,   192,   192,   192,   198,   199,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     214,   217,   220,   220,   227,   230,   238,   246,   247,   250,
     251,   254,   257,   258,   261,   264,   265,   268,   269,   272,
     273,   276,   277,   278,   279,   280,   281,   284,   285,   288,
     289,   292,   293,   296,   297,   300,   301,   302,   303,   304,
     305,   308,   309,   312,   318,   319,   322,   322,   325,   326,
     329,   330
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ASSIGN", "EQUAL", "NE", "GT", "GE",
  "KT", "KE", "PLUS", "MINUS", "MUL", "DIV", "PROGRAM", "TYPE", "VAR",
  "CONST", "PROC", "FUNC", "IN", "OUT", "INOUT", "T_BEGIN", "END", "BREAK",
  "EXIT", "IF", "THEN", "ELSE", "ELSIF", "WHILE", "DO", "REPEAT", "UNTIL",
  "FOR", "TO", "INPUT", "OUTPUT", "AND", "OR", "NOT", "INTEGER", "STRING",
  "BOOLEAN", "INTCONST", "BOOLCONST", "STRCONST", "ID", "ERROR", "ARRAY",
  "OF", "'.'", "';'", "':'", "','", "'['", "']'", "'('", "')'", "$accept",
  "program", "@1", "opt-type-sect", "decl-list", "decl", "id-list", "@2",
  "domain", "atomic-domain", "array-domain", "@3", "opt-var-sect",
  "opt-const-sect", "const-list-decl", "const-decl", "const",
  "array-const", "const-list", "opt-module-list", "module-list",
  "module-decl", "procedure-decl", "@4", "function-decl", "@5",
  "opt-formal-list", "formal-list", "formal-decl", "mode", "stat-body",
  "@6", "@7", "expr-body", "@8", "@9", "stat-list", "stat", "input-stat",
  "output-stat", "for-stat", "@10", "while-stat", "repeat-stat", "if-stat",
  "opt-elsif-stat-list", "opt-else-stat", "assign-stat", "left-hand-side",
  "indexing", "expr", "bool-op", "bool-term", "comp-op", "comp-term",
  "add-op", "term", "mul-op", "factor", "unary-op", "cond-expr",
  "opt-elsif-expr-list", "module-call", "@11", "opt-expr-list",
  "expr-list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,    46,    59,    58,    44,    91,    93,    40,    41
};
# endif

#define YYPACT_NINF -161

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-161)))

#define YYTABLE_NINF -117

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,   -25,    29,  -161,  -161,    16,   -15,    26,    -6,  -161,
       1,    34,   -15,    66,    15,   -15,    80,  -161,   -15,    60,
     -15,  -161,  -161,  -161,  -161,  -161,    25,  -161,  -161,  -161,
      97,  -161,   -15,    57,    67,   134,  -161,    60,  -161,  -161,
    -161,    75,    28,  -161,  -161,  -161,    83,   112,  -161,  -161,
    -161,  -161,  -161,    28,   113,  -161,   107,   109,  -161,  -161,
     111,   114,   115,  -161,   -10,   -10,    64,   119,    28,  -161,
    -161,  -161,   116,  -161,   118,   -15,   117,  -161,  -161,    -1,
      -1,    64,   123,   126,    -1,   122,   153,   125,  -161,  -161,
    -161,  -161,  -161,  -161,  -161,     2,  -161,  -161,    80,  -161,
      16,   120,  -161,   127,  -161,    -1,  -161,    -1,  -161,   128,
      -3,  -161,   145,   146,  -161,    -1,  -161,  -161,   106,   148,
    -161,  -161,   121,   129,   131,    64,    -1,    -1,  -161,    26,
    -161,    80,    68,   -18,    64,  -161,  -161,    -1,  -161,  -161,
    -161,  -161,  -161,  -161,  -161,  -161,    -1,    -1,  -161,  -161,
      -1,  -161,    64,    -1,   180,    -1,  -161,  -161,   121,    -5,
      66,    16,    -1,  -161,   155,  -161,   152,   146,  -161,   162,
     121,    -1,    27,   130,  -161,  -161,  -161,    60,    66,    74,
      -1,   159,  -161,    96,    -1,  -161,   134,    60,    -1,   161,
      70,    64,   167,    -1,  -161,   139,   170,    78,    -1,    64,
    -161,  -161,   108,  -161,   147,   141,    -1,    32,   155,    64,
    -161,  -161,    74,  -161,  -161,   172,    -1,  -161,  -161,    53,
     149,  -161,  -161
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     5,     0,    21,     9,     4,
       0,     0,     0,    23,     0,     7,     0,    20,     0,    35,
       0,     6,    15,    16,    17,    14,     0,     8,    12,    13,
       0,    22,    25,     0,     0,     0,    34,    37,    38,    39,
      10,     0,     0,    24,    40,    42,     0,     0,    36,    18,
      27,    29,    28,     0,     0,    30,     0,     0,    52,     3,
       0,    33,     0,    26,    45,    45,     0,     0,     0,    31,
      50,    51,     0,    44,    47,     0,     0,    68,    69,     0,
       0,     0,     0,     0,     0,    82,     0,     0,    65,    66,
      64,    62,    63,    61,    60,     0,    83,    67,     0,    32,
       5,    49,    48,     0,   111,     0,   112,     0,   108,   107,
       0,    86,    90,    98,   102,     0,   109,   110,     0,     0,
      72,    70,    71,     0,     0,    59,     0,     0,    19,    21,
      46,     0,     0,     0,     0,    87,    88,     0,    91,    92,
      93,    94,    95,    96,    99,   100,     0,     0,   103,   104,
       0,   105,     0,     0,     0,   119,    53,    58,    81,     0,
      23,     5,     0,   106,    78,    85,    89,    97,   101,     0,
      75,     0,   121,     0,   118,    54,    84,    35,    23,   115,
       0,    80,    74,     0,     0,   117,     0,    35,     0,     0,
       0,     0,     0,     0,   120,     0,     0,     0,     0,     0,
      79,    76,     0,    41,     0,     0,     0,     0,    78,     0,
      55,    43,   115,   113,    77,     0,     0,   114,    73,     0,
       0,    56,    57
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -161,  -161,  -161,   -96,    49,   -12,   178,  -161,   -80,  -161,
    -161,  -161,    71,  -146,   169,  -161,   -29,  -161,   135,  -160,
     165,  -161,  -161,  -161,  -161,  -161,   140,    98,  -161,  -161,
      18,  -161,  -161,  -161,  -161,  -161,   -72,  -161,  -161,  -161,
    -161,  -161,  -161,  -161,  -161,    -2,  -161,  -161,   -66,  -161,
     -77,  -161,    72,  -161,    61,  -161,    63,  -161,  -107,  -161,
    -161,    -4,   -65,  -161,  -161,    30
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,     7,     9,    10,    11,    14,    27,    28,
      29,    60,    13,    19,    31,    32,   108,    55,    62,    35,
      36,    37,    38,    56,    39,    57,    72,    73,    74,    75,
      47,    66,   175,   205,   216,   222,    86,    87,    88,    89,
      90,   154,    91,    92,    93,   181,   192,    94,   109,    96,
     172,   137,   111,   146,   112,   147,   113,   150,   114,   115,
     116,   189,   117,   123,   173,   174
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      95,    97,   110,   118,   129,   126,    30,   122,   151,   119,
     104,    70,    71,    54,   177,    95,    97,   186,   128,     1,
      30,   135,   136,     3,    61,   134,   105,   196,   132,     4,
     133,     6,   187,     8,   135,   136,   135,   136,   -49,    61,
     106,   163,    12,   168,    50,    51,    52,    85,   -11,   158,
     159,   161,   176,   157,    15,    53,   213,   107,   127,    95,
      97,    17,   164,   102,    21,   178,   135,   136,    95,    97,
      20,   135,   136,    50,    51,    52,   170,   220,    33,    34,
     169,    41,   184,    18,    53,   179,    95,    97,    16,    77,
      78,    79,   135,   136,   183,    80,   162,    81,   199,    82,
      42,    83,    84,   190,   188,    44,   206,   135,   136,   135,
     136,   197,    85,   135,   136,    45,   202,   135,   136,   200,
      49,   207,    22,    23,    24,    95,    97,   208,    25,   212,
      26,    58,   193,    95,    97,   135,   136,   215,   152,   219,
     209,    70,    71,    95,    97,   135,   136,   135,   136,   138,
     139,   140,   141,   142,   143,   144,   145,    46,   148,   149,
     135,   136,   144,   145,    59,    64,    63,    65,    67,    68,
      98,   120,    69,   101,   121,   100,   103,   124,   125,   156,
    -116,   131,   153,   171,   127,   180,   182,   155,   191,   185,
     198,   201,   203,   204,   211,   210,   218,   221,    40,   130,
     160,    43,    48,    99,   195,    76,   214,   166,   217,   165,
     167,     0,     0,     0,   194
};

static const yytype_int16 yycheck[] =
{
      66,    66,    79,    80,   100,     3,    18,    84,   115,    81,
      11,    21,    22,    42,   160,    81,    81,   177,    98,    14,
      32,    39,    40,    48,    53,    28,    27,   187,   105,     0,
     107,    15,   178,    48,    39,    40,    39,    40,    48,    68,
      41,    59,    16,   150,    45,    46,    47,    48,    54,   126,
     127,   131,    57,   125,    53,    56,    24,    58,    56,   125,
     125,    12,   134,    75,    15,   161,    39,    40,   134,   134,
      55,    39,    40,    45,    46,    47,   153,    24,    18,    19,
     152,    56,    55,    17,    56,   162,   152,   152,    54,    25,
      26,    27,    39,    40,   171,    31,    28,    33,    28,    35,
       3,    37,    38,   180,    30,    48,    28,    39,    40,    39,
      40,   188,    48,    39,    40,    48,   193,    39,    40,   191,
      45,   198,    42,    43,    44,   191,   191,   199,    48,   206,
      50,    48,    36,   199,   199,    39,    40,   209,    32,   216,
      32,    21,    22,   209,   209,    39,    40,    39,    40,     4,
       5,     6,     7,     8,     9,    10,    11,    23,    12,    13,
      39,    40,    10,    11,    52,    58,    53,    58,    57,    55,
      51,    48,    57,    55,    48,    59,    59,    24,    53,    48,
      58,    54,    34,     3,    56,    30,    24,    58,    29,    59,
      29,    24,    53,    23,    53,    48,    24,    48,    20,   101,
     129,    32,    37,    68,   186,    65,   208,   146,   212,   137,
     147,    -1,    -1,    -1,   184
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    61,    48,     0,    62,    15,    63,    48,    64,
      65,    66,    16,    72,    67,    53,    54,    64,    17,    73,
      55,    64,    42,    43,    44,    48,    50,    68,    69,    70,
      65,    74,    75,    18,    19,    79,    80,    81,    82,    84,
      66,    56,     3,    74,    48,    48,    23,    90,    80,    45,
      45,    46,    47,    56,    76,    77,    83,    85,    48,    52,
      71,    76,    78,    53,    58,    58,    91,    57,    55,    57,
      21,    22,    86,    87,    88,    89,    86,    25,    26,    27,
      31,    33,    35,    37,    38,    48,    96,    97,    98,    99,
     100,   102,   103,   104,   107,   108,   109,   122,    51,    78,
      59,    55,    65,    59,    11,    27,    41,    58,    76,   108,
     110,   112,   114,   116,   118,   119,   120,   122,   110,    96,
      48,    48,   110,   123,    24,    53,     3,    56,    68,    63,
      87,    54,   110,   110,    28,    39,    40,   111,     4,     5,
       6,     7,     8,     9,    10,    11,   113,   115,    12,    13,
     117,   118,    32,    34,   101,    58,    48,    96,   110,   110,
      72,    68,    28,    59,    96,   112,   114,   116,   118,    96,
     110,     3,   110,   124,   125,    92,    57,    73,    63,   110,
      30,   105,    24,   110,    55,    59,    79,    73,    30,   121,
     110,    29,   106,    36,   125,    90,    79,   110,    29,    28,
      96,    24,   110,    53,    23,    93,    28,   110,    96,    32,
      48,    53,   110,    24,   105,    96,    94,   121,    24,   110,
      24,    48,    95
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    62,    61,    63,    63,    64,    64,    65,    67,
      66,    66,    68,    68,    68,    69,    69,    69,    71,    70,
      72,    72,    73,    73,    74,    74,    75,    76,    76,    76,
      76,    77,    78,    78,    79,    79,    80,    80,    81,    81,
      83,    82,    85,    84,    86,    86,    87,    87,    88,    89,
      89,    89,    91,    92,    90,    94,    95,    93,    96,    96,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      98,    99,   101,   100,   102,   103,   104,   105,   105,   106,
     106,   107,   108,   108,   109,   110,   110,   111,   111,   112,
     112,   113,   113,   113,   113,   113,   113,   114,   114,   115,
     115,   116,   116,   117,   117,   118,   118,   118,   118,   118,
     118,   119,   119,   120,   121,   121,   123,   122,   124,   124,
     125,   125
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     2,     0,     3,     2,     3,     0,
       4,     1,     1,     1,     1,     1,     1,     1,     0,     7,
       2,     0,     2,     0,     2,     1,     4,     1,     1,     1,
       1,     3,     3,     1,     1,     0,     2,     1,     1,     1,
       0,    12,     0,    13,     1,     0,     3,     1,     2,     0,
       1,     1,     0,     0,     7,     0,     0,     7,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     0,    10,     5,     4,     7,     5,     0,     2,
       0,     3,     1,     1,     4,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     2,     3,     1,     1,     1,
       1,     1,     1,     8,     5,     0,     0,     5,     1,     0,
       3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
      yychar = yylex ();
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 67 "parser.y" /* yacc.c:1646  */
    {(yyval) = idnode();}
#line 1431 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 73 "parser.y" /* yacc.c:1646  */
    {root=(yyval)=nontermnode(N_PROGRAM); 
                     (yyval)->child=(yyvsp[-6]); 
                     (yyvsp[-6])->brother=(yyvsp[-5]);
                     (yyvsp[-5])->brother=(yyvsp[-4]);
                     (yyvsp[-4])->brother=(yyvsp[-3]);
                     (yyvsp[-3])->brother=(yyvsp[-2]);
                     (yyvsp[-2])->brother=(yyvsp[-1]);
                    }
#line 1444 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 83 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_OPTTYPESECT);(yyval)->child=(yyvsp[0]);}
#line 1450 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 84 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_OPTTYPESECT);}
#line 1456 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 87 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-2]); (yyvsp[-2])->brother=(yyvsp[0]);}
#line 1462 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 88 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 1468 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 91 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_DECL);(yyval)->child=nontermnode(N_IDLIST);(yyval)->child->brother=(yyvsp[0]);(yyval)->child->child=(yyvsp[-2]);}
#line 1474 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 94 "parser.y" /* yacc.c:1646  */
    {(yyval) = idnode();}
#line 1480 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 94 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-2]);(yyvsp[-2])->brother=(yyvsp[0]);}
#line 1486 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 95 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0])=idnode();(yyval)=(yyvsp[0]);}
#line 1492 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 98 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_DOMAIN);(yyval)->child=(yyvsp[0]);}
#line 1498 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 99 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_DOMAIN);(yyval)->child=(yyvsp[0]);}
#line 1504 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 100 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_DOMAIN);(yyvsp[0])=idnode();(yyval)->child=(yyvsp[0]);}
#line 1510 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 103 "parser.y" /* yacc.c:1646  */
    {(yyval)=atomicnode(D_INTEGER);}
#line 1516 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 104 "parser.y" /* yacc.c:1646  */
    {(yyval)=atomicnode(D_STRING);}
#line 1522 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 105 "parser.y" /* yacc.c:1646  */
    {(yyval)=atomicnode(D_BOOLEAN);}
#line 1528 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 108 "parser.y" /* yacc.c:1646  */
    {(yyval)=intconstnode();}
#line 1534 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 108 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_ARRAYDOMAIN);(yyval)->child=(yyvsp[-3]);(yyval)->child->brother=(yyvsp[0]);}
#line 1540 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 111 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_OPTVARSECT);(yyval)->child=(yyvsp[0]);}
#line 1546 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 112 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_OPTVARSECT);}
#line 1552 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 115 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_OPTCONSTSECT);(yyval)->child=(yyvsp[0]);}
#line 1558 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 116 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_OPTCONSTSECT);}
#line 1564 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 119 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);(yyvsp[-1])->brother->brother=(yyvsp[0]);}
#line 1570 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 120 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1576 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 123 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-3]);(yyvsp[-3])->brother=(yyvsp[-1]);}
#line 1582 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 126 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_CONST);(yyval)->child=intconstnode();}
#line 1588 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 127 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_CONST);(yyval)->child=strconstnode();}
#line 1594 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 128 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_CONST);(yyval)->child=boolconstnode();}
#line 1600 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 129 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_CONST);(yyval)->child=nontermnode(N_ARRAYCONST);(yyval)->child->child=(yyvsp[0]);}
#line 1606 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 132 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 1612 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 135 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-2]);(yyvsp[-2])->brother=(yyvsp[0]);}
#line 1618 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 136 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1624 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 139 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_OPTMODULELIST);(yyval)->child=(yyvsp[0]);}
#line 1630 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 140 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_OPTMODULELIST);}
#line 1636 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 143 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);(yyvsp[-1])->brother=(yyvsp[0]);}
#line 1642 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 144 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1648 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 147 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1654 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 148 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1660 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 151 "parser.y" /* yacc.c:1646  */
    {(yyval)=idnode();}
#line 1666 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 152 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_PROCDECL);(yyval)->child=(yyvsp[-9]);(yyvsp[-9])->brother=(yyvsp[-7]);//$5 opt-formal-list
                        (yyvsp[-7])->brother=(yyvsp[-5]);//$7=opt-type-sect
                        (yyvsp[-5])->brother=(yyvsp[-4]);//$8=opt-var-sect
                        (yyvsp[-4])->brother=(yyvsp[-3]);//$9=opt-const-sect
                        (yyvsp[-3])->brother=(yyvsp[-2]);//$10=opt-module-list
                        (yyvsp[-2])->brother=(yyvsp[-1]);//$11=stat-body
                        }
#line 1678 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 161 "parser.y" /* yacc.c:1646  */
    {(yyval)=idnode();}
#line 1684 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 162 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_FUNCDECL);(yyval)->child=(yyvsp[-10]);(yyvsp[-10])->brother=(yyvsp[-8]);//$5 opt-formal-list
                         (yyvsp[-8])->brother=(yyvsp[-5]);//$8=domain
                         (yyvsp[-5])->brother=(yyvsp[-4]);//$9=opt-type-sect
                         (yyvsp[-4])->brother=(yyvsp[-3]);//$10=opt-const-sect
                         (yyvsp[-3])->brother=(yyvsp[-2]);//$11=opt-module-list
                         (yyvsp[-2])->brother=(yyvsp[-1]);}
#line 1695 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 170 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_OPTFORMALLIST);(yyval)->child=(yyvsp[0]);}
#line 1701 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 171 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_OPTFORMALLIST);}
#line 1707 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 174 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-2]);(yyvsp[-2])->brother=(yyvsp[0]);}
#line 1713 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 175 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1719 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 178 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_FORMALDECL);(yyval)->child=(yyvsp[-1]);(yyvsp[-1])->brother=(yyvsp[0]);}
#line 1725 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 181 "parser.y" /* yacc.c:1646  */
    {(yyval) = modenode(M_IN);}
#line 1731 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 182 "parser.y" /* yacc.c:1646  */
    {(yyval) = modenode(M_OUT);}
#line 1737 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 183 "parser.y" /* yacc.c:1646  */
    {(yyval) = modenode(M_INOUT);}
#line 1743 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 186 "parser.y" /* yacc.c:1646  */
    {(yyval)=idnode();}
#line 1749 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 186 "parser.y" /* yacc.c:1646  */
    {(yyval)=idnode();}
#line 1755 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 187 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STATBODY);(yyval)->child=(yyvsp[-4]);(yyvsp[-4])->brother=nontermnode(N_STATLIST);(yyvsp[-4])->brother->child=(yyvsp[-3]);(yyvsp[-4])->brother->brother=(yyvsp[0]);
                            if((yyvsp[-4])->val.sval != (yyvsp[0])->val.sval){printError((yyvsp[-4])->val.sval);}
                        }
#line 1763 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 192 "parser.y" /* yacc.c:1646  */
    {(yyval)=idnode();}
#line 1769 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 192 "parser.y" /* yacc.c:1646  */
    {(yyval)=idnode();}
#line 1775 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 193 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_EXPRBODY);(yyval)->child=(yyvsp[-4]);(yyvsp[-4])->brother=(yyvsp[-3]);(yyvsp[-4])->brother->brother=(yyvsp[0]);
                            if((yyvsp[-4])->val.sval != (yyvsp[0])->val.sval){printError((yyvsp[-4])->val.sval);}
                        }
#line 1783 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 198 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-2]);(yyvsp[-2])->brother=(yyvsp[0]);}
#line 1789 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 199 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 1795 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 202 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STAT);(yyval)->child=(yyvsp[0]);}
#line 1801 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 203 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STAT);(yyval)->child=(yyvsp[0]);}
#line 1807 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 204 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STAT);(yyval)->child=(yyvsp[0]);}
#line 1813 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 205 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STAT);(yyval)->child=(yyvsp[0]);}
#line 1819 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 206 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STAT);(yyval)->child=(yyvsp[0]);}
#line 1825 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 207 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STAT);(yyval)->child=(yyvsp[0]);}
#line 1831 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 208 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STAT);(yyval)->child=(yyvsp[0]);}
#line 1837 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 209 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STAT);(yyval)->child=(yyvsp[0]);(yyvsp[0])->val.ival=E_PROC;}
#line 1843 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 210 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STAT);(yyvsp[0])=newnode(T_BREAK);(yyval)->child=(yyvsp[0]);}
#line 1849 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 211 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STAT);(yyvsp[0])=newnode(T_EXIT);(yyval)->child=(yyvsp[0]);}
#line 1855 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 214 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_INPUTSTAT);(yyvsp[0])=idnode();(yyval)->child=(yyvsp[0]);}
#line 1861 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 217 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_OUTPUTSTAT);(yyval)->child=(yyvsp[0]);}
#line 1867 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 220 "parser.y" /* yacc.c:1646  */
    {(yyval)=idnode();}
#line 1873 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 221 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_FORSTAT);
                     (yyval)->child=(yyvsp[-7]); (yyvsp[-7])->brother=(yyvsp[-5]);(yyvsp[-5])->brother=(yyvsp[-3]);(yyvsp[-3])->brother=nontermnode(N_STATLIST);
                     (yyvsp[-3])->brother->child=(yyvsp[-1]);
                    }
#line 1882 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_WHILESTAT);(yyval)->child=(yyvsp[-3]);(yyvsp[-3])->brother=nontermnode(N_STATLIST);(yyvsp[-3])->brother->child=(yyvsp[-1]);}
#line 1888 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 231 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_REPEATSTAT);
                     (yyval)->child=nontermnode(N_STATLIST);
                     (yyval)->child->child=(yyvsp[-2]); 
                     (yyval)->child->brother=(yyvsp[0]);
                    }
#line 1898 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 239 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_IFSTAT);(yyval)->child=(yyvsp[-5]);(yyvsp[-5])->brother=nontermnode(N_STATLIST);
                    (yyvsp[-5])->brother->child = (yyvsp[-3]);
                    (yyvsp[-5])->brother->brother=nontermnode(N_OPTELSEIFSTAT);
                    (yyvsp[-5])->brother->brother->brother=(yyvsp[-1]);
                    (yyvsp[-5])->brother->brother->child=(yyvsp[-2]);}
#line 1908 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 246 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-3]);(yyvsp[-3])->brother=nontermnode(N_STATLIST);(yyvsp[-3])->brother->child=(yyvsp[-1]);(yyvsp[-3])->brother->brother=(yyvsp[0]);}
#line 1914 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 247 "parser.y" /* yacc.c:1646  */
    {(yyval)=NULL;}
#line 1920 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 250 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_STATLIST);(yyval)->child=(yyvsp[0]);}
#line 1926 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 251 "parser.y" /* yacc.c:1646  */
    {(yyval)=NULL;}
#line 1932 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 254 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_ASSIGNSTAT);(yyval)->child=(yyvsp[-2]);(yyvsp[-2])->brother=(yyvsp[0]);}
#line 1938 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 257 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_LHS);(yyvsp[0])=idnode();(yyval)->child=(yyvsp[0]);}
#line 1944 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 258 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_LHS);(yyval)->child=(yyvsp[0]);}
#line 1950 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 261 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_INDEXING);(yyval)->child=(yyvsp[-3]);(yyvsp[-3])->brother=(yyvsp[-1]);}
#line 1956 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 264 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);(yyvsp[-1])->child=(yyvsp[-2]);(yyvsp[-2])->brother=(yyvsp[0]);}
#line 1962 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 265 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1968 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 268 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_LOGICEXPR,E_AND);}
#line 1974 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 269 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_LOGICEXPR,E_OR);}
#line 1980 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 272 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);(yyvsp[-2])->brother=(yyvsp[0]);(yyvsp[-1])->child=(yyvsp[-2]);}
#line 1986 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 273 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1992 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 276 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_COMPEXPR,E_EQ);}
#line 1998 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 277 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_COMPEXPR,E_NE);}
#line 2004 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 278 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_COMPEXPR,E_GT);}
#line 2010 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 279 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_COMPEXPR,E_GE);}
#line 2016 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 280 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_COMPEXPR,E_LT);}
#line 2022 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 281 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_COMPEXPR,E_LE);}
#line 2028 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 284 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);(yyvsp[-1])->child=(yyvsp[-2]);(yyvsp[-2])->brother=(yyvsp[0]);}
#line 2034 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 285 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2040 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 288 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_MATHEXPR,E_PLUS);}
#line 2046 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 289 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_MATHEXPR,E_MINUS);}
#line 2052 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 292 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);(yyvsp[-1])->child=(yyvsp[-2]);(yyvsp[-2])->brother=(yyvsp[0]);}
#line 2058 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 293 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2064 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 296 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_MATHEXPR,E_MUL);}
#line 2070 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 297 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_MATHEXPR,E_DIV);}
#line 2076 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 300 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);(yyvsp[-1])->child=(yyvsp[0]);}
#line 2082 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 301 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 2088 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 302 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2094 "parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 303 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2100 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 304 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2106 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 305 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);(yyvsp[0])->val.ival=E_FUNC;}
#line 2112 "parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 308 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_NEGEXPR,E_UMINUS);}
#line 2118 "parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 309 "parser.y" /* yacc.c:1646  */
    {(yyval)=exprnode(T_NEGEXPR,E_NOT);}
#line 2124 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 313 "parser.y" /* yacc.c:1646  */
    {(yyval)=nontermnode(N_CONDEXPR);(yyval)->child=(yyvsp[-6]);(yyvsp[-6])->brother=(yyvsp[-4]);
                    (yyvsp[-4])->brother=nontermnode(N_OPTELSEIFEXPR);(yyvsp[-4])->brother->brother=(yyvsp[-1]);
                    (yyvsp[-4])->brother->child=(yyvsp[-3]);}
#line 2132 "parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 318 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-3]);(yyvsp[-3])->brother=(yyvsp[-1]);(yyvsp[-1])->brother=(yyvsp[0]);}
#line 2138 "parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 319 "parser.y" /* yacc.c:1646  */
    {(yyval)=NULL;}
#line 2144 "parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 322 "parser.y" /* yacc.c:1646  */
    {(yyval)=idnode();}
#line 2150 "parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 322 "parser.y" /* yacc.c:1646  */
    {(yyval)=newnode(T_MODCALL);(yyval)->child=(yyvsp[-3]);(yyvsp[-3])->brother=(yyvsp[-1]);}
#line 2156 "parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 325 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2162 "parser.c" /* yacc.c:1646  */
    break;

  case 119:
#line 326 "parser.y" /* yacc.c:1646  */
    {(yyval)=NULL;}
#line 2168 "parser.c" /* yacc.c:1646  */
    break;

  case 120:
#line 329 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-2]);(yyvsp[-2])->brother=(yyvsp[0]);}
#line 2174 "parser.c" /* yacc.c:1646  */
    break;

  case 121:
#line 330 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2180 "parser.c" /* yacc.c:1646  */
    break;


#line 2184 "parser.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 333 "parser.y" /* yacc.c:1906  */


void yyerror(){
    fprintf(stderr, "Errore sul simbolo '%s' alla linea %d\n\n",yytext,line);
}
