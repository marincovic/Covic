#pragma once
#include"MultiChildTree.h"
#include<stdexcept>
#include<vector>
class Trie {
public:
	Trie() 
	{
		m_root = new MultiChildTree<char>('\0', 26, true);
	}
	virtual ~Trie() {};

	void AddString(const char* DataOfNewMember) {};
	void DeleteString(const char* StringToBeRemovedFromTrie) {};

	std::vector<char*> FindAllWords(const char* partOfWordToBeFound) {};

private:
	MultiChildTree<char>* m_root;

};