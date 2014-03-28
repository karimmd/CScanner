#ifndef SAFELIB_H
#define SAFELIB_H
#include<stdio.h>
#include<string.h>

void strcpy(int a,char b[],char c[])
{ 
	int k;
	k=strlen(c);
	if (a==4)
	         strcpy(b,c);
	         
  else
  {   if (k>a)
	  {
		  strncpy(b,c,a);
		  b[a]= '\0';
		  
	}
	
	else
	       strcpy(b,c);
	       
	      }
}
	  

void _sstrcpy(char b[],char c[])
{
	int k;
	k=strlen(c);
	
	     if (k>4)
	     
	   {
		   strncpy(b,c,4);
		   b[k]= '\0';
		 }
		 else
		        strcpy(b,c);
}

void strcat(int a,char b[],char c[])
{
	 int k;
	 k=strlen(c);
	 if (a==4)
	          strcat (b,c);
	  else
	  {  if(k>a)
		  {
			  strncat(b,c,a);
			  b[a]='\0';
			}
			else
			     strcat(b,c);
		}
}	 
	
void _sstrcat(char b[],char c[])
{
	int k;
	k=strlen(c);
	       if(k>4)
	    {
			strncat(b,c,4);
			b[4]='\0';
		}
		else
		       strcat(b,c);
}

void memcpy(int a,char b[],char c[],int d)
{
	 if (a==4)
	          memcpy(b,c,d);
	  else
	  {  if(d>a)
		  {
			  memcpy(b,c,a);
			  b[a]='\0';
			
		  }
			else
			     memcpy(b,c,d);
		}
}	 
	
void _mmemcpy(char b[],char c[],int d)
{
	   if(d>4)
	    {
			memcpy(b,c,4);
			b[4]='\0';
		}
		else
		       memcpy(b,c,d);
}		       	   	      		 

		          
void bcopy(int a,char b[],char c[],int d)
{
	 if (a==4)
	          bcopy(b,c,d);
	  else
	  {  
		  if(d>a)
		  {
			  bcopy(b,c,a);
			  b[a]='\0';
			
		  }
			else
			     bcopy(b,c,d);
		}
}	 
	
void _bbcopy(char b[],char c[],int d)
{
	   if(d>4)
	    {
			bcopy(b,c,4);
			b[4]='\0';
		}
		else
		       bcopy(b,c,d);
}		          
		          

void memccpy(int a,char b[],char c[],int d,int e)
{
	 if (a==4)
	          memccpy(b,c,d,e);
	  else
	  {  
		  if(d>a)
		  {
			  memccpy(b,c,d,a);
			  b[a]='\0';
			
		  }
			else
			     memccpy(b,c,d,e);
		}
}	 
	
void _mmemccpy(int a,char b[],char c[],int d,int e)
{
	   if(e>4)
	    {
			memccpy(b,c,d,4);
			b[4]='\0';
		}
		else
		       memccpy(b,c,d,e);
}		


void memmove(int a,char b[],char c[],int d)
{
	 if (a==4)
	          memmove(b,c,d);
	  else
	  {  
		  if(d>a)
		  {
			  memmove(b,c,a);
			  b[a]='\0';
			
		  }
			else
			     memmove(b,c,d);
		}
}	 
	
void _mmemmove(char b[],char c[],int d)
{
	   if(d>4)
	    {
			memmove(b,c,4);
			b[4]='\0';
		}
		else
		       memmove(b,c,d);
}	

void memset(int a,char b[],int c,int d)
{
if(a==4)
        memset(b,c,d);
else
{
     if(d>a)
{
    memset(b,c,a);
    b[a]='\0';
}
else
    memset(b,c,d);

}
}
void _mmrmset(char b[],int c,int d)
{
  if(d>4)
    {
          memset(b,c,4);
          b[4]='\0';
     }
   else
         memset(b,c,d);
}

#endif
