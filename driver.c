#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "signal_generator.h"
#include "data_processor.h"
  
pthread_t tid[2];
int counter;
pthread_mutex_t lock;
  
// void* trythis(void* arg)
// {
//     pthread_mutex_lock(&lock);
  
//     unsigned long i = 0;
//     counter += 1;
//     printf("\n Job %d has started\n", counter);
  
//     for (i = 0; i < (0xFFFFFFFF); i++)
//         ;
  
//     printf("\n Job %d has finished\n", counter);
  
//     pthread_mutex_unlock(&lock);
  
//     return NULL;
// }

void *thread_Interrupt(void* arg) {
    int freq = 2;
    int trigger = 1000 / freq;
    
    FILE *fp;
    fp = fopen("sensor_data.txt", "r");
    char *line = NULL;
    while (1)
    {
        int msec = 0;
        clock_t start = clock();
        while ( msec < trigger ) {
            clock_t difference = clock() - start;
            msec = difference * 1000 / CLOCKS_PER_SEC;
        }
        interrupt_Handler(signal_Simulator(fp, line));
        // printf("Time taken %d seconds %d milliseconds \n",msec/1000, msec%1000);
        msec = 0;
    }
    fclose(fp);
    if (line)
        free(line);
    
    
}
  
int main(void)
{
    int i = 0;
    int error;
  
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
  
    // while (i < 2) {
    //     error = pthread_create(&(tid[i]),
    //                            NULL,
    //                            &trythis, NULL);
    //     if (error != 0)
    //         printf("\nThread can't be created :[%s]",
    //                strerror(error));
    //     i++;
    // }
    // tid[2].argv_string = 
    error = pthread_create(&(tid[2]),
                            NULL,
                            &thread_Interrupt, NULL);
    if (error != 0)
        printf("\nThread can't be created :[%s]",
                strerror(error));
  
    // pthread_join(tid[0], NULL);
    // pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_mutex_destroy(&lock);
  
    return 0;
}