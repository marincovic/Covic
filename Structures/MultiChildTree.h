#pragma once

#include<stdexcept>
#include<vector>

template<typename T>
struct MultiChildTree
{
public:
	MultiChildTree(const T& DataOfNewMember, int NumberOfChildren = 0, bool PreAlocateNextNodeVector = false)
	{
		m_dataMember = DataOfNewMember;
		m_numberOfChildren = NumberOfChildren;
		m_PreAlocateNextNodeVector = PreAlocateNextNodeVector;
		if (PreAlocateNextNodeVector)
			m_nextNodeVector.insert(m_nextNodeVector.begin(), m_numberOfChildren, nullptr);
	}
	virtual ~MultiChildTree() {}

	const T& GetDataOfNode() { return m_dataMember; }
	void SetDataOfNode(const T& NewDataOfNode) { m_dataMember = NewDataOfNode; }

	MultiChildTree<T>* GetNextChildAtAdress(int Adress) {
		if( Adress < m_numberOfChildren )
			return m_nextNodeVector.at(Adress);
		else 
			throw std::out_of_range("Adress out of bound");
	}
	void SetNextChildAtAdress(int Adress, MultiChildTree<T>* NewChildToBeAdded)
	{
		if (!m_PreAlocateNextNodeVector)
			m_nextNodeVector.insert(m_nextNodeVector.end(), NewChildToBeAdded);
		else if (Adress < m_numberOfChildren)
			m_nextNodeVector.at(Adress) = NewChildToBeAdded;
		else
			throw std::out_of_range("Adress out of bound");
	}

private:
	T m_dataMember;
	int m_numberOfChildren;
	bool m_PreAlocateNextNodeVector;
	std::vector<MultiChildTree<T>*> m_nextNodeVector

};