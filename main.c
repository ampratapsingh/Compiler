#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum
{
  SEMI,
  OPEN_PAREN,
  CLOSE_PAREN,
} TypeSeperator;

typedef enum
{
  INT,
} TypeLiteral;

typedef enum
{
  EXIT,
} TypeKeyword;

typedef struct
{
  TypeKeyword type;
} TokenKeyword;

typedef struct
{
  TypeLiteral type;
  char *value;
} TokenLiteral;

typedef struct
{
  TypeSeperator type;
} TokenSeperator;

TokenLiteral *generate_number(char *current, int *current_index)
{
  TokenLiteral *token = malloc(sizeof(TokenLiteral));
  token->type = INT;
  char *value = malloc(sizeof(char) * 8);
  int value_index = 0;

  while (isdigit(current[*current_index]) && current[*current_index] != '\0')
  {
    value[value_index] = current[*current_index];
    value_index++;
    *current_index += 1;
  }
  value[value_index] = '\0';
  token->value = value;
  return (token);
}

TokenKeyword *generate_keyword(char *current, int *current_index)
{
  TokenKeyword *token = malloc(sizeof(TokenKeyword));
  char *keyword = malloc(sizeof(char) * 8);
  int keyword_index = 0;
  while (isalpha(current[*current_index]) && current[*current_index] != '\0')
  {
    keyword[keyword_index] = current[*current_index];
    keyword_index++;
    *current_index += 1;
  }
  keyword[keyword_index] = '\0';
  if (strcmp(keyword, "exit") == 0)
  {
    token->type = EXIT;
  }
  return token;
}

void lexer(FILE *file)
{
  int length;
  char *buffer = 0;
  fseek(file, 0, SEEK_END);
  length = ftell(file);
  fseek(file, 0, SEEK_SET);
  buffer = malloc(sizeof(char) * length + 1);
  fread(buffer, 1, length, file);
  fclose(file);
  buffer[length] = '\0';
  char *current = buffer;
  int current_index = 0;

  while (current[current_index] != '\0')
  {
    if (current[current_index] == ';')
    {
      printf("FOUND SEMICOLON\n");
    }
    else if (current[current_index] == '(')
    {
      printf("FOUND OPEN PARENTHESIS\n");
    }
    else if (current[current_index] == ')')
    {
      printf("FOUND CLOSE PARENTHESIS\n");
    }
    else if (isdigit(current[current_index]))
    {
      TokenLiteral *test_token = generate_number(current, &current_index);
      printf("TEST TOKEN VALUE: %s\n", test_token->value);
      continue;
    }
    else if (isalpha(current[current_index]))
    {
      TokenKeyword *test_keyword = generate_keyword(current, &current_index);
      if (test_keyword->type == EXIT)
      {
        printf("FOUND KEYWORD: EXIT\n");
      }
      continue;
    }
    current_index += 1;
  }
}

int main()
{
  FILE *file;
  file = fopen("test.upes", "r");
  if (file == NULL)
  {
    printf("Error: cannot open test.upes\n");
    return 1;
  }
  lexer(file);
}
