#include <sys/types.h> 
#include <unistd.h>
#include <stdio.h> 
#include <wait.h> 
#include <signal.h>
#include <stdlib.h> 

pid_t pid; 
int counter = 0;

void parentHandle() 
{ 
	printf(">> Enkokelehe\n");
	kill(pid, SIGINT); 
} 

void childHandle() 
{
	printf("<< Meneawkelehe\n");
    counter++;
    if(counter < 3){
kill(getppid(), SIGINT); 
    }else{
        exit(0);
    }
    
} 

int main() 
{ 
	pid_t p; 
	int status;

	signal(SIGINT, parentHandle); 
	if ((pid = fork()) == 0) 
	{ 
		signal(SIGINT, childHandle); 
		kill(getppid(), SIGINT); 
		while(1) ; 
	} 
	if ((p = wait(&status)) > 0) 
	{ 
		puts("Conversation Ends");
	} 
} 
