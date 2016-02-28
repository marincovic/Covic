#pragma once

#include<vector>
#include<exception>
#include<algorithm>


// Nije mi jasno èemu služi èlan moveWeightType: ne koristite ga nigdje,
// osim u metodi GetWieghtOfMove (koja je krivo nazvana, treba biti GetWeightOfMove)
// za koju nemate niti jedan test napisan! Njome nepotrebno zagaðujete suèelje!
// Nekako mi se èini da je NextChildStruct nepotrebna klasa jer ju ionako
// svugdje koristite kao ovojnicu oko pokazivaèan na sljedeæi GraphNode

// VAŽNO: smatram da biste sustavno trebali koristiti kljuènu rijeè class 
// umjesto struct. Struct je praktièki atavizam iz jezika C, zadržan zbog
// kompatibilnosti sa starim kodom, a danas se koristi samo za jednostavne 
// strukture koje sve èlanove imaju javno dostupne, da se ne mora eksplicitno
// pisati javno pravo pristupa
template<typename GraphNode, typename moveWeightType>
struct NextChildStruct
{
public:
	// Prazni konstruktor nema smisla jer prazni child je u biti nullptr
	//NextChildStruct() {}
	NextChildStruct(const GraphNode& nextNode, moveWeightType weightOfMove = 0) : m_NextChild(nextNode), m_weightOfMove(weightOfMove) {}
	~NextChildStruct()
	{
		// ovo ne valja jer pozivate operator delete na objektu, a ne na pokazivaèu.
		// Izvoðenje donje naredbe æe srušiti program (baciti iznimku)
		delete m_NextChild;
		// osim što u ovom sluèaju ovo nema smisla, èak i kada bi m_NextChild bio pokazivaè, nema
		// potrebe ovo raditi jer to radite u destruktoru i nakon toga m_NextChild neæe
		// više postojati (kao da ste pucali u èovjeka koji upravo umire i koji bi ionako 
		// sljedeæeg trenutka bio klinièki mrtav)
		m_NextChild = nullptr;
	}

	void SetNextChild(const GraphNode& nextChild) { m_NextChild = nextChild; }
	const GraphNode& GetNextChild() { return m_NextChild; }

	void SetWeightOfMove(moveWeightType weightOfMove) { m_weightOfMove = weightOfMove; }
	int GetWieghtOfMove() { return m_weightOfMove; }

private:
	GraphNode m_NextChild;
	moveWeightType m_weightOfMove;
};

template<typename dataTypeOfNode, typename moveWeightType>
struct GraphNode
{
public:
	GraphNode() {}
	GraphNode(const dataTypeOfNode& dataOfNode) :m_dataOfNode(dataOfNode) {}
	GraphNode(const dataTypeOfNode& dataOfNode, 
		const dataTypeOfNode& dataOfFirstChildNode,
		const moveWeightType& weightOfMovemenToNewChild = 0)
	{
		m_dataOfNode = dataOfNode;
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode<dataTypeOfNode, moveWeightType>*, moveWeightType>(new GraphNode<dataTypeOfNode, moveWeightType>(dataOfFirstChildNode,weightOfMovemenToNewChild)));
	}
	
	GraphNode(const dataTypeOfNode& dataOfNode, 
		const GraphNode<dataTypeOfNode, moveWeightType>* pToChild,
		const moveWeightType& weightOfMovemenToNewChild = 0)
	{
		m_dataOfNode = dataOfNode;
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode<dataTypeOfNode, moveWeightType>*, moveWeightType>(new GraphNode<dataTypeOfNode, moveWeightType>(pToChild, weightOfMovemenToNewChild)));
	}
	
	virtual ~GraphNode()
	{
		m_vectorOfNodeChildren.clear();
	}

	const dataTypeOfNode& GetDataOfNode() { return m_dataOfNode; }
	void SetDataOFNode(const dataTypeOfNode& newDataofNode) { m_dataOfNode = newDataofNode; }

	// Promijenio sam tip indeksa u size_t. 
	// Na taj naèin ne treba provjeravati je li indeks sluèajno manji od 0,
	// niti kompajler javlja upozorenje
	GraphNode<dataTypeOfNode,moveWeightType>* GetChildAtIndex(size_t index)
	{
		if (!m_vectorOfNodeChildren.size())
			return nullptr;
		if (index > m_vectorOfNodeChildren.size())
			throw std::out_of_range("Index out of range");
		return m_vectorOfNodeChildren.at(index)->GetNextChild();
	}
	
	const moveWeightType& GetMovementWeightToChildAtIndex(int index) {};
	
	void AddNewChild(GraphNode<dataTypeOfNode, moveWeightType>* newChildToBeAdded, moveWeightType WeightOFMovement = 0)
	{
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode<dataTypeOfNode, moveWeightType>*, moveWeightType>(newChildToBeAdded,WeightOFMovement));
	}
	
	void AddNewChild(const dataTypeOfNode& dataOfNewChild,moveWeightType WeightOFMovement = 0) {
		GraphNode<dataTypeOfNode, moveWeightType>* tempNode = new GraphNode<dataTypeOfNode, moveWeightType>(dataOfNewChild);
		m_vectorOfNodeChildren.push_back(new NextChildStruct<GraphNode<dataTypeOfNode,moveWeightType>*, moveWeightType>(tempNode,WeightOFMovement));
	}

	// ovaj èlan otkriva internu implementaciju bilo kome tko vidi GraphNode,
	// što nije dobro. Ja bih ovo napravio privatnim èlanom, a ako je potrebno,
	// klasu koja koristi GraphNode bih proglasio prijateljem, tako da može koristiti 
	// ovu metodu ako treba
	void RemoveChild(GraphNode<dataTypeOfNode, moveWeightType>* childToBeRemoved)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if (childToBeRemoved == (*it)->GetNextChild())
			{
				m_vectorOfNodeChildren.erase(it);
				return;
			}
		}
		throw std::out_of_range("Child does not exist");
	}
	
	void RemoveChild(const dataTypeOfNode& dataOfChildToBeRemoved)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if (dataOfChildToBeRemoved == (*it)->GetNextChild()->GetDataOfNode())
			{
				m_vectorOfNodeChildren.erase(it);
				return;
			}
		}
		throw std::out_of_range("Child does not exist");
	}

	bool ContainsChild(GraphNode<dataTypeOfNode, moveWeightType>* childToBeFound)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if ((*it)->GetNextChild() == childToBeFound)
				return true;
		}
		return false;
	}
	
	bool ContainsChild(dataTypeOfNode dataOfChildToBeFound)
	{
		for (auto it = m_vectorOfNodeChildren.begin(); it != m_vectorOfNodeChildren.end(); ++it)
		{
			if ((*it)->GetNextChild()->GetDataOfNode() == dataOfChildToBeFound)
				return true;
		}
		return false;
	}

private:
	dataTypeOfNode m_dataOfNode;
	std::vector<NextChildStruct<GraphNode<dataTypeOfNode,moveWeightType>*,moveWeightType>*> m_vectorOfNodeChildren;
};