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


char *copyInputString(char *str, int i)
{
    int chV;
    char *duplicate = malloc(sizeof(char) * strlen(str));

    for(i;(chV = str[++i]) != '\0';)
    {
        duplicate[i] = chV;
    }
    duplicate[i] = '\0';
    return duplicate;
}

jstruct job_generation(char *j_commands, int job_id)
{
    jstruct genjob;
    genjob.job_id = job_id;
    genjob.exit_status = -1;
    genjob.j_commands = copyInputString(j_commands, -1);
    genjob.start_time = genjob.stop_time = NULL;
    genjob.j_status = "waiting";
    sprintf(genjob.fdout, "%d.out", genjob.job_id);
    sprintf(genjob.fderr, "%d.err", genjob.job_id);
    return genjob;
}



void jobShowSubmit(jstruct *job, int k, char *ch, char *command)
{
   
    if (job != NULL)
    {
    if (k != 0)
        {
            if (strcmp(command, "showjobs") ==0) 
            {
                printf("jobid\tcommand\t\t\tstatus\n");
                int i=0;
                while( i < k) 
                {
                    if (strcmp(job[i].j_status, "success") != 0)
                    {
                        printf("%d\t%s\t%s\n",job[i].job_id+1,job[i].j_commands,job[i].j_status);
                    }
                    i++;
                }
            }
            else if (strcmp(command, "submithistory") == 0) 
            {
                printf("jobid\tcommand\t\t\tstarttime\t\t\tendtime\t\t\t\tstatus\n");
                int i = 0;
                while(i < k)
                {
                    if (strcmp(job[i].j_status, "success") == 0)
                    {
                        printf("%d\t%s\t%s\t%s\t%s\n",job[i].job_id+1,job[i].j_commands,job[i].start_time,job[i].stop_time,job[i].j_status);
                    }
                    i++;
                }
            }
        }
    }
}

queue *queue_init(int k)
{
    queue *q = malloc(sizeof(queue));
    q->buffer = malloc(sizeof(jstruct *) * k);
    q->size = k;
    q->end = 0;
    q->start = 0;
    q->count = 0;

    return q;
}

int queue_insert(queue *q, jstruct *jobp_Pointer)
{
    if ((q == NULL) || (q->count == q->size))
        return -1;

    q->buffer[q->end % q->size] = jobp_Pointer;
    q->end = (q->end + 1) % q->size;
    q->count++;

    return q->count;
}

jstruct *queue_delete(queue *q)
{
    if ((q == NULL) || (q->count == 0))
        return (jstruct *)-1;

    jstruct *genjob = q->buffer[q->start];
    q->start = (q->start + 1) % q->size;
    q->count--;

    return genjob;
}

void queue_destroy(queue *q)
{
    free(q->buffer);
    free(q);
}

int gettingTheInput( int k, char *str, int w)
{
    int i, chV;
    for (i = 0; i < k - 1 && (chV = getchar()) != '\n'; ++i)
    {
        if (chV == EOF)
            return -1;
        str[i] = chV;
    }
    str[i] = '\0';
    return i;
    
}

bool nullSpaceChars(char chV)
{
    if( chV == '\n' ||chV == '\r' )
        return true;
    

    else if(chV == ' ' ||chV == '\t' ||chV == '\x0b' ||chV == '\x0c')
        return true;

    else return false;
}

char *firstCharPointer(char *str, int i)
{
    char *fcp;
        for(i=0; nullSpaceChars(str[i])==true;)
        {
            i++;
        }
    fcp = str + i;
    return fcp;
}



char *newStringCopy(char *str, int i)
{
    char *duplicate = malloc(sizeof(char) * strlen(str));;
    int  chV;

   
    for(i ;(chV = str[++i]) != '\0' && chV != '\n'; )
    {
        duplicate[i] = chV;
    }
    duplicate[i] = '\0';
    return duplicate;
}

char *timeAndDateStr(char *nsc)
{
    time_t timer = time(NULL);
    nsc=newStringCopy(ctime(&timer), -1);
    return nsc;
}

char **arguments(char *inputLine)
{
    char *duplicate = malloc(sizeof(char) * (strlen(inputLine) + 1));
    strcpy(duplicate, inputLine);

    char *arg;
    int i = 0;
    char **args = malloc(sizeof(char *));
    while ((arg = strtok(duplicate, " \t")) != NULL)
    {
        args[i] = malloc(sizeof(char) * (strlen(arg) + 1));
        strcpy(args[i], arg);
        args = realloc(args, sizeof(char *) * (++i + 1));
        duplicate = NULL;
    }
    args[i] = NULL;
    return args;
}
