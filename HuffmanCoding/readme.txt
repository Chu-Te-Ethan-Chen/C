hw3-Huffman Coding
@compress text

step1: Record the frequency of each character in the text.txt.
step2: Set up a priorityqueue which was inplemented with min heap according to the frequency.
step3: Pop two elements from the priorityqueue and merge to a node. Left child is the first element and the right child is the second element.
Put the node back into the priorityqueue until the Huffman tree was completed.
step4: Record the path while travesal. Left is 0 and right is 1. We will get a Huffman table.
step5: read text.txt again and transform each charater to Encrypted text accordin to Huffman table.
