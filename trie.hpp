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
class Trie {
private:
	struct Node;
public:
	/**
	* \brief Default Constructor to create an empty trie
	*/
	Trie();

	/**
	* \brief Destructor
	*/
	~Trie();

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


	/// NODE DECLARATION
	struct Node {
	public:
		/**
		* \brief Default constructor
		*/
		Node();

	private:
	};
};
#endif
