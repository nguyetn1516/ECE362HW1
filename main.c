#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "Queue.h"

/* function generates a random value between 2 values */
int Rand(int MIN, int MAX )
{
    int randValue = rand() % (MAX - MIN) + MIN;
    return randValue;
}

/* function calculates the number of available requests */
int Calculate(int SIZE, int TOTAL)
{
    int R;

    if (TOTAL >= SIZE)
    { R = TOTAL - SIZE;}

    else
    { R = TOTAL;}

    return R;

}

/* function adds a new value to the previous sum in order to get the new sum */
int Sum(int PREV_SUM, int NEW_VAL)
{
    int newSum;
    newSum = PREV_SUM + NEW_VAL;

    return newSum;
}

/* function determines the lower-sum */
int Compare(int PREV_VAL, int NEW_VAL)
{
    int lowestValue;

    /* comparing the sums */
    if(PREV_VAL <= NEW_VAL || NEW_VAL == 0)
    {
        lowestValue = PREV_VAL;
    }
    else if(PREV_VAL >= NEW_VAL || PREV_VAL == 0)
    {
        lowestValue = NEW_VAL;
    }

    return lowestValue;
}

int main(int argc, const char *argv[])
{
    printf("\n***** Invalid input values will be discarded and default values will then be used instead! *****\n");

    /* default values */
    int qValue = 1;
    int rValue = 5;
    int minValue = 0;
    int maxValue = 20;

    int randomValue;
    int sumValue = 0;   // initialize the sum of a queue
    int lowestSum;      // the lowest sum out of the queues
    int index;          // the index of the lowest-sum queue

    srand(time(0));     // random seed

    /* if more than 1 argument entered */
    if (argc > 1)
    {
        /* convert each value from char to int */
        for (int i=1; i<argc-1 ; i++)
        {
            if (!(strcmp("-q", argv[i])))
            {
                qValue = atoi(argv[i+1]);

                i++;
            }
            else if (!(strcmp("-r", argv[i])))
            {
                rValue = atoi(argv[i+1]);

                i++;
            }
            else if (!(strcmp("-min", argv[i])))
            {
                minValue = atoi(argv[i+1]);

                i++;
            }
            else if (!(strcmp("-max", argv[i])))
            {
                maxValue = atoi(argv[i+1]);

                i++;
            }
        }

        /* check for invalid inputs */
        if (qValue <= 0 || minValue >= maxValue || rValue <= 0 || minValue < 0 || maxValue <= 0)
        {
            printf("Error! Invalid input data!\n\n");

            /* use default values */
            qValue = 1;
            rValue = 5;
            minValue = 0;
            maxValue = 20;
        }
    }

    /* if only 1 argument entered, then use the default values */
    else if (argc == 1)
    {
        qValue = 1;
        rValue = 5;
        minValue = 0;
        maxValue = 20;
    }

    /* display the values */
    printf("q value is %d\n", qValue);
    printf("r value is %d\n", rValue);
    printf("min value is %d\n", minValue);
    printf("max value is %d\n\n", maxValue);

    /* malloc the queues */
    struct Queue** queue = (struct Queue**) malloc((qValue)*sizeof(struct Queue*));

    int qSize;              // the size of a queue
    int sumArray[qValue];   // store the sum of each queue in the array



    /* if there's 1 queue */
    if (qValue == 1)
        {
            qSize = rValue;                                 // the size of the queue equal the number of request
            queue[0] = createQueue(qSize);                  // create a queue

            for(int m=0; m<qSize; m++)
            {
                randomValue = Rand(minValue, maxValue);     // generate a random value with input min and max values
                sumValue = Sum(sumValue, randomValue);      // Calculate the current sum
                enqueue(queue[0], randomValue);             // enqueue the generated random value
            }
            printf("\n");
            printf("Queue 1 sum:\t%d\n", sumValue);
            printf("\nValues in the lowest-queue:\n");

            for (int i=0; i<(queue[0]->capacity); i++)
            {printf("%d ", queue[0]->array[i]);}            // display the elements in the queue
        }


    /* if there are 2 queues */
    else if (qValue == 2)
    {
        /* create the first queue */
        qSize = Rand(0, rValue);                            // generate a random size for the first queue
        queue[0] = createQueue(qSize);                      // create the first queue with the generated size

        for (int m=0; m<qSize; m++)
        {
            randomValue = Rand(minValue, maxValue);         // generate a random value
            enqueue(queue[0], randomValue);                 // enqueue the generated random value to the queue
            sumValue = Sum(sumValue, randomValue);          // calculate the sum of the queue
        }
        sumArray[0] = sumValue;                             // store the final sum of the queue into the array
        printf("\n");
        printf("Queue 1 sum:\t%d\n", sumArray[0]);
        sumValue = 0;                                       // reset the sum

        /* create the second queue */
        qSize = rValue - qSize;                             // the size for the second queue is the available of requests
        queue[1] = createQueue(qSize);                      // create the second queue

        for (int m=0; m<qSize; m++)                         // repeat the same steps as in the first queue
        {
            randomValue = Rand(minValue, maxValue);
            enqueue(queue[1], randomValue);
            sumValue = Sum(sumValue, randomValue);
        }
        sumArray[1] = sumValue;
        printf("\n");
        printf("Queue 2 sum:\t%d\n\n\n", sumArray[1]);
        lowestSum = Compare(sumArray[0], sumArray[1]);      // determine the lowest sum
        printf("Values in the lowest-queue:\n");

        if (lowestSum == sumArray[0])                       // if the first queue has the lowest sum
        {
            for (int i=0; i<(queue[0]->capacity); i++)
            {
                printf("%d ", queue[0]->array[i]);          // display the values in the first queue
            }
        }
        else
        {
             for (int i=0; i<(queue[1]->capacity); i++)
            {
                printf("%d ", queue[1]->array[i]);          // else, display the value in the second queue
            }
        }
    }


    /* if there are more than 2 queues */
    else if (qValue > 2)
    {
        int rLeft = rValue;                         // set the available requests equal to the initial number of requests

        /* create the queues */
        int i;
        for ( i=0; i<qValue; i++)
        {
            /* check if no more available requests but there are empty queues left */
            if (rLeft == 0)
            {
                /* set the sum of each queue equal zero */
                for (int a=i; a<qValue; a++)
                {
                    queue[a] = createQueue(1);
                    enqueue(queue[a], 0);
                }
            }
            else
            {
                /* check if this is the last queue */
                if ((i+1) == qValue)
                {
                    qSize = rLeft;                  // the size of the last queue equal the current available requests
                }
                else
                {
                    /* else, generate a random value for the size */
                    qSize = Rand(0, rLeft);
                }

                rLeft = Calculate(qSize, rLeft);    // calculate the number of available requests

                /* if queue size is zero */
                if (qSize == 0)
                {
                    queue[i] = createQueue(1);      // create a queue of size 1
                    enqueue(queue[i], 0);           // enqueue a zero once, no change to the number of available requests
                    sumValue = 0;                   // set the sum equal to zero

                }
                else if(qSize > 0)
                {
                    queue[i] = createQueue(qSize);                  // create a queue with the generated queue size

                    for (int m=0; m<qSize; m++)
                    {
                        randomValue = Rand(minValue, maxValue);     // generate a random value
                        sumValue = Sum(sumValue, randomValue);      // calculate the current sum
                        enqueue(queue[i], randomValue);             // enqueue the generated random value
                    }

                }

                sumArray[i] = sumValue;                             // store the final sum to the array
                printf("Queue %d sum:\t%d\n\n",i+1, sumArray[i]);

                /* determine the loweer sum between the first two queues */
                if(i==1)
                {
                    lowestSum = Compare(sumArray[0], sumArray[1]);

                    if(lowestSum == sumArray[0])                    // if the first queue has the lower sum
                    {index = 0;}                                    // the index of the lower-sum queue is zero
                    else
                    {index = 1;}                                    // else, the index of the lower-sum queue is one
                }

                /* determine the lowest sum */
                else if(i>1)
                {
                    lowestSum = Compare(lowestSum, sumArray[i]);
                    if(lowestSum == sumArray[i])                    // if the new sum is the lowest sum
                    {index = i;}                                    // change the index value
                }                                                   // else, do not change the index value
            }
            sumValue = 0;                                           // reset the sumValue for the next queue
        }

        /* display the lowest-sum values */
        printf("\nValues in the lowest-queue(%d): \n", index+1);
        int capacity = queue[index]->capacity+1;

        for (int b=0; b<capacity; b++)
        {
            printf("%d ", queue[index]->array[b]);
        }
    }
    return 0;
}
