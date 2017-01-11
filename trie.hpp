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
#include <map>
#include <iostream>

/// how many words we can remove before we remove unused nodes
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
	* \param  word	    inserted word
	*/
	void insert(std::string word);

	/**
	* \brief			Check if a string exists in the trie
	* \param  word	    word being checked in the trie
	* \return			true if word is in the trie. false otherwise
	*/
	bool exists(std::string word);

	/**
	* \brief			Tries to guess the rest of the word
	* \param  prefix    Prefix of the word that is being searched
	* \return			Possible words that prefix could be
	* 				      format: prefix: predicted words (alphabetical order)
	*/
	std::string restOfWord(std::string prefix);

	/**
	* \brief			Remove a string from the trie
	* \param  word      Word being removed
	* \return			true if word is removed from trie. false otherwise
	*/
	bool remove(std::string word);

	/**
	* \brief			Remove all words from trie
	*/
	void removeAll();

	/**
	* \brief			Gives the size of the trie
	* \return			amound of 'words' in trie
	*/
	size_t size() const;

	/**
	* \brief			Tells user if Trie is empty
	* \return			true is Trie is empty
	*/
	bool empty() const;

	/**
	* \brief			total nodes
	* \return			amount of nodes in trie
	* \note             Root Node does not count as node. 
	*						Only nodes that contain chars.
	*/
	size_t totalNodes() const;

	/**
	* \brief			Print out Statistics of the trie
	* \param  out		where to print Trie
	* \return		    ostream with statistics
	* \note				contains endl at end
	*/
	std::ostream& showStatistics(std::ostream& out) const;

	/**
	* \brief			Print out the words in the trie 
	* \param  out		where to print Trie
	* \return		    ostream 
	* \note				contains endl at end
	*/
	std::ostream& print(std::ostream& out) const;
private:
	/**
	* \brief			Insert a string into the trie
	* \param  subNode	which node we are looking to insert word to
	*         word	    word being inserted
	*/
	void subTrieInsert(Node& subNode, std::string word);

	/**
	* \brief			Insert a string into a subTrie
	* \param  subNode	which node we are looking to insert word to
	*         word	    word being inserted
	* \return           true if word exists in subTrie
	*/
	bool subTrieExists(Node& subNode, std::string word);

	/**
	* \brief			Returns words that contain the input word as a prefix
	* \param  subNode	which node we are looking to see if word can be completed
	*         prefix	word being completed
	*		  currWord  current word being predicted
	*		  output    string that will ultimately be returned. 
	* \return           a string in the format. prefix: predicted words (in alphabetical order)
	*/
	std::string restOfWord(const Node& subNode, std::string prefix
									,std::string currWord, std::string output) const;

	/**
	* \brief			Insert a string into a subTrie
	* \param  subNode	which node we are looking to insert word to
	*         word	    word being inserted
	* \return           true if word was unmarked (it existed as a word)
	*/
	bool unmarkEndOfWord(Node& subNode, std::string word);

	/**
	* \brief			Remove Nodes that are not part of words
	* \param  subNode	which node we are looking for unused words
	* \return           true if we should keep the subNode
	* \note				will only delete unused nodes after a certain
	*					 amount of times unmarking or when trie is empty
	*/
	bool removeUnusedNodes(Node& subNode);

	/**
	* \brief			Counts all the nodes being used
	* \param  subNode	which node we are counting
	*		  count     current count of nodes in subNode
	* \return           total amount of nodes
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
		friend class Trie; // trie can see private data members

		bool endOfWord_; // true if a node represents end of word
		std::map<char, Node> children_; // map of children nodes
	};
	
	/// private data members
	Node root_; // root Node (empty node with children nodes that contain words)
	size_t size_; // how many words contained in the trie
	size_t wordsRemoved_; // how many words have been removed
};

#endif
