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
	~BST() {};

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
		for (; treeWalkerVariable; newMemberData < treeWalkerVariable->GetDataOfNode() ? treeWalkerVariable = treeWalkerVariable->GetLeftTreeSide() : treeWalkerVariable = treeWalkerVariable->GetRightTreeSide())
			if (newMemberData < treeWalkerVariable->GetDataOfNode() && !treeWalkerVariable->GetLeftTreeSide())
			{
				treeWalkerVariable->SetLeftTreeSide(new BSTNode<T>(newMemberData));
				++m_treeSize;
				++m_leftTreeSize;
			}
			else if (newMemberData > treeWalkerVariable->GetDataOfNode() && !treeWalkerVariable->GetRightTreeSide())
			{
				treeWalkerVariable->SetRightTreeSide(new BSTNode<T>(newMemberData));
				++m_treeSize;
				++m_rightTreeSize;
			}
	}
	bool Contains(const T& dataMember) {
		if (!m_pTreeRoot)
			return false;
		BSTNode<T>* treeWalkerVariable = m_pTreeRoot;
		for (; treeWalkerVariable; dataMember < treeWalkerVariable->GetDataOfNode() ? treeWalkerVariable = treeWalkerVariable->GetLeftTreeSide() : treeWalkerVariable = treeWalkerVariable->GetRightTreeSide())
			if (dataMember == treeWalkerVariable->GetDataOfNode())
				return true;
		return false;
	}
	void Delete(const T& dataOfMemberToBeDeleted) {};
	int TreeSize() { return m_treeSize; };
	int LeftTreeSize() {return m_leftTreeSize};
	int RightTreeSize() {return m_rightTreeSize};
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
	void NLR(std::vector<T>& vectorOfPreOrderSortedMembers, BSTNode<T>* root)
	{
		if (!root)
			return;
		vectorOfPreOrderSortedMembers.insert(vectorOfPreOrderSortedMembers.begin(), root->GetDataOfNode());
		NLR(vectorOfPreOrderSortedMembers, root->GetLeftTreeSide());
		NLR(vectorOfPreOrderSortedMembers, root->GetRightTreeSide());

	}
	void LNR(std::vector<T>& vectorOfPreOrderSortedMembers, BSTNode<T>* root)
	{
		if (!root)
			return;
		NLR(vectorOfPreOrderSortedMembers, root->GetLeftTreeSide());
		vectorOfPreOrderSortedMembers.insert(vectorOfPreOrderSortedMembers.begin(), root->GetDataOfNode());
		NLR(vectorOfPreOrderSortedMembers, root->GetRightTreeSide());

	}
	void LRN(std::vector<T>& vectorOfPreOrderSortedMembers, BSTNode<T>* root)
	{
		if (!root)
			return;
		NLR(vectorOfPreOrderSortedMembers, root->GetLeftTreeSide());
		NLR(vectorOfPreOrderSortedMembers, root->GetRightTreeSide());
		vectorOfPreOrderSortedMembers.insert(vectorOfPreOrderSortedMembers.begin(), root->GetDataOfNode());

	}




	BSTNode<T>* m_pTreeRoot = nullptr;

	int m_treeSize = 0;
	int m_leftTreeSize = 0;
	int m_rightTreeSize = 0;
};