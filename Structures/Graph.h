#pragma once
#include"GraphNode.h"

#include<vector>
#include<memory>

template<typename TId>
class Graph {
public:
	Graph(const TId& id)
	{
		m_root = std::make_shared<GraphNode<TId>>(id);
		m_numberOfNodes = 1; // nema smisla operator inkrementiranja kada se zna da �e ovo uvijek biti 1
	};
	~Graph() {};

	void AddNode(const TId& newNodeId, const TId& predecessorId, double weightOfMovement = 0)
	{
		// preimenovano da bude u skladu s uobi�ajenom terminologijom (https://en.wikipedia.org/wiki/Directed_graph)
		std::shared_ptr<GraphNode<TId>> predecessorNode = nullptr;
		std::shared_ptr<GraphNode<TId>> successorNode = nullptr;
		// preimenovao sam jer je terminolo�ki neispravno; to nije bila niti u kom slu�aju mapa, jer mapu �ine parovi klju�-vrijednost
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;

		FindSuccessor(m_root, predecessorId, visitedNodes, predecessorNode);
		if (!predecessorNode)
			throw std::out_of_range("Predecessor node does not exist");

		visitedNodes.clear();

		FindSuccessor(m_root, newNodeId, visitedNodes, successorNode);
		if (successorNode)
		{
			// budu�i da s iznimkom ni�ta ne radite ve� ju odmah bacate dalje, 
			// nema potrebe pisati try-catch blok 
			//try
			//{
			//	ConnectNode(predecessor, pToPosibleChildNode);
			//}
			//catch (std::out_of_range& error)
			//{
			//	throw error;
			//}
			ConnectNodes(predecessorNode, successorNode);
			return;
		}

		predecessorNode->AddSuccessor(newNodeId, weightOfMovement);
		++m_numberOfNodes;
	}

	const TId& GetPredecessorId(const TId& id)
	{
		std::shared_ptr<GraphNode<TId>> predecessorNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;

		FindSuccessor(m_root, id, visitedNodes, predecessorNode);

		if (!predecessorNode)
			throw std::out_of_range("Predecessor node does not exist");

		return predecessorNode->GetId();
	}

	bool ContainsNode(const TId& id)
	{
		std::shared_ptr<GraphNode<TId>> predecessor = nullptr;
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;

		FindSuccessor(m_root, id, visitedNodes, predecessor);

		return predecessor != nullptr;
	}

	bool CheckConnection(const TId& predecessorId, const TId& successorId)
	{
		std::shared_ptr<GraphNode<TId>> predecessor = nullptr;
		std::shared_ptr<GraphNode<TId>> successor = nullptr;
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;

		FindSuccessor(m_root, predecessorId, visitedNodes, predecessor);

		visitedNodes.clear();
		FindSuccessor(m_root, successorId, visitedNodes, successor);

		if (!predecessor || !successor)
			return false;

		return predecessor->HasSuccessor(successor->GetId());
	}

	void ConnectNodes(const TId& predecessorId, const TId& successorId, double weightOfMovement = 0)
	{
		std::shared_ptr<GraphNode<TId>> predecessor = nullptr;
		std::shared_ptr<GraphNode<TId>> successor = nullptr;
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;

		FindSuccessor(m_root, predecessorId, visitedNodes, predecessor);
		if (!predecessor)
			throw std::out_of_range("Father node does not exist");

		visitedNodes.clear();
		FindSuccessor(m_root, successorId, visitedNodes, successor);
		if (!successor)
			throw std::out_of_range("Child node does not exist");

		predecessor->AddSuccessor(successor, weightOfMovement);
	}

	void RemoveConnection(const TId& predecessorId, const TId& successorId)
	{
		std::shared_ptr<GraphNode<TId>> predecessor = nullptr;
		std::shared_ptr<GraphNode<TId>> successor = nullptr;
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;

		FindSuccessor(m_root, predecessorId, visitedNodes, predecessor);
		if (!predecessor)
			throw std::out_of_range("Father node does not exist");

		visitedNodes.clear();
		FindSuccessor(m_root, successorId, visitedNodes, successor);
		if (!successor)
			throw std::out_of_range("Child node does not exist");

		predecessor->RemoveSuccessor(successor);
	}

	void RemoveNode(const TId& idToRemove, const TId& newPredecessorId)
	{
		std::shared_ptr<GraphNode<TId>> predecessor = nullptr;
		std::shared_ptr<GraphNode<TId>> pToNodeToBeRemoved = nullptr;
		std::shared_ptr<GraphNode<TId>> successor = nullptr;
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;

		FindSuccessor(m_root, idToRemove, visitedNodes, pToNodeToBeRemoved);
		if (!pToNodeToBeRemoved)
			throw std::out_of_range("Successor node does not exist");
		visitedNodes.clear();

		FindSuccessor(m_root, newPredecessorId, visitedNodes, successor);
		if (!successor)
			throw std::out_of_range("Node that inherits connection has not been found");
		visitedNodes.clear();

		// kada prebacujete �vorove, �to se doga�a s njihovim te�inskim faktorima (nekako mi se �ini da se oni po putu izgube)
		for (size_t i = 0; i < pToNodeToBeRemoved->NumberOfSuccessors(); ++i)
		{
			successor->AddSuccessor(pToNodeToBeRemoved->GetSuccessor(i));
		}

		FindPredecessor(m_root, idToRemove, visitedNodes, predecessor);
		// ovo dolje je ru�na petlja (nije uop�e kandidat za for petlju!)
		for (; 
			predecessor; 
			predecessor = nullptr, 
			FindPredecessor(m_root, idToRemove, visitedNodes, predecessor))
		{

			predecessor->RemoveSuccessor(pToNodeToBeRemoved);
		}
			
		if (m_root->GetId() == idToRemove)
			m_root = std::shared_ptr<GraphNode<TId>>(successor);
		--m_numberOfNodes;
	}

	int NumberOfNodesInGraph() { return m_numberOfNodes; }

private:
	void ConnectNodes(std::shared_ptr<GraphNode<TId>> predecessor, std::shared_ptr<GraphNode<TId>> successor)
	{
		if (!predecessor)
			throw std::out_of_range("Predecessor node does not exist");
		if (!successor)
			throw std::out_of_range("Successor node does not exist");

		predecessor->AddSuccessor(successor);
	}

	void FindPredecessor(std::shared_ptr<GraphNode<TId>> walker,
		const TId& predecessorId,
		std::vector<std::shared_ptr<GraphNode<TId>>>& visitedNodes,
		std::shared_ptr<GraphNode<TId>>& predecessor)
	{
		if (!walker)
			return;
		if (predecessor)
			return;

		for (auto it = visitedNodes.begin(); it != visitedNodes.end(); ++it)
		{
			if ((*it)->GetId() == walker->GetId())
				return;
		}

		visitedNodes.push_back(walker);
		if (walker->HasSuccessor(predecessorId))
		{
			predecessor = walker;
			return;
		}

		for (size_t i = 0; i < walker->NumberOfSuccessors(); ++i)
		{
			FindSuccessor(walker->GetSuccessor(i), predecessorId, visitedNodes, predecessor);
			if (predecessor)
				return;
		}
	}

	void FindSuccessor(std::shared_ptr<GraphNode<TId>> walkerVariable,
		const TId& successorId,
		std::vector<std::shared_ptr<GraphNode<TId>>>& visitedNodes,
		std::shared_ptr<GraphNode<TId>>& successor)
	{
		if (!walkerVariable)
			return;
		if (successor)
			return;

		for (auto it = visitedNodes.begin(); it != visitedNodes.end(); ++it)
		{
			if ((*it)->GetId() == walkerVariable->GetId())
				return;
		}

		visitedNodes.push_back(walkerVariable);
		if (walkerVariable->GetId() == successorId)
		{
			successor = walkerVariable;
			return;
		}

		for (size_t i = 0; i < walkerVariable->NumberOfSuccessors(); ++i)
		{
			FindSuccessor(walkerVariable->GetSuccessor(i), successorId, visitedNodes, successor);
			if (successor)
				return;
		}
	}

	std::shared_ptr<GraphNode<TId>> m_root;
	int m_numberOfNodes = 0;
};