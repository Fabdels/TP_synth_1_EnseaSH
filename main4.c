#include <stdlib.h>
#include<string.h>
#include <stdio.h>
#include <unistd.h>
#include<signal.h>
#include <sys/types.h>
#include <sys/wait.h>








int main(void) {



	// Initialisation et affichage du message d'accueil

	int status;

	char buffer[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.";


	write(0, buffer,sizeof(buffer));



	char prompt_buffer[] ="\nenseash";

	char buff_1[] ="";


	char input[100]={0};


	int size_input;


	pid_t pid;

	pid=1;




	write(0, prompt_buffer,sizeof(prompt_buffer));

	write(0, "%", sizeof("%"));









	


	while (1)

	{

		




		size_input=read ( 0 , input , sizeof(input) );





		// pid=0 correspond au fils,
		// ainsi on fait un fork()
		// seulement si pid!=0

		if (pid!=0){


		pid = fork();

		}

  		sleep(0.01);


		







		// Le fils s'occupe des commandes


	  	if (pid==0)
	  	{


				// Gestion des commandes

				 if(strncmp(input,"fortune", 7)==0)

				 {


					char affich_buffer[] ="Today is what happened to yesterday";

				 	write(0,affich_buffer,sizeof(affich_buffer));

				}


			exit(EXIT_SUCCESS);


		}






		else
		{


		// On affiche le statut de sortie

		wait(&status);


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


		// Exit si l'utilisateur écrit "exit" ou entre ctr+d

		 if((strncmp(input,"exit", 4)==0)||(size_input==0))
			{



				 if (pid!=0)
				{

				char affich_buffer[] ="\nBye bye...";

			 	 write(0,affich_buffer,sizeof(affich_buffer));

			 	}

				 break;

				 exit(EXIT_SUCCESS);

			}

		

	}



  return 0;
}
