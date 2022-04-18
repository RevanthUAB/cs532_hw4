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


int writeLog(char *filename, int file_descriptor)
{
    file_descriptor= open(filename, O_CREAT | O_APPEND | O_WRONLY, 0755);
    if (file_descriptor == -1)
    {
        fprintf(stderr, "Opening the file failed. Check permissions \"%s\"\n", filename);
        perror("open");
        exit(1);
    }
    return file_descriptor;
}

void *proc_done(void *arg)
{
    pid_t pid;   
    char **args; 
     jstruct *jobp_Pointer;

    jobp_Pointer = (jstruct *)arg;

    jobRunning++;
    jobp_Pointer->j_status = "working";
    jobp_Pointer->start_time = timeAndDateStr(NULL);

    pid = fork();
    if (pid == 0) 
    {
        dup2(writeLog(jobp_Pointer->fdout,0), 1); 
        dup2(writeLog(jobp_Pointer->fderr,0), 2); 
        args = arguments(jobp_Pointer->j_commands);
        execvp(args[0], args); 
        fprintf(stderr, "Executing the command failed: \"%s\"\n", args[0]);
        perror("execvp");
        exit(1);
    }
    else if (pid > 0) 
    {
        waitpid(pid, &jobp_Pointer->exit_status, WUNTRACED); 
        jobp_Pointer->j_status = "success";
        jobp_Pointer->stop_time = timeAndDateStr(NULL);

        if (!WIFEXITED(jobp_Pointer->exit_status)) 
            fprintf(stderr, "Child process %d did not terminate normally!\n", pid);
    }
    else
    {
        fprintf(stderr, "Error: Forking process failed\n");
        perror("fork");
        exit(1);
    }

    jobRunning--;
    return NULL;
}

void *proc_success(void *args)
{
    jstruct *jobp_Pointer;
    jobRunning = 0;
    while(true)
    {
        if (JobWaiting->count > 0)
        {
            if(jobByJob>jobRunning)
            {
                jobp_Pointer = queue_delete(JobWaiting);
                pthread_create(&jobp_Pointer->thread_id, NULL, proc_done, jobp_Pointer);
                pthread_detach(jobp_Pointer->thread_id);
            }
        }
        sleep(1); 
    }
    return NULL;
}



int main(int argc, char **argv)
{
    printf("To quit the Program Please Press 'CNTL+%c'\n",92);
    int i = 0;              
    char inputLine[1000]; 
    char *kw, *c=NULL;           
    char *j_commands;
    jstruct *jobp_Pointer;

    char *fderr;  
    pthread_t thread_id; 

    if (argc != 2)
    {
        printf("Usage: %s Number of simultanious processes\n", argv[0]);
        exit(0);
    }


    jobByJob = atoi(argv[1]);

    jobByJob < 1?jobByJob = 1:jobByJob;

    jobByJob > 8?jobByJob = 8:jobByJob;


    fderr = malloc(sizeof(char) * (strlen(argv[0]) + 7));
    sprintf(fderr, "%s.err", argv[0]);
    dup2(writeLog(fderr,0), 2);

    JobWaiting = queue_init(100);

    pthread_create(&thread_id, NULL, proc_success, NULL);

    while (printf("Enter command> ") && gettingTheInput(1000, inputLine, 0) != -1)
    {
        if ((kw = strtok(copyInputString(inputLine, -1), " \t\n\r\x0b\x0c")) != NULL) 
        {
            if (strcmp(kw, "submit") == 0) 
            {
                if (i >= 1000)
                {
                    printf("You have submitted the max number of jobs. Rerun the program to operate on more\n");
                }
                else if (JobWaiting->count >= JobWaiting->size)
                {
                    printf("Max Queue of jobs are submitted. Please wait for them to complete\n");
                }
                else
                {
                    j_commands = firstCharPointer((strstr(inputLine, "submit") + 6), 0);
                    JobArray[i] = job_generation(j_commands, i);
                    queue_insert(JobWaiting, JobArray + i);
                    printf("job %d added to the queue\n", (i++)+1);
                }
            }
            else if (strcmp(kw, "showjobs") == 0 || strcmp(kw, "submithistory") == 0)
            {
                jobShowSubmit(JobArray, i, c, kw);
            }
        }
    }
    kill(0, 2); 

    exit(0);
}