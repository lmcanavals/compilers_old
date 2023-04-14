%{
using namespace std;
int mylineno = 0;
%}

blank [ \t]+
relop (<[=>]?)|(>(=)?)|=

%%

{blank}   /* ignoring white space */
{relop}   cout << YYText() << " relop\n";
\n        mylineno++;
.         cout << "Unknown token\n";
<<EOF>>   return 0;

%%

int yyFlexLexer::yywrap() { return 0; }

int main() {
  FlexLexer* lexer = new yyFlexLexer();
  while (lexer->yylex() != 0)
  ;

  return 0;
}
