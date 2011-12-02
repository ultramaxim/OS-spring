#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

char info[100];

void term_handler(int i,siginfo_t *c,void *v) 
{
  	write(1,info,strlen(info));
  	if(i==2)
    		exit(0);
}

int main() 
{
  	sprinf(info,"PID: %d; GID %d\n",getpid(),getpgid(getpid()));
	write(1,info,strlen(info));
	
}
