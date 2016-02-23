#include "CppUnitTest.h"
#include "../Structures/DoubleList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(DoubleListTest)
	{
	public:

		TEST_METHOD(DoubleList_SizeMethodForEmptyListReturnsZero)
		{
			DoubleList<int> list;
			Assert::AreEqual(0, list.Size());
		}

		TEST_METHOD(DoubleList_AppendMethodIncreasesSizeOfListByOne)
		{
			DoubleList<int> list;
			list.Append(1);
			Assert::AreEqual(1, list.Size());
		}

		TEST_METHOD(DoubleList_GetAtMethodReturnsElementAtGivenIndex)
		{
			DoubleList<int> list;
			list.Append(5);
			list.Append(3);
			Assert::AreEqual(5, list.GetAt(0));
			Assert::AreEqual(3, list.GetAt(1));
		}

		TEST_METHOD(DoubleList_GetAtThrowsExceptionForNonInitList)
		{
			DoubleList<int> lista;
			try {
				lista.GetAt(0);
				Assert::Fail;
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(DoubleList_RemoveAtMethodDecreasesSizeOfList)
		{
			DoubleList<int> list;
			list.Append(5);
			list.Append(10);
			list.RemoveAt(0);
			Assert::AreEqual(1, list.Size());
		}

		TEST_METHOD(DoubleList_RemoveAtMethodForIndexZeroMovesSecondElementToTheStartOfList)
		{
			DoubleList<int> list;
			list.Append(5);
			list.Append(10);
			list.RemoveAt(0);
			Assert::AreEqual(10, list.GetAt(0));
		}

		TEST_METHOD(DoubleList_RemoveAtMethodForLastIndexRemovesLastElement)
		{
			DoubleList<int> list;
			list.Append(5);
			list.Append(10);
			list.RemoveAt(list.Size() - 1);
			Assert::AreEqual(1, list.Size());
			Assert::AreEqual(5, list.GetAt(0));
		}

		TEST_METHOD(DoubleList_RemoveAtMethodForEmptyListThrowsException)
		{
			try
			{
				DoubleList<int> list;
				list.RemoveAt(0);
				Assert::Fail(L"should throw exception");
			}
			catch (const std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(DoubleList_InsertAtMethodForZeroIndexInsertsElementToTheBeginningOfEmptyList)
		{
			DoubleList<int> list;
			list.InsertAt(0, 5);
			Assert::AreEqual(1, list.Size());
			Assert::AreEqual(5, list.GetAt(0));
		}

		TEST_METHOD(DoubleList_InsertAtMethodForZeroIndexInsertsElementInFrontOfFirstElement)
		{
			DoubleList<int> list;
			list.Append(1);
			list.InsertAt(0, 5);
			Assert::AreEqual(2, list.Size());
			Assert::AreEqual(5, list.GetAt(0));
			Assert::AreEqual(1, list.GetAt(1));
		}

		TEST_METHOD(DoubleList_InsertAtMethodForLastIndexInsertsElementToTheEndOfList)
		{
			DoubleList<int> list;
			list.Append(1);
			list.InsertAt(1, 5);
			Assert::AreEqual(2, list.Size());
			Assert::AreEqual(1, list.GetAt(0));
			Assert::AreEqual(5, list.GetAt(1));
		}

		TEST_METHOD(DoubleList_InsertAtMethodThrowsExceptionForInvalidIndex)
		{
			try
			{
				DoubleList<int> list;
				list.InsertAt(5, 5);
				Assert::Fail();
			}
			catch (const std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		//Iterator Tests
		TEST_METHOD(DoubleList_GetIteratorThrowExceptionForNonInitList)
		{
			try {
				DoubleList<int> lista;
				lista.GetIterator();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		
		TEST_METHOD(DoubleLIst_GetIteratorReturnsFirstMemberOfNewDoubleList)
		{
			DoubleList<int> lista(5);
			Assert::AreEqual(5, lista.GetIterator()->GetData());
		}

		TEST_METHOD(DoubleList_IteratorNextReturnsNextMemberFromListAndSetsIteratorToNextMemberOfList)
		{
			DoubleList<int> lista(5);
			lista.Append(10);
			if (10 == lista.IteratorNext()->GetData())
				Assert::AreEqual(10, lista.GetIterator()->GetData());
			else
				Assert::Fail();
		}

		TEST_METHOD(DoubleList_IteratorNextThrowEceptionForNonInitList)
		{
			try {
				DoubleList<int> lista;
				lista.IteratorNext();
				Assert::Fail();
			}
			catch(std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(DoubleList_IteratorNextThrowExceptionIfListComesToAnEnd)
		{
			try {
				DoubleList<int> lista;
				lista.Append(5);
				lista.IteratorNext();
				lista.IteratorNext();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(DoubleList_SetIteratorAtIndexReturnsTheElementAtIndexAndSetsIteratorAtThatIndex)
		{
			DoubleList<int> lista(5);
			lista.Append(10);
			lista.Append(15);
			if (15 == lista.SetIteratorToAtIndex(3)->GetData())
				Assert::AreEqual(15, lista.GetIterator()->GetData());
			else
				Assert::Fail();
		}

		TEST_METHOD(DoubleList_IteratorPrevThrowExceptionForNonInitList)
		{
			try {
				DoubleList<int> lista;
				lista.IteratorPrev();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}

		}

		TEST_METHOD(DoubleList_IteratorPrevThrowsExceptionIfUsedOnFirstMember)
		{
			try {
				DoubleList<int> lista;
				lista.Append(5);
				lista.IteratorPrev();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(DoubleList_IteratorPrevReturnsPrevMemberAndSetsIteratorTothatMember)
		{
			DoubleList<int> lista(5);
			lista.Append(10);
			lista.Append(15);
			lista.IteratorNext();
			if (5 == lista.IteratorPrev()->GetData())
				Assert::AreEqual(5, lista.GetIterator()->GetData());
			else
				Assert::Fail();
		}

		TEST_METHOD(DoubleList_ResetIteratorSetsIteratorToFirstMember)
		{
			DoubleList<int>lista(5);
			lista.Append(10);
			lista.IteratorNext();
			lista.ResetIterator();
			Assert::AreEqual(5, lista.GetIterator()->GetData());
		}

		TEST_METHOD(DoubleList_ResetIteratorThrowsExceptionForNonInitLIst)
		{
			try {
				DoubleList<int> lista;
				lista.ResetIterator();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
	};
}