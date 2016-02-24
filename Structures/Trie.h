#pragma once
#include"MultiChildTree.h"
#include<stdexcept>
#include<vector>
#include <string>
#define ASCII 27

//delete funkciju potrebno napisati
class Trie {
public:
	Trie() 
	{
		m_root = new MultiChildTree<char>('\0', ASCII, true);
	}
	virtual ~Trie() { 
		DeleteTree();
	delete m_root;
	};

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
	void DeleteString(const char* StringToBeRemoved)
	{
		if (!StringToBeRemoved)
			std::out_of_range("Use DeleteTree Method for deleting whole tree");
		try{
			DeleteStringRecursive(StringToBeRemoved, m_root);
		}
		catch (std::out_of_range& throwVariable)
		{
			throw throwVariable;
		}
	}
	
	std::vector<std::string> FindAllWordsThatStartWith(const char* partOfWordToBeFound) {
		std::string wordString;
		std::vector<std::string> wordCollectionVector;
		MultiChildTree<char>* walkerVariable = m_root;

		if (!m_root->NodeHasChildren())
			return wordCollectionVector;


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
	std::vector<std::string> FindAllWords()
	{
		std::string wordString;
		std::vector<std::string> wordCollectionVector;
		MultiChildTree<char>* walkerVariable = m_root;

		if (!m_root->NodeHasChildren())
			throw std::out_of_range("Tree has no words");

		for (int iterator = 0; iterator < ASCII; ++iterator)
		{
			RecursiveFindAllWords(wordString, wordCollectionVector, walkerVariable->GetNextChildAtAdress(iterator));
		}

		return wordCollectionVector;


	}

	void DeleteTree()
	{
		if (!m_root->NodeHasChildren())
			throw std::out_of_range("Tree is empty");
		for (int iterator = 0; iterator < ASCII; ++iterator)
		{
			delete m_root->GetNextChildAtAdress(iterator);
			m_root->SetNextChildAtAdress(iterator, nullptr);
		}
	}
private:
	void DeleteStringRecursive(const char* StringToBeRemoved, MultiChildTree<char>* walkerVariable)
	{
		if (!walkerVariable->GetNextChildAtAdress(tolower(StringToBeRemoved[0]) - 'a'))
			throw std::out_of_range("ward or part of ward you want to delete does not exist");

		if (walkerVariable->GetNextChildAtAdress(tolower(StringToBeRemoved[0]) - 'a')->GetDataOfNode() == '\0')
		{
			delete walkerVariable->GetNextChildAtAdress(tolower(StringToBeRemoved[0]) - 'a');
			walkerVariable->SetNextChildAtAdress(tolower(StringToBeRemoved[0]) - 'a', nullptr);
			return;
		}

		if (StringToBeRemoved[1] == '\0')
		{
			delete walkerVariable->GetNextChildAtAdress(tolower(StringToBeRemoved[0]) - 'a');
			walkerVariable->SetNextChildAtAdress(tolower(StringToBeRemoved[0]) - 'a', nullptr);
			return;
		}

		DeleteStringRecursive(StringToBeRemoved + 1, walkerVariable->GetNextChildAtAdress(tolower(StringToBeRemoved[0]) - 'a'));
	}
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

	void RecursiveFindAllWords(std::string& wordString,
		std::vector<std::string>& wordCollectionVector,
		MultiChildTree<char>* trieWalkerVariable)
	{
		if (!trieWalkerVariable)
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