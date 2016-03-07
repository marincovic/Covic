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
	// zlatno pravilo enkapsulacije: podatkovni �lanovi UVIJEK moraju biti privatni!
	TNextNode m_nextNode;
	double m_weightOfMovement;
};

// prema dogovoru, parametar predlo�ka po�inje velikim slovom
template<typename TId>
class GraphNode
{
	using Movement = MovementStruct<std::shared_ptr<GraphNode<TId>>>;
	template <typename TId> friend class Graph;
public:
	// mislim da prazni �vor uop�e nema smisla
	// GraphNode() {};
	GraphNode(const TId& id) : m_id(id) {};
	~GraphNode() {}

	const TId& GetId() { return m_id; }
	
	// mislim da ovo ne treba (za�to biste mijenjali id �vora?)
	//void SetDataOfMember(const TId& newDataMember) { m_id = newDataMember; }

	void AddSuccessor(const TId& successorId, double weightOfMovement = 0)
	{
		m_movements.emplace_back(std::make_shared<GraphNode<TId>>(successorId), weightOfMovement);
	}

	void RemoveSuccessor(const TId& successorId)
	{
		if (!NumberOfSuccessors())
			throw std::out_of_range("Node has no successors");

		const auto& found = std::find_if(m_movements.cbegin(), m_movements.cend(), [&successorId](const Movement& movement) { return successorId == movement.GetNextNode()->GetId(); });
		if (found != m_movements.cend())
		{
			m_movements.erase(found);
			return;
		}
		throw std::out_of_range("Node has no successor with that id");
	}

	bool HasSuccessor(const TId& successorId) const
	{
		return std::find_if(m_movements.cbegin(), m_movements.cend(), [&successorId](const Movement& movement) { return successorId == movement.GetNextNode()->GetId(); }) != m_movements.cend();
	}

	// ne vidim realnog razloga za�to biste nasljednike dohva�ali preko cjelobrojnog indeksa? 
	// Na taj na�in posredno otkrivate da su nasljednici pohranjeni u vektoru
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

	double GetWeightOfMovementToSuccessor(const TId& id) const
	{
		if (!HasSuccessor(id))
			throw std::out_of_range("Node has no successor with this id");

		return GetMovement(id)->GetWeightOfMovement();
	}
	void SetWeightOfMovementToSuccessor(const TId& id, const double& newWeight)
	{
		if (!HasSuccessor(id))
			throw std::out_of_range("Node has no successor with this id");

		return GetMovementNonConst(id).SetWeightOfMovement(newWeight);
	}
	size_t NumberOfSuccessors() const { return m_movements.size(); }

private:
	// ova metoda mora biti private jer njome otvarate prikaz implementacije (shared_ptr) prema vanjskom kodu
	std::shared_ptr<GraphNode<TId>> GetSuccessor(size_t index) const
	{
		// budite dosljedni a ne jednom vra�ati nullptr a u svim ostalim slu�ajevima bacati iznimku!
		//if (!NumberOfChildren())
		//	return nullptr;
		if (!NumberOfSuccessors())
			throw std::out_of_range("Node has no children");

		if (index > NumberOfSuccessors())
			throw std::out_of_range("Index out of range");

		return m_movements.at(index).GetNextNode();
	}

	const Movement* GetMovement(const TId& id) const
	{
		const auto& found = std::find_if(m_movements.cbegin(), m_movements.cend(), [&id](const Movement& movement) { return id == movement.GetNextNode()->GetId(); });
		return found != m_movements.cend() ? &*found : nullptr;
	}

	Movement& GetMovementNonConst(const TId& id)
	{
		for (size_t it = 0; it < m_movements.size();++it)
			{
				if (m_movements.at(it).GetNextNode()->GetId() == id)
					return m_movements.at(it);
			}
	}

	// za�to otkrivati internu implementaciju (shared_ptr)?
	void AddSuccessor(std::shared_ptr<GraphNode<TId>> newSuccessor, double weightOfMovement = 0)
	{
		m_movements.emplace_back(newSuccessor, weightOfMovement);
	}

	void RemoveSuccessor(std::shared_ptr<GraphNode<TId>> successor)
	{
		RemoveSuccessor(successor->GetId());
	}

private:
	TId m_id;
	std::vector<Movement> m_movements;
};