#pragma once

#include <vector> 
#include <string> 
#include <fstream> 
#include <iostream> 
#include <queue>
#include <windows.h>
#include"Edge.h"
#include"Graph.h"

using namespace std;

struct Course_Struct {
	int num;
	double score;
	string name;
};

class MatrixGraph :public Graph {
private:
	int** matrix;
public:
	MatrixGraph(int numVert) :Graph(numVert) {
		matrix = (int**) new int[numVertex];
		for (int i = 0; i < numVertex; i++) {
			matrix[i] = new int[numVertex];		//�����ά����
		}
		for (int i = 0; i < numVertex; i++)
			for (int j = 0; j < numVertex; j++)
				matrix[i][j] = INF;
	}
	~MatrixGraph();

	Edge FirstEdge(int oneVertex);
	Edge NextEdge(Edge preEdge);
	void setEdge(int from, int to, int weight);
	void delEdge(int from, int to);
	
	int** TopoSort(Course_Struct* classinfo, double everyterm[], int change);		//���������㷨
};

MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i < numVertex; i++)
		delete[] matrix[i];
	delete[] matrix;
}

Edge MatrixGraph::FirstEdge(int oneVertex) {		//�ҵ���һ����
	Edge myEdge;
	myEdge.from = oneVertex;
	for (int i = 0; i < numVertex; i++) {
		if (matrix[oneVertex][i] != INF) {
			myEdge.to = i;
			myEdge.weight = matrix[oneVertex][i];
			break;
		}
	}
	return myEdge;
}

Edge MatrixGraph::NextEdge(Edge preEdge) {		//�ҵ���һ����
	Edge myEdge;
	myEdge.from = preEdge.from;
	if (preEdge.to < numVertex) {
		for (int i = preEdge.to + 1; i < numVertex; i++) {
			if (matrix[preEdge.from][i] != INF) {
				myEdge.to = i;
				myEdge.weight = matrix[preEdge.from][i];
				break;
			}
		}
	}
	return myEdge;
}

void MatrixGraph::setEdge(int from, int to, int weight) {
	if (matrix[from][to] == INF) {
		numEdge++;					//�ߵ�����++
		Indegree[to]++;				//����to�Ķ�++
	}
	matrix[from][to] = weight;      //���ٽ������е�������������ߵ�����������ΪȨ��
}

void MatrixGraph::delEdge(int from, int to) {
	if (matrix[from][to] != INF) {
		numEdge--;					//�ߵ�����--
		Indegree[to]--;				//����to�Ķ�--
	}
	matrix[from][to] = INF;
}

int** MatrixGraph::TopoSort(Course_Struct* classinfo, double everyterm[], int change) {		//���������㷨

	int ClassChange = change;	    //ClassChange�����ж��Ƿ�Ҫ����ĳһ�ſγ̵��Ӻ�û����Ĭ�����ó�INF
	int Currentterm = 1;			//��ʾĿǰѧ�ڣ�һ��7��ѧ��

	double Termscore1 = 0;
	double Termscore2 = 0;		//�����ۼ����������е�ѧ���ܺ�

	int Termclass1 = 0;		
	int Termclass2 = 0;		//�����洢ÿ��ѧ�ڵĿγ̱��

	int Delay = 0;		//�����ж��Ƿ�Ҫ��ĳһ�ſ��������		
	int DelayClassTemp = INF;	//������ʱ�洢Ҫ�Ӻ�Ŀγ̵ı�ţ���ʼ��Ϊ����󣬼��޲���
	int DelayTermTemp = INF;	//�����ݴ�ѧ����


	this->ClearVisited(); //���������ķ��ʱ�־


	//Ϊ�����ƻ�ԭͼ������ԭͼ���������
	int* indegree = new int[this->VerticesNum()];
	for (int i = 0; i < this->VerticesNum(); i++) {
		indegree[i] = this->Indegree[i];
	}



	//ͼ�����Ϊ0�Ķ����������1
	std::queue< int > que1, que2;
	for (int i = 0; i < this->VerticesNum(); i++) {
		if (indegree[i] == 0) { 
			que1.push(i); 
		}
	}

	if (ClassChange != 100) Delay = 1;     //��ά���������洢ÿ��ѧ�ڵĿγ̱��
	int** TwoArray1 = new int* [20];
	for (int i = 0; i < 20; i++)
		TwoArray1[i] = new int[20];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			TwoArray1[i][j] = 100;
		}
	}

	int element1 = 0;
	int	element2 = 0;
	while (!que1.empty() || !que2.empty()) {

		while (!que1.empty()) {

			if ((Currentterm == DelayTermTemp + 1) && (Delay == 1)) {		//��һ��ѧ�ڵ��Ӽ���
				element1 = DelayClassTemp; 
				Delay = 0;	//��ֹ�ٴ��ж�
			}
			else {
				element1 = que1.front();  
				que1.pop();
				if (element1 == ClassChange) {			//ʶ����Ҫ�Ӻ�Ŀγ̣����ݴ�����ڵ㣬���ҽ�u/v�ٴθ���
					DelayClassTemp = element1;
					DelayTermTemp = Currentterm;
					element1 = que1.front();  
					que1.pop();
					ClassChange = INF;		//�ı�change��ֵ����ֹ�ٴ��ж�
				}
			}
			SetVisit(element1);
			TwoArray1[Currentterm][Termclass1] = element1;			//�����Ӽ�
			this->visited[element1] = true;

			for (Edge e = this->FirstEdge(element1); this->isEdge(e); e = this->NextEdge(e)) {	//�����������һ�������ȼ�һ
				indegree[this->ToVertex(e)]--;
				if (indegree[this->ToVertex(e)] == 0)  
					que2.push(this->ToVertex(e));
			}
			Termscore1 += classinfo[element1].score;
			if (Termscore1 >= everyterm[Currentterm - 1]) {
				break;
			}
			Termclass1++;
		}


		if (Termscore1 < everyterm[Currentterm - 1]) {			//���ѧ����С�ڹ涨ѧ�֣����ж������������һѧ�ڵĿΣ�����score2��ֵ��Ϊscore1
			Termscore2 = Termscore1;
			Termclass2 = Termclass1;
		}
		else {
			Currentterm++;
			Termscore2 = 0;
			Termclass2 = 0;
		}

		while (!que2.empty()) {

			if ((Currentterm == DelayTermTemp + 1) && (Delay == 1)) {
				element2 = DelayClassTemp; 
				Delay = 0;
			}
			else {
				element2 = que2.front();  
				que2.pop();
				if (element2 == ClassChange) {			//���ʶ����Ҫ�Ӻ�Ŀγ̣�����storeclass�ݴ�����ڵ㣬���ҽ�u/v�ٴθ���
					DelayClassTemp = element2;
					DelayTermTemp = Currentterm;
					element2 = que2.front();  que2.pop();
					ClassChange = INF;		//�ı�change��ֵ����ֹ�ٴ��ж�
				}
			}
			SetVisit(element2);
			TwoArray1[Currentterm][Termclass2] = element2;
			this->visited[element2] = true;

			for (Edge e = this->FirstEdge(element2); this->isEdge(e); e = this->NextEdge(e)) {	//�����������һ�������ȼ�һ
				indegree[this->ToVertex(e)]--;
				if (indegree[this->ToVertex(e)] == 0)  que1.push(this->ToVertex(e));
			}
			Termscore2 += classinfo[element2].score;
			if (Termscore2 >= everyterm[Currentterm - 1]) {
				break;
			}
			Termclass2++;
		}

		if (Termscore2 < everyterm[Currentterm - 1]) {			//���ѧ����С�ڹ涨ѧ�֣����ж������������һѧ�ڵĿΣ�����score1��ֵ��Ϊscore2
			Termscore1 = Termscore2;
			Termclass1 = Termclass2;
		}
		else {
			Currentterm++;
			Termscore1 = 0;
			Termclass1 = 0;
		}
	}
	for (int i = 0; i < this->VerticesNum(); i++) {
		if (this->visited[i] == false) {
			std::cerr << "��ͼ�л� ��������ʧ��" << std::endl; break;
		}
	}
	return TwoArray1;
}