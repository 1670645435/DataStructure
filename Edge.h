#pragma once

class Edge {	//ͼ�ı���
public:
	int from;
	int to;
	int weight;
	Edge() {			//���캯��
		from = -1;  to = -1; weight = 0;
	}
	Edge(int f, int Course_Num, int w) {
		from = f;  to = Course_Num; weight = w;
	}
};

