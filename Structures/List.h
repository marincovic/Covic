#pragma once

#include <memory>
#include <stdexcept>

#include "Node.h"

template<typename T>
class List
{
protected:
	std::shared_ptr<Node<T>> m_pHead = nullptr;
	std::shared_ptr<Node<T>> m_pTail = nullptr;

	std::shared_ptr<Node<T>> m_pIterator = nullptr;

	int m_listSize = 0;

public:
	List() {}

	List(const T& firstMemberValue)
	{
		m_pHead = std::make_shared<Node<T>>(firstMemberValue);
		m_pIterator = m_pTail = m_pHead;
	}

	List(const std::shared_ptr<Node<T>> pNewNode)
	{
		m_pHead = std::make_shared<Node<T>>(pNewNode);
		m_pIterator = m_pTail = m_pHead;
	}

	virtual ~List() {}

	const T& GetIteratorData()
	{
		if (m_pIterator)
			return m_pIterator->GetData();
		else
			throw std::out_of_range("List Is Empty");
	}

	std::shared_ptr<Node<T>> GetIteratorPointer() {
		if (m_pIterator)
			return m_pIterator;
		else
			throw std::out_of_range("List is Empty");
	}

	std::shared_ptr<Node<T>> IteratorNext() {
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

	virtual void Append(const T& value)
	{
		++m_listSize;

		if (!m_pHead)
		{
			m_pHead = std::make_shared<Node<T>>(value);
			m_pIterator = m_pTail = m_pHead;
			return;
		}
		m_pTail->SetNext(std::make_shared<Node<T>>(value));
		m_pTail = m_pTail->GetNext();
	}

	virtual void InsertAt(int index, const T& value)
	{
		++m_listSize;
		if (index == 0)
			m_pHead = std::make_shared<Node<T>>(value, m_pHead);
		else
		{
			std::shared_ptr<Node<T>> pPrev = GetNextPtrAt(index - 1);
			std::shared_ptr<Node<T>> pNext = pPrev->GetNext();
			pPrev->SetNext(std::make_shared<Node<T>>(value, pNext));
		}
	}

	const T& GetAt(int index) { return GetNextPtrAt(index)->GetData(); }

	virtual void RemoveAt(int index)
	{

		if (!m_pHead) throw std::out_of_range("List is Empty");
		if (index > Size())
			throw std::out_of_range("Index is out of list range");
		--m_listSize;

		if (index == 0)
			m_pHead = m_pHead->GetNext();
		else
		{
			std::shared_ptr<Node<T>> pPrevious = GetNextPtrAt(index - 1);
			pPrevious->SetNext(pPrevious->GetNext());
		}
	}

	const T& Pop()
	{
		if (Size())
			--m_listSize;
		else
			throw std::out_of_range("List is empty");

		T dataTemp = m_pHead->GetData();
		if (!Size())
			m_pIterator = m_pTail = m_pHead = m_pHead->GetNext();
		else if (m_pHead == m_pIterator)
		{
			m_pHead = m_pIterator = m_pHead->GetNext();
		}
		return dataTemp;
	}

	const T& Dequeue()
	{
		if (Size())
			--m_listSize;
		else
			throw std::out_of_range("List is empty");

		T dataTemp = m_pTail->GetData();
		if (!Size())
			m_pIterator = m_pTail = m_pHead = m_pHead->GetNext();
		else if (m_pHead == m_pIterator)
		{
			m_pTail = m_pIterator = GetNextPtrAt(Size() - 2);
		}
		return dataTemp;
	}

private:
	std::shared_ptr<Node<T>> GetNextPtrAt(int index) const
	{
		if (!m_pHead)
			throw std::out_of_range("list is empty");
		std::shared_ptr<Node<T>> pNext = m_pHead;
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