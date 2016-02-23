#pragma once


template<typename T>
struct BSTNode
{
public:
	BSTNode(const T& thisNodeData, BSTNode<T>* leftTreeSide = nullptr, BSTNode<T>* rightTreeSide = nullptr)
	{
		m_dataOfNode = thisNodeData;
		m_pLeftChild = leftTreeSide;
		m_pRightChild = rightTreeSide;
	}

	virtual ~BSTNode()
	{
		delete m_pLeftChild;
		delete m_pRightChild;
	}

	void SetLeftTreeSide(BSTNode<T>* newLeftTreeSide) { m_pLeftChild = newLeftTreeSide; }
	BSTNode<T>* GetLeftTreeSide() { return m_pLeftChild; }

	void SetRightTreeSide(BSTNode<T>* newRightTreeSide) { m_pRightChild = newRightTreeSide; }
	BSTNode<T>* GetRightTreeSide() { return m_pRightChild; }

	void SetDataOfNode(const T& newNodeData) { m_dataOfNode = newNodeData; }
	const T& GetDataOfNode() { return m_dataOfNode; }

	void SetChildrenToNullptr() {
		m_pLeftChild = nullptr;
		m_pRightChild = nullptr;
	}
	bool DoesNotHaveChildren()
	{
		if (m_pLeftChild || m_pRightChild)
			return false;
		else return true;
	}
	bool HasBoathChildren()
	{
		if (m_pLeftChild && m_pRightChild)
			return true;
		else return false;
	}
	BSTNode<T>* ReturnSingleChild()
	{
		if (!m_pLeftChild && m_pRightChild)
			return m_pRightChild;
		else if (m_pLeftChild && !m_pRightChild)
			return m_pLeftChild;
		else return nullptr;
			
	}

private:
	BSTNode<T>* m_pLeftChild;
	BSTNode<T>* m_pRightChild;
	T m_dataOfNode;
};