#pragma once

#include"Matrix.h"

int ClassNumber(Course_Struct* classinfo, char* fragment, int Course_Num) {
	for (int i = 0; i < Course_Num; i++) {
		if (strcmp(classinfo[i].name.c_str(), fragment) == 0) {    //�жϿγ� �����ؿγ̱��
			return classinfo[i].num;
		}
	}
}

void Display(int** t, struct Course_Struct* classinfo) {
	int** show = new int* [20];
	for (int i = 0; i < 20; i++)
		show[i] = new int[20];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			show[i][j] = 100;
		}
	}
	show = t;
	int count[10];			//��������ÿѧ�����˶����ſ�
	memset(count, 0, sizeof(count));
	for (int j = 1; j < 20; j++) {
		if (show[j][0] == 100)  break;
		for (int c = 0; c < 20; c++) {
			if (show[j][c] == 100)  break;
			count[j] ++;
		}
	}
	cout << endl;
	cout << "                          7��ѧ�ڵ��ſν�����£�" << endl;
	cout << "����������������������������������������������������������������������������" << endl;
	for (int j = 1; j < 20; j++) {
		if (show[j][0] == 100)  break;
		cout <<  "��"  << j <<  "ѧ�ڵĿγ���Ϊ��"  << count[j]   <<  "��      ����γ�������ʾ��"  << endl;
		for (int c = 0; c < 20; c++) {
			if (show[j][c] == 100)  break;
			cout << classinfo[show[j][c]].name << " " << endl;
		}
		cout << endl;
	}
	for (int i = 0; i < 20; i++)
		delete[]show[i];
	delete[]show;
}