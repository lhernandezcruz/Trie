#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

// include trie
#include "trie.hpp"
using namespace std;

TEST_CASE("Testing Default Constructor")
{
	// basically should have size of zero
	Trie testingTrie = Trie();
	REQUIRE(testingTrie.size() == 0);
}


TEST_CASE("Testing Insert/Exists SIMPLE")
{
	// we should be able to insert words into the trie
	Trie testingTrie = Trie();
	
	
	// insert word and make sure word is in trie
	testingTrie.insert("hell");
	REQUIRE(!testingTrie.exists("he"));
	REQUIRE(testingTrie.exists("hell"));
	REQUIRE(testingTrie.size() == 1);
	REQUIRE(testingTrie.totalNodes() == 4);

	// insert help and check if it is in it
	testingTrie.insert("help");
	REQUIRE(testingTrie.size() == 2);
	REQUIRE(testingTrie.exists("help"));
	REQUIRE(testingTrie.totalNodes() == 5);

	// inserting word with different letter
	testingTrie.insert("abc");
	REQUIRE(testingTrie.exists("abc"));
	REQUIRE(testingTrie.size() == 3);

	// reinserting does not increase size
	testingTrie.insert("abc");
	REQUIRE(testingTrie.size() == 3);
}


TEST_CASE("Testing Remove/Exists SIMPLE")
{
	// we should be able to insert words into the trie
	Trie testingTrie = Trie();

	testingTrie.insert("hello");
	REQUIRE(testingTrie.totalNodes() == 5);

	// check that we can remove it
	REQUIRE(testingTrie.remove("hello")); // 1
	REQUIRE(testingTrie.size() == 0);
	REQUIRE(testingTrie.empty());
	REQUIRE(!testingTrie.exists("hello"));
	// nodes not removed yet
	REQUIRE(testingTrie.totalNodes() == 0);
	
	// cant remove the same word
	REQUIRE(!testingTrie.remove("hello"));

	// insert stuff to testingTrie
	testingTrie.insert("he");
	REQUIRE(testingTrie.totalNodes() == 2);
	testingTrie.insert("abc");
	REQUIRE(testingTrie.totalNodes() == 5);
	testingTrie.insert("gg");
	REQUIRE(testingTrie.totalNodes() == 7);
	testingTrie.insert("you");
	testingTrie.insert("your");
	REQUIRE(testingTrie.totalNodes() == 11);

	// remove words from testingTrie
	testingTrie.remove("he"); // 1
	REQUIRE(testingTrie.totalNodes() == 11);
	testingTrie.remove("you"); // 2
	REQUIRE(testingTrie.totalNodes() == 11);
	testingTrie.remove("gg"); // 3 remove. will delete unused nodes
	REQUIRE(testingTrie.totalNodes() == 11);
	testingTrie.showStatistics(cout);
	testingTrie.print(cout);
}


TEST_CASE("Testing Rest of Word")
{
	// we should be able to insert words into the trie
	Trie testingTrie = Trie();

	// insert words
	testingTrie.insert("them");
	testingTrie.insert("theirs");
	testingTrie.insert("they");

	// look at predicted words
	vector<string> rest = testingTrie.restOfString("t");
	for (auto i = rest.begin(); i != rest.end(); ++i)
		cout << *i << ' ';
	cout << endl;

	// add words and check these too
	testingTrie.insert("a");
	testingTrie.insert("albert");
	testingTrie.insert("anna");
	rest = testingTrie.restOfString("a");
	for (auto i = rest.begin(); i != rest.end(); ++i)
		cout << *i << ' ';
	cout << endl;

	rest = testingTrie.restOfString("b");
	for (auto i = rest.begin(); i != rest.end(); ++i)
		cout << *i << ' ';
	cout << endl;

	testingTrie.print(cout);

	// quick test of remove all
	testingTrie.removeAll();
	REQUIRE(testingTrie.size()== 0);
	REQUIRE(testingTrie.totalNodes() == 0);

	testingTrie.insert("yo");
	testingTrie.insert("you");
	testingTrie.insert("your");
	testingTrie.insert("yours");
	rest = testingTrie.restOfString("yo");
	for (auto i = rest.begin(); i != rest.end(); ++i)
		cout << *i << ' ';
	cout << endl;
}


TEST_CASE("HUGE DICTIONARY")
{ 
	// create a testingtrie
	Trie testingTrie = Trie();

	// Open provided file
	ifstream inFile("google-10000-english.txt");
	if (!inFile) {
		cerr << "Couldn't open file" << endl;
	}
	// Read data from the file, one item per line
	// and insert each word into the testingTrie
	//  require that each line was actually put into testingTrie
	string line;
	while (inFile.good()) {
		getline(inFile, line);
		testingTrie.insert(line);
		REQUIRE(testingTrie.exists(line));
	}

	// require that none have been deleted so far
	ifstream inFile2("google-10000-english.txt");
	if (!inFile2) {
		cerr << "Couldn't open file... rip" << endl;
	}
	string line2;
	while (inFile2.good()) {
		getline(inFile2, line2);
		REQUIRE(testingTrie.exists(line2));
	}
	testingTrie.showStatistics(cout);

	// require that we can delete all of the words
	ifstream inFile3("google-10000-english.txt");
	if (!inFile3) {
		cerr << "Couldn't open file... rip" << endl;
	}
	string line3;
	size_t totalNodes = testingTrie.totalNodes();
	size_t removeCount = 0;
	while (inFile3.good()) {
		getline(inFile3, line3);

		// make sure it properly removes it
		REQUIRE(testingTrie.remove(line3));
		REQUIRE(!testingTrie.exists(line3));
		++removeCount;

		// check that nodes are removed only everyonce in a while
		if (removeCount != MAXWORDSREMOVED && !testingTrie.empty()) {
			// uneeded nodes are not deleted often
			REQUIRE(totalNodes == testingTrie.totalNodes());
		}
		else {
			// check that nodes have been removed
			size_t newTotal = testingTrie.totalNodes();
			REQUIRE(totalNodes > newTotal);
			totalNodes = newTotal;
			removeCount = 0;
		}
	}

	// check empty and show statistics
	REQUIRE(testingTrie.empty());
	testingTrie.showStatistics(cout);
}
