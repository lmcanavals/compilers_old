%{
using namespace std;
int mylineno = 0;
%}

blank [ \t]+

%%

{blank}   /* ignoring white space */
"<>"      cout << YYText() << " relop NE\n";
"<="      cout << YYText() << " relop LE\n";
"<"       cout << YYText() << " relop LT\n";
">="      cout << YYText() << " relop GE\n";
">"       cout << YYText() << " relop GT\n";
"="       cout << YYText() << " relop EQ\n";
\n        mylineno++;
<<EOF>>   return 0;

%%

int yyFlexLexer::yywrap() { return 0; }

int main() {
  FlexLexer* lexer = new yyFlexLexer();
  while (lexer->yylex() != 0)
  ;

  return 0;
}
