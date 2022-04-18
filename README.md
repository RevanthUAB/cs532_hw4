# Home Work 4 - Job Scheduler

## Description

The main aim of the homework four is to impelment a simple job scheduler the executes non-interactive jobs means these jobs run without the user interaction and only run in the background.

This job scheduler will only implement only the given number of programs at a time and the others are kept in waiting until the one of the preprogram is completed. 

And these jobs are non interactive so the errors and output of these programs are printed into the files with job id as their names that is associated with it.

Read keywords, command-line arguments, job scheduler, background processing, pid, threads, queue, c language.

### Prerequisites

Requirements for the software and other tools to build, test and push
- [Example 1]GCC compiler
- [Example 2]C language

## To Build the file

To compile the files 
    $ gcc -g -c -Wall inputedit.c
    $ gcc -g -c -Wall jobqueue.c 
    $ gcc -g -c -Wall schedulejob.c
    $ gcc -g inputedit.o jobqueue.o schedulejob.o -o jobq -lpthread
or simply
    $ make
        gives you the output with filename: jobq

## Running the tests


And to run the output file, Run the command lines as

    $./jobq <integer input>
        here <integer input> is the number of simultaneous programs you want to run at a time with a max upto to 8.

    The program will now move to the scheduler with the given parameters and the following commands are used to run the required programs.

    Enter Command> submit <command argument> <input> (input if necessary)
    Enter Command> showjobs
    Enter Command> submithistory

If there is a need to terminate the program then use either 'CNTL+c' or 'CNTL+\' to terminate the pprogram.

### Sample Tests

Samples of the program on the provided commands
Enter command> submit ./sleep 50
job 1 added to the queue
Enter command> submit ./sleep 50
job 2 added to the queue
Enter command> submit ./sleep 15
job 3 added to the queue
Enter command> submit ./sleep 45
job 4 added to the queue
Enter command> showjobs
jobid   command         status
1       ./sleep 50      working
2       ./sleep 50      working
3       ./sleep 15      waiting
4       ./sleep 45      waiting
Enter command> showjobs
jobid   command         status
1       ./sleep 50      working
2       ./sleep 50      working
3       ./sleep 15      waiting
4       ./sleep 45      waiting
Enter command> showjobs
jobid   command         status
2       ./sleep 50      working
3       ./sleep 15      working
4       ./sleep 45      waiting
Enter command> showjobs
jobid   command         status
3       ./sleep 15      working
4       ./sleep 45      working
Enter command> showjobs
jobid   command         status
4       ./sleep 45      working
Enter command> submithistory
jobid   command         starttime                       endtime                         status
1       ./sleep 50      Sat Apr 16 13:18:22 2022        Sat Apr 16 13:19:12 2022        success
2       ./sleep 50      Sat Apr 16 13:18:29 2022        Sat Apr 16 13:19:19 2022        success
3       ./sleep 15      Sat Apr 16 13:19:13 2022        Sat Apr 16 13:19:28 2022        success
Enter command> submithistory
jobid   command         starttime                       endtime                         status
1       ./sleep 50      Sat Apr 16 13:18:22 2022        Sat Apr 16 13:19:12 2022        success
2       ./sleep 50      Sat Apr 16 13:18:29 2022        Sat Apr 16 13:19:19 2022        success
3       ./sleep 15      Sat Apr 16 13:19:13 2022        Sat Apr 16 13:19:28 2022        success
4       ./sleep 45      Sat Apr 16 13:19:19 2022        Sat Apr 16 13:20:04 2022        success
Enter command>


## Authors

  - **Naresh Vaddempudi** - *CS 532* -
  [GitHub](https://github.com/NareshVaddempudi)
  - **Revanth Kari** - *CS 532* - 
  [GitHub](https://github.com/RevanthUAB/CS532_hw4)

## Acknowledgments

  - To execute the programs the given as command arguments execvp is used from the provided lab material
  - To run the programs in the queue manner, the queue.tar provided for the homework session is used.
  - Referenced websites are Tutorialspoint, Quora, Geeksforgeeks, linux,
  - stackoverflow, CSCMU, JournalDev.

[//]: #
  [tutorialspoint]:<https://www.tutorialspoint.com/multithreading-in-c>
  [Quora]:<https://www.quora.com/How-do-you-dynamically-allocate-an-array-of-struct-pointers-in-C>
  [geeksforgeeks]:<https://www.geeksforgeeks.org/exec-family-of-functions-in-c/>
  [EOF AND FEOF]:<https://www.geeksforgeeks.org/eof-and-feof-in-c/>
  [geeksforgeeks]:<https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/>
  [geeksforgeeks]:<https://www.geeksforgeeks.org/multithreading-c-2/>
  [stackoverflow]:<https://stackoverflow.com/questions/27541910/how-to-use-execvp>
  [stackoverflow]:<https://stackoverflow.com/questions/4184954/are-there-standard-queue-implementations-for-c>
  [JournalDev]:<https://www.journaldev.com/36220/queue-in-c#:~:text=A%20queue%20in%20C%20is,be%20removed%20from%20the%20array.>
  [Linux]:<https://linux.die.net/man/3/execvp>
  [CS CMU]:<https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html>