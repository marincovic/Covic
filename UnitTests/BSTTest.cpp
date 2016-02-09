#include "CppUnitTest.h"
#include "../Structures/BST.h"
#include<vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/* 
Prijedlog izgleda stabla za testove

				10
			/		\
		/				\
		5				15
		/\				/\
	/		\		/		\
	2		8		12		18

	{10,5,15,2,8,12,18}
	prikaz stabla u obliku vektora

*/

namespace UnitTests
{
	TEST_CLASS(BSTTest)
	{
	public:
		std::vector<int> listOfNodesForTest{ 10,5,15,2,8,12,18 };
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
		
		TEST_METHOD(BST_AddVectorToTreeMembersToTree) {
			BST<int> bst;
			for (int i = 0; i < listOfNodesForTest.size(); ++i)
				bst.AddNewMember(listOfNodesForTest.at(i));
			Assert::AreEqual(7,bst.TreeSize());
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
			BST<int> bst;
			for (int i = 0; i < listOfNodesForTest.size(); ++i)
				bst.AddNewMember(listOfNodesForTest.at(i));

			bst.Delete(15);

			Assert::IsFalse(bst.Contains(15));

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
		
		TEST_METHOD(BST_PreOrderOutputMethodThrowsExceptionForNonInitTree)
		{
			try {
				BST<int> bst;
				bst.PreOrderOutput();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		
		TEST_METHOD(BST_PostOrderOutputMethodThrowsExceptionForNonInitTree)
		{
			try {
				BST<int> bst;
				bst.PostOrderOutput();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		
		TEST_METHOD(BST_InOrderOutputMethodThrowsExceptionForNonInitTree)
		{
			try {
				BST<int> bst;
				bst.InOrderOutput();
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(BST_PreOrderReturnsAllMembersOfBSTInRightOrder)
		{
			BST<int> bst;
			for (int i = 0; i < listOfNodesForTest.size(); ++i)
				bst.AddNewMember(listOfNodesForTest.at(i));
			Assert::AreEqual(7, (int)bst.PreOrderOutput().size());
		}

		TEST_METHOD(BST_PostOrderReturnsAllMembersOfBSTInRightOrder)
		{
			BST<int> bst;
			for (int i = 0; i < listOfNodesForTest.size(); ++i)
				bst.AddNewMember(listOfNodesForTest.at(i));
			Assert::AreEqual(7, (int)bst.PostOrderOutput().size());
		}
		
		TEST_METHOD(BST_InOrderReturnsAllMembersOfBSTInRightOrder)
		{
			BST<int> bst;
			for (int i = 0; i < listOfNodesForTest.size(); ++i)
				bst.AddNewMember(listOfNodesForTest.at(i));
			Assert::AreEqual(7, (int)bst.InOrderOutput().size());
		}
	};
}