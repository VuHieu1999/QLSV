// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"
using namespace std;
void xoa_man_hinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void SetSizeConsole() // thay doi kich thuoc man hinh co the noi tren win 7 hoac 8 do khong cho phep thay doi kick thuoc Console
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	// thay doi tieu de cua so
	SetConsoleTitle(TEXT("Nguyen Huu Tien"));
	// thay doi kich thuoc console
	SMALL_RECT windowSize = { 0, 0, cRong - 1, cCao - 1 };
	SetConsoleWindowInfo(h, TRUE, &windowSize);
	// thay doi kich thuoc bo dem
	COORD bufferSize = { cRong, cCao };
	SetConsoleScreenBufferSize(h, bufferSize);
}
void setColor(int x)
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, x);
}
void gotoxy(int x, int y)
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void Init(List &list)
{
	list.head = NULL;
	list.tail = NULL;
	n = 0;
}

Node *creatNode(DataType x)
{
	Node *temp = new Node;
	if (temp == NULL) exit(1);
	else
	{
		temp->data = x;
		temp->next = NULL;
		temp->prev = NULL;
	}
	return temp;
}

bool isEmpty(List list)
{
	if (list.head == NULL) return true;
	return false;
}
void addHead(List &list, DataType x)
{
	/*
	Buoc1:Chen
		Co 2 TH: 1, neu list rong ;
				 2, neu list khong rong;
	Buoc2:
		so luong phan tu tang len 1;
	*/
	Node *temp = creatNode(x);
	if (isEmpty(list))
	{
		list.head = temp;
		list.tail = temp;
	}
	else
	{
		temp->next = list.head;
		list.head->prev = temp;
		list.head = temp;
	}
	n++;
	stt++;
	i += 2;
	gotoxy(0, 0); cout << "i = " << i << "stt" << stt;
}
void addTail(List &list, DataType x)
{
	/*
	Buoc1:Chen
		Co 2 TH: 1, neu list rong ;
				 2, neu list khong rong;
	Buoc2:
		so luong phan tu tang len 1;
	*/
	Node *temp = creatNode(x);
	if (isEmpty(list))
	{
		addHead(list, x);
	}
	else
	{
		list.tail->next = temp;
		temp->prev = list.tail;
		list.tail = temp;
		n++;
	}


}
void insertInList(List &list, int k, DataType x)
{
	/*
	 Buoc1:Chen
		 Co 3 TH: 1, neu list rong hoac k <= 0 -> chen dau;
				  2, neu k>= n                 -> chen cuoi;
				  3, sau do thi bat dau chen;
	 Buoc2:
		 so luong phan tu tang len 1;
	 */
	Node *temp = creatNode(x);
	if (isEmpty(list) || k <= 0) addHead(list, x);
	else if (k >= n) addTail(list, x);
	else
	{
		//tim den vi tri node tu k - 1;
		Node *i = list.head;
		int dem = 0;
		while (i != NULL)
		{
			if (dem == k - 1) break;
			dem++;
			i = i->next;
		}
		temp->next = i->next;
		i->next->prev = temp;
		temp->prev = i;
		i->next = temp;
		n++;
	}
}

void sap_xep_Diem_TB(List &list, DataType x)
{
	/*
	1, Chen vao dau;
	2, Chen vao cuoi;
	3, Chen vao 1 vi tri bat ki ;
	*/
	//Tim ra vi tri can chen
	Node *i = list.head;
	int count = 0;
	while (i != NULL)
	{
		if (i->data.DiemTB >= x.DiemTB) break;
		if (i->next == NULL)
		{
			count++;
			break;
		}
		if (i->data.DiemTB <= x.DiemTB && x.DiemTB <= i->next->data.DiemTB)
		{
			count++;
			break;
		}
		count++;
		i = i->next;
	}
	insertInList(list, count, x);
}
void sap_xep_MSV(List &list, DataType x)
{
	/*
	1, Chen vao dau;
	2, Chen vao cuoi;
	3, Chen vao 1 vi tri bat ki ;
	*/
	//Tim ra vi tri can chen
	Node *i = list.head;
	int count = 0;
	while (i != NULL)
	{
		if (strcmp(x.MaSinhVien, i->data.MaSinhVien)<0) break;
		if (i->next == NULL)
		{
			count++;
			break;
		}
		if (strcmp(x.MaSinhVien,i->data.MaSinhVien)>0 && strcmp(x.MaSinhVien,i->next->data.MaSinhVien)<0)
		{
			count++;
			break;
		}
		count++;
		i = i->next;
	}
	insertInList(list, count, x);
}
void DelHead(List &list)
{
	if (isEmpty(list)) cout << "Empty list!" << endl;
	else if (list.head->next == NULL)
	{
		Init(list);
	}
	else
	{
		Node *temp = list.head;
		temp->next->prev = NULL;
		list.head = temp->next;
		delete temp;
		n--;
		stt--;
		i -= 2;

	}
}

void DelTail(List &list)
{
	if (isEmpty(list)) cout << "Empty list!" << endl;
	else if (list.head->next == NULL)
	{
		Init(list);
	}
	else
	{
		Node *temp = list.tail;
		temp->prev->next = NULL;
		list.tail = temp->prev;
		delete temp;
		stt--;
		i -= 2;
		n--;

	}
}

void DelInList(List &list, int k)
{
	if (isEmpty(list)) cout << "Empty list!" << endl;
	else if (k < 0 || k > n) cout << "Vi tri xoa khong hop le!" << endl;
	else if (list.head->next == NULL)
	{
		Init(list);
	}
	else if (k == 0) DelHead(list);
	else if (k == stt - 1) DelTail(list);
	else
	{
		Node *sv = list.head;

		int dem = 0;
		while (sv != NULL)
		{
			if (dem == k - 1) break;
			dem++;
			sv = sv->next;
		}
		Node *temp = sv->next;
		sv->next = temp->next;
		temp->next->prev = sv;
		delete temp;
		n--;
		stt--;
		i -= 2;
		gotoxy(0, 0); cout << "i = " << i << "stt" << stt;
	}
 }
void input(List &list)
{
	ifstream in;
	in.open("Text.dat");
	//if (in.fail()) return -1;
	while (!in.eof())
	{
		DataType x;
		in >> x.MaLop;
		in >> x.MaSinhVien;
		in.ignore();
		getline(in, x.HoTen);
		in >> x.NgS;
		in >> x.TS;
		in >> x.NS;
		in >> x.DiemTB;
		addHead(list, x);
	}
	
	in.close();

}

void output(const char *fileName, List list)
{
	ofstream out;
	out.open(fileName);
	Node *i = list.head;
	if (i == NULL) cout << "Unsuccessful!" << endl;
	else
	{
		while (i != NULL)
		{
			out << i->data.MaLop <<"\n"<< i->data.MaSinhVien <<"\n"<< i->data.HoTen <<"\n"<< i->data.NgS <<"\n"<< i->data.TS <<"\n"<< i->data.NS <<"\n"<< i->data.DiemTB;
			
			i = i->next;
		}
		cout << endl;
	}
	out.close();
}
//void DelDuplicate(List &list) {
//	if (isEmpty(list)) cout << "Empty list!" << endl;
//	else if (list.head->next == NULL)
//	{
//		cout << "There is only 1 element." << endl;
//	}
//	else
//	{
//		Node *i = list.head;
//		int k = 1;
//		while (i->next != NULL) {
//			if (i->data == i->next->data)
//			{
//				Node *temp = i->next;
//				i->next = temp->next;
//				temp->next->prev = i;
//				delete temp;
//				n--;
//			}
//			else
//			{
//				k++;
//				i = i->next;
//			}
//		}
//		cout << "Success!" << endl;
//
//	}
//}

void menu_chinh(int choice) //menu chuong trinh chinh
{
	setColor(63);
	string menu[7] = { "     ***** MENU *****      ",
					"1. Cap nhat ho so             ",
					"2. Xem danh sach              ",
					"3. Sap xep                    ",
					"4. Tim kiem                   ",
					"5. Thong ke                   ",
					"6. Thoat                      " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 7; i++)
	{
		gotoxy(3, 5 + i);
		if(i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void menu_M1(int choice)
{
	
	setColor(63);
	string menu[4] = { "     ** CAP NHAT HO SO **     ",
					"1. Them sinh vien             ",
					"2. Xoa sinh vien              ",
					"3. Quay lai                   " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 4; i++)
	{
		gotoxy(3, 5 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void menu_M3_2(int choice) //menu chon thuat toan sap xep
{
	setColor(63);
	string menu[6] = { "    CHON THUAT TOAN SAP XEP   ",
					"1. Sap xep chon               ",
					"2. Sap xep chen               ",
					"3. Sap xep noi bot            ",
					"4. Sap xep nhanh              ",
					"5. Quay lai                   " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 6; i++)
	{
		gotoxy(3, 5 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void menu_M3_1(int choice) //menu chon khoa sap xep
{
	setColor(63);
	string menu[6] = { "       CHON KHOA SAP XEP      ",
					"1. Sap xep theo ma sinh vien  ",
					"2. Sap xep theo ho ten        ",
					"3. Sap xep theo ngay sinh     ",
					"4. Sap xep theo diem TB       ",
					"5. Quay lai                   " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 6; i++)
	{
		gotoxy(3, 5 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void menu_M4_2(int choice)
{
	setColor(63);
	string menu[4] = { "   CHON THUAT TOAN TIM KIEM   ",
					"1. Tim kiem tuan tu           ",
					"2. Tim kiem nhi phan          ",
					"3. Quay lai                   " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 4; i++)
	{
		gotoxy(3, 5 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void menu_M4_1(int choice)
{
	setColor(63);
	string menu[7] = { "   CHON THUAT TOAN TIM KIEM   ",
					"1. Tim kiem theo ma lop       ",
					"2. Tim kiem theo ma sinh vien ",
		            "3. Tim kiem theo ho ten       ",
		            "4. Tim kiem theo ngay sinh    ",
		            "5. Tim kiem theo diem TB      ",
					"6. Quay lai                   " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 7; i++)
	{
		gotoxy(3, 5 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void background_DS(List list)
{
	/*
	In ra các hàng các cột Danh Sách 
	In ra display 
	*/
	char g1 = 218, ngang = 196, top = 194, g2 = 191;
	char xtt = 195, doc = 179, xcong = 197, xtp = 180;
	char g4 = 192, bot = 193, g3 = 217;

	char s[] = "DANH SACH SINH VIEN";
	setColor(240);
	int x = 35, y = 3, i = 0;
	
	int l_hoten = cRong - sizemenu - l_stt - l_malop - l_masv - l_ngaysinh - l_diemtb - 7;
	int width = l_stt + l_malop + l_masv + l_hoten + l_ngaysinh + l_diemtb + 5;
	// in tieu de
	gotoxy(x, y + i++);
	cout <<g1 << setfill(ngang)<< setw(width + 1) << g2;
	gotoxy(x, y + i++);
	cout << setfill(' ') << doc << setw(width / 2 + strlen(s) / 2) << s << setw(width - (width / 2 + strlen(s) / 2) + 1) << doc;
	gotoxy(x, y + i++);
	cout << setfill(ngang) << xtt << setw(l_stt + 1) << top << setw(l_malop + 1) << top << setw(l_masv + 1) << top
		<< setw(l_hoten + 1) << top << setw(l_ngaysinh + 1) << top << setw(l_diemtb + 1) << xtp;
	gotoxy(x, y + i++);
	cout << setfill(' ') << setiosflags(ios::left) << doc << setw(l_stt) << " STT" << doc << setw(l_malop) << "  Ma Lop" << doc
		<< setw(l_masv) << "  Ma SV" << doc << setw(l_hoten) << "     Ho Va Ten" << doc << setw(l_ngaysinh) << "   Ngay Sinh" << doc
		<< setw(l_diemtb) << "Diem TB" << doc << resetiosflags(ios::left);
	//in bang
	int n = 0;
	while (n != 10)
	{
		n++;
		gotoxy(x, y + i++);
		cout << setfill(ngang) << xtt << setw(l_stt + 1) << xcong << setw(l_malop + 1) << xcong << setw(l_masv + 1) << xcong << setw(l_hoten + 1) << xcong
			<< setw(l_ngaysinh + 1) << xcong << setw(l_diemtb + 1) << xtp;
		gotoxy(x, y + i++);
		cout << setfill(' ') << doc << setw(l_stt) << " " << doc << setw(l_malop) << " " << doc << setw(l_masv) << " "
			<< doc << setw(l_hoten) << " " << doc << setw(l_ngaysinh) << " " << doc << setw(l_diemtb) << " " << doc;
	}
	// in cuoi
	gotoxy(x, y + i++);
	cout << setfill(ngang) << g4 << setw(l_stt + 1) << bot << setw(l_malop + 1) << bot << setw(l_masv + 1)
		<< bot << setw(l_hoten + 1) << bot << setw(l_ngaysinh + 1) << bot << setw(l_diemtb + 1) << g3;
	display(list);
	
}
void hinh_chu_nhat(int x, int y, int width, int height, int color)
{
	char g1 = 201, ngang = 205, g2 = 187, doc = 186, g3 = 188, g4 = 200;
	setColor(color);
	gotoxy(x, y);
	cout << setfill(ngang) << g1 << setw(width - 1) << g2;
	for (int i = 1; i < height; i++)
	{
		gotoxy(x , y+ i); cout << setfill(' ') << doc << setw(width - 1) << doc;
	}
	gotoxy(x, y + height); cout << setfill(ngang) << g4 << setw(width - 1) << g3; 

}
void background_Menu()
{
	/*
	
	In ra khung hình chữ nhật menu()
	*/
	gotoxy(0, 3); 
	hinh_chu_nhat(0, 3, sizemenu,25 , 63);
}
void background(List list)
{
	/*
	In ra menu();
	In ra Danh sách ();
	*/
	char s[] = "QUAN LY SINH VIEN";
	string tt[2] = { "Chao: NGUYEN HUU TIEN ","CNTT" };
	SetSizeConsole();
	gotoxy(0, 0); setColor(47);
	cout << setw(cRong) << setfill(' ') << " ";
	gotoxy(0, 1); cout << setw(cRong / 2 + strlen(s)/ 2) << setfill(' ') << s << setw(cRong - (cRong / 2 + strlen(s) / 2)) << setfill(' ') << " ";
	cout << tt[0] << setw(cRong - tt[0].length() - tt[1].length()) << setfill(' ') << tt[1]<< setw(tt[0].length() + tt[1].length())<<setfill(' ')<<" ";
	background_Menu();
	background_DS(list);
	gotoxy(0, 0);
}
void khung_thong_ke()
{
	char gtt = 218, ngang = 196, top = 194, gpt = 191;
	char xtt = 195, xt = 179, xcong = 197, xtp = 180;
	char gtd = 192, bot = 193, gpd = 217;

	char s[] = "THONG KE KET QUA HOC TAP";
	setColor(240);
	int x = 35, y = 3, i = 0;
	int l_stt = 5, l_tongsv = 10, l_gioi = 10, l_kha = 10, l_trungbinh = 10, l_yeu = 10;
	int l_malop = cRong - sizemenu - l_stt - l_tongsv - l_gioi - l_kha - l_trungbinh - l_yeu - 8;
	int width = l_malop + l_stt + l_tongsv + l_gioi + l_kha + l_trungbinh + l_yeu + 6;
	// in tieu de
	gotoxy(x, y + i++);
	cout << setfill(ngang) << gtt << setw(width + 1) << gpt;
	gotoxy(x, y + i++);
	cout << setfill(' ') << xt << setw(width / 2 + strlen(s) / 2) << s << setw(width - (width / 2 + strlen(s) / 2) + 1) << xt;
	gotoxy(x, y + i++);
	cout << setfill(ngang) << xtt << setw(l_stt + 1) << top << setw(l_malop + 1) << top << setw(l_tongsv + 1) << top << setw(l_gioi + 1) << top
		<< setw(l_kha + 1) << top << setw(l_trungbinh + 1) << top << setw(l_yeu + 1) << xtp;
	gotoxy(x, y + i++);
	cout << setfill(' ') << setiosflags(ios::left) << xt << setw(l_stt) << " STT" << xt << setw(l_malop) << "    Ma Lop" << xt << setw(l_tongsv) << "  Tong SV" << xt
		<< setw(l_gioi) << "   Gioi" << xt << setw(l_kha) << "   Kha" << xt << setw(l_trungbinh) << "Trung Binh" << xt
		<< setw(l_yeu) << "   Yeu" << xt << resetiosflags(ios::left);
	int n = 0;
	while (n != 10) {
		n++;
		gotoxy(x, y + i++);
		cout << setfill(ngang) << xtt << setw(l_stt + 1) << xcong << setw(l_malop + 1) << xcong << setw(l_tongsv + 1) << xcong << setw(l_gioi + 1) << xcong << setw(l_kha + 1) << xcong
			<< setw(l_trungbinh + 1) << xcong << setw(l_yeu + 1) << xtp;
		gotoxy(x, y + i++);
		cout << setfill(' ') << xt << setw(l_stt) << " " << xt << setw(l_malop) << " " << xt << setw(l_tongsv) << " " << xt << setw(l_gioi) << " "
			<< xt << setw(l_kha) << " " << xt << setw(l_trungbinh) << " " << xt << setw(l_yeu) << " " << xt;
	}
	// in cuoi
	gotoxy(x, y + i++);
	cout << setfill(ngang) << gtd << setw(l_stt + 1) << bot << setw(l_malop + 1) << bot << setw(l_tongsv + 1) << bot << setw(l_gioi + 1)
		<< bot << setw(l_kha + 1) << bot << setw(l_trungbinh + 1) << bot << setw(l_yeu + 1) << gpd;
	gotoxy(0, 0);
}
void display(List list)
{
	
	int stt1 = 1;
	int i = 0;
	Node *s = list.tail;
	while (s != NULL)
	{
		gotoxy(38, 8 + i); cout << stt1;
		gotoxy(42, 8 + i); cout << s->data.MaLop;
		gotoxy(53, 8 + i); cout << s->data.MaSinhVien;
		gotoxy(65, 8 + i); cout << s->data.HoTen;
		gotoxy(99, 8 + i); cout << "/  /";
		gotoxy(97, 8 + i); cout << s->data.NgS;
		gotoxy(100, 8 + i); cout << s->data.TS;
		gotoxy(103, 8 + i); cout << s->data.NS;
		gotoxy(111, 8 + i); cout << s->data.DiemTB;
		s = s->prev;
		i += 2;
		stt1++;
	}
	gotoxy(0, 0);
}
int phim_enter_esc()
{	//enter return true esc return false
	int c;
	while (1)
	{
		c = _getch();
		if (c == 13) return 13;
		if (c == 27) return 27;
	}
}
int phim_di_chuyen(int c, int choice, int line)
{
	if (c == 224)
	{
		c = _getch();
		if (c == 80)
		{
			if (choice == line) choice = 1;
			else choice++;
		}
		if (c == 72)
		{
			if (choice == 1) choice = line;
			else choice--;
		}
		
	}
	return choice;
}
int menu_chinh_thao_tac(int last_line)
{
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();

		if (c == 224)
		{
			line = phim_di_chuyen(c, line, last_line);

			menu_chinh(line);
		}
		if (c == 13)
		{
			return line;
		}
	}
}

bool set_ma_lop(char *s)
{
	/*48  -> 57   la ca so 1->9*/

	int lenght;
	lenght = strlen(s);
	if (!((int)s[lenght - 1] <= 57 && (int)s[lenght - 1] >= 48 && (int)s[lenght - 2]<=57 && (int)s[lenght - 2] >= 48))
	{
		return false;
	}
	return true;
}
bool set_NgS(int &n)
{
	if (!(n > 0 && n <= 31)) return false;
	return true;
}
bool set_TS(int &n, int &ngay_sinh)
{
	if (n == 2 && ngay_sinh >= 30) return false;
	if (!(n > 0 && n <13)) return false;
	return true;
}
bool set_NS(int &n)
{
	if (n > 2000 || n < 1000) return false;
	return true;
}
bool set_ma_SV(char* s, List list)
{
	int lenght;
	lenght = strlen(s);
	if (lenght != 8) return false;
	else 
	{
		for (int i = 0; i < lenght; i++)
		{
			if (!((int)s[i] <= 57 && (int)s[i] >= 48))
			{
				return false;
			}
		}
	}
	Node* x = list.head;
	while (x != NULL)
	{
		
		if (strcmp(s, x->data.MaSinhVien) == 0) 
		{
			gotoxy(0, 0); cout << "Trung MSV";
			return false;
		}
		x = x->next;
	}
	
	return true;

}
bool set_diem(float &d)
{
	if (!(d >= 0 && d <= 10)) return false;
	return true;
}
void xoa_khoang_thua_dau_va_cuoi(string &str)
{
	// Bước 1: Xóa hết tất cả các kí tự khoảng trắng thừa ở đầu chuỗi
	// cho vòng lặp while lặp cho đến khi nào kiểm tra kí tự đầu tiên - vị trí 0 không phải là khoảng trắng thì dừng
	while (str[0] == ' ')
	{
		str.erase(str.begin() + 0); // xóa kí tự tại vị trí 0
	}


	// Bước 2: Xóa hết tất cả các kí tự khoảng trắng thừa ở cuối chuỗi
	while (str[str.length() - 1] == ' ')
	{
		str.erase(str.begin() + str.length() - 1); // xóa kí tự tại vị trí cuối của chuỗi
	}
}

// hàm xóa khoảng trắng thừa ở giữa các từ
void xoa_khoang_trang(string &str)
{
	for (int i = 0; i < str.length(); i++)
	{
		// nếu 2 kí tự liên tiếp nhau mà là khoảng trắng ==> xóa đi 1 kí tự
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			str.erase(str.begin() + i);
			i--;
		}
	}
}

// hàm viết hoa kí tự đầu của mỗi từ
void in_hoa_ki_tu_dau_moi_tu(string &str)
{
	xoa_khoang_thua_dau_va_cuoi(str);
	xoa_khoang_trang(str);
	// Bước 1: chuyển chuỗi str về chuỗi in thường
	strlwr((char *)str.c_str()); // hàm chuyển chuỗi str về chuỗi in thường
	// Bước 2: viết hoa kí tự đầu của mỗi từ
	if (str[0] != ' ')
	{
		if (str[0] >= 97 && str[0] <= 122)
		{
			str[0] -= 32;
		}

	}
	// kí tự tại vị trí i là khoảng trắng, i + i khác khoảng trắng thì kí tự tại vị trí i + 1 chính là kí tự đầu tiên của mỗi từ
	for (int i = 0; i < str.length() - 1; i++)
	{
		if (str[i] == ' ' && str[i + 1] != ' ')
		{
			// A: 65
			// B: 66
			// Z: 90
			// a: 97
			// b: 98
			// c: 99
			// z: 122
			if (str[i + 1] >= 97 && str[i + 1] <= 122)
			{
				// - 32 là chuyển kí tự in thường về in hoa
				str[i + 1] -= 32; // <=> str[i + 1] = str[i + 1] - 32;
			}
		}
	}
}

void chon_M1_them_SV(List &list)
{
	/*
	Cho phép nhập các thông tin sinh viên
	có : i += 2; và stt ++ ;
	*/
	gotoxy(0, 0); cout << "i = " << i << "stt" << stt;
	menu_M1(1);
	int c;
	while (1)
	{
		DataType x;
		
		setColor(240);
		gotoxy(38, 8 + i); cout << stt+1;
		gotoxy(42, 8 + i);
		cin >> x.MaLop;
		while (!set_ma_lop(x.MaLop))
		{
			gotoxy(42, 8 +i);
			cout << setw(l_malop) << setfill(' ') << " "; gotoxy(42, 8 + i);
			cin >> x.MaLop;
		}

		gotoxy(53, 8+i);
		cin >> x.MaSinhVien;
		while (!set_ma_SV(x.MaSinhVien, list))
		{
			gotoxy(53, 8+i);
			cout << setw(l_masv) << setfill(' ') << " "; gotoxy(53, 8 + i);
			cin >> x.MaSinhVien;
		}
		cin.ignore(); gotoxy(65, 8+i);
		getline(cin, x.HoTen); 
		in_hoa_ki_tu_dau_moi_tu(x.HoTen);
		fflush(stdin);
		gotoxy(99, 8+i); cout << "/  /";
		gotoxy(97, 8+i);
		cin >> x.NgS;
		while (!set_NgS(x.NgS))
		{
			gotoxy(97, 8+i);
			cout << setw(2) << setfill(' ') << " "; gotoxy(97, 8+i);
			cin >> x.NgS;
		}
		gotoxy(97, 10); 
		cin.clear();

		gotoxy(100, 8+i);
		cin >> x.TS;
		while (!set_TS(x.TS, x.NgS))
		{
			gotoxy(100, 8+i);
			cout << setw(2) << setfill(' ') << " "; gotoxy(100, 8+i);
			cin >> x.TS;
		}
		cin.clear();
		gotoxy(103, 8+i);
		cin >> x.NS;
		while (!set_NS(x.NS))
		{
			gotoxy(103, 8+i);
			cout << setw(4) << setfill(' ') << " "; gotoxy(103, 8+i);
			cin >> x.NS;
		}
		cin.clear();
		gotoxy(111, 8+i); cin >> x.DiemTB;
		while (!set_diem(x.DiemTB))
		{
			gotoxy(111, 8+i);
			cout << setw(4) << setfill(' ') << " "; gotoxy(111, 8+i);
			cin >> x.DiemTB;
		}
		cin.clear();
		
		c = phim_enter_esc();
		if (c == 13)
		{
			addHead(list, x);
		}
		if (c == 27)
		{
			addHead(list, x);
			display(list);
			break;
		}

	}
	
}
void DS_M1_xoa_SV(List &list, int choice)
{
	setColor(240);
	Node *n = list.head;
	int stt = 1;
	int i = 0;
	while (n != NULL)
	{
		if (stt != choice)
		{
			gotoxy(38, 8 + i); cout << stt;
			gotoxy(42, 8 + i); cout << n->data.MaLop;
			gotoxy(53, 8 + i); cout << n->data.MaSinhVien;
			gotoxy(65, 8 + i); cout << n->data.HoTen;
			gotoxy(99, 8 + i); cout << "/  /";
			gotoxy(97, 8 + i); cout << n->data.NgS;
			gotoxy(100, 8 + i); cout << n->data.TS;
			gotoxy(103, 8 + i); cout << n->data.NS;
			gotoxy(111, 8 + i); cout << n->data.DiemTB;
		}
		else
		{
			setColor(241);
			gotoxy(38, 8 + i); cout << stt;
			gotoxy(42, 8 + i); cout << n->data.MaLop;
			gotoxy(53, 8 + i); cout << n->data.MaSinhVien;
			gotoxy(65, 8 + i); cout << n->data.HoTen;
			gotoxy(99, 8 + i); cout << "/  /";
			gotoxy(97, 8 + i); cout << n->data.NgS;
			gotoxy(100, 8 + i); cout << n->data.TS;
			gotoxy(103, 8 + i); cout << n->data.NS;
			gotoxy(111, 8 + i); cout << n->data.DiemTB;
			setColor(240);
		}
		stt++;
		i += 2;
		n = n->next;
	}
	
	gotoxy(0, 0);
}
void chon_M1_xoa_SV(List &list)
{
	background_DS(list);
	DS_M1_xoa_SV(list, 1);
	int c;
	loop:int line = 1;
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			
			line = phim_di_chuyen(c, line, stt);
			DS_M1_xoa_SV(list, line);
		}
		if (c == 13)
		{
			DelInList(list, line-1);
			background_DS(list);
			goto loop;
		}
		if (c == 27)
		{
			background_DS(list);
			break;
		}
		gotoxy(0, 0);
		cout << "line" << line;
	}
}
void chon_M1(List &list)
{
	background(list);
	menu_M1(1);
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			line = phim_di_chuyen(c, line, 3);
			menu_M1(line);
		}
		if (c == 13)
		{
			if (line == 1) chon_M1_them_SV(list);
			if (line == 2) chon_M1_xoa_SV(list);
			if (line == 3) break;
		}
		
	}
	fflush(stdin);
}

void chon_M3_1_4(List &list)
{
	List l1;
	Init(l1);
	int temp = stt;
	int temp_i = i;
	Node *l = list.head;
	while (l != NULL)
	{
		sap_xep_Diem_TB(l1, l->data);
		l = l->next;
	}
	list = l1;
	i = temp_i;
	stt = temp;
}
void chon_M3_1_1(List &list)
{
	List l1;
	Init(l1);
	int temp = stt;
	int temp_i = i;
	Node *l = list.head;
	while (l != NULL)
	{
		sap_xep_MSV(l1, l->data);
		l = l->next;
	}
	list = l1;
	i = temp_i;
	stt = temp;
}


void chon_M3_2(List &list, int choice)
{
	background(list);
	menu_M3_2(1);
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();

		if (c == 224)
		{
			line = phim_di_chuyen(c, line, 5);
			menu_M3_2(line);
		}
		if (c == 13)
		{

			if (line == 5)
			{
				break;
			}
		}
	}
}
void chon_M3_1(List &list)
{
	loop: background(list);
	menu_M3_1(1);
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();

		if (c == 224)
		{
			line = phim_di_chuyen(c, line, 5);
			menu_M3_1(line);
		}
		if (c == 13)
		{
			if (line == 1)
			{
				chon_M3_1_1(list); goto loop;
			}
			if (line == 4)
			{
				chon_M3_1_4(list); goto loop;
			}
			if (line == 5) break;
			//chon_M3_2(list, line); goto loop;
			
		}
	}

}
void chon_M4_2(List &list, int choice)
{
	background(list);
	menu_M4_2(1);
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();

		if (c == 224)
		{
			line = phim_di_chuyen(c, line, 3);
			menu_M4_2(line);
		}
		if (c == 13)
		{

			if (line == 3)
			{
				break;
			}
		}
	}
}
void chon_M4_1(List list)
{
	background(list);
	loop : menu_M4_1(1);
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();

		if (c == 224)
		{
			line = phim_di_chuyen(c, line, 6);
			menu_M4_1(line);
		}
		if (c == 13)
		{
			if (line == 6)  break;
			chon_M4_2(list, line); goto loop;
		}
	}
}
void chon_M5(List list)
{
	background(list);
    menu_chinh(1);
	khung_thong_ke();
	cin.get();
}
void chon_M(List &list)
{
	loop: background(list);
	menu_chinh(1);
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			line = phim_di_chuyen(c, line, 6);
			menu_chinh(line);
		}
		if (c == 13)
		{
			if (line == 1)
			{
				chon_M1(list);  goto loop;
			}
			if (line == 3)
			{
				chon_M3_1(list); goto loop;
			}
			if (line == 4)
			{
				chon_M4_1(list); goto loop;
			}
			if (line == 5)
			{
				chon_M5(list); goto loop;
			}
			if (line == 6) break;
		}
	}
}

// In general, ignore this file, but keep it around if you are using pre-compiled headers.
