#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 100

typedef struct queue *ptr; //calculate the frequency of character in the text
typedef struct queue
{
    char character;
    int frequency;
    char code[23]; //record code
    ptr link;
} Queue;
ptr rear = NULL;
ptr front = NULL;
void push1(char item); //calculate the frequency of character
void print_char_freq(ptr front1, FILE *fout);

typedef struct Node *nodePointer; //struct for priotityQueue
typedef struct Node
{
    char character;
    int frequency;
    nodePointer leftChild;
    nodePointer rightChild;
} node;
nodePointer priorityQueue[MAX_QUEUE_SIZE];

void push2(nodePointer addition, int *n);                                 //set up minheap
void pop2(int *n, nodePointer item);                                      //pop node from minheap
void print_minheap(nodePointer priorityQueue[]);                          //print minheap
void merge_node(nodePointer temp1, nodePointer temp2, nodePointer temp3); //set up node
void print_code(nodePointer ptr);                                         //make Huffman table
void push3(char item);                                                    //put code into struct
void encypted(FILE *fout);                                                //make Encryted text
int b = 0;                                                                //counter for code
char arrayA[23] = {0};                                                    //array for code
int number = 0;                                                           //record how many different symbols
int e = 0;                                                                //record how many bits were used
char E[1000] = {0};                                                       //Encrypted text

int main()
{
    char read;
    FILE *fin;
    fin = fopen("text.txt", "r"); //read text.txt
    if (fin == NULL)
    {
        printf("Error! File doesn't exist.");
        return 0;
    }
    while (1)
    {
        fscanf(fin, "%c", &read);
        if (feof(fin))
        {
            break;
        }
        //step1: Record the frequency of each character in the text.txt.
        push1(read);
    }
    fclose(fin);

    int i, n = 0; //how many nodes in the minheap
    for (i = 0; i < MAX_QUEUE_SIZE; i++)
    {
        priorityQueue[i] = (nodePointer)malloc(sizeof(node));
    }
    for (i = 0; i < MAX_QUEUE_SIZE; i++)
    {
        memset(priorityQueue[i], 0, sizeof(node));
    }

    nodePointer temp0, temp1, temp2, temp3; //temp0 for the context. temp1 for pop1. temp2 for pop2. temp3 for temp1 merge temp2.
    temp0 = (nodePointer)malloc(sizeof(node));
    temp1 = (nodePointer)malloc(sizeof(node));
    temp2 = (nodePointer)malloc(sizeof(node));
    temp3 = (nodePointer)malloc(sizeof(node));
    //step2: Set up a priorityqueue which was inplemented with min heap according to the frequency.
    ptr front1 = front;
    while (front1 != NULL)
    {
        number++;
        temp0->character = front1->character;
        temp0->frequency = front1->frequency;
        front1 = front1->link;
        push2(temp0, &n);
    }

    /*Pop two elements from the priorityqueue and merge to a node. Left child is the first element and the right child is the second element.
Put the node back into the priorityqueue until the Huffman tree was completed.*/
    while (priorityQueue[1]->frequency != 0)
    {
        pop2(&n, temp1);
        pop2(&n, temp2);
        merge_node(temp1, temp2, temp3);
        if (priorityQueue[1]->frequency == 0)
        {
            break;
        }
        push2(temp3, &n);
    }

    //step4: Record the path while travesal. Left is 0 and right is 1. We will get a Huffman table.
    print_code(temp3);

    //step5: read text.txt again and transform each charater to Encrypted text accordin to Huffman table.
    FILE *fout;
    fout = fopen("code.txt", "w"); //write code.txt
    if (fin == NULL)
    {
        printf("Error! File doesn't exist.");
    }
    else
    {
        fprintf(fout, "%d\n", number);
        print_char_freq(front, fout);
        encypted(fout);
        printf("code.txt has been established");
    }
    fclose(fout);

    //release the memory
    for (i = 0; i < MAX_QUEUE_SIZE; i++)
    {
        free(priorityQueue[i]);
    }
    free(temp0);
    free(temp1);
    free(temp2);
    free(temp3);
    return 0;
}

void push1(char item)
{ //calculate the frequency of character
    int inside = 0;
    ptr counter = NULL;
    counter = front;

    while (counter != NULL)
    {
        if (item == counter->character)
        {
            counter->frequency = counter->frequency + 1;
            inside = 1;
            break;
        }
        else
        {
            counter = counter->link;
        }
    }
    if (inside == 0)
    {
        ptr temp;
        temp = (Queue *)malloc(sizeof(*temp));
        if (temp == NULL)
        {
            printf("Dynamic memory allocation failed.");
            exit(1);
        }
        if (front == NULL && rear == NULL)
        {
            temp->character = item; //remember to put item
            temp->frequency = 1;
            temp->link = NULL;
            memset(temp->code, 0, (sizeof(char) * 24));
            front = rear = temp;
            return;
        }
        temp->character = item;
        temp->frequency = 1;
        temp->link = NULL;
        memset(temp->code, 0, (sizeof(char) * 24));
        rear->link = temp;
        rear = temp;
    }
}

void print_char_freq(ptr front1, FILE *fout)
{ //print character, frequency, and code
    int i;
    if (front1 == NULL)
    {
        printf("Queue is empty!");
    }
    while (front1 != NULL)
    {
        if (front1->character == 32)
        {
            fprintf(fout, "space ");
        }
        else
        {
            fprintf(fout, "%c ", front1->character);
        }
        fprintf(fout, "%d ", front1->frequency);
        for (i = 1; i <= 23; i++)
        {
            if (front1->code[i] != 0)
            {
                fprintf(fout, "%c", front1->code[i]);
            }
        }
        fprintf(fout, "\n");
        front1 = front1->link;
    }
}

void push2(nodePointer addition, int *n)
{ //set up minheap
    int i;
    if (*n == MAX_QUEUE_SIZE)
    {
        printf("The heap is full!\n");
        exit(1);
    }
    i = ++(*n);
    while (i != 1)
    { //update minheap
        if (!(i % 2))
        { //i is even
            if (addition->frequency < priorityQueue[i / 2]->frequency)
            { //compare with parent
                priorityQueue[i]->character = priorityQueue[i / 2]->character;
                priorityQueue[i]->frequency = priorityQueue[i / 2]->frequency;
                priorityQueue[i]->leftChild = priorityQueue[i / 2]->leftChild;
                priorityQueue[i]->rightChild = priorityQueue[i / 2]->rightChild;
                i /= 2;
            }
            else
            {
                break;
            }
        }
        else
        { //i is odd
            if (addition->frequency < priorityQueue[(i - 1) / 2]->frequency)
            { //compare with parent
                priorityQueue[i]->character = priorityQueue[(i - 1) / 2]->character;
                priorityQueue[i]->frequency = priorityQueue[(i - 1) / 2]->frequency;
                priorityQueue[i]->leftChild = priorityQueue[(i - 1) / 2]->leftChild;
                priorityQueue[i]->rightChild = priorityQueue[(i - 1) / 2]->rightChild;
                i /= 2;
            }
            else
            {
                break;
            }
        }
    }
    priorityQueue[i]->character = addition->character; //update other nodes
    priorityQueue[i]->frequency = addition->frequency;
    priorityQueue[i]->leftChild = addition->leftChild;
    priorityQueue[i]->rightChild = addition->rightChild;
}

void pop2(int *n, nodePointer item)
{ //pop node from minheap
    int parent, child;
    nodePointer temp;
    temp = (nodePointer)malloc(sizeof(node));
    if (priorityQueue[1]->frequency == 0)
    {
        printf("The heap is empty!\n");
        exit(1);
    }
    item->character = priorityQueue[1]->character; //record the first element
    item->frequency = priorityQueue[1]->frequency;
    item->leftChild = priorityQueue[1]->leftChild;
    item->rightChild = priorityQueue[1]->rightChild;
    temp->character = priorityQueue[*n]->character; //temp for the last element
    temp->frequency = priorityQueue[*n]->frequency;
    temp->leftChild = priorityQueue[*n]->leftChild;
    temp->rightChild = priorityQueue[*n]->rightChild;
    memset(priorityQueue[(*n)--], 0, sizeof(node));
    parent = 1;
    child = 2;
    while (child <= *n)
    {
        if ((child < *n) && (priorityQueue[child]->frequency > priorityQueue[child + 1]->frequency))
        { //if the right child is smaller than the left child
            child++;
        }
        if (temp->frequency <= priorityQueue[child]->frequency)
        { //if temp <= child, put the temp here
            break;
        }
        priorityQueue[parent]->character = priorityQueue[child]->character;
        priorityQueue[parent]->frequency = priorityQueue[child]->frequency;
        priorityQueue[parent]->leftChild = priorityQueue[child]->leftChild;
        priorityQueue[parent]->rightChild = priorityQueue[child]->rightChild;
        parent = child;
        child *= 2;
    }
    if (*n != 0)
    {
        priorityQueue[parent]->character = temp->character;
        priorityQueue[parent]->frequency = temp->frequency;
        priorityQueue[parent]->leftChild = temp->leftChild;
        priorityQueue[parent]->rightChild = temp->rightChild;
    }
    free(temp);
}

void print_minheap(nodePointer priorityQueue[])
{ //print minheap
    int i;
    for (i = 1; i < MAX_QUEUE_SIZE; i++)
    {
        printf("%c ", priorityQueue[i]->character);
    }
    printf("\n");
    for (i = 1; i < MAX_QUEUE_SIZE; i++)
    {
        printf("%d ", priorityQueue[i]->frequency);
    }
    printf("\n");
}

void merge_node(nodePointer temp1, nodePointer temp2, nodePointer temp3)
{ //set up node
    nodePointer left, right;
    left = (nodePointer)malloc(sizeof(node));
    right = (nodePointer)malloc(sizeof(node));
    left->character = temp1->character;
    left->frequency = temp1->frequency;
    left->leftChild = temp1->leftChild;
    left->rightChild = temp1->rightChild;
    right->character = temp2->character;
    right->frequency = temp2->frequency;
    right->leftChild = temp2->leftChild;
    right->rightChild = temp2->rightChild;
    temp3->character = 0;
    temp3->frequency = (left->frequency + right->frequency);
    temp3->leftChild = left;
    temp3->rightChild = right;
}

void print_code(nodePointer ptr)
{ //make Huffman table
    char item;
    if (ptr)
    {
        if (ptr->leftChild != NULL)
        {
            b++;
            arrayA[b] = '0';
            print_code(ptr->leftChild);
        }
        item = ptr->character;
        push3(item);

        if (ptr->rightChild != NULL)
        {
            b++;
            arrayA[b] = '1';
            print_code(ptr->rightChild);
        }
        b--;
    }
}

void push3(char item)
{ //put code into struct
    int i;
    ptr counter = NULL;
    counter = front;
    while (counter != NULL)
    { //find the character in queue
        if (item == counter->character)
        {
            for (i = 1; i <= b; i++)
            {
                counter->code[i] = arrayA[i];
            }
            break;
        }
        else
        {
            counter = counter->link;
        }
    }
}

void encypted(FILE *fout)
{ //make Encryted text
    int i;
    char item;
    FILE *fin;
    fin = fopen("text.txt", "r"); //read text.txt
    if (fin == NULL)
    {
        printf("Error! File doesn't exist.");
    }
    while (1)
    {
        fscanf(fin, "%c", &item);
        if (feof(fin))
        {
            break;
        }
        i = 1;
        ptr front2 = front;
        while (front2 != NULL)
        {
            if (item == front2->character)
            {
                while (1)
                {
                    if (front2->code[i] != 0)
                    {
                        E[e] = front2->code[i];
                        e++;
                        i++;
                    }
                    else
                    {
                        break;
                    }
                }
                break;
            }
            else
            {
                front2 = front2->link;
            }
        }
    }
    fclose(fin);
    fprintf(fout, "%d\n", e);
    fprintf(fout, "%s", E);
}
