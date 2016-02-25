#pragma once


#include<vector>
#include<stdexcept>
#include"BSTNode.h"



template<typename T>
class BST
{
public:
	BST() {};
	
	BST(const T& dataMember) {
		++m_treeSize;
		m_pTreeRoot = new BSTNode<T>(dataMember);
	}
	
	~BST() {
		delete m_pTreeRoot;
	};



	void AddNewMember(const T& newMemberData) {
		if (!m_pTreeRoot)
		{
			m_pTreeRoot = new BSTNode<T>(newMemberData);
			++m_treeSize;
			return;
		}
		BSTNode<T>* treeWalkerVariable = m_pTreeRoot;

		if (Contains(newMemberData))
			return;
		for (; treeWalkerVariable;treeWalkerVariable=HigherOrLower(newMemberData,treeWalkerVariable))
			if (newMemberData < treeWalkerVariable->GetDataOfNode() && !treeWalkerVariable->GetLeftTreeSide())
			{
				treeWalkerVariable->SetLeftTreeSide(new BSTNode<T>(newMemberData));
				++m_treeSize;
				++m_leftTreeSize;
				return;
			}
			else if (newMemberData > treeWalkerVariable->GetDataOfNode() && !treeWalkerVariable->GetRightTreeSide())
			{
				treeWalkerVariable->SetRightTreeSide(new BSTNode<T>(newMemberData));
				++m_treeSize;
				++m_rightTreeSize;
				return;
			}
	}

	bool Contains(const T& dataMember) {
		if (!m_pTreeRoot)
			return false;
		BSTNode<T>* treeWalkerVariable = m_pTreeRoot;
		for (; treeWalkerVariable; treeWalkerVariable = HigherOrLower(dataMember,treeWalkerVariable))
			if (dataMember == treeWalkerVariable->GetDataOfNode())
				return true;
		return false;
	}

	void DeleteMember(const T& dataOfMemberToBeDeleted) 
	{
		if (!TreeSize()) throw std::out_of_range("Tree is empty");
		if (!Contains(dataOfMemberToBeDeleted)) throw std::out_of_range("Tree does not contain member");

		if (dataOfMemberToBeDeleted == m_pTreeRoot->GetDataOfNode())
		{
			BSTNode<T>* tempNode = m_pTreeRoot;
			m_pTreeRoot = RootIsToBeDeleted(m_pTreeRoot->GetRightTreeSide());
			m_pTreeRoot->SetLeftTreeSide(tempNode->GetLeftTreeSide());
			m_pTreeRoot->SetRightTreeSide(tempNode->GetRightTreeSide());
			tempNode->SetChildrenToNullptr();
			delete tempNode;
			return;
		}
		
		BSTNode<T>* treeWalkerVariable = m_pTreeRoot;
		BSTNode<T>* fatherOFMemberToBeDeleted = FatherOfMember(dataOfMemberToBeDeleted);
		BSTNode<T>* memberToBeDeleted = FindMember(dataOfMemberToBeDeleted);
		bool memberToBeDeletedIsLeftSide = false;
		//Tests if the member to be deleted is omn the left side of the father member
		if (fatherOFMemberToBeDeleted->GetLeftTreeSide() == memberToBeDeleted)
			memberToBeDeletedIsLeftSide = true;


		//this part works in case the the has no children
		if (memberToBeDeleted->DoesNotHaveChildren())

		{
			if (memberToBeDeletedIsLeftSide)
				fatherOFMemberToBeDeleted->SetLeftTreeSide(memberToBeDeleted->ReturnSingleChild());
			else
				fatherOFMemberToBeDeleted->SetRightTreeSide(memberToBeDeleted->ReturnSingleChild());
			
			delete memberToBeDeleted;
			--m_treeSize;
			if (dataOfMemberToBeDeleted < m_pTreeRoot->GetDataOfNode())
				--m_leftTreeSize;
			else
				--m_rightTreeSize;
			return;
		}

		//this part tests if the child to be deleted has only one child
		BSTNode<T>* tempNode = memberToBeDeleted->ReturnSingleChild();
		if (tempNode)
		{
			if (memberToBeDeletedIsLeftSide)
				fatherOFMemberToBeDeleted->SetLeftTreeSide(tempNode);
			else
				fatherOFMemberToBeDeleted->SetRightTreeSide(tempNode);
			memberToBeDeleted->SetChildrenToNullptr();
			delete memberToBeDeleted;
			--m_treeSize;
			if (dataOfMemberToBeDeleted < m_pTreeRoot->GetDataOfNode())
				--m_leftTreeSize;
			else
				--m_rightTreeSize;
			return;
		}

		//If member to be deleted has both children
		if (memberToBeDeletedIsLeftSide)
		{
			BSTNode<T>* tempNode = fatherOFMemberToBeDeleted->GetLeftTreeSide();
			fatherOFMemberToBeDeleted->SetLeftTreeSide(BestOptionForReplacement(memberToBeDeleted->GetLeftTreeSide()));
			tempNode->SetChildrenToNullptr();
			delete tempNode;
		}
		else
		{
			BSTNode<T>* tempNode = fatherOFMemberToBeDeleted->GetRightTreeSide();
			fatherOFMemberToBeDeleted->SetRightTreeSide(BestOptionForReplacement(memberToBeDeleted->GetLeftTreeSide()));
			fatherOFMemberToBeDeleted->GetRightTreeSide()->SetRightTreeSide(tempNode->GetRightTreeSide());
			tempNode->SetChildrenToNullptr();
			delete tempNode;
		}
		--m_treeSize;
		if (dataOfMemberToBeDeleted < m_pTreeRoot->GetDataOfNode())
			--m_leftTreeSize;
		else
			--m_rightTreeSize;
			
	};

	int TreeSize() { return m_treeSize; }

	int LeftTreeSize() { return m_leftTreeSize; }

	int RightTreeSize() { return m_rightTreeSize; }

	std::vector<T> PreOrderOutput() { 
		if (!m_pTreeRoot)
			throw std::out_of_range("Tree is empty");
		std::vector<T> vectorOfPreOrderSortedMembers;
		NLR(vectorOfPreOrderSortedMembers, m_pTreeRoot);
		return vectorOfPreOrderSortedMembers;
	}
	
	std::vector<T> PostOrderOutput() {
		if (!m_pTreeRoot)
			throw std::out_of_range("Tree is empty");
		std::vector<T> vectorOfPreOrderSortedMembers;
		LRN(vectorOfPreOrderSortedMembers, m_pTreeRoot);
		return vectorOfPreOrderSortedMembers;
	}
	
	std::vector<T> InOrderOutput() {
		if (!m_pTreeRoot)
			throw std::out_of_range("Tree is empty");
		std::vector<T> vectorOfPreOrderSortedMembers;
		LNR(vectorOfPreOrderSortedMembers, m_pTreeRoot);
		return vectorOfPreOrderSortedMembers;
	}

private:
	BSTNode<T>* RootIsToBeDeleted(BSTNode<T>* walkerVariable)
	{
		while (walkerVariable->GetLeftTreeSide()->GetLeftTreeSide())
		{
			walkerVariable = walkerVariable->GetLeftTreeSide();
		}
		BSTNode<T>* variableToBeReturned = walkerVariable->GetLeftTreeSide();

		walkerVariable->SetLeftTreeSide(variableToBeReturned->GetRightTreeSide());
		variableToBeReturned->SetChildrenToNullptr();
		return variableToBeReturned;
	}

	int TreeCount(BSTNode<T>* walkerVariable)
	{
		if (!walkerVariable) return 0;
		return 1 + TreeCount(walkerVariable->GetLeftTreeSide()) + TreeCount(walkerVariable->GetRightTreeSide());
	}

	BSTNode<T>* BestOptionForReplacement(BSTNode<T>* firstLeftMemberOfNodeTobeDeleted)
	{
		if (!firstLeftMemberOfNodeTobeDeleted->GetRightTreeSide())
			return firstLeftMemberOfNodeTobeDeleted;
		BSTNode<T>* tempTreeWalkerVariable = firstLeftMemberOfNodeTobeDeleted;

		while (tempTreeWalkerVariable->GetRightTreeSide())
		{
			tempTreeWalkerVariable = tempTreeWalkerVariable->GetRightTreeSide();
		}
		if (!tempTreeWalkerVariable->GetLeftTreeSide())
		{
			tempTreeWalkerVariable->SetLeftTreeSide(firstLeftMemberOfNodeTobeDeleted);
			BSTNode<T>* tempVariable = FatherOfMember(tempTreeWalkerVariable->GetDataOfNode());
			if (tempVariable->GetLeftTreeSide() == tempVariable)
				tempVariable->SetLeftTreeSide(nullptr);
			else
				tempVariable->SetRightTreeSide(nullptr);

			return tempTreeWalkerVariable;
		}
		

		BSTNode<T>* lowestPointOftempTreeWalkerVariable = tempTreeWalkerVariable;
		while (lowestPointOftempTreeWalkerVariable->GetLeftTreeSide())
		{
			lowestPointOftempTreeWalkerVariable = lowestPointOftempTreeWalkerVariable->GetLeftTreeSide();
		}
		firstLeftMemberOfNodeTobeDeleted->SetRightTreeSide(nullptr);
		lowestPointOftempTreeWalkerVariable->SetLeftTreeSide(firstLeftMemberOfNodeTobeDeleted);
		return tempTreeWalkerVariable;
	}

	BSTNode<T>* FindMember(const T& dataOfMemberToBeFound)
	{
		BSTNode<T>* walkerVariable = m_pTreeRoot;
		while(true)
		{
			if (walkerVariable->GetDataOfNode() == dataOfMemberToBeFound)
				return walkerVariable;

			walkerVariable = HigherOrLower(dataOfMemberToBeFound, walkerVariable);
		}
	}

	BSTNode<T>* FatherOfMember(const T& dataOfMember)
	{
		BSTNode<T>* father = m_pTreeRoot;
		while (true)
		{
			if (father->GetLeftTreeSide() && father->GetLeftTreeSide()->GetDataOfNode() == dataOfMember)
				return father;
			else if (father->GetRightTreeSide() && father->GetRightTreeSide()->GetDataOfNode() == dataOfMember)
				return father;

			father = HigherOrLower(dataOfMember, father);
		}
	}

	BSTNode<T>* HigherOrLower(const T& data, BSTNode<T>* node)
	{
		if (node->GetDataOfNode() < data)
			return node->GetRightTreeSide();
		else
			return node->GetLeftTreeSide();
	}

	void NLR(std::vector<T>& vectorOfPreOrderSortedMembers, BSTNode<T>* root)
	{
		if (!root)
			return;
		vectorOfPreOrderSortedMembers.insert(vectorOfPreOrderSortedMembers.end(), root->GetDataOfNode());
		NLR(vectorOfPreOrderSortedMembers, root->GetLeftTreeSide());
		NLR(vectorOfPreOrderSortedMembers, root->GetRightTreeSide());

	}
	
	void LNR(std::vector<T>& vectorOfPreOrderSortedMembers, BSTNode<T>* root)
	{
		if (!root)
			return;
		LNR(vectorOfPreOrderSortedMembers, root->GetLeftTreeSide());
		vectorOfPreOrderSortedMembers.insert(vectorOfPreOrderSortedMembers.end(), root->GetDataOfNode());
		LNR(vectorOfPreOrderSortedMembers, root->GetRightTreeSide());

	}
	
	void LRN(std::vector<T>& vectorOfPreOrderSortedMembers, BSTNode<T>* root)
	{
		if (!root)
			return;
		LRN(vectorOfPreOrderSortedMembers, root->GetLeftTreeSide());
		LRN(vectorOfPreOrderSortedMembers, root->GetRightTreeSide());
		vectorOfPreOrderSortedMembers.insert(vectorOfPreOrderSortedMembers.end(), root->GetDataOfNode());

	}




	BSTNode<T>* m_pTreeRoot = nullptr;

	int m_treeSize = 0;
	int m_leftTreeSize = 0;
	int m_rightTreeSize = 0;
};


