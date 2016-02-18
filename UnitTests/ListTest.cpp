#include "CppUnitTest.h"
#include "../Structures/List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(ListTest)
	{
	public:

		TEST_METHOD(List_SizeMethodReturnsZeroForEmptyList)
		{
			List<int> list;
			Assert::AreEqual(0, list.Size());
		}

		TEST_METHOD(List_AppendMethodIncreasesSizeOfListByOne)
		{
			List<int> list;
			list.Append(1);
			Assert::AreEqual(1, list.Size());
		}

		TEST_METHOD(List_GetAtMethodReturnsElementAtGivenIndex)
		{
			List<int> list;
			list.Append(5);
			Assert::AreEqual(5, list.GetAt(0));
		}

		TEST_METHOD(List_RemoveAtMethodDecreasesSizeOfList)
		{
			List<int> list;
			list.Append(5);
			list.Append(10);
			list.RemoveAt(0);
			Assert::AreEqual(1, list.Size());
		}

		TEST_METHOD(List_RemoveAtMethodForIndexZeroMovesSecondElementoTheStartOfList)
		{
			List<int> list;
			list.Append(5);
			list.Append(10);
			list.RemoveAt(0);
			Assert::AreEqual(10, list.GetAt(0));
		}

		TEST_METHOD(List_RemoveAtMethodForLastIndexRemovesElementFromTheEndOfList)
		{
			List<int> list;
			list.Append(5);
			list.Append(10);
			list.RemoveAt(list.Size() - 1);
			Assert::AreEqual(1, list.Size());
			Assert::AreEqual(5, list.GetAt(0));
		}

		TEST_METHOD(List_RemoveAtMethodThrowsExceptionForEmptyList)
		{
			try
			{
				List<int> list;
				list.RemoveAt(0);
				Assert::Fail(L"should throw exception");
			}
			catch (const std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(List_InsertAtMethodForZeroIndexInsertsElementToTheBeginningOfList)
		{
			List<int> list;
			list.Append(1);
			list.InsertAt(0, 5);
			Assert::AreEqual(2, list.Size());
			Assert::AreEqual(5, list.GetAt(0));
			Assert::AreEqual(1, list.GetAt(1));
		}

		TEST_METHOD(List_InsertAtMethodForLastIndexInsertsElementToTheEndOfList)
		{
			List<int> list;
			list.Append(1);
			list.InsertAt(1, 5);
			Assert::AreEqual(2, list.Size());
			Assert::AreEqual(1, list.GetAt(0));
			Assert::AreEqual(5, list.GetAt(1));
		}

		TEST_METHOD(List_InsertAtMethodThrowsExceptionForInvalidIndex)
		{
			try
			{
				List<int> list;
				list.InsertAt(1, 5);
				Assert::Fail();
			}
			catch (const std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		
		TEST_METHOD(List_PopMethodReturnsValueOfFirstMember)
		{
			try {
				List<int> list;
				list.Append(5);
				list.Append(4);
				list.Append(3);
				Assert::AreEqual(5, list.Pop());
				Assert::AreEqual(2, list.Size());
			}
			catch (const std::out_of_range&)
			{
				Assert::Fail();
			}

		}

		TEST_METHOD(List_PopMethodThrowsErrorIfListIsEmpty)
		{
			try {
				List<int> list;
				list.Pop();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}

		}
		
		TEST_METHOD(List_DequeueReturnsValoueOfLastMember)
		{
			try {
				List<int> list;
				list.Append(5);
				list.Append(10);
				list.Append(15);
				Assert::AreEqual(15, list.Dequeue());
			}
			catch (const std::out_of_range&)
			{
				Assert::Fail();
			}

		}

		TEST_METHOD(List_DequeueMethodThrowsErrorIfListIsEmpty)
		{
			try {
				List<int> list;
				list.Dequeue();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}

		}

		TEST_METHOD(List_IteratorReturnsFirstMemberOfList)
		{
			List<int> list;
			list.Append(5);
			Assert::AreEqual(5, list.GetIteratorData());
		}

		TEST_METHOD(List_IteratorThrowsExceptionForNotInitLists)
		{
			try {
				List<int> list;
				list.GetIteratorData();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(List_IteratorNextReturnsDataFromSecondMember)
		{
			List<int> list;
			list.Append(5);
			list.Append(10);
			list.Append(15);
			Assert::AreEqual(10, list.IteratorNext()->GetData());
		}

		TEST_METHOD(List_IteratorThrowExceptionForNonInitLIst)
		{
			try {
				List<int> list;
				list.IteratorNext();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(List_SetIteratorAtIndexSetsIteratorToSecondNode)
		{
			List<int> list;
			list.Append(5);
			list.Append(10);
			list.Append(15);

			list.SetIteratorAtIndex(2);

			Assert::AreEqual(15, list.GetIteratorData());
		}

		TEST_METHOD(LIST_ContainsFunctionReturnsTrueWhenMemberHasBeenFound)
		{
			List<int> list;
			list.Append(5);
			list.Append(10);
			list.Append(15);
			Assert::IsTrue(list.ContainsElement(10));
		}

		TEST_METHOD(List_ContainsElementThrowExceptionForEmptyList)
		{
			try {
				List<int> list;
				list.ContainsElement(5);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(List_DeleteMemberRemovesFirstMemberFromList)
		{
			List<int> list;
			list.Append(5);
			list.Append(10);
			list.Append(15);
			list.DeleteMember(5);
			Assert::IsFalse(list.ContainsElement(5));
		}

		TEST_METHOD(List_DeleteMemberRemovesAnyElementFromList)
		{

			List<int> list;
			list.Append(5);
			list.Append(10);
			list.Append(15);
			list.DeleteMember(10);
			Assert::IsFalse(list.ContainsElement(10));
		}
	};
}