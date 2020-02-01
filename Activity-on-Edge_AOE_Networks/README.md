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

`Description`  
step1: set up adjacency list.  
step2: forward-early activity time.  
step3: backward-late activity time.  
step4: calculate degree of criticality(slack) and check Critical or not.
