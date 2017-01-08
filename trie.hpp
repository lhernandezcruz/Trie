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
#include <iostream>

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
	*/
	void insert(std::string word);

	/**
	* \brief			Check if a string exists in the trie
	* \return			true if word is in the trie. false otherwise
	*/
	bool exists(std::string word);

	/**
	* \brief			Tries to guess the rest of the word
	* \param  prefix    Prefix of the word that is being searched
	* \return			At most 3? possible words that it could be
	*					   space if it cant be found in the dictionary
	*/
	std::string restOfWord(std::string prefix);

	/**
	* \brief			Remove a string from the trie
	* \return			true if word is removed from trie. false otherwise
	*/
	bool remove(std::string word);

	/**
	* \brief     Gives the size of the trie
	* \return	 size of trie
	*/
	size_t size() const;

	/**
	* \brief	 Print out the words in the trie 
	* \return	 ostream 
	*/
	std::ostream& print(std::ostream& out) const;
private:
	/// private data members
	std::vector<Node> root_; // pointer to the root Node array
	size_t size_; // how many words have been put into the trie

	/// return true if the thing inserted before it was the last letter
	bool subTrieInsert(std::vector<Node>& subNode, std::string word); 

	/// return true if the word exists
	bool subTrieExists(std::vector<Node>& subNode, std::string word);

	/// print the rest of the word
	std::string restOfWord(std::vector<Node>& subNode, std::string prefix
									,std::string currWords, std::string output);

	/// NODE DECLARATION
	struct Node {
	public:
		// no default constructor
		Node() = delete;

		/**
		* \brief		Parameterized Constructor
		* \param  val	is the char value of the node
		*		  end   tells whether node is end of a word
		*/
		Node(char val);

	private:
		friend class Trie;

		char value_; // value of the Node
		bool endOfWord_; // true if end of a node that represents end of word
		std::vector<Node> children_; // pointer to array of children array
	};
};
#endif
