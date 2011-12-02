#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#define BUF_SIZE 32

int main (int argc,char **argv) 
{
	if (argc<2) 
	{
		puts("Need more arguments");
		return 1;
	}
	fd_set fdset;
	FD_ZERO (&fdset);
	int i,max=0,arg[argc];

	for (i=1;i<argc;++i) 
	{
		arg[i] = strtol(argv[i],(char**)NULL,10);
        	if(arg[i]>max) max=arg[i];
        	FD_SET(arg[i],&fdset);
    	}

	char buf[BUF_SIZE];
	int done=1,bytes;
    	
	while(done<argc) 
    	{	
		if (select(max+1,&fdset,NULL,NULL,NULL)==-1) 
		{
			puts("bad descriptors");
	            	return 2;
        	}
        
	        for (i=1;i<argc;++i)
       			if(FD_ISSET(arg[i],&fdset)) 
	    		{
             			bytes=read(arg[i],buf,BUF_SIZE*sizeof(char));
                    		if (bytes<1) 
				{
                        		FD_CLR(arg[i],&fdset);
                        		++done;
                    		}
                    		else 
                        		write(1,buf,bytes);
            		}
    	}
    
    return 0;
}

