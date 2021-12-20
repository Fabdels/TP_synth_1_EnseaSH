#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<string.h>





int main(void) {

	char buffer[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.";


	write(0, buffer,sizeof(buffer));



	char prompt_buffer[] ="\nenseash%";


	char input[100]={0};
	


	while (1)

	{

	write(0, prompt_buffer,sizeof(prompt_buffer));

	

	read ( 0 , input , sizeof(input) );


	 if(strncmp(input,"fortune", 7)==0)
	 {


		char affich_buffer[] ="Today is what happened to yesterday";

	 	write(0,affich_buffer,sizeof(affich_buffer));

	}

	

}



  return 0;
}
