# Word-Ladder
This was created as an assignment for my Algorithms and Data Structures course. I will give a visual description of the data strcutures but do not allow coplete copy and submittion of my assignent as your own if you are given an assignment similar to this one.

#The original assignment:
 http://faculty.utpa.edu/rtschweller/CS3333/CS3333S2015/hwk/wordPuzzle.htm
 
#The appoches prior to this one:
  Before figuring out how to solve this problem I did go through many different ideas. My first idea involved using a hash table. But after trying to draw it out it did seem more anoying to implement than I would have liked. I searched google for different types of data structures that organize dictionaries well and I did find the Trie data structure. Now When I first implemented my trie it was not using vertexes and edges. I tried things left and right to figure out a way to create a graph and run the shortest path algorithm on the graph to find the word ladder. The thing is that the way my trie was set up it wouldn't work as such. I actually didn't even manage to turn in the assignment on time. I did show the instructor the finished product the folowing Monday, as it was due on a Friday.

#I wasnt the only one with this approach.
  The trie is also considered a radix tree, which is what my friends Taigai and xMoros implemented but in a weird fashion. They explained their approach and it made sence on why mine didnt work. I didnt have the qualities in my Trie to even think of finding the neighbors of the words as I inputed them into the structure. Taigai explain how his trie worked when putting in words but it confused me. After re-reading the shortest path problem i realized for it to even work, you have to have a few things in your data structure.
  1. Vertexes
  2. Edges
  3. ability to find the niehgbors of each vertex
  4. and most importantly the VertexList

#How the Custom trie looks:
 http://i.imgur.com/clvMolM.png
 
#Making life easier
 After trying to build the graph I realized all I needed is the VertexList so I didn't even have to build the graph actually. I wont say more because it's neat when you realize why. 
 
#if you have questions feel free to mesage me about the project. Maybe I was unclear on some parts or it got confusing. 
