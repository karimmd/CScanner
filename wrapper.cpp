#include <stdio.h>
#include <string.h>


/* STRCPY */
void _strcpy(int a, char b[], char c[])
{
      if (a != 4)   /*This means that the destination is statically allocated*/
      {
           int k;
        char action;
         k= strlen(c);
            
      if ( k > a)
      {
      
      throw MSG::msg(1);
      strncpy(b,c,a);
      b[a]= '\0';
      
  }
            
      else           
      strcpy (b,c);
  }
      else
      strcpy(b,c); /*when the destination is dynamically allocated (dest==4),then we use the original call*/    
      
  }
  
  
  /* STRCAT */
   
void _strcat(int a, char b[], char c[])
{
   if (a != 4)   
   
   {

      int k;
      char action;
      k= strlen(c);
      
      if ( k > a)
      
      {
      throw MSG::msg(1);
      strncat(b,c,a);
      b[a]= '\0';
      }
            
      else           
      strcat (b,c);
     }     
      else
      strcat(b,c);             
      
  }
  
  
  /* MEMCPY */

void _memcpy(int a, char b[], char c[],int d)
{
   if (a != 4)   
   
   {

      int k;
      char action;
      k= strlen(c);
      
      if ( k > a)
      
      {
      throw MSG::msg(1);
      memcpy(b,c,a);
      b[a]= '\0';
      }
            
      else           
      memcpy (b,c,d);
     }     
      else
      memcpy (b,c,d);             
      
  }
 
 
 /*BCOPY*/
 
void _bcopy(int a, char b[], char c[],int d)
{
   if (a != 4)   
   
   {

      int k;
      char action;
      k= strlen(c);
      
      if ( k > a)
      
      {
      throw MSG::msg(1);
      bcopy(b,c,a);
      b[a]= '\0';
      }
            
      else           
      bcopy (b,c,d);
     }     
      else
      bcopy (b,c,d);             
      
  }
 
 /*MEMCCPY*/
 
void _memcpy(int a, char b[], char c[],int d)
{
   if (a != 4)   
   
   {

      int k;
      char action;
      k= strlen(c);
      
      if ( k > a)
      
      {
      throw MSG::msg(1);
      memcpy(b,c,a);
      b[a]= '\0';
      }
            
      else           
      memcpy (b,c,d);
     }     
      else
      memcpy (b,c,d);             
      
  }
 
 /*MEMMOVE*/
 
void _memmove(int a, char b[], char c[],int d)
{
   if (a != 4)   
   
   {

      int k;
      char action;
      k= strlen(c);
      
      if ( k > a)
      
      {
      throw MSG::msg(1);
      memmove(b,c,a);
      b[a]= '\0';
      }
            
      else           
      memmove(b,c,d);
     }     
      else
      memmove (b,c,d);             
      
  } 
 
 /*MEMSET*/
 
 void _memset(int a, char b[], char c[],int d)
{
   if (a != 4)   
   
   {

      int k;
      char action;
      k= strlen(c);
      
      if ( k > a)
      
      {
      throw MSG::msg(1);
      memset(b,c,a);
      b[a]= '\0';
      }
            
      else           
      memset(b,c,d);
     }     
      else
      memset (b,c,d);             
      
  } 
      
 /*  exception handling messages  */         
 
 
  char* MSG::data[] = {
	  
	 "\nBad Argument to msg()\n", 
  
  "\nThe destination string buffer in strcpy is being exceeded by the source string\n by pressing 'y' the function will be rewritten with safe version.By pressing 'n' no action will be done! \n",
  
  "\nThe destination string buffer in strcat is being exceeded by the source string\n by pressing 'y' the function will be rewritten with safe version.By pressing 'n' no action will be done! \n",
  
  "\nThe destination string buffer in bcopy is being exceeded by the source string\n by pressing 'y' the function will be rewritten with safe version.By pressing 'n' no action will be done! \n",
    
  "\nThe destination string buffer in memcpy is being exceeded by the source string\n by pressing 'y' the function will be rewritten with safe version.By pressing 'n' no action will be done! \n",
    
    "\nThe destination string buffer in memccpy is being exceeded by the source string\n by pressing 'y' the function will be rewritten with safe version.By pressing 'n' no action will be done! \n",
    
    "\nThe destination string buffer in memmove is being exceeded by the source string\n by pressing 'y' the function will be rewritten with safe version.By pressing 'n' no action will be done! \n",
    
     "\nThe destination string buffer in memset is being exceeded by the source string\n by pressing 'y' the function will be rewritten with safe version.By pressing 'n' no action will be done! \n",
    
}
