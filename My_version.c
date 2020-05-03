#include<stdio.h>
#include<string.h>
#include<stdbool.h>

FILE* file;
int eof = 0;

void match(char* string)
{
	fscanf(file,"%s",string);
	if(feof(file))
  	{
	//	printf("ERROR!!!\nEnd of FIle reached.\n");
	  	eof=1;
	  	return;
  	}
  	else
  	{
          	
	  	printf("%s  ",string);
  	}
}

bool valid_variable(char* s)
{
  	if(!(s[0]>='a' && s[0]<='z'))
  	{
    		return false;
  	}
  	for(int i=0;i<strlen(s);i++)
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
  	char s[100];
  	match(s);
  	if(strcmp(s,"int")==0 || strcmp(s,"char")==0)
  	{
    		//fseek(file,0,SEEK_CUR);
    		printf("\nType check successful\n");
  	}
  	else
  	{
    		printf("\nError: Type not matched.\n");
  	}
}

void VarDec1List()
{
	Type();
	char s[100];
  	match(s);
  	if(valid_variable(s)==true)
  	{
    		fseek(file,0,SEEK_CUR);
  	}
  	else
  	{
    		printf("\nError: Not a valid variable\n");
  	}
  	char s1[100];
  	match(s1);
  	if(strcmp(s1,";")==0)
  	{
    		return;
  	}
  	else
  	{
    		printf("\nError: ';' expected\n");
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
    		Program();
    	//	printf("****");
    	//	printf("^^^%c^^^",fgetc(file));
    		if(feof(file))
    		{
	//    		printf("****");
	    		if(eof==0)
      	    		{
		    		printf("\nProgram successfully executed\n");
	    		}
    		}
  	}
	fclose(file);
}
