#include "CppUnitTest.h"
#include "../Structures/BST.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(BSTTest)
	{
	public:
		TEST_METHOD(BST_AddFirstMemberTest) {
			BST<int> bst(3);
			Assert::AreEqual(1, bst.TreeSize());
		}
		TEST_METHOD(BST_AddSecondMemberToLeftTreeSide) {
			BST<int> bst;
			bst.AddNewMember(5);
			bst.AddNewMember(2);
			Assert::AreEqual(2, bst.TreeSize());
		}
		TEST_METHOD(BST_AddSecondMemberToRightTreeside) {
			BST<int> bst(5);
			bst.AddNewMember(10);
			Assert::AreEqual(2, bst.TreeSize());
		}
		TEST_METHOD(BST_Add15RandomMembersToTree) {
			BST<int> bst;
			for (int i = 0; i < 15; ++i)
				//bst.AddNewMember(rand % 50);
				Assert::AreEqual(15, bst.TreeSize());

		}
		TEST_METHOD(BST_ContainsFunctionReturnsTrueIfMemberExists) {
			BST<int> bst(5);
			bst.AddNewMember(2);
			bst.AddNewMember(7);
			Assert::IsTrue(bst.Contains(7));
		}
		TEST_METHOD(BST_ContainsFunctionReturnsFalseIfMemberDoesNotExist) {
			BST<int> bst(5);
			bst.AddNewMember(2);
			bst.AddNewMember(7);
			Assert::IsFalse(bst.Contains(9));
		}
		TEST_METHOD(BST_DeleteRemovesMemberFromTree) {
			BST<int> bst(5);
			bst.AddNewMember(2);
			bst.AddNewMember(7);
			bst.AddNewMember(9);
			bst.AddNewMember(11);
			bst.AddNewMember(10);
			bst.AddNewMember(12);

			bst.Delete(11);

			Assert::IsFalse(bst.Contains(11));

		}
		TEST_METHOD(BST_DeleteThrowsExceptionIfTreeDoesNotContainMember) {
			try {
				BST<int> bst(5);
				bst.AddNewMember(2);
				bst.AddNewMember(7);
				bst.AddNewMember(9);
				bst.AddNewMember(11);
				bst.AddNewMember(10);
				bst.AddNewMember(12);

				bst.Delete(11);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

	};
}