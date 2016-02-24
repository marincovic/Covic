#include "CppUnitTest.h"
#include "../Structures/BST.h"
#include<vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/* 
Prijedlog izgleda stabla za testove

															50
														/		\
													/				\
												/						\
											/								\
										/										\
									30											  70
										\										/	\
											40								  60	 80
										/		\									/	 \
									/				\							  75	   85
								35					45							/	\	   /\
							/		\			/		\					  72	77	 82  88
						   32		37		   42		48					  /\	/	 /   /\
											/		   / \				    71  73 76  81  86  89
										  41		 46	  49			
	{50,30,40,35,32,37,45,42,41,48,46,49,70,60,80,75,72,71,73,77,76,85,82,88,86,89,81}
	prikaz stabla u obliku vektora

*/

namespace UnitTests
{
	TEST_CLASS(BSTTest)
	{
	public:
		std::vector<int> listOfNodesForTest{ 50,30,40,35,32,37,45,42,41,48,46,49,70,60,80,75,72,71,73,77,76,85,82,88,86,89,81 };

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
			Assert::AreEqual(27,bst.TreeSize());
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

			bst.DeleteMember(77);

			Assert::AreEqual(26, (int)bst.InOrderOutput().size());

			bst.DeleteMember(80);

			Assert::AreEqual(25, (int)bst.InOrderOutput().size());

			bst.DeleteMember(50);

			Assert::AreEqual(24, (int)bst.InOrderOutput().size());

			bst.DeleteMember(49);

			Assert::AreEqual(23, (int)bst.InOrderOutput().size());

		}
		
		TEST_METHOD(BST_DeleteThrowsExceptionIfTreeDoesNotContainMember) {
			try {
				BST<int> bst;
				for (int i = 0; i < listOfNodesForTest.size(); ++i)
					bst.AddNewMember(listOfNodesForTest.at(i));

				bst.DeleteMember(11);
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
			Assert::AreEqual(27, (int)bst.PreOrderOutput().size());
		}

		TEST_METHOD(BST_PostOrderReturnsAllMembersOfBSTInRightOrder)
		{
			BST<int> bst;
			for (int i = 0; i < listOfNodesForTest.size(); ++i)
				bst.AddNewMember(listOfNodesForTest.at(i));
			Assert::AreEqual(27, (int)bst.PostOrderOutput().size());
		}
		
		TEST_METHOD(BST_InOrderReturnsAllMembersOfBSTInRightOrder)
		{
			BST<int> bst;
			for (int i = 0; i < listOfNodesForTest.size(); ++i)
				bst.AddNewMember(listOfNodesForTest.at(i));
			Assert::AreEqual(27, (int)bst.InOrderOutput().size());
		}

		TEST_METHOD(BST_ForEmptyTreeTreeSizeFunctionReturnsZero)
		{
			BST<int> bst;
			Assert::AreEqual(0, bst.TreeSize());
		}

		TEST_METHOD(BST_TreeSizeFunctionReturnsSameSizeAfterAddingMemberThatISAlreadyInTheTree)
		{
			BST<int> bst;
			bst.AddNewMember(5);
			Assert::AreEqual(1, bst.TreeSize());
			bst.AddNewMember(5);
			Assert::AreEqual(1, bst.TreeSize());

		}
	};
}