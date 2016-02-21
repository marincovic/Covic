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

	const T& GetAt(int index)
	{
		if (!m_pHead) throw std::out_of_range("List is empty");
		if (index > Size()) throw std::out_of_range("index out of range");

		DoubleNode<T>* walkerNode = m_pHead;

		while (index--)
		{
			if (index) walkerNode = walkerNode->GetNext();
			else
				return walkerNode->GetData();
		}

	}

	int Size()
	{
		return m_listSize;
	}

	void Append(const T& value)
	{
		++m_listSize;
		if (!m_pHead)
			m_pHead = m_pTail = m_pIterator = new DoubleNode<T>{ value, nullptr, nullptr };
		else
		{
			m_pTail->SetNext(new DoubleNode<T>(value,nullptr,m_pTail));
			m_pTail = m_pTail->GetNext();

		}
	}

	void InsertAt(int index, const T& value)
	{

		if (!m_pHead)
		{
			m_pHead = m_pTail = new DoubleNode<T>{ value,nullptr,nullptr };
			++m_listSize;
			return;
		}
		if (index > Size()) throw std::out_of_range("Index out of range");

		else
		{

			DoubleNode<T>* walkerNode = m_pHead;

			do
			{
				if (index - 1) walkerNode = walkerNode->GetNext();
				else
				{
					DoubleNode<T>* newNode = new DoubleNode<T>(value, walkerNode, walkerNode->GetNext());
					walkerNode->SetNext(newNode);
					if (newNode->GetNext())
						newNode->GetNext()->SetPrevious(newNode);
					else
						m_pTail = newNode;
					++m_listSize;
					return;
				}
			} while (index--);
		}
	}

	void RemoveAt(int index)
	{
		if (!m_pHead)
			throw std::out_of_range("List is empty");

		if (index > Size())
			throw std::out_of_range("Index out of range");
		--m_listSize;
		if (index == 0)
		{
			DoubleNode<T>* toBeRemoved = m_pHead;
			m_pHead = m_pHead->GetNext();
			delete toBeRemoved;
		}
		else
		{
			DoubleNode<T>* walkerNode = m_pHead;
			do
			{
				if (index - 1) walkerNode = walkerNode->GetPrevious();
				else
				{
					DoubleNode<T>* toBeRemoved = walkerNode->GetNext();
					walkerNode->SetNext(toBeRemoved->GetNext());
					if (toBeRemoved->GetNext())
						toBeRemoved->GetNext()->SetPrevious(walkerNode);
					else
						m_pTail = toBeRemoved->GetPrevious();
					delete toBeRemoved;
					return;
				}
			} while (index--);
		}
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
		m_pIterator = m_pIterator->GetPrevious();
		if (!m_pIterator)
		{
			ResetIterator();
			throw std::out_of_range("List iterator is at list end. Reset iterator or set to new index");
		}

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

private:
};