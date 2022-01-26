#include "types.h"
#include "stat.h"
#include "user.h"
#include <stddef.h>
#define CHILDREN_NUMBER 10

void run(int pid) {
    int i;
    for (i = 0; i < 10; ++i){
        printf(1, "%d, %d\n", pid, i);
        sleep(10);
    }
    exit();
}

int main() {
    int parentId = getpid();

    if (changePolicy(1) == 0)
        printf(1, "changing Policy  was succes\n");
    else
        printf(1, "changing Policy  was failed\n");
  

    for (int i = 0; i < CHILDREN_NUMBER; i++)
    {            
        
        if (fork() == 0 ) // if Child
            break;// child was created successfully and break from loop
    }

    if (getpid() != parentId)//child process
    {
        run(getpid());  
    }

    else//parent process
    { 
        int CBTs[CHILDREN_NUMBER] = {0};        // CBTs for each child
        int pids[CHILDREN_NUMBER] = {0};        // pid for each child
        int turnarounds[CHILDREN_NUMBER] = {0}; // turnaround times for each child
        int waitings[CHILDREN_NUMBER] = {0};    // waiting times for each child
       

        int *arrayTime = malloc(4 * sizeof(int));
        int counter = 0;

        // wait for children
        //this function help us to clculate times
        while (wait_findTimes(arrayTime) > 0)
        {
            int childTurnaround = arrayTime[0];
            int childWaiting = arrayTime[1];
            int childCBT = arrayTime[2];
            int childPID = arrayTime[3];

            pids[counter] = childPID;
            turnarounds[counter] = childTurnaround;
            waitings[counter] = childWaiting;
            CBTs[counter] = childCBT;
            counter++;
        }

        printf(1, "\n\n\nTimes for each child\n");
        for (int j = 0; j < CHILDREN_NUMBER; j++)
        {
            printf(1, "child with pid: %d ---> TurnaroundTime: %d, WaitingTime: %d, CBT: %d\n",
                   pids[j], turnarounds[j], waitings[j], CBTs[j]);
        }

  
        int turnaroundsSum = 0;
        int waitingsSum = 0;
        int CBTsSum = 0;
        for (int j = 0; j < CHILDREN_NUMBER; j++)
        {
            turnaroundsSum += turnarounds[j];
            waitingsSum += waitings[j];
            CBTsSum += CBTs[j];
        }   
        printf(1, "\n\n\nTotal average Times \n");
        printf(1, "Total ---> Average Turnaround_T: %d, Average Waiting_T: %d, Average CBT: %d\n",
               turnaroundsSum / CHILDREN_NUMBER,
               waitingsSum / CHILDREN_NUMBER,
               CBTsSum / CHILDREN_NUMBER);
    }

    while (wait() != -1)
        ;
    exit();
}