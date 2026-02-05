# Tiny BASIC Lexer - Lab 2

## Author
Mason Watkins

## Overview
This is a lexical analyzer (lexer) for Tiny BASIC, implemented in C without using lexer-generator tools like lex or flex. The lexer identifies all tokens and lexemes according to the Tiny BASIC grammar specification and generates appropriate errors for illegal symbols.

## Compilation
```bash
gcc -o front front.c
```

## Usage
```bash
./front
```
The lexer reads from a file named `front.in` in the current directory.

## Tiny BASIC Grammar Support

### Keywords
The lexer recognizes all Tiny BASIC keywords (case-insensitive):
- PRINT
- IF
- THEN  
- GOTO
- INPUT
- LET
- GOSUB
- RETURN
- CLEAR
- LIST
- RUN
- END

### Operators
**Arithmetic:**
- `+` (addition)
- `-` (subtraction)
- `*` (multiplication)
- `/` (division)

**Relational:**
- `<` (less than)
- `<=` (less than or equal)
- `>` (greater than)
- `>=` (greater than or equal)
- `=` (equals)
- `<>` (not equal)
- `><` (not equal, alternate form)

### Delimiters
- `(` (left parenthesis)
- `)` (right parenthesis)
- `,` (comma)

### Literals
- **Integer literals**: Sequences of digits (0-9)
- **String literals**: Text enclosed in double quotes (`"..."`)
  - Properly handles unterminated strings with error messages

### Variables
- Single-letter variables (A-Z)
- Case-insensitive
- Multi-letter non-keywords generate error messages

## Token Codes

| Token Type | Code | Description |
|------------|------|-------------|
| STR_LIT | 8 | String literal |
| INT_LIT | 10 | Integer literal |
| IDENT | 11 | Identifier (single-letter variable) |
| LT_OP | 18 | Less than (<) |
| RT_OP | 19 | Greater than (>) |
| EQUALS_OP | 20 | Equals (=) |
| ADD_OP | 21 | Addition (+) |
| SUB_OP | 22 | Subtraction (-) |
| MULT_OP | 23 | Multiplication (*) |
| DIV_OP | 24 | Division (/) |
| LEFT_PAREN | 25 | Left parenthesis (() |
| RIGHT_PAREN | 26 | Right parenthesis ()) |
| LTEQ_OP | 27 | Less than or equal (<=) |
| RTEQ_OP | 28 | Greater than or equal (>=) |
| NOTEQ_OP | 29 | Not equal (<> or ><) |
| PRINT | 30 | PRINT keyword |
| IF | 31 | IF keyword |
| THEN | 32 | THEN keyword |
| GOTO | 33 | GOTO keyword |
| GOSUB | 34 | GOSUB keyword |
| INPUT | 35 | INPUT keyword |
| LET | 36 | LET keyword |
| RETURN | 37 | RETURN keyword |
| CLEAR | 38 | CLEAR keyword |
| LIST | 39 | LIST keyword |
| COMMA | 40 | Comma (,) |
| RUN | 41 | RUN keyword |
| END | 42 | END keyword |

## Features

### Error Handling
The lexer provides informative error messages for:
1. **Illegal symbols**: Characters that don't match any valid token pattern
2. **Invalid identifiers**: Multi-letter identifiers (Tiny BASIC only allows single-letter variables)
3. **Unterminated strings**: String literals without closing quotes

### Compound Operators
The lexer correctly handles multi-character relational operators:
- `<=` is recognized as a single token (LTEQ_OP), not as `<` followed by `=`
- `>=` is recognized as a single token (RTEQ_OP), not as `>` followed by `=`
- `<>` is recognized as a single token (NOTEQ_OP), not as `<` followed by `>`
- `><` is also recognized as NOTEQ_OP (alternate notation)

### String Handling
Strings are the most challenging part of this lexer:
- Strings start and end with double quotes (`"`)
- The lexer handles strings that span until EOF or newline with appropriate error messages
- Empty strings (`""`) are valid

## Test Files

### front.in
The default test file (currently set to comprehensive_test.in)

### comprehensive_test.in
A comprehensive test that exercises all features:
- All keywords
- All operators (arithmetic and relational, including compound operators)
- String literals
- Integer literals  
- Variable assignment and usage
- Subroutines (GOSUB/RETURN)
- Conditional branching (IF/THEN/GOTO)

### life_simple.in
A simple cellular automaton simulation demonstrating:
- User input (INPUT)
- Loops (GOTO)
- Conditional logic (IF/THEN)
- Arithmetic operations

## Implementation Details

### Key Functions

**`lex()`**
- Main lexical analysis function
- Handles identification of all token types
- Manages the state machine for token recognition

**`lookup(char ch)`**
- Handles operator and delimiter recognition
- Implements lookahead for compound operators (<= >= <>)
- Returns appropriate error for illegal symbols

**`keywordLookup()`**
- Distinguishes keywords from identifiers
- Case-insensitive keyword matching
- Validates single-letter variable constraint

**`getChar()`**
- Reads next character from input
- Classifies characters (LETTER, DIGIT, QUOTE, UNKNOWN, EOF)

**`addChar()`**
- Adds current character to lexeme buffer
- Provides buffer overflow protection

**`getNonBlank()`**
- Skips whitespace (spaces and tabs)
- Preserves newlines for statement separation

## Example Output

Input:
```
10 PRINT "HELLO"
20 LET A = 5
30 IF A <= 10 THEN GOTO 50
```

Output:
```
Next token is: 10, Next lexeme is 10
Next token is: 30, Next lexeme is PRINT
Next token is: 8, Next lexeme is "HELLO"
Next token is: 10, Next lexeme is 20
Next token is: 36, Next lexeme is LET
Next token is: 11, Next lexeme is A
Next token is: 20, Next lexeme is =
Next token is: 10, Next lexeme is 5
Next token is: 10, Next lexeme is 30
Next token is: 31, Next lexeme is IF
Next token is: 11, Next lexeme is A
Next token is: 27, Next lexeme is <=
Next token is: 10, Next lexeme is 10
Next token is: 32, Next lexeme is THEN
Next token is: 33, Next lexeme is GOTO
Next token is: 10, Next lexeme is 50
Next token is: -1, Next lexeme is EOF
```

## References
- Tiny BASIC Wikipedia: https://en.wikipedia.org/wiki/Tiny_BASIC
- Original Tiny BASIC Design Note by Dennis Allison (1975)
- Sebesta, "Concepts of Programming Languages" (Chapter on Lexical Analysis)