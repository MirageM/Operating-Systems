/* ------------------------------------------------ ------------
File: cpr.c

Name: Mirage Mohammad


Description: This program contains the code for creation
 of a child process and attach a pipe to it.
	 The child will send messages through the pipe
	 which will then be sent to standard output.

Explanation of the zombie process
(point 5 of "To be completed" in the assignment):
 Answer:

Zombie Process is a child process that has finished its execution but still sticks around in the process table, waiting
to be reaped by the parent process. Usually, the parent process checks on their child’s process by calling wait or
waitpid, which the kernel deletes the zombie process but if the parent fails to call wait, the process entry table
sticks around and that’s what makes it a zombie. A single zombie process wouldn’t pose a threat but a built-up of zombie
processes would slow down the operating system.


	(please complete this part);

------------------------------------------------------------- */
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


/* Prototype */
void createChildAndRead (int);

/* -------------------------------------------------------------
Function: main
Arguments:
	int ac	- number of command arguments
	char **av - array of pointers to command arguments
Description:
	Extract the number of processes to be created from the
	Command line. If an error occurs, the process ends.
	Call createChildAndRead to create a child, and read
	the child's data.
-------------------------------------------------- ----------- */
//ac is the (argument count)
//**av is the array of string pointers (argument vector)
int main (int ac, char **av)
{
 int processNumber;

 if (ac == 2)
 {
 if (sscanf (av [1], "%d", &processNumber)== 1)
 {
    createChildAndRead(processNumber);
 }
    else fprintf(stderr, "Cannot translate argument\n");
 }
    else fprintf(stderr, "Invalid arguments\n");
    return (0);
}


/* ------------------------------------------------ -------------
Function: createChildAndRead
Arguments:
	int prcNum - the process number
Description:
	Create the child, passing prcNum-1 to it. Use prcNum
	as the identifier of this process. Also, read the
	messages from the reading end of the pipe and sends it to
	the standard output (df 1). Finish when no data can
	be read from the pipe.
-------------------------------------------------- ----------- */
//Note to self
//strlen() is a function that calculates the length of a string
//stderr stands for standard error
//Character array for writing
char message[] = "Message Text";

void createChildAndRead(int prcNum)
{
    //fd[0] (pipe) - read
    //fd[1] (pipe) - write
    //contains two file descriptors
    //standard input, standard output, and standard error are three descriptors that refer to the terminal

    //first pipe
    int pipe1[2];
    pipe(pipe1);//creating pipe

    //second pipe
    int pipe2[2];
    pipe(pipe2);//creating pipe

    int length1, length2; //message length  and string length


    if(prcNum == 1)
    {
        //change to write
        //Writes to its standard output
        fprintf(stderr,"Process %d begins \n", prcNum);//messages to the terminal

        //waits 5 seconds using sleep(5)
        sleep(5);

        fprintf(stderr, "Process %d ends\n", prcNum); // messages to the terminal
        //write(STDOUT_FILENO, buffer, length1);
    }
    else{

        //pid_t stands for process identification
        //pid represents process ids which is a signed integer type
        pid_t pid;

        fprintf(stderr, "Process %d begins \n", prcNum); //messages to the terminal


        //forking (creating the process)
        pid = fork();

        //if process id is greater than 0 then it's a parent
        //Child Process
        if(!(pid > 0))
        {
            char buffer[99];
            close(pipe1[1]);
            dup(pipe1[1]);


            //reading from first pipe
            read(pipe1[0],buffer,99);

            //close the read end of both pipes
            close(pipe2[0]);
            close(pipe1[0]);


            length2 = strlen(buffer)+1;

            //writing to second pipe
            write(pipe2[1],buffer,length2);
            close(pipe2[1]);
            dup(pipe2[1]);
            //n is the number of processes to be created
            //(n-1) children
            //(cpr num-1 command)
            createChildAndRead(prcNum-1); //Recursive call



        }
        else if(pid < 0){
            fprintf(stderr, "Error creating the pipe \n");
            exit(EXIT_FAILURE); //returns unsuccessful termination
        }
        //Parent Process
        else
            {

                char buffer[99];
                close(pipe1[0]); //closing the pipe (closes read end)
                dup(pipe1[0]);

                length1 = strlen(message)+1;

                //writing to first pipe
                write(pipe1[1],message, length1);
                close(pipe1[1]);
                dup(pipe1[1]);
                fprintf(stderr,"Message is written to the pipe (Process %d) \n", prcNum);

                //wait for child to execute
                wait(NULL);

                close(pipe2[1]);
                dup(pipe2[1]);

                //reading from second pipe
                read(pipe2[0],buffer,99);
                fprintf(stderr,"Message reads (%s) from the pipe (Process %d)   \n", buffer, prcNum);
                close(pipe2[0]);
                dup(pipe2[0]);
                fprintf(stderr,"Process %d ends \n", prcNum);
                sleep(5);

        }
            /*
            //Zombie Process
            close(pipe1[0]);

            fprintf(stderr,"Process %d ends \n", prcNum);
            //sleep 10 seconds to observe zombie processes
            sleep(10);
             */

    //dup() -> takes one parameter and duplicates
    //dup2() -> takes two parameter and replaces a file descriptor

    }
//Finished Assignment - Mirage
//Delete all dup*
 /* Please complete this function according to the
Assignment instructions. */
}



