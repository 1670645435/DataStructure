#pragma once

#include"Edge.h"

#define INF 0x3F3F3F3F    //设为无穷大
#define VISITED   1
#define UNVISITED 0

class Graph {		//图类
public:
	int numVertex;   //顶点个数
	int numEdge;     //边条数
	int* visited;    //访问标记
	int* Indegree;   //入度

	Graph(int numVert);
	~Graph();

	int VerticesNum() const {	//获得顶点的个数
		return numVertex;
	}
	bool isEdge(Edge oneEdge) {		//
		return oneEdge.weight != INF && 0 <= oneEdge.from && oneEdge.from < numVertex && 0 <= oneEdge.to && oneEdge.to < numVertex;
	}
	int FromVertex(Edge oneEdge) {
		return oneEdge.from;
	}
	int ToVertex(Edge oneEdge) {
		return oneEdge.to;
	}
	void SetVisit(int v) {
		visited[v] = 0;
	}
	void ClearVisited() {
		for (int i = 0; i < numVertex; i++) {
			visited[i] = UNVISITED;
		}
	}
};

Graph::Graph(int numVert) {		//图的构造函数
	numVertex = numVert;
	numEdge = 0;
	Indegree = new int[numVertex];	//入度表
	visited = new int[numVertex];	//访问表
	for (int i = 0; i < numVertex; i++) {	//对两个表初始化
		visited[i] = UNVISITED;
		Indegree[i] = 0;
	}
}

Graph::~Graph() {		//图的析构函数
	delete[] visited;
	delete[] Indegree;
}