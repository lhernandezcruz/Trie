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
	: root_{ Node() }, size_{ 0 }, wordsRemoved_{ 0 }
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

void Trie::subTrieInsert(Node& subNode, std::string word)
{
	// base case is that we are inserting last character
	if (word.size() == 1) {
		// search nodes for character
		auto found = subNode.children_.find(word[0]);

		if (found != subNode.children_.end()) {
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
			Node insertee = Node();
			insertee.endOfWord_ = true;
			subNode.children_.insert({ word[0], insertee });
			++size_;
		}

	} else {
		// inserting a word that is longer than 1 char

		std::string rest = word.substr(1);
		// check if the first character is inside the map
		auto found = subNode.children_.find(word[0]);
		if (found != subNode.children_.end()) {
			// first char there already
			//  so we just insert the rest of the word
			// found->second.children_
			subTrieInsert(found->second, rest);
		}
		else {
			// first char is not inside the map
			// insert rest of the word and add it to the map
			Node insertee = Node();
			subTrieInsert(insertee, rest);
			subNode.children_.insert({ word[0], insertee });
		}
	}
}

bool Trie::exists(std::string word)
{
	// look for word in trie
	return (word.size() != 0 && subTrieExists(root_, word));
}

bool Trie::subTrieExists(Node& subNode, std::string word)
{
	// base case is that we have one letter left to check
	if (word.size() == 1) {
		// need it to be in the map, and be the end of a word
		auto found = subNode.children_.find(word[0]);
		return ((found != subNode.children_.end()) && (found->second.endOfWord_));
	}
	else {
		// checking for existance of a word that is longer than 1 char

		std::string rest = word.substr(1);
		// check if the first character is in the map
		auto found = subNode.children_.find(word[0]);
		if (found != subNode.children_.end()) {
			// search for rest of word
			return subTrieExists(found->second, rest);
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

std::string Trie::restOfWord(const Node& subNode, std::string prefix,
									std::string currWord, std::string output) const
{
	// base case we found the end of the word
	if (prefix.size() == 0) {
		// keep searching sub nodes for words
		auto i = subNode.children_.begin();
		while (i != subNode.children_.end()) {
			std::string word =  currWord + i->first;
			if (i->second.endOfWord_) {
				// check rest of the word
				output += word;
				output += " ";
			}

			output = restOfWord(i->second, prefix, word, output);
			++i; // move on to next node
		}
		return output;
	}
	else {
		// finding our way to the end of the word
		std::string rest = prefix.substr(1);
		auto found = subNode.children_.find(prefix[0]);
		if (found != subNode.children_.end()) {
			// found first letter. now we move on to rest of word
			currWord += prefix[0];
			return restOfWord(found->second, rest, currWord, output);
		}

		// character not in trie... no suggestions
		return output;
	}
}
bool Trie::remove(std::string word)
{
	return unmarkEndOfWord(root_, word);
}

void Trie::removeAll()
{
	root_.children_ = std::map<char, Node>();
	size_ = 0;
	wordsRemoved_ = 0;
}

bool Trie::unmarkEndOfWord(Node& subNode, std::string word)
{
	// base case is that we have one letter left to check
	if (word.size() == 1) {
		// need it to be in the map, and be the end of a word
		auto found = subNode.children_.find(word[0]);

		// check if it is the last char in a word
		bool lastChar = ((found != subNode.children_.end()) && (found->second.endOfWord_));
		if (lastChar) {
			// umark as end of word. decrease size
			found->second.endOfWord_ = false;
			--size_;
			++wordsRemoved_;
			
			// check if we need to remove unused nodes
			if (wordsRemoved_ == MAXWORDSREMOVED || empty()) {
				removeUnusedNodes(root_); // removing unused nodes
				wordsRemoved_ = 0;
			}
		
			// finished unmarking end of word
			return true;
		}

		// didnt unmark end of word... return false
		return false;
	}
	else {
		// checking for existance of a word that is longer than 1 char

		std::string rest = word.substr(1);
		// check if the first character is in the map
		auto found = subNode.children_.find(word[0]);
		if (found != subNode.children_.end()) {
			// search for rest of word
			return unmarkEndOfWord(found->second, rest);
		}

		// character not in trie. means word does not exist in trie
		return false;
	}
}

bool Trie::removeUnusedNodes(Node& subNode)
{
	// try to found end of word
	auto node = subNode.children_.begin();
	bool keepNodes = false;
	while (node != subNode.children_.end()) {
		// search to see if we need to remove subNode
		bool keepSubNode = removeUnusedNodes(node->second);
		
		// we do not contain end of word... and no child does either
		if (!node->second.endOfWord_ && !keepSubNode) {
			node = subNode.children_.erase(node);
		}
		else {
			// contains either an end of word... or a child does
			//  so we keep this node
			++node;
			keepNodes = true;
		}
	}
		
	// return whether we should keep nodes or not
	return keepNodes;
}

size_t Trie::countAllNodes(const Node& subNode, size_t count) const
{
	// count nodes
	auto found = subNode.children_.begin();
	while (found != subNode.children_.end()) {
		// we are a node... so incrememnt count
		++count;

		// add size of children nodes
		count += countAllNodes(found->second, 0);

		// search rest of nodes
		++found;
	}
	// return the count
	return count;
}

size_t Trie::size() const
{
	return size_;
}

bool Trie::empty() const
{
	return size_ == 0;
}

size_t Trie::totalNodes() const
{
	return countAllNodes(root_, 0);
}

std::ostream& Trie::showStatistics(std::ostream& out) const
{
	out << "Words contained: " << size_;
	out << ", Total nodes: " << totalNodes();
	out << ", Words left till removing unused nodes: " << (MAXWORDSREMOVED - wordsRemoved_);
	out << std::endl;
	return out;
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

Trie::Node::Node()
	: endOfWord_ { false }, children_{ std::map<char, Node>() }
{
	// nothing to do here
}

