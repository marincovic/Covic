#pragma once

#include<vector>
#include<exception>
#include<algorithm>


template<typename GraphNode, typename moveWeightType>
struct NextChildStruct
{
public:
	NextChildStruct() {}
	NextChildStruct(const GraphNode& nextNode, moveWeightType weightOfMove = 0) : m_NextChild(nextNode), m_weightOfMove(weightOfMove) {}
	~NextChildStruct() {
		delete m_NextChild;
		m_NextChild = nullptr;
	}

	void SetNextChild(const GraphNode& nextChild) { m_NextChild = nextChild; }
	const GraphNode& GetNextChild() { return m_NextChild; }

	void SetWeightOfMove(moveWeightType weightOfMove) { m_weightOfMove = weightOfMove; }
	int GetWieghtOfMove() { return m_weightOfMove; }

private:
	GraphNode m_NextChild;
	moveWeightType m_weightOfMove;
};

template<typename dataTypeOfNode, typename moveWeightType>
struct GraphNode
{
public:
	GraphNode() {}
	GraphNode(const dataTypeOfNode& dataOfNode) :m_dataOfNode(dataOfNode) {}
	GraphNode(const dataTypeOfNode& dataOfNode, 
		const dataTypeOfNode& dataOfFirstChildNode,
		const moveWeightType& weightOfMovemenToNewChild = 0)
	{
		m_dataOfNode = dataOfNode;
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode<dataTypeOfNode, moveWeightType>*, moveWeightType>(new GraphNode<dataTypeOfNode, moveWeightType>(dataOfFirstChildNode,weightOfMovemenToNewChild)));
	}
	GraphNode(const dataTypeOfNode& dataOfNode, 
		const GraphNode<dataTypeOfNode, moveWeightType>* pToChild,
		const moveWeightType& weightOfMovemenToNewChild = 0)
	{
		m_dataOfNode = dataOfNode;
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode<dataTypeOfNode, moveWeightType>*, moveWeightType>(new GraphNode<dataTypeOfNode, moveWeightType>(pToChild, weightOfMovemenToNewChild)));
	}
	virtual ~GraphNode() {
		m_vectorOfNodeChildren.clear();
	}

	const dataTypeOfNode& GetDataOfNode() { return m_dataOfNode; }
	void SetDataOFNode(const dataTypeOfNode& newDataofNode) { m_dataOfNode = newDataofNode; }

	GraphNode<dataTypeOfNode,moveWeightType>* GetChildAtIndex(int index){
		if (!m_vectorOfNodeChildren.size()) return nullptr;
		if (index > m_vectorOfNodeChildren.size() || index < 0)
			throw std::out_of_range("Index out of range");
		return m_vectorOfNodeChildren.at(index)->GetNextChild();
	}
	const moveWeightType& GetMovementWeightToChildAtIndex(int index) {};
	
	void AddNewChild(GraphNode<dataTypeOfNode, moveWeightType>* newChildToBeAdded, moveWeightType WeightOFMovement = 0)
	{
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode<dataTypeOfNode, moveWeightType>*, moveWeightType>(newChildToBeAdded,WeightOFMovement));
	}
	void AddNewChild(const dataTypeOfNode& dataOfNewChild,moveWeightType WeightOFMovement = 0) {
		GraphNode<dataTypeOfNode, moveWeightType>* tempNode = new GraphNode<dataTypeOfNode, moveWeightType>(dataOfNewChild);
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode<dataTypeOfNode,moveWeightType>*, moveWeightType>(tempNode,WeightOFMovement));
	}

	void RemoveChild(GraphNode<dataTypeOfNode, moveWeightType>* childToBeRemoved)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if (childToBeRemoved == (*it)->GetNextChild())
			{
				m_vectorOfNodeChildren.erase(it);
				return;
			}
		}
		throw std::out_of_range("Child does not exist");
	}
	void RemoveChild(const dataTypeOfNode& dataOfChildToBeRemoved)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if (dataOfChildToBeRemoved == (*it)->GetNextChild()->GetDataOfNode())
			{
				m_vectorOfNodeChildren.erase(it);
				return;
			}
		}
		throw std::out_of_range("Child does not exist");
	}

	bool ContainsChild(GraphNode<dataTypeOfNode, moveWeightType>* childToBeFound)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if ((*it)->GetNextChild() == childToBeFound)
				return true;
		}
		return false;
	}
	bool ContainsChild(dataTypeOfNode dataOfChildToBeFound)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if ((*it)->GetNextChild()->GetDataOfNode() == dataOfChildToBeFound)
				return true;
		}
		return false;
	}

private:
	dataTypeOfNode m_dataOfNode;
	std::vector<NextChildStruct<GraphNode<dataTypeOfNode,moveWeightType>*,moveWeightType>*> m_vectorOfNodeChildren;
};