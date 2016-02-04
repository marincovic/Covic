#pragma once

#include<memory>

template<typename T>
class Node
{
private:
	T m_data;
	std::shared_ptr<Node<T>> m_pNextNode = nullptr;
public:
	Node(T data, std::shared_ptr<Node<T>> pNextNode = nullptr)
	{
		m_data = data;
		m_pNextNode = pNextNode;
	}

	Node(std::shared_ptr<Node<T>> pNextNode) { m_pNextNode = pNextNode; }

	virtual ~Node() { }

	//void SetData(const T& data) { m_data = data; }
	const T& GetData() const { return m_data; }

	void SetNext(std::shared_ptr<Node<T>> pNext) { m_pNextNode = pNext; }
	std::shared_ptr<Node<T>> GetNext() { return m_pNextNode; }
};