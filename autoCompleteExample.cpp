#include<iostream>
#include <fstream>
#include "trie.hpp"

using namespace std;
void autoComplete(const string& fname) {
	// Create our trie to store our dictionary
	Trie dictionary = Trie();

	// Write dictionary file to a stream called dictfile
	ifstream dictFile(fname);

	if (!dictFile) {
		cerr << "Couldn't open file. Exiting" << endl;
		exit(1);
	}

	string line;
	// Insert all words into Trie
	while (getline(dictFile, line)) {
		dictionary.insert(line);
	}
	
	cout << "Finished Reading Dictionary. Please Enter words to autocomplete: " << endl;
	//  Stores predicted words
	vector<string> predicts;

	// Stores the prefix to be checked
	string prefix;
	// Read in line and print out prediction.
	while (getline(cin, prefix)) {
		predicts = dictionary.restOfString(prefix);
		cout << "Predicted words are:";
		for (auto i = predicts.begin(); i != predicts.end(); ++i)
			cout << *i << ' ';
		cout << endl;
	}
}
int main(int argc, const char** argv)
{
	if (argc != 2) {
		cerr << "Usage: simpleEx dictfile" << endl;
		exit(2);
	}

	// Process command-line options
	++argv;

	// Check running autoComplete
	try {
		autoComplete(argv[0]);
	}
	catch (std::runtime_error err) {
		cerr << err.what() << endl;
		return 1;
	}

	return 0;
}

