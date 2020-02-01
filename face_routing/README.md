Generate a Planar Subgraph  
Given:
  1.node.txt  
  2.Number of nodes  
  3.Nodes with non-negative coordinates(x, y) (the input graph is connected when we add links if dist(u,v) ≤ 1)  
Goal:  
  1.output link.txt  
  2.The edges before and after planarization  
Constraints:  
  1.The first node ID should be smaller than the second one for each link  
  2.The links should be sequentially indexed in ascending order of the first node ID  
  3.If there is a tie, the two links are indexed in ascending order of the second node ID  
  4.The IDs of remaining links after planarization should be identical to the ones before the planarization  
Hints:  
  1.Add a link between any two nodes u, v as dist(u,v) ≤ 1  
  2.Remove some links to generate a planar graph  
![](https://github.com/Jordon-Chen/C/blob/master/face_routing/generate%20a%20planar%20subgraph.png?raw=true)
