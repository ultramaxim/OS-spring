#include <stdio.h>
#include <pthread.h>

#define mb() asm volatile("mfence":::"memory")

volatile char flag[2] = { 0, 0 };
volatile char turn    = 0;
volatile int  val     = 0;

static void* func( void* id ) 
{
	int self  = (int)id;
    	int other = 1 - self;
	volatile int countdown = 100000000;
    	
	while( countdown >= 0 ) 
   	{
        	flag[self] = 1;
		mb();
       	 	while( flag[other] == 1 ) 
		{
            		if( turn != self ) 
			{
                		flag[self] = 0;
                		while( turn != self );
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
        	turn = other;
	        flag[self] = 0;
    	}
}

int main() {
    
	pthread_t thread[2];

	pthread_create(&thread[0], NULL, &func, (void*)0);
	pthread_create(&thread[1], NULL, &func, (void*)1);
    
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	
	printf("%d\n", val);
	
    return 0;
}

