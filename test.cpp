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
	testingTrie.insert("he");
	testingTrie.exists("he");
	REQUIRE(testingTrie.size() == 1);
	testingTrie.print(std::cout);

	// check th
}

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

TEST_CASE("Testing Rest of Word")
{
	// we should be able to insert words into the trie
	Trie testingTrie = Trie();

	// check if hello is in there
	testingTrie.insert("the");
	// testingTrie.insert("them");
	// testingTrie.insert("they");

	// check that we can remove it
	REQUIRE(testingTrie.restOfWord("th") == "the");
}