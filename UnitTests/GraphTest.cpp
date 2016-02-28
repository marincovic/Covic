#include "CppUnitTest.h"
#include "../Structures/GraphNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(GraphNode2Test)
	{
	public:
		TEST_METHOD(GraphNode_SizeReturns0ForNodeWithNoChildren)
		{
			GraphNode<int> node;
			Assert::AreEqual(0, node.NumberOfChildren());
		}
		TEST_METHOD(GraphNode_AddMemberAddsNewMemberToTheList) {
			GraphNode<int> node(5);
			node.AddMember(10);
			Assert::AreEqual(1, node.NumberOfChildren());
		}

		TEST_METHOD(GraphNode_GetDataMemberReturnsDataOfMember)
		{
			GraphNode<int> node(9);
			Assert::AreEqual(9, node.GetDataOfMember());
		}

		TEST_METHOD(GraphNode_ContainsReturnsTrueIfMemberDoesContainChild)
		{
			GraphNode<int> node(5);
			node.AddMember(10);
			node.AddMember(15);
			Assert::IsTrue(node.ContainsMember(10));
		}
		TEST_METHOD(GraphNode_ContainsMemberReturnsFalseIfMemberDoesContainChild)
		{
			GraphNode<int> node(5);
			node.AddMember(10);
			node.AddMember(15);
			Assert::IsFalse(node.ContainsMember(6));
		}

		TEST_METHOD(GraphNode_RemoveRemovesChildFromList)
		{
			GraphNode<int> node(5);
			node.AddMember(10);
			node.AddMember(15);
			node.RemoveMember(10);
			Assert::IsFalse(node.ContainsMember(10));
			Assert::AreEqual(1, node.NumberOfChildren());
		}
		TEST_METHOD(GraphNode_RemoveMemberThrowExceptionIfNodeDoesNotContainChild)
		{
			GraphNode<int> node(5);
			node.AddMember(10);
			node.AddMember(15);
			try {
				node.RemoveMember(9);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(GraphNode_GetChildAtIndexReturnsNullptrIfNodeDoesNotContainChildren)
		{
			GraphNode<int> node(5);
			Assert::IsTrue(node.GetChildAtIndex(0) == nullptr);
		}
		TEST_METHOD(GraphNode_GetChildAtIndexThrowExceptionIfIndexsOutOfRange)
		{
			GraphNode<int> node(5);
			node.AddMember(10);
			try
			{
				node.GetChildAtIndex(9);
				Assert::Fail;
			}
			catch (std::out_of_range&)
			{
				Assert::IsTrue(true);
			}
		}
		TEST_METHOD(GraphNode_GetChildAtIndexReturnsChildFromGivenIndex)
		{
			GraphNode<int> node(5);
			node.AddMember(10);
			node.AddMember(15);
			Assert::AreEqual(10, node.GetChildAtIndex(0)->GetDataOfMember());
		}

	};
}