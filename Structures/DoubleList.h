#pragma once

#include <stdexcept>

#include "DoubleNode.h"

template<typename T>
class DoubleList
{
private:
	DoubleNode<T>* m_pTail{ nullptr };
	DoubleNode<T>* m_pHead{ nullptr };
	DoubleNode<T>* m_pIterator = nullptr;

	int m_listSize = 0;

public:
	DoubleList() {}

	DoubleList(const T& DataOfFirstMember)
	{
		m_pHead = m_pTail = m_pIterator = new DoubleNode<T>(DataOfFirstMember);
		++m_listSize;
	}

	const T& GetAt(int index) const
	{
		if (!m_pHead) throw std::out_of_range("List is empty");
		if (index >= Size() || index < 0)
			throw std::out_of_range("index out of range");

		DoubleNode<T>* walkerNode = m_pHead;
		while (--index >= 0)
			walkerNode = walkerNode->GetNext();
		return walkerNode->GetData();
	}

	int Size() const
	{
		return m_listSize;
	}

	void Append(const T& value)
	{
		if (!m_pHead)
			m_pHead = m_pTail = m_pIterator= new DoubleNode<T>{ value, nullptr, nullptr };
		else
		{
			DoubleNode<T>* pPrevious = m_pTail;
			DoubleNode<T>* pNew = new DoubleNode<T>{ value, nullptr, pPrevious };
			m_pTail = pNew;
			pPrevious->SetNext(pNew);
		}
		++m_listSize;
	}

	void InsertAt(int index, const T& value)
	{
		if (index > Size() || index < 0)
			throw std::out_of_range("Index out of range");

		if (index == 0)
		{
			m_pHead = new DoubleNode<T>{ value, m_pHead, nullptr };
			if (!m_pTail)
				m_pTail = m_pHead;
		}
		else
		{
			DoubleNode<T>* walkerNode = m_pHead;
			while (--index > 0)
				walkerNode = walkerNode->GetNext();
			DoubleNode<T>* newNode = new DoubleNode<T>{ value, walkerNode->GetNext(), walkerNode };
			walkerNode->SetNext(newNode);
			if (newNode->GetNext())
				newNode->GetNext()->SetPrevious(newNode);
			else
				m_pTail = newNode;
		}
		++m_listSize;
	}

	void RemoveAt(int index)
	{
		if (index >= Size() || index < 0)
			throw std::out_of_range("Index out of range");
		if (index == 0)
		{
			DoubleNode<T>* toBeRemoved = m_pHead;
			m_pHead = m_pHead->GetNext();
			if (!m_pHead)
				m_pTail = nullptr;
			delete toBeRemoved;
		}
		else
		{
			DoubleNode<T>* walkerNode = m_pHead;
			while (--index > 0)
				walkerNode = walkerNode->GetNext();
			DoubleNode<T>* toBeRemoved = walkerNode->GetNext();
			walkerNode->SetNext(toBeRemoved->GetNext());
			if (toBeRemoved->GetNext())
				toBeRemoved->GetNext()->SetPrevious(walkerNode);
			else
				m_pTail = toBeRemoved->GetPrevious();
			delete toBeRemoved;
		}
		--m_listSize;
	}

	DoubleNode<T>* IteratorNext() { 
		if (!Size()) throw std::out_of_range("List is Empty");
		m_pIterator = m_pIterator->GetNext();
		if (!m_pIterator)
		{
			m_pIterator = m_pTail;
			throw std::out_of_range("List iterator is at list end. Reset iterator or set to new index");
		}

		return m_pIterator;
	}

	DoubleNode<T>* IteratorPrev() { 
		if (!Size()) throw std::out_of_range("List is Empty");
		if (m_pIterator == m_pHead)
		{
			ResetIterator();
			throw std::out_of_range("List iterator is at begining of list. Reset iterator or set to new index");
		}
		m_pIterator = m_pIterator->GetPrevious();
		

		return m_pIterator;
	}

	DoubleNode<T>* GetIterator() {
		if (!Size()) throw std::out_of_range("List is Empty");

		return m_pIterator;
	}

	DoubleNode<T>* SetIteratorToAtIndex(int index) 
	{ 
		if (!Size()) std::out_of_range("List is empty");
		if (index < 0 || index>Size())
			std::out_of_range("Index is out of range");

		ResetIterator();
		while (--index)
			m_pIterator = m_pIterator->GetNext();
		return m_pIterator;
	}
	
	void ResetIterator() {
		if (!Size()) throw std::out_of_range("List is Empty");

		m_pIterator = m_pHead;
	}
};