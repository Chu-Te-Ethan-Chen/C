#include <fstream> //fscanf
#include <iostream>
#include <memory.h> //memset
#include <random>
#include <string> //hash function in C++11
#define size 50
using namespace std;

void inti(int **hashmap, int r, int c, int *a, int *b, int p);
void changetolower(char *str, char *str1);
int myhash(char *str, int counter, int r, int c, int p, int *a, int *b);
void insert_hashmap(int **hashmap, int r, int c, int p, char *str, int *a, int *b);
void querry(int **hashmap, int r, int c, int p, char *str, int *a, int *b);

int main()
{
    char str[size] = {0};  //record words read from the text
    char str1[size] = {0}; //record words after removing the upper letter and punctunation marks
    int r, c, p;
    int i, j;
    int **hashmap = NULL; //ptr to dynamic 2D array hashmap
    FILE *fin;
    fin = fopen("input.txt", "r");
    if (!fin)
    {
        cout << "File doesn't exsist!\n";
        exit(1);
    }
    fscanf(fin, "%d", &r);
    fscanf(fin, "%d", &c);
    fscanf(fin, "%d", &p);

    int a[r];
    int b[r];

    hashmap = new int *[r]; //allocate memory for row
    for (i = 0; i < r; i++)
    {
        hashmap[i] = new int[c]; //allocate memory for column
    }
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            hashmap[i][j] = 0; //initailize 2D dynamic array
        }
    }

    random_device rd;                                              //random engine
    default_random_engine generator = default_random_engine(rd()); //random engine
    uniform_int_distribution<int> dist(1, p - 1);                  //uniform int distribution
    for (i = 0; i < r; i++)
    { //set up arrayA
        a[i] = dist(generator);
    }
    for (i = 0; i < r; i++)
    { //set up arrayB
        b[i] = dist(generator);
    }

    while (1)
    {                                                 //read input.txt
        fscanf(fin, "%s", str);                       //read strings
        changetolower(str, str1);                     //change upper letter into lower letter and remove punctuation marks
        insert_hashmap(hashmap, r, c, p, str1, a, b); //add 1 to the specific position in the hashmap after calculation
        if (feof(fin))
        { //break after reading the last line
            break;
        }
        memset(str, 0, sizeof(str));   //clear str
        memset(str1, 0, sizeof(str1)); //clear str1
    }
    fclose(fin);
    cout << "Please enter the word that you want to find in the input.txt" << endl;
    while (1)
    { //querry
        memset(str, 0, sizeof(str));
        memset(str1, 0, sizeof(str1));
        cout << "#"
             << " ";
        cin >> str;
        changetolower(str, str1);
        querry(hashmap, r, c, p, str1, a, b);
    }

    for (i = 0; i < r; i++)
    {
        delete[] hashmap[i];
    }
    delete[] hashmap;

    return 0;
}

void inti(int **hashmap, int r, int c, int *a, int *b, int p)
{
    int i, j;
    hashmap = new int *[r]; //allocate memory for row
    for (i = 0; i < r; i++)
    {
        hashmap[i] = new int[c]; //allocate memory for column
    }
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            hashmap[i][j] = 0; //initailize 2D dynamic array
        }
    }

    random_device rd;                                              //random engine
    default_random_engine generator = default_random_engine(rd()); //random engine
    uniform_int_distribution<int> dist(1, p - 1);                  //uniform int distribution
    for (i = 0; i < r; i++)
    { //set up arrayA
        a[i] = dist(generator);
    }
    for (i = 0; i < r; i++)
    { //set up arrayB
        b[i] = dist(generator);
    }
}

void changetolower(char *str, char *str1)
{
    int i;
    for (i = 0; i < size; i++)
    {
        str[i] = tolower(str[i]);
        if (97 <= str[i] && str[i] <= 122)
        { //keep the alphbet
            str1[i] = str[i];
        }
        else
        {
            break;
        }
    }
}

int myhash(char *str, int counter, int r, int c, int p, int *a, int *b)
{
    std::hash<std::string> h;
    std::string s = str;
    size_t key = h(s);
    return (a[counter] * key + b[counter]) % p % c;
}

void insert_hashmap(int **hashmap, int r, int c, int p, char *str, int *a, int *b)
{
    int hash_result[r];     //record the result from the hash function, which means the specific position in the hashmap
    int increment_table[r]; //record position that should be added 1
    int smallest, temp, counter;
    for (counter = 0; counter < r; counter++)
    { //calculate hash value
        hash_result[counter] = myhash(str, counter, r, c, p, a, b);
    }
    smallest = hashmap[0][hash_result[0]]; //initialize the first value used to compare
    for (counter = 0; counter < r; counter++)
    { //find the min in the hashmap
        temp = hashmap[counter][hash_result[counter]];
        if (temp < smallest)
        {
            memset(increment_table, 0, sizeof(increment_table));
            increment_table[counter] = 1;
            smallest = temp;
        }
        else if (temp == smallest)
        {
            increment_table[counter] = 1;
        }
        else
        {
            continue;
        }
    }
    for (counter = 0; counter < r; counter++)
    { //add 1 at the min
        if (increment_table[counter] == 1)
        {
            hashmap[counter][hash_result[counter]]++;
        }
    }
}

void querry(int **hashmap, int r, int c, int p, char *str, int *a, int *b)
{
    int hash_result[r]; //record the result from the hash function, which means the specific position in the hashmap
    int i, smallest, temp, counter;
    for (counter = 0; counter < r; counter++)
    { //calculate hash value from the querry word
        hash_result[counter] = myhash(str, counter, r, c, p, a, b);
    }
    smallest = hashmap[0][hash_result[0]];
    for (i = 0; i < r; i++)
    { //find the min in the hashmap
        temp = hashmap[i][hash_result[i]];
        if (temp < smallest)
        {
            smallest = temp;
        }
        else
        {
            continue;
        }
    }
    cout << smallest << endl;
}