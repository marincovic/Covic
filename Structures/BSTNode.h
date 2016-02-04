#pragma once


template<typename T>
struct BSTNode
{
public:
	BSTNode(const T& thisNodeData, const BSTNode<T>* leftTreeSide = nullptr, const BSTNode<T>* rightTreeSide = nullptr)
	{
		m_dataOfNode = thisNodeData;
		m_pLeftSideOfTree = leftTreeSide;
		m_pRightSideOfTree = rightTreeSide;
	}

	virtual ~BSTNode()
	{
		delete m_pLeftSideOfTree;
		delete m_pRightSideOfTree;
	}

	void SetLeftTreeSide(BSTNode<T>* newLeftTreeSide) { m_pLeftSideOfTree = newLeftTreeSide; }
	BST<T>* GetLeftTreeSide() { return m_pLeftSideOfTree; }

	void SetRightTreeSide(BSTNode<T>* newRightTreeSide) { m_pRightSideOfTree = newRightTreeSide; }
	BST<T>* GetRightTreeSide() { return m_pRightSideOfTree; }

	void SetDataOfNode(const T& newNodeData) { m_dataOfNode = newNodeData; }
	const T& GetDataOfNode() { return m_dataOfNode; }

private:
	BSTNode<T>* m_pLeftSideOfTree;
	BSTNode<T>* m_pRightSideOfTree;
	T m_dataOfNode;
};