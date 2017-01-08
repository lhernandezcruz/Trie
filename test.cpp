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
	
	
	// insert he and make sure he is in it
	testingTrie.insert("hell");
	REQUIRE(!testingTrie.exists("he"));
	REQUIRE(testingTrie.size() == 1);
	// testingTrie.print(std::cout);

	// insert help and check if it is in it
	testingTrie.insert("help");
	REQUIRE(testingTrie.size() == 2);
	REQUIRE(testingTrie.exists("help"));
}

/*
TEST_CASE("Testing Remove/Exists SIMPLE")
{
	// we should be able to insert words into the trie
	Trie testingTrie = Trie();

	// check if hello is in there
	testingTrie.insert("hello");
	testingTrie.print(std::cout);

	// check that we can remove it
	REQUIRE(testingTrie.remove("hello"));
	REQUIRE(testingTrie.size() == 0);
	REQUIRE(!testingTrie.exists("hello"));
	REQUIRE(!testingTrie.remove("hello"));
	testingTrie.print(std::cout);
}
*/

TEST_CASE("Testing Rest of Word")
{
	// we should be able to insert words into the trie
	Trie testingTrie = Trie();

	// check if hello is in there
	testingTrie.insert("them");
	
	REQUIRE(!testingTrie.exists("the"));
	testingTrie.insert("the");
	REQUIRE(testingTrie.exists("them"));
	testingTrie.insert("they");
	REQUIRE(testingTrie.exists("they"));

	// look at predicted words
	 std::cout << testingTrie.restOfWord("th") << std::endl;
}

