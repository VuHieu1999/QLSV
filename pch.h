// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<string>
#include<string.h>
#include<stdio.h>
#include<cstdlib>
#define cRong 119
#define cCao 29
#define sizemenu 35
#pragma warning(disable : 4996)

int l_stt = 5, l_malop = 10, l_masv = 10, l_ngaysinh = 15, l_diemtb = 7;
int n;
int stt = 0; // Số thứ tự sinh viên trong danh sách
int i = 0;  //i là bước nhảy dòng trong DS ứng vs sinh viên
using namespace std;
typedef struct DataType
{
    char MaLop[11];
	char MaSinhVien[11];
	string HoTen;
	int NgS, TS, NS;
	float DiemTB;
};

typedef struct Node
{
	DataType data;
	Node *next; //tro den vi tri Node tiep theo
	Node *prev; // tro den vi tri Node sau no
};
typedef struct List
{
	Node *head;
	Node *tail;
};
//Cac thao tac tren danh sach
void Init(List &list);
Node *creatNode(DataType x);
bool isEmpty(List list);

//Cac thao tac chen
void addHead(List &list, DataType x);
void addTail(List &list, DataType x);
void insertInList(List &list, int k, DataType x);


//Cac thao tac xoa
void DelHead(List &list);
void DelTail(List &list);
void DelInList(List &list, int k);
void display(List list);
void input(List &list);
void output(const char *fileName, List list);


void xoa_man_hinh();
void SetSizeConsole();
void setColor(int x);
void gotoxy(int x, int y);
void chon_M(List &list);
void background(List list);
void menu_chinh(int choice);
void khung_thong_ke();
// TODO: add headers that you want to pre-compile here

#endif //PCH_H
