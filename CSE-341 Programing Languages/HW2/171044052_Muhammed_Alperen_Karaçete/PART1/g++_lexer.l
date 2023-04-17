%option noyywrap
%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>  

    char *temp;  
    /* definitions*/
%}

/* rules */
KEYWORDS and|or|not|equal|less|nil|list|append|concat|set|deffun|for|if|exit|load|disp|true|false

%%

[ ] {}
[;][;][a-zA-Z0-9_.+]* {printf ("%s:COMMENT\n",yytext);}


[0] {printf ("%s:VALUE_I\n",yytext);}
[1-9][0-9]* {printf ("%s:VALUE_I\n",yytext);}
[1-9]*[f][0-9]* {printf ("%s:VALUE_F\n",yytext);}

[aA][nN][dD] {printf ("%s:KW_AND\n",yytext);}
[oO][rR] {printf ("%s:KW_OR\n",yytext);}
[nN][oO][tT] {printf ("%s:KW_NOT\n",yytext);}
[eE][qQ][uU][aA][lL] {printf ("%s:KW_EQUAL\n",yytext);}
[lL][eE][sS][sS] {printf ("%s:KW_LESS\n",yytext);}
[nN][iI][lL] {printf ("%s:KW_NILL\n",yytext);}
[lL][iI][sS][tT] {printf ("%s:KW_LIST\n",yytext);}
[aA][pP][pP][eE][nN][dD] {printf ("%s:KW_APPEND\n",yytext);}
[cC][oO][nN][cC][aA][tT] {printf ("%s:KW_CONCAT\n",yytext);}
[sS][eE][tT] {printf ("%s:KW_SET\n",yytext);}
[dD][eE][fF][fF][uU][nN]	 {printf ("%s:KW_DEFFUN\n",yytext);}
[fF][oO][rR] {printf ("%s:KW_FOR\n",yytext);}
[iI][fF] {printf ("%s:KW_IF\n",yytext);}
[eE][xX][iI][tT] {printf ("%s:KW_EXIT\n",yytext);
                    return -1;}
[lL][oO][aA][dD] {printf ("%s:KW_LOAD\n",yytext);}
[dD][iI][sS][pP] {printf ("%s:KW_DISP\n",yytext);}
[tT][rR][uU][eE] {printf ("%s:KW_TRUE\n",yytext);}
[fF][aA][lL][sS][eE] {printf ("%s:KW_FALSE\n",yytext);}

{KEYWORDS}[a-zA-Z]* {
                        printf ("LEXICAL ERROR: A message that indicates the reason for the error.");
                        printf("%s:Can not found \n",yytext);
                        return 0;
                    }

[+]  {printf ("%s:OP_PLUS\n",yytext);}  
[-]  {printf ("%s:OP_MINUS\n",yytext);} 
[/]  {printf ("%s:OP_DIV\n",yytext);} 
[*]  {printf ("%s:OP_MULT\n",yytext);} 
[(]  {printf ("%s:OP_OP\n",yytext);} 
[)]  {printf ("%s:OP_CP\n",yytext);} 
[*][*] {printf ("%s:OP_DBLMULT\n",yytext);}
["][a-zA-Z0-9_]*["] {        
        printf("%c:OP_OC\n",yytext[0]);
        yytext++;
        temp = (char*) malloc (sizeof(char)*(yyleng-1));
        temp[yyleng-1]='\0';
        strncpy(temp,yytext,yyleng-2);
        printf("%s:VALUESTR\n",temp);
        printf("%c:OP_CC\n",yytext[yyleng-2]);  
        free(temp);  
        }
[,]  {printf ("%s:OP_COMA\n",yytext);}

[a-zA-Z_][a-zA-Z0-9_]* {printf ("%s:IDENTIFIER\n",yytext);}

\n {}

%%

int main(int argc, char *argv[]){
    char string[100];
    if (argc==2){
	    FILE *fp = fopen(argv[1], "r");
	    if(fp){
	    	yyin = fp;
            yylex();        
        }
        fclose(fp);
    }
    else if (argc==1){
        printf("Please enter test values:.For terminate type exit\n");
        sscanf("%s",string);
        if (string!="exit" || string!="EXIT")
            yylex();
    }
    return 0;
}