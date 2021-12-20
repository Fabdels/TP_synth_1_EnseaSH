#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>




int main(void) {

	char buffer[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash%";


	write(0, buffer,sizeof(buffer));




  return 0;
}


