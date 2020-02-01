#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTICES 20
typedef struct node *nodePointer;
typedef struct node
{
    int vertex;
    int duration;
    nodePointer link;
};
typedef struct
{
    int count;
    nodePointer link;
} hdnodes; //headnodes

hdnodes graph[MAX_VERTICES];
void push(int vertex1, int vertex2, int duration);                     //set up adjacency list;update count of hdnode;find the number of vertex
void print_adjacency_list();                                           //print adjacency list
void topSort(int topological_order[], int earliest[]);                 //calculate topological order, earliest event time
void backward(int lateset[], int earliest[], int topological_order[]); //calculate late activity time
int number = 0;                                                        //save the amount of vertex
int activity;                                                          //save the amount of acitivities

int main()
{
    ////////////////////step1:set up adjacency list////////////////////
    FILE *fin;
    fin = fopen("input.txt", "r");
    if (fin == NULL)
    {
        printf("Error! File doesn't exist.");
    }
    int vertex1, vertex2, duration;
    fscanf(fin, "%d", &activity);
    while (1)
    {
        fscanf(fin, "%d", &vertex1);
        if (feof(fin))
            break;
        fscanf(fin, "%d", &vertex2);
        fscanf(fin, "%d", &duration);
        push(vertex1, vertex2, duration);
    }
    fclose(fin);

    ////////////////////step2:forward-early activity time////////////////////
    int i, r = 0;                  //r record how many ee of vertex are zero
    int topological_order[number]; //record topological_order
    int earliest[number];          //record (ee, earliest event time)
    memset(topological_order, 0, sizeof(int) * number);
    memset(earliest, 0, sizeof(int) * number);

    topSort(topological_order, earliest);
    for (i = 0; i < number; i++)
    { //check is there any vertex that can not arrive
        if (earliest[i] == 0)
        {
            r++;
        }
    }

    ////////////////////step3:backward-late activity time////////////////////
    int latest[number]; //record (le, latest event time)
    for (i = 0; i < number; i++)
    { //lateset[number-1]=earliest[number-1]
        latest[i] = earliest[number - 1];
    }
    backward(latest, earliest, topological_order);

    ////////////////////step4:calculate degree of criticality(slack) and check Critical or not////////////////////
    FILE *fout;
    fin = fopen("input.txt", "r");
    if (fin == NULL)
    {
        printf("Error! File doesn't exist.");
    }
    fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("File creation failed");
    }

    if (r > 1)
    {
        fprintf(fout, "No solution!");
        printf("Oh No!! No solution!!");
    }
    else
    {
        fscanf(fin, "%d", &activity);
        fprintf(fout, "%d\n", activity);
        int event1, event2, time, e, l;
        while (1)
        {
            fscanf(fin, "%d", &event1);
            if (feof(fin))
                break;
            fscanf(fin, "%d", &event2);
            fscanf(fin, "%d", &time);
            e = earliest[event1];          //�p��early time for each tasks
            l = (latest[event2] - time);   //�p��late time for each tasks
            fprintf(fout, "%d ", e);       //�g�Xearly time
            fprintf(fout, "%d ", l);       //�g�Xlate time
            fprintf(fout, "%d ", (l - e)); //�g�Xslack
            if ((l - e) == 0)
            { //decide critical or not
                fprintf(fout, "y\n");
            }
            else
            {
                fprintf(fout, "n\n");
            }
        }
        printf("output.txt has been founded!!\n");
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

void push(int vertex1, int vertex2, int duration)
{
    nodePointer temp0, temp1;
    temp1 = (nodePointer)malloc(sizeof(*temp1));
    if (temp1 == NULL)
    {
        printf("Dynamic memory allocation failed.");
        exit(1);
    }
    temp0 = graph[vertex1].link;
    if (temp0 == NULL)
    { //set up the firsr node
        temp1->vertex = vertex2;
        temp1->duration = duration;
        temp1->link = NULL;
        graph[vertex1].link = temp1;
    }
    else
    { //noded after the first one
        for (temp0; temp0->link != NULL; temp0 = temp0->link)
            ;
        temp1->vertex = vertex2;
        temp1->duration = duration;
        temp1->link = NULL;
        temp0->link = temp1;
    }
    //update count of hdnode
    graph[vertex2].count++;
    //find the amount of vertex
    if ((vertex2 + 1) > number)
    { 
        number = (vertex2 + 1);
    }
}

void print_adjacency_list()
{
    int i;
    nodePointer temp0;
    printf("count\tv d\tv d\tv d\n");
    for (i = 0; i < number; i++)
    {
        printf("%d\t", graph[i].count);
        temp0 = graph[i].link;
        while (temp0 != NULL)
        {
            printf("%d ", temp0->vertex);
            printf("%d\t", temp0->duration);
            temp0 = temp0->link;
        }
        printf("\n");
    }
}

void topSort(int topological_order[], int earliest[])
{
    int i, j, k, l, top;
    top = -1;
    l = 0;
    nodePointer ptr;
    for (i = 0; i < number; i++)
    {
        if (!graph[i].count)
        {
            graph[i].count = top;
            top = i;
        }
    }
    for (i = 0; i < number; i++)
    {
        if (top == -1)
        {
            printf("\nNetwork has a cycle. Sort terminated.\n");
            exit(1);
        }
        else
        {
            j = top; //vertex that should remove
            top = graph[top].count;
            topological_order[l++] = j; //calculate topological order
            for (ptr = graph[j].link; ptr != NULL; ptr = ptr->link)
            {
                k = ptr->vertex;
                if (earliest[k] < (earliest[j] + ptr->duration))
                { //earliest event time
                    earliest[k] = (earliest[j] + ptr->duration);
                }
                graph[k].count--;
                if (!graph[k].count)
                { //put vertex k into stack
                    graph[k].count = top;
                    top = k;
                }
            }
        }
    }
}

void backward(int lateset[], int earliest[], int topological_order[])
{
    nodePointer ptr;
    int k, j, i;    //k record topological order; j record the value according to the k ; i is the vertex that j connected with
    k = number - 2; 
    for (k; k >= 0; k--)
    { //reverse topological order
        j = topological_order[k];
        ptr = graph[j].link;
        for (ptr; ptr != NULL; ptr = ptr->link)
        {
            i = ptr->vertex;
            if (lateset[j] > (lateset[i] - ptr->duration))
            {
                lateset[j] = (lateset[i] - ptr->duration);
            }
        }
    }
}