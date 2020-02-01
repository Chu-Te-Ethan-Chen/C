[Description]
1.Load points from node.txt and calculate distance between any two points.
2.Record points pair whose distance is less than 1 in the arrayD.
3.Find a pair from arrayD and check if there is any point will inside the cycle of the pair. If there is any point in the cycle then delete the link of the pair.
  (implemetation:Choose node(A,B)¡Afind middle point M¡Afind distance between A, M¡Acheck distance between other points e.g. C,D,E and the middle point.
   If distCM < distAM, means the point C is inside the cycle of pair AB and should delete the link between pair AB.
4.Record point pair in arrayE after deleting links.
5.output arrayD and arrayE to link.txt.

[Time complexity]
If we have n nodes, then n!/(n-2)!/2!=n(n-1)/2=(n^2-2n)/2.
thus Big-oh=(n^2).