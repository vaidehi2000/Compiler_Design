#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

FILE* file;
int line=0;
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
		fscanf(file,"%c",&c);
		if(feof(file))
		{
			break;
		}
		if(c=='\n')
		{
			line++;
			if(i==0)
			{
				continue;
			}
			break;
		}
		if(c==' ')
		{
			if(i==0)
			{
				continue;
			}
			break;
		}
		s[i]=c;
		i++;
	}
	if(c==EOF && i==0)
  	{
		printf("ERROR!!!\nEnd of FIle reached.\n");
	  	return;
  	}
  	else
  	{
		printf("%s\n",s);
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
  	for(int i=1;i<strlen(s);i++)
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
    		printf("\nType check successfull on line %d\n",line);
    		scan(s);
  	}
  	else
  	{
    		printf("\nError: Type not matched on line %d.\n",line);
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
      		printf("\nError: Not a valid variable\n");
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
			  		printf(" ';' Expected on line %d\n ",line);
                    			exit(0);
			  	}
			 }
			 else
			 {
			 	printf(" ']' expected on line %d\n",line);
                		exit(0);
			 }
		}
		else
		{
			printf("\nValid number expected on line %d\n",line);
            		exit(0);
		}
	}	
  	else
  	{
    		printf("\n either ';', '[' or '(' expected on line %d\n",line);
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
         	return;
    	}
    	else if(strcmp(s,"(")==0)
    	{
         	scan(s);
         	Expr();
         	if(strcmp(s,")")==0)
         	{
              		scan(s);
              		return;
         	}
         	else
         	{
              		printf("Error: ')' expected on line %d\n",line);
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
                   		return;
              		}
              		else
              		{
                   		printf("Error: ')' expected on line %d\n",line);
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
                   		else
                   		{
                        		return;
                   		}
              		}
              		else
              		{
                   		printf("Error: ']' expected on line %d\n",line);
              		}
		}
        	else if(strcmp(s,"=")==0)
       	 	{
            		scan(s);
              		Expr();
        	}
        	else
        	{
              		return;
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
                    		printf(" ';' Expected on line %d\n ",line);
                    		exit(0);
              		}
         	}
         	else
         	{
              		printf("\nValid ID expected on line %d\n",line);
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
             		printf(" ';' Expected on line %d\n ",line);
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
                  		printf(" ')' Expected on line %d\n ",line);
                  		exit(0);
              		}
         	}
         	else
         	{
             		printf(" '(' Expected on line %d\n ",line);
             		exit(0);
         	}
    	}
    	else if(strcmp(s,"{")==0)
    	{
    		printf("5\n");
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
         	printf("Error on line %d\n ",line);
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
		printf("Expected '{' on line %d\n",line);
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
		printf("Error: '}' expected on line %d\n",line);
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
    		printf("\nError: Not a valid variable on line %d\n",line);
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
  			printf(" ']' expected at line %d\n",line);
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
        	printf(" ')' expected at line %d\n",line);
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
    		printf("\nValid variable\n");
    		scan(s);
  	}
  	else
  	{
    		printf("\nError: Not a valid variable\n");
  	}
  	if(strcmp(s,"(")==0)
  	{
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
			}
		}
		else
		{
			printf(" ')' expected at line %d\n",line);
		}
	}
	else
	{
		printf(" Expected '(' at line %d\n",line);
	}
}
  				
void FunDeclList()
{
	FunDecl();
	if(feof(file))
	{
		return;
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
        printf(" Expected '(' or ';' at line %d\n",line);
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
		printf("error opening the file");
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
