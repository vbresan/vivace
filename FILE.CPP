#include "./include/file.h"
#include "./include/cnota.h"		// Nota

#include <ctype.h>		// isspace
#include <string.h>		// strchr
#include <stdlib.h>		// free

/*
*/

#define MAX_LINE_LENGHT		128
#define ACTUAL_MAX_LINE_LENGHT	MAX_LINE_LENGHT + 2

/*
*/

MFile::MFile()
 {
   fp = NULL;
 }

char MFile::open(char const * fName)
 {
   fp = fopen(fName,"rt");
   if(fp)
       return (TRUE);
   else
       return (FALSE);
 }


char MFile::close() const
 {
   if(!fclose(fp))
       return (TRUE);
   else
       return (FALSE);
 }


char MFile::process() const
 { unsigned int br_linije;
   char		ret_val;
   char   	achLinija[ACTUAL_MAX_LINE_LENGHT+1];
   char       * cpBuffer;

   ret_val = TRUE;
   br_linije = 0;
   cpBuffer = NULL;
   while(fgets(achLinija,ACTUAL_MAX_LINE_LENGHT,fp))
     {
       br_linije++;

       if(!cpBuffer)
           cut_leading_whitespace(achLinija);

       if(achLinija[0] != '\0')
         { char * cpWork;

           if((cpWork = strchr(achLinija,';')))
             {
               *cpWork = '\0';

               cpBuffer = strcat_ptrs(cpBuffer,achLinija);

               if(!obradi_buffer(cpBuffer,br_linije,ret_val))
                   ret_val = FALSE;

               delete [] cpBuffer;
               cpBuffer = NULL;
             }
           else
               cpBuffer = strcat_ptrs(cpBuffer,achLinija);

         } // ako postoji linija
     } // while(fgets)

   if(cpBuffer)
     {
       printf("(%i) %s\n",br_linije,TXT_IFERR2);

       delete [] cpBuffer;
       cpBuffer = NULL;

       ret_val = FALSE;
     }

   return (ret_val);
 }

/*
*/

char MFile::obradi_buffer(char     * cpBuffer,
                          int const  br_linije,
                          char const status) const
 { Nota          nota;
   int		 cNota;
   char        * cpTmpEnd,
   	       * cpTmpBgn;
   char		 tmp,
   		 ret_val;

   cut_trailing_whitespace(cpBuffer);

   ret_val = status;
   cNota = 0;
   cpTmpBgn = cpBuffer;
   while((cpTmpEnd = strchr(cpTmpBgn,',')))
     {
       *cpTmpEnd = '\0';
       cut_leading_whitespace(cpTmpBgn);
       cut_trailing_whitespace(cpTmpBgn);

       tmp = nota.set_from_str(cpTmpBgn);
       cNota++;

       if(tmp == ERR_SYNTX1 )
         {
           printf("(%i) %s (%i)!\n",br_linije,TXT_IFERR3,cNota);
           ret_val = FALSE;
         }
       else if(tmp == ERR_SYNTX2)
         {
           printf("(%i) %s (%i)!\n",br_linije,TXT_IFERR4,cNota);
           ret_val = FALSE;
         }
       if(!tmp && ret_val)
         {
           nota.play();
         }

       cpTmpBgn = cpTmpEnd+1;
     }
   cut_leading_whitespace(cpTmpBgn);
   cut_trailing_whitespace(cpTmpBgn);
   tmp = nota.set_from_str(cpTmpBgn);
   cNota++;

   if(tmp == ERR_SYNTX1 )
     {
       printf("(%i) %s (%i)!\n",br_linije,TXT_IFERR3,cNota);
       ret_val = FALSE;
     }
   else if(tmp == ERR_SYNTX2)
     {
       printf("(%i) %s (%i)!\n",br_linije,TXT_IFERR4,cNota);
       ret_val = FALSE;
     }
   if(!tmp && ret_val)
     {
       nota.play();
     }

   return (ret_val);
 }


void MFile::cut_leading_whitespace(char * linija) const
 { char * cpWork;

   cpWork = linija;
   while(isspace(*cpWork))
       cpWork++;
   strcpy(linija,cpWork);
 }


void MFile::cut_trailing_whitespace(char * linija) const
 { char * cpWork;

   cpWork = linija + strlen(linija);
   cpWork--;
   while(isspace(*cpWork) && cpWork >= linija)
       *cpWork-- = '\0';
 }


char * MFile::strcat_ptrs(char       * cpDest,
                          char const * cpSource) const
 {
   if(cpDest)
     { char * cpTmp;

       cpTmp = strdup(cpDest);     // kopiraj string iz buffera u tmp

       delete [] cpDest;       	   // oslobodi buffer
       cpDest = new char [(unsigned int) (strlen(cpTmp) +
                                          strlen(cpSource))+1];

       strcpy(cpDest,cpTmp);       // kopiraj tmp u buffer
       strcat(cpDest,cpSource);    // dodaj liniju bufferu

       free(cpTmp);                // oslobodi tmp
     }
   else
     {
       cpDest = new char [(unsigned int) strlen(cpSource)+1];
       strcpy(cpDest,cpSource);
     }

   return (cpDest);
 }

