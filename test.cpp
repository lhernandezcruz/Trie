#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

// include trie
#include "trie.hpp"

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
	REQUIRE(!testingTrie.exists("hello"));
	// nodes not removed yet
	REQUIRE(testingTrie.totalNodes() == 5);
	
	// cant remove the same word
	REQUIRE(!testingTrie.remove("hello"));


	testingTrie.insert("hell");
	REQUIRE(testingTrie.remove("hell")); // 2
	REQUIRE(testingTrie.size() == 0);
	REQUIRE(testingTrie.totalNodes() == 5);

	// insert stuff to testingTrie
	testingTrie.insert("he");
	REQUIRE(testingTrie.totalNodes() == 5);
	testingTrie.insert("abc");
	REQUIRE(testingTrie.totalNodes() == 8);
	testingTrie.insert("gg");
	REQUIRE(testingTrie.totalNodes() == 10);
	testingTrie.insert("you");
	testingTrie.insert("your");
	REQUIRE(testingTrie.totalNodes() == 14);

	// remove words from testingTrie
	testingTrie.remove("he"); // 3
	REQUIRE(testingTrie.totalNodes() == 14);
	testingTrie.remove("you"); // 4
	REQUIRE(testingTrie.totalNodes() == 14);
	testingTrie.remove("gg"); // 5 remove. will delete unused nodes
	REQUIRE(testingTrie.totalNodes() == 7);
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
	std::cout << testingTrie.restOfWord("t") << std::endl;

	// add words and check these too
	testingTrie.insert("a");
	testingTrie.insert("albert");
	testingTrie.insert("anna");
	std::cout << testingTrie.restOfWord("a") << std::endl;
	std::cout << testingTrie.restOfWord("b") << std::endl;
	testingTrie.print(std::cout);
}

