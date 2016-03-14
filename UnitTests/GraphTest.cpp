#include "CppUnitTest.h"
#include "../Structures/Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;






//prijedlog za izgled grafa
//Graf je usmijerenog tipa te napreduje s lijeva na desno
//
//
//
//	  /---->6---->7----->8\
//	5         \---->13     ->12
//	\ \---->9---->10--->11/ /
//   \---->14-------------15
//
//te Tezine pomaka
//5 -> 6 = 1
//6 -> 7 = 1
//7 -> 8 = 2
//8 -> 12 = 5
//6 -> 13 = 6
//13 -> 8 = 7
//13 -> 12 = 9
//5 -> 9 = 3
//9 -> 10 = 3
//10 -> 11 = 0
//11 -> 12 = 1
//5 -> 14 = 5
//14 -> 15 = 1
//15 -> 12 = 7

//najkraca ruta za prelazak preko grafa je 5 -> 6 -> 13 -> 12 i ruta 5 -> 14 -> 15 ->12
// njalaksa ruta za prelazak preko grafa 5 -> 9-> 10 -> 11 -> 12
namespace UnitTests
{
	TEST_CLASS(GraphTest)
	{
	private:
		void GrafConstruction(Graph<int>& Graph)
		{
			Graph.AddNode(6, 5, 1);
			Graph.AddNode(9, 5, 3);
			Graph.AddNode(14, 5, 5);
			Graph.AddNode(7, 6, 1);
			Graph.AddNode(13, 6, 6);
			Graph.AddNode(8, 7, 2);
			Graph.AddNode(8, 13, 7);
			Graph.AddNode(12, 8, 5);
			Graph.AddNode(13, 12, 9);
			Graph.AddNode(10, 9, 3);
			Graph.AddNode(11, 10, 0);
			Graph.AddNode(12, 11, 1);
			Graph.AddNode(14, 9, 2);
			Graph.AddNode(15, 14, 1);
			Graph.AddNode(12, 15, 7);
		}
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
		TEST_METHOD(Graph_ContainsNodeReturnesTrueIfNodeIdExists)
		{
				Graph<int> graph(5);
				unsigned i = 0;
				graph.AddNode(6, 5);

				Assert::IsTrue(graph.ContainsNode(i));

		}
		TEST_METHOD(Graph_ContainsNodeReturnsFalseIfNodeIdDoesNotExist)
		{
			Graph<int> graph(5);
			unsigned i = 9;
			graph.AddNode(6, 5);

			Assert::IsFalse(graph.ContainsNode(i));
		}


		//Testovi za GetPredecessorId metodu
		TEST_METHOD(Graph_DataOfNodeReturnsDataOfNodeToBeFound)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			Assert::AreEqual(5, graph.GetPredecessorId(0));
		}
		TEST_METHOD(Graph_DataOfNodeThrowsExceptionIfMemberIsNotFound)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			try {
				graph.GetPredecessorId(7);
				Assert::Fail();
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

			Assert::IsTrue(graph.CheckConnection(0, 1));
		}
		TEST_METHOD(Graph_CheckConnectionReturnsFalseIfParentIsNotConnectedToChild)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);

			Assert::IsFalse(graph.CheckConnection(0, 7));
		}
		TEST_METHOD(Graph_CheckConnectionReturnsFalseIfParentDoesNotExist)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			Assert::IsFalse(graph.CheckConnection(7, 0));
		}
		TEST_METHOD(Graph_CheckConnectionReturnsFalseIfChildDoesNotExist)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			Assert::IsFalse(graph.CheckConnection(1,7));
		}

		//Testovi za ConnectNode
		TEST_METHOD(Graph_ConnectNodeConnectsParentAndChildNode)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);

			graph.ConnectNodes(0, 2);
			Assert::IsTrue(graph.CheckConnection(0, 2));
		}
		TEST_METHOD(Graph_ConnectNodeThrowsExceptionWhenChildDoesNotExist)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);

			try {
				graph.ConnectNodes(0, 8);
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
				graph.ConnectNodes(9,0);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		// Testovi za metodu u kojoj se povezuje AddNode i ConnectNode
		TEST_METHOD(Graph_AddNodeConnectsTwoExistingNodes)
		{
			Graph<int> graf(5);
			GrafConstruction(graf);
			Assert::AreEqual(11, graf.NumberOfNodesInGraph());
		}

		//Testovi za SetWeightOfMovementConnectingTwoNodes
		TEST_METHOD(Graph_SetWeightOfMovementConnectingTwoNodesChangesWeightOfMovementForTwoConnecetedNodes)
		{
			Graph<int> graph(5);
			graph.AddNode(6,5);
			graph.SetWeightOfMovementConnectingTwoNodes(0, 1, 2.0);
			Assert::AreEqual(2.0, graph.GetWeightOfMovementConnectingTwoNodes(0,1));
		}
		TEST_METHOD(Graph_SetWeightOfMovementConnectingTwoNodesThorwExceptionWhenFirstNodeIsNotFound)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			try {
				graph.SetWeightOfMovementConnectingTwoNodes(7, 1, 2.0);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		TEST_METHOD(Graph_SetWeightOfMovementConnectingTwoNodesThorwExceptionWhenSecondNodeIsNotFound)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			try {
				graph.SetWeightOfMovementConnectingTwoNodes(0, 7, 2.0);
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
			GrafConstruction(graph);
			graph.RemoveConnection(0, 1);
			graph.CheckPtrQualaty();
			Assert::IsFalse(graph.CheckConnection(0, 1));
		}
		TEST_METHOD(Graph_RemoveConnectionThrowsExceptionWhenFatherDoesNotExist)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);

			try {
				graph.RemoveConnection(9, 0);
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
				graph.RemoveConnection(0, 9);
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
			GrafConstruction(graph);

			graph.RemoveNode(1, 0);
			Assert::IsFalse(graph.ContainsNode(1));
			Assert::IsTrue(graph.CheckConnection(0, 4));
			Assert::IsTrue(graph.CheckConnection(0, 5));
		}
		TEST_METHOD(Graph_RemoveNodeThrowsExceptionWhenParentDoesNotExis)
		{
			Graph<int> graph(5);
			graph.AddNode(6, 5);
			graph.AddNode(7, 6);
			try {
				graph.RemoveNode(0, 7);
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
				graph.RemoveNode(7, 0);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		//Testovi za najkraci put
		TEST_METHOD(Graph_FindShortestRouteConnectingTwoPointsReturnsShortestRouteConnectingPoint5toPoint12)
		{
			Graph<int> graph(5);
			GrafConstruction(graph);

			Assert::AreEqual(4, (int) graph.FindShortestRouteConnectingTwoNodes(0, 7).size());
		}
		TEST_METHOD(Graph_FindShortestRouteConnectingTwoPointsThrowExceptionWhenFatherStarPointDoesNOtExist)
		{
			Graph<int> graph(5);
			GrafConstruction(graph);
			try {
				graph.FindShortestRouteConnectingTwoNodes(50, 7);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		TEST_METHOD(Graph_FindShortestRouteConnectingTwoPointsThrowExceptionWhenEndPointDoesNOtExist)
		{
			Graph<int> graph(5);
			GrafConstruction(graph);
			try {
				graph.FindShortestRouteConnectingTwoNodes(0, 22);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}


		//Testovi za nalaksi put
		TEST_METHOD(Graph_FindEasiestRouteConnectingTwoPointsReturnsEasiestRouteConnectingPoint5toPoint12)
		{
			Graph<int> graph(5);
			GrafConstruction(graph);

			Assert::AreEqual(5, (int)graph.FindEasiestRouteConnectingTwoPoints(0, 7).size());
		}
		TEST_METHOD(Graph_FindEasiestRouteConnectingTwoPointsThrowExceptionWhenFatherStarPointDoesNOtExist)
		{
			Graph<int> graph(5);
			GrafConstruction(graph);
			try {
				graph.FindEasiestRouteConnectingTwoPoints(20, 7);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		TEST_METHOD(Graph_FindEasiestRouteConnectingTwoPointsThrowExceptionWhenEndPointDoesNOtExist)
		{
			Graph<int> graph(5);
			GrafConstruction(graph);
			try {
				graph.FindEasiestRouteConnectingTwoPoints(0, 50);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

	};
}