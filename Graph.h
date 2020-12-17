#pragma once

#include"Edge.h"

#define INF 0x3F3F3F3F    //��Ϊ�����
#define VISITED   1
#define UNVISITED 0

class Graph {		//ͼ��
public:
	int numVertex;   //�������
	int numEdge;     //������
	int* visited;    //���ʱ��
	int* Indegree;   //���

	Graph(int numVert);
	~Graph();

	int VerticesNum() const {	//��ö���ĸ���
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

Graph::Graph(int numVert) {		//ͼ�Ĺ��캯��
	numVertex = numVert;
	numEdge = 0;
	Indegree = new int[numVertex];	//��ȱ�
	visited = new int[numVertex];	//���ʱ�
	for (int i = 0; i < numVertex; i++) {	//���������ʼ��
		visited[i] = UNVISITED;
		Indegree[i] = 0;
	}
}

Graph::~Graph() {		//ͼ����������
	delete[] visited;
	delete[] Indegree;
}