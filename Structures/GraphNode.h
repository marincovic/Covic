#pragma once

#include <vector>
#include <memory>
#include <algorithm>

template <typename TNextNode>
class MovementStruct
{
public:
	MovementStruct(TNextNode nextNode, double weightOfMovement) : m_nextNode(nextNode), m_weightOfMovement(weightOfMovement) {};
	~MovementStruct() {};

	const TNextNode& GetNextNode() const { return m_nextNode; }
	double GetWeightOfMovement() const { return m_weightOfMovement; }

	void SetWeightOfMovement(const double& newWeight) { m_weightOfMovement = newWeight; }
private:
	// zlatno pravilo enkapsulacije: podatkovni èlanovi UVIJEK moraju biti privatni!
	TNextNode m_nextNode;
	double m_weightOfMovement;
};

// prema dogovoru, parametar predloška poèinje velikim slovom
template<typename TId>
class GraphNode
{
	using Movement = MovementStruct<std::shared_ptr<GraphNode<TId>>>;
	template <typename TId> friend class Graph;
public:
	// mislim da prazni èvor uopæe nema smisla
	// GraphNode() {};
	GraphNode(const TId& id, unsigned nodeId) : m_nodeData(id) , m_nodeId(nodeId) {};
	~GraphNode() {}

	const TId& GetId() { return m_nodeData; }
	const unsigned GetNodeId() { return m_nodeId; }
	
	// mislim da ovo ne treba (zašto biste mijenjali id èvora?)
	void SetDataOfMember(const TId& newDataMember) { m_nodeData = newDataMember; }

	void AddSuccessor(const TId& successorId, int nodeId, double weightOfMovement = 0)
	{
		m_movements.emplace_back(std::make_shared<GraphNode<TId>>(successorId, nodeId), weightOfMovement);
	}

	void RemoveSuccessor(const unsigned successorNodeId)
	{
		if (!NumberOfSuccessors())
			throw std::out_of_range("Node has no successors");

		const auto& found = std::find_if(m_movements.cbegin(), m_movements.cend(), [&successorNodeId](const Movement& movement) { return successorNodeId == movement.GetNextNode()->GetNodeId(); });
		if (found != m_movements.cend())
		{
			m_movements.erase(found);
			return;
		}
		throw std::out_of_range("Node has no successor with that id");
	}

	bool HasSuccessor(const unsigned successorId) const
	{
		//return std::find_if(m_movements.cbegin(), m_movements.cend(), [&successorId](const Movement& movement) { return successorId == movement.GetNextNode()->GetId(); }) != m_movements.cend();
		for (size_t it = 0; it < m_movements.size(); ++it)
		{
			if (m_movements.at(it).GetNextNode()->GetNodeId() == successorId)
				return true;
		}
		return false;
	}

	// ne vidim realnog razloga zašto biste nasljednike dohvaæali preko cjelobrojnog indeksa? 
	// Na taj naèin posredno otkrivate da su nasljednici pohranjeni u vektoru
	//const TId& GetSuccessorId(size_t index)
	//{
	//	return GetSuccessor(index)->m_id;
	//}

	//double GetWeightOfMovementToSuccessor(size_t index)
	//{
	//	if (!NumberOfSuccessors())
	//		throw std::out_of_range("Node has no children");
	//	if (index > NumberOfSuccessors())
	//		throw std::out_of_range("Index out of range");
	//	return m_successors.at(index)->GetWeightOfMovement();
	//}

	double GetWeightOfMovementToSuccessor(const unsigned nodeId) const
	{
		if (!HasSuccessor(nodeId))
			throw std::out_of_range("Node has no successor with this id");

		return GetMovement(nodeId)->GetWeightOfMovement();
	}
	void SetWeightOfMovementToSuccessor(const unsigned nodeId, const double& newWeight)
	{
		if (!HasSuccessor(nodeId))
			throw std::out_of_range("Node has no successor with this id");

		return GetMovementNonConst(nodeId).SetWeightOfMovement(newWeight);
	}
	size_t NumberOfSuccessors() const { return m_movements.size(); }

private:
	// ova metoda mora biti private jer njome otvarate prikaz implementacije (shared_ptr) prema vanjskom kodu
	std::shared_ptr<GraphNode<TId>> GetSuccessor(size_t index) const
	{
		// budite dosljedni a ne jednom vraæati nullptr a u svim ostalim sluèajevima bacati iznimku!
		//if (!NumberOfChildren())
		//	return nullptr;
		if (!NumberOfSuccessors())
			throw std::out_of_range("Node has no children");

		if (index > NumberOfSuccessors())
			throw std::out_of_range("Index out of range");

		return m_movements.at(index).GetNextNode();
	}

	const Movement* GetMovement(const unsigned id) const
	{
		const auto& found = std::find_if(m_movements.cbegin(), m_movements.cend(), [&id](const Movement& movement) { return id == movement.GetNextNode()->GetNodeId(); });
		return found != m_movements.cend() ? &*found : nullptr;
	}

	Movement& GetMovementNonConst(const unsigned id)
	{
		for (size_t it = 0; it < m_movements.size();++it)
			{
				if (m_movements.at(it).GetNextNode()->GetNodeId() == id)
					return m_movements.at(it);
			}
	}

	// zašto otkrivati internu implementaciju (shared_ptr)?
	void AddSuccessor(std::shared_ptr<GraphNode<TId>> newSuccessor, double weightOfMovement = 0)
	{
		m_movements.emplace_back(newSuccessor, weightOfMovement);
	}

	void RemoveSuccessor(std::shared_ptr<GraphNode<TId>> successor)
	{
		RemoveSuccessor(successor->GetNodeId());
	}

private:
	unsigned m_nodeId;
	TId m_nodeData;
	std::vector<Movement> m_movements;
};