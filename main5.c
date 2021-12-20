#include <stdlib.h>
#include<string.h>
#include <stdio.h>
#include <unistd.h>
#include<signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>








int main(void) {

	// Initialisation des variables et affichage du message d'accueil

	int status;
	int accum=0;
	char buffer[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.";
	char prompt_buffer[] ="\nenseash";
	char buff_1[] ="";
	char input[100]={0};
	int size_input;
	pid_t pid;
	pid=1;
 	

	write(0, buffer,sizeof(buffer));
	

	write(0, prompt_buffer,sizeof(prompt_buffer));
	write(0, "%", sizeof("%"));




	//Initialisation de la clock

	struct timespec c_start,c_end;
	#define BILLION  1000000000;

	
	
	
//Boucle constituant la base du shell

	while (1)

	{
		size_input=read ( 0 , input , sizeof(input) );


		/* pid=0 correspond au fils, ainsi on fait un fork()

		seulement si pid!=0 et si l'utilisateur	a écrit quelque chose.

		 */


		if ((pid!=0) & (size_input!=0)){
		pid = fork();
		
		}


		
		// Le fils s'occupe d'executer les commandes
	  	if (pid==0)

	  	{	
	  		// Récupération du temps au début du traitement

  			clock_gettime(CLOCK_REALTIME, &c_start);














			
			// Gestion des commandes

			
			 if(strncmp(input,"fortune\n", 8)==0)
			 {
				

				char affich_buffer[] ="Today is what happened to yesterday\n";
			 	write(0,affich_buffer,sizeof(affich_buffer));
				
			}













			/* Récupération du temps à la fin du traitement
			   et affichage du temps écoulé en ms*/
	  		
			clock_gettime(CLOCK_REALTIME, &c_end);

		 	accum =( c_end.tv_nsec - c_start.tv_nsec )/1000;

			printf( "[%d μs]\n", accum );

			exit(EXIT_SUCCESS);
		}



		// Exit si l'utilisateur écrit "exit" ou entre ctr+d

		 if((strncmp(input,"exit\n", 5)==0)||(size_input==0))
			{
				 if (pid!=0)
				{
					char affich_buffer[] ="\nBye bye...\n";
					write(0,affich_buffer,sizeof(affich_buffer));
				 	
			 	}
				 break;
				 exit(EXIT_SUCCESS);
			}




		if (pid!=0)
		{


		// On attend la mort d'un fils
		
		wait(&status);


		// On affiche le statut de sortie


			if (WIFEXITED(status))
			{
				buff_1[0]=WEXITSTATUS(status)+'0';
				
				write(0, prompt_buffer, sizeof(prompt_buffer));
				write(0, " [exit : ", sizeof("[exit : "));
				write(0, buff_1, sizeof(buff_1));
				write(0, "] ", sizeof("] "));

				write(0, "%", sizeof("%"));
			}
			else if (WIFSIGNALED(status)){
				buff_1[0]=WEXITSTATUS(status)+'0';
				write(0, prompt_buffer, sizeof(prompt_buffer));
				write(0, " [sign : ", sizeof("[sign : "));
				write(0, buff_1, sizeof(buff_1));
				write(0, "] ", sizeof("] "));
				write(0, "%", sizeof("%"));
			}


		}
		

			size_input=0;

		/* La remise à 0 de size_input permet de ne pas générer

			de fils tant que l'utilisateur n'a rien écrit 

		 */

	}


  return 0;
}
