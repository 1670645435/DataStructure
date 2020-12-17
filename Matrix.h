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
			matrix[i] = new int[numVertex];		//构造二维数组
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
	
	int** TopoSort(Course_Struct* classinfo, double everyterm[], int change);		//拓扑排序算法
};

MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i < numVertex; i++)
		delete[] matrix[i];
	delete[] matrix;
}

Edge MatrixGraph::FirstEdge(int oneVertex) {		//找到第一条边
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

Edge MatrixGraph::NextEdge(Edge preEdge) {		//找到下一条边
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
		numEdge++;					//边的条数++
		Indegree[to]++;				//顶点to的度++
	}
	matrix[from][to] = weight;      //将临近矩阵中的所代表的这条边的数从无穷大变为权重
}

void MatrixGraph::delEdge(int from, int to) {
	if (matrix[from][to] != INF) {
		numEdge--;					//边的条数--
		Indegree[to]--;				//顶点to的度--
	}
	matrix[from][to] = INF;
}

int** MatrixGraph::TopoSort(Course_Struct* classinfo, double everyterm[], int change) {		//拓扑排序算法

	int ClassChange = change;	    //ClassChange用于判断是否要进行某一门课程的延后，没有则默认设置成INF
	int Currentterm = 1;			//显示目前学期，一共7个学期

	double Termscore1 = 0;
	double Termscore2 = 0;		//用来累加两个队列中的学分总和

	int Termclass1 = 0;		
	int Termclass2 = 0;		//用来存储每个学期的课程编号

	int Delay = 0;		//用来判断是否要将某一门课向后拖延		
	int DelayClassTemp = INF;	//用来暂时存储要延后的课程的编号，初始化为无穷大，即无操作
	int DelayTermTemp = INF;	//用来暂存学期数


	this->ClearVisited(); //清除各顶点的访问标志


	//为避免破坏原图，复制原图的入度数组
	int* indegree = new int[this->VerticesNum()];
	for (int i = 0; i < this->VerticesNum(); i++) {
		indegree[i] = this->Indegree[i];
	}



	//图中入度为0的顶点先入队列1
	std::queue< int > que1, que2;
	for (int i = 0; i < this->VerticesNum(); i++) {
		if (indegree[i] == 0) { 
			que1.push(i); 
		}
	}

	if (ClassChange != 100) Delay = 1;     //二维数组用来存储每个学期的课程编号
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

			if ((Currentterm == DelayTermTemp + 1) && (Delay == 1)) {		//下一个学期的子集中
				element1 = DelayClassTemp; 
				Delay = 0;	//防止再次判定
			}
			else {
				element1 = que1.front();  
				que1.pop();
				if (element1 == ClassChange) {			//识别到是要延后的课程，则暂存这个节点，并且将u/v再次更新
					DelayClassTemp = element1;
					DelayTermTemp = Currentterm;
					element1 = que1.front();  
					que1.pop();
					ClassChange = INF;		//改变change的值，防止再次判定
				}
			}
			SetVisit(element1);
			TwoArray1[Currentterm][Termclass1] = element1;			//放入子集
			this->visited[element1] = true;

			for (Edge e = this->FirstEdge(element1); this->isEdge(e); e = this->NextEdge(e)) {	//这个点所有下一个点的入度减一
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


		if (Termscore1 < everyterm[Currentterm - 1]) {			//如果学分数小于规定学分，队列二将继续填充这一学期的课，并且score2初值设为score1
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
				if (element2 == ClassChange) {			//如果识别到是要延后的课程，则用storeclass暂存这个节点，并且将u/v再次更新
					DelayClassTemp = element2;
					DelayTermTemp = Currentterm;
					element2 = que2.front();  que2.pop();
					ClassChange = INF;		//改变change的值，防止再次判定
				}
			}
			SetVisit(element2);
			TwoArray1[Currentterm][Termclass2] = element2;
			this->visited[element2] = true;

			for (Edge e = this->FirstEdge(element2); this->isEdge(e); e = this->NextEdge(e)) {	//这个点所有下一个点的入度减一
				indegree[this->ToVertex(e)]--;
				if (indegree[this->ToVertex(e)] == 0)  que1.push(this->ToVertex(e));
			}
			Termscore2 += classinfo[element2].score;
			if (Termscore2 >= everyterm[Currentterm - 1]) {
				break;
			}
			Termclass2++;
		}

		if (Termscore2 < everyterm[Currentterm - 1]) {			//如果学分数小于规定学分，队列二将继续填充这一学期的课，并且score1初值设为score2
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
			std::cerr << "该图有环 拓扑排序失败" << std::endl; break;
		}
	}
	return TwoArray1;
}