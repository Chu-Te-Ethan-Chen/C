Generate a Planar Subgraph  
==========================
`Given`:  
* node.txt  
* Number of nodes  
* Nodes with non-negative coordinates(x, y) (the input graph is connected when we add links if dist(u,v) ≤ 1)  

`Goal`:  
* output link.txt  
* The edges before and after planarization  

`Constraints`:  
* The first node ID should be "smaller" than the second one for each link  
* The links should be sequentially indexed in "ascending" order of the first node ID  
* If there is a tie, the two links are indexed in "ascending" order of the second node ID  
* The IDs of remaining links after planarization should be "identical" to the ones before the planarization  

`Hints`:  
* Add a link between any two nodes u, v as dist(u,v) ≤ 1  
* Remove some links to generate a planar graph  
![](https://github.com/Jordon-Chen/C/blob/master/face_routing/generate%20a%20planar%20subgraph.png?raw=true)
Before:22 links  
After:11 links  
*Red lines are deleted after using the algorithm
