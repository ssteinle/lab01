#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

char **radArr;
int **radArrIndex;

void inputGeneration(int n, int w, char minChar, int alphabetSize)
{
    int i;
    int j;
    char randomChar;

    srand(time(0));

    for(i=0; i<n; i++)
    {
        for(j=0;j<w;j++)
        {
            randomChar = (char) (rand() % alphabetSize) + minChar;
            radArr[i][j] = randomChar;
        }
        radArr[i][w] = '\0';
    }
}


void radixSort(int n, int w, char minChar, int alphabetSize, int demoFlag)
{


    int h=1;
    int i;
    int bucketVal;
    int bucket[alphabetSize];
    int x;
    int j;

    for(h=1;h<=w;h++)
    {

        for(i=0;i<alphabetSize;i++)
            bucket[i] = 0;

        for(i=0;i<n;i++)
        {
            bucketVal = (radArr[radArrIndex[i][0]][w-h] - minChar ) % alphabetSize;
            bucket[bucketVal]++;
        }

        if(demoFlag == 1)
        {
        printf("===================================================\n");
        printf("\nBucket for Iteration %d, Character %d\n", h, w-h+1);
        for(i=0;i<alphabetSize;i++)
            printf("%d ", bucket[i]);
        printf("\n");
        for(i=0;i<alphabetSize;i++)
            printf("%c ", i+minChar);
        printf("\n");
        }

        for(i=1;i<alphabetSize;i++)
            bucket[i] = bucket[i-1] + bucket[i];

        if(demoFlag == 1)
        {
            printf("\nBucket Summation:\n\n");
            for(i=0;i<alphabetSize;i++)
                printf("%d ", bucket[i]);
        }

        for(i=n-1;i>=0;i--)
        {
            j = (int) radArr[radArrIndex[i][0]][w-h];
            x = (j - minChar) % alphabetSize;

            bucket[x] = bucket[x] - 1;

            if(demoFlag == 1)
            {   
                printf("\nAfter Partial Sorting on digit %d: %s<->", (w-h+1), radArr[radArrIndex[bucket[x]][1]]);
            }

            radArrIndex[bucket[x]][1] = radArrIndex[i][0];

            if(demoFlag == 1)
            {   
                printf("%s\n", radArr[radArrIndex[bucket[x]][1]]);
            }
        }

        if(demoFlag == 1)
        {   
            printf("\n\nAfter Sorting on digit %d\n", (w-h+1));
            for(i=0; i<n; i++)
            {
                printf("%s ", radArr[radArrIndex[i][1]]);
            }
            printf("\n");
        }
        
        for(i=0;i<n;i++)
        {
            radArrIndex[i][0] = radArrIndex[i][1];
        }
    }
}

void simSort(int n, int w, int demo)
{
    int i;
    int j;
    char temp[w];

    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            //printf("\n%s vs %s\n", radArr[j], radArr[j+1]);
            if(strcmp(radArr[j], radArr[j+1]) > 0)
            {
                strcpy(temp, radArr[j+1]);
                strcpy(radArr[j+1], radArr[j]);
                strcpy(radArr[j], temp);
            }
        }
    }

    if(demo == 1)
    {
        printf("\nIteration %d of Bubble Sort \n", n);
        for(i=0; i<n; i++)
        {
            printf("%s ", radArr[i]);
        }
    }
}

//===================================================

void swap(char* a, char* b) 
{ 
    char t = *a; 
    *a = *b; 
    *b = t; 
} 

int partition (int min, int max, int stringSize) 
{ 
    char pivot[stringSize];
    strcpy(pivot, radArr[max]);
    char temp[stringSize];
    int i = (min - 1);
    //printf("Gate 2 min: %d max: %d ", min, max);

    for (int j = min; j <= max - 1; j++) 
    {    
        //printf("i: %d ", i);
        //printf("Comparing %s and %s\n", radArr[j], pivot);

        if (strcmp(radArr[j], pivot) < 0) 
        { 
            i++;
            //printf("Swapping %s and %s\n", radArr[i], radArr[j]);
            swap(radArr[i], radArr[j]);
        } 
    }

    //printf("Swapping %s and %s\n", radArr[i+1], radArr[max]);
    swap(radArr[i+1], radArr[max]);
/*
        printf("\n\nIteration of Quick Sort \n", 0);
        for(int j=0; j<10; j++)
            printf("%s ", radArr[j]);
        printf("\n");
*/
    return (i + 1);
} 

void quickSort(int min, int max, int stringSize) 
{ 
      //printf("Gate 1 ");

    if (min < max)
    { 
        int pi = partition(min, max, stringSize); 
        //printf("pi: %d, min: %d, max %d ", pi, min, max);
        quickSort(min, pi - 1, stringSize); 
        quickSort(pi + 1, max, stringSize); 
    } 
} 
//=================================================


int main()
{
    int i;
    int j;
    int listLength;
    int stringSize;
    int alphabetSize = 12;
    int demo = 0;
    int numDouble = 10;
    clock_t start, end;
    double total;
    double theoretical;
    int averageVal = 100;
    int rows = 2097152*2;
    int columns = 5;

    int rowsI = rows;
    int columnsI = 2;

	radArr = malloc(rows * sizeof(int *));
	for(i = 0; i < rows; i++)
		radArr[i] = malloc(columns * sizeof(char));

	radArrIndex = malloc(rowsI * sizeof(int *));
	for(i = 0; i < rowsI; i++)
		radArrIndex[i] = malloc(columnsI * sizeof(int));

    listLength = rows;
    stringSize = columns;

    inputGeneration(listLength, stringSize, 'A', alphabetSize);

    if(demo == 1)
        printf("List Length: %d. String Size: %d.",listLength,stringSize);

    if(demo == 1)
    {
        printf("\n\n");
        for(i=0;i<110;i++)
            printf("=");
    }

    for(i=0;i<listLength;i++)
    {
        radArrIndex[i][0] = i;
    }


    //RADIX SORT
    if(demo == 1)
    {
        printf("***************************************************\n");
        printf("Iteration %d of Radix Sort \n", 0);
        for(i=0; i<listLength; i++)
            printf("%s ", radArr[i]);
        printf("\n");
    }

    if(demo == 1)
    {
        //listLength = listLength*2;
        printf("\nList Size: %d String Size: %d Averaged Across: %d\n", listLength, stringSize, averageVal);

        printf("===================================================\n");

        start = clock();
        //for(int j=0;j<averageVal;j++)
            radixSort(listLength, stringSize, 'A', alphabetSize, demo);
        end = clock();

        printf("===================================================\n");

        total = (double)(end - start) / CLOCKS_PER_SEC;
        //total = total / averageVal;
        theoretical = stringSize * (listLength + alphabetSize);
        printf("\nRadix Sort Experimental Time: %f", total);
        printf("\nRadix Sort Theoretical Time: %f", theoretical);
        printf("\n***************************************************\n");
    }

    if(demo == 1)
    {
        printf("\n\n");
        for(i=0;i<110;i++)
            printf("=");
    }

    if(demo == 1)
    {
        printf("\nIteration %d of Bubble Sort \n", 0);
        for(i=0; i<listLength; i++)
            printf("%s ", radArr[i]);
        printf("\n");
    }

    if(demo == 1)
    {
        //listLength = listLength*2;
        printf("\n\nList Size: %d String Size: %d", listLength, stringSize);

        start = clock();
        for(int j=0;j<averageVal;j++)
            simSort(listLength, stringSize, demo);
        end = clock();

        total = (double)(end - start) / CLOCKS_PER_SEC;
        //total = total / averageVal;
        theoretical = listLength*listLength;
        printf("\nBubble Sort Experimental Time: %f", total);
        printf("\nBubble Sort Theoretical Time: %f", theoretical);
    }

    if(demo == 1)
        printf("\n");

    if(demo == 1)
    {
        printf("\n\n");
        for(i=0;i<110;i++)
            printf("=");
    }

    if(demo == 1)
    {
        printf("\n\nIteration %d of Quick Sort \n", 0);
        for(i=0; i<listLength; i++)
            printf("%s ", radArr[i]);
        printf("\n");
    }

    //if(demo == 1)
    {
        printf("\n\nList Size: %d String Size: %d Averaged Across: %d", listLength, stringSize, averageVal);

        start = clock();
        for(int j=0;j<averageVal;j++)
            quickSort(0, listLength-1, stringSize);
        end = clock();

        total = (double)(end - start) / CLOCKS_PER_SEC;
        //total = total / averageVal;
        theoretical = listLength*log(listLength);
        printf("\nQuick Sort Experimental Time: %f", total);
        printf("\nQuick Sort Theoretical Time: %f", theoretical);
    }
    
    if(demo == 1)
    {
        printf("\n\nFinal Iteration of Quick Sort \n", 0);
        for(i=0; i<listLength; i++)
            printf("%s ", radArr[i]);
        printf("\n");
    }

    for(i = 0; i < rows; i++)
        free(radArr[i]);
	free(radArr);

    for(i = 0; i < rowsI; i++)
        free(radArrIndex[i]);
	free(radArrIndex);

    return 0;
}