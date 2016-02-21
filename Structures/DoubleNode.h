#pragma once

#include "Node.h"

template<typename T>
class DoubleNode
{
private:
	DoubleNode<T>* m_pPreviousNode{ nullptr };
	DoubleNode<T>* m_pNextNode{ nullptr };

	T m_data;
public:
	DoubleNode(const T& data, DoubleNode<T>* pNextNode = nullptr, DoubleNode<T>* pPreviousNode = nullptr)
	{
		m_pPreviousNode = pPreviousNode;
		m_pNextNode = pNextNode;
		m_data = data;
	}
	~DoubleNode() { }

	void SetPrevious(DoubleNode<T>* pPrevious) { m_pPreviousNode = pPrevious; }
	DoubleNode<T>* GetPrevious() const { return m_pPreviousNode; }

	const T& GetData() const { return m_data; }

	void SetNext(DoubleNode<T>* pNext) { m_pNextNode = pNext; }
	DoubleNode<T>* GetNext() const { return m_pNextNode; }
};