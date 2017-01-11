# Trie

## Trie
This is an implementation of a trie. A sample usage of a trie is autocompletion of words. Words sometimes have the same prefixes such as 'you', 'your', and 'yours' share the prefix 'yo'. A trie would allow one to complete words that start with 'yo' very quickly. A trie is very useful when things share common prefixes.

### Usage:

First you must include the header file. After that you can declare the Trie and use the functions that are provided.

```c++
#include "trie.hpp"

int main ()
{
  // default constructor
  Trie simpleEx = trie();
  simpleEx.insert("yo");
  simpleEx.insert("you");
  simpleEx.insert("your");
  simpleEx.insert("yours");
  simpleEx.insert("abc");
  std::cout << simpleEx.restOfWord("yo") << std::endl; // should print yo: you your yours
  return 0;
}
```

### Operation provided:

 * insert
 * exists
 * restOfWord
 * remove
 * removeAll
 * size
 * empty
 * totalNodes
 * showStatistics
 * print

# Resources:

[Wikipedia Page for Trie](https://en.wikipedia.org/wiki/Trie) (used to see what a Trie is)

[Catch](https://github.com/philsquared/Catch). (used for testing)

[10000 most common english-Words](https://github.com/first20hours/google-10000-english) (used for testing with a bunch of words)

[Dr Memory] (http://drmemory.org) (used to check for memery leaks and errors)
