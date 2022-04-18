#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include<stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

typedef struct jstruct
{
    char *j_commands;
    char *j_status;   
    char *start_time; 
    char *stop_time;  
    char fdout[25]; 
    char fderr[25];
    int job_id; 
    int exit_status;       
    pthread_t thread_id;
} jstruct;

typedef struct queue
{
    int size;    
    jstruct **buffer; 
    int start;  
    int end;    
    int count;  
} queue;

int jobByJob;      
int jobRunning;    
jstruct JobArray[1000]; 
queue *JobWaiting;

jstruct job_generation(char *j_commands, int job_id);
void jobShowSubmit(jstruct *job, int k, char *ch, char *command);

queue *queue_init(int k);
int queue_insert(queue *q, jstruct *jobp_Pointer);
jstruct *queue_delete(queue *q);
void queue_destroy(queue *q);

char *copyInputString(char *str, int i);
bool nullSpaceChars(char chV);
char *firstCharPointer(char *str, int i);
int gettingTheInput( int k, char *str, int w);
char *newStringCopy(char *str, int i);
char *timeAndDateStr(char *nsc);
char **arguments(char *inputLine);
int writeLog(char *filename, int file_descriptor);

#endif
