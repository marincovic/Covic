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

	void AddNewMember(const T& newMemberData) {};
	bool Contains(const T& dataMember) {};
	void Delete(const T& dataOfMemberToBeDeleted) {};
	int TreeSize() {};
	int LeftTreeSize() {};
	int RightTreeSize() {};
	std::vector<T>& PreOrderOutput() {};
	std::vector<T>& PostOrderOutput() {};
	std::vector<T>& InOrderOutput() {};

private:
	BSTNode<T> m_pTreeRoot;

	int m_treeSize = 0;
	int m_leftTreesize = 0;
	int m_rightTreeSize = 0;
};