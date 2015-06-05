#include "Dictionary.h"


int main()
{
	//call the class dictionary
	Dictionary dictionary;

	//decide if the user wants to continue finding word ladders
	char choice = 'y';

	while (choice == 'y')
	{
		cout << "please enter two words to find a short path to: " << endl;
		string Word1, Word2;
		cin >> Word1; cin >> Word2;

		//dictionary method to find the wordladder between two given words
		dictionary.WordLadder(Word1, Word2);

		cout << "would you like to try another word? (y/n):" << endl;
		cin >> choice; cout << endl;

	}

	system("pause");
	return 0;
}