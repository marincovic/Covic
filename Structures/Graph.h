#pragma once
#include"GraphNode.h"

#include<vector>
#include<memory>

template<typename dataType>
class Graph {
public:
	Graph(const dataType& dataOfFirstNode) {};
	~Graph() {};

	void AddNode(const dataType& dataOfNewNode, const dataType& dataOfFatherNode) {};
	const dataType& DataOfNode(const dataType& dataToBeSearchedBy) {};

	bool ContainsNode(const dataType& dataToBeFound) {};
	bool CheckConnection(const dataType& dataOfParentNode, const dataType& dataOfChildNode) {};

	void ConnectNode(const dataType& dataOfParentNode, const dataType& dataOfChildNode) {};
	void RemoveConnection(const dataType& dataOfParentNode, const dataType& dataOfChildNode) {};

	void RemoveNode(const dataType& dataOfNodeToBeRemoved, const dataType& dataOfFutureNodeParent) {};

	int NumberOfNodesInGraph() {};
private:
	void CheckForBadWeakPtr() {};
	std::vector<std::weak_ptr<GraphNode<dataType>>> m_vectorOfNodeInGraph;
};