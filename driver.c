#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <netinet/in.h> 

#include "signal_generator.h"
#include "data_processor.h"
#include "udp_server.h"
#include "data_logging.h"
  
pthread_t tid[3];
int counter;
pthread_mutex_t lock;

int sockfd;
int len;
struct sockaddr_in cliaddr;

struct {
    sem_t init_finished;
    sem_t init_failed;
    sem_t init_processing;
    sem_t init_connected;
} shared;
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




void *thread_init_udp(void* arg) {
    // if (pthread_mutex_init(&lock, NULL) != 0) {
    //     printf("\n mutex init has failed\n");
    //     return 1;
    // }
    sem_wait(&shared.init_failed);
    sem_post(&shared.init_processing);
    init_udp();
    sem_post(&shared.init_finished);
    sem_post(&shared.init_connected);
    // pthread_mutex_destroy(&lock);
    // pthread_detach(pthread_self());
    // pthread_exit(NULL);
    return NULL;
}

void *thread_interrupt(void* arg) {
    sem_wait(&shared.init_finished);

    int freq = 10;
    int trigger = 1000 / freq;

    FILE *fp;
    fp = fopen("sensor_data.txt", "r");
    char *line = NULL;
    open_log();
    
    while (1)
    {
        int msec = 0;
        clock_t start = clock();
        while (msec < trigger) {
            clock_t difference = clock() - start;
            msec = difference * 1000 / CLOCKS_PER_SEC;
        }
        char *data = get_simulated_data(fp, line);
        if(data == NULL) break;
        interrupt_handler(data);
        // printf("Time taken %d seconds %d milliseconds \n",msec/1000, msec%1000);
        send_udp(data);
        msec = 0;
    }
    fclose(fp);
    close_log();
    if (line)
        free(line);
    // pthread_detach(pthread_self());
    sem_post(&shared.init_failed);
    // pthread_exit(NULL);
    return NULL;
}

void *thread_init_timeout(void* arg) {
    int trigger2 = 5000;

    sem_wait(&shared.init_processing);

    printf("Searching for data visualizer...\n");

    struct timespec ts;
    int error;
    error = clock_gettime(CLOCK_REALTIME, &ts);
    if (error != 0) {
        printf("Error: Get clock time failed\n");
        return NULL;
    }
    ts.tv_sec += 3;
    ts.tv_nsec = 0;

    error = sem_timedwait(&shared.init_connected, &ts);

    if (error != 0) {
        printf("No data visualizer found\n");
        sleep(1);
        pthread_cancel(tid[0]);
    }

    sem_post(&shared.init_finished);
    return NULL;
}

int main(void)
{
    int error;

    sem_init(&shared.init_failed, 0, 1); 
    sem_init(&shared.init_finished, 0, 0); 
    sem_init(&shared.init_processing, 0, 0); 
    sem_init(&shared.init_connected, 0, 0); 
  
    error = pthread_create(&(tid[0]),
                            NULL,
                            &thread_init_udp, NULL);
    if (error != 0)
        printf("\nThread 0 can't be created :[%s]",
                strerror(error));

    error = pthread_create(&(tid[1]),
                            NULL,
                            &thread_interrupt, NULL);
    if (error != 0)
        printf("\nThread 1 can't be created :[%s]",
                strerror(error));
  
    error = pthread_create(&(tid[2]),
                            NULL,
                            &thread_init_timeout, NULL);
    if (error != 0)
        printf("\nThread 2 can't be created :[%s]",
                strerror(error));

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_exit(NULL);
}