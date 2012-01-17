#include <stdio.h>
#include <pthread.h>

#define mb() asm volatile("mfence":::"memory")

volatile char flag[2] = { 0, 0 };
volatile char turn    = 0;
volatile int  val     = 0;

void alert(int code, char* mes)
{
	printf(mes);
	exit(code);
}

static void* func( void* id ) 
{
	int self  = (int)id;
    	int other = 1 - self;
	volatile int countdown = 10000000;
    	
	while( countdown >= 0 ) 
   	{
		mb();
        	flag[self] = 1;
		mb();
       	 	while( flag[other] == 1 ) 
		{
            		mb();
			if( turn != self ) 
			{
                		mb();
				flag[self] = 0;
                		mb();
				while( turn != self );
                		mb();
				flag[self] = 1;
            		}
        	}
        	// critical section
		mb();
        	if( --countdown >= 0 ) 
		{
			mb();			
			val++;
		}
        	// end
		mb();
        	turn = other;
		mb();
	        flag[self] = 0;
		mb();
    	}
}

int main() 
{
    	
	cpu_set_t cpu1, cpu2;
	CPU_ZERO(&cpu1);
	CPU_SET(0, &cpu1);
	
	CPU_ZERO(&cpu2);
	CPU_SET(1 ,&cpu2);
	
	pthread_t thread[2];

	if(pthread_create(&thread[0], NULL, &func, (void*)0))
		alert(11,"create thread 1 error");
	if(pthread_create(&thread[1], NULL, &func, (void*)1))
		alert(21,"create thread 2 error");
    
	if (pthread_setaffinity_np(thread[0], sizeof(cpu_set_t), &cpu1))
		alert(10, "set affinity thread 1 error");	
	if (pthread_setaffinity_np(thread[1], sizeof(cpu_set_t), &cpu2))
		alert(10, "set affinity thread 2 error");	

	if(pthread_join(thread[0], NULL))
		alert(12,"join thread 1 error");
	if(pthread_join(thread[1], NULL))
		alert(22,"join thread 2 error");
	
	printf("%d\n", val);
	
    return 0;
}

