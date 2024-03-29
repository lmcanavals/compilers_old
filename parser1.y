%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  
  int yylex(void);
  void yyerror(char const*);
%}

%define api.value.type { double }
%token NUM

%%

input:
    %empty
  | input line
  ;

line:
    '\n'
  | exp '\n'      { printf("ANS: %.10g\n", $1); }
  ;

exp:
    NUM
  | exp exp '+'   { $$ = $1 + $2; }
  | exp exp '-'   { $$ = $1 - $2; }
  | exp exp '*'   { $$ = $1 * $2; }
  | exp exp '/'   { $$ = $1 / $2; }
  /*| exp exp '^'   { $$ = pow($1, $2); }*/
  | exp 'n'       { $$ = -$1; }
  ;

%%

int yylex(void) {
  int c = getchar();
  while (c == ' ' || c == '\t') {
    c = getchar();
  }
  if (c == '.' || (c >= '0' && c <= '9')) {
    ungetc(c, stdin);
    if (scanf("%lf", &yylval) != 1) {
      abort();
    }
    return NUM;
  } else if (c == EOF) {
    return YYEOF;
  } else {
    return c;
  }
}

void yyerror(char const* s) {
  fprintf(stderr, "%s\n", s);
}

int main(void) {
  return yyparse();
}
