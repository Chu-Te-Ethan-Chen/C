Count-Min_Sketch  
==========================
`Given`:  
* keys in many documents  

`Goal`:  
* Count the key frequency  
* Bounded error is allowed    
 
`Constraints`:  
* Limited storage and limited computation  
* The trick: don’t store the distinct elements, but just the counters  

`Hints`:  
* You may want to use libraries Guava or FastUtil in Java for convenience and better performance  

![](https://highlyscalable.files.wordpress.com/2012/04/count-min-sketch.png?w=805)
from:https://www.google.com/search?q=count-min+sketch&tbm=isch&tbas=0&source=lnt&sa=X&ved=0ahUKEwjYhYKK5bHnAhWZL6YKHZkHDOUQpwUIJA&biw=1920&bih=937&dpr=1#imgrc=c91hp_VPaKSOkM:
![](https://hkorte.github.io/slides/cmsketch/img/experiments-mem.png)
from:https://www.google.com/search?biw=1920&bih=937&tbm=isch&sa=1&ei=uS82XsPsIreFr7wP9fqBiAo&q=memory+used+guava+cmsketch&oq=memory+used+guava+cmsketch&gs_l=img.3...68551.81091..81323...4.0..0.63.1353.31......0....1..gws-wiz-img.......0i30j0i24j0j0i67j0i5i30j0i8i30.pYv3PQrNqPA&ved=0ahUKEwiDreWN5bHnAhW3wosBHXV9AKEQ4dUDCAc&uact=5#imgrc=YqhMWyrGS0BOdM:

`Description`  
step1: read input.txt, change upper letter to lower letter and remove punctuation marks.  
step2: use hash function in C++<string> to change strings into key and put it into the hash function: (a[count]*key+b[count])%p%c，to get the hash value.  
step3: find the hash value in the hash table and add one.  
step4: set up a querry function to find the hash value.  
