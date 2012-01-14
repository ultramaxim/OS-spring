#include <stdio.h>
#include<unistd.h>//for pipe
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int channel[2];

void func(int i,siginfo_t *c,void *v) 
{
	
}

int main() 
{
  	if(pipe(channel)==-1)
	{
		puts("Can't create pipe");
		return 1;
	}
	struct sigaction sa;
	sa.sa_sigaction=func;
	sa.sa_flags=SA_SIGINFO;
	if(sigfillset(&sa.sa_mask)==-1)
	{
		puts("Can't set sa_mask");
		return 2;
	}
	int i;
	for(i=1;i<32;i++)
		if(i!=9 && i!=19 && sigaction(i,&sa,NULL))
		{
			printf("Can't set signal %d\n",i);
			return 3\;
		}

	while(1) sleep(1);

	return 0;
}
