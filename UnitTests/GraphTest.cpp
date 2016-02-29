#include "CppUnitTest.h"
#include "../Structures/Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(GraphTest)
	{
	public:
		//Testovi za NumberOfNodesInGraph metodu
		TEST_METHOD(Graph_NumberOfNodesInGraphReturns1ForGraphWithOnlyOneNode)
		{
			Graph<int> graph(5);
			Assert::AreEqual(1, graph.NumberOfNodesInGraph());
		}

		//Testovi za AddNode Metodu
		TEST_METHOD(Graph_AddNodeAddsNewNodeToGraph)
		{
			Graph<int> graph(5);
			graph.AddNode(9, 5);
			Assert::AreEqual(2, graph.NumberOfNodesInGraph());
		}
		TEST_METHOD(Graph_AddNodeThrowsExceptionWhenParentDoesNotExist)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);

			try {
				graph.AddNode(9, 3);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}


		//Testovi za ContainsNode metodu
		TEST_METHOD(Graph_ContainsNodeReturnsTrueIfDataIsPartOfANodeInGraph)
		{
			Graph<int> graph(5);
			graph.AddNode(6,5);

			Assert::IsTrue(graph.ContainsNode(5));
		}
		TEST_METHOD(Graph_ContainsNodeReturnsFalseIfDataIsNotPartOfANodeInGraph)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);

			Assert::IsFalse(graph.ContainsNode(7));
		}

		//Testovi za DataOfNode metodu
		TEST_METHOD(Graph_DataOfNodeReturnsDataOfNodeToBeFound)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			Assert::AreEqual(5, graph.DataOfNode(5));
		}
		TEST_METHOD(Graph_DataOfNodeThrowsExceptionIfMemberIsNotFound)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			try {
				graph.DataOfNode(7);
				Assert::Fail;
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		
		//Testovi za CheckConnection metodu
		TEST_METHOD(Graph_CheckConnectionReturnsTrueIfParentIsConnectedToChild)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);

			Assert::IsTrue(graph.CheckConnection(5, 6));
		}
		TEST_METHOD(Graph_CheckConnectionReturnsFalseIfParentIsNotConnectedToChild)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);

			Assert::IsFalse(graph.CheckConnection(5, 7));
		}
		TEST_METHOD(Graph_CheckConnectionReturnsFalseIfParentDoesNotExist)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			Assert::IsFalse(graph.CheckConnection(7, 5));
		}
		TEST_METHOD(Graph_CheckConnectionReturnsFalseIfChildDoesNotExist)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			Assert::IsFalse(graph.CheckConnection(6, 7));
		}
		
		//Testovi za ConnectNode
		TEST_METHOD(Graph_ConnectNodeConnectsParentAndChildNode)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);

			graph.ConnectNode(5, 7);
		}
		TEST_METHOD(Graph_ConnectNodeThrowsExceptionWhenChildDoesNotExist)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);

			try {
				graph.ConnectNode(5, 8);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		TEST_METHOD(Graph_ConnectNodeThrowsExceptionWhenParentDoesNotExist)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);

			try {
				graph.ConnectNode(9, 5);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		//Testovi za RemoveConnection
		TEST_METHOD(Graph_RemoveConnectionRemovesConnectionBetweenParentAndChild)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);
			graph.ConnectNode(5, 7);
			graph.ConnectNode(7, 6);
			graph.RemoveConnection(5, 6);

			Assert::IsFalse(graph.CheckConnection(5, 6));
		}
		TEST_METHOD(Graph_RemoveConnectionThrowsExceptionWhenFatherDoesNotExist)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);

			try {
				graph.RemoveConnection(9, 5);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		TEST_METHOD(Graph_RemoveConnectionThrowExceptionWhenChildDoesNotExist)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);
			try {
				graph.RemoveConnection(5, 9);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		//Testovi za RemoveNode
		TEST_METHOD(Graph_RemoveNodeRemovesNodeFromGraph)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);

			graph.RemoveNode(5, 7);
			Assert::IsFalse(graph.ContainsNode(5));
		}
		TEST_METHOD(Graph_RemoveNodeThrowsExceptionWhenParentDoesNotExis)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);
			try {
				graph.RemoveNode(5, 9);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		TEST_METHOD(Graph_RemoveNodeThrowsExceptionWhenNodeToBeDeletedDoesNotExis)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);
			try {
				graph.RemoveNode(9, 5);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
};
}