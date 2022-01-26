#include "types.h"
#include "stat.h"
#include "user.h"

#define CHILDREN_NUMBER 30


void run(int child_num) {
    int i;
    for (i = 0; i < 100; ++i){
        printf(1, "%d , %d\n", child_num, i+1);
        // sleep(20);
    }
    exit();
}

int main() {
    int priority = -1;
    int parentId = getpid();
    int child_num = -1;

    if (changePolicy(2) == 0)
        printf(1, "changing Policy  was succes\n");
    else
        printf(1, "changing Policy  was failed\n");
  

    for (int i = 0; i < CHILDREN_NUMBER; i++)
    {            
        
        if (fork() == 0 ) // if Child
        {
            priority = 6 - (i / 5);
            setPriority(priority);
            child_num = i + 1;
            // printf(1, "i: %d, priority: %d\n", i, priority);
            break;// child was created successfully and break from loop
        }
    }

    if (getpid() != parentId)//child process
    {
        run(child_num);  
    }

    else//parent process
    { 
        int CBTs[CHILDREN_NUMBER] = {0};        // CBTs for each child
        int priorities[CHILDREN_NUMBER] = {0};  // priorites for each child
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
            int childPriority = arrayTime[3];

            priorities[counter] = childPriority;
            turnarounds[counter] = childTurnaround;
            waitings[counter] = childWaiting;
            CBTs[counter] = childCBT;
            counter++;
        }

        printf(1, "\n\n\nTimes for each child\n");
        for (int j = 0; j < CHILDREN_NUMBER; j++)
        {
            printf(1, "priority %d ---> TurnaroundTime: %d, WaitingTime: %d, CBT: %d\n",
                   priorities[j], turnarounds[j], waitings[j], CBTs[j]);
        }

        int turnaroundsInClass[6] = {0};
        int waitingsInClass[6] = {0};
        int CBTsInClass[6] = {0};
        for (int j = 0; j < CHILDREN_NUMBER; j++)
        {
            int childPriority = priorities[j];
            
            turnaroundsInClass[childPriority - 1] += turnarounds[j];
            waitingsInClass[childPriority - 1] += waitings[j];
            CBTsInClass[childPriority - 1] += CBTs[j];
        }

        printf(1, "\n\n\nAverage Times for priority classess\n");
        for (int j = 5; j >= 0; j--)
        {
            printf(1, "class with priority: %d ---> Average Turnaround_T: %d, Average Waiting_T: %d, Average CBT: %d\n",
                   j + 1,
                   turnaroundsInClass[j] / (CHILDREN_NUMBER / 6),
                   waitingsInClass[j] / (CHILDREN_NUMBER / 6),
                   CBTsInClass[j] / (CHILDREN_NUMBER / 6));
           
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