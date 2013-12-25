%{
#include <string.h>
#include "node.h"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() { }

 int current_line_indent = 0; // indentation of current line
 int indent_level = 0; // indentation level passed to the parser

%}

%x indent // start state for parsing indentation
%s normal // normal state for all else?

%%
// logic to handle indentation
// based off of code here: 
// http://stackoverflow.com/questions/1413204/how-to-use-indentation-as-block-delimiters-with-bison-and-flex
<indent>" "            { printf("A line can not start with spaces! only tabs denote indentation.\n"); yyterminate(); }

<indent>"\t"           { current_line_indent++; }
<indent>.              { 
  unput(*yytext);
   if (current_line_indent > indent_level) {
     indent_level++;
     return TOKEN(TINDENT);
   } else if (current_line_indent < indent_level) {
     indent_level--;
     return TOKEN(TUNINDENT);
   } else {
     BEGIN normal;
   }
 }

// regular logic 
<normal>"\n"           { current_line_indent = 0; BEGIN indent; }

[a-zA-Z_][a-ZA-Z0-9_]* SAVE_TOKEN; return TIDENTIFIER;
[0-9]+\.[0-9]*         SAVE_TOKEN; return TDOUBLE;
[0-9]+                 SAVE_TOKEN; return TINTEGER;
"="                    return TOKEN(TEQUAL);
"=="                   return TOKEN(TCEQ);
"!="                   return TOKEN(TCNE);
"<"                    return TOKEN(TCLT);
"<="                   return TOKEN(TCLE);
">"                    return TOKEN(TCGT);
">="                   return TOKEN(TCGE);
"("                    return TOKEN(TLPAREN);
")"                    return TOKEN(TRPAREN);
":"                    return TOKEN(TCOLON);
":="                   return TOKEN(TDECLARE);
"."                    return TOKEN(TDOT);
","                    return TOKEN(TCOMMA);
"+"                    return TOKEN(TPLUS);
"-"                    return TOKEN(TMINUS);
"*"                    return TOKEN(TMUL);
"/"                    return TOKEN(TDIV);
" "                    ; // spaces are null operators
.                      printf("Unknown token!\n"); yyterminate();

%%
