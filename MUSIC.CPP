#include "./include/music.h"

#include <pc.h>		// sound, nosound NA
#include <dos.h>	// delay          NA
#include <string.h>	// strchr, strcmp
#include <stdlib.h>	// atoi
#include <stdio.h>	// printf

/*
*/

Nota::Nota(unsigned char const n_vi,
           float const	       n_tr)
 {
   visina = n_vi;
   trajanje = n_tr;
 }


char Nota::set_from_str(char * cpFrom)
 { char * cpWork;

   /* trajanje note
   */
   cpWork = strchr(cpFrom,'_');
   if(!cpWork)
       trajanje = 4;
   else
     { unsigned int brojnik,
      		    nazivnik;

       *cpWork = '\0';

       cpWork++;
       brojnik = atoi(cpWork);

       if((cpWork = strchr(cpWork,'/')))
           nazivnik = atoi(++cpWork);
       else
           nazivnik = 1;

       if(!brojnik || !nazivnik)
           return (ERR_SYNTX2);

       trajanje = (float) brojnik/nazivnik;
     }

   /* visina note
   */
   if(!strcmp(cpFrom,"c1"))
       visina = N_c1;
   else if(!strcmp(cpFrom,"d1"))
       visina = N_d1;
   else if(!strcmp(cpFrom,"e1"))
       visina = N_e1;
   else if(!strcmp(cpFrom,"f1"))
       visina = N_f1;
   else if(!strcmp(cpFrom,"g1"))
       visina = N_g1;
   else if(!strcmp(cpFrom,"a1"))
       visina = N_a1;
   else if(!strcmp(cpFrom,"h1"))
       visina = N_h1;

   else if(!strcmp(cpFrom,"c2"))
       visina = N_c2;
   else if(!strcmp(cpFrom,"d2"))
       visina = N_d2;
   else if(!strcmp(cpFrom,"e2"))
       visina = N_e2;
   else if(!strcmp(cpFrom,"f2"))
       visina = N_f2;
   else if(!strcmp(cpFrom,"g2"))
       visina = N_g2;
   else if(!strcmp(cpFrom,"a2"))
       visina = N_a2;
   else if(!strcmp(cpFrom,"h2"))
       visina = N_h2;

   else if(!strcmp(cpFrom,"c3"))
       visina = N_c3;
   else if(!strcmp(cpFrom,"d3"))
       visina = N_d3;
   else if(!strcmp(cpFrom,"e3"))
       visina = N_e3;
   else if(!strcmp(cpFrom,"f3"))
       visina = N_f3;
   else if(!strcmp(cpFrom,"g3"))
       visina = N_g3;
   else if(!strcmp(cpFrom,"a3"))
       visina = N_a3;
   else if(!strcmp(cpFrom,"h3"))
       visina = N_h3;

   else if(!strcmp(cpFrom,"c4"))
       visina = N_c4;
   else if(!strcmp(cpFrom,"d4"))
       visina = N_d4;
   else if(!strcmp(cpFrom,"e4"))
       visina = N_e4;
   else if(!strcmp(cpFrom,"f4"))
       visina = N_f4;
   else if(!strcmp(cpFrom,"g4"))
       visina = N_g4;
   else if(!strcmp(cpFrom,"a4"))
       visina = N_a4;
   else if(!strcmp(cpFrom,"h4"))
       visina = N_h4;
   else if(!strcmp(cpFrom,"P"))
       visina = N_P;
   else
       return (ERR_SYNTX1);

   return (ERR_SYNTX0);
 }


void Nota::play() const
 {
   switch(visina)
     {
       case N_P:
            sound(0);
            break;

       case N_c1:
            sound(NS_c1);
            break;
       case N_d1:
            sound(NS_d1);
            break;
       case N_e1:
            sound(NS_e1);
            break;
       case N_f1:
            sound(NS_f1);
            break;
       case N_g1:
            sound(NS_g1);
            break;
       case N_a1:
            sound(NS_a1);
            break;
       case N_h1:
            sound(NS_h1);
            break;

       case N_c2:
            sound(NS_c2);
            break;
       case N_d2:
            sound(NS_d2);
            break;
       case N_e2:
            sound(NS_e2);
            break;
       case N_f2:
            sound(NS_f2);
            break;
       case N_g2:
            sound(NS_g2);
            break;
       case N_a2:
            sound(NS_a2);
            break;
       case N_h2:
            sound(NS_h2);
            break;

       case N_c3:
            sound(NS_c3);
            break;
       case N_d3:
            sound(NS_d3);
            break;
       case N_e3:
            sound(NS_e3);
            break;
       case N_f3:
            sound(NS_f3);
            break;
       case N_g3:
            sound(NS_g3);
            break;
       case N_a3:
            sound(NS_a3);
            break;
       case N_h3:
            sound(NS_h3);
            break;

       case N_c4:
            sound(NS_c4);
            break;
       case N_d4:
            sound(NS_d4);
            break;
       case N_e4:
            sound(NS_e4);
            break;
       case N_f4:
            sound(NS_f4);
            break;
       case N_g4:
            sound(NS_g4);
            break;
       case N_a4:
            sound(NS_a4);
            break;
       case N_h4:
            sound(NS_h4);
            break;

       default:
            printf("\nInterna greska, obavijesiti o ovome programera!");
            exit(13);
            break;
     }
   delay((unsigned int) (trajanje*1000));
   nosound();
 }

