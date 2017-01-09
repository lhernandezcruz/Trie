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
	: root_{ std::map<char, Node>() }, size_{ 0 }
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

void Trie::subTrieInsert(std::map<char, Node>& subNode, std::string word)
{
	// base case is that we are inserting last character
	if (word.size() == 1) {
		// search nodes for character
		auto found = subNode.find(word[0]);

		if (found != subNode.end()) {
			// character is in the map
			if (!found->second.endOfWord_) {
				// character was not end of word. so we mark it as so
				//  and increment size
				found->second.endOfWord_ = true;
				++size_;
			}
		}
		else {
			// character not inside the map
			// add pair to map, increment size
			Node insertee = Node(word[0]);
			insertee.endOfWord_ = true;
			subNode.insert({ word[0], insertee });
			++size_;
		}

	} else {
		// inserting a word that is longer than 1 char

		std::string rest = word.substr(1);
		// check if the first character is inside the map
		auto found = subNode.find(word[0]);
		if (found != subNode.end()) {
			// first char there already
			//  so we just insert the rest of the word
			subTrieInsert(found->second.children_, rest);
		}
		else {
			// first char is not inside the map
			// insert rest of the word and add it to the map
			Node insertee = Node(word[0]);
			subTrieInsert(insertee.children_, rest);
			subNode.insert({ word[0], insertee });
		}
	}
}

bool Trie::exists(std::string word)
{
	// look for word in trie
	return (word.size() != 0 && subTrieExists(root_, word));
}

bool Trie::subTrieExists(std::map<char, Node>& subNode, std::string word)
{
	// base case is that we have one letter left to check
	if (word.size() == 1) {
		// need it to be in the map, and be the end of a word
		auto found = subNode.find(word[0]);
		return ((found != subNode.end()) && (found->second.endOfWord_));
	}
	else {
		// checking for existance of a word that is longer than 1 char

		std::string rest = word.substr(1);
		// check if the first character is in the map
		auto found = subNode.find(word[0]);
		if (found != subNode.end()) {
			// search for rest of word
			return subTrieExists(found->second.children_, rest);
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

std::string Trie::restOfWord(const std::map<char, Node>& subNode, std::string prefix,
									std::string currWord, std::string output) const
{
	// base case we found the end of the word
	if (prefix.size() == 0) {
		// keep searching sub nodes for words
		auto i = subNode.begin();
		while (i != subNode.end()) {
			std::string word =  currWord + i->second.value_;
			if (i->second.endOfWord_) {
				// check rest of the word
				output += word;
				output += " ";
			}

			output = restOfWord(i->second.children_, prefix, word, output);
			++i; // move on to next node
		}
		return output;
	}
	else {

		// finding our way to the end of the word
		std::string rest = prefix.substr(1);
		auto found = subNode.find(prefix[0]);
		if (found != subNode.end()) {
			// found first letter. now we move on to rest of the word
			currWord += prefix[0];
			return restOfWord(found->second.children_, rest, currWord, output);
		}

		// character not in trie... no suggestions
		return output;
	}
}
bool Trie::remove(std::string word)
{
	return subTrieRemove(root_, word);
}

bool Trie::subTrieRemove(std::map<char, Node>& subNode, std::string word)
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
	: value_{ val }, endOfWord_{ false }, children_ { std::map<char, Node>()
}
{
	// nothing to do here
}

bool Trie::Node::operator==(const Node &other) const
{
	// value_, endOfWord_, and children_ must be true
	return (value_ == other.value_
		&& endOfWord_ == other.endOfWord_
		&& children_ == other.children_);
}

bool Trie::Node::operator<(const Node& other) const
{
	return (value_ < other.value_);
}

bool Trie::Node::operator>(const Node& other) const
{
	return !(*this < other);
}