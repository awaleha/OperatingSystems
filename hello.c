#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int queryNo[3]={1011,1012,1013};
int total_queries = 0;

void *PrintHello(void *threadid)
{
   int i;
   int q = (int)(long)threadid;
   for (i=0;i<queryNo[q];i++) { //handle queries
       total_queries=total_queries+1;
   }
   _exit(0);
}

int main(int argc, char *argv[])
{
   pthread_t threads[3];
   int rc;
   long t;
   for(t=0;t<3;t++){
     printf("In main: creating thread %ld\n", t);
     rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
     if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
     }
   printf("%d total_queries should be 3036 and it is %d\n",getpid(), total_queries);

   /* Last thing that main() should do */
   pthread_exit(NULL);
}