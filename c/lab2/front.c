/* front.c - a lexical analyzer system for simple
             arithmetic expressions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp; /*, *fopen(); */
/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define QUOTE 2
#define UNKNOWN 99

/* Token codes */
#define STR_LIT 8
#define INT_LIT 10
#define FLOAT_LIT 9
#define IDENT 11
#define LT_OP 18
#define RT_OP 19
#define EQUALS_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LTEQ_OP 27
#define RTEQ_OP 28
#define NOTEQ_OP 29
#define PRINT 30
#define IF 31
#define THEN 32
#define GOTO 33
#define GOSUB 34
#define INPUT 35
#define LET 36
#define RETURN 37
#define CLEAR 38
#define LIST 39
#define COMMA 40
#define RUN 41
#define END 42

/******************************************************/
/* main driver */
int main()
{
  /* Open the input data file and process its contents */
  if ((in_fp = fopen("front.in", "r")) == NULL)
    printf("ERROR - cannot open front.in \n");
  else
  {
    getChar();
    do
    {
      lex();
    } while (nextToken != EOF);
  }
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses
            and return the token */

int lookup(char ch)
{
  switch (ch)
  {
  case '(':
    addChar();
    nextToken = LEFT_PAREN;
    break;

  case ')':
    addChar();
    nextToken = RIGHT_PAREN;
    break;

  case '+':
    addChar();
    nextToken = ADD_OP;
    break;

  case '-':
    addChar();
    nextToken = SUB_OP;
    break;

  case '*':
    addChar();
    nextToken = MULT_OP;
    break;

  case '/':
    addChar();
    nextToken = DIV_OP;
    break;

  case '=':
    addChar();
    nextToken = EQUALS_OP;
    break;

  case '<':
    addChar();
    getChar();
    if (nextChar == '=') {
      addChar();
      nextToken = LTEQ_OP;
      return nextToken;  // Don't call getChar again
    } else if (nextChar == '>') {
      addChar();
      nextToken = NOTEQ_OP;
      return nextToken;  // Don't call getChar again
    } else {
      nextToken = LT_OP;
      return nextToken;  // nextChar already contains next character
    }
    break;

  case '>':
    addChar();
    getChar();
    if (nextChar == '=') {
      addChar();
      nextToken = RTEQ_OP;
      return nextToken;  // Don't call getChar again
    } else if (nextChar == '<') {
      addChar();
      nextToken = NOTEQ_OP;
      return nextToken;  // Don't call getChar again
    } else {
      nextToken = RT_OP;
      return nextToken;  // nextChar already contains next character
    }
    break;

  case ',':
    addChar();
    nextToken = COMMA;
    break;

  default:
    addChar();
    printf("ERROR: Illegal symbol found: '%c' (ASCII %d) in lexeme: %s\n", 
           nextChar, (int)nextChar, lexeme);
    nextToken = UNKNOWN;
    return nextToken;
    break;
  }
  return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar()
{
  if (lexLen <= 98)
  {
    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = 0;
  }
  else
    printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
             input and determine its character class */
void getChar()
{
  int c = getc(in_fp);
  if (c == EOF)
  {
    charClass = EOF;
    nextChar = 0;
  }
  else
  {
    nextChar = (char)c;
    if (isalpha((unsigned char)nextChar))
      charClass = LETTER;
    else if (isdigit((unsigned char)nextChar))
      charClass = DIGIT;
    else if (nextChar == '"')
      charClass = QUOTE;
    else
      charClass = UNKNOWN;
  }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it
                 returns a non-whitespace character */
void getNonBlank()
{
  while (isspace(nextChar))
    getChar();
}

/* examines current lexeme and returns specific token or IDENT if it's not a keyword */
int keywordLookup() {
  // Keywords are case-insensitive in BASIC, so convert to uppercase for comparison
  char upper[100];
  int i;
  for (i = 0; i < lexLen && i < 99; i++) {
    upper[i] = toupper(lexeme[i]);
  }
  upper[i] = '\0';
  
  // Check all Tiny BASIC keywords
  if (strcmp(upper, "PRINT") == 0)
    return PRINT;
  else if (strcmp(upper, "INPUT") == 0)
    return INPUT;
  else if (strcmp(upper, "IF") == 0)
    return IF;
  else if (strcmp(upper, "THEN") == 0)
    return THEN;
  else if (strcmp(upper, "GOTO") == 0)
    return GOTO;
  else if (strcmp(upper, "GOSUB") == 0)
    return GOSUB;
  else if (strcmp(upper, "LET") == 0)
    return LET;
  else if (strcmp(upper, "RETURN") == 0)
    return RETURN;
  else if (strcmp(upper, "CLEAR") == 0)
    return CLEAR;
  else if (strcmp(upper, "LIST") == 0)
    return LIST;
  else if (strcmp(upper, "RUN") == 0)
    return RUN;
  else if (strcmp(upper, "END") == 0)
    return END;
  else {
    // Not a keyword - check if it's a valid single-letter variable
    // Tiny BASIC only allows single-letter variables (A-Z)
    if (lexLen == 1 && isalpha(lexeme[0])) {
      return IDENT;
    } else {
      printf("ERROR: Invalid identifier '%s' - Tiny BASIC only allows single-letter variables (A-Z)\n", lexeme);
      return IDENT;  // Return IDENT but we've warned the user
    }
  }
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
         expressions 
   // depends on charClass and nextChar already being set by the caller
         */
int lex()
{
  lexLen = 0;
  getNonBlank();
  switch (charClass)
  {
    /* Parse identifiers */
  case LETTER:
    addChar();
    getChar();
    while (charClass == LETTER || charClass == DIGIT)
    {
      addChar();
      getChar();
    }
    nextToken = keywordLookup();
    break;

    /* Parse integer literals */
  case DIGIT:
    addChar();
    getChar();
    while (charClass == DIGIT)
    {
      addChar();
      getChar();
    }
    nextToken = INT_LIT;
    break;

  case QUOTE:
    addChar();
    getChar();
    while (charClass != QUOTE && charClass != EOF && nextChar != '\n')
    {
      addChar(); 
      getChar();
    }
    if (charClass == QUOTE) {
      addChar();
      getChar();
      nextToken = STR_LIT;
    } else {
      printf("ERROR: Unterminated string literal\n");
      nextToken = STR_LIT;  // Return string token anyway
    }
    break;

    /* Parentheses and operators */
  case UNKNOWN:
    lookup(nextChar);
    // For < and >, lookup() checks for compound operators and calls getChar() if needed
    // For other operators, we need to call getChar() ourselves
    if (nextToken != LT_OP && nextToken != RT_OP && 
        nextToken != LTEQ_OP && nextToken != RTEQ_OP && 
        nextToken != NOTEQ_OP) {
      getChar();
    }
    break;

    /* EOF */
  case EOF:
    nextToken = EOF;
    lexeme[0] = 'E';
    lexeme[1] = 'O';
    lexeme[2] = 'F';
    lexeme[3] = 0;
    break;
  } /* End of switch */
  printf("Next token is: %d, Next lexeme is %s\n",
         nextToken, lexeme);
  return nextToken;
} /* End of function lex */