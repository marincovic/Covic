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

		// Ima li smisla inicijalizirati èvor koji nema vrijednost? 
		// Po meni to nema smisla jer èvor služi da sadrži neku vrijednost.
		// Zato mislim da prazan konstruktor ne bi smio postojati i ovaj test 
		// nema smisla. 
		TEST_METHOD(GraphNode_SetDataOfNodeSetsDataOfNodeToWantedValue)
		{
			GraphNode<int, int> node;
			node.SetDataOFNode(5);
			Assert::AreEqual(5, node.GetDataOfNode());
		}

		TEST_METHOD(GraphNode_GetChildAtIndexsReturnsNullptrWhenGraphHasNoChildren)
		{
			GraphNode<int, int> node(5);
			// donja naredba ne valja:
			// 1. u što god nullptr kastali, to æe i dalje biti nullptr. Stoga je donje kastanje besmisleno!
			//    Assert::AreEqual(static_cast<GraphNode<int, int>*>(nullptr), node.GetChildAtIndex(0));
			// 2. Da biste mogli napisati test u ovom obliku:
			//    Assert::AreEqual(nullptr, node.GetChildAtIndex(0));
			//    morate napisati preoptereæenu verziju metode Assert::AreEqual() koja æe usporeðivati
			//    objekte korisnièkog tipa GraphNode<,>* . Buduæi da to (nadam se) ne želite raditi,
			//    provjeru jednostavno napišite na sljedeæi naèin:
			Assert::IsTrue(node.GetChildAtIndex(0) == nullptr);
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
	
		// test pada jer GetChildAtIndex(0) vraæa nullptr i ne bace iznimku
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
	
		// test pada jer GetChildAtIndex(2) vraæa nullptr i ne bace iznimku
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
			// pogledajte komentar za metodu GraphNode_ContainsChildReturnsFalseIfDataDoesNotMatchAnyChild
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

		// test pada jer GetChildAtIndex(0) vraæa nullptr i ne bace iznimku
		TEST_METHOD(GraphNode_RemoveChildDefinedByPointer)
		{
			GraphNode<int, int> node1(5);
			GraphNode<int, int>* node2=new GraphNode<int,int>(5);
			node1.AddNewChild(node2);

			node1.RemoveChild(node2);
			try {
				node1.GetChildAtIndex(0);
				Assert::Fail(false);
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}

		}

		// Test Vam je krivo napisan jer metoda ne baca iznimku. To je dobro
		// jer metode koje "propitkuju" (i vraæaju bool) ne bi smjele bacati iznimku. 
		// Zamislite da se želite udvarati curi i pitate je "Jesi li slobodna?" a ona Vam
		// na to jednostavno opali šamarèinu!
		TEST_METHOD(GraphNode_ContainsChildThrowExceptionIfNodeHasNoChildren)
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

		TEST_METHOD(GraphNode_ContainsChildReturnsTrueIfDataMatchesDataOfAtLeastOneChild)
		{
			// pogledajte komentar za metodu GraphNode_ContainsChildReturnsFalseIfDataDoesNotMatchAnyChild
			GraphNode<int, int> node(5, 6);
			Assert::IsTrue(node.ContainsChild(6));
		}

		TEST_METHOD(GraphMove_ContainsChildReturnsTrueIfAdressMatchesAddressOfAtLeastOneChild)
		{
			GraphNode<int, int> node1(5);
			GraphNode<int, int>* node2 = new GraphNode<int, int>(6);
			// Koja naredba dodaje node2 u node1?
			Assert::IsTrue(node1.ContainsChild(node2));
		}
	
		TEST_METHOD(GraphNode_ContainsChildReturnsFalseIfDataDoesNotMatchAnyChild)
		{
			// ovdje imate VELIKIH problema pri pozivu konstruktora 
			// koje kompajler nije primijetio iz banalnog razloga.
			// Imate konstruktor koji prima 3 argumenta:
			//  template<typename dataTypeOfNode, typename moveWeightType>
			//  GraphNode(const dataTypeOfNode& dataOfNode,
			//	          const dataTypeOfNode& dataOfFirstChildNode,
			//	          const moveWeightType& weightOfMovemenToNewChild = 0)
			// i pri instantaciji kažete da su oba parametra predloška tipa int.
			// Zbog toga su sva tri argumenta konstruktoru tipa int.
			// Prilikom donjeg poziva u konstruktoru se dodaje novo dijete.
			// Pritom se poziva isti konstruktor i taj rekurzivni poziv konstruktora 
			// ide u nedogled. Ovo je jeoš jedan lijepi primjer:
			// a) zašto ne treba nepotrebno pretrpavati suèelje (argumentom weightOfMovemenToNewChild
			//    koji se nigdje ne koristi (ako æe Vam kasnije zatrebati, lako æete ga dodati)
			// b) zašto nije dobro koristiti podrazumijevane vrijednosti argumenata (da
			//    ih niste koristili, kompajler bi Vam javio pogrešku) 
			GraphNode<int, int> node(5, 6);
			Assert::IsFalse(node.ContainsChild(7));
		}

		TEST_METHOD(GraphNode_ContainsChildReturnsFalseIfAddressDoesNotMatchAnyChildren)
		{
			GraphNode<int, int> node(5, 6);
			Assert::IsFalse(node.ContainsChild(new GraphNode<int, int>()));
		}


	};
}