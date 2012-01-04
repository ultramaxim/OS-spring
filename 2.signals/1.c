#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

char info[100];

void func(int i,siginfo_t *c,void *v) 
{
  	write(1,info,strlen(info));
  	if(i==2)
    		exit(0);
}

int main() 
{
  	sprintf(info,"PID: %d; GID %d\n",getpid(),getpgid(getpid()));
	write(1,info,strlen(info));
	
	struct sigaction sa;
	sa.sa_sigaction=func;
	sa.sa_flags=SA_SIGINFO;
	if(sigfillset(&sa.sa_mask)==-1)
	{
		puts("Can't set sa_mask");
		return 1;
	}	
	
	int i;
	for(i=1;i<32;i++)
		if(i!=9 && i!=19 && sigaction(i,&sa,NULL))
		{
			printf("Error: %d\n",i);
			return 2;
		}

	while(1) sleep(1);

	return 0;
}
