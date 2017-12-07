/**
* \file trie.hpp
*
* \author lhernandezcruz
*
* \brief Interface for Trie
*
*/

// include gaurds
#ifndef TRIE_HPP_INCLUDED
#define TRIE_HPP_INCLUDED 1

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>

/// Amount of words to remove before actually removing unused nodes
const size_t MAXWORDSREMOVED = 20; 
class Trie {
private:
	struct Node;
public:
	/**
	* \brief Default Constructor to create an empty trie
	*/
	Trie();

	/**
	* \brief			Insert a string into the trie
	* \param  word	    Inserted word
	*/
	void insert(std::string word);

	/**
	* \brief			Check if a string exists in the trie
	* \param  word	    Word being checked in the trie
	* \return			true if word is in the trie. false otherwise
	*/
	bool exists(std::string word);

	/**
	* \brief			Tries to guess the rest of the string
	* \param  prefix    Prefix that is being searched
	* \return			A vector with strings in which the input is a prefix
	*/
	std::vector<std::string> restOfString(std::string prefix);

	/**
	* \brief			Remove a string from the trie
	* \param  word      Word being removed
	* \return			true if word is removed from trie. false otherwise
	*/
	bool remove(std::string word);

	/**
	* \brief			Remove all strings from trie
	*/
	void removeAll();

	/**
	* \brief			Gives the size of the trie
	* \return			Amount of strings in trie
	*/
	size_t size() const;

	/**
	* \brief			Tells user if Trie is empty
	* \return			true if Trie is empty. false otherwise
	* \note				Trie can be empty but still have nodes.
	*/
	bool empty() const;

	/**
	* \brief			Totol amount of nodes
	* \return			Total mount of nodes in trie
	* \note             Root Node does not count as node. 
	*						Only nodes that contain chars.
	*					Expensive call because it searches all nodes
	*/
	size_t totalNodes() const;

	/**
	* \brief			Print out Statistics of the trie
	* \param  out		Where to print Trie
	* \return		    ostream with statistics
	* \note				Contains endl at end
	*/
	std::ostream& showStatistics(std::ostream& out) const;

	/**
	* \brief			Print out the words in the trie 
	* \param  out		Where to print Trie
	* \return		    ostream with words in Trie
	* \note				Contains endl at end
	*/
	std::ostream& print(std::ostream& out) const;
private:
	/**
	* \brief			Insert a string into the trie
	* \param  subNode	Which node we are looking to insert word to
	*         word	    Word being inserted
	*/
	void subTrieInsert(Node& subNode, std::string word);

	/**
	* \brief			Insert a string into a subTrie
	* \param  subNode	Which node we are looking to insert word to
	*         word	    Word being inserted
	* \return           true if word exists in subTrie
	*/
	bool subTrieExists(Node& subNode, std::string word);

	/**
	* \brief			Returns strings that contain the input string as a prefix
	* \param  subNode	Which node we are looking to see if word can be completed
	*         prefix	prefix being completed
	*		  currWord  Current word being predicted
	*		  output    A vector that contains predicted words 
	* \return           A vector with predicted words
	*/
	std::vector<std::string> restOfString(const Node& subNode, std::string prefix
									,std::string currWord, std::vector<std::string> output) const;

	/**
	* \brief			Insert a string into a subTrie
	* \param  subNode	Which node we are looking to insert word to
	*         word	    Word being inserted
	* \return           true if word was marked (it existed as a word)
	*/
	bool unmarkEndOfString(Node& subNode, std::string word);

	/**
	* \brief			Remove Nodes that are not part of words
	* \param  subNode	Which node we are looking for unused words
	* \return           true if we should keep the subNode
	* \note				Will only delete unused nodes after a certain
	*					 amount of times unmarking or when trie is empty
	*/
	bool removeUnusedNodes(Node& subNode);

	/**
	* \brief			Counts all the nodes being used
	* \param  subNode	Which node we are counting
	*		  count     Current count of nodes in subNode
	* \return           Total amount of nodes
	*/
	size_t countAllNodes(const Node& subNode, size_t count) const;

	/// NODE DECLARATION
	struct Node {
	public:
		/**
		* \brief Default Constructor
		*/
		Node();

	private:
		friend class Trie; // Trie can see private data members

		bool endOfString_; // true if a node represents end of string. false otherwise
		std::unordered_map<char, std::shared_ptr<Node> > children_; // map of children nodes
	};
	
	/// private data members
	Node root_; // Root Node (empty node with children nodes that contain words)
	size_t size_; // Amount of words contained in the trie
	size_t wordsRemoved_; // Amount of words that have been removed
};

#endif
