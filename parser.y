%{
    #include <stdio.h>
    int yylex(void);
    void yyerror(char *);
%}

%union{
    int integer;
    
}