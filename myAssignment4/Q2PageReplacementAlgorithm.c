//Mirage
//Assignment 4 CSI3131 Operating System
//Question 2 Page-Replacement Algorithm
#include <stdio.h>
#include <stdbool.h>
#define true 1
#define false 0


//GLOBAL ATTRIBUTES
int numberOfPages; // number of pages
int pages[99];
int frames[99];
int frameSize;

void fifo();
void lru();

int main() {



    printf("Enter the number of pages: ");
    scanf("%d", &numberOfPages);


    printf("\nEnter the number of page reference strings: ");

    for (int i = 0; i < numberOfPages; i++) {
        scanf("%d", &pages[i]);

    }
    printf("\n Enter the size of the page frame: ");
    scanf("%d",&frameSize);
    printf("\n");

    for(int i = 0; i < numberOfPages;i++){
        if(i == 0){
            printf("Number of pages: %d;  ", numberOfPages);
            printf("Reference Strings: ");
        }
        printf(" %d", pages[i]);

    }
    printf(";");
    printf(" Frame size: %d;",frameSize);
    printf("\n");

    bool keepRunning = true;

    while(keepRunning) {
        int choice;
        printf("\n\t[MENU]\n");
        printf("\n\t   1) FIFO ");
        printf("\n\t   2) LRU ");
        printf("\n\t   3) QUIT ");
        printf("\n ");
        printf("\nEnter your choice 1 or 2: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo();
                break;
            case 2:
                lru();
                break;
            case 3:
                keepRunning = false;
                break;
            default:
                printf("\nINVALID INPUT: \n --> [Please Select 1 for FIFO or Select 2 for LRU]\n");
                break;
        }

    }


    getchar();


    return 0;
}

//FIFO -> 1 represents True
//FIFO -> 0 represents False

//FIFO page-replacement algorithm
void fifo()
{


    int faults = 0;
    int index = 0;
    bool runProgram = false; //found

    int leadership = 0;//index 1 f
    int conflict = 0;//index 2 r




    for(int i = 0; i<frameSize; i++){
        frames[i] = -1;
    }

    while(index < numberOfPages)
    {
        runProgram = false;
        int myNumber = pages[index];

        for(int j = 0; j<frameSize; j++)
        {
            if(myNumber == frames[j])
            {
                index++;
                runProgram= true;
                break;
            }
        }


        if(runProgram == false){
            if(conflict < frameSize)
            {
                frames[conflict] = pages[index];
                conflict++;
                faults ++;
                index++;

            }
            else{
                if(leadership < frameSize)
                {
                    frames[leadership] = pages[index];
                    leadership++;
                    faults++;
                    index++;
                }
                else{
                    leadership = 0;
                }
            }

        }



        //Operation
        printf("\n"); // splits it into the number of frames
        for(int k = 0; k<frameSize; k++)
        {
            printf("%d\t", frames[k]);
        }

    }

    //Executing The Number of Page Faults
    printf("\n #Page Faults: %d", faults);
    getchar();

}

//LRU page-replacement algorithm

void lru()
{

    int myArray[99];
    int x = 0;
    int index = 0;
    int fault = 0;
    bool pageExist = false;


    for(int i = 0; i<frameSize; i++){
        myArray[i] = 0;
        frames[i] = -1;
    }

    for(int i = 0; i<numberOfPages; i++){
        pageExist = false;
        int temp = pages[i];
        for(int j = 0; j<frameSize; j++)
        {
            if(temp == frames[j]){
                pageExist = true;
                myArray[j] = i;
                break;
            }
        }

        if(pageExist == false && (index < frameSize))
        {
            fault++;
            frames[index] = temp;
            myArray[index] = i;
            index+=1;
        }
        else if(pageExist == false && index == frameSize){
            fault+=1;
            int leastRecent = myArray[0];
            for(int k = 0; k < frameSize; k++){
                if(myArray[k] < leastRecent){
                    leastRecent = myArray[k];
                    x = k;
                }
            }
            frames[x] = temp;
            myArray[x] = i;
            x = 0;
        }

        printf("\n");
        for(int m = 0; m<frameSize;m++)
        {
            printf("%d \t", frames[m]);
        }
    }

    printf("\n #Page Faults: %d", fault);
    getchar();



    }


