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
			Assert::AreEqual(5, list.GetAt(1));
		}

		TEST_METHOD(DoubleList_RemoveAtMethodDecreasesSizeOfList)
		{
			DoubleList<int> list;
			list.Append(5);
			list.Append(10);
			list.RemoveAt(1);
			Assert::AreEqual(1, list.Size());
		}

		TEST_METHOD(DoubleList_RemoveAtMethodForIndexZeroMovesSecondElemenToTheStartOfList)
		{
			DoubleList<int> list;
			list.Append(5);
			list.Append(10);
			list.RemoveAt(1);
			Assert::AreEqual(5, list.GetAt(1));
		}

		TEST_METHOD(DoubleList_RemoveAtMethodForLastIndexRemovesLastElement)
		{
			DoubleList<int> list;
			list.Append(5);
			list.Append(10);
			list.RemoveAt(list.Size() - 1);
			Assert::AreEqual(1, list.Size());
		}

		TEST_METHOD(DoubleList_RemoveAtMethodForEmptyListThrowsException)
		{
			try
			{
				DoubleList<int> list;
				list.RemoveAt(1);
				Assert::Fail(L"should throw exception");
			}
			catch (const std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(DoubleList_InsertAtMethodForZeroIndexInsertsElementToTheBeginningOfList)
		{
			DoubleList<int> list;
			list.Append(1);
			list.InsertAt(1, 5);
			Assert::AreEqual(2, list.Size());
			Assert::AreEqual(1, list.GetAt(1));
			Assert::AreEqual(5, list.GetAt(2));
		}

		TEST_METHOD(DoubleList_InsertAtMethodForLastIndexInsertsElementToTheEndOfList)
		{
			DoubleList<int> list;
			list.Append(1);
			list.InsertAt(1, 5);
			Assert::AreEqual(2, list.Size());
			Assert::AreEqual(1, list.GetAt(1));
			Assert::AreEqual(5, list.GetAt(2));
		}

		TEST_METHOD(DoubleList_InsertAtMethodThrowsExceptionForInvalidIndex)
		{
			try
			{
				DoubleList<int> list;
				list.Append(1);
				list.InsertAt(5, 5);
				Assert::Fail();
			}
			catch (const std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

	};
}