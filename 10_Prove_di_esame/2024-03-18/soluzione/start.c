#include "header.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int pid;

	//TODO: creazione processo startPL
	pid = fork();
	if (pid == 0){
		execl("./startPL", "startPL" , NULL);
		die("execl");
	} else if (pid < 0){
		printf("Error \n");
	}

	//TODO: creazione processo startRL
	pid = fork();
	if (pid == 0){
		execl("./startRL", "startRL", NULL);
	} else if (pid < 0){
		printf("Error \n");
	}
	
	//TODO: attesa processi figlio
	while(wait(NULL)>0);
	
	return 0;
}	
