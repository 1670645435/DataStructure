#pragma once

class Edge {	//图的边类
public:
	int from;
	int to;
	int weight;
	Edge() {			//构造函数
		from = -1;  to = -1; weight = 0;
	}
	Edge(int f, int Course_Num, int w) {
		from = f;  to = Course_Num; weight = w;
	}
};

