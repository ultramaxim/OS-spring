#include <stdio.h>
#include <unistd.h>//for pipe
#include <stdlib.h>
#include <signal.h>

int channel[2];

struct packet
{
	int number,signo,mypid,mygid,sender_pid,sender_gid,sender_uid;
};

void func(int i,siginfo_t *info,void *empty) 
{
	struct packet packet;
	packet.number = i;
	packet.signo = info->si_signo;
	packet.mypid = getpid();
	packet.mygid = getpgrp();
	packet.sender_pid = info->si_pid;
	packet.sender_gid = getpgid(info->si_pid);
	packet.sender_uid = info->si_uid;
	write(channel[1],&packet,sizeof(packet));
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
			return 3;
		}
	struct packet pack;
	do
	{
		int read_result=read(pair[0],&pack,sizeof(pack));
		if(read_result>0)
		{
			printf("-----------------------");
			printf("Signal %d\nsigno=%d\nmypid=%d\nmygid=%d\n",pack.number,pack.signo,pack.mypid,pack.mygid);
			printf("sender_pid=%d\nsender_gid=%d\nsender_uid=%d\n",pack.sender_pid,pack.sender_gid,pack.sender_uid);
			printf("-----------------------");
		}
		else if(read_result==-1)
		{
			puts("Read Error");
			return 4;
		}
		else
			d.number=-1
	}
	while(d.number != 20);

	return 0;
}
