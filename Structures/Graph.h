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
		m_numberOfNodes = 1; // nema smisla operator inkrementiranja kada se zna da æe ovo uvijek biti 1
	};
	~Graph() {};

	void AddNode(const TId& newNodeId, const TId& predecessorId, double weightOfMovement = 0)
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
			// buduæi da s iznimkom ništa ne radite veæ ju odmah bacate dalje, 
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

	void SetWeightOfMovementConnectingTwoNodes(const TId& firstNodeId, const TId& secondNodeId, double weightOfMovement = 0)
	{
		std::shared_ptr<GraphNode<TId>> firstNode = nullptr;
		std::shared_ptr<GraphNode<TId>> secondNode = nullptr;
		
		FindPredecessorAndSuccessor(firstNodeId, secondNodeId, firstNode, secondNode);
		
		firstNode->SetWeightOfMovementToSuccessor(secondNodeId, weightOfMovement);
	}

	double GetWeightOfMovementConnectingTwoNodes(const TId& firstNodeId, const TId& secondNodeId)
	{
		std::shared_ptr<GraphNode<TId>> firstNode = nullptr;
		std::shared_ptr<GraphNode<TId>> secondNode = nullptr;

		FindPredecessorAndSuccessor(firstNodeId, secondNodeId, firstNode, secondNode);

		return firstNode->GetWeightOfMovementToSuccessor(secondNodeId);
	}

	void ConnectNodes(const TId& predecessorId, const TId& successorId, double weightOfMovement = 0)
	{
		std::shared_ptr<GraphNode<TId>> predecessor = nullptr;
		std::shared_ptr<GraphNode<TId>> successor = nullptr;
		FindPredecessorAndSuccessor(predecessorId, successorId, predecessor, successor);

		predecessor->AddSuccessor(successor, weightOfMovement);
	}

	void RemoveConnection(const TId& predecessorId, const TId& successorId)
	{
		std::shared_ptr<GraphNode<TId>> predecessor = nullptr;
		std::shared_ptr<GraphNode<TId>> successor = nullptr;
		

		FindPredecessorAndSuccessor(predecessorId, successorId, predecessor, successor);

		predecessor->RemoveSuccessor(successor);
	}

	void RemoveNode(const TId& idToRemove, const TId& newPredecessorId)
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
		--m_numberOfNodes;
	}

	int NumberOfNodesInGraph() { return m_numberOfNodes; }

	std::vector<TId> FindShortestRouteConnectingTwoNodes(const TId startPoint, const TId endPoint)
	{
		std::shared_ptr<GraphNode<TId>> startNode = nullptr;
		std::shared_ptr<GraphNode<TId>> endNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;
		std::vector<TId> shortest;
		std::vector<TId> helper;

		FindSuccessor(m_root, startPoint, visitedNodes, startNode);
		if (!startNode)
			throw std::out_of_range("Start node has not been found");
		visitedNodes.clear();

		FindSuccessor(m_root, endPoint, visitedNodes, endNode);
		if (!endNode)
			throw std::out_of_range("End node has not been found");
		visitedNodes.clear();

		FindShortestRoute(startNode, endNode, visitedNodes, shortest, helper);
		return shortest;
	}

	std::vector<TId> FindEasiestRouteConnectingTwoPoints(const TId startPoint, const TId endPoint)
	{
		std::shared_ptr<GraphNode<TId>> startNode = nullptr;
		std::shared_ptr<GraphNode<TId>> endNode = nullptr;
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;
		std::vector<TId> easiest;
		std::vector<TId> helper;
		int weight;

		FindSuccessor(m_root, startPoint, visitedNodes, startNode);
		if (!startNode)
			throw std::out_of_range("Start node has not been found");
		visitedNodes.clear();

		FindSuccessor(m_root, endPoint, visitedNodes, endNode);
		if (!endNode)
			throw std::out_of_range("End node has not been found");
		visitedNodes.clear();

		FindEasiestRoute(startNode, endNode, visitedNodes, easiest, helper, weight);
		return easiest;
	}


	

private:
	void FindPredecessorAndSuccessor(const TId& predecessorId, const TId& successorId,
		std::shared_ptr<GraphNode<TId>>& predecessor, std::shared_ptr<GraphNode<TId>>& successor)
	{
		std::vector<std::shared_ptr<GraphNode<TId>>> visitedNodes;

		FindSuccessor(m_root, predecessorId, visitedNodes, predecessor);
		if (!predecessor)
			throw std::out_of_range("Father node does not exist");

		visitedNodes.clear();
		FindSuccessor(m_root, successorId, visitedNodes, successor);
		if (!successor)
			throw std::out_of_range("Child node does not exist");
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
		int &routeWeight, // Tezina najlakas rute
		int routeWeightHelper = 0) // Tezina trenutacne rute
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
				routeWeightHelper + startPoint->GetWeightOfMovementToSuccessor(startPoint->GetSuccessor(i)->GetId())
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
	int m_numberOfNodes = 0;
};