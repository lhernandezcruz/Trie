/**
* \file ScapegoatTreeSet-private.hpp
*
* \author lhernandezcruz
*
* \brief Implemententation for Trie.hpp
*/

#include "trie.hpp"

///////////////////////////////////////////////////////////////
///////////// Trie Implementation /////////////////////////////
///////////////////////////////////////////////////////////////

Trie::Trie()
	: root_{ std::vector<Node>() }, size_{ 0 }
{
	// nothing to do here
}

void Trie::insert(std::string word)
{
	if (word.size() != 0) {
		// insert word into the root
		subTrieInsert(root_, word);
	}
}

void Trie::subTrieInsert(std::vector<Node>& subNode, std::string word)
{
	// base case is that we are inserting last character
	if (word.size() == 1) {
		// search nodes for letter
		bool found = false;
		auto i = subNode.begin();
		while (!found && i != subNode.end()) {
			if (i->value_ == word[0]) {
				// character is in subNode
				found = true;
				if (!i->endOfWord_) {
					// new word so increment size
					//  and update end or word
					++size_;
					i->endOfWord_ = true;
				}	
			}
			++i; // move on to next node
		}

		if (!found) {
			// add node for character, increment size
			Node insertee = Node(word[0]);
			insertee.endOfWord_ = true;
			subNode.push_back(insertee);
			++size_;
		}

	} else {
		// now we check check if the first char of the string is 
		//  in the subNodes
		char firstLetter = word[0]; 
		std::string rest = word.substr(1);

		bool found = false;
		auto i = subNode.begin();
		while (!found && i!=subNode.end()) {
			if (i->value_ == firstLetter) {
				// node already exists here so we just add rest of word
				found = true;
				subTrieInsert(i->children_, rest);
			}
			++i; // move on to next node
		}

		if (!found) {
			// character not in subnode
			//  create node, and insert rest of word
			Node insertee = Node(firstLetter);
			subTrieInsert(insertee.children_, rest);
			subNode.push_back(insertee);
		}	
	}
}

bool Trie::exists(std::string word)
{
	// look for word in trie
	return (word.size() != 0 && subTrieExists(root_, word));
}

bool Trie::subTrieExists(std::vector<Node>& subNode, std::string word)
{
	// base case is that we have one letter left
	//  check if it is the end of a word
	if (word.size() == 1) {
		auto i = subNode.begin();
		while (i != subNode.end()) {
			if (i->value_ == word[0]) {
				// check rest of the word
				return i->endOfWord_;
			}
			++i; // move on to next node
		}

		// didnt find it
		return false;
	}
	else {
		// now we check check if the first letter of the string is 
		//  in the subNode
		char firstLetter = word[0];
		std::string rest = word.substr(1);

		// check if i is in this level
		auto i = subNode.begin();
		while (i !=subNode.end()) {
			if (i->value_ == firstLetter) {
				// check rest of the word
				return subTrieExists(i->children_, rest);
			}
			++i; // move on to next node
		}

		// character not in trie. means word does not exist in trie
		return false;
	}
}

std::string Trie::restOfWord(std::string prefix)
{
	// find rest of word
	std::string output = prefix + ": ";
	return restOfWord(root_, prefix, "", output);
}

std::string Trie::restOfWord(const std::vector<Node>& subNode, std::string prefix,
									std::string currWord, std::string output) const
{
	// we finished finding the word
	if (prefix.size() == 0) {
		// hit end of word
		// keep searching sub nodes for words
		auto i = subNode.begin();
		while (i != subNode.end()) {
			std::string word =  currWord + i->value_;
			if (i->endOfWord_) {
				// check rest of the word
				output += word;
				output += " ";
			}

			output = restOfWord(i->children_, prefix, word, output);
			++i; // move on to next node
		}
		return output;
	}
	else {
		// finding our way to the end of the word
		char firstLetter = prefix[0];
		std::string rest = prefix.substr(1);
		auto i = subNode.begin();

		while (i != subNode.end()) {
			if (i->value_ == firstLetter) {
				currWord += firstLetter;
				// find rest of word
				return restOfWord(i->children_, rest, currWord, output);
			}
			++i; // keep searching nodes
		}

		// character not in trie... no suggestions
		return output;
	}
}
bool Trie::remove(std::string word)
{
	// to be implemented
	return true;
}

size_t Trie::size() const
{
	return size_;
}

std::ostream& Trie::print(std::ostream& out) const
{
	// find all the words inside the trie
	std::string blank = "";
	out << restOfWord(root_, blank, blank, blank);
	out << std::endl;
	return out;
}

///////////////////////////////////////////////////////////////
///////////// Node Implementation /////////////////////////////
///////////////////////////////////////////////////////////////

Trie::Node::Node(char val)
	: value_{ val }, endOfWord_{ false }, children_ {std::vector<Node>()
}
{
	// nothing to do here
}