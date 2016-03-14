#pragma once
#include"GraphNode.h"

#include<vector>
#include<map>
#include<memory>

template<typename TId>
class Graph {
public:
	Graph(const TId& id)
	{
		m_root = std::make_shared<GraphNode<TId>>(id,m_numberOfNodes);
		m_mapOfExistingNodes.emplace(m_nodeID++, m_root);
		m_numberOfNodes = 1; // nema smisla operator inkrementiranja kada se zna da æe ovo uvijek biti 1
	};
	~Graph() {};

	unsigned AddNode(const TId& newNodeId, const TId& predecessorId, double weightOfMovement = 0)
	{
		// preimenovano da bude u skladu s uobièajenom terminologijom (https://en.wikipedia.org/wiki/Directed_graph)
		std::shared_ptr<GraphNode<TId>> predecessorNode = nullptr;
		std::shared_ptr<GraphNode<TId>> successorNode = nullptr;
		// preimenovao sam jer je terminološki neispravno; to nije bila niti u kom sluèaju mapa, jer mapu èine parovi kljuè-vrijednost
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;

		FindSuccessor(m_root, predecessorId, visitedNodes, predecessorNode);
		if (!predecessorNode)
			throw std::out_of_range("Predecessor node does not exist");

		visitedNodes.clear();

		FindSuccessor(m_root, newNodeId, visitedNodes, successorNode);
		if (successorNode)
		{
			ConnectNodes(predecessorNode, successorNode);
			return INT32_MAX;
		}
		std::shared_ptr<GraphNode<TId>> tempNode = std::make_shared<GraphNode<TId>>(newNodeId, m_numberOfNodes);
		predecessorNode->AddSuccessor(tempNode, weightOfMovement);
		
		std::weak_ptr<GraphNode<TId>> weakTempNode = tempNode;

		m_mapOfExistingNodes.emplace(m_nodeID++,weakTempNode);

		++m_numberOfNodes;
		return m_nodeID-1;
	}

	const TId& GetPredecessorId(const unsigned id)
	{
		std::map<unsigned, std::weak_ptr<GraphNode<TId>>>::iterator it = m_mapOfExistingNodes.find(id);
		
		if (it == m_mapOfExistingNodes.end())
			throw std::out_of_range("Predecessor node does not exist");

		return it->second.lock()->GetId();
	}

	bool ContainsNode(const unsigned nodeId)
	{
		std::map<unsigned, std::weak_ptr<GraphNode<TId>>>::iterator it = m_mapOfExistingNodes.find(nodeId);

		if (it == m_mapOfExistingNodes.end())
			return false;
		return true;
		
	}

	bool CheckConnection(const unsigned predecessorId, const unsigned successorId)
	{
		std::map<unsigned, std::weak_ptr<GraphNode<TId>>>::iterator itPred = m_mapOfExistingNodes.find(predecessorId);
		if (itPred == m_mapOfExistingNodes.end()) 
			return false;

		std::map<unsigned, std::weak_ptr<GraphNode<TId>>>::iterator itSucc = m_mapOfExistingNodes.find(successorId);
		if (itSucc == m_mapOfExistingNodes.end()) 
			return false;

		return itPred->second.lock()->HasSuccessor(itSucc->second.lock()->GetNodeId());
	}

	void SetWeightOfMovementConnectingTwoNodes(const unsigned firstNodeId, const unsigned secondNodeId, double weightOfMovement = 0)
	{
		std::shared_ptr<GraphNode<TId>> firstNode = nullptr;
		std::shared_ptr<GraphNode<TId>> secondNode = nullptr;
		
		FindPredecessorAndSuccessor(firstNodeId, secondNodeId, firstNode, secondNode);
		
		firstNode->SetWeightOfMovementToSuccessor(secondNode->GetNodeId(), weightOfMovement);
	}

	double GetWeightOfMovementConnectingTwoNodes(const unsigned firstNodeId, const unsigned secondNodeId)
	{
		std::shared_ptr<GraphNode<TId>> firstNode = nullptr;
		std::shared_ptr<GraphNode<TId>> secondNode = nullptr;

		FindPredecessorAndSuccessor(firstNodeId, secondNodeId, firstNode, secondNode);

		return firstNode->GetWeightOfMovementToSuccessor(secondNode->GetNodeId());
	}

	void ConnectNodes(const unsigned predecessorId, const unsigned successorId, double weightOfMovement = 0)
	{
		std::shared_ptr<GraphNode<TId>> predecessor = nullptr;
		std::shared_ptr<GraphNode<TId>> successor = nullptr;
		FindPredecessorAndSuccessor(predecessorId, successorId, predecessor, successor);

		predecessor->AddSuccessor(successor, weightOfMovement);
	}

	void RemoveConnection(const unsigned predecessorId, const unsigned successorId)
	{
		std::shared_ptr<GraphNode<TId>> predecessor = nullptr;
		std::shared_ptr<GraphNode<TId>> successor = nullptr;
		

		FindPredecessorAndSuccessor(predecessorId, successorId, predecessor, successor);

		predecessor->RemoveSuccessor(successor->GetNodeId());
	}

	void RemoveNode(const unsigned idToRemove, const unsigned newPredecessorId)
	{
		std::shared_ptr<GraphNode<TId>> predecessor = nullptr;
		std::shared_ptr<GraphNode<TId>> pToNodeToBeRemoved = nullptr;
		std::shared_ptr<GraphNode<TId>> successor = nullptr;
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;

		FindPredecessorAndSuccessor(idToRemove, newPredecessorId, pToNodeToBeRemoved, successor);

		// kada prebacujete èvorove, što se dogaða s njihovim težinskim faktorima (nekako mi se èini da se oni po putu izgube)
		for (size_t i = 0; i < pToNodeToBeRemoved->NumberOfSuccessors(); ++i)
		{
			successor->AddSuccessor(pToNodeToBeRemoved->GetSuccessor(i));
		}

		FindPredecessor(m_root, idToRemove, visitedNodes, predecessor);
		

		while (predecessor)
		{

			predecessor->RemoveSuccessor(pToNodeToBeRemoved);
			FindPredecessor(m_root, idToRemove, visitedNodes, predecessor = nullptr);
		}
		
		if (m_root->GetId() == idToRemove)
			m_root = std::shared_ptr<GraphNode<TId>>(successor);
		m_mapOfExistingNodes.erase(idToRemove);
		--m_numberOfNodes;
		
	}

	int NumberOfNodesInGraph() { return m_numberOfNodes; }

	std::vector<TId> FindShortestRouteConnectingTwoNodes(const unsigned startPoint, const unsigned endPoint)
	{
		std::shared_ptr<GraphNode<TId>> startNode = nullptr;
		std::shared_ptr<GraphNode<TId>> endNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;
		std::vector<TId> shortest;
		std::vector<TId> helper;

		FindPredecessorAndSuccessor(startPoint, endPoint, startNode, endNode);

		FindShortestRoute(startNode, endNode, visitedNodes, shortest, helper);
		return shortest;
	}

	std::vector<TId> FindEasiestRouteConnectingTwoPoints(const unsigned startPoint, const unsigned endPoint)
	{
		std::shared_ptr<GraphNode<TId>> startNode = nullptr;
		std::shared_ptr<GraphNode<TId>> endNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;
		std::vector<TId> easiest;
		std::vector<TId> helper;
		double weight;

		FindPredecessorAndSuccessor(startPoint, endPoint, startNode, endNode);

		FindEasiestRoute(startNode, endNode, visitedNodes, easiest, helper, weight);
		return easiest;
	}


	void CheckPtrQualaty()
	{
		std::map<unsigned, std::weak_ptr<GraphNode<TId>>>::iterator it = m_mapOfExistingNodes.find(0);
		for (; it != m_mapOfExistingNodes.end(); ++it)
		{
			if (it->second.expired())
				it = m_mapOfExistingNodes.erase(it);
		}
	}

private:
	void FindPredecessorAndSuccessor(const unsigned predecessorId, const unsigned successorId,
		std::shared_ptr<GraphNode<TId>>& predecessor, std::shared_ptr<GraphNode<TId>>& successor)
	{
		std::map<unsigned, std::weak_ptr<GraphNode<TId>>>::iterator it  = m_mapOfExistingNodes.find(predecessorId);
		if (it == m_mapOfExistingNodes.end())
			throw std::out_of_range("Father node does not exist");
		predecessor = it->second.lock();

		it = m_mapOfExistingNodes.find(successorId);
		if (it == m_mapOfExistingNodes.end())
			throw std::out_of_range("Child node does not exist");
		successor = it->second.lock();
	}

	void FindShortestRoute(
		std::shared_ptr<GraphNode<TId>> startPoint, // Tocka u kojoj se trenutacno nalazimo	
		std::shared_ptr<GraphNode<TId>> endPoint,// Krajnja tocka 
		std::vector<std::shared_ptr<GraphNode<TId>>> &visitedNodes,// Lista svih tocaka koje smo prosli
		std::vector<TId> &shortest,// Lista najlakse rute
		std::vector<TId> &helper)// Pomocna lista)
	{
		if (!startPoint || !endPoint)
			return;
		if (startPoint == endPoint)
		{
			helper.push_back(startPoint->GetId());
			if (shortest.size()>helper.size() || shortest.size() == 0)
				shortest = helper;
			return;
		}
		for each (auto iterator in visitedNodes)
		{
			if (startPoint == iterator)
				return;
		}
		visitedNodes.push_back(startPoint);
		helper.push_back(startPoint->GetId());

		for (size_t i = 0; i < startPoint->NumberOfSuccessors(); ++i)
		{
			FindShortestRoute(
				startPoint->GetSuccessor(i),
				endPoint,
				visitedNodes,
				shortest,
				helper
				);
			if (visitedNodes.size()) visitedNodes.pop_back();
			if (helper.size()) helper.pop_back();
		}
	}

	void FindEasiestRoute(
		std::shared_ptr<GraphNode<TId>> startPoint, // Tocka u kojoj se trenutacno nalazimo	
		std::shared_ptr<GraphNode<TId>> endPoint,// Krajnja tocka 
		std::vector<std::shared_ptr<GraphNode<TId>>> &visitedNodes,// Lista svih tocaka koje smo prosli
		std::vector<TId> &shortest,// Lista najlakse rute
		std::vector<TId>&helper, // Pomocna lista
		double &routeWeight, // Tezina najlakas rute
		double routeWeightHelper = 0) // Tezina trenutacne rute
	{
		if (!startPoint || !endPoint)
			return;
		if (startPoint == endPoint)
		{
			helper.push_back(startPoint->GetId());
			if (routeWeight > routeWeightHelper || shortest.size() == 0)
			{
				shortest = helper;
				routeWeight = routeWeightHelper;
			}
			return;
		}
		for each (auto iterator in visitedNodes)
		{
			if (startPoint == iterator)
				return;
		}
		visitedNodes.push_back(startPoint);
		helper.push_back(startPoint->GetId());

		for (size_t i = 0; i < startPoint->NumberOfSuccessors(); ++i)
		{
			FindEasiestRoute(
				startPoint->GetSuccessor(i),
				endPoint,
				visitedNodes,
				shortest,
				helper,
				routeWeight,
				routeWeightHelper + startPoint->GetWeightOfMovementToSuccessor(startPoint->GetSuccessor(i)->GetNodeId())
				);
			if (visitedNodes.size()) visitedNodes.pop_back();
			if (helper.size()) helper.pop_back();
		}
	}


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
	std::map<unsigned, std::weak_ptr<GraphNode<TId>>> m_mapOfExistingNodes;
	unsigned m_numberOfNodes = 0;
	unsigned m_nodeID = 0;
};