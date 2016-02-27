#include "CppUnitTest.h"
#include "../Structures/GraphNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(GraphNodeTest)
	{
	public: 
		TEST_METHOD(GraphNode_GetDataReturnsDataOFNode)
		{
			GraphNode<int, int> node(5);
			Assert::AreEqual(5, node.GetDataOfNode());
		}

		TEST_METHOD(GraphNode_SetDataOfNodeSetsDataOfNodeToWantedValue)
		{
			GraphNode<int, int> node;
			node.SetDataOFNode(5);
			Assert::AreEqual(5, node.GetDataOfNode());
		}

		TEST_METHOD(GraphNode_GetChildAtIndexsReturnsNullptrWhenGraphHasNoChildren)
		{
			GraphNode<int, int> node(5);
			Assert::AreEqual(static_cast<GraphNode<int,int>*>(nullptr), node.GetChildAtIndex(0));
		}

		TEST_METHOD(GraphNode_GetChildAtIndexThrowsExceptionWhenIndexIsOutOfRange)
		{
			GraphNode<int, int> node(5, 6);
			try {
				node.GetChildAtIndex(2);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(GraphNode_GetChildAtIndexReturnsNextChildInList)
		{
			GraphNode<int, int> node(5, 6);
			Assert::AreEqual(6, node.GetChildAtIndex(0)->GetDataOfNode());
		}
	
		TEST_METHOD(GraphNode_AddNewChildAddsNewChildToListWhenWeightIs0)
		{
			GraphNode<int, int> node(5);
			node.AddNewChild(6);
			Assert::AreEqual(6, node.GetChildAtIndex(0)->GetDataOfNode());
		}

		TEST_METHOD(GraphNode_AddNewChildAddsNewChildViaPointerWhenWeightIs0)
		{
			GraphNode<int, int> node(5);
			node.AddNewChild(new GraphNode<int, int>(6));
			Assert::AreEqual(6, node.GetChildAtIndex(0)->GetDataOfNode());
		}
	
		TEST_METHOD(GraphNode_RemoveChildThrowExceptionIfNodeHasNoChildren)
		{
			try {
				GraphNode<int, int> node;
				node.GetChildAtIndex(0);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
	
		TEST_METHOD(GraphNode_RemoveChildThrowsExceptionIfIdexOutOfRange)
		{
			try {
				GraphNode<int, int> node(5);
				node.GetChildAtIndex(2);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
	
		TEST_METHOD(GraphNode_RemoveChildDefinedByDataType)
		{
			GraphNode<int, int> node(5, 6);
			node.RemoveChild(6);
			try {
				node.GetChildAtIndex(0);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(GraphNode_RemoveChildDefinedByPointer)
		{
			GraphNode<int, int> node1(5);
			GraphNode<int, int>* node2=new GraphNode<int,int>(5);
			node1.AddNewChild(node2);

			node1.RemoveChild(node2);
			try {
				node1.GetChildAtIndex(0);
				Assert::Fail;
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}

		}

		TEST_METHOD(GraphNode_ContainsThrowExceptionIfNodeHasNoChildren)
		{
			GraphNode<int, int> node;
			try {
				node.ContainsChild(1);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(GraphNode_ContainsReturnsTrueIfDataMatchesDataOfAtLeastOneChild)
		{
			GraphNode<int, int> node(5, 6);
			Assert::IsTrue(node.ContainsChild(6));
		}

		TEST_METHOD(GraphMove_ContainsReturnsTrueIfAdressMatchesAddressOfAtLeastOneChild)
		{
			GraphNode<int, int> node1(5);
			GraphNode<int, int>* node2 = new GraphNode<int, int>(6);
			Assert::IsTrue(node1.ContainsChild(node2));
		}
	
		TEST_METHOD(GraphNode_ContainsReturnsFalseIfDataDoesNotMatchAnyChild)
		{
			GraphNode<int, int> node(5, 6);
			Assert::IsFalse(node.ContainsChild(7));
		}

		TEST_METHOD(GraphNode_ContainsReturnsFalseIfAddressDoesNotMatchAnyChildren)
		{
			GraphNode<int, int> node(5, 6);
			Assert::IsFalse(node.ContainsChild(new GraphNode<int, int>()));
		}


	};
}