#include <iostream>
#include <stdio.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <Windows.h>
#include <mylib.h>
#include <time.h>

using namespace std;

const int MAXNV = 500;
const int MAXVT = 500;
const int MAXTOP10 = 10;
const int sodong = 6;
const int sodong1 = 5;
const int sodong3 = 5;
const int cot = 2;
const int dong = 6;
const int UP = 72;
const int DOWN = 80;
const int SPACE = 32;
const int ENTER = 13;
const int ESC = 27;
const int BACKSPACE = 8;
const int F1 = 59;
const int F2 = 60;
const int F3 = 61;
const int F4 = 62;
const int LEFT = 75;
const int RIGHT = 77;
const int TAB = 9;

/**********************************************KHAI BAO CAU TRUC**************************************************************/
struct Date
{
	int Ngay, Thang, Nam;
};

//---cthoadon--- danh sach lien ket don
struct CTHoaDon
{
	char MaVT[10];
	int SoLuong;
	int DonGia;
	int VAT;
};
struct NodeCTHD
{
	CTHoaDon cthd;
	NodeCTHD *pNext;
};
typedef struct NodeCTHD* NODECTHD;

//---hoadon--- danh sach lien ket don
struct HoaDon
{
	char SoHD[20];
	Date NgayLap;
	char Loai;// N:phieu nhap   X:phieu xuat
	NODECTHD nodecthd;
};
struct NodeHD
{
	HoaDon hd;
	NodeHD *pNext;
};
typedef struct NodeHD* NODEHD;

//---vattu--- cay nhi phan tim kiem
struct VatTu
{
	char MaVT[10];
	char TenVT[50];
	char DVT[10];// don vi tinh
	int SLT;// so luong ton
};
struct ListVatTu
{
	VatTu vt;
	ListVatTu *pLeft, *pRight;
};
typedef struct ListVatTu* LISTVT;

//---nhanvien--- ds tuyen tinh la 1 mang con tro
struct NhanVien
{
	char MaNV[10];
	char Ho[20];
	char Ten[10];
	int Phai;
	NODEHD nodehd;
};
struct ListNhanVien
{
	int n;
	NhanVien *dsnv[MAXNV];
};
typedef struct ListNhanVien LISTNV;

/***************************************************GIAO DIEN******************************************************/
void Normal()
{
	SetColor(15);
	SetBGColor(0);
}
void HighLight()
{
	SetColor(15);
	SetBGColor(28);
}
int GetKey()
{	
	char key;
	key = getch();
	if(key == -32 || key == 0)
	return -getch();
	else return key;
}
char MenuCha[sodong][50] = {  "1. Vat tu",
							  "2. In danh sach vat tu ton kho",
							  "3. Nhan vien",
							  "4. In danh sach nhan vien ten ho",
							  "5. Hoa don",
							  "6. Thong ke hoa don trong khoang tg"};

char Menu1[sodong1][50] = {  "1. Them vat tu",
							 "2. Xoa vat tu",
							 "3. Sua vat tu",
							 "4. Xem danh sach vat tu",
							 "5. Thoat" };
							
char Menu3[sodong3][50] = {	 "1. Them nhan vien",
							 "2. Xoa nhan vien",
							 "3. Sua nhan vien",
							 "4. Xem danh sach nhan vien",
							 "5. Thoat" };
int DemDongMenu(char td [sodong][50])
{
	int i;
	for(i = 0; td[i][0] != NULL; ++i);
	return i;
};	
int MenuDong(char td [][50], int sodong)
{
	td[sodong][50];
	Normal();
	system("cls");
	SetBGColor(28);
	gotoxy(2, 4);		cout << "*******QUAN LY NHAP XUAT VAT TU********";
	gotoxy(2, 13);		cout << "UP: Len     DOWN: Xuong     ENTER: Chon";
	Normal();
	int chon =0;
	int i;
	sodong = DemDongMenu(td);
	for (i = 0; i < sodong ; i++)
	{
		gotoxy(cot, dong + i);		cout << td[i];
	}
	HighLight();
	gotoxy(cot, dong + chon);		cout << td[chon];
	char kytu;
	do
	{
		kytu = getch();
		if (kytu == 0) kytu = getch();
		switch (kytu)
		{
			case UP:
				if (chon + 1 > 1)
				{
					Normal();
					gotoxy(cot, dong + chon);		cout << td[chon];
					chon --;
					HighLight();
					gotoxy(cot, dong + chon);		cout << td[chon];
				}
				break;
			case DOWN:
				if (chon + 1 < sodong)
				{
					Normal();
					gotoxy(cot, dong + chon);		cout << td[chon];
					chon ++;
					HighLight();
					gotoxy(cot, dong + chon);		cout << td[chon];
				}
				break;
			case ENTER:
				return chon + 1;
			case ESC:
				system("cls");
				return sodong;
		} 
	}while(true);
};
void GiaoDien_InDSVT (int y, int n, string c)
{
	for (int i = 8; i <= 110; i++)
	{
		gotoxy(i, 2 + y);			cout << char(196);
		gotoxy(i, n + 1 + y);		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(7, 2 + i + y);		cout << char(179);
		gotoxy(21, 2 + i + y);		cout << char(179);
		gotoxy(81, 2 + i + y);		cout << char(179);
		gotoxy(95, 2 + i + y);		cout << char(179);
		gotoxy(110, 2 + i + y);		cout << char(179);
	}
	gotoxy(42, y);					cout << c;
	gotoxy(10, 2 + y);				cout << "Ma Vat Tu";
	gotoxy(45, 2 + y);				cout << "Ten Vat Tu";
	gotoxy(83, 2 + y);				cout << "Don vi tinh";
	gotoxy(97, 2 + y);				cout << "So Luong Ton";
}
//in danh sach vat tu trong cthd
void GiaoDien_InDSVT_CTHD (int y, int n, string c)
{
	for (int i = 60; i <= 123; i++)
	{
		gotoxy(i, 2 + y);			cout << char(196);
		gotoxy(i, n + 1 + y);		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(60, 2 + i + y);		cout << char(179);
		gotoxy(72, 2 + i + y);		cout << char(179);
		gotoxy(96, 2 + i + y);		cout << char(179);
		gotoxy(110, 2 + i + y);		cout << char(179);
		gotoxy(123, 2 + i + y);		cout << char(179);
	}
	gotoxy(70, 0 + y);				cout << c;
	gotoxy(62, 2 + y);				cout << "Ma vat tu";
	gotoxy(80, 2 + y);				cout << "Ten vat tu";
	gotoxy(102, 2 + y);				cout << "DVT";
	gotoxy(115, 2 + y);				cout << "SLT";
}
void GiaoDien_InDSNV(int y, int n, string c)
{
	for (int i = 8; i <= 98; i++)
	{
		gotoxy(i, 2 + y);			cout << char(196);
		gotoxy(i, n + 1 + y);		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(8, 2 + i + y);		cout << char(179);
		gotoxy(28, 2 + i + y);		cout << char(179);
		gotoxy(58, 2 + i + y);		cout << char(179);
		gotoxy(78, 2 + i + y);		cout << char(179);
		gotoxy(98, 2 + i + y);		cout << char(179);
	}
	gotoxy(38, 0 + y);				cout << c;
	gotoxy(13, 2 + y);				cout << "Ma Nhan Vien";
	gotoxy(43, 2 + y);				cout << "Ho";
	gotoxy(67, 2 + y);				cout << "Ten";
	gotoxy(86, 2 + y);				cout << "Phai";
}
//in danh sach nhan vien de xem trong hoa don
void GiaoDien_InDSNV_HD(int y, int n, string c)
{
	for (int i = 18; i <= 108; i++)
	{
		gotoxy(i, 2 + y);			cout << char(196);
		gotoxy(i, n + 1 + y);		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(18, 2 + i + y);		cout << char(179);
		gotoxy(38, 2 + i + y);		cout << char(179);
		gotoxy(68, 2 + i + y);		cout << char(179);
		gotoxy(88, 2 + i + y);		cout << char(179);
		gotoxy(108, 2 + i + y);		cout << char(179);
	}
	gotoxy(47, 0 + y);				cout << c;
	gotoxy(23, 2 + y);				cout << "Ma Nhan Vien";
	gotoxy(53, 2 + y);				cout << "Ho";
	gotoxy(77, 2 + y);				cout << "Ten";
	gotoxy(96, 2 + y);				cout << "Phai";
}
void GiaoDien_InHD(int y, int n, string c)
{
	for (int i = 6; i <= 56; i++)
	{
		gotoxy(i, 2 + y);			cout << char(196);
		gotoxy(i, n + 1 + y);		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(6, 2 + i + y);		cout << char(179);
		gotoxy(30, 2 + i + y);		cout << char(179);
		gotoxy(47, 2 + i + y);		cout << char(179);
		gotoxy(56, 2 + i + y);		cout << char(179);
	}
	gotoxy(17, 0 + y);				cout << c;
	gotoxy(14, 2 + y);				cout << "So Hoa Don";
	gotoxy(35, 2 + y);				cout << "Ngay Lap";
	gotoxy(50, 2 + y);				cout << "Loai";
}
void GiaoDien_LapHD(int y, int n, string c)
{
	for (int i = 6; i <= 56; i++)
	{
		gotoxy(i, 2 + y);			cout << char(196);
		gotoxy(i, n + 1 + y);		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(6, 2 + i + y);		cout << char(179);
		gotoxy(30, 2 + i + y);		cout << char(179);
		gotoxy(47, 2 + i + y);		cout << char(179);
		gotoxy(56, 2 + i + y);		cout << char(179);
	}
	gotoxy(20, 0 + y);				cout << c;
	gotoxy(14, 2 + y);				cout << "So Hoa Don";
	gotoxy(35, 2 + y);				cout << "Ngay Lap";
	gotoxy(50, 2 + y);				cout << "Loai";
}
void GiaoDien_LapCTHD(int y, int n, string c)
{
	for (int i = 60; i <= 123; i++)
	{
		gotoxy(i, 2 + y);			cout << char(196);
		gotoxy(i, n + 1 + y);		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(60, 2 + i + y);		cout << char(179);
		gotoxy(83, 2 + i + y);		cout << char(179);
		gotoxy(96, 2 + i + y);		cout << char(179);
		gotoxy(110, 2 + i + y);		cout << char(179);
		gotoxy(123, 2 + i + y);		cout << char(179);
	}
	gotoxy(70, 0 + y);				cout << c;
	gotoxy(68, 2 + y);				cout << "Ma vat tu";
	gotoxy(86, 2 + y);				cout << "So luong";
	gotoxy(100, 2 + y);				cout << "Don gia";
	gotoxy(115, 2 + y);				cout << "%VAT";
}
void GiaoDien_ThongKeHD()
{
	gotoxy(30, 0);					cout << "------BANG THONG KE CAC HOA DON TRONG KHOANG THOI GIAN-----";
	gotoxy(30, 2);					cout << "Tu ngay : ";
	gotoxy(62, 2);					cout << "Den ngay : ";
	for (int i = 8; i <= 120; i++)
	{
		gotoxy(i, 5);				cout << char(196);
		gotoxy(i, 42);				cout << char(196);
	}
	for (int i = 0; i < 38; i++)
	{
		gotoxy(8, 5 + i);			cout << char(179);
		gotoxy(27, 5 + i);			cout << char(179);
		gotoxy(51, 5 + i);			cout << char(179);
		gotoxy(62, 5 + i);			cout << char(179);
		gotoxy(100, 5 + i);			cout << char(179);
		gotoxy(120, 5 + i);			cout << char(179);
	}
	gotoxy(15, 5);					cout << "So HD";
	gotoxy(35, 5);					cout << "Ngay nhap";
	gotoxy(55, 5);					cout << "Loai";
	gotoxy(77, 5);					cout << "nhan vien";
	gotoxy(106, 5);					cout << "Tri gia";
}
//hien thi thong bao
void ThongBao(string str, int x, int y)
{
	gotoxy(x, y);	cout << str;
	Sleep(2000);
	gotoxy(x, y);
	clreol();
	gotoxy(x, y);
}
//an dau nhay di
void AnDauNhay()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
//hien thi dau nhay
void HienDauNhay()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
//nhap phai nhan vien
int ChiNhap0or1(int& x)
{
	int kq;
	while (true)
	{
		while (!_kbhit())
		{
			int key = GetKey();
			if (key != 224 && key != 0)
			{
				if (key == 48 || key == 49)
				{
					kq = key - 48;
					cout << kq;
					x = kq;
				}
				else if (key == ENTER)
				{
					return x;
				}
				else if (key == BACKSPACE)
				{
					cout << "\b" << " " << "\b";
					x /= 10;
				}
				else if (key == SPACE)
				{
					ThongBao("Khong duoc bo trong !", 9, 5);
					gotoxy(85, 3);
					continue;
				}
			}
			else
			{
				key = GetKey();
			}
		}
	}
	return x;
}
//xu ly nhap loai hoa don
char ChiNhapNorX(char& temp)
{
	int key;
	while (true)
	{
		while (_kbhit())
		{
			key = GetKey();
			if (key != 224 && temp == '\0')
			{
				if (key == 78 /*N*/ || key == 88 /*X*/)
				{
					cout << (char)key;
					temp += (char)key;
				}
				else if (key == 110 /*n*/ || key == 120/*x*/)
				{
					key -= 32;
					cout << (char)key;
					temp += (char)key;
				}
			}
			else if (key == BACKSPACE && temp != '\0')
			{
				cout << "\b" << " " << "\b";
				temp = '\0';
			}
			else if (key == ENTER)
			{
				return temp;
			}
			else
			{
				key = GetKey();
			}
		}
	}
	return temp;
}
//them chu so
void ThemChu(char* A, char kt, int &vt, int &dem)
{
	int l = strlen(A);
	A[l + 1] = '\0';
	while(l != vt)
	{
		A[l] = A[l - 1];
		l--;
	}
	A[vt] = kt;
	vt++;
	dem++;
}
//xoa chu so
void XoaChu(char* A, int &vt, int &dem)
{
	int l = strlen(A);
	for(int i = vt; i < l; i++)
	{
		A[i] = A[i + 1];
	}
	A[l-1] = '\0';
	vt--;
	dem--;
}
//nhap ma
char *NhapMa(int x, int y, int length, int type, bool Space = false)
{
	//type = 0 => nhap ma + so
	//type = 1 => chi nhap so
	char *text = new char[length];// hung ket qua khi nhap lieu
	text[0] = '\0';//
	int dem = 0, temp = 0;//temp vi tri hien tai trong mang char, dem la vi tri lon nhat cua chuoi nhap vao
	char key;
	gotoxy(x, y);
	while(true)
	{
		key = GetKey();
		if(key == ENTER && strlen(text) > 0)
		{
			return text;
		}
		if(type == 0 && (key >= 65 && key <= 90) && (temp >= 0 && temp < length))
		{
			ThemChu(text, key, temp, dem);
			for(int i = 0; i <= length; i++)
			{
				gotoxy(x + i, y);	cout << " ";
			} 
			gotoxy(x, y);			cout << text;
		}
		if(type == 0 && (key >= 97 && key <= 122) && (temp >= 0 && temp < length))
		{
			key -= 32;
			ThemChu(text, key, temp, dem);
			for(int i = 0; i <= length; i++)
			{
				gotoxy(x + i, y);	cout << " ";
			} 
			gotoxy(x, y);			cout << text;
		}
		if((key >= 48 && key <= 57) && (temp >= 0 && temp < length))
		{
			ThemChu(text, key, temp, dem);
			for(int i = 0; i <= length; i++)
			{
				gotoxy(x + i, y);	cout << " ";
			} 
			gotoxy(x, y);			cout << text;
		}
		if(Space == true && key == SPACE && (temp >= 0 && temp < length))
		{
			ThemChu(text, ' ', temp, dem);
			for(int i = 0; i <= length; i++)
			{
				gotoxy(x + i, y);	cout << " ";
			} 
			gotoxy(x, y);			cout << text;
		}
		if(key == BACKSPACE && temp > 0)
		{
			int pos = temp - 1;
			XoaChu(text, pos , dem);
			for(int i=0; i <= length; i++)
			{
				gotoxy(x + i, y);	cout << " ";
			} 
			gotoxy(x, y);			cout << text;
			temp--;
		}
	}	
}
/***************************************XU LY NGAY***************************************************/
//tra ve thoi gian hien tai
Date Now()
{
	Date date;
	time_t now = time(0);//tra ve so giay tu 1/1/1970 den hien tai
	tm* ltm = localtime(&now);//tra ve thoi gian hien tai
	date.Nam = 1900 + ltm->tm_year;
	date.Thang = 1 + ltm->tm_mon;
	date.Ngay = ltm->tm_mday;
	return date;
}
int NamNhuan(int nam)
{
	return(nam % 4 == 0 && nam % 100 != 0 || nam % 400 == 0) ? 1 : 0;
}
//so ngay cua tung thang
int NgayOfThang[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//kiem tra nhap dung ngay
int CheckNgay(Date date)
{
	int ngay = date.Ngay, thang = date.Thang, nam = date.Nam;
	int check = 0, maxday = 0;
	if (thang > 12) return 1;
	switch (thang)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			maxday = 31;
			break;
		case 4: case 6: case 9: case 11:
			maxday = 30;
			break;
		case 2:
			if (NamNhuan(nam) == 1) maxday = 29;
			else maxday = 28;
			break;
	}
	if (ngay > maxday)	return 1;
	return 0;
};
int TongSoNgay(int Ngay, int Thang, int Nam)
{
	int tong = 0;
	for(int t = 1; t < Thang; t++)
	{
		tong += NgayOfThang[t];
		if(t == 2) tong += NamNhuan(Nam);
	}
	tong += Ngay;
	return tong;
}
int SoSanh2Ngay(Date date1, Date date2)
{
	if(date1.Nam > date2.Nam) return 1;
	if(date1.Nam < date2.Nam) return 2;
	int tongdate1 = TongSoNgay(date1.Ngay, date1.Thang, date1.Nam);
	int tongdate2 = TongSoNgay(date2.Ngay, date2.Thang, date2.Nam);
	if(tongdate1 < tongdate2) return 2;
	else if(tongdate1 > tongdate2) return 1;
}
//****************************************************XU LY FILE***********************************************************
//khoi tao cay nhi phan
void InitTree(LISTVT &root)
{
	root = NULL;
}
//xu ly them vat tu
void InsertVatTu(LISTVT &tree, VatTu vt)
{	
	if(tree == NULL)
	{
		ListVatTu *p = new ListVatTu;
		p->vt = vt;
		p->pLeft = p->pRight = NULL;
		tree = p;//p chinh la node goc <=> vt chinh la node goc
	}
	else
	{
		if(strcmp(tree->vt.MaVT, vt.MaVT) > 0)
		{
			InsertVatTu(tree->pLeft, vt);
		}
		else
		{
			InsertVatTu(tree->pRight, vt);
		}
	}
}
//ghi file vat tu
void GhiFileVatTu_NLR(ListVatTu *root, ofstream &f)//phai co &f de tranh loi ios_base is private
{
	if(root != NULL)
	{
		f << root->vt.MaVT << endl << root->vt.TenVT << endl << root->vt.DVT << endl << root->vt.SLT << endl;
		GhiFileVatTu_NLR(root->pLeft, f);
		GhiFileVatTu_NLR(root->pRight, f);
	}
}
void GhiFileVatTu(ListVatTu *root)
{
	ofstream f;
	f.open("dsvattu.txt", ios_base::out);
	GhiFileVatTu_NLR(root, f);
	f.close();
}
//doc file vat tu
void DocFileVatTu(LISTVT &root)
{
	string data;
	fstream f;
	f.open("dsvattu.txt", ios::in);
	if(f == NULL)
	{
		return;
	}
	while(!f.eof())
	{
		VatTu vt;
		getline(f, data);
		if(data.size() == 0)
		{
			break;
		} 
		strcpy(vt.MaVT, data.c_str());
		getline(f, data);	strcpy(vt.TenVT, data.c_str());
		getline(f, data);	strcpy(vt.DVT, data.c_str());
		f >> vt.SLT;
		f.ignore();
		InsertVatTu(root, vt);
	}
	f.close();
}
//doc file nhan vien
void DocFileNhanVien(LISTNV& ds)
{
	fstream f;
	f.open("dsnhanvien.txt", ios::in);
	if(f == NULL)
	{
		return;
	}
	while(!f.eof())
	{
		NhanVien nv;
		string data;
		getline(f, data);
		if(data.size() == 0) break;
							strcpy(nv.MaNV, data.c_str());
		getline(f, data);	strcpy(nv.Ho, data.c_str());
		getline(f, data);	strcpy(nv.Ten, data.c_str());
		f >> nv.Phai;
		f.ignore();
		//xu ly
		ds.dsnv[ds.n] = new NhanVien;
		strcpy(ds.dsnv[ds.n]->MaNV, nv.MaNV);
		strcpy(ds.dsnv[ds.n]->Ho, nv.Ho);
		strcpy(ds.dsnv[ds.n]->Ten, nv.Ten);	
		ds.dsnv[ds.n]->Phai = nv.Phai;
		ds.n++;
	}
	f.close();
}
//ghi file nhan vien
void GhiFileNhanVien(LISTNV ds)
{
	string data;
	fstream f;
	f.open("dsnhanvien.txt", ios::out);
	for(int i = 0; i < ds.n; i++)
	{
		f << ds.dsnv[i]->MaNV << endl << ds.dsnv[i]->Ho << endl << ds.dsnv[i]->Ten << endl <<ds.dsnv[i]->Phai << endl;
	}
	f.close();
}
//**********************************************XU LY VAT TU**********************************************************
//tim kiem ma vat tu neu trung khi nhap vat tu
ListVatTu* TimKiemMaVT (LISTVT tree, VatTu vt)
{
	if (tree != NULL)
	{
		if (strcmp(tree->vt.MaVT, vt.MaVT) == 0)
		{
			ListVatTu* p = tree;
			return p;
		}
		else if (strcmp(tree->vt.MaVT, vt.MaVT) > 0)
		{
			return TimKiemMaVT(tree->pLeft, vt);
		}
		else
		{
			return TimKiemMaVT(tree->pRight, vt);
		}
	}
	return NULL;
}
//check ma vat tu trong cthd
ListVatTu* CheckMaVT(LISTVT tree, char mavt[10])
{
	if (tree == NULL) return NULL;
	else if (strcmp(tree->vt.MaVT, mavt) == 0)
	{
		ListVatTu* p = tree;
		return p;
	}
	else if (strcmp(tree->vt.MaVT, mavt) > 0)
	{
		return CheckMaVT(tree->pLeft, mavt);
	}
	else
	{
		return CheckMaVT(tree->pRight, mavt);
	}
}
//______________________IN DANH SACH VAT TU___________________________
//in danh sach vat tu
void InDSVT(LISTVT tree, int& i)
{
	GiaoDien_InDSVT(8, 30, "-----DANH SACH VAT TU-----");
	if(tree != NULL)
	{
		gotoxy(10, 11 + i);			cout << tree->vt.MaVT;
		gotoxy(26, 11 + i);			cout << tree->vt.TenVT;
		gotoxy(84, 11 + i);			cout << tree->vt.DVT;
		gotoxy(98, 11 + i);			cout << tree->vt.SLT;
		i++;
		InDSVT(tree->pLeft, i);
		InDSVT(tree->pRight, i);
	}
	AnDauNhay();
}
//in danh sach vat tu trong vthd
void InDSVT_CTHD(LISTVT tree, int& i)
{
	GiaoDien_InDSVT_CTHD(18, 24, "         -----DANH SACH VAT TU-----");
	if(tree != NULL)
	{
		gotoxy(62, 21 + i);			cout << tree->vt.MaVT;
		gotoxy(74, 21 + i);			cout << tree->vt.TenVT;
		gotoxy(99, 21 + i);			cout << tree->vt.DVT;
		gotoxy(112, 21 + i);		cout << tree->vt.SLT;
		i++;
		InDSVT_CTHD(tree->pLeft, i);
		InDSVT_CTHD(tree->pRight, i);
	}
	AnDauNhay();
}
//lay danh sach vt do ra mang(SLT!=0)
VatTu* getDSVT_SLT (LISTVT &tree, VatTu vt[], int &n)
{
	if (tree != NULL)
	{
		if (tree->vt.SLT != 0)
		{
			strcpy(vt[n].MaVT, tree->vt.MaVT);
			strcpy(vt[n].TenVT, tree->vt.TenVT);
			strcpy(vt[n].DVT, tree->vt.DVT);
			vt[n].SLT = tree->vt.SLT;
			n++;
		}
		getDSVT_SLT(tree->pLeft, vt, n);
		getDSVT_SLT(tree->pRight, vt, n);
	}
	return vt;
}
//lay dsvt do ra mang
VatTu* getDSVT (LISTVT &tree, VatTu vt[], int &n)
{
	if (tree != NULL)
	{
		strcpy(vt[n].MaVT, tree->vt.MaVT);
		strcpy(vt[n].TenVT, tree->vt.TenVT);
		strcpy(vt[n].DVT, tree->vt.DVT);
		vt[n].SLT = tree->vt.SLT;
		n++;
		getDSVT(tree->pLeft, vt, n);
		getDSVT(tree->pRight, vt, n);
	}
	return vt;
}
//sap xep theo ma vat tu de xem
VatTu* SX_TenVT (VatTu vt[], int &n)
{
	VatTu x;
	for (int i = 0; i < n; i++)
	{
		for(int j = n-1; j >= i; j--)
		{
			if(strcmp(vt[i].TenVT, vt[j].TenVT) > 0)
			{
				x = vt[i];
				vt[i] = vt[j];
				vt[j] = x;
			}
		}
	}
	return vt;
}
//xem danh sach vat tu
void XemDSVT(LISTVT tree)
{
	int key, n = 0;
	if ( tree == NULL)
	{
		ThongBao("Danh sach rong !", 7, 6);
		return;
	}
	GiaoDien_InDSVT(0, 30, "  -----DANH SACH VAT TU-----                               ESC: Thoat");
	VatTu vt[MAXVT];
	getDSVT(tree, vt, n);
	SX_TenVT(vt, n);
	for (int i = 0; i < n; i++)
	{
		gotoxy(10, 3 + i);			cout << vt[i].MaVT;
		gotoxy(26, 3 + i);			cout << vt[i].TenVT;
		gotoxy(84, 3 + i);			cout << vt[i].DVT;
		gotoxy(98, 3 + i);			cout << vt[i].SLT;
	}
	AnDauNhay();
	while (true)
	{
		while (_kbhit())
		{
			key = _getch();
			if (key == ESC) return;
		}
	}
}
//_________________________THEM VAT TU_________________________
//ham them vat tu
void ThemVT(LISTVT &tree)
{
	int x = 0, x1 = 0;
	system("cls");
	gotoxy(100, 0);		cout << "ENTER: chon";
	InDSVT(tree, x);
	while(true)
	{
		VatTu vt;
		GiaoDien_InDSVT(0, 3, "  -----NHAP VAT TU-----");
		HienDauNhay();
		char *mavt = new char[10];
		mavt = NhapMa(10, 3, 10, 0, false);
		strcpy(vt.MaVT, mavt);
		if(TimKiemMaVT(tree, vt) != NULL)
		{
			ThongBao("Da co vat tu nay roi !", 7, 6);
			return;
		}
		char *tenvt = new char[50];
		tenvt = NhapMa(26, 3, 50, 0, true);
		strcpy(vt.TenVT, tenvt);
		char *dvt = new char[10];
		dvt = NhapMa(84, 3, 10, 0, false);
		strcpy(vt.DVT, dvt);
		char *slt = new char[10];
		slt = NhapMa(98, 3, 10, 1, false);
		vt.SLT = atoi(slt);
		//xu ly them
		InsertVatTu(tree,vt);
		GhiFileVatTu(tree);
		ThongBao("Them vat tu thanh cong !", 7, 6);
		return;
	}
}
//_____________________XOA VAT TU_____________________
//xu ly xoa vat tu
void RemoveVatTu(LISTVT &tree, VatTu vt)
{
	if (tree == NULL)
	{
		return;
	}
	if (strcmp(tree->vt.MaVT,vt.MaVT) > 0)
	{
		return RemoveVatTu(tree->pLeft, vt);
	}
	else if (strcmp(tree->vt.MaVT,vt.MaVT) < 0)
		{
			return RemoveVatTu(tree->pRight, vt);
		}
	else
	{
		if (tree->pLeft == NULL)
		{
			tree = tree->pRight;
		}
		else if (tree->pRight == NULL)
		{
			tree = tree->pLeft;
		}
		else 
		{
			//tim phan tu the mang
			ListVatTu* x = tree->pLeft;
			while (x->pRight != NULL)
			{
				x = x->pRight;
			}
			tree->vt = x->vt;
			RemoveVatTu(tree->pLeft, x->vt);
			delete x;//giai phong vung nho
		}
	}
}
//ham xoa vat tu
void XoaVT(LISTVT &tree, LISTNV &ds)
{
	while(true)
	{
		VatTu vt;
		if(tree == NULL)
		{
			ThongBao("Danh sach vat tu rong !", 7, 6);
			return;
		}
		int x = 0;
		system("cls");
		InDSVT(tree,x);
		HienDauNhay();
		gotoxy(45, 0);		cout << "-----XOA VAT TU-----";
		gotoxy(100, 0);		cout << "ENTER: chon";
		gotoxy(7, 3);		cout << "Nhap ma vat tu can xoa : ";
		char *mavt = new char[10];
		mavt = NhapMa(32, 3, 10, 0, false);
		strcpy(vt.MaVT, mavt);
		
		ListVatTu* node;
		node = TimKiemMaVT(tree, vt);
		if(node == NULL)
		{
			ThongBao("Khong co vat tu nay !", 7, 5);
			return;
		}
		//kiem tra khoa ngoai, mavt trong cthd
		for(int i = 0; i < ds.n; i++)
		{
			for(NODEHD p = ds.dsnv[i]->nodehd; p != NULL; p = p->pNext)
			{
				for(NODECTHD q = p->hd.nodecthd; q != NULL; q = q->pNext)
				{
					if(strcmp(q->cthd.MaVT, vt.MaVT) == 0)
					{
						ThongBao("Vat tu da lap CTHD, KHONG XOA DUOC !", 7, 5);
						return;
					}
				}
			}
		}
		RemoveVatTu(tree, vt);
		GhiFileVatTu(tree);
		ThongBao("Xoa vat tu thanh cong !", 7, 5);
		return;
	}
}
//___________________SUA VAT TU____________________
void SuaVT(LISTVT &tree)
{
	while(true)
	{
		VatTu vt;
		if(tree == NULL)
		{
			ThongBao("Danh sach vat tu rong !", 7, 5);
			return;
		}
		int x = 0;
		InDSVT(tree, x);
		HienDauNhay();
		gotoxy(45, 0);		cout << "-----SUA VAT TU-----";
		gotoxy(99, 0);		cout << "ENTER: chon";
		gotoxy(7, 3);		cout << "Nhap ma vat tu can sua : ";
		char *mavt = new char[10];
		mavt = NhapMa(32, 3, 10, 0, false);
		strcpy(vt.MaVT, mavt);
		if(TimKiemMaVT(tree,vt) == NULL)
		{
			ThongBao("Khong co vat tu nay !", 7, 5);
			return;
		}
		ListVatTu *p = TimKiemMaVT(tree, vt);
		if (p != NULL)
		{
			system("cls");
			gotoxy(100, 0);	cout << "ENTER: chon";
			GiaoDien_InDSVT(0, 3, "---SUA THONG TIN VAT TU---");
			int x1 = 0;
			InDSVT(tree, x1);
			gotoxy(10, 3);	cout << p->vt.MaVT;
			gotoxy(98, 3);	cout << p->vt.SLT;
			HienDauNhay();
			char *tenvt = new char[50];
			tenvt = NhapMa(26, 3, 50, 0, true);
			strcpy(vt.TenVT, tenvt);
			char *dvt = new char[10];
			dvt = NhapMa(84, 3, 10, 0, false);
			strcpy(vt.DVT, dvt);
			
			strcpy(p->vt.TenVT, vt.TenVT);
			strcpy(p->vt.DVT, vt.DVT);
		}
		GhiFileVatTu(tree);
		ThongBao("Sua vat tu thanh cong !", 7, 6);
		return;
	}
}
//_________________SAP XEP VAT TU____________________
//sap xep theo ten vat tu----bubble sort
VatTu* SX_TenVT_TK (VatTu vt[], int &n)
{
	VatTu x;
	for (int i = 0; i < n; i++)
	{
		for(int j = i + 1; j < n; j++)
		{
			if(strcmp(vt[i].TenVT, vt[j].TenVT) > 0)
			{
				x = vt[i];
				vt[i] = vt[j];
				vt[j] = x;
			}
		}
	}
	return vt;
}
//in danh sach vat tu ton kho
void InDSVTTK_Ten(LISTVT tree)
{
	int key, n = 0;
	if ( tree == NULL)
	{
		ThongBao("Danh sach rong !", 9, 5);
		return;
	}
	GiaoDien_InDSVT(0, 30, "---DANH SACH VAT TU TON KHO---                             ESC: Thoat");
	VatTu vt[MAXVT];
	getDSVT_SLT(tree, vt, n);
	SX_TenVT_TK(vt, n);
	for (int i = 0; i < n; i++)
	{
		gotoxy(10, 3 + i);		cout << vt[i].MaVT;
		gotoxy(26, 3 + i);		cout << vt[i].TenVT;
		gotoxy(84, 3 + i);		cout << vt[i].DVT;
		gotoxy(98, 3 + i);		cout << vt[i].SLT;
	}
	AnDauNhay();
	while (true)
	{
		while (_kbhit())
		{
			key = _getch();
			if (key == ESC) return;
		}
	}
}
//*****************************XU LY NHAN VIEN******************************
//kiem tra rong
int EmptyDSNV(LISTNV ds)
{
	return (ds.n == 0 ? 1 : 0);
}
//kiem tra full
int FullDSNV(LISTNV ds)
{
	return (ds.n == MAXNV ? 1 : 0);
}
//in danh sach nhan vien
void InDSNV(LISTNV ds)
{
	if (EmptyDSNV(ds) == 1)
	{
		ThongBao("Danh sach rong ! ", 8, 6);
		return;
	}
	GiaoDien_InDSNV(8, 30, "---DANH SACH NHAN VIEN---");
	for (int i = 0; i < ds.n; i++)
	{
		gotoxy(15, 11 + i);		cout << ds.dsnv[i]->MaNV;
		gotoxy(35, 11 + i);		cout << ds.dsnv[i]->Ho;
		gotoxy(65, 11 + i);		cout << ds.dsnv[i]->Ten;
		gotoxy(85, 11 + i);
		if(ds.dsnv[i]->Phai == 1)
		{
			cout << "NAM";
		}
		else if(ds.dsnv[i]->Phai == 0)
		{
			cout << "NU";
		}
	}
	AnDauNhay();
}
//kiem tra trung ma nhan vien
int KiemTraMaNV(LISTNV ds, char manv[])
{
	for(int i = 0; i < ds.n; i++)
	{
		if(strcmp(ds.dsnv[i]->MaNV, manv) == 0)
		{
			return 1;
		}
	}
	return -1;
}
//ham tra ve vi tri nv trong dstt la 1 mang con tro
int ViTriNV(LISTNV &ds, char manv[])
{
	for(int i = 0; i < ds.n; i++)
	{
		if(strcmp(ds.dsnv[i]->MaNV, manv) == 0)
		{
			return i;
		}
	}
	return -1;
}
//in danh sach nhan vien trong hd
void InDSNV_HD(LISTNV ds)
{
	if (EmptyDSNV(ds) == 1)
	{
		ThongBao("Danh sach rong ! ", 8, 6);
		return;
	}
	GiaoDien_InDSNV_HD(8, 34, "-----DANH SACH NHAN VIEN-----");
	for (int i = 0; i < ds.n; i++)
	{
		gotoxy(23, 11 + i);		cout << ds.dsnv[i]->MaNV;
		gotoxy(45, 11 + i);		cout << ds.dsnv[i]->Ho;
		gotoxy(75, 11 + i);		cout << ds.dsnv[i]->Ten;
		gotoxy(95, 11 + i);
		if(ds.dsnv[i]->Phai == 1)
		{
			cout << "NAM";
		}
		else if(ds.dsnv[i]->Phai == 0)
		{
			cout << "NU";
		}
	}
	AnDauNhay();
}
//___________________THEM NHAN VIEN___________________
//ham them nhan vien
void ThemNV(LISTNV &ds)
{
	gotoxy(88, 0);	cout << "ENTER: chon";
	gotoxy(80,5);	cout << "Phai: 1-NAM  0-NU";
	NhanVien nv;
	if(FullDSNV(ds) == 1)
	{
		ThongBao("Danh sach day !", 9, 6);
		return;
	}
	int ktra = 0;
	for ( ; ds.n < MAXNV; )
	{
		InDSNV(ds);
		GiaoDien_InDSNV(0, 3, "-----NHAP NHAN VIEN-----");
		HienDauNhay();
		char *manv = new char[10];
		manv = NhapMa(15, 3, 10, 0, false);
		strcpy(nv.MaNV, manv);
		if(KiemTraMaNV(ds, manv) == 1)
		{
			ThongBao("Da co nhan vien nay roi !", 8, 6);
			return;
		}
		char *ho = new char[20];
		ho = NhapMa(35, 3, 20, 0, true);
		strcpy(nv.Ho, ho);
		char *ten = new char[10];
		ten = NhapMa(65, 3, 10, 0, false);
		strcpy(nv.Ten, ten);
		gotoxy(85, 3);
		int Phai = 0;
		ChiNhap0or1(nv.Phai);
		//xu ly trong ds nhan vien
		ds.dsnv[ds.n] = new NhanVien;
		strcpy(ds.dsnv[ds.n]->MaNV, nv.MaNV);
		strcpy(ds.dsnv[ds.n]->Ho, nv.Ho);
		strcpy(ds.dsnv[ds.n]->Ten, nv.Ten);
		ds.dsnv[ds.n]->Phai = nv.Phai;
		ds.dsnv[ds.n]->nodehd = NULL;
		ThongBao("Them nhan vien thanh cong !", 8, 6);
		ds.n++;
		GhiFileNhanVien(ds);
		return;
	}
}
//________________XOA NHAN VIEN_______________
//ham xoa nhan vien
void XoaNV(LISTNV &ds)
{
	while(true)
	{
		if(EmptyDSNV(ds) == 1)
		{
			ThongBao("Danh sach rong !", 8, 5);
			return;
		}
		InDSNV(ds);
		HienDauNhay();
		gotoxy(39, 0);	cout << "-----XOA NHAN VIEN-----";
		gotoxy(88, 0);	cout << "ENTER: chon";
		gotoxy(8, 3);	cout << "Nhap ma nhan vien can xoa : ";
		char *manv = new char[10];
		manv = NhapMa(37, 3, 10, 0, false);
		if(KiemTraMaNV(ds, manv) != 1)
		{
			ThongBao("Khong co nhan vien nay !", 8, 5);
			return;
		}
		//ktra nhan vien: neu da lap hoa don thi ko xoa duoc
		int vitri = ViTriNV(ds, manv);
		for(NODEHD p = ds.dsnv[vitri]->nodehd; p != NULL; p = p->pNext)
		{
			if(p != NULL)
			{
				ThongBao("Nhan vien da lap hoa don. KHONG XOA DUOC !", 8, 5);
				return;
			}
		}
		//xu ly
		for (int i = vitri; i < ds.n; i++)
		{
			delete ds.dsnv[i];//giai phong bo nho
			ds.dsnv[i] = ds.dsnv[i + 1];
		}
		ds.n--;
		GhiFileNhanVien(ds);
		ThongBao("Xoa nhan vien thanh cong !", 8, 6);
		return;
	}
}
//_________________SUA NHAN VIEN___________________
//ham sua nhan vien
void SuaNV(LISTNV &ds)
{
	while(true)
	{
		NhanVien nv;
		if(EmptyDSNV(ds) == 1)
		{
			ThongBao("Danh sach rong !", 8, 5);
			return;
		}
		InDSNV(ds);
		HienDauNhay();
		gotoxy(39, 0);			cout << "-----SUA NHAN VIEN-----";
		gotoxy(88, 0);			cout << "ENTER: chon";
		gotoxy(9, 3);			cout << "Nhap ma nhan vien can sua : ";
		char *manv = new char[10];
		manv = NhapMa(37, 3, 10, 0, false);
		strcpy(nv.MaNV, manv);
		int ktra = ViTriNV(ds, manv);
		if(KiemTraMaNV(ds, manv) != 1)
		{
			ThongBao("Khong co nhan vien nay !", 8, 5);
			return;
		}
		else
		{	
			system("cls");
			gotoxy(88, 0);		cout << "ENTER: chon";
			InDSNV(ds);
			GiaoDien_InDSNV(0,3, " -----SUA NHAN VIEN-----");
			gotoxy(80, 5);		cout << "Phai: 1-NAM   0-NU";
			gotoxy(15, 3);		cout << ds.dsnv[ktra]->MaNV;
			char *ho  = new char[20];
			ho = NhapMa(35, 3, 20, 0, true);
			strcpy(nv.Ho, ho);
			char *ten = new char[10];
			ten = NhapMa(65, 3, 10, 0, false);
			strcpy(nv.Ten, ten);
			gotoxy(85, 3);
			ChiNhap0or1(nv.Phai);
			
			//strcpy vao nv sua
			strcpy(ds.dsnv[ktra]->Ho, nv.Ho);
			strcpy(ds.dsnv[ktra]->Ten, nv.Ten);
			ds.dsnv[ktra]->Phai = nv.Phai;
		}
		GhiFileNhanVien(ds);
		ThongBao("Sua nhan vien thanh cong !", 8, 6);
		return;
	}
}
//________________SAP XEP NHAN VIEN_________________
//sap xep ds nhan vien theo ten ho___bubble sort
void SX_TenHoNV(LISTNV &ds)
{
	NhanVien *x;///giai thich
	for(int i = 0; i < ds.n-1 ; i++)
	{
		for(int j = i + 1; j < ds.n ; j++)
		{
			if(strcmp(ds.dsnv[i]->Ten, ds.dsnv[j]->Ten) > 0)
			{
				x = ds.dsnv[i];
				ds.dsnv[i] = ds.dsnv[j];
				ds.dsnv[j] = x;
			} 
			else if(strcmp(ds.dsnv[i]->Ten, ds.dsnv[j]->Ten) == 0)
			{
				if(strcmp(ds.dsnv[i]->Ho, ds.dsnv[j]->Ho) > 0)
				{
					x = ds.dsnv[i];
					ds.dsnv[i] = ds.dsnv[j];
					ds.dsnv[j] = x;
				}
			}
		}
	}
}
//ham in danh sach nhan vien sap xep theo ten ho tang dan
void InDSNV_TenHo(LISTNV ds)
{
	int key;
	if(EmptyDSNV(ds) == 1)
	{
		ThongBao("Danh sach rong ! ", 9, 5);
		return;
	}
	GiaoDien_InDSNV(0, 30, "---DANH SACH NHAN VIEN TEN HO---                  ESC: Thoat");
	SX_TenHoNV(ds);
	for (int i = 0; i < ds.n; i++)
	{
		gotoxy(15, 3 + i);		cout << ds.dsnv[i]->MaNV;
		gotoxy(35, 3 + i);		cout << ds.dsnv[i]->Ho;
		gotoxy(65, 3 + i);		cout << ds.dsnv[i]->Ten;
		gotoxy(85, 3 + i);
		if(ds.dsnv[i]->Phai == 1)
		{
			cout << "NAM";
		}
		else if(ds.dsnv[i]->Phai == 0)
		{
			cout << "NU";
		}
	}
	AnDauNhay();
	while (true)
	{
		while (_kbhit())
		{
			key = _getch();
			if (key == ESC) return;
		}
	}
}
//*****************************XU LY HOA DON******************************
//khoi tao ds lien ket don HD
void InitHoaDon(NODEHD &first)
{
	first = NULL;
}
//tao node hoa don
NODEHD TaoNodeHD (HoaDon hd)
{
	NODEHD p = new NodeHD;
	if ( p == NULL)
	{
		cout << "Khong du bo nho de cap phat !";
		return NULL;
	}
	p->hd = hd;
	p->pNext = NULL;
	return p;
}
//kiem tra trung so hoa don
int KiemTraSoHD(NODEHD &first, char sohd[20])
{
	for (NODEHD k = first; k != NULL; k = k->pNext)
	{
		if(strcmp(k->hd.SoHD, sohd) == 0)
		{
			return 1;
		}
	}
	return -1;
}
//ham tra ve vi tri cua 1 hoa don la con tro(node)
NODEHD ViTriHD(NODEHD &first, char sohd[20])
{
	for (NODEHD k = first; k != NULL; k = k->pNext)
	{
		if(strcmp(k->hd.SoHD, sohd) == 0)
		{
			return k;
		}
	}
	return NULL;
}
//them vao cuoi danh sach
void InsertHD(NODEHD &first, NODEHD p)
{
	if(first == NULL)
	{
		first = p;
	}
	else
	{
		NODEHD last = first;
		for( ; last->pNext != NULL; last = last->pNext);
		last->pNext = p;
	}
}
//ham doc file hoa don
void DocFileHoaDon(LISTNV &ds)
{
	string data;
	fstream f;
	f.open("dshoadon.txt", ios::in);
	char manv[10];
	if(f == NULL)
	{
		return;
	}
	getline(f, data);
	strcpy(manv, data.c_str());
	while (!f.eof() && manv != NULL)
	{
		HoaDon hd;
		getline(f, data);
		if(data.size() == 0)
		{
			break;
		}
		strcpy(hd.SoHD, data.c_str());
		f >> hd.NgayLap.Ngay;
		f.ignore();
		f >> hd.NgayLap.Thang;
		f.ignore();
		f >> hd.NgayLap.Nam;
		f.ignore();
		f >> hd.Loai;
		f.ignore();
		//xu ly danh sach chi tiet hoa don  ??
		hd.nodecthd = NULL;
		int vitrinv = ViTriNV(ds, manv);
		InsertHD(ds.dsnv[vitrinv]->nodehd, TaoNodeHD(hd));
		f >> manv;
		f.ignore();
	}
	f.close();
}
//ham ghi file hoa don
void GhiFileHoaDon(LISTNV ds)
{
	fstream f;
	f.open("dshoadon.txt", ios::out);
	NODEHD nodeHD;
	
	for(int i = 0; i < ds.n; i++)
	{
		if(ds.dsnv[i]->nodehd != NULL)
		{
			nodeHD = ds.dsnv[i]->nodehd;
		}
		else
		{
			nodeHD = NULL;
		}
		while(nodeHD != NULL)
		{
			f << ds.dsnv[i]->MaNV << endl;
			f << nodeHD->hd.SoHD << endl;
			f << nodeHD->hd.NgayLap.Ngay << endl;
			f << nodeHD->hd.NgayLap.Thang << endl;
			f << nodeHD->hd.NgayLap.Nam << endl;
			f << nodeHD->hd.Loai << endl;
			//xy ly
			nodeHD = nodeHD->pNext;
		}
	}
	f.close();
}
//in danh sach hoa don
void InDSHD(NODEHD first)
{
	AnDauNhay();
	GiaoDien_InHD(12, 30, "-----DANH SACH HOA DON-----");
	int k = 0;
	for(NODEHD p = first; p != NULL; p = p->pNext)
	{
		gotoxy(9, 15 + k);		cout << p->hd.SoHD;
		gotoxy(32, 15 + k);		cout << p->hd.NgayLap.Ngay << " / " << p->hd.NgayLap.Thang << " / " << p->hd.NgayLap.Nam;
		gotoxy(50, 15 + k);
		if (p->hd.Loai == 'n' || p->hd.Loai == 'N')
		{
			cout << "NHAP";
		}
		if (p->hd.Loai == 'x' || p->hd.Loai == 'X')
		{
			cout << "XUAT";
		}
		k++;
	}
}
//xu ly nhap hoa don
void NhapHD(LISTNV &ds, LISTVT tree, char manv[10])
{
	GiaoDien_LapHD(6, 3, "-----LAP HOA DON-----");
	HoaDon hd;
	char *sohd = new char[10];
	sohd = NhapMa(9, 9, 20, 0, false);
	strcpy(hd.SoHD, sohd);
	for(int i = 0; i < ds.n; i++)
	{
		for(NODEHD p = ds.dsnv[i]->nodehd; p != NULL; p = p->pNext)
		{
			if(KiemTraSoHD(ds.dsnv[i]->nodehd, sohd) == 1)
			{
				
				ThongBao("Da co so hoa don nay !", 7, 11);
				system("cls");
				return;
			}
		}
	}
	Date date = Now();
	gotoxy(32, 9);			cout << date.Ngay;
	gotoxy(35, 9);			cout << "/";
	gotoxy(37, 9);			cout << date.Thang;
	gotoxy(39, 9);			cout << "/";
	gotoxy(41, 9);			cout << date.Nam;
	gotoxy(51, 9);
	char loai;
	hd.Loai = ChiNhapNorX(loai);
	hd.NgayLap = date;
	hd.Loai = loai;
	NODECTHD dsCTHD;
	hd.nodecthd = dsCTHD;
	hd.nodecthd = NULL;
	//xu ly
	int vitrinv = ViTriNV(ds, manv);
	InsertHD(ds.dsnv[vitrinv]->nodehd, TaoNodeHD(hd));
	GhiFileHoaDon(ds);
	ThongBao("Them hoa don thanh cong !", 7, 11);
	InDSHD(ds.dsnv[vitrinv]->nodehd);
	system("cls");
	return;
}
//************************XU LY CHI TIET HOA DON***************************
//khoi tao ds lien ket don CTHD
void InitCTHD(NODECTHD &first)
{
	first = NULL;
}
//tao node chi tiet hoa don
NODECTHD TaoNodeCTHD (CTHoaDon cthd)
{
	NODECTHD p = new NodeCTHD;
	if ( p == NULL)
	{
		cout << "Khong du bo nho de cap phat !";
		return NULL;
	}
	p->cthd = cthd;
	p->pNext = NULL;
	return p;
}
//them vao cuoi danh sach
void InsertCTHD(NODECTHD &first, NODECTHD p)
{
	if(first == NULL)
	{
		first = p;
	}
	else
	{
		NODECTHD last = first;
		for( ; last->pNext != NULL; last = last->pNext);
		last->pNext = p;
	}
}
//kiem tra trung ma vat tu trong cthd
int KiemTraMaVT_CTHD(NODECTHD &first, char mavt[10])
{
	for (NODECTHD k = first; k != NULL; k = k->pNext)
	{
		if(strcmp(k->cthd.MaVT, mavt) == 0)
		{
			return 1;
		}
	}
	return -1;
}
//doc file chi tiet hoa don
void DocFileCTHD(LISTNV &ds)
{
	HoaDon hd;
	string data;
	fstream f;
	f.open("dschitiethoadon.txt", ios::in);
	char manv[10];
	if(f == NULL)
	{
		return;
	}
	getline(f, data);		strcpy(manv, data.c_str());
	while (!f.eof() && manv != NULL)
	{
		char sohd[20];
		getline(f, data);		strcpy(sohd, data.c_str());
		int vitrinv = ViTriNV(ds, manv);
		for(NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
		{
			if(strcmp(sohd, p->hd.SoHD) == 0)
			{
				CTHoaDon cthd;
				getline(f, data);		strcpy(cthd.MaVT, data.c_str());
				f >> cthd.SoLuong;
				f.ignore();
				f >> cthd.DonGia;
				f.ignore();
				f >> cthd.VAT;
				f.ignore();
				//xu ly
				InsertCTHD(p->hd.nodecthd, TaoNodeCTHD(cthd));
				break;
			}
		}
		f >> manv;
		f.ignore();
	}
	f.close();
}
//ghi file chi tiet hoa don
void GhiFileCTHD(LISTNV &ds)
{
	fstream f;
	f.open("dschitiethoadon.txt", ios::out);
	NODECTHD nodeCTHD;
	
	for(int i = 0; i < ds.n; i++)
	{
		if(ds.dsnv[i]->nodehd != NULL)
		{
			for(NODEHD p = ds.dsnv[i]->nodehd; p != NULL; p = p->pNext)
			{
				if(p->hd.nodecthd != NULL)
				{
					nodeCTHD = p->hd.nodecthd;
					while(nodeCTHD != NULL)
					{
						f << ds.dsnv[i]->MaNV << endl;
						f << p->hd.SoHD << endl;
						f << nodeCTHD->cthd.MaVT << endl;
						f << nodeCTHD->cthd.SoLuong << endl;
						f << nodeCTHD->cthd.DonGia << endl;
						f << nodeCTHD->cthd.VAT << endl;
						nodeCTHD = nodeCTHD->pNext;
					}
				}
				else
				{
					nodeCTHD = NULL;
				}
			}
		}
	}
	f.close();
}
//in ds cthd
void InDSCTHD(NODECTHD first)
{
	AnDauNhay();
	GiaoDien_LapCTHD(12, 30, "         -----CHI TIET HOA DON-----");
	int k = 0;
	for(NODECTHD p = first; p != NULL; p = p->pNext)
	{
		gotoxy(62, 15 + k);		cout << p->cthd.MaVT;
		gotoxy(85, 15 + k);		cout << p->cthd.SoLuong;
		gotoxy(99, 15 + k);		cout << p->cthd.DonGia;
		gotoxy(112, 15 + k);	cout << p->cthd.VAT << "%";
		k++;
	}
}
//xem cthd
void XemCTHD(LISTNV &ds, char manv[10])
{
	while (true)
	{
		gotoxy(7, 5);					cout << "Nhap so hoa don can xem cthd : ";
		HienDauNhay();
		char *sohd = new char[20];
		sohd = NhapMa(38, 5, 20, 0, false);
		int vitrinv = ViTriNV(ds, manv);
		for (NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
		{
			if (strcmp(p->hd.SoHD, sohd) == 0)
			{
				AnDauNhay();
				system("cls");
				InDSCTHD(p->hd.nodecthd);
				gotoxy(7, 5);			cout << "Nhap so hoa don can xem cthd : " << sohd;
				GiaoDien_LapHD(12, 3, "  -----HOA DON-----");
				gotoxy(9, 15);			cout << p->hd.SoHD;
				gotoxy(32, 15);			cout << p->hd.NgayLap.Ngay;
				gotoxy(35, 15);			cout << "/";
				gotoxy(37, 15);			cout << p->hd.NgayLap.Thang;
				gotoxy(39, 15);			cout << "/";
				gotoxy(41, 15);			cout << p->hd.NgayLap.Nam;
				gotoxy(50, 15);
				if(p->hd.Loai == 'n' || p->hd.Loai == 'N') 	cout << "NHAP";
				if(p->hd.Loai == 'x' || p->hd.Loai == 'X') 	cout << "XUAT";
				gotoxy(50, 0);			cout << "--------HOA DON--------";
				gotoxy(7, 3); 			cout << "Ma nhan vien : " << manv;
				gotoxy(26, 3);			cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
				gotoxy(107, 0);			cout << "F1    : Them HD";
				gotoxy(107, 1);			cout << "F2    : Nhap CTHD";
				gotoxy(107, 2);			cout << "F3    : Xem CTHD";
				gotoxy(107, 3);			cout << "ESC   : Thoat";
				return;
			}
		}
		ThongBao("Khong co so hoa don nay !", 7, 7);
		system("cls");
		InDSHD(ds.dsnv[vitrinv]->nodehd);
		gotoxy(50, 0);				cout << "--------HOA DON--------";
		gotoxy(7, 3); 				cout << "Ma nhan vien : " << manv;
		gotoxy(26, 3);				cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
		gotoxy(107, 0);				cout << "F1    : Them HD";
		gotoxy(107, 1);				cout << "F2    : Nhap CTHD";
		gotoxy(107, 2);				cout << "F3    : Xem CTHD";
		gotoxy(107, 3);				cout << "ESC   : Thoat";
		return;
	}
}
//ham nhap chi tiet hoa don
void NhapCTHD(LISTNV &ds, LISTVT tree, NODECTHD &first, char loai, char sohd[20], char manv[10])
{
	GiaoDien_LapCTHD(12, 3, "       -----LAP CHI TIET HOA DON-----");
	int x = 0;
	InDSVT_CTHD(tree, x);
	VatTu vt;
	CTHoaDon cthd;

	char *mavt = new char[10];
	mavt = NhapMa(62, 15, 20, 0, false);
	strcpy(cthd.MaVT, mavt);
	
	int vitrinv = ViTriNV(ds, manv);
	ListVatTu *p1 = CheckMaVT(tree, mavt);
	
	if(p1 == NULL)
	{
		ThongBao("Khong co ma vat tu nay !", 7, 7);
		system("cls");
		for(NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
		{
			if (strcmp(p->hd.SoHD, sohd) == 0)
			{
				GiaoDien_LapHD(12, 3, "  -----HOA DON-----");
				gotoxy(9, 15);		cout << p->hd.SoHD;
				gotoxy(32, 15);		cout << p->hd.NgayLap.Ngay;
				gotoxy(35, 15);		cout << "/";
				gotoxy(37, 15);		cout << p->hd.NgayLap.Thang;
				gotoxy(39, 15);		cout << "/";
				gotoxy(41, 15);		cout << p->hd.NgayLap.Nam;
				gotoxy(50, 15);
				if(p->hd.Loai == 'n' || p->hd.Loai == 'N') 	cout << "NHAP";
				if(p->hd.Loai == 'x' || p->hd.Loai == 'X') 	cout << "XUAT";
				InDSCTHD(p->hd.nodecthd);
			}
		}
		gotoxy(50, 0);				cout << "--------HOA DON--------";
		gotoxy(7, 3);				cout << "Ma nhan vien : " << manv;
		gotoxy(26, 3);				cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
		gotoxy(107, 0);				cout << "F4    : Tiep tuc";
		gotoxy(107, 1);				cout << "ESC   : Thoat";
		return;
	}
	else
	{
		for(NODECTHD q = first; q != NULL; q = q->pNext)
		{
			if(strcmp(q->cthd.MaVT, mavt) == 0)
			{
				ThongBao("Da nhap ma vat tu nay cho cthd !", 7, 7);
				system("cls");
				for(NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
				{
					if (strcmp(p->hd.SoHD, sohd) == 0)
					{
						GiaoDien_LapHD(12, 3, "  -----HOA DON-----");
						gotoxy(9, 15);		cout << p->hd.SoHD;
						gotoxy(32, 15);		cout << p->hd.NgayLap.Ngay;
						gotoxy(35, 15);		cout << "/";
						gotoxy(37, 15);		cout << p->hd.NgayLap.Thang;
						gotoxy(39, 15);		cout << "/";
						gotoxy(41, 15);		cout << p->hd.NgayLap.Nam;
						gotoxy(50, 15);
						if(p->hd.Loai == 'n' || p->hd.Loai == 'N') 	cout << "NHAP";
						if(p->hd.Loai == 'x' || p->hd.Loai == 'X') 	cout << "XUAT";
						InDSCTHD(p->hd.nodecthd);
					}
				}
				gotoxy(50, 0);				cout << "--------HOA DON--------";
				gotoxy(7, 3); 				cout << "Ma nhan vien : " << manv;
				gotoxy(26, 3);				cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
				gotoxy(107, 0);				cout << "F4    : Tiep tuc";
				gotoxy(107, 1);				cout << "ESC   : Thoat";
				return;
			}
		}
	}
	
	char *soluong = new char[10];
	soluong = NhapMa(85, 15, 10, 1, false);
	cthd.SoLuong = atoi(soluong);
	
	char *dongia = new char[10];
	dongia = NhapMa(99, 15, 10, 1, false);
	cthd.DonGia = atoi(dongia);
	
	char *vat = new char[10];
	vat = NhapMa(112, 15, 10, 1, false);
	cthd.VAT = atoi(vat);
	
	if(loai == 'x' || loai == 'X')
	{
		if(cthd.SoLuong > p1->vt.SLT)	
		{
			gotoxy(7, 7);
			cout << "Khong du vat tu de xuat, hien co : " << p1->vt.SLT << " vat tu";
			Sleep(2000);
			system("cls");
			for(NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
				{
					if (strcmp(p->hd.SoHD, sohd) == 0)
					{
						gotoxy(50, 0);			cout << "--------HOA DON--------";
						gotoxy(7, 3); 			cout << "Ma nhan vien : " << manv;
						gotoxy(26, 3);			cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
						gotoxy(107, 0);			cout << "F4    : Tiep tuc";
						gotoxy(107, 1);			cout << "ESC   : Thoat";
						GiaoDien_LapHD(12, 3, "  -----HOA DON-----");
						gotoxy(9, 15);			cout << p->hd.SoHD;
						gotoxy(32, 15);			cout << p->hd.NgayLap.Ngay;
						gotoxy(35, 15);			cout << "/";
						gotoxy(37, 15);			cout << p->hd.NgayLap.Thang;
						gotoxy(39, 15);			cout << "/";
						gotoxy(41, 15);			cout << p->hd.NgayLap.Nam;
						gotoxy(50, 15);
						if(p->hd.Loai == 'n' || p->hd.Loai == 'N') 	cout << "NHAP";
						if(p->hd.Loai == 'x' || p->hd.Loai == 'X') 	cout << "XUAT";
						InDSCTHD(p->hd.nodecthd);
					}
				}
			return;
		}
		else if(cthd.SoLuong <= p1->vt.SLT)
		{
			p1->vt.SLT -= cthd.SoLuong;
			InsertCTHD(first, TaoNodeCTHD(cthd));
			GhiFileCTHD(ds);
			GhiFileVatTu(tree);
		}
	}
	if(loai == 'n' || loai == 'N')
	{
		p1->vt.SLT += cthd.SoLuong;
		InsertCTHD(first, TaoNodeCTHD(cthd));
		GhiFileCTHD(ds);
		GhiFileVatTu(tree);
	}
	ThongBao("Them cthd thanh cong !", 7, 7);
	system("cls");
	gotoxy(50, 0);				cout << "--------HOA DON--------";
	gotoxy(7, 3); 				cout << "Ma nhan vien : " << manv;
	gotoxy(26, 3);				cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
	gotoxy(107, 0);				cout << "F4    : Tiep tuc";
	gotoxy(107, 1);				cout << "ESC   : Thoat";
	for(NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
	{
		if (strcmp(p->hd.SoHD, sohd) == 0)
		{
			InDSCTHD(p->hd.nodecthd);
			GiaoDien_LapHD(12, 3, "  -----HOA DON-----");
			gotoxy(9, 15);		cout << p->hd.SoHD;
			gotoxy(32, 15);		cout << p->hd.NgayLap.Ngay;
			gotoxy(35, 15);		cout << "/";
			gotoxy(37, 15);		cout << p->hd.NgayLap.Thang;
			gotoxy(39, 15);		cout << "/";
			gotoxy(41, 15);		cout << p->hd.NgayLap.Nam;
			gotoxy(50, 15);
			if(p->hd.Loai == 'n' || p->hd.Loai == 'N') 	cout << "NHAP";
			if(p->hd.Loai == 'x' || p->hd.Loai == 'X') 	cout << "XUAT";
		}
	}
	return;
}
//nhap cthd F2
void NhapSoHD_NhapCTHD(LISTNV &ds, LISTVT tree, char manv[10])
{
	while (true)
	{
		gotoxy(7, 5);					cout << "Nhap so hoa don de them cthd : ";
		HienDauNhay();
		char *sohd = new char[20];
		sohd = NhapMa(38, 5, 20, 0, false);
		
		int vitrinv = ViTriNV(ds, manv);
		for (NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
		{
			if (strcmp(p->hd.SoHD, sohd) == 0)
			{
				system("cls");
				GiaoDien_LapHD(12, 3, "  -----HOA DON-----");
				gotoxy(9, 15);			cout << p->hd.SoHD;
				gotoxy(32, 15);			cout << p->hd.NgayLap.Ngay;
				gotoxy(35, 15);			cout << "/";
				gotoxy(37, 15);			cout << p->hd.NgayLap.Thang;
				gotoxy(39, 15);			cout << "/";
				gotoxy(41, 15);			cout << p->hd.NgayLap.Nam;
				gotoxy(50, 15);
				if(p->hd.Loai == 'n' || p->hd.Loai == 'N') 	cout << "NHAP";
				if(p->hd.Loai == 'x' || p->hd.Loai == 'X') 	cout << "XUAT";
				gotoxy(50, 0);				cout << "--------HOA DON--------";
				gotoxy(107, 0);			cout << "ENTER : Chon";
				gotoxy(7, 5);			cout << "Nhap so hoa don de them cthd : " << sohd;
				gotoxy(7, 3); 			cout << "Ma nhan vien : " << manv;
				gotoxy(26, 3);			cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
				AnDauNhay();
				NhapCTHD(ds, tree, p->hd.nodecthd, p->hd.Loai, sohd, manv);
				while (true)
				{
					while (_kbhit())
					{
						int chon = _getch();
						if (chon == 224 || chon == 0) chon = _getch();
						if (chon == ESC) return;
						if (chon == F4)
						{
							system("cls");
							gotoxy(50, 0);			cout << "--------HOA DON--------";
							gotoxy(107, 0);			cout << "ENTER : Chon";
							gotoxy(7, 3); 			cout << "Ma nhan vien : " << manv;
							gotoxy(26, 3);			cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
							GiaoDien_LapHD(12, 3, "  -----HOA DON-----");
							gotoxy(9, 15);			cout << p->hd.SoHD;
							gotoxy(32, 15);			cout << p->hd.NgayLap.Ngay;
							gotoxy(35, 15);			cout << "/";
							gotoxy(37, 15);			cout << p->hd.NgayLap.Thang;
							gotoxy(39, 15);			cout << "/";
							gotoxy(41, 15);			cout << p->hd.NgayLap.Nam;
							gotoxy(50, 15);
							if(p->hd.Loai == 'n' || p->hd.Loai == 'N') 	cout << "NHAP";
							if(p->hd.Loai == 'x' || p->hd.Loai == 'X') 	cout << "XUAT";
							NhapCTHD(ds, tree, p->hd.nodecthd, p->hd.Loai, sohd, manv);
						}
					}
				}
				return;
			}
		}
		ThongBao("Khong co so hoa don nay !", 7, 7);
		system("cls");
		InDSHD(ds.dsnv[vitrinv]->nodehd);
		gotoxy(50, 0);				cout << "--------HOA DON--------";
		gotoxy(7, 3); 				cout << "Ma nhan vien : " << manv;
		gotoxy(26, 3);				cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
		gotoxy(107, 0);				cout << "F1    : Them HD";
		gotoxy(107, 1);				cout << "F2    : Nhap CTHD";
		gotoxy(107, 2);				cout << "F3    : Xem CTHD";
		gotoxy(107, 3);				cout << "ESC   : Thoat";
		return;
	}
}
//*********************THONG KE HOA DON TU NGAY... DEN NGAY...************************
struct ThongKeHD
{
	char SoHD[20];
	Date NgayNhap;
	char Loai;
	char Ho[20];
	char Ten[10];
	float TriGia;
};
void InThongKeHD(ThongKeHD tkhd, int y)
{
	gotoxy(13, 6 + y);		cout << tkhd.SoHD;
	gotoxy(32, 6 + y);		cout << tkhd.NgayNhap.Ngay;
	gotoxy(35, 6 + y);		cout << "/";
	gotoxy(37, 6 + y);		cout << tkhd.NgayNhap.Thang;
	gotoxy(40, 6 + y);		cout << "/";
	gotoxy(42, 6 + y);		cout << tkhd.NgayNhap.Nam;
	gotoxy(55, 6 + y);
	if (tkhd.Loai == 'n' || tkhd.Loai == 'N')
	{
		cout << "NHAP";
	}
	if (tkhd.Loai == 'x' || tkhd.Loai == 'X')
	{
		cout << "XUAT";
	}
	gotoxy(70, 6 + y);		cout << tkhd.Ho << " " << tkhd.Ten;
	gotoxy(105, 6 + y);		cout << tkhd.TriGia;
}
void ThongKeHD_Ngay(LISTNV ds)
{
	while(true)
	{
		system("cls");
		GiaoDien_ThongKeHD();
		gotoxy(110, 0);		cout << "ENTER: chon";
		HienDauNhay();
		Date date1, date2;
		char manv[10];
		HienDauNhay();
		date1.Ngay = date1.Thang = date1.Nam = 0;
		date2.Ngay = date2.Thang = date2.Nam = 0;
		char *ngay1 = new char(2);
		ngay1 = NhapMa(40, 2, 2, 1, false);
		date1.Ngay = atoi(ngay1);
		
		gotoxy(43, 2);	cout << "/";
		
		char *thang1 = new char(2);
		thang1 = NhapMa(45, 2, 2, 1, false);
		date1.Thang = atoi(thang1);
		
		gotoxy(48, 2);	cout << "/";
		
		char *nam1 = new char(4);
		nam1 = NhapMa(50, 2, 4, 1, false);
		date1.Nam = atoi(nam1);
		if (CheckNgay(date1) == 1)
		{
			ThongBao("Nhap sai ngay !", 30, 3);
			continue;
		}
		char *ngay2 = new char(2);
		ngay2 = NhapMa(73, 2, 2, 1, false);
		date2.Ngay = atoi(ngay2);
		
		gotoxy(76, 2);	cout << "/";
		
		char *thang2 = new char(2);
		thang2 = NhapMa(78, 2, 2, 1, false);
		date2.Thang = atoi(thang2);
		
		gotoxy(81, 2);	cout << "/";
		
		char *nam2 = new char(4);
		nam2 = NhapMa(83, 2, 4, 1, false);
		date2.Nam = atoi(nam2);
		if (CheckNgay(date2) == 1)
		{
			ThongBao("Nhap sai ngay !", 30, 3);
			continue;
		}
		if (SoSanh2Ngay(date1, date2) == 1)
		{
			ThongBao("Ngay bat dau phai nho hon ngay ket thuc", 30, 3);
			continue;
		}
		int y = 0;
		for(int i = 0; i < ds.n; i++)
		{
			for(NODEHD p = ds.dsnv[i]->nodehd; p != NULL; p = p->pNext)
			{
				if (SoSanh2Ngay(p->hd.NgayLap, date1) == 1 && SoSanh2Ngay(date2, p->hd.NgayLap) == 1)
				{
					ThongKeHD tkhd;
					strcpy(tkhd.SoHD, p->hd.SoHD);
					tkhd.NgayNhap = p->hd.NgayLap;
					tkhd.Loai = p->hd.Loai;
					strcpy(tkhd.Ho, ds.dsnv[i]->Ho);
					strcpy(tkhd.Ten, ds.dsnv[i]->Ten);
					float trigia = 0, kq = 0;
					for (NODECTHD q = p->hd.nodecthd; q != NULL; q = q->pNext)
					{
						kq = q->cthd.SoLuong * q->cthd.DonGia;
						trigia += kq + (q->cthd.VAT*kq)/100;
					}
					tkhd.TriGia = trigia;
					InThongKeHD(tkhd, y++);
				}
				else
				{
					ThongBao("Khong co hoa don nao trong khoang thoi gian nay !", 30, 3);
					ThongKeHD_Ngay(ds);
				}
			}
		}
		AnDauNhay();
		gotoxy(107, 0);		cout << "F1  : Tiep tuc";
		gotoxy(107, 1);		cout << "ESC : Thoat";
		int key = GetKey();
		while (true)
		{
			while (_kbhit())
			{
				int key = _getch();
				if (key == 224 || key == 0) key = GetKey();
				if (key == ESC) return;
				if (key == F1) ThongKeHD_Ngay(ds);
			}
		}
	}
}
//*************************MAIN******************************
int main()
{
	int chon;
	LISTVT root = NULL;
	LISTNV ds;
	ds.n = 0;
	LISTVT tree;
	InitTree(tree);
	DocFileVatTu(tree);
	DocFileNhanVien(ds);
	DocFileHoaDon(ds);
	DocFileCTHD(ds);
	do
	{
		chon = MenuDong(MenuCha, sodong);
		system("cls");
		switch(chon)
 		{
			case 1:
				int chon1;
				do
				{
					chon1 = MenuDong(Menu1, sodong);
					system("cls");
					switch (chon1)
					{
						case 1:
							ThemVT(tree);
							break;
						case 2:
							XoaVT(tree, ds);
							break;
						case 3:
							SuaVT(tree);
							break;
						case 4:
							XemDSVT(tree);
							break;
						case sodong1 :
							break;
					}
				}
				while(chon1 != sodong1);
				break;
			case 2:
				InDSVTTK_Ten(tree);
				break;
			case 3:
				int chon3;
				do
				{
					chon3 = MenuDong(Menu3, sodong);
					system("cls");
					switch (chon3)
					{
						case 1:
							ThemNV(ds);
							break;
						case 2:
							XoaNV(ds);
							break;
						case 3:
							SuaNV(ds);
							break;
						case 4:
							InDSNV_TenHo(ds);
							break;
						case sodong3:
							break;
					}
				}
				while (chon3 != sodong3);
				break;
			case 4:
				InDSNV_TenHo(ds);
				break;
			case 5:
				{
					gotoxy(50, 0);			cout << "--------HOA DON--------";
					gotoxy(107, 0);			cout << "ENTER : Chon";
					gotoxy(7, 3);			cout << "Ma nhan vien : ";
					InDSNV_HD(ds);
					char *manv = new char[10];
					manv = NhapMa(22, 3, 10, 0, false);
					if(KiemTraMaNV(ds, manv) == -1)
					{
						ThongBao("Khong co nhan vien nay !", 7, 5);
						break;
					}
					int vitrinv = ViTriNV(ds, manv); //tra ve nhan vien nay
					system("cls");
					InDSHD(ds.dsnv[vitrinv]->nodehd);
					gotoxy(50, 0);			cout << "--------HOA DON--------";
					gotoxy(7, 3);			cout << "Ma nhan vien : " << manv;
					gotoxy(26, 3);			cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
					gotoxy(107, 0);			cout << "F1    : Them HD";
					gotoxy(107, 1);			cout << "F2    : Nhap CTHD";
					gotoxy(107, 2);			cout << "F3    : Xem CTHD";
					gotoxy(107, 3);			cout << "ESC   : Thoat";
					bool flag = true;
					while (flag)
					{
						while (_kbhit())
						{
							int chon = _getch();
							if (chon == 224) chon = _getch();
							if (chon == 0) chon = _getch();
							switch (chon)
							{
							case F1:
								system("cls");
								gotoxy(50, 0);		cout << "--------HOA DON--------";
								gotoxy(107, 0);		cout << "ENTER : Chon";
								gotoxy(7, 3);		cout << "Ma nhan vien : " << manv;
								gotoxy(26, 3);		cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
								InDSHD(ds.dsnv[vitrinv]->nodehd);
								NhapHD(ds, tree, manv);
								//tra ve khi bao loi
								gotoxy(50, 0);		cout << "--------HOA DON--------";
								gotoxy(7, 3);		cout << "Ma nhan vien : " << manv;
								gotoxy(26, 3);		cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
								gotoxy(107, 0);		cout << "F1    : Them HD";
								gotoxy(107, 1);		cout << "F2    : Nhap CTHD";
								gotoxy(107, 2);		cout << "F3    : Xem CTHD";
								gotoxy(107, 3);		cout << "ESC   : Thoat";
								InDSHD(ds.dsnv[vitrinv]->nodehd);
								break;
							case F2:
								system("cls");
								gotoxy(50, 0);		cout << "--------HOA DON--------";
								gotoxy(107, 0);		cout << "ENTER : Chon";
								gotoxy(7, 3);		cout << "Ma nhan vien : " << manv;
								gotoxy(26, 3);		cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
					
								InDSHD(ds.dsnv[vitrinv]->nodehd);
								NhapSoHD_NhapCTHD(ds, tree, manv);
								break;
							case F3:
								system("cls");
								gotoxy(50, 0);		cout << "--------HOA DON--------";
								gotoxy(107, 0);		cout << "ENTER : Chon";
								gotoxy(7, 3);		cout << "Ma nhan vien : " << manv;
								gotoxy(26, 3);		cout << " - " << ds.dsnv[vitrinv]->Ho << " " << ds.dsnv[vitrinv]->Ten;
								
								InDSHD(ds.dsnv[vitrinv]->nodehd);
								XemCTHD(ds, manv);
								break;
							case ESC:
								flag = false;
								break;
							}
						}
					}
					break;
				}
			case 6:
				ThongKeHD_Ngay(ds);
				break;
		}
	}
	while(true);
	return 0;
}
