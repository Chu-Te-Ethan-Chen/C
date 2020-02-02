hw5-Count-Min Sketch
1.use hash function to calculate the frequency of a word in a text.
2.Do not spend space to record the frequency of a word, record the amount of frequency of a word instead.
Altough we may overestimate the amount of the frequency, this method can give us a least number and save a lot of space when processing big data.

step1: read input.txt, change upper letter to lower letter and remove punctuation marks.
step2: use hash function in C++<string> to change strings into key and put it into the hash function: (a[count]*key+b[count])%p%c¡Ato get the hash value.
step3: find the hash value in the hash table and add one.
step4: set up a querry function to find the hash value.