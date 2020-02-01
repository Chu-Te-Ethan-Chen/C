Huffman Coding  
==========================
`Given`:  
* text.txt  

`Goal`:  
* output code.txt  
* Construct a priority queue in which:  
The keys in nodes are the frequencies.  
The data in nodes are the characters.  
Add all the characters with their frequencies into the priority queue.  

`Constraints`:  
* You must implement the project with a priority queue.  
* Tree node should be declared as follows.  
typedef struct node *nodePointer;  
typedef struct node {  
  char character;  
  int frequency;  
  nodePointer leftChild;  
  nodePointer rightChild;  
};  
int MAX_QUEUE_SIZE;  
nodePointer priorityQueue[MAX_QUEUE_SIZE];  
* You have to create a node with malloc function.  
* Your code must be able to: read the text from a file, and output the code book and encrypted text to a file.  

`Hints`:  
* Pop two nodes u and v in order.  
* Create a node w.  
* The left child and right child of w are set to u and v, respectively.  
* Push node w back to the priority queue.  
* Repeat the above pop and push until no node in the queue.  

![](https://github.com/Jordon-Chen/C/blob/master/HuffmanCoding/HuffmanCoding.png?raw=true)

`Description`  
step1: Record the frequency of each character in the text.txt.  
step2: Set up a priorityqueue which was inplemented with min heap according to the frequency.  
step3: Pop two elements from the priorityqueue and merge to a node. Left child is the first element and the right child is the second element.  
Put the node back into the priorityqueue until the Huffman tree was completed.  
step4: Record the path while travesal. Left is 0 and right is 1. We will get a Huffman table.  
step5: read text.txt again and transform each charater to Encrypted text accordin to Huffman table.  
