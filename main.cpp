#define _CRT_SECURE_NO_WARNINGS   //兼容
#define _CRT_SECURE_NO_DEPRECATE  
#pragma warning(disable:4996)     //全部禁用

#include"Displayresult.h"

using namespace std;

int main()
{	
	ifstream Testfile("TestText.txt");
	string temp;
	string Ttemp;
	getline(Testfile, temp);
	
	int Course_Num = atoi(temp.c_str());			//将第一行的课程数转化为int

	string* course = new string[Course_Num];		//建立字符串数组

	if (!Testfile.is_open()) {
		cout << "文件打开失败" << endl;
	}
	else {
		for (int i = 0; i < Course_Num; i++) {			//将文件里的课程信息导入字符串数组中数组
			getline(Testfile, Ttemp);
			course[i] = Ttemp;
		}
	}
	Testfile.close();
	

	//将txt中的课程信息全部导入结构体数组中
	struct Course_Struct* classinfo = new Course_Struct[Course_Num];
	char* TempContext = new char[2048];
	for (int i = 0; i < Course_Num; i++) {			//将课程信息先存储在结构体数组中
		strcpy(TempContext, course[i].c_str());
		char* thistemp = strtok(TempContext, " ");   //以空格为分隔符将每门课程名称赋给thistemp
		classinfo[i].name = thistemp;
		classinfo[i].num = i;
		char* thistempp = strtok(NULL, " ");
		classinfo[i].score = atof(thistempp);
	}



	//将结构体数组中的课程信息全部写入邻接矩阵
	MatrixGraph classgraph(Course_Num);
	char* namestring = new char[1024];
	for (int i = 0; i < Course_Num; i++) {				//将数据写入邻接矩阵
		strcpy(namestring, course[i].c_str());
		char* readpart = strtok(namestring, " ");		//readpart第一个字符串 即为先修课程
		readpart = strtok(NULL, " ");			//从第二个字符串开始为后继课程 即为需要写进邻接矩阵的课程
		readpart = strtok(NULL, " ");
		
		while (readpart != NULL) {				//和结构体数组中的name比较，判断他的num，从而填入邻接矩阵
			int this_num = ClassNumber(classinfo, readpart, Course_Num);
			classgraph.setEdge(i, this_num, 0);
			readpart = strtok(NULL, " ");
		}
	}


	double Eachterm[7];
	Eachterm[6] = 122;
	while (1) {
		cout << "请输入前6个学期中每学期您想修的学分数：(共有122学分,平均每学期最好修16-19学分)" << endl;
		cout << "请注意 每学期所修学分不得超过19" << endl;
		for (int i = 0; i < 6; i++) {
			cout << "第" << i + 1 << "学期：";
			cin >> Eachterm[i];
			Eachterm[6] = Eachterm[6] - Eachterm[i];
			cin.clear();
		}
		if (Eachterm[6] <= 0) {
			cout << "如果这样安排，第7学期将没有课程，是否要安排学分？ 1：重新安排    2：继续" << endl;
			int ifcontinue;
			cin >> ifcontinue;
			if (ifcontinue == 2) break;
		}
		else break;
	}
	cout << "您第7学期剩余学分为：" << Eachterm[6] << endl;


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
		cout << "是否要进行延后操作：是：1    否：2" << endl;
		int delay;
		cin >> delay;
		if (delay == 2) break;

		while (1) {
			cout << "·························" << endl;
			char* changeclass = new char[20];
			cout << "请输入您想要延后的课程名称：" << endl;
			cin >> changeclass;
			int changenum = ClassNumber(classinfo, changeclass, Course_Num);			//找到想要更改的课程的编号

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

			cout << "是否还有其他课需要延后： 是：1    否：2" << endl;
			int delay;
			cin >> delay;
			if (delay == 2) break;
		}
		break;
	}


	cout << "感谢使用此排课系统！！！" << endl;
	system("pause");
}

