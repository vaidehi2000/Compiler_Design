#include<stdio.h>
#include<string.h>
#include<stdbool.h>

FILE* file;
int /*eof = 0,*/line=0/*,eof1=0,ne=0*/,err = 0;
char s[100];

void match(char* s)
{
	memset(s,0,strlen(s));
	//printf("%s",s);
	char c;
	int i=0;
	while(c!=EOF)
	{
		c = fgetc(file);
		if(c==EOF)
		{
		//	printf("ITeration: %d",i);
			break;
		}
		if(c=='\n')
		{
			line++;
			continue;
		}
		if(c==' ')
		{
			if(i==0)
			{
				continue;
			}
			//printf("Before break\n");
			break;
			//printf("After break\n");
		}
		s[i]=c;
		i++;
	//	printf("%c  %d\n",c,i);
	}
	//printf("$$$$");
	if(c==EOF && i==0)
  	{
  		err = 1;
		printf("ERROR!!!\nEnd of FIle reached.\n");
	  	return;
  	}
  	else
  	{
		printf("%s  ",s);
  	}
}

bool valid_num(char* s)
{
  	for(int i=0;i<strlen(s);i++)
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
  	for(int i=1;i<strlen(s);i++)
  	{
    		if(!((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') || (s[i]>='0' && s[i]<='9') || (s[i]=='_')))
    		{
      			return false;
    		}
  	}
  	return true;
}

void Type()
{
  	s[100]="";
  	match(s);
  	if(strcmp(s,"int")==0 || strcmp(s,"char")==0)
  	{
    		//fseek(file,0,SEEK_CUR);
    		printf("\nType check successful\n");
  	}
  	else
  	{
  		err = 1;
    		printf("\nError: Type not matched.\n");
  	}
}

void VarDec1List()
{
	Type();
  	match(s);
  	if(valid_ID(s)==true)
  	{
    		fseek(file,0,SEEK_CUR);
    		printf("\nValid variable\n");
  	}
  	else
  	{
  		err = 1;
    		printf("\nError: Not a valid variable\n");
  	}
  	match(s);
  	if(strcmp(s,";")==0)
  	{
  		return;
  	}
  	else if(strcmp(s,"[")==0)
  	{
  		match(s);
  		if(valid_num(s)==true)
  		{
  			match(s);
  			if(strcmp(s,"]")==0)
  			{
  				match(s);
			  	if(strcmp(s,";")==0)
			  	{
			    		return;
			  	}
			  	else
			  	{
			  		err = 1;
			  		printf("Error");
			  	}
			 }
			 else
			 {
			 	err = 1;
			 	printf("Error");
			 }
		}
		else
		{
			err = 1;
			printf("\nNot a valid number\n");
		}
	}	
  	else
  	{
  		err = 1;
    		printf("\nError in line %d\n",line);
  	}
}

void Program()
{
	VarDec1List();
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
		//printf("%d",valid_num("2"));
    		Program();
    		if(feof(file))
    		{
	    		if(err!=1)
      	    		{
		    		printf("\nProgram successfully executed\n");
	    		}
	    		else
	    		{
	    			printf("\nInvalid input\n");
	    		}
    		}
  	}
	fclose(file);
}
