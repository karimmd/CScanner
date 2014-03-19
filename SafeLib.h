#ifndef SAFELIB_H
#define SAFELIB_H
#include<stdio.h>
#include<string.h>

void Sstrcpy(int a,char b[],char c[])
{ 
	int k;
	k=strlen(c);
	if (a==4)
	         strcpy(b,c);
	         
  else
  {   if (k>a)
	  {
		  strncpy(b,c,a);
		  b[a]='\0';
		  
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
		   b[4]='\0';
		 }
		 else
		        strcpy(b,c);
}


void Sstrcat(int a,char b[],char c[])
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

void Mmemcpy(int a,char b[],char c[],int d)
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

		          
/*void Bbcopy(int a,char b[],char c[],int d)
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
 */
void Mmemccpy(int a,char b[],char c[],int d,int e)
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


void Mmemmove(int a,char b[],char c[],int d)
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

void Mmemset(int a,char b[],int c,int d)
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
  /*  
char Sstrecpy(int a, char b[],char c[],char d[])
{
if (a==4)
  return strecpy(b,c,d);
else
{
    int k;
    k=strlen(c);
    if(k>a)
    {
     strncpy(b,c,a);
     b[a]='\0';	
     return strecpy(b,c,d);	     
    }
    else 
	return strecpy(b,c,d);
}
}
char _sstrecpy(char b[],char c[],char d[])
{
    int k;
    k=strlen(c);
    if(k>4)
	{ 
	strncpy(b,c,4);
	b[4]='\0';
	return strecpy(b,c,d);
	}
	else
	return strecpy(b,c,d);
}
char Sstreadd(int a, char b[],char c[],char d[])
{
if (a==4)
return streadd(b,c,d);
else
{   int k;
    k=strlen(c);
    if(k>a)	{
	 strncpy(b,c,a);
	 b[a]='\0';
	 return streadd(b,c,d);
	}
	else
	return streadd(b,c,d);
	
	}
}
char _sstreadd(char b[],char c[],char d[])
{
    int k;
    k=strlen(c);
    if(k>4)
	{
	strncpy(b,c,4);
	b[4]='\0';
	return streadd(b,c,d);
	}
	else
	return streadd(b,c,d);

}
char Sstrccpy(int a, char b[],char c [])
{
   int k;
   k=strlen(c);
   if (a==4)
   return strccpy(b,c);
    else
       {
     if(k>a)	{
	   strncpy(b,c,a);
	   b[a]='\0';
	   return strccpy(b,c);
	}
	else
	return strccpy(b,c);
	}
}
char _sstrccpy(char b[],char c[])
{
    int k;
    k=strlen(c);
    if(k>4)
	{
	    strncpy(b,c,4);
	    b[4]='\0';
	    return strccpy(b,c);
	}
	else
	return strccpy(b,c);
}
*/
#endif
