#include <stdio.h> 
#include <string.h> 
#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h> 
  
pthread_t tid[2]; 
pthread_mutex_t mutex;
int counter; 
  
void* thread_func(void *arg) 
{ 
    unsigned long i = 0; 

    pthread_mutex_lock(&mutex);

    counter += 1; 
    printf("\n Thread %d has started\n", counter); 
  
    for(i=0; i<(0xFFFFFFFF);i++); 
    printf("\n Thread %d has finished\n", counter); 

    pthread_mutex_unlock(&mutex);
  
    return NULL; 
} 
  
int main(void) 
{ 
    int i = 0; 
    int error; 
    pthread_mutex_init(&mutex, NULL);

    while(i < 2) 
    { 
        error = pthread_create(&(tid[i]), NULL, &thread_func, NULL); 
        if (error != 0) 
            printf("\nThread can't be created : [%s]", strerror(error)); 
        i++; 
    } 
  
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
  
    return 0; 
}
