/*
 Word Ladder Trie header by Xavid Ramirez
 for Algorithmms and Data Structures
 Spring 2015 semester
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <list>
using namespace std;

//this is the custom trie that uses edges and vertexes 

class Trie
{
private:
	class vertex; //prototype
	class edge
	{
	public:
		char letter;
		vertex * child;

		edge(char x)
		{
			child = NULL;
			letter = x;
		}
	};

	class vertex
	{
	public:
		vector<vertex*> neighbors;
		vector<int> edgeP;
		string word;
		bool end;
		vertex * pred;
		vector<edge*> edges;
		bool visited;

		vertex(string x)
		{
			edges.resize(26);
			word = x;
			pred = NULL;
			end = false;
			visited = false;
		}
		vertex()
		{
			edges.resize(26);
			pred = NULL;
			end = false;
			visited = false;
		}
	};

	// Private functions start here

	//give me bacck the vertex of the given string
	//since during insert i put them into the vertexlist
	//just find it in there.
	vertex * findWord(string x)
	{
		for each(vertex * v in vertexList)
		{
			if (v->word == x)
				return v;
		}
		return NULL;
	}

	//just in case there is a chance that predesesors from a previous
	//search will screw somthing up, rahter than take a chance
	// i will reset them back to null before doing breadhFirstSearch
	void resetPred()
	{
		for each (vertex * v in vertexList)
		{
			v->visited = false;
			v->pred = NULL;
		}

	}

	//insert will insert the word starting from root
	void insert(vertex * ptr, string word)
	{
		//this is used to fidn where to put the edge
		int i = 0;
		//if the character is actually within the alphabet range
		// it will be from 0 - 25, if it is a weird character it will be
		// bigger or smaller
		if ((word[0] - 97) < 0 || word[0] - 97 > 25)
			i = 26;
		// thus make it 26
		else
			i = (word[0] - 97);

		//then if it is actually a weird character, we dont want to deal with that
		// so i ignore them
		if (i == 26)
		{
			return;
		}

		//if the edge doesnt exist for that pointer, make it assign it, and point to it
		if (ptr->edges[i] == NULL){
			ptr->edges[i] = new edge(word[0]);
			ptr->edgeP.push_back(i);
			ptr->edges[i]->child = new vertex(ptr->word + word[0]);
		}
		//if it is the last character in the word then this is the end of the word, so set
		// the flag as true and find the neighbors as well as push this vertex back into the
		//vertexList for later use with breadhFirstSearch
		vertex * nextVertex = ptr->edges[i]->child;

		if (word.size() == 1){
			
			findNeighbor(nextVertex, root, nextVertex->word, 0);
			vertexList.push_back(nextVertex);
			nextVertex->end = true;
		}
		//else just keep inserting into the trie
		else{
			insert(ptr->edges[i]->child, word.substr(1, word.size()));
		}
	}

public:
	vertex * root;
	vector<vertex *> vertexList;
	Trie()
	{
		root = new vertex();
	}

	void insert(string x)
	{
		insert(root, x);
	}


	//this is the reason why i broke up the tries into difference hashed sizes
	void findNeighbor(vertex * forwho, vertex * finder, string word, int difference)
	{
		//since some words like car had r as the end but cars had the r and s as end
		//this function kept breaking, because this was my base case, but to save myself
		// a headache i split them up into word sized tries

		//if the end of the word is met, then if the difference is only 1 push it back
		//as an edge to both finder and for who.
		if (finder->end == true)
		{
			if (difference == 1)
			{
				forwho->neighbors.push_back(finder);
				finder->neighbors.push_back(forwho);
			}
		}
		//if the word is still 1 character long, check its edges and find the niehgbors for it.
		else if (word.size() == 1)
		{
			for each (int x in finder->edgeP)
			{
				if (finder->edges[x]->letter == word[0])
					findNeighbor(forwho, finder->edges[x]->child, word.substr(1, word.size()), difference);
				else
					findNeighbor(forwho, finder->edges[x]->child, word.substr(1, word.size()), difference + 1);
			}
		}
		//for any time the word size is bigger than 1 find the neighbors for all the edges
		else if (word.size() > 1)
		{
			if (difference > 1)
			{
				return;
			}
			else if (difference == 0)
			{
				for each (int x in finder->edgeP)
				{
					if (finder->edges[x]->letter == word[0])
						findNeighbor(forwho, finder->edges[x]->child, word.substr(1, word.size()), 0);
					else
						findNeighbor(forwho, finder->edges[x]->child, word.substr(1, word.size()), 1);
				}
			}
			else if (difference == 1)
			{
				for each (int x in finder->edgeP)
				{
					if (finder->edges[x]->letter == word[0])
						findNeighbor(forwho, finder->edges[x]->child, word.substr(1, word.size()), difference);
					else
						findNeighbor(forwho, finder->edges[x]->child, word.substr(1, word.size()), difference + 1);
				}
			}
		}

	}

	//using print to test the neighbors list of the words in the trie
	//and make sure that they are corect.
	//basically error checking function
	void print()
	{
		for each(vertex * v in vertexList)
		{
			if (v->neighbors.size() > 0)
			{

				cout << v->word << ":";
				for each(vertex  * x in v->neighbors)
				{

					cout << x->word << ",";
				}
				cout << endl;
			}


		}

	}

	//breadthFirstSearch on a graph.
	void breadthFirstSearch(vertex * s)
	{
		
		s->visited = true;
		queue<vertex *> Q;
		Q.push(s);
		while (!Q.empty())
		{
			vertex * x = Q.front(); Q.pop();

			for each (vertex  * v in x->neighbors)
			{
				if (v->visited == false)
				{
					v->visited = true;
					v->pred = x;
					Q.push(v);
				}

			}

		}

	}


	//This function will find the shortest path from one word to another
	void findPath(string x, string y)
	{
		vertex * start = findWord(y);

		//check if the word given by the user even exists in the dictionary
		if (start == NULL)
		{
			cout << start << " does not exist in the dictionary!" << endl;
			return;
		}

		vertex * end = findWord(x);

		//check if the word given by the user even exists in the dictionary
		if (end == NULL)
		{
			cout << end << " does not exist in the dictionary!" << endl;
			return;
		}
		//do breadthFirstSearch on end, which in this case is the first word
		//because we will do breadthfiurstsearch backwards
		breadthFirstSearch(start);


		//print out the path.
		while (end->pred != NULL)
		{
			if (end->pred == NULL)
			{
				cout << "No Path found!" << endl;
				return;
			}

			cout << end->word << endl;
			end = end->pred;
		}
		cout << end->word << endl;
	}
};