
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 10

typedef struct
{
    int num_strings;
    char *strings[QUEUE_SIZE];
    int front_i;
    int back_i;
} Queue;

void InitializeQueue(Queue *q)
{
    q->num_strings = 0;
    q->front_i = 0;
    q->back_i = 0;
}

void Enqueue(Queue *q, char *val)
{
    if (q->num_strings >= QUEUE_SIZE)
    {
        return;
    }
    q->strings[q->back_i] = val;
    q->back_i = (q->back_i+1)%QUEUE_SIZE;
    q->num_strings++;
}

char* Dequeue(Queue *q)
{
    if (q->num_strings == 0)
    {
        return NULL;
    }
    char *goodbye = q->strings[q->front_i];
    q->front_i = (q->front_i+1)%QUEUE_SIZE;
    q->num_strings--;
    return goodbye;
}

char* Front(Queue *q)
{
    if (q->num_strings==0)
        return NULL;
    return q->strings[q->front_i];
}

/* void
PrintQueue(Queue *q)
{
    int i;
    printf("Printing queue %p\n", q);
    printf("\tThe index for the front of the queue is %d\n", q->front_i);
    printf("\tThe index for the back of the queue is %d\n", q->back_i);
    if (q->front_i == q->back_i)
    {
        printf("\tThe queue is empty.\n");
        return;
    }
    int back = q->back_i;
    if (q->back_i < q->front_i)
    {
        // wrapped around, so modify indexing 
        back += QUEUE_SIZE;
    }

    for (i = q->front_i ; i < back ; i++)
    {
        printf("\t\tEntry[%d] = \"%s\"\n", i%QUEUE_SIZE, q->strings[i%QUEUE_SIZE]);
    }
}
 */

void
PrettyPrintQueue(Queue *q, char *type)
{
    if (Front(q) == NULL)
    {
        printf("No unmatched entries for %s\n", type);
    }
    else
    {
        char *s;
        printf("Unmatched %s:\n", type);
        while ((s = Dequeue(q)))
        {
            printf("%s\n", s);
        }
    }
}

char *NewString(char *s)
{
    int len = strlen(s);
    char *rv = malloc(len+1);
    strcpy(rv, s);
    rv[len-1] = '\0'; /* take out newline */
    return rv;
}

int main(int argc, char *argv[])
{

/***  STEP #1: Test your queue code.  ***/

/*** STEP #2: read in from the input file (argc/argv stuff). 
     NewString is likely helpful here.
 ***/
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Unable to open file \"%s\" \n", argv[1]);
        exit(EXIT_FAILURE);
    }

    Queue DMen;
    InitializeQueue(&DMen);
    Queue DWomen;
    InitializeQueue(&DWomen);
    Queue RMen;
    InitializeQueue(&RMen);
    Queue RWomen;
    InitializeQueue(&RWomen);
    Queue Hospitals;
    InitializeQueue(&Hospitals);

    int size = 50;
    char buffer[size];
    while (fgets(buffer, size, f))
    {
        char *event = NewString(buffer);
        if (event[0]=='R')
        {
            if (event[2]=='M')
                Enqueue(&RMen, event+4);
            else
                Enqueue(&RWomen, event+4);
        }
        else if (event[0]=='D')
        {
            if (event[2]=='M')
                Enqueue(&DMen, event+4);
            else
                Enqueue(&DWomen, event+4);
        }
        else
        {
            Enqueue(&Hospitals, event+2);;
        }

        if (Hospitals.num_strings>0)
        {
            if (DWomen.num_strings>0 && RWomen.num_strings>0)
            {
                char *donor = Dequeue(&DWomen);
                char *recip = Dequeue(&RWomen);
                char *hosp = Dequeue(&Hospitals);
                printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
            }
            else if (DMen.num_strings>0 && RMen.num_strings>0)
            {
                char *donor = Dequeue(&DMen);
                char *recip = Dequeue(&RMen);
                char *hosp = Dequeue(&Hospitals);
                printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
            }
        }
    }

    PrettyPrintQueue(&DWomen, "female donors");
    PrettyPrintQueue(&RWomen, "female recipients");
    PrettyPrintQueue(&DMen, "male donors");
    PrettyPrintQueue(&RMen, "male recipients");
    PrettyPrintQueue(&Hospitals, "hospitals");

/*** STEP #3: *after* your queue code works and *after* you can read the file, 
     implement the prompt ***/
    return 0;
}
