#include <stdio.h>
#include <pthread.h>

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
	volatile int countdown = 100000000;
    	
	while( countdown >= 0 ) 
   	{
        	flag[self] = 1;
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
        	if( --countdown >= 0 ) val++;
        	// end
        	turn = other;
	        flag[self] = 0;
    	}
}

int main() {
    
	pthread_t thread[2];

	if(pthread_create(&thread[0], NULL, &func, (void*)0))
		alert(11,"create thread 1 error");
	if(pthread_create(&thread[1], NULL, &func, (void*)1))
		alert(21,"create thread 2 error");
    
	if(pthread_join(thread[0], NULL))
		alert(10,"join thread 1 error");
	if(pthread_join(thread[1], NULL))
		alert(20,"join thread 2 error");
	
	printf("%d\n", val);
	
    return 0;
}

