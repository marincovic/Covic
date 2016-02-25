#pragma once

#include<vector>
#include<exception>
#include<algorithm>


template<typename T>
struct GraphNode
{
public:
	GraphNode() {}
	GraphNode(const T& dataOfNode) :m_dataOfNode(dataOfNode) {}
	GraphNode(const T& dataOfNode, const T& dataOfFirstChildNode)
	{
		m_dataOfNode = dataOfNode;
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode*>(new GraphNode<T>(dataOfFirstChildNode)));
	}
	GraphNode(const T& dataOfNode, GraphNode<T>* pToChild)
	{
		m_dataOfNode = dataOfNode;
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode*>(pToChild));
	}
	virtual ~GraphNode() {
		m_vectorOfNodeChildren->clear();
	}

	const T& GetDataOfNode() { return m_dataOfNode; }
	void SetDataOFNode(const T& newDataofNode) { m_dataOfNode = newDataofNode }

	GraphNode<T>* GetChildAtIndex(int index){
		if (index > m_vectorOfNodeChildren.size() || index < 0)
			throw std::out_of_range("Index out of range");
		return m_vectorOfNodeChildren.at(index)->GetNextChild();
	}
	
	void AddNewChild(GraphNode<T>* newChildToBeAdded)
	{
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode*>(newChildToBeAdded));
	}
	void AddNewChild(const T& dataOfNewChild) {
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode*>(new GraphNode<T>(dataOfNewChild)));
	}

	void RemoveChild(GraphNode<T>* childToBeRemoved)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if (childToBeRemoved == it->GetNextChild())
			{
				m_vectorOfNodeChildren.erase(it);
				return;
			}
		}
		throw std::out_of_range("Child does not exist");
	}
	void RemoveChild(const T& dataOfChildToBeRemoved)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if (dataOfChildToBeRemoved == it->GetNextChild()->GetDataOfNode)
			{
				m_vectorOfNodeChildren.erase(it);
				return;
			}
		}
		throw std::out_of_range("Child does not exist");
	}

	bool ContainsChild(GraphNode<T>* childToBeFound)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if (it->GetNextChild == childToBeFound)
				return true;
		}
		return false;
	}
	bool ContainsChild(GraphNode<T>* dataOfChildToBeFound)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if (it->GetNextChild()->GetDataOfNode() == dataOfChildToBeFound)
				return true;
		}
		return false;
	}

private:
	T m_dataOfNode;
	std::vector<NextChildStruct<GraphNode*>> m_vectorOfNodeChildren;
};

template<typename T>
struct NextChildStruct
{
public:
	NextChildStruct() {}
	NextChildStruct(const T& nextNode, int weightOfMove = 0) : m_NextChild(nextNode), m_weightOfMove(weightOfMove) {}
	~NextChildStruct() {
		delete m_NextChild;
		m_NextChild = nullptr;
	}

	void SetNextChild(const T& nextChild) { m_NextChild = nextChild; }
	const T& GetNextChild() { return m_NextChild; }

	void SetWeightOfMove(int weightOfMove) { m_weightOfMove = weightOfMove; }
	int GetWieghtOfMove() { return m_weightOfMove; }

private:
	T m_NextChild;
	int m_weightOfMove
};