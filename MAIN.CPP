#include "./include/main.h"
#include "./include/cmfile.h"		// Mfile

/*
*/

int main(int argc, char *argv[])
 { int ret_val;

   printf(TXT_INFO);
   ret_val = NO_ERR;

   if(argc != 2)
     {
       printf(TXT_USAGE);
       ret_val = ERR_CMND_LINE;
     }
   else
     { MFile mfile;

       if(mfile.open(argv[1]))			// otvori datoteku
         {
           if(!mfile.process())              	// obradi datoteku
             {
               printf("\n%s\n\n",TXT_ERRFSYNTAX);
               ret_val = ERR_IFS;
             }
       	   if(!mfile.close())                	// zatvori datoteku
             {
               printf("\n%s\n\n",TXT_ERRFCLOSE);
               ret_val = ERR_IFC;
             }
         }
       else
         {
           printf(TXT_ERRFOPEN);
           ret_val = ERR_IFO;
         }
     }

   if(ret_val == NO_ERR)
       printf(TXT_OK);

   return (ret_val);
 }
