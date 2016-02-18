#pragma once

#include <memory>
#include <stdexcept>

#include "Node.h"

template<typename T>
class List
{
protected:
	Node<T>* m_pHead = nullptr;
	Node<T>* m_pTail = nullptr;

	Node<T>* m_pIterator = nullptr;

	int m_listSize = 0;

public:
	List() {}

	List(const T& firstMemberValue)
	{
		m_pHead = new Node<T>(firstMemberValue);
		m_pIterator = m_pTail = m_pHead;
	}

	List(const Node<T>* pNewNode)
	{
		m_pHead = new Node<T>(pNewNode);
		m_pIterator = m_pTail = m_pHead;
	}

	virtual ~List() {
		m_pTail = m_pIterator = nullptr;
		delete m_pHead;
	}

	const T& GetIteratorData()
	{
		if (m_pIterator)
			return m_pIterator->GetData();
		else
			throw std::out_of_range("List Is Empty");
	}

	Node<T>* GetIteratorPointer() {
		if (m_pIterator)
			return m_pIterator;
		else
			throw std::out_of_range("List is Empty");
	}

	Node<T>* IteratorNext() {
		if (m_pIterator)
			return m_pIterator = m_pIterator->GetNext();
		else
			throw std::out_of_range("List is Empty");
	}

	void IteratorRestart() { m_pIterator = m_pHead; }

	void SetIteratorAtIndex(int index)
	{
		if (!m_pHead) throw std::out_of_range("List is empty");
		if (index > Size()) throw  std::out_of_range("Index out of range");

		do
		{
			if (index) m_pIterator = m_pIterator->GetNext();

		} while (--index);
	}

	int Size() const { return m_listSize; }

	void Append(const T& value)
	{
		++m_listSize;

		if (!m_pHead)
		{
			m_pHead = new Node<T>(value);
			m_pIterator = m_pTail = m_pHead;
			return;
		}
		m_pTail->SetNext(new Node<T>(value));
		m_pTail = m_pTail->GetNext();
	}

	void InsertAt(int index, const T& value)
	{
		++m_listSize;
		if (index == 0)
			m_pHead = new Node<T>(value, m_pHead);
		else
		{
			Node<T>* pPrev = GetNextPtrAt(index - 1);
			Node<T>* pNext = pPrev->GetNext();
			pPrev->SetNext(new Node<T>(value, pNext));
		}
	}

	const T& GetAt(int index) { return GetNextPtrAt(index)->GetData(); }

	void RemoveAt(int index)
	{

		if (!m_pHead) throw std::out_of_range("List is Empty");
		if (index > Size())
			throw std::out_of_range("Index is out of list range");
		--m_listSize;

		if (index == 0)
			m_pHead = m_pHead->GetNext();
		else
		{
			Node<T>* pPrevious = GetNextPtrAt(index - 1);
			pPrevious->SetNext(pPrevious->GetNext());
		}
	}

	const T Pop()
	{
		if (Size())
			--m_listSize;
		else
			throw std::out_of_range("List is empty");

		T dataTemp = m_pHead->GetData();
		Node<T> * tempToBeDeletedVariable= m_pHead;
		if (!Size())
			m_pIterator = m_pTail = m_pHead = m_pHead->GetNext();
		else if (m_pHead == m_pIterator)
		{
			m_pHead = m_pIterator = m_pHead->GetNext();
		}
		tempToBeDeletedVariable->SetNext(nullptr);
		delete tempToBeDeletedVariable;
		return dataTemp;
	}

	const T Dequeue()
	{
		if (Size())
			--m_listSize;
		else
			throw std::out_of_range("List is empty");

		T dataTemp = m_pTail->GetData();
		Node<T> * tempToBeDeletedVariable = m_pTail;
		if (!Size())
			m_pIterator = m_pTail = m_pHead = m_pHead->GetNext();
		else if (m_pTail == m_pIterator)
		{
			m_pTail = m_pIterator = GetNextPtrAt(Size() - 1);
		}
		else
		{
			m_pTail = GetNextPtrAt(Size() - 1);
			m_pTail->SetNext(nullptr);
		}
		tempToBeDeletedVariable->SetNext(nullptr);
		delete tempToBeDeletedVariable;
		return dataTemp;
	}

	void DeleteMember(const T& dataOfMemberToBeDeleted)
	{
		if (!m_pHead)
			throw std::out_of_range("List is empty");
		if (m_pHead->GetData() == dataOfMemberToBeDeleted)
		{
			Node<T>* tempPointerToNode = m_pHead;
			if (m_pHead == m_pIterator)
				m_pHead = m_pIterator = m_pHead->GetNext();
			else
				m_pHead = m_pHead->GetNext();
			tempPointerToNode->SetNext(nullptr);
			delete tempPointerToNode;
		}
		else
		{
			for (Node<T>* tempNode = m_pHead; tempNode->GetNext(); tempNode = tempNode->GetNext())
			{
				if (tempNode->GetNext()->GetData() == dataOfMemberToBeDeleted)
				{
					Node<T>* tempPointerToNodeTOBeDeleted = tempNode->GetNext();
					tempNode->SetNext(tempPointerToNodeTOBeDeleted->GetNext());
					tempPointerToNodeTOBeDeleted->SetNext(nullptr);
					delete tempPointerToNodeTOBeDeleted;
				}
			}
		}
	}

	bool ContainsElement(const T& dataOfMemberToBeFaund)
	{
		if (!m_pHead)
			throw std::out_of_range("List is empty");
		for (Node<T>* tempNode = m_pHead; tempNode; tempNode = tempNode->GetNext())
			if (tempNode->GetData() == dataOfMemberToBeFaund)
				return true;
		return false;
	}

private:
	Node<T>* GetNextPtrAt(int index) const
	{
		if (!m_pHead)
			throw std::out_of_range("list is empty");
		Node<T>* pNext = m_pHead;
		while (--index >= 0)
		{
			if (!pNext)
				throw std::out_of_range("invalid index");
			pNext = pNext->GetNext();
		}
		if (!pNext)
			throw std::out_of_range("invalid index");
		return pNext;
	}
};