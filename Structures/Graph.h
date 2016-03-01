#pragma once
#include"GraphNode.h"

#include<vector>
#include<memory>

template<typename dataType>
class Graph {
public:
	Graph(const dataType& dataOfFirstNode) {
		m_root = std::make_shared<GraphNode<dataType>>(dataOfFirstNode);
		++m_numberOfNodes;
	};
	~Graph() {};

	void AddNode(const dataType& dataOfNewNode, const dataType& dataOfFatherNode) {
		GraphNode<dataType>* pToFatherNode=nullptr;
		std::vector<GraphNode<dataType>*> mapOfVisitedNodes;

		FindNode(m_root.get(), dataOfFatherNode, mapOfVisitedNodes, pToFatherNode);

		if (!pToFatherNode) throw std::out_of_range("Father node does notExist");

		pToFatherNode->AddMember(dataOfNewNode);
		++m_numberOfNodes;
	};
	const dataType& DataOfNode(const dataType& dataToBeSearchedBy) {
		GraphNode<dataType>* pToFatherNode = nullptr;
		std::vector<GraphNode<dataType>*> mapOfVisitedNodes;

		FindNode(m_root.get(), dataToBeSearchedBy, mapOfVisitedNodes, pToFatherNode);

		if (!pToFatherNode) throw std::out_of_range("Father node does notExist");

		return pToFatherNode->GetDataOfMember();
	};


	bool ContainsNode(const dataType& dataToBeFound) {
		GraphNode<dataType>* pToFatherNode = nullptr;
		std::vector<GraphNode<dataType>*> mapOfVisitedNodes;

		FindNode(m_root.get(), dataToBeFound, mapOfVisitedNodes, pToFatherNode);

		if (!pToFatherNode)
			return false;
		else
			return true;

	};
	bool CheckConnection(const dataType& dataOfParentNode, const dataType& dataOfChildNode) {
		GraphNode<dataType>* pToFatherNode = nullptr;
		GraphNode<dataType>* pToChildNode = nullptr;
		std::vector<GraphNode<dataType>*> mapOfVisitedNodes;

		FindNode(m_root.get(), dataOfParentNode, mapOfVisitedNodes, pToFatherNode);

		mapOfVisitedNodes.clear();
		FindNode(m_root.get(), dataOfChildNode, mapOfVisitedNodes, pToChildNode);

		if (!pToFatherNode || !pToChildNode) return false;

		if (pToFatherNode->ContainsMember(pToChildNode->GetDataOfMember()))
			return true;
		else
			return false;
	};

	void ConnectNode(const dataType& dataOfParentNode, const dataType& dataOfChildNode) {
		GraphNode<dataType>* pToFatherNode = nullptr;
		GraphNode<dataType>* pToChildNode = nullptr;
		std::vector<GraphNode<dataType>*> mapOfVisitedNodes;

		FindNode(m_root.get(), dataOfParentNode, mapOfVisitedNodes, pToFatherNode);
		if (!pToFatherNode) throw std::out_of_range("Father node does not exist");

		mapOfVisitedNodes.clear();
		FindNode(m_root.get(), dataOfChildNode, mapOfVisitedNodes, pToChildNode);
		if (!pToChildNode) throw std::out_of_range("Child node does not exist");

		pToFatherNode->AddMember(pToChildNode);
	};
	void RemoveConnection(const dataType& dataOfParentNode, const dataType& dataOfChildNode) {
		GraphNode<dataType>* pToFatherNode = nullptr;
		GraphNode<dataType>* pToChildNode = nullptr;
		std::vector<GraphNode<dataType>*> mapOfVisitedNodes;

		FindNode(m_root.get(), dataOfParentNode, mapOfVisitedNodes, pToFatherNode);
		if (!pToFatherNode) throw std::out_of_range("Father node does not exist");

		mapOfVisitedNodes.clear();
		FindNode(m_root.get(), dataOfChildNode, mapOfVisitedNodes, pToChildNode);
		if (!pToChildNode) throw std::out_of_range("Child node does not exist");
		pToFatherNode->RemoveMember(pToChildNode);
	};

	void RemoveNode(const dataType& dataOfNodeToBeRemoved, const dataType& dataOfFutureNodeParent) {
		GraphNode<dataType>* pToFatherNode = nullptr;
		GraphNode<dataType>* pToNodeToBeRemoved = nullptr;
		GraphNode<dataType>* pToInheritorNode = nullptr;
		std::vector<GraphNode<dataType>*> mapOfVisitedNodes;

		FindNode(m_root.get(), dataOfNodeToBeRemoved, mapOfVisitedNodes, pToNodeToBeRemoved);
		if (!pToNodeToBeRemoved) throw std::out_of_range("Child node does not exist");
		mapOfVisitedNodes.clear();

		FindNode(m_root.get(), dataOfFutureNodeParent, mapOfVisitedNodes, pToInheritorNode);
		if (!pToInheritorNode) throw std::out_of_range("Node that inharits connection has not been found");
		mapOfVisitedNodes.clear();

		for (int i = 0; i < pToNodeToBeRemoved->NumberOfChildren(); ++i)
		{
			pToInheritorNode->AddMember(pToNodeToBeRemoved->GetChildAtIndex(i));
		}

		FindFatherOfNode(m_root.get(), dataOfNodeToBeRemoved, mapOfVisitedNodes, pToFatherNode);
		for (; 
			pToFatherNode; 
			pToFatherNode = nullptr, 
			FindFatherOfNode(m_root.get(), dataOfNodeToBeRemoved, mapOfVisitedNodes, pToFatherNode))
		{

			pToFatherNode->RemoveMember(pToNodeToBeRemoved);
		}
		--m_numberOfNodes;
	};

	int NumberOfNodesInGraph() { return m_numberOfNodes; }
private:
	void FindFatherOfNode(GraphNode<dataType>* walkerVariable,
		const dataType& dataOfChildNode,
		std::vector<GraphNode<dataType>*>& mapOfVisitedNodes,
		GraphNode<dataType>*& fatherOfChildNode)
	{
		if (!walkerVariable) return;
		if (fatherOfChildNode) return;

		for (auto it = mapOfVisitedNodes.begin(); it != mapOfVisitedNodes.end(); ++it)
		{
			if ((*it)->GetDataOfMember() == walkerVariable->GetDataOfMember())
				return;
		}

		mapOfVisitedNodes.push_back(walkerVariable);
		if (walkerVariable->ContainsMember(dataOfChildNode))
		{
			fatherOfChildNode = walkerVariable;
			return;
		}

		for (int it = 0; it < walkerVariable->NumberOfChildren(); ++it)
		{
			FindNode(walkerVariable->GetChildAtIndex(it), dataOfChildNode, mapOfVisitedNodes, fatherOfChildNode);
			if (fatherOfChildNode)
				return;
		}
	}

	void FindNode(GraphNode<dataType>* walkerVariable,
		const dataType& dataOfNodeToBefound,
		std::vector<GraphNode<dataType>*>& mapOfVisitedNodes,
		GraphNode<dataType>*& nodeToBefound
		)
	{
		if (!walkerVariable) return;
		if (nodeToBefound) return;

		for (auto it = mapOfVisitedNodes.begin(); it != mapOfVisitedNodes.end();++it)
		{
			if ((*it)->GetDataOfMember() == walkerVariable->GetDataOfMember())
				return;
		}

		mapOfVisitedNodes.push_back(walkerVariable);
		if (walkerVariable->GetDataOfMember() == dataOfNodeToBefound)
		{
			nodeToBefound = walkerVariable;
			return;
		}

		for (int it = 0; it < walkerVariable->NumberOfChildren(); ++it)
		{
			FindNode(walkerVariable->GetChildAtIndex(it), dataOfNodeToBefound, mapOfVisitedNodes, nodeToBefound);
			if (nodeToBefound)
				return;
		}
		
	}

	std::shared_ptr<GraphNode<dataType>> m_root;
	int m_numberOfNodes = 0;
};