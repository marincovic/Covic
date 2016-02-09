#include "CppUnitTest.h"
#include "../Structures/Trie.h"
#include<vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TrieTest)
	{
	public:
		TEST_METHOD(Trie_AddMemberAddsNewWordToTrie)
		{
			Trie trie;
			trie.AddString("Ovo");

		}

		TEST_METHOD(Trie_DeleteOneWordFromTrie)
		{
			Trie trie;
			trie.AddString("Ovo");
			trie.DeleteString("O");
		}

		TEST_METHOD(Trie_DeleteStringThrowsExceptionWhenNoSringMatchingEntryParametarIsFound)
		{
			Trie trie;
			trie.AddString("Ovo");
			trie.DeleteString("oj");
		}

		TEST_METHOD(Trie_FindAllWordsFindsAllTheWordsThatStartWithTheLetterO)
		{
			Trie trie;
			trie.AddString("Ovo");
			trie.AddString("ono");
			trie.AddString("oni");

			Assert::AreEqual(3,(int)trie.FindAllWords("o").size());
		}
	};
}