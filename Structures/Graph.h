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

	void AddNode(const dataType& dataOfNewNode, const dataType& dataOfFatherNode,
		double weightOfMovement = 0) {
		std::shared_ptr<GraphNode<dataType>> pToFatherNode = nullptr;
		std::shared_ptr<GraphNode<dataType>> pToPosibleChildNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<dataType>>> mapOfVisitedNodes;

		FindNode(m_root, dataOfFatherNode, mapOfVisitedNodes, pToFatherNode);
		if (!pToFatherNode) throw std::out_of_range("Father node does notExist");

		mapOfVisitedNodes.clear();

		FindNode(m_root, dataOfNewNode, mapOfVisitedNodes, pToPosibleChildNode);
		if (pToPosibleChildNode)
		{
			
			try {
				ConnectNode(pToFatherNode, pToPosibleChildNode);
			}
			catch (std::out_of_range& error)
			{
				throw error;
			}
			return;
		}

		pToFatherNode->AddMember(dataOfNewNode,weightOfMovement);
		++m_numberOfNodes;
	};
	const dataType& DataOfNode(const dataType& dataToBeSearchedBy) {
		std::shared_ptr<GraphNode<dataType>> pToFatherNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<dataType>>> mapOfVisitedNodes;

		FindNode(m_root, dataToBeSearchedBy, mapOfVisitedNodes, pToFatherNode);

		if (!pToFatherNode) throw std::out_of_range("Father node does notExist");

		return pToFatherNode->GetDataOfMember();
	};


	bool ContainsNode(const dataType& dataToBeFound) {
		std::shared_ptr<GraphNode<dataType>> pToFatherNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<dataType>>> mapOfVisitedNodes;

		FindNode(m_root, dataToBeFound, mapOfVisitedNodes, pToFatherNode);

		if (!pToFatherNode)
			return false;
		else
			return true;

	};
	bool CheckConnection(const dataType& dataOfParentNode, const dataType& dataOfChildNode) {
		std::shared_ptr<GraphNode<dataType>> pToFatherNode = nullptr;
		std::shared_ptr<GraphNode<dataType>> pToChildNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<dataType>>> mapOfVisitedNodes;

		FindNode(m_root, dataOfParentNode, mapOfVisitedNodes, pToFatherNode);

		mapOfVisitedNodes.clear();
		FindNode(m_root, dataOfChildNode, mapOfVisitedNodes, pToChildNode);

		if (!pToFatherNode || !pToChildNode) return false;

		if (pToFatherNode->ContainsMember(pToChildNode->GetDataOfMember()))
			return true;
		else
			return false;
	};

	void ConnectNode(const dataType& dataOfParentNode, const dataType& dataOfChildNode,
		double weightOfMovement = 0) {
		std::shared_ptr<GraphNode<dataType>> pToFatherNode = nullptr;
		std::shared_ptr<GraphNode<dataType>> pToChildNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<dataType>>> mapOfVisitedNodes;

		FindNode(m_root, dataOfParentNode, mapOfVisitedNodes, pToFatherNode);
		if (!pToFatherNode) throw std::out_of_range("Father node does not exist");

		mapOfVisitedNodes.clear();
		FindNode(m_root, dataOfChildNode, mapOfVisitedNodes, pToChildNode);
		if (!pToChildNode) throw std::out_of_range("Child node does not exist");

		pToFatherNode->AddMember(pToChildNode,weightOfMovement);
	};
	void RemoveConnection(const dataType& dataOfParentNode, const dataType& dataOfChildNode) {
		std::shared_ptr<GraphNode<dataType>> pToFatherNode = nullptr;
		std::shared_ptr<GraphNode<dataType>> pToChildNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<dataType>>> mapOfVisitedNodes;

		FindNode(m_root, dataOfParentNode, mapOfVisitedNodes, pToFatherNode);
		if (!pToFatherNode) throw std::out_of_range("Father node does not exist");

		mapOfVisitedNodes.clear();
		FindNode(m_root, dataOfChildNode, mapOfVisitedNodes, pToChildNode);
		if (!pToChildNode) throw std::out_of_range("Child node does not exist");
		pToFatherNode->RemoveMember(pToChildNode);
	};

	void RemoveNode(const dataType& dataOfNodeToBeRemoved, const dataType& dataOfFutureNodeParent) {
		std::shared_ptr<GraphNode<dataType>> pToFatherNode = nullptr;
		std::shared_ptr<GraphNode<dataType>> pToNodeToBeRemoved = nullptr;
		std::shared_ptr<GraphNode<dataType>> pToInheritorNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<dataType>>> mapOfVisitedNodes;

		FindNode(m_root, dataOfNodeToBeRemoved, mapOfVisitedNodes, pToNodeToBeRemoved);
		if (!pToNodeToBeRemoved) throw std::out_of_range("Child node does not exist");
		mapOfVisitedNodes.clear();

		FindNode(m_root, dataOfFutureNodeParent, mapOfVisitedNodes, pToInheritorNode);
		if (!pToInheritorNode) throw std::out_of_range("Node that inharits connection has not been found");
		mapOfVisitedNodes.clear();

		for (int i = 0; i < pToNodeToBeRemoved->NumberOfChildren(); ++i)
		{
			pToInheritorNode->AddMember(pToNodeToBeRemoved->GetChildAtIndex(i));
		}

		FindFatherOfNode(m_root, dataOfNodeToBeRemoved, mapOfVisitedNodes, pToFatherNode);
		for (; 
			pToFatherNode; 
			pToFatherNode = nullptr, 
			FindFatherOfNode(m_root, dataOfNodeToBeRemoved, mapOfVisitedNodes, pToFatherNode))
		{

			pToFatherNode->RemoveMember(pToNodeToBeRemoved);
		}
			
		if(m_root->GetDataOfMember()==dataOfNodeToBeRemoved)
			m_root = std::shared_ptr<GraphNode<dataType>>(pToInheritorNode);
		--m_numberOfNodes;
	};

	int NumberOfNodesInGraph() { return m_numberOfNodes; }
private:
	void ConnectNode(std::shared_ptr<GraphNode<dataType>> fatherNode, std::shared_ptr<GraphNode<dataType>> childNode)
	{
		if (!fatherNode) throw std::out_of_range("Father node does not exist");
		if (!childNode) throw std::out_of_range("Child node does not Exist");

		fatherNode->AddMember(childNode);
	}
	void FindFatherOfNode(std::shared_ptr<GraphNode<dataType>> walkerVariable,
		const dataType& dataOfChildNode,
		std::vector<std::shared_ptr<GraphNode<dataType>>>& mapOfVisitedNodes,
		std::shared_ptr<GraphNode<dataType>>& fatherOfChildNode)
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

	void FindNode(std::shared_ptr<GraphNode<dataType>> walkerVariable,
		const dataType& dataOfNodeToBefound,
		std::vector<std::shared_ptr<GraphNode<dataType>>>& mapOfVisitedNodes,
		std::shared_ptr<GraphNode<dataType>>& nodeToBefound
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