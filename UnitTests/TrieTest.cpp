#include "CppUnitTest.h"
#include "../Structures/Trie.h"
#include<vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TrieTest)
	{
	public:


		TEST_METHOD(Trie_DeleteOneWordFromTrie)
		{
			Trie trie;
			trie.AddString("Ovo");
			trie.DeleteString("O");
			Assert::AreEqual(0, (int)trie.FindAllWordsThatStartWith("o").size());
			trie.AddString("Ovo");
			trie.AddString("ono");
			trie.AddString("ana");
			trie.DeleteString("o");
			Assert::AreEqual(1, (int)trie.FindAllWords().size());
			trie.AddString("Ovo");
			trie.AddString("ono");
			trie.DeleteString("ovo");
			Assert::AreEqual(2, (int)trie.FindAllWords().size());
		}

		TEST_METHOD(Trie_DeleteStringThrowsExceptionWhenNoSringMatchingEntryParametarIsFound)
		{
			try{
			Trie trie;
			trie.AddString("Ovo");
			trie.DeleteString("oj");
			Assert::Fail();
			}
			catch (const std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		
		TEST_METHOD(Trie_AddStringAddsAllMembersToTrieAndFindAllWordsThatStartWithFindsAllTheWordsThatStartWithTheLetterO)
		{
			Trie trie;
			trie.AddString("Ovo");
			trie.AddString("ono");
			trie.AddString("oni");
			trie.AddString("ana");
			trie.AddString("voli");
			std::vector<std::string> string = trie.FindAllWordsThatStartWith("o");
			Assert::AreEqual(3,(int)string.size());
		}
		
		TEST_METHOD(Trie_FindAllWordsReturnsAllWordsFromTree)
		{
			Trie trie;
			trie.AddString("Ovo");
			trie.AddString("ono");
			trie.AddString("ana");
			trie.AddString("Ovo");
			trie.AddString("ono");
			trie.AddString("oni");
			trie.AddString("ana");
			trie.AddString("voli");
			Assert::AreEqual(5, (int)trie.FindAllWords().size());
		}

		TEST_METHOD(Trie_FindAllWordsThrowExceptionWhenTreeHasNoWords)
		{
			Trie trie;
			try {
				trie.FindAllWords();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
	
		TEST_METHOD(Trie_DeleteTreeRemovesAllWordsFromTree)
		{
			Trie trie;
			trie.AddString("Ovo");
			trie.AddString("ono");
			trie.AddString("ana");
			trie.AddString("Ovo");
			trie.AddString("ono");
			trie.AddString("oni");
			trie.AddString("ana");
			trie.AddString("voli");

			trie.DeleteTree();

			try {
				trie.FindAllWords();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
	};
}