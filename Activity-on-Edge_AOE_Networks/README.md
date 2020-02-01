Activity-on-Edge (AOE) Networks  
==========================
`Given`:  
* An AOE network  
* Vertices represent events  
* Edge represent tasks  
* Numbers represent time required to perform the task   

`Goal`:  
* If the project is feasible,find the early and late times for each task, Find the degree of criticality for each task  
* Otherwise,Indicate the infeasibility abd Print “No solution”  

![](https://github.com/Jordon-Chen/C/blob/master/Activity-on-Edge_AOE_Networks/input1.png?raw=true)  
input1  
![](https://github.com/Jordon-Chen/C/blob/master/Activity-on-Edge_AOE_Networks/input2.png?raw=true)  
input2  
![](https://github.com/Jordon-Chen/C/blob/master/Activity-on-Edge_AOE_Networks/output.png?raw=true)  
output  

`Description`  
step1: set up adjacency list.  
step2: forward-early activity time.  
step3: backward-late activity time.  
step4: calculate degree of criticality(slack) and check Critical or not.
