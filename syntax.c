/* Syntax Error Identification of C-- Grammar */
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

FILE* file;
int line=1,err = 0,character_count = 0 ;
char s[100]="";

// Function Declarations 
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

/* Function to print Common Error Statement */
void error_print()  
{
	printf("\nLine %d:%d \033[1;31mERROR\033[0m",line,character_count-1);   // "\033[1;31m.....\033[0m"  : This is used to change the text color to red.
}

/* Function to scan file character by character to get words */
void scan(char* s)
{
	memset(s,0,strlen(s));   
	char c;
	int i=0,space = 0;
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
			printf("\n");
			character_count = 0;
			if(i==0)
			{
				continue;
			}
			break;
		}
		if(c==' ')
		{
			space=1;
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
	printf("%s",s);
	if(space==1)
	{
		printf(" ");
	}

}

/* Function to check validity of a number */
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

/* Function to check validity of a variable */
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

/* Function to check whether the input scanned is a binary operator or not */
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

/* Function to check whether the input scanned is a unary operator or not */
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

/* Function to check whether the data type is either integer or character */
void Type()
{
  	if(strcmp(s,"int")==0 || strcmp(s,"char")==0)
  	{
  	    if(feof(file))
       	{
       		error_print();
       		printf(" : Valid_ID expected but reached End of file\n");
       		exit(0);
      	}
   		scan(s);
  	}
  	else
  	{
  		error_print();
    	printf(" : Type check unsuccessful.\n"); /* Any other data type is not valid in C-- grammar */
    	exit(0);
  	}
}


/* Function to check the correctness of one or more comma separated Expressions */
void ExprListTail()
{
	Expr();
	if(strcmp(s,",")==0)
   	{
      	if(feof(file))
       	{
       		error_print();
          	printf(" : Expression expected but reached End of file\n");
           	exit(0);
       	}
      	scan(s);
      	ExprListTail();
   	}
  	else
   	{
       	return;
   	}
}
/* Expression List Function */
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

/* Function to check the correctness of all possible expressions */
void Expr()
{
    if(UnaryOp(s))
   	{
       	if(feof(file))
       	{
       		error_print();
       		printf(" : Expression expected but reached End of file\n");
       		exit(0);
      	}
       	scan(s);
       	Expr();
  	}
  	else if(valid_num(s))
  	{
      	if(feof(file))
       	{
       		error_print();
       		printf(" : ';' or ')' or ']' or ',' or Binary operator expected but reached End of file\n");
       		exit(0);
       	}
       	scan(s);
    }
   	else if(strcmp(s,"(")==0)
   	{
       	if(feof(file))
       	{
       		error_print();
       		printf(" : Expression expected but reached End of file\n");
       		exit(0);
       	}
       	scan(s);
       	Expr();
       	if(strcmp(s,")")==0)
       	{
       		if(feof(file))
      		{
      			error_print();
           		printf(" : Incomplete statement and reached End of file\n");
           		exit(0);
      		}
       		scan(s);
       		return;
      	}
       	else
       	{
       		error_print();
      		printf(" : ')' expected instead of %s\n",s);
      		exit(0);
       	}
	}
	else if(valid_ID(s))
    {
		if(feof(file))
        {
        	error_print();
           	printf(" : '(' or '[' or '=' expected but reached End of file\n");
            exit(0);
        }
        scan(s);
		if(strcmp(s,"(")==0)
        {
            if(feof(file))
			{
				error_print();
                printf(" : Expression or ')' expected but reached End of file\n");
                exit(0);
            }
            scan(s);
            ExprList();
            if(strcmp(s,")")==0)
            {
            	scan(s);
            	if(BinOp(s))
            	{
            		if(feof(file))
            		{
            			exit(0);
                    }
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
       			error_print();
          		printf(" : ')' expected instead of %s\n",s);
          		exit(0);
        	}
      	}
        else if(strcmp(s,"[")==0)
       	{
       		if(feof(file))
       		{	
       			error_print();
          		printf(" : Expression expected but reached End of file\n");
           		exit(0);
       		}
      		scan(s);
       		Expr();
       		if(strcmp(s,"]")==0)
       		{
           		if(feof(file))
         		{
         			error_print();
           			printf(" : End of file\n");
           			exit(0);
          		}	
           		scan(s);
           		if(strcmp(s,"=")==0)
           		{
           			if(feof(file))
              		{
              			error_print();
              			printf(" : Expression expected but reached End of file\n");
               			exit(0);
                    }
                    scan(s);
                    Expr();
                }
			}
            else
            {
            	error_print();
                printf(" : ']' expected instead of %s\n",s);
                exit(0);
			}
        }
        else if(strcmp(s,"=")==0)
        {
        	if(feof(file))
            {
            	error_print();
                printf(" : Expression expected but reached End of file\n");
                exit(0);
            }
            scan(s);
            Expr();
        }
    }
    if(BinOp(s))
    {
        if(feof(file))
        {
        	error_print();
        	printf(" : Expression expected but reached End of file\n");
            exit(0);
        }
        scan(s);
        Expr();
    }
    else
    {
        return;
    }
}

/* Function to check the correctness of a single statement */
void Stmt()
{
	if(strcmp(s,"write")==0 || strcmp(s,"return")==0)
    {
        if(feof(file))
        {
        	error_print();
            printf(" : Expression expected but reached End of file\n");
            exit(0);
        }
        scan(s);
        Expr();
        if(strcmp(s,";")==0)
        {
            scan(s);
            return;
        }
        else
        {
        	error_print();
            printf(" : ';' Expected instead of %s\n ",s);
            exit(0);
        }
    }
    else if(strcmp(s,"read")==0)
    {
        if(feof(file))
        {
        	error_print();
            printf(" : Valid_ID expected but reached End of file\n");
            exit(0);
        }
        scan(s);
        if(valid_ID(s))
        {
        	if(feof(file))
            {
            	error_print();
                printf(" : ';' expected but reached End of file\n");
                exit(0);
            }
            scan(s);
            if(strcmp(s,";")==0)
            {
                 return;
            }
            else
            {
            	error_print();
            	printf(" : ';' Expected instead of %s\n ",s);
                exit(0);
            }
		}
       	else
       	{
       		error_print();
            printf(" : Valid ID expected instead of %s\n",s);
            exit(0);
       	}
   	}
   	else if(strcmp(s,"writeln")==0 || strcmp(s,"break")==0)
   	{
       	if(feof(file))
       	{
       		error_print();
       		printf(" : ';' expected but reached End of file\n");
           	exit(0);
        }
        scan(s);
        if(strcmp(s,";")==0)
        {
            return;
        }
        else
        {
        	error_print();
            printf(" : ';' Expected instead of %s\n ",s);
            exit(0);
        }
    }
    else if(strcmp(s,"while")==0)
    {
        if(feof(file))
        {
        	error_print();
            printf(" : '(' expected but reached End of file\n");
            exit(0);
        }
        scan(s);
        if(strcmp(s,"(")==0)
        {
            if(feof(file))
            {
            	error_print();
            	printf(" : Expression expected but reached End of file\n");
                exit(0);
            }
            scan(s);
            Expr();
            if(strcmp(s,")")==0)
            {
            	if(feof(file))
                {
                	error_print();
                	printf(" : Statement expected but reached End of file\n");
                	exit(0);
                }
                scan(s);
                Stmt();
                return;
            }
            else
            {
            	error_print();
            	printf(" : ')' Expected instead of %s\n ",s);
                exit(0);
            }
		}
        else
        {
        	error_print();
            printf(" : '(' Expected instead of %s\n ",s);
            exit(0);
        }
	}
    else if(strcmp(s,"if")==0)
    {
        if(feof(file))
        {
        	error_print();
            printf(" : '(' expected but reached End of file\n");
            exit(0);
        }
        scan(s);
        if(strcmp(s,"(")==0)
        {
            if(feof(file))
            {
            	error_print();
                printf(" : Expression expected but reached End of file\n");
                exit(0);
            }
            scan(s);
            Expr();
            if(strcmp(s,")")==0)
            {
                if(feof(file))
                {
                	error_print();
                    printf(" : Statement expected but reached End of file\n");
                    exit(0);
                }
                scan(s);
                Stmt();
                if(strcmp(s,"else")==0)
                {
                    if(feof(file))
                    {
                    	error_print();
                        printf(" : Statement expected but reached End of file\n");
                        exit(0);
                    }
                    scan(s);
                    Stmt();
                }
                else
                {
                	error_print();
                    printf(" : 'else' Expected instead of %s\n ",s);
                    exit(0);
                }
            }
            else
            {
            	error_print();
                printf(" : ')' Expected instead of %s\n ",s);
                exit(0);
            }
        }
        else
        {
        	error_print();
            printf(" : '(' Expected instead of %s\n ",s);
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
       	if(strcmp(s,";")==0)
       	{
           	scan(s);
           	return;
       	}
       	else
       	{
       		error_print();
           	printf(" : ';' Expected instead of %s\n ",s);
           	exit(0);
       	}
   	}
   	else if(strcmp(s,";")==0)
   	{
    	scan(s);
    	return;
   	}
   	else
   	{
   		error_print();
       	exit(0);
	}
}

/* Function to check the correctness of a one or more consecutive statements */
void StmtList()
{
	Stmt();
	if(strcmp(s,"}")!=0)
	{
		StmtList();
	}
}

/*Function to check the correctness of variable declarations and following statements */
void Block()
{
	if(strcmp(s,"{")!=0)
	{
		error_print();
		printf(" : '{'  Expected instead of %s\n",s);
        exit(0);
	}
	if(feof(file))
    {
    	error_print();
        printf(" : Valid type or Statement expected but reached End of file\n");
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
		error_print();
		printf(" : '}' Expected instead of %s\n",s);
        exit(0);
	}
	scan(s);
}

/* Function to check the correctness of a single parameter declaration in a function */
void ParamDecl()
{
	Type();
	if(valid_ID(s)!=true)
  	{
  		error_print();
    	printf(" : Valid variable expected instead of %s\n",s);
      	exit(0);
  	}
  	if(feof(file))
    {
    	error_print();
        printf(" : '[' or ',' or ')' expected but reached End of file\n");
        exit(0);
    }
  	scan(s);
    if(strcmp(s,"[")==0)
  	{
  	    if(feof(file))
        {
        	error_print();
            printf(" : ']' expected but reached End of file\n");
            exit(0);
        }
  		scan(s);
  		if(strcmp(s,"]")==0)
  		{
  		    if(feof(file))
            {
            	error_print();
                printf(" : ',' or ')' expected but reached End of file\n");
                exit(0);
            }
  			scan(s);
  		}
  		else
  		{
  			error_print();
  			printf(" : ']' expected instead of %s\n",s);
            exit(0);
  		}
  	}
  	else
  	{
  		return;
  	}
}

/* Function to check the correctness of consecutive parameter declarations in a function */
void ParamDeclListTail()
{
	ParamDecl();
    if(strcmp(s,",")==0)
  	{
  	    if(feof(file))
        {
        	error_print();
            printf(" : Valid Type expected but reached End of file\n");
            exit(0);
        }
  		scan(s);
  		ParamDeclListTail();
  	}
	if(strcmp(s,")")==0)
	{
		return;
	}
    else
    {
    	error_print();
        printf(" : ',' or ')' expected instead of %s\n",s);
        exit(0);
    }
}

/* Function to check the correctness of zero or more consecutive parameter declarations in a function */
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

/* Function to check the correctness of a single function declaration in a program */
void FunDecl()
{
	Type();
	if(valid_ID(s)!=true)
  	{
  		error_print();
    	printf(" : Valid variable expected instead of %s\n",s);
    	exit(0);
  	}
  	if(feof(file))
    {
    	error_print();
        printf(" : '(' expected but reached End of file\n");
        exit(0);
    }
    scan(s);
  	if(strcmp(s,"(")==0)
  	{
  	    if(feof(file))
        {
        	error_print();
            printf(" : Valid Type or ')' expected but reached End of file\n");
            exit(0);
        }
  	    scan(s);
  		ParamDecList();
  		if(strcmp(s,")")==0)
  		{
  		    if(feof(file))
            {
            	error_print();
                printf(" : '{' expected but reached End of file\n");
                exit(0);
            }
  			scan(s);
  			Block();
		}
		else
		{
			error_print();
			printf(" : ')' expected instead of %s\n",s);
			exit(0);
		}
	}
	else
	{
		error_print();
		printf(" : '(' Expected instead of %s\n",s);
		exit(0);
	}
}

/* Function to check the correctness of consecutive function declarations in a program */
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

/* Function to check the correctness of a single variable declaration */
void VarDecl()
{
	Type();
	if(valid_ID(s))
	{
	    if(feof(file))        /* This is placed in order not to scan EOF */
        {
        	error_print();
           	printf(" : ';' or '(' or '[' expected but reached End of file\n");
       		exit(0);
       	}
      	scan(s);
  	}
  	else
  	{
  		error_print();
   		printf(" : Valid variable expected instead of %s\n",s);
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
  	  	if(feof(file))
       	{
       		error_print();
       		printf(" : Valid_num expected but reached End of file\n");
       		exit(0);
      	}
  		scan(s);

  		if(valid_num(s)==true)

  		{

 	    	if(feof(file))

       		{
       			error_print();

           		printf(" : ']' expected but reached End of file\n");

           		exit(0);

       		}

  			scan(s);

  			if(strcmp(s,"]")==0)

			{

  		    	if(feof(file))

           		{
           			error_print();

           			printf(" : ';' expected but reached End of file\n");

           			exit(0);

           		}

  				scan(s);

			  	if(strcmp(s,";")==0)

			  	{
			   		VarDeclList();
			  	}
			  	else
			  	{
			  		error_print();
			  		printf(" : ';' Expected instead of %s\n ",s);
           			exit(0);
			  	}
			}
			else
			{
				error_print();
				printf(" : ']' expected instead of %s\n",s);
                exit(0);
			}
		}
		else
		{
			error_print();
			printf(" : Valid number expected instead of %s\n",s);
       		exit(0);
		}
	}
  	else
  	{
  		error_print();
    	printf(" : Either ';', '[' or '(' expected instead of %s\n",s);
        exit(0);
  	}
}


/* Function to check the correctness of zero or more consecutive variable declarations*/
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
    	error_print();
        printf(" : '(' or ';' Expected instead of %s\n",s);
        exit(0);
    }
}

/* Program Function */
void Program()
{
	VarDeclList();
	ParamDecList();
	if(strcmp(s,")")==0)
	{
	    if(feof(file))
        {
        	error_print();
            printf(" : '{' expected but reached End of file\n");
            exit(0);
        }
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
	file = fopen("input.txt", "r");   // input.txt contains the c-- program to be checked for syntax error identification
	if(file == NULL)         
	{
		printf("\nError opening the file\n");     // Give error when file not found
	}
	else
	{
		scan(s);
	    if(feof(file))          /* This is placed in order not to scan EOF */
        {
            printf("\nError: End of file\n");
            exit(0);
        }
    	Program();
   		if(feof(file))
    	{
	   		printf("\nINPUT FILE DOES NOT CONTAIN ANY SYNTAX ERROR\n");    // If reaching EOF without encountering any error then successfull
		}
  	}
	fclose(file);
}
