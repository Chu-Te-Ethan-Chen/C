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

[Description]  
>1.Load points from node.txt and calculate distance between any two points.  
>2.Record points pair whose distance is less than 1 in the arrayD.  
>3.Find a pair from arrayD and check if there is any point will inside the cycle of the pair. If there is any point in the cycle then delete the link of the pair.  
implemetation:Choose node(A,B), find middle point M, find distance between A, M, check distance between other points e.g. C,D,E and the middle point.If distCM < distAM, means the point C is inside the cycle of pair AB and should delete the link between pair AB.  
>4.Record point pair in arrayE after deleting links.  
>5.output arrayD and arrayE to link.txt.  

[Time complexity]  
>If we have n nodes, then n!/(n-2)!/2!=n(n-1)/2=(n^2-2n)/2, thus Big-oh=(n^2).  
