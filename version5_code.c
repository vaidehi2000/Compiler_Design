#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

FILE* file;
int line=1,err = 0,character_count = 0 ;
char s[100]="";

void Program();
void VarDeclList();
void VarDecl();
void FunDeclList();
void FunDecl();
void ParamDecList();
void ParamDeclListTail();
void ParamDecl();
void Block();
void Type();
void StmtList();
bool UnaryOp(char* s);
bool BinOp(char* s);
void Stmt();
void Expr();
void ExprList();
void ExprListTail();

void scan(char* s)
{
	memset(s,0,strlen(s));
	char c;
	int i=0;
	while(c!=EOF)
	{
		fscanf(file, "%c", &c);
	    	if(feof(file))
       		{
           		break;
        	}
		if(c=='\n')
		{
			line++;
			character_count = 0;
			if(i==0)
			{
				continue;
			}
			break;
		}
		if(c==' ')
		{
			character_count++;
			if(i==0)
			{
				continue;
			}
			break;
		}
		character_count++;
		s[i]=c;
		i++;
	}
}

bool valid_num(char* s)
{
	int i;
  	for(i=0;i<strlen(s);i++)
  	{
    		if(!(s[i]>='0' && s[i]<='9'))
    		{
      			return false;
    		}
  	}
  	return true;
}


bool valid_ID(char* s)
{
  	if(!(s[0]>='a' && s[0]<='z'))
  	{
    		return false;
  	}
  	int i;
  	for(i=1;i<strlen(s);i++)
  	{
    		if(!((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') || (s[i]>='0' && s[i]<='9') || (s[i]=='_')))
    		{
      			return false;
    		}
  	}
  	return true;
}

bool BinOp(char* s)
{
	if(strcmp(s,"+")==0 || strcmp(s,"-")==0 || strcmp(s,"*")==0 || strcmp(s,"/")==0 || strcmp(s,"==")==0 || strcmp(s,"!=")==0 || strcmp(s,"<")==0 || strcmp(s,"<=")==0 || strcmp(s,">")==0 || strcmp(s,">=")==0 || strcmp(s,"&&")==0 || strcmp(s,"||")==0)
	{
		return true;
     	}
     	else
     	{
          	return false;
     	}
}

bool UnaryOp(char* s)
{
     	if(strcmp(s,"!")==0 || strcmp(s,"-")==0)
     	{
          	return true;
     	}
     	else
     	{
          	return false;
     	}
}

void Type()
{
  	if(strcmp(s,"int")==0 || strcmp(s,"char")==0)
  	{
    		scan(s);
  	}
  	else
  	{
    		printf("ERROR: Type check unsuccessful on line %d:%d.\n",line,character_count-1);
    		exit(0);
  	}
}

void VarDecl()
{
	Type();
	if(valid_ID(s))
	{
    		scan(s);
  	}
  	else
  	{
      		printf("ERROR: Not a valid variable on line %d:%d\n",line,character_count-1);
	    	exit(0);
  	}
  	if(strcmp(s,";")==0)
  	{
      		return;
  	}
  	else if(strcmp(s,"(")==0)
	{
		return;
	}
  	else if(strcmp(s,"[")==0)
  	{
  		scan(s);
  		if(valid_num(s)==true)
  		{
  			scan(s);
  			if(strcmp(s,"]")==0)
  			{
  				scan(s);
			  	if(strcmp(s,";")==0)
			  	{
			    		VarDeclList();
			  	}
			  	else
			  	{
			  		printf("ERROR: ';' Expected on line %d:%d\n ",line,character_count-1);
                    			exit(0);
			  	}
			 }
			 else
			 {
			 	printf("ERROR: ']' expected on line %d:%d\n",line,character_count-1);
                		exit(0);
			 }
		}
		else
		{
			printf("ERROR: Valid number expected on line %d:%d\n",line,character_count-1);
            		exit(0);
		}
	}
  	else
  	{
    		printf("ERROR: Either ';', '[' or '(' expected on line %d:%d\n",line,character_count-1);
            	exit(0);
  	}
}

void ExprListTail()
{
     	Expr();
     	if(strcmp(s,",")==0)
     	{
          	scan(s);
          	ExprListTail();
     	}
     	else
     	{
          	return;
     	}
}

void ExprList()
{
     	if(strcmp(s,")")==0)
     	{
          	return;
     	}
     	else
     	{
          	ExprListTail();
     	}
}


void Expr()
{
    	if(UnaryOp(s))
    	{
         	scan(s);
         	Expr();
    	}
    	else if(valid_num(s))
    	{
         	scan(s);
    	}
    	else if(strcmp(s,"(")==0)
    	{
         	scan(s);
         	Expr();
         	if(strcmp(s,")")==0)
         	{
              		scan(s);
         	}
         	else
         	{
              		printf("ERROR: ')' expected on line %d:%d\n",line,character_count-1);
              		exit(0);
         	}	
    	}
    	else if(valid_ID(s))
    	{
         	scan(s);
         	if(strcmp(s,"(")==0)
         	{
              		scan(s);
              		ExprList();
              		if(strcmp(s,")")==0)
              		{
                   		scan(s);
              		}
              		else
              		{
                   		printf("ERROR: ')' expected on line %d:%d\n",line,character_count-1);
                   		exit(0);
              		}
       		}
       		else if(strcmp(s,"[")==0)
       		{
              		scan(s);
              		Expr();
              		if(strcmp(s,"]")==0)
              		{
                   		scan(s);
                   		if(strcmp(s,"=")==0)
                   		{
                        		scan(s);
                        		Expr();
                   		}
              		}
              		else
              		{
                   		printf("ERROR: ']' expected on line %d:%d\n",line,character_count-1);
                   		exit(0);
              		}
         	}
         	else if(strcmp(s,"=")==0)
         	{
              		scan(s);
              		Expr();
         	}
    	}
    	if(BinOp(s))
    	{
         	scan(s);
         	Expr();
    	}
    	else
    	{
         	return;
    	}
}

void Stmt()
{
	if(strcmp(s,"write")==0 || strcmp(s,"return")==0)
    	{
        	scan(s);
        	Expr();
    	}
    	else if(strcmp(s,"read")==0)
    	{
         	scan(s);
         	if(valid_ID(s))
         	{
              		scan(s);
              		if(strcmp(s,";")==0)
              		{
                   		return;
              		}
              		else
              		{
                    		printf("ERROR: ';' Expected on line %d:%d\n ",line,character_count-1);
                    		exit(0);
              		}
         	}
         	else
         	{
              		printf("ERROR: Valid ID expected on line %d:%d\n",line,character_count-1);
              		exit(0);
         	}
    	}
    	else if(strcmp(s,"writeln")==0 || strcmp(s,"break")==0)
    	{
         	scan(s);
         	if(strcmp(s,";")==0)
         	{
              		return;
         	}
         	else
         	{
             		printf("ERROR: ';' Expected on line %d:%d\n ",line,character_count-1);
             		exit(0);
         	}
    	}
    	else if(strcmp(s,"if")==0 || strcmp(s,"while")==0)
    	{
         	scan(s);
         	if(strcmp(s,"(")==0)
         	{
              		scan(s);
              		Expr();
              		if(strcmp(s,")")==0)
              		{
                   		scan(s);
                   		Stmt();
                   		if(strcmp(s,"else")==0)
                   		{
                        		scan(s);
                        		Stmt();
                   		}
                   		else
                   		{
                       			return;
                   		}
              		}
              		else
              		{
                  		printf("ERROR: ')' Expected on line %d:%d\n ",line,character_count-1);
                  		exit(0);
              		}
         	}
         	else
         	{
             		printf("ERROR: '(' Expected on line %d:%d\n ",line,character_count-1);
             		exit(0);
         	}
    	}
    	else if(strcmp(s,"{")==0)
    	{
         	Block();
    	}
    	else if(strcmp(s,"(")==0 || valid_ID(s) || valid_num(s) || UnaryOp(s))
    	{
         	Expr();
    	}
    	else if(strcmp(s,";")==0)
    	{
        	scan(s);
         	return;
    	}
    	else
    	{
         	printf("Error on line %d:%d\n ",line,character_count-1);
         	exit(0);
    	}
}

void StmtList()
{
	Stmt();
	if(strcmp(s,"}")!=0)
	{
		StmtList();
	}
}

void Block()
{
	if(strcmp(s,"{")!=0)
	{
		printf("ERROR: Expected '{' on line %d:%d\n",line,character_count-1);
        	exit(0);
	}
	scan(s);
    	if(strcmp(s,"int")==0 || strcmp(s,"char")==0)
	{
		VarDeclList();
	}
	StmtList();
	if(strcmp(s,"}")!=0)
	{
		printf("ERROR: Expected '}' on line %d:%d\n",line,character_count-1);
        	exit(0);
	}
	scan(s);
}

void ParamDecl()
{
	Type();
	if(valid_ID(s)==true)
  	{
    		scan(s);
  	}
  	else
  	{
    		printf("ERROR: Not a valid variable on line %d:%d\n",line,character_count-1);
      		exit(0);
  	}
    	if(strcmp(s,"[")==0)
  	{
  		scan(s);
  		if(strcmp(s,"]")==0)
  		{
  			scan(s);
  		}
  		else
  		{
  			printf("ERROR: ']' expected at line %d:%d\n",line,character_count-1);
            		exit(0);
  		}
  	}
  	else
  	{
  		return;
  	}
}

void ParamDeclListTail()
{
	ParamDecl();
    	if(strcmp(s,",")==0)
  	{
  		scan(s);
  		ParamDeclListTail();
  	}
	if(strcmp(s,")")==0)
	{
		return;
	}
    	else
    	{	
        	printf("ERROR: ',' or ')' expected at line %d:%d\n",line,character_count-1);
        	exit(0);
    	}
}

void ParamDecList()
{
	if(strcmp(s,")")==0)
	{
		return;
	}
	else
	{
		ParamDeclListTail();
		if(strcmp(s,")")==0)
		{
			return;
		}
	}
}

void FunDecl()
{
	Type();
	if(valid_ID(s)==true)
  	{
    		scan(s);
  	}
  	else
  	{
    		printf("ERROR: Not a valid variable at position %d:%d\n",line,character_count-1);
    		exit(0);
  	}
  	if(strcmp(s,"(")==0)
  	{
  	    	scan(s);
  		ParamDecList();
  		if(strcmp(s,")")==0)
  		{
  			scan(s);
  			Block();
		}
		else
		{
			printf("ERROR: ')' expected at line %d:%d\n",line,character_count-1);
			exit(0);
		}
	}
	else
	{
		printf("ERROR: Expected '(' at line %d:%d\n",line,character_count-1);
		exit(0);
	}
}

void FunDeclList()
{
	FunDecl();
	if(feof(file))
    	{
        	return;
    	}
	else
	{
		FunDeclList();
	}
}

void VarDeclList()
{
	VarDecl();
	if(strcmp(s,"(")==0)
	{
		scan(s);
		return;
	}
    	else if(strcmp(s,";")==0)
    	{
        	scan(s);
      		if(strcmp(s,"int")==0 || strcmp(s,"char")==0)
        	{
            		VarDeclList();
        	}
        	else
        	{
            		return;
        	}
    	}
    	else
    	{
        	printf("ERROR: Expected '(' or ';' at line %d:%d\n",line,character_count-1);
        	exit(0);
    	}
}

void Program()
{
	VarDeclList();
	ParamDecList();
	if(strcmp(s,")")==0)
	{
		scan(s);
		Block();
		if(feof(file))
		{
			return;
		}
		else
		{
			FunDeclList();
			if(feof(file))
			{
				return;
			}
		}
	}
}

int main()
{
	file = fopen("input.txt", "r");
	if(file == NULL)
	{
		printf("Error opening the file");
	}
	else
	{
		scan(s);
    		Program();
    		if(feof(file))
    		{	
    			printf("\nProgram successfully executed\n");
	    	}
  	}
	fclose(file);
}
