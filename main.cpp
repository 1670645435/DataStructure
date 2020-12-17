#define _CRT_SECURE_NO_WARNINGS   //����
#define _CRT_SECURE_NO_DEPRECATE  
#pragma warning(disable:4996)     //ȫ������

#include"Displayresult.h"

using namespace std;

int main()
{	
	ifstream Testfile("TestText.txt");
	string temp;
	string Ttemp;
	getline(Testfile, temp);
	
	int Course_Num = atoi(temp.c_str());			//����һ�еĿγ���ת��Ϊint

	string* course = new string[Course_Num];		//�����ַ�������

	if (!Testfile.is_open()) {
		cout << "�ļ���ʧ��" << endl;
	}
	else {
		for (int i = 0; i < Course_Num; i++) {			//���ļ���Ŀγ���Ϣ�����ַ�������������
			getline(Testfile, Ttemp);
			course[i] = Ttemp;
		}
	}
	Testfile.close();
	

	//��txt�еĿγ���Ϣȫ������ṹ��������
	struct Course_Struct* classinfo = new Course_Struct[Course_Num];
	char* TempContext = new char[2048];
	for (int i = 0; i < Course_Num; i++) {			//���γ���Ϣ�ȴ洢�ڽṹ��������
		strcpy(TempContext, course[i].c_str());
		char* thistemp = strtok(TempContext, " ");   //�Կո�Ϊ�ָ�����ÿ�ſγ����Ƹ���thistemp
		classinfo[i].name = thistemp;
		classinfo[i].num = i;
		char* thistempp = strtok(NULL, " ");
		classinfo[i].score = atof(thistempp);
	}



	//���ṹ�������еĿγ���Ϣȫ��д���ڽӾ���
	MatrixGraph classgraph(Course_Num);
	char* namestring = new char[1024];
	for (int i = 0; i < Course_Num; i++) {				//������д���ڽӾ���
		strcpy(namestring, course[i].c_str());
		char* readpart = strtok(namestring, " ");		//readpart��һ���ַ��� ��Ϊ���޿γ�
		readpart = strtok(NULL, " ");			//�ӵڶ����ַ�����ʼΪ��̿γ� ��Ϊ��Ҫд���ڽӾ���Ŀγ�
		readpart = strtok(NULL, " ");
		
		while (readpart != NULL) {				//�ͽṹ�������е�name�Ƚϣ��ж�����num���Ӷ������ڽӾ���
			int this_num = ClassNumber(classinfo, readpart, Course_Num);
			classgraph.setEdge(i, this_num, 0);
			readpart = strtok(NULL, " ");
		}
	}


	double Eachterm[7];
	Eachterm[6] = 122;
	while (1) {
		cout << "������ǰ6��ѧ����ÿѧ�������޵�ѧ������(����122ѧ��,ƽ��ÿѧ�������16-19ѧ��)" << endl;
		cout << "��ע�� ÿѧ������ѧ�ֲ��ó���19" << endl;
		for (int i = 0; i < 6; i++) {
			cout << "��" << i + 1 << "ѧ�ڣ�";
			cin >> Eachterm[i];
			Eachterm[6] = Eachterm[6] - Eachterm[i];
			cin.clear();
		}
		if (Eachterm[6] <= 0) {
			cout << "����������ţ���7ѧ�ڽ�û�пγ̣��Ƿ�Ҫ����ѧ�֣� 1�����°���    2������" << endl;
			int ifcontinue;
			cin >> ifcontinue;
			if (ifcontinue == 2) break;
		}
		else break;
	}
	cout << "����7ѧ��ʣ��ѧ��Ϊ��" << Eachterm[6] << endl;


	int** TwoArray2 = new int*[20];
	for (int i = 0; i < 20; i++)
		TwoArray2[i] = new int[20];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			TwoArray2[i][j] = 100;
		}
	}

	TwoArray2 = classgraph.TopoSort(classinfo, Eachterm, 100);
	Display(TwoArray2, classinfo);

	while (1) {
		cout << "�Ƿ�Ҫ�����Ӻ�������ǣ�1    ��2" << endl;
		int delay;
		cin >> delay;
		if (delay == 2) break;

		while (1) {
			cout << "��������������������������������������������������" << endl;
			char* changeclass = new char[20];
			cout << "����������Ҫ�Ӻ�Ŀγ����ƣ�" << endl;
			cin >> changeclass;
			int changenum = ClassNumber(classinfo, changeclass, Course_Num);			//�ҵ���Ҫ���ĵĿγ̵ı��

			int** TwoArray3 = new int* [20];
			for (int i = 0; i < 20; i++)
				TwoArray3[i] = new int[20];
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					TwoArray3[i][j] = 100;
				}
			}

			TwoArray3 = classgraph.TopoSort(classinfo, Eachterm, changenum);
			Display(TwoArray3, classinfo);

			cout << "�Ƿ�����������Ҫ�Ӻ� �ǣ�1    ��2" << endl;
			int delay;
			cin >> delay;
			if (delay == 2) break;
		}
		break;
	}


	cout << "��лʹ�ô��ſ�ϵͳ������" << endl;
	system("pause");
}

