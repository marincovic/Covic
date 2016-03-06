#include <array>
#include "CppUnitTest.h"
#include "../Structures/GraphNode.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(GraphNode2Test)
	{
	public:
		TEST_METHOD(GraphNode_NumberOfChildrenMethodReturnsZeroForSingleNode)
		{
			GraphNode<int> node(5);
			Assert::AreEqual(size_t(0), node.NumberOfSuccessors());
		}

		TEST_METHOD(GraphNode_GetIdMethodReturnsIdOfNode)
		{
			GraphNode<int> node(9);
			Assert::AreEqual(9, node.GetId());
		}

		TEST_METHOD(GraphNode_AddMemberMethodIncreasesNumberOfChildNodes)
		{
			GraphNode<int> node(5);
			Assert::AreEqual(size_t(0), node.NumberOfSuccessors());
			node.AddSuccessor(10);
			Assert::AreEqual(size_t(1), node.NumberOfSuccessors());
		}
		
		TEST_METHOD(GraphNode_GetChildDataReturnsContentOfTheChildNodeForASingleChild)
		{
			GraphNode<int> node(5);
			node.AddSuccessor(10);
			Assert::IsTrue(node.HasSuccessor(10));
		}

		TEST_METHOD(GraphNode_GetChildDataReturnsContentOfCorrespondingChildNodeForMultipleChildren)
		{
			GraphNode<int> node(5);
			std::vector<int> successorIds{ 10, 15, 20 };
			for (auto value : successorIds)
				node.AddSuccessor(value);

			for (size_t i = 0; i < node.NumberOfSuccessors(); ++i)
				Assert::IsTrue(node.HasSuccessor(successorIds[i]));
		}

		// ovaj test nema potrebe raditi jer ste ovo provjerili veæ u testu GraphNode_AddMemberMethodIncreasesNumberOfChildNodes
		//TEST_METHOD(GraphNode_AddMemberAddsConnectionToExistingNode)
		//{
		//	GraphNode<int> node1(5);
		//	std::shared_ptr<GraphNode<int>> node2 = std::make_shared<GraphNode<int>>(10);
		//	node1.AddMember(node2);
		//	Assert::AreEqual(1u, node1.NumberOfChildren());
		//}

		// nema potrebe ovo testirati jer SetDataOfMember nema smisla
		//TEST_METHOD(GraphNode_SetDataOfMemberSetsDataToNewValue)
		//{
		//	GraphNode<int> node(5);
		//	Assert::AreEqual(5, node.GetId());
		//	node.SetDataOfMember(9);
		//	Assert::AreEqual(9, node.GetId());
		//}

		TEST_METHOD(GraphNode_ContainsSuccessorMethodReturnsTrueIfNodeDoesContainSuccessor)
		{
			GraphNode<int> node(5);
			node.AddSuccessor(10);
			node.AddSuccessor(15);
			Assert::IsTrue(node.HasSuccessor(10));
			Assert::IsTrue(node.HasSuccessor(15));
		}
		
		TEST_METHOD(GraphNode_ContainsSuccessorReturnsFalseIfNodeDoesNotContainSuccessor)
		{
			GraphNode<int> node(5);
			node.AddSuccessor(10);
			node.AddSuccessor(15);
			Assert::IsFalse(node.HasSuccessor(6));
		}

		TEST_METHOD(GraphNode_RemoveSuccessorMethodRemovesSuccessorWithGivenId)
		{
			GraphNode<int> node(5);
			node.AddSuccessor(10);
			node.AddSuccessor(15);
			node.RemoveSuccessor(10);
			Assert::IsFalse(node.HasSuccessor(10));
			Assert::AreEqual(size_t(1), node.NumberOfSuccessors());
		}
		
		TEST_METHOD(GraphNode_RemoveSuccessorMethodThrowsExceptionIfNodeDoesNotContainSuccessorToBeDeleted)
		{
			GraphNode<int> node(5);
			node.AddSuccessor(10);
			node.AddSuccessor(15);
			try {
				node.RemoveSuccessor(9);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		//TEST_METHOD(GraphNode_GetSuccessorMethodThrowsExceptionIfSuccessorWithGivenIdDoesNotExist)
		//{
		//	GraphNode<int> node(5);
		//	Assert::IsTrue(node.GetSuccessorId(0) == nullptr);
		//}
		//
		//TEST_METHOD(GraphNode_GetChildAtIndexThrowExceptionIfIndexsOutOfRange)
		//{
		//	GraphNode<int> node(5);
		//	node.AddMember(10);
		//	try
		//	{
		//		node.GetChildNodeAtIndex(9);
		//		Assert::Fail();
		//	}
		//	catch (std::out_of_range&)
		//	{
		//		Assert::IsTrue(true);
		//	}
		//}
		//
		//TEST_METHOD(GraphNode_GetChildAtIndexReturnsChildFromGivenIndex)
		//{
		//	GraphNode<int> node(5);
		//	node.AddMember(10);
		//	node.AddMember(15);
		//	Assert::AreEqual(10, node.GetChildNodeAtIndex(0)->GetDataOfMember());
		//}

		TEST_METHOD(GraphMove_GetWeightOfMovementToSuccessorMethodReturnsWeightOfMovementForExistingNodeId)
		{
			GraphNode<int> node(5);
			node.AddSuccessor(10, 10);
			node.AddSuccessor(15, 15);
			Assert::AreEqual(10.0, node.GetWeightOfMovementToSuccessor(10));
		}

		TEST_METHOD(GraphMove_GetWeightOfMovementToSuccessorMethodThrowsExceptionForNonexistingSuccessor)
		{
			GraphNode<int> node(1);
			try
			{
				node.GetWeightOfMovementToSuccessor(10);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		// ovaj test nema smisla jer neæemo nasljednike dohvaæati preko indeksa
		//TEST_METHOD(GraphNode_GetWeightOfMovementToChildAtIndexThrowsExceptionIfIndexOutOfRange)
		//{
		//	GraphNode<int> node{ 2 };
		//	try
		//	{
		//		node.GetWeightOfMovementToSuccessor(1);
		//		Assert::Fail();
		//	}
		//	catch (std::out_of_range&)
		//	{
		//		Assert::IsTrue(true);
		//	}
		//}

	};
}