/*
2018/12/13
Data Structure hw2 Infix to Postfix and Evaluation (Stacks must be implemented by singly linked lists)
ctchen
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memset()
#define stack_size 200

typedef struct node *ptr; //stack of infix_to_postfix
typedef struct node
{
    char data;
    ptr link;
} Node;

typedef struct node1 *ptr1; //stack of evaluate
typedef struct node1
{
    double data;
    ptr1 link;
} Node1;

enum precedence
{
    lparen,
    rparen,
    plus,
    minus,
    times,
    divide,
    mod,
    eos,
    operand,
    positive,
    negative,
    space
};
typedef enum precedence precedence;
int isp[8] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[8] = {20, 19, 12, 12, 13, 13, 13, 0};

void infixnp(char infix[]);
void in_to_postfix(char infix[], char postfix[]);
double evaluate(char postfix[]);
int getToken(char array[], int *n);
int printToken(precedence token);
ptr push(ptr top, char item);
ptr pop(ptr top, char *item);
ptr1 push1(ptr1 top, double item);
ptr1 pop1(ptr1 top, double *item);

int main()
{
    char infix[stack_size] = {0};
    char postfix[stack_size] = {0};
    double answer;
    FILE *fin, *fout;
    fin = fopen("infix.txt", "r"); //read infix.txt
    if (fin == NULL)
    {
        printf("Error! File doesn't exist.");
        return 0;
    }
    fout = fopen("postfix.txt", "w"); //write postfix.txt
    if (fout == NULL)
    {
        printf("File creation failed\n");
        return 0;
    }
    while (1)
    {
        if (feof(fin))
            break;                      //read the whole txt
        fscanf(fin, "%s", &infix);      //step1. read infix.txt and put data into infix[]
        infixnp(infix);                 //step2.change plus and minus into p and n
        in_to_postfix(infix, postfix);  //step3.infix to postfix
        answer = evaluate(postfix);     //step4.calculate postfix
        fprintf(fout, "%s\t", postfix); //step5.write the anwser into postfix.txt
        fprintf(fout, "%g\n", answer);
        memset(infix, 0, stack_size); //reset array
        memset(postfix, 0, stack_size);
    }
    fclose(fin);
    fclose(fout);
    printf("Done! postfix.txt has been established.\n");
    return 0;
}

void infixnp(char infix[])
{ //change plus and minus into p and n
    precedence token;
    char np[stack_size] = {0};
    int n = 0; //index of infix
    int m = 0; //index of np
    int i;
    for (token = getToken(infix, &n); token != eos; token = getToken(infix, &n))
    {
        if (token == minus)
        { //put operator into postfix
            if (infix[n - 2] == '-' || infix[n - 2] == '+')
            {
                np[m++] = 'n';
            }
            else
            {
                np[m++] = '-';
            }
        }
        else if (token == plus)
        {
            if (infix[n - 2] == '-' || infix[n - 2] == '+')
            {
                np[m++] = 'p';
            }
            else
            {
                np[m++] = '+';
            }
        }
        else
        {
            np[m++] = infix[n - 1];
        }
    }
    for (i = 0; i < stack_size; i++)
    {
        infix[i] = np[i];
    }
}

void in_to_postfix(char infix[], char postfix[])
{ //infix to postfix
    precedence token;
    int n = 0; //index of infix
    int m = 0; //index of postfix
    ptr stack_top = NULL;
    ptr stack_np_top = NULL;
    stack_top = push(stack_top, eos); //eos means number 7
    stack_np_top = push(stack_np_top, eos);
    char item; //temp for operator
    char np;   //temp for posivie and negative
    for (token = getToken(infix, &n); token != eos; token = getToken(infix, &n))
    {
        if (token == operand)
        { //put operator into postfix
            postfix[m++] = infix[n - 1];
        }
        else if (token == positive || token == negative)
        {
            stack_np_top = push(stack_np_top, token);
        }
        else if (token == rparen)
        { //if meet a right parentheses, pop the operands from a stack until meeting left parentheses
            if (postfix[m - 1] != ' ')
            {
                postfix[m++] = ' ';
            }
            while (stack_np_top->data != eos)
            { //pop positive and negative
                stack_np_top = pop(stack_np_top, &np);
                postfix[m++] = printToken(np);
                postfix[m++] = ' ';
            }
            while (stack_top->data != lparen)
            {
                stack_top = pop(stack_top, &item);
                postfix[m++] = printToken(item);
            }
            stack_top = pop(stack_top, &item); //remove left parentheses
        }
        else
        {
            if (m != 0 && postfix[m - 1] != ' ')
            {
                //add space if the previous position is not a space
                postfix[m++] = ' ';
            }
            while (stack_np_top->data != eos)
            { //pop positive and negative
                stack_np_top = pop(stack_np_top, &np);
                postfix[m++] = printToken(np);
                postfix[m++] = ' ';
            }
            while (isp[stack_top->data] >= icp[token])
            {
                stack_top = pop(stack_top, &item);
                postfix[m++] = printToken(item);
                postfix[m++] = ' ';
            }
            stack_top = push(stack_top, token);
        }
    }
    while (stack_np_top->data != eos)
    { //pop positive and negative
        if (postfix[m - 1] != ' ')
        {
            postfix[m++] = ' ';
        }
        stack_np_top = pop(stack_np_top, &np);
        postfix[m++] = printToken(np);
    }
    while (stack_top->data != eos)
    { //pop operators out inside the stack
        stack_top = pop(stack_top, &item);
        postfix[m++] = ' ';
        postfix[m++] = printToken(item);
    }
}

double evaluate(char postfix[])
{ //calculate postfix
    precedence token;
    double op1, op2;
    int m = 0; //counter,indix of postfix
    ptr1 stack_top = NULL;
    stack_top = push1(stack_top, 7.0);
    double item = 0;               //temp for pop
    double num = 0;                //temp for integer
    token = getToken(postfix, &m); //take a token out fisrt
    while (token != eos)
    {
        if (token == operand)
        { //merge numbers
            num = num * 10 + (postfix[m - 1] - '0');
        }
        else if (token == space)
        {
            if (48 <= postfix[m - 2] && postfix[m - 2] <= 57)
            {
                stack_top = push1(stack_top, num);
                num = 0; //reset
            }
        }
        else if (token == positive)
        { //do nothing
        }
        else if (token == negative)
        {
            stack_top = pop1(stack_top, &item);
            item = -item;
            stack_top = push1(stack_top, item);
        }
        else
        { //if operends, calculate them
            //op2: the later op1:the former
            stack_top = pop1(stack_top, &item);
            op2 = item;
            stack_top = pop1(stack_top, &item);
            op1 = item;
            switch (token)
            {
            case plus:
                stack_top = push1(stack_top, op1 + op2);
                break;
            case minus:
                stack_top = push1(stack_top, op1 - op2);
                break;
            case times:
                stack_top = push1(stack_top, op1 * op2);
                break;
            case divide:
                stack_top = push1(stack_top, op1 / op2);
                break;
            }
        }
        token = getToken(postfix, &m); //take the next operator
    }
    stack_top = pop1(stack_top, &item);
    return item;
}

int getToken(char array[], int *n)
{ //distinguish operator
    char symbol;
    symbol = array[(*n)++];
    switch (symbol)
    {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '*':
        return times;
    case '/':
        return divide;
    case '%':
        return mod;
    case '0':
        return operand;
    case '1':
        return operand;
    case '2':
        return operand;
    case '3':
        return operand;
    case '4':
        return operand;
    case '5':
        return operand;
    case '6':
        return operand;
    case '7':
        return operand;
    case '8':
        return operand;
    case '9':
        return operand;
    case 'p':
        return positive;
    case 'n':
        return negative;
    case ' ':
        return space;
    default:
        return eos;
    }
}

int printToken(precedence token)
{ //change number into operators
    switch (token)
    {
    case lparen:
        return '(';
    case rparen:
        return ')';
    case plus:
        return '+';
    case minus:
        return '-';
    case times:
        return '*';
    case divide:
        return '/';
    case mod:
        return '%';
    case positive:
        return 'p';
    case negative:
        return 'n';
    case eos:
        return ' ';
    }
}

ptr push(ptr top, char item)
{ //push() for in_to_postfix
    ptr temp;
    temp = (Node *)malloc(sizeof(*temp));
    if (temp == NULL)
    {
        printf("Dynamic memory allocation failed.");
        exit(1);
    }
    temp->data = item;
    temp->link = top;
    top = temp;
    return top;
}

ptr pop(ptr top, char *item)
{ //pop() for in_to_postfix
    ptr temp;
    temp = top;
    if (temp == NULL)
    {
        printf("Stack is empty");
    }
    *item = top->data;
    top = top->link;
    free(temp);
    return top;
}

ptr1 push1(ptr1 top, double item)
{ //push() for evaluate
    ptr1 temp;
    temp = (Node1 *)malloc(sizeof(*temp)); //malloc(sizeof(*temp))!
    if (temp == NULL)
    {
        printf("Dynamic memory allocation for temp failed.");
        exit(1);
    }
    temp->data = item;
    temp->link = top;
    top = temp;
    return top;
}

ptr1 pop1(ptr1 top, double *item)
{ //pop() for evaluate
    ptr1 temp;
    temp = top;
    if (temp == NULL)
    {
        printf("Stack is empty");
    }
    *item = top->data;
    top = top->link;
    free(temp);
    return top;
}