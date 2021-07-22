#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "..\\..\\myfunctions.h"
#include "..\\..\\myclasses.h"
using namespace std;
void myopen(ifstream &fin, const char* fname, const int n = ios_base::in);
void myopen(ofstream &fout, const char* fname, const int n = ios_base::out | ios_base::trunc);
const int nname = 24, nval = 4;
struct session { char name[nname]; int val[nval]; float midl; };
const int stsize = sizeof(session);
int main()
{
	setlocale(LC_CTYPE, "rus"); 
	{cout << "=== Задание 1 ==========\n";
	ifstream fin1, fin2;
	cout << "Открытие файла 14.1.txt" << endl;
	myopen(fin1, "14.1.txt");
	fin1.close();
	//myopen(fin2, "fabuyuyc.txt"); fin2.close();
	}

	{cout << "\n=== Задание 2 ==========\n"; 
	cout << "Посимвольное запись в файл первой строки.\n";
	cout << "Посимвольное добавление в файл второй строки.\n";
	cout << endl;
	ofstream fout;
	char *fname = "14.2.txt";
	myopen(fout, fname);
	char *s1 = "1111111111111111111";
	for (int i = 0; i < 20; i++) fout.put(s1[i]);
	fout.put('\n');
	fout.close();
	myopen(fout, fname, ios_base::app);
	char *s2 = "2222222222222222222";
	for (int i = 0; i < 20; i++) fout.put(s2[i]);
	fout.put('\n');
	fout.close();
	ifstream fin;
	myopen(fin, fname);
	cout << "Посимвольное чтение файла:" << endl;
	while (!fin.eof()) {
		char ch;
		fin.get(ch);
		cout << ch;
	}
	fin.close();
	}

	{//cout << "=== Задание 3a ==========\n";
	ofstream fout;
	char *fname = "14.3.txt";
	myopen(fout, fname);
	int m = 12345;
	float a = acos(-1);
	fout << "====================\n";
	fout << fixed << setprecision(2) << "m = " << setw(7) << m <<"\n" <<
		"a = " << setw(7) << a << "\n";
	fout << "====================\n";
	fout.close();
	cout << "=== Задание 3b ==========\n";
	ifstream fin;
	myopen(fin, fname);
	const int maxlen = 50;
	char s[maxlen];
	int n;
	float b;
	fin >> s;
	fin >> s >> s >> n;
	fin >> s >> s >> b;
	fin.close();
	cout << n << " " << b<<endl;
	myopen(fin, fname);
	int k;
	float c;
	fin.getline(s, maxlen);
	fin.getline(s, maxlen); k = atoi(s + 6);
	fin.getline(s, maxlen); c = atof(s + 7);
	fin.close();
	cout << k << " " << c << endl;
	}

	{cout << "\n=== Задание 4 ==========\n";
	cout << "Скопировано файлов:";
	system("copy 14.4.txt Отличники.txt");
	cout << endl;
	ifstream fin;
	myopen(fin, "Группа 3.txt");
	ofstream fout;
	myopen(fout, "Отличники.txt",ios_base::app);
	while (!fin.eof()) {
		const int nv = 4; int v[nv], i;
		char s[30], t[30];
		fin >> s >> t;
		for (i = 0; i < nv; i++) fin >> v[i];
		for (i = 0; i < nv; i++) if (v[i] < 9) break;
		if (i == nv) {
			fout <<left<< setw(12)<< s  << setw(8)<< t ;
			for (i = 0; i < nv; i++) fout<<left << setw(3) << v[i];
			fout << endl;
		}
	}
	fin.close();
	fout.close();
	cout << "Отсортированный список: " << endl;
	myopen(fin, "Отличники.txt");
	const int maxlen = 100;
	char k[maxlen];
	while (!fin.eof()) {
		fin.getline(k, maxlen);
		cout << k << endl;
	}
	fin.close();
	}

	{cout << "=== Задание 5 ==========\n";
	ofstream fout;
	myopen(fout, "14.5.bin", ios_base::binary);
	int m = 100;  fout.write((char*)&m, sizeof(m));
	double a = 173.904;   fout.write((char*)&a, sizeof(a));
	int X[] = {1,2,3,5,7,11,13,17,19};
	int nx = sizeof(X) / sizeof(X[0]);
	fout.write((char*)&nx, sizeof(nx));
	fout.write((char*)X, nx*sizeof(nx));
	char s[] = "********************";
	int ns = sizeof(s) / sizeof(s[0]) + 1;
	fout.write((char*)&ns, sizeof(ns));
	fout.write(s, ns * sizeof(ns));
	//const int nname = 24, nval = 4;
	//struct session { char name[nname]; int val[nval]; float midl; };
	session st1 = { "Липницкий А.Н.", 8 ,9,7,9,8.25 };
	fout.write((char*)&st1, sizeof(st1));
	fout.close();
	ifstream fin;
	myopen(fin, "14.5.bin", ios_base::binary);
	int n; fin.read((char*)&n, sizeof(n));
	cout << n << endl;
	double b; fin.read((char*)&b, sizeof(b));
	cout << b << endl;
	int ny; fin.read((char*)&ny, sizeof(ny));
	int *Y = new int[ny];
	fin.read((char*)Y,ny*sizeof(ny));
	for (int i = 0; i < ny; i++)
		cout << Y[i]<<" ";
	cout << endl;
	int nt;
	fin.read((char*)&nt, sizeof(nt));
	char*t = new char[nt];
	fin.read(t, nt * sizeof(nt));
	cout << t << endl;
	session st2;
	fin.read((char*)&st2, sizeof(st2));
	cout << st2.name<<"  ";
	for (int i = 0; i < nval; i++)
		cout << st2.val[i] << " ";
	cout << st2.midl << endl;
	fin.close();
	}

	{cout << "\n=== Задание 6 ==========\n";
	int nstud = strcount("Группа 3.txt");
	session *stud = new session[nstud];
	ifstream fin; myopen(fin, "Группа 3.txt");
	const int maxlen = 50;
	char tmp[maxlen];
	for (int i = 0; i < nstud; i++) {
		fin >> stud[i].name >> tmp;
		strcat(stud[i].name, " ");
		strcat(stud[i].name, tmp);
		stud[i].midl = 0;
		for (int j = 0; j < nval; j++) {
			fin >> stud[i].val[j];
			stud[i].midl+= stud[i].val[j];
		}
		stud[i].midl /= nval;
	}
	fin.close();
	session **pstud = new session*[nstud];
	for (int i = 0; i < nstud; i++) {
		pstud[i] = &stud[i];
	}
	mysrt((char**)pstud, nstud, 1);
	ofstream fout;  myopen(fout, "Группа 3.bin", ios_base::binary);
	fout.write((char*)&nstud, sizeof(int));
	for (int i = 0; i < nstud; i++) {
		fout.write((char*)pstud[i], stsize);
	}
	fout.close();
	myopen(fin, "Группа 3.bin", ios_base::binary);
	int ns;
	fin.read((char*)&ns, sizeof(ns));
	for (int i = 0; i < nstud; i++) {
		session st;
		fin.read((char*)&st, stsize);
		cout << left  << setw(25) << st.name;
		for (int i = 0; i < nval; i++)
			cout << setw(3) << st.val[i];
		cout << right << setw(8) << st.midl << endl;
	}
	fin.close();
	delete[]stud; delete[]pstud;
	}

	system("pause");
	return 0;
}
void myopen(ifstream &fin, const char* fname, const int n) {
	fin.open(fname, n);
	
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла " << fname << endl;
		system("pause"); exit(1);
	}
}
void myopen(ofstream &fout, const char* fname, const int n ) {
	fout.open(fname, n);
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла " << fname << endl;
		system("pause"); exit(1);
	}
}
