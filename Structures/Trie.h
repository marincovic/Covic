#pragma once
#include"MultiChildTree.h"
#include<stdexcept>
#include<vector>
#include <string>
#define ASCII 27
class Trie {
public:
	Trie() 
	{
		m_root = new MultiChildTree<char>('\0', ASCII, true);
	}
	virtual ~Trie() {};

	void AddString(const char* DataOfNewMember) {
		if (!DataOfNewMember)
			throw std::out_of_range("No word to be added");

		MultiChildTree<char>* walkerVariable = m_root;
		
		for (int letterCounter = 0;
		*(DataOfNewMember + letterCounter) != '\0';
		walkerVariable = walkerVariable->GetNextChildAtAdress(tolower(*(DataOfNewMember+letterCounter)) - 'a'), ++letterCounter)
		{
			if(!walkerVariable->GetNextChildAtAdress(tolower(*(DataOfNewMember + letterCounter)) - 'a'))
				walkerVariable->SetNextChildAtAdress(
					tolower(*(DataOfNewMember + letterCounter)) - 'a',
					new MultiChildTree<char>(*(DataOfNewMember + letterCounter), ASCII, true));
		}
		walkerVariable->SetNextChildAtAdress(ASCII-1, new MultiChildTree<char>('\0'));
	}
	void DeleteString(const char* StringToBeRemovedFromTrie) {};

	std::vector<std::string> FindAllWordsThatStartWith(const char* partOfWordToBeFound) {
		std::string wordString;
		std::vector<std::string> wordCollectionVector;
		MultiChildTree<char>* walkerVariable = m_root;

		for (int i = 0; *(partOfWordToBeFound + i) != '\0'; ++i)
		{
			wordString += *(partOfWordToBeFound + i);
			walkerVariable = walkerVariable->GetNextChildAtAdress(tolower(*(partOfWordToBeFound + i)) - 'a');
		}
		for (int i = 0; i < ASCII; ++i)
		{
			if(walkerVariable->GetNextChildAtAdress(i))
				RecursiveFindAllWordsFromPart(wordString, wordCollectionVector, walkerVariable->GetNextChildAtAdress(i));
		}

		return wordCollectionVector;
	};

private:

	void RecursiveFindAllWordsFromPart( std::string& wordString,
		std::vector<std::string>& wordCollectionVector,
		MultiChildTree<char>* trieWalkerVariable)
	{
		if (!trieWalkerVariable )
			return;
		if (trieWalkerVariable->GetDataOfNode() == '\0')
		{
			wordCollectionVector.push_back(wordString);
			return;
		}
		wordString += trieWalkerVariable->GetDataOfNode();
		for (int i = 0; i < ASCII; ++i)
		{
			RecursiveFindAllWordsFromPart(wordString, wordCollectionVector, trieWalkerVariable->GetNextChildAtAdress(i));
		}
		wordString.pop_back();
	}

	MultiChildTree<char>* m_root;

};