#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

char info[100];

void term_handler(int i,siginfo_t *c,void *v) 
{
  write(1,info,strlen(info));
  
}

int main(int argc, char ** argv) 
{
  sigset_t sset;
  int sig;
  struct sigaction sa;
  sa.sa_handler = term_handler;
  sigaction(SIGTERM, &sa, 0);
  sigfillset(&sset);
  sigdelset(&sset, SIGTERM);
  sigprocmask(SIG_SETMASK, &sset, 0);
  printf("My pid is %i\n", getpid());
  while(!sigwait(&sset, &sig))
    printf("Signal %i - %s\n", sig, sys_siglist[sig]);
  return EXIT_SUCCESS;
}
