/*
 Word Ladder Dictionary header by Xavid Ramirez
 for Algorithmms and Data Structures
 Spring 2015 semseter
*/

#include "TrieTree.h"

class Dictionary
{
private:
	vector<Trie> TrieTable;
	fstream inFile;
public:
	Dictionary()
	{
		inFile.open("largedictionary.txt");
		string word = " ";
		string word2;

		//this seems like a lot of work but meh, it works.
		//find the biggest word size and make a vector
		// of tries that extend to that size
		while (!inFile.eof())
		{
			inFile >> word2;
			if (word.length() < word2.length())
				word = word2;
		}
		inFile.close();
		//resize vector to the size of the longest word + 1
		TrieTable.resize(word.length() + 1);


		inFile.open("largedictionary.txt");
		//start inserting words.
		while (!inFile.eof())
		{
			inFile >> word;
			insert(word);
		}

	}

	//insert the word based on its size into it's appropriate trie.
	void insert(string word)
	{
		TrieTable[word.size()].insert(word);
	}

	//check first if the word sizes match if not then tell the user
	// if they do then go find the path for that trie of that word size
	void WordLadder(string x, string y)
	{
		if (x.size() != y.size())
			cout << "These word sizes do not match." << endl;
		else
			TrieTable[x.size()].findPath(x, y);
	}

};