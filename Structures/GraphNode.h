#pragma once

#include<vector>

template<typename typeOfDataMember>
class GraphNode
{
public:
	GraphNode() {};
	GraphNode(typeOfDataMember dataMember) : m_dataMember(dataMember) {};
	~GraphNode() { m_vectorOfAllChildren.clear(); }

	const typeOfDataMember& GetDataOfMember() { return m_dataMember; }

	void AddMember(const typeOfDataMember& dataOfNewMember)
	{
		m_vectorOfAllChildren.push_back(new GraphNode<typeOfDataMember>(dataOfNewMember));
	}

	void RemoveMember(const typeOfDataMember& dataOfMemberToBeDeleted) {
		if (!NumberOfChildren()) throw std::out_of_range("Node has no children");

		if (!ContainsMember(dataOfMemberToBeDeleted)) throw std::out_of_range("Node has no child with contaning that data");

		for (auto it = m_vectorOfAllChildren.begin(); it != m_vectorOfAllChildren.end(); ++it)
		{
			if ((*it)->GetDataOfMember() == dataOfMemberToBeDeleted)
				it = m_vectorOfAllChildren.erase(it);
		}
	}

	bool ContainsMember(const typeOfDataMember& dataOfMemberToBeSearchedFor) {
		if (!NumberOfChildren()) return false;
		for (auto it = m_vectorOfAllChildren.begin(); it != m_vectorOfAllChildren.end(); ++it)
		{
			if ((*it)->GetDataOfMember() == dataOfMemberToBeSearchedFor)
				return true;
		}
		return false;
	}

	int NumberOfChildren() { return m_vectorOfAllChildren.size(); }

private:
	typeOfDataMember m_dataMember;
	std::vector<GraphNode<typeOfDataMember>*> m_vectorOfAllChildren;
};