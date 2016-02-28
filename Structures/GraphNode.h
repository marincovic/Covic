#pragma once

#include<vector>
#include<memory>

template <typename pToNode>
struct MovementStruct
{
public:
	MovementStruct(pToNode nextNode, double weightOfMovement) : m_nextNode(nextNode), m_weightOfMovement(weightOfMovement) {};
	pToNode m_nextNode;
	double m_weightOfMovement;
};



template<typename typeOfDataMember>
class GraphNode
{
public:
	GraphNode() {};
	GraphNode(typeOfDataMember dataMember) : m_dataMember(dataMember) {};
	~GraphNode() { m_vectorOfAllChildren.clear(); }

	const typeOfDataMember& GetDataOfMember() { return m_dataMember; }
	void SetDataOfMember(const typeOfDataMember& newDataMember) { m_dataMember = newDataMember; }

	void AddMember(const typeOfDataMember& dataOfNewMember, double weightOfMovement = 0)
	{
		m_vectorOfAllChildren.push_back(MovementStruct<std::shared_ptr<GraphNode<typeOfDataMember>>>(std::make_shared<GraphNode<typeOfDataMember>> (dataOfNewMember),weightOfMovement));
	}

	void RemoveMember(const typeOfDataMember& dataOfMemberToBeDeleted) {
		if (!NumberOfChildren()) throw std::out_of_range("Node has no children");

		if (!ContainsMember(dataOfMemberToBeDeleted)) throw std::out_of_range("Node has no child with contaning that data");

		for (auto it = m_vectorOfAllChildren.begin(); it != m_vectorOfAllChildren.end(); ++it)
		{
			if ((*it).m_nextNode->GetDataOfMember() == dataOfMemberToBeDeleted)
				it = m_vectorOfAllChildren.erase(it);
		}
	}

	bool ContainsMember(const typeOfDataMember& dataOfMemberToBeSearchedFor) {
		if (!NumberOfChildren()) return false;
		for (auto it = m_vectorOfAllChildren.begin(); it != m_vectorOfAllChildren.end(); ++it)
		{
			if ((*it).m_nextNode->GetDataOfMember() == dataOfMemberToBeSearchedFor)
				return true;
		}
		return false;
	}

	GraphNode<typeOfDataMember>* GetChildAtIndex(size_t index) {
		if (!NumberOfChildren()) return nullptr;

		if (index > NumberOfChildren()) throw std::out_of_range("Index out of range");

		return m_vectorOfAllChildren.at(index).m_nextNode.get();
	}
	double GetWeightOfMovementToChildAtIndex(size_t index)
	{
		if (!NumberOfChildren()) throw std::out_of_range("Node has no children");
		if (index > NumberOfChildren()) throw std::out_of_range("Index out of range");

		return m_vectorOfAllChildren.at(index).m_weightOfMovement;
	}

	int NumberOfChildren() { return m_vectorOfAllChildren.size(); }

private:
	typeOfDataMember m_dataMember;
	std::vector<MovementStruct<std::shared_ptr<GraphNode<typeOfDataMember>>>> m_vectorOfAllChildren;
};