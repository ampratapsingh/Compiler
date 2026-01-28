#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
  SEMI,
  OPEN_PAREN,
  CLOSE_PAREN,
} TypeSeperator;

typedef enum {
  INT,
} TypeLiteral;

typedef enum{
  EXIT,
} TypeKeyword;

typedef struct {
  TypeKeyword type;
} TokenKeyword;

typedef struct {
  TypeLiteral type;
  char *value;
} TokenLiteral;

typedef struct {
  TypeSeperator type;
} TokenSeperator;

TokenLiteral *generate_number(char current, FILE *file){
  TokenLiteral *token = malloc(sizeof(TokenLiteral));
  token->type = INT;
  char *value = malloc(sizeof(char) * 8);
  int value_index = 0;

  while(isdigit(current) && current != EOF){
    if(!isdigit(current)){
      break;
    }
    value[value_index] = current;
    value_index++;
    current = fgetc(file);
  }
  token->value = value;
  return(token);
}

void lexer(FILE *file){
  char current = fgetc(file);

  while(current != EOF){
    if(current == ';'){
      printf("FOUND SEMICOLON\n");
    }
    else if(current == '('){
      printf("FOUND OPEN PARENTHESIS\n");
    }
    else if(current == ')'){
      printf("FOUND CLOSE PARENTHESIS\n");
    }
    else if(isdigit(current)){
      TokenLiteral *test_token = generate_number(current, file);
      printf("TEST TOKEN VALUE: %s\n", test_token->value);
    }
    else if(isalpha(current)){
      printf("FOUND CHARACTER: %c\n", current);
    } 
    current = fgetc(file);
  }
}

int main(){
  FILE *file;
  file = fopen("test.upes", "r");
  lexer(file);
}
