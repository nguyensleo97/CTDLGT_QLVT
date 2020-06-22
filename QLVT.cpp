#include <iostream>
#include <stdio.h>
#include<fstream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <Windows.h>
#include <mylib.h>
#include<time.h>
#include <cmath>

using namespace std;

const int MAXNV = 500;
const int MAXVT = 500;
const int sodong = 9;
const int sodong1 = 5;
const int sodong3 = 5;
const int cot = 2;
const int dong = 6;
const int Up = 72;
const int Down = 80;
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
	NODECTHD nodecthd;//con tro cthd
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
	NODEHD nodehd;//con tro dshd
};
struct ListNhanVien
{
	int n; //so luong nhan vien
	NhanVien *dsnv[MAXNV];
};
typedef struct ListNhanVien LISTNV;

/***************************************************GIAO DIEN******************************************************/
void Normal(){
	SetColor(15);
	SetBGColor(0);
}

void HighLight(){
	SetColor(15);
	SetBGColor(1);
}

int GetKey()
{	
	char key;
	key = getch();
	if(key==-32 || key==0)
	return -getch();
	else return key;
}

char MenuCha[sodong][50] = {  "1. Vat tu",
							  "2. In danh sach vat tu ton kho",
							  "3. Nhan vien",
							  "4. In danh sach nhan vien ten ho",
							  "5. Hoa don",
							  "6. In hoa don",
							  "7. Thong ke hoa don trong khoang tg",
							  "8. In 10 vat tu doanh thu cao nhat",
							  "9. Thong ke doanh thu trong 1 thang" };

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
	int chon =0;
	int i;
	sodong = DemDongMenu(td);
	for ( i=0; i< sodong ; i++)
	{
		gotoxy(cot, dong +i);
		cout << td[i];
	}
	HighLight();
	gotoxy(cot,dong+chon);
	cout << td[chon];
	char kytu;
	do
	{
		kytu = getch();
		if (kytu == 0) kytu = getch();
		switch (kytu)
		{
			case Up:
				if (chon+1 >1)
				{
					Normal();
					gotoxy(cot,dong+chon);
					cout << td[chon];
					chon --;
					HighLight();
					gotoxy(cot,dong+chon);
					cout << td[chon];
				}
				break;
			case Down:
				if (chon + 1 <sodong)
				{
					Normal();
					gotoxy(cot,dong+chon);
					cout << td[chon];
					chon ++;
					HighLight();
					gotoxy(cot,dong+chon);
					cout << td[chon];
				}
				break;
			case ENTER:
				return chon+1;
			case ESC:
				system("cls");
				return sodong;
		} 
	} while (1);
};

void GiaoDien_InDSVT (int y, int n, string c)
{
	for (int i = 8; i<= 110; i++)
	{
		gotoxy(i, 2 + y);
		cout << char(196);
		gotoxy(i, n + 1 + y);
		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(7, 2 + i + y);
		cout << char(179);
		gotoxy(21, 2 + i + y);
		cout << char(179);
		gotoxy(81, 2 + i + y);
		cout << char(179);
		gotoxy(95, 2 + i + y);
		cout << char(179);
		gotoxy(110, 2 + i + y);
		cout << char(179);
	}
	gotoxy(42, y);
	cout << c;
	gotoxy(10, 2 + y);
	cout << "Ma Vat Tu";
	gotoxy(45, 2 + y);
	cout << "Ten Vat Tu";
	gotoxy(83, 2 + y);
	cout << "Don vi tinh";
	gotoxy(97, 2 + y);
	cout << "So Luong Ton";
}

void GiaoDien_InDSNV(int y, int n, string c)
{
	for (int i = 8; i <= 98; i++)
	{
		gotoxy(i, 2 + y);
		cout << char(196);
		gotoxy(i, n + 1 + y);
		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(8, 2 + i + y);
		cout << char(179);
		gotoxy(28, 2 + i + y);
		cout << char(179);
		gotoxy(58, 2 + i + y);
		cout << char(179);
		gotoxy(78, 2 + i + y);
		cout << char(179);
		gotoxy(98, 2 + i + y);
		cout << char(179);
	}
	gotoxy(38, 0 + y);
	cout << c;
	gotoxy(13, 2 + y);
	cout << "Ma Nhan Vien";
	gotoxy(43, 2 + y);
	cout << "Ho";
	gotoxy(67, 2 + y);
	cout << "Ten";
	gotoxy(86, 2 + y);
	cout << "Phai";
}

void GiaoDien_InHD(int y, int n, string c)
{
	for (int i = 6; i <= 56; i++)
	{
		gotoxy(i, 2 + y);
		cout << char(196);
		gotoxy(i, n + 1 + y);
		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(6, 2 + i + y);
		cout << char(179);
		gotoxy(30, 2 + i + y);
		cout << char(179);
		gotoxy(47, 2 + i + y);
		cout << char(179);
		gotoxy(56, 2 + i + y);
		cout << char(179);
	}
	gotoxy(17, 0 + y);
	cout << c;
	gotoxy(14, 2 + y);
	cout << "So Hoa Don";
	gotoxy(35, 2 + y);
	cout << "Ngay Lap";
	gotoxy(50, 2 + y);
	cout << "Loai";
}

void GiaoDien_LapHD(int y, int n, string c)
{
	for (int i = 6; i <= 56; i++)
	{
		gotoxy(i, 2 + y);
		cout << char(196); //ngang
		gotoxy(i, n + 1 + y);
		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(6, 2 + i + y);
		cout << char(179); //doc
		gotoxy(30, 2 + i + y);
		cout << char(179);
		gotoxy(47, 2 + i + y);
		cout << char(179);
		gotoxy(56, 2 + i + y);
		cout << char(179);
	}
	gotoxy(20, 0 + y);
	cout << c;
	gotoxy(14, 2 + y);
	cout << "So Hoa Don";
	gotoxy(35, 2 + y);
	cout << "Ngay Lap";
	gotoxy(50, 2 + y);
	cout << "Loai";
}

void GiaoDien_LapCTHD(int y, int n, string c)
{
	for (int i = 60; i <= 110; i++)
	{
		gotoxy(i, 2 + y);
		cout << char(196);
		gotoxy(i, n + 1 + y);
		cout << char(196);
	}
	for (int i = 0; i < n; i++)
	{
		gotoxy(60, 2 + i + y);
		cout << char(179);
		gotoxy(74, 2 + i + y);
		cout << char(179);
		gotoxy(87, 2 + i + y);
		cout << char(179);
		gotoxy(99, 2 + i + y);
		cout << char(179);
		gotoxy(110, 2 + i + y);
		cout << char(179);
	}
	gotoxy(70, 0 + y);
	cout << c;
	gotoxy(63, 2 + y);
	cout << "Ma vat tu";
	gotoxy(77, 2 + y);
	cout << "So luong";
	gotoxy(90, 2 + y);
	cout << "Don gia";
	gotoxy(103, 2 + y);
	cout << "%VAT";
}

void GiaoDien_ThongKeHD()
{
	gotoxy(25, 1);
	cout << "BANG THONG KE CAC HOA DON TRONG KHOANG THOI GIAN";
	gotoxy(25, 2);
	cout << "Tu ngay : ";
	gotoxy(55, 2);
	cout << "Den ngay : ";
	for (int i = 8; i <= 108; i++)
	{
		gotoxy(i, 5);
		cout << char(196);
		gotoxy(i, 34);
		cout << char(196);
	}
	for (int i = 0; i < 30; i++)
	{
		gotoxy(8, 5 + i);
		cout << char(179);
		gotoxy(28, 5 + i);
		cout << char(179);
		gotoxy(58, 5 + i);
		cout << char(179);
		gotoxy(78, 5 + i);
		cout << char(179);
		gotoxy(108, 5 + i);
		cout << char(179);
	}
	gotoxy(15, 5);
	cout << "So HD";
	gotoxy(35, 5);
	cout << "Ngay nhap";
	gotoxy(65, 5);
	cout << "LoaiHD";
	gotoxy(85, 5);
	cout << "Ho ten NV lap";
	gotoxy(105, 5);
	cout << "Tri gia hoa don";
}

void GiaoDien_ThongKeDT()
{
	gotoxy(20, 1);
	cout << "BANG THONG KE DOANH THU CUA NAM : ";
	for (int i = 8; i <= 78; i++)
	{
		gotoxy(i, 5);
		cout << char(196);
		gotoxy(i, 18);
		cout << char(196);
	}
	for (int i = 0; i < 14; i++)
	{
		gotoxy(8, 5 + i);
		cout << char(179);
		gotoxy(28, 5 + i);
		cout << char(179);
		gotoxy(78, 5 + i);
		cout << char(179);
	}
	gotoxy(15, 5);
	cout << "Thang";
	gotoxy(35, 5);
	cout << "Doanh thu";
}

//hien thi thong bao
void ThongBao(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
	Sleep(1500);
	gotoxy(x, y);
	clreol();
	gotoxy(x, y);
}

//nhap phai nhan vien
int ChiNhap0or1(int& x)
{
	int kq;
	while (true)
	{
		while (!_kbhit())
		{
			int key = _getch();
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
				else if (key == ESC)
				{
					system("cls");
					return -1;
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
				key = _getch();
			}
		}
	}
	return x;
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
void HienThiDauNhay()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

//xu ly nhap SLT
int ChiNhapSo(int &x)
{
	int kq;
	while (true)
	{
		while (!_kbhit())
		{
			int key = _getch();
			if (key != 224 && key != 0)
			{
				if (key >= 48 && key <= 57)
				{
					kq = key - 48;
					cout << kq;
					x = x * 10 + kq;
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
				else if (key == ESC)
				{
					system("cls");
					x = -1;
					return -1;
				}
//				else if(kq == max)
//				{
//					ThongBao("Qua so ki tu !", 5, 5)
//				}
			}
			else
			{
				key = _getch();
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
			key = _getch();
			if (key != 224)
			{
				if (key == 78 /*N*/ || key == 88 /*X*/ || key == 110 /*n*/ || key == 120/*x*/)
				{
					cout << (char)key;
					temp += (char)key;
				}
				else if (key == ENTER)
				{
					return temp;
				}
//				else if (key == 8)
//				{
//					cout << "\b" << " " << "\b";
//					temp.erase(temp.strlen() - 1, 1);
//				}
				else if (key == ESC)
				{
					return 0;
				}
			}
			else
			{
				key = _getch();
			}
		}
	}
	return temp;
}

//chuyen chu hoa
void ChuHoa(char *x)
{
	char a;
	for (int i = 0; i < strlen(x); ++i)
	{
		a = x[i];
		if(a >= 97 && a <= 122)
		{
			x[i] = a - 32;
		}
		else
		{
			x[i] = a;
		}
	}
}

//them chu so
void ThemChu(char* A, char kt, int &vt, int &dem)
{
	int l = strlen(A);
	A[l+1] = '\0';
	while(l != vt)
	{
		A[l] = A[l-1];
		l--;
	}
	A[vt]=kt;
	vt++;
	dem++;
}

//xoa chu so
void XoaChu(char* A, int &vt, int &dem)
{
	int l = strlen(A);
	for(int i = vt; i<l; i++)
	{
		A[i] = A[i+1];
	}
	A[l-1] = '\0';
	vt--;
	dem--;
}

//nhap ma
char *NhapMa(int x, int y, int length, int type, bool &check, bool isValue = false, bool isSpace = false)
{
	//isValue kiem tra co gia tri cua text khong
	//type = 0 => nhap ma + so
	//type = 1 => nhap so
	char *text = new char[length];// hung ket qua khi nhap lieu
	text[0] = '\0';
	int dem = 0, temp = 0;//temp vi tri hien tai trong mang char, dem la vi tri lon nhat cua chuoi nhap vao
	char key;
	gotoxy(x, y);
	while(check)
	{
		key = GetKey();
		if(key == ENTER && strlen(text) > 0)
		{
//			check=false;
			return text;
			
		}
		if(type == 0 && (key >= 65 && key <= 90) && (temp >= 0 && temp < length))
		{
			ThemChu(text, key, temp, dem);
			for(int i = 0; i <= length; i++)
			{
				gotoxy(x+i, y);
				cout << " ";
			} 
			gotoxy(x, y);
			cout << text;
		}
		if(type == 0 && (key >= 97 && key <= 122)  && (temp >= 0 && temp < length))
		{
			key -= 32;
			ThemChu(text, key, temp, dem);
			for(int i = 0; i <= length; i++)
			{
				gotoxy(x+i, y);
				cout << " ";
			} 
			gotoxy(x, y);
			cout << text;
		}
		if((key >= 48 && key <= 57) && (temp >= 0 && temp < length))
		{
			ThemChu(text, key, temp, dem);
			for(int i = 0; i <= length; i++)
			{
				gotoxy(x+i, y);
				cout << " ";
			} 
			gotoxy(x, y);
			cout << text;
		}
		if(isSpace == true && key == SPACE && (temp >= 0 && temp < length))
		{
			ThemChu(text, ' ', temp, dem);
			for(int i = 0; i <= length; i++)
			{
				gotoxy(x+i, y);
				cout << " ";
			} 
			gotoxy(x, y);
			cout << text;
		}
		if(key == BACKSPACE && temp>0)
		{
			int pos = temp - 1;
			XoaChu(text, pos , dem);
			for(int i=0; i <= length; i++)
			{
				gotoxy(x+i, y);
				cout << " ";
			} 
			gotoxy(x, y);
			cout << text;
			temp--;
		}
//		if(key == ESC)
//		{
//			check = false;
//		}
		if(key == TAB && isValue == true)
		{
			return NULL;
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

//int NamNhuan(int nam)
//{
//	return(nam % 4 == 0 && nam % 100 != 0 || nam % 400 == 0) ? 1 : 0;
//}
//
//int Thang[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

//int TongNgayTuNam2000(int nam) //tinh tu ngay 1/1/2000 den 31/12/nam
//{
//	int tong = 0;
//	for (int i = 2000; i < nam; i++)
//	{
//		tong = tong + 365;
//		tong = tong + NamNhuan(i);
//	}
//	return tong;
//}

//int TongSoNgay (DateTime date)
//{
//	int tong = 0;
//	for (int t = 1; t < date.thang; t++)
//	{
//		tong = tong + Thang[t];
//		if (t == 2)
//		{
//			tong = tong + NamNhuan(date.nam);
//		}
//	}
//	tong = tong + date.ngay;
//	tong = tong + TongNgayTuNam2000(date.nam);
//	return tong;
//}

//int CheckNgay(DateTime date) {
//	int ngay = date.ngay;
//	int thang = date.thang;
//	int nam = date.nam;
//
//	int check = 0;
//	int maxDay = 0;
//
//	if (thang > 12) return 1;
//	switch (thang)
//	{
//	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
//		maxDay = 31;
//		break;
//	case 4: case 6: case 9: case 11:
//		maxDay = 30;
//		break;
//	case 2:
//		if (NamNhuan(nam) == 1) maxDay = 29;
//		else maxDay = 28;
//		break;
//	}
//
//	if (ngay > maxDay) return 1;
//
//	return 0;
//}
//
////cau g: thong ke hoa don trong 1 khoang thoi gian tu ngay...den ngay...
//int SoSanh2Ngay(DateTime date1, DateTime date2) {
//	return ((TongSoNgay(date1) - TongSoNgay(date2)) >= 0) ? 0 : 1; // giai thich :
//}//neu date1 >= date2 : return 0


//****************************************************XU LY FILE***********************************************************
//khoi tao cay nhi phan
void InitTree(LISTVT &root)
{
	root = NULL;
}

//duyet cay NLR
void Preorder (LISTVT tree)
{
	if(tree!= NULL)
	{
		//cout << "danh sach : " << tree->vt.MaVT << "\t" << tree->vt.TenVT << "\t" << tree->vt.DVT << "\t" << tree->vt.SLT;
		Preorder(tree->pLeft);
		Preorder(tree->pRight);
	}
}

//xu ly them vat tu
void InsertVatTu(LISTVT &tree, VatTu vt)
{	
	if(tree == NULL)// neu rong thi de quy xuong duoi
	{
		ListVatTu *p = new ListVatTu;//khoi tao node listvattu them vao cay
		p->vt = vt;
		p->pLeft = p->pRight = NULL;
		tree = p;//p chinh la node goc <=> vt chinh la node goc
	}
	else
	{
		if(strcmp(tree->vt.MaVT, vt.MaVT) > 0)
		{
			InsertVatTu(tree->pLeft,vt);
		}
		else
		{
			InsertVatTu(tree->pRight,vt);
		}
	}
}

//ghi file vat tu
void GhiFileVatTu_NLR(ListVatTu *root, ofstream &f)//phai co &f de tranh loi ios_base is private
{
	if(root!= NULL)
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
		getline(f,data);
		if(data.size() == 0)
		{
			break;//Da co file nhung chua co du lieu
		} 
		strcpy(vt.MaVT,data.c_str());
		getline(f,data);		strcpy(vt.TenVT,data.c_str());
		getline(f,data);		strcpy(vt.DVT,data.c_str());
		f >> vt.SLT;
		f.ignore();
		InsertVatTu(root,vt);
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
		getline(f,data);
		if(data.size() == 0) break;
							strcpy(nv.MaNV, data.c_str());
		getline(f,data);	strcpy(nv.Ho, data.c_str());
		getline(f,data);	strcpy(nv.Ten, data.c_str());
		f >> nv.Phai;
		f.ignore(); //bo ki tu dau tien
		
		ds.dsnv[ds.n] = new NhanVien;
		strcpy(ds.dsnv[ds.n]->MaNV,nv.MaNV);
		strcpy(ds.dsnv[ds.n]->Ho,nv.Ho);
		strcpy(ds.dsnv[ds.n]->Ten,nv.Ten);		
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
	for(int i=0; i<ds.n; i++)
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
		else if (strcmp(tree->vt.MaVT,vt.MaVT) > 0)
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
	if (strcmp(tree->vt.MaVT, mavt) == 0)
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
	if(tree!=NULL)
	{
		gotoxy(10, 11 + i);
		cout << tree->vt.MaVT;
		gotoxy(26, 11 + i);
		cout << tree->vt.TenVT;
		gotoxy(84, 11 + i);
		cout << tree->vt.DVT;
		gotoxy(98, 11 + i);
		cout << tree->vt.SLT;

		i++;
		InDSVT(tree->pLeft, i);
		InDSVT(tree->pRight, i);
	}
	AnDauNhay();
}

//lay danh sach vt do ra mang
VatTu* getDSVT (LISTVT &tree, VatTu vt[], int &n)
{
	if (tree != NULL)
	{
		if (tree->vt.SLT != 0)
		{
			strcpy(vt[n].MaVT,tree->vt.MaVT);
			strcpy(vt[n].TenVT,tree->vt.TenVT);
			strcpy(vt[n].DVT,tree->vt.DVT);
			vt[n].SLT = tree->vt.SLT;
			n++;
		}
		getDSVT(tree->pLeft, vt, n);
		getDSVT(tree->pRight, vt, n);
	}
	return vt;
}

//sap xep theo ma vat tu de xem
VatTu* SX_MaVT (VatTu vt[], int &n)
{
	VatTu x;
	for (int i=0; i<n; i++)
	{
		for(int j=n-1; j>=i; j--)
		{
			if(strcmp(vt[i].MaVT,vt[j].MaVT) == 1)
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
	int key;
	if ( tree == NULL)
	{
		ThongBao("Danh sach rong !", 7, 5);
		return;
	}
	GiaoDien_InDSVT(0, 30, "  -----DANH SACH VAT TU-----                              ESC: Thoat");
	VatTu vt[MAXVT];
	int n = 0;
	getDSVT(tree, vt, n);
	SX_MaVT(vt, n);
	for (int i = 0; i < n; i++)
	{
		gotoxy(10, 3 + i);
		cout << vt[i].MaVT;
		gotoxy(26, 3 + i);
		cout << vt[i].TenVT;
		gotoxy(84, 3 + i);
		cout << vt[i].DVT;
		gotoxy(98, 3 + i);
		cout << vt[i].SLT;
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
//	bool check;
	int x = 0;
	int x1 = 0;
	system("cls");
	InDSVT(tree, x);
	while(true)
	{
		VatTu vt;
		GiaoDien_InDSVT(0, 3, "  -----NHAP VAT TU-----");
		HienThiDauNhay();
		
		bool kt = true;
		char *mavt;
		mavt = new char[10];
		mavt = NhapMa(10, 3, 10, 0, kt, false, false);
		strcpy(vt.MaVT, mavt);
//		if(!check) {return;}

		if(TimKiemMaVT(tree, vt) != NULL)
		{
			ThongBao("Da co vat tu nay roi !", 7, 5);
//			system("cls");
//			InDSVT(tree,x1);
//			continue;
			return;
		}

		char *tenvt;
		tenvt = new char[50];
		tenvt = NhapMa(26, 3, 50, 0, kt, false, true);
		strcpy(vt.TenVT, tenvt);
//		if(!check) {return;}
		
		char *dvt;
		dvt = new char[10];
		dvt = NhapMa(84, 3, 10, 0, kt, false, false);
		strcpy(vt.DVT, dvt);
//		if(!check) {return;}
		
		gotoxy(98, 3);
		vt.SLT = 0;
		ChiNhapSo(vt.SLT);
		
		InsertVatTu(tree,vt);
		GhiFileVatTu(tree);
		ThongBao("Them vat tu thanh cong !", 7, 5);
		return;
	}
}

//_____________________XOA VAT TU_____________________
//xu ly xoa vat tu
void DeleteVatTu(LISTVT &tree, VatTu vt)
{
	if (tree == NULL)
	{
		return;
	}
	if (strcmp(tree->vt.MaVT,vt.MaVT) > 0)
	{
		return DeleteVatTu(tree->pLeft, vt);
	}
	else if (strcmp(tree->vt.MaVT,vt.MaVT) < 0)
		{
			return DeleteVatTu(tree->pRight, vt);
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
			ListVatTu* x = tree->pLeft;
			while (x->pRight != NULL)
			{
				x = x->pRight;
			}
			tree->vt = x->vt;
			DeleteVatTu(tree->pLeft, x->vt);
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
			ThongBao("Danh sach vat tu rong !", 7, 5);
			return;
		}
		int x = 0;
		system("cls");
		InDSVT(tree,x);
		HienThiDauNhay();
		gotoxy(7,3);
		cout << "Nhap ma vat tu can xoa : ";
	
		bool kt = true;
		char *mavt;
		mavt = new char[10];
		mavt = NhapMa(32, 3, 10, 0, kt, false, false);
		strcpy(vt.MaVT, mavt);
		
		ListVatTu* node;
		node = TimKiemMaVT(tree,vt);
		
		if(node == NULL)
		{
			ThongBao("Khong tim thay vat tu da nhap !", 7, 5);
//			system("cls");
//			continue;
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
		DeleteVatTu(tree,vt);
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
		HienThiDauNhay();
		gotoxy(7,3);
		cout << "Nhap ma vat tu can sua : ";
		bool kt = true;
		char *mavt;
		mavt = new char[10];
		mavt = NhapMa(32, 3, 10, 0, kt, false, false);
		strcpy(vt.MaVT, mavt);

		if(TimKiemMaVT(tree,vt) == NULL)
		{
			ThongBao("Khong co vat tu nay !", 7, 5);
//			system("cls");
//			continue;
			return;
		}
		ListVatTu *p = TimKiemMaVT(tree,vt);
		
		if (p != NULL)
		{
			system("cls");
			GiaoDien_InDSVT(0, 3, "---SUA THONG TIN VAT TU---");
			int x1 = 0;
			InDSVT(tree,x1);
			gotoxy(10,3);
			cout << p->vt.MaVT;
			gotoxy(98,3);
			cout << p->vt.SLT;
			HienThiDauNhay();
			
			char *tenvt;
			tenvt = new char[50];
			tenvt = NhapMa(26, 3, 50, 0, kt, false, true);
			strcpy(vt.TenVT, tenvt);
//			if(!check) {return;}

			char *dvt;
			dvt = new char[10];
			dvt = NhapMa(84, 3, 10, 0, kt, false, false);
			strcpy(vt.DVT, dvt);
//			if(!check) {return;}
			
			strcpy(p->vt.TenVT,vt.TenVT);
			strcpy(p->vt.DVT,vt.DVT);
		}
		GhiFileVatTu(tree);
		ThongBao("Sua vat tu thanh cong !", 7, 6);
//		system("cls");
		return;
	}
}

//_________________SAP XEP VAT TU____________________
//sap xep theo ten vat tu----bubble sort
VatTu* SX_TenVT (VatTu vt[], int &n)
{
	VatTu x;
	for (int i=0; i<n; i++)
	{
		for(int j=n-1; j>=i; j--)
		{
			if(strcmp(vt[i].TenVT,vt[j].TenVT) == 1)
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
	int key;
	if ( tree == NULL)
	{
		ThongBao("Danh sach rong !", 9, 5);
		return;
	}
	GiaoDien_InDSVT(0, 30, "---DANH SACH VAT TU TON KHO THEO TEN---                   ESC: Thoat");
	VatTu vt[MAXVT];
	int n = 0;
	getDSVT(tree, vt, n);
	SX_TenVT(vt, n);
	for (int i = 0; i < n; i++)
	{
		gotoxy(10, 3 + i);
		cout << vt[i].MaVT;
		gotoxy(26, 3 + i);
		cout << vt[i].TenVT;
		gotoxy(84, 3 + i);
		cout << vt[i].DVT;
		gotoxy(98, 3 + i);
		cout << vt[i].SLT;
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
		ThongBao("Danh sach rong ! ", 9, 6);
		return;
	}
	GiaoDien_InDSNV(8,30, "---DANH SACH NHAN VIEN---");
	for (int i = 0; i<ds.n; i++)
	{
		gotoxy(15, 11 + i);
		cout << ds.dsnv[i]->MaNV;
		gotoxy(35, 11 + i);
		cout << ds.dsnv[i]->Ho;
		gotoxy(65, 11 + i);
		cout << ds.dsnv[i]->Ten;
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
	for(int i=0; i<ds.n; i++)
	{
		if(strcmp(ds.dsnv[i]->MaNV,manv) == 0)
		{
			return 1;
		}
	}
	return -1;
}

//ham tra ve vi tri nv trong dstt la 1 mang con tro
int ViTriNV(LISTNV &ds, char manv[])
{
	for(int i=0; i<ds.n; i++)
	{
		if(strcmp(ds.dsnv[i]->MaNV,manv) == 0)
		{
			return i;
		}
	}
	return -1;
}

//sap xep ds nhan vien theo ma nhan vien de xem
void SX_MaNV(LISTNV &ds)
{
	NhanVien *x;///giai thich
	for(int i = 0; i<ds.n-1 ;i++)
	{
		for(int j = i+1; j<ds.n ;j++)
		{
			if(strcmp(ds.dsnv[i]->MaNV, ds.dsnv[j]->MaNV) > 0)
			{
				x = ds.dsnv[i];
				ds.dsnv[i] = ds.dsnv[j];
				ds.dsnv[j] = x;
			} 
		}
	}
}

//xem danh sach nhan vien sap xep theo ma nhan vien
void XemDSNV_MaNV(LISTNV ds)
{
	int key;
	if(EmptyDSNV(ds) == 1)
	{
		ThongBao("Danh sach rong ! ", 9, 5);
		return;
	}
	GiaoDien_InDSNV(0, 30, "---DANH SACH NHAN VIEN---                         ESC: Thoat");
	SX_MaNV(ds);
	for (int i = 0; i < ds.n; i++)
	{
		gotoxy(15, 3 + i);
		cout << ds.dsnv[i]->MaNV;
		gotoxy(35, 3 + i);
		cout << ds.dsnv[i]->Ho;
		gotoxy(65, 3 + i);
		cout << ds.dsnv[i]->Ten;
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

//___________________THEM NHAN VIEN___________________
//ham them nhan vien
void ThemNV(LISTNV &ds)
{
	gotoxy(80,5);
	cout << "Phai: 1-NAM   0-NU";
	NhanVien nv;
	if(FullDSNV(ds) == 1)
	{
		ThongBao("Danh sach day !", 9, 5);
		return;
	}
	int ktra = 0;
	for ( ;ds.n<MAXNV; )
	{
		InDSNV(ds);
		GiaoDien_InDSNV(0, 3, "-----NHAP NHAN VIEN-----");
		HienThiDauNhay();
		bool kt = true;
		char *manv;
		manv = new char[10];
		manv = NhapMa(15, 3, 10, 0, kt, false, false);
		strcpy(nv.MaNV, manv);
		if(KiemTraMaNV(ds, manv) == 1)
		{
			ThongBao("Da co nhan vien nay roi !", 9, 6);
//			system("cls");
//			ThemNV(ds);
//			continue;
			return;
		}
		char *ho;
		ho = new char[20];
		ho = NhapMa(35, 3, 20, 0, kt, true, true);
		strcpy(nv.Ho, ho);
		
		char *ten;
		ten = new char[10];
		ten = NhapMa(65, 3, 10, 0, kt, false, false);
		strcpy(nv.Ten, ten);

		gotoxy(85, 3);
		int Phai = 0;
		ChiNhap0or1(nv.Phai);
		
		ds.dsnv[ds.n] = new NhanVien;
		strcpy(ds.dsnv[ds.n]->MaNV, nv.MaNV);
		strcpy(ds.dsnv[ds.n]->Ho, nv.Ho);
		strcpy(ds.dsnv[ds.n]->Ten, nv.Ten);
		ds.dsnv[ds.n]->Phai = nv.Phai;
		ds.dsnv[ds.n]->nodehd = NULL;
		
		ThongBao("Them nhan vien thanh cong !", 9, 6);
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
		NhanVien nv;
		if(EmptyDSNV(ds) == 1)
		{
			ThongBao("Danh sach rong !", 9, 5);
			return;
		}
		InDSNV(ds);
		HienThiDauNhay();
		
		gotoxy(9, 3);
		cout << "Nhap ma nhan vien can xoa : ";
		bool kt = true;
		char *manv;
		manv = new char[10];
		manv = NhapMa(37, 3, 10, 0, kt, false, false);
		if(KiemTraMaNV(ds, manv) != 1)
		{
			ThongBao("Khong co nhan vien nay !", 9, 5);
//			system("cls");
//			continue;
			return;
		}
		//ktra nhan vien: neu da lap hoa don thi ko xoa duoc
		int vitri = ViTriNV(ds,manv);
		for(NODEHD p = ds.dsnv[vitri]->nodehd; p != NULL; p = p->pNext)
		{
			if(p != NULL)
			{
				ThongBao("Nhan vien da lap hoa don. KHONG XOA DUOC !", 9, 5);
				return;
			}
		}
		//xu ly
		for (int i = vitri; i < ds.n; i++)
		{
			ds.dsnv[i] = ds.dsnv[i + 1];
		}
		ds.n--;
		
		GhiFileNhanVien(ds);
		ThongBao("Xoa nhan vien thanh cong !", 9, 6);
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
			ThongBao("Danh sach rong !", 9, 5);
			return;
		}
		InDSNV(ds);
		HienThiDauNhay();
		gotoxy(9, 3);
		cout << "Nhap ma nhan vien can sua : ";
		bool kt = true;
		char *manv;
		manv = new char[10];
		manv = NhapMa(37, 3, 10, 0, kt, false, false);
		strcpy(nv.MaNV, manv);
		
		int ktra = ViTriNV(ds,manv);
		if(KiemTraMaNV(ds, manv) != 1)
		{
			ThongBao("Khong co nhan vien nay !", 9, 5);
//			system("cls");
//			continue;
			return;
		}
		else
		{
			system("cls");
			InDSNV(ds);
			GiaoDien_InDSNV(0,3, " -----SUA NHAN VIEN-----");
			gotoxy(15, 3);
			cout << ds.dsnv[ktra]->MaNV;
			
			char *ho;
			ho = new char[20];
			ho = NhapMa(35, 3, 20, 0, kt, true, true);
			strcpy(nv.Ho, ho);
//			if(strcmp(nv.Ho, "") == 0)
//			{
//				ThongBao("Hay nhap Ho nhan vien !", 9, 6);
//				continue;
//			}
			char *ten;
			ten = new char[10];
			ten = NhapMa(65, 3, 10, 0, kt, false, false);
			strcpy(nv.Ten, ten);
//			if(strcmp(nv.Ho, "") == 0)
//			{
//				ThongBao("Hay nhap Ho nhan vien !", 9, 6);
//				continue;
//			}
			int Phai;
			gotoxy(85, 3);
			ChiNhap0or1(nv.Phai);
			
			//xu ly them thong tin moi nhap de sua
			strcpy(ds.dsnv[ktra]->Ho, nv.Ho);
			strcpy(ds.dsnv[ktra]->Ten,nv.Ten);
			ds.dsnv[ktra]->Phai = nv.Phai;
		}
		GhiFileNhanVien(ds);
		ThongBao("Sua nhan vien thanh cong !", 9, 6);
		return;
	}
}

//________________SAP XEP NHAN VIEN_________________
//sap xep ds nhan vien theo ten ho___bubble sort
void SX_TenHoNV(LISTNV &ds)
{
	NhanVien *x;///giai thich
	for(int i = 0; i<ds.n-1 ;i++)
	{
		for(int j = i+1; j<ds.n ;j++)
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
		gotoxy(15, 3 + i);
		cout << ds.dsnv[i]->MaNV;
		gotoxy(35, 3 + i);
		cout << ds.dsnv[i]->Ho;
		gotoxy(65, 3 + i);
		cout << ds.dsnv[i]->Ten;
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
		for(; last->pNext != NULL; last = last->pNext);
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
	int vitri;
	while (!f.eof() && manv != NULL)
	{
		HoaDon hd;
		getline(f,data);
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
		
		//xu ly danh sach chi tiet hoa don
		hd.nodecthd = NULL;
		
		vitri = ViTriNV(ds, manv);
		InsertHD(ds.dsnv[vitri]->nodehd, TaoNodeHD(hd));
		
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
		if(ds.dsnv[i]->nodehd != NULL)//ktra nv da lap hoa don chua
		{
			nodeHD = ds.dsnv[i]->nodehd;//da lap roi -> gan node tam
		}
		else
		{
			nodeHD = NULL;//chua lap hoa don
		}
		while(nodeHD != NULL)
		{
			f << ds.dsnv[i]->MaNV << endl;
			f << nodeHD->hd.SoHD << endl;
			f << nodeHD->hd.NgayLap.Ngay << endl;
			f << nodeHD->hd.NgayLap.Thang << endl;
			f << nodeHD->hd.NgayLap.Nam << endl;
			f << nodeHD->hd.Loai << endl;
			
			nodeHD = nodeHD->pNext;
		}
	}
	f.close();
}

//in danh sach hoa don
void InDSHD(NODEHD first)
{
	AnDauNhay();
	GiaoDien_InHD(12, 15, "-----DANH SACH HOA DON-----");
	int k = 0;
	for(NODEHD p = first; p != NULL; p = p->pNext)
	{
		int demvt = 0;
//		for(int i = 0; i < p->hd.nodecthd; i++)
//		{
//			demvt++;
//		}
		gotoxy(9, 15 + k);
		cout << p->hd.SoHD;
		gotoxy(32, 15 + k);
		cout << p->hd.NgayLap.Ngay << " / " << p->hd.NgayLap.Thang << " / " << p->hd.NgayLap.Nam;
		gotoxy(50, 15 + k);
		if (p->hd.Loai == 'n' || p->hd.Loai == 'N')
		{
			cout << "NHAP";// << demvt;
		}
		if (p->hd.Loai == 'x' || p->hd.Loai == 'X')
		{
			cout << "XUAT";// << demvt;
		}
		k++;
	}
}

//void NhapCTHD(LISTNV &ds, LISTVT tree, NODECTHD &first, char loai, char sohd[20], char manv[10]);

//xu ly nhap hoa don
void NhapHD(LISTNV &ds, LISTVT tree, char manv[10])
{
	GiaoDien_LapHD(6, 3, "-----LAP HOA DON-----");
	HoaDon hd;
	gotoxy(9, 9);
	char sohd[20];
	char loai;
	cin.getline(sohd, 21);
	ChuHoa(sohd);
	
	if(strcmp(sohd,"") == 0)
	{
		ThongBao("So hoa don khong duoc bo trong !", 7, 11);
		system("cls");
		return;
	}
	
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
	gotoxy(32, 9);
	cout << date.Ngay;
	gotoxy(35, 9);
	cout << "/";
	gotoxy(37, 9);
	cout << date.Thang;
	gotoxy(39, 9);
	cout << "/";
	gotoxy(41, 9);
	cout << date.Nam;
	gotoxy(51, 9);
	hd.Loai = ChiNhapNorX(loai);
	
	strcpy(hd.SoHD, sohd);
	hd.NgayLap = date;
	hd.Loai = loai;
	
	NODECTHD dsCTHD;
	hd.nodecthd = dsCTHD;
	hd.nodecthd = NULL;
	
	int vitrinv = ViTriNV(ds,manv);		
			
	InsertHD(ds.dsnv[vitrinv]->nodehd, TaoNodeHD(hd));
	GhiFileHoaDon(ds);
	InDSHD(ds.dsnv[vitrinv]->nodehd);
//	NhapCTHD(ds, tree,ds.dsnv[vitrinv]->nodehd->hd.nodecthd, loai, ds.dsnv[vitrinv]->nodehd->hd.SoHD , manv);
//	clrscr();
//	for(NODECTHD p = ds.dsnv[vitrinv]->nodehd->hd.nodecthd; p != NULL; p = p->pNext)
//	{
//		cout << p->cthd.MaVT << endl;
//		cout << p->cthd.SoLuong << endl;
//		cout << p->cthd.DonGia << endl;
//		cout << p->cthd.VAT << endl;
//	}
//	system("pause");
	
	system("cls");
	return;
//	for (NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
//	{
//		if (strcmp(p->hd.SoHD,hd.SoHD) == 0)
//		{
//			NhapCTHD(ds, tree,p->hd.nodecthd, loai, p->hd.SoHD, manv);
//
//			clrscr();
//			for(NODECTHD p = ds.dsnv[vitrinv]->nodehd->hd.nodecthd; p != NULL; p = p->pNext)
//			{
//				cout << p->cthd.MaVT << endl;
//				cout << p->cthd.SoLuong << endl;
//				cout << p->cthd.DonGia << endl;
//				cout << p->cthd.VAT << endl;
//				
//			}
//			system("pause");
//		}
//	}
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
		for(; last->pNext != NULL; last = last->pNext);
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
		int vitrinv;
		vitrinv = ViTriNV(ds, manv);
		char sohd[20];
		getline(f, data);		strcpy(sohd, data.c_str());
		
		for(NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
		{
			if(strcmp(sohd, p->hd.SoHD) == 0)
			{
				CTHoaDon cthd;
				
				getline(f,data);		strcpy(cthd.MaVT, data.c_str());
				
				f >> cthd.SoLuong;
				f.ignore();
				f >> cthd.DonGia;
				f.ignore();
				f >> cthd.VAT;
				f.ignore();
				
				//xu ly
				InsertCTHD(p->hd.nodecthd, TaoNodeCTHD(cthd));
//				break;
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
//				while(nodeCTHD != NULL)
//				{
//					f << ds.dsnv[i]->MaNV << endl;
//					f << p->hd.SoHD << endl;
//					f << nodeCTHD->cthd.MaVT << endl;
//					f << nodeCTHD->cthd.SoLuong << endl;
//					f << nodeCTHD->cthd.DonGia << endl;
//					f << nodeCTHD->cthd.VAT << endl;
//
//					nodeCTHD = nodeCTHD->pNext;
//				}
			}
		}
	}
	f.close();
}

//in ds cthd
void InDSCTHD(NODECTHD first)
{
	AnDauNhay();
	GiaoDien_LapCTHD(12, 15, "DANH SACH CHI TIET HOA DON");
	int k = 0;
	for(NODECTHD p = first; p != NULL; p = p->pNext)
	{
		gotoxy(65, 15 + k);
		cout << p->cthd.MaVT;
		gotoxy(75, 15 + k);
		cout << p->cthd.SoLuong;
		gotoxy(90, 15 + k);
		cout << p->cthd.DonGia;
		gotoxy(105, 15 + k);
		cout << p->cthd.VAT;
		k++;
	}
}

//mang tam vat tu NLR
void MangTam_VT(ListVatTu *root, VatTu vt[], int &n)
{	
	if(root != NULL)
	{
		vt[n++] = root->vt;
		MangTam_VT(root->pLeft, vt, n);
		MangTam_VT(root->pRight, vt, n);
	}
}

//xem cthd
void XemCTHD(LISTNV &ds, char manv[10])
{
	NhanVien nv;
	while (true)
	{
		char sohd[20];
		gotoxy(7, 5);
		cout << "Nhap so hoa don can xem cthd : ";
		HienThiDauNhay();
		cin.getline(sohd, 21);
		ChuHoa(sohd);
		int vitrinv;
		vitrinv = ViTriNV(ds, manv);
		if(strcmp(sohd,"") == 0)
		{
			ThongBao("Khong duoc bo trong so hoa don !", 7, 7);
			system("cls");
			gotoxy(7, 3); cout << "Ma nhan vien : " << manv;
			InDSHD(ds.dsnv[vitrinv]->nodehd);
			gotoxy(70, 3);
			cout << "F1 : Nhap HD";
			gotoxy(70, 4);
			cout << "F2 : Nhap CTHD";
			gotoxy(70, 5);
			cout << "F3 : Xem CTHD";
			gotoxy(70, 6);
			cout << "ESC: Thoat";
			return;
		}
		for (NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
		{
			if (strcmp(p->hd.SoHD, sohd) == 0)
			{
				AnDauNhay();
				InDSCTHD(p->hd.nodecthd);
				return;
			}
		}
		ThongBao("Khong co so hoa don nay !", 7, 7);
		system("cls");
		gotoxy(7, 3); cout << "Ma nhan vien : " << manv;
		InDSHD(ds.dsnv[vitrinv]->nodehd);
		gotoxy(70, 3);
		cout << "F1 : Nhap HD";
		gotoxy(70, 4);
		cout << "F2 : Nhap CTHD";
		gotoxy(70, 5);
		cout << "F3 : Xem CTHD";
		gotoxy(70, 6);
		cout << "ESC: Thoat";
		return;
	}
}

//ham nhap chi tiet hoa don
void NhapCTHD(LISTNV &ds, LISTVT tree, NODECTHD &first, char loai, char sohd[20], char manv[10])
{

	GiaoDien_LapCTHD(12, 3, "-----LAP CHI TIET HOA DON-----");
//	int k = 0;
//	for(NODECTHD p = first; p != NULL; p = p->pNext)
//	while(true)
	{
		VatTu vt;
		CTHoaDon cthd;
		char mavt[10];
		int soluong = 0;
		int dongia = 0;
		int vat = 0;
		
		gotoxy(65, 15);
		cin.getline(mavt, 9);
		ChuHoa(mavt);

//		bool kt = true;
//		char *mavt = new char[10];
//		mavt = NhapMa(9, 9, 20, 0, kt, false, false);
		strcpy(cthd.MaVT, mavt);
		
//		if(strcmp(mavt,"") == 0)
//		{
//			ThongBao("Hay nhap ma vat tu !", 7, 5);
//			system("cls");
//			return;
//		}
//		//trung ma vat tu trong cthd
//		if(strcmp(p->cthd.MaVT,mavt) == 0)
//		{
//			ThongBao("Cthd da co vat tu nay !", 7, 5);
//			system("cls");
//			return;
//		}
		gotoxy(75, 15);
		cthd.SoLuong = ChiNhapSo(soluong);
		gotoxy(90, 15);
		cthd.DonGia = ChiNhapSo(dongia);
		gotoxy(105, 15);
		cthd.VAT = ChiNhapSo(vat);
		
		strcpy(cthd.MaVT, mavt);
		cthd.SoLuong = soluong;
		cthd.DonGia = dongia;
		cthd.VAT = vat;
		
		int vitrinv = ViTriNV(ds, manv);
		ListVatTu *p1 = CheckMaVT(tree, mavt);
		
//		clrscr();
//		cout << p1->vt.MaVT << endl;
//		cout << p1->vt.TenVT << endl;
//		cout << p1->vt.DVT << endl;
//		cout << p1->vt.SLT << endl;
//		system("pause");
		
		if(p1 == NULL)
		{
			ThongBao("Khong co ma vat tu nay !", 7, 7);
			system("cls");
			gotoxy(7, 3); cout << "Ma nhan vien : " << manv;
			InDSHD(ds.dsnv[vitrinv]->nodehd);
			gotoxy(70, 3);
			cout << "F1 : Nhap HD";
			gotoxy(70, 4);
			cout << "F2 : Nhap CTHD";
			gotoxy(70, 5);
			cout << "F3 : Xem CTHD";
			gotoxy(70, 6);
			cout << "ESC: Thoat";
			return;
		}
		else
		{
			for(NODECTHD q = first; q != NULL; q = q->pNext)
			{
				if(strcmp(ds.dsnv[vitrinv]->nodehd->hd.nodecthd->cthd.MaVT, mavt) == 0)
				{
					ThongBao("Da nhap ma vat tu nay cho cthd !", 7, 7);
					system("cls");
					gotoxy(7, 3); cout << "Ma nhan vien : " << manv;
					InDSHD(ds.dsnv[vitrinv]->nodehd);
					gotoxy(70, 3);
					cout << "F1 : Nhap HD";
					gotoxy(70, 4);
					cout << "F2 : Nhap CTHD";
					gotoxy(70, 5);
					cout << "F3 : Xem CTHD";
					gotoxy(70, 6);
					cout << "ESC: Thoat";
					return;
				}
			}
		}
		if(loai == 'x' || loai == 'X')
		{
			if(cthd.SoLuong > p1->vt.SLT)
			{
				gotoxy(9, 2);
				cout << "Khong du vat tu de xuat, hien co : " << p1->vt.SLT << " vat tu";
				return;
			}
			if(cthd.SoLuong < p1->vt.SLT)
			{
				int sl = p1->vt.SLT - cthd.SoLuong;
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
			
//			clrscr();
//			cout << manv << endl;
//			cout << sohd << endl;
//			cout << p->cthd.MaVT << endl;
//			cout << p->cthd.SoLuong << endl;
//			cout << p->cthd.DonGia << endl;
//			cout << p->cthd.VAT << endl;
//			system("pause");
			
			GhiFileCTHD(ds);
			GhiFileVatTu(tree);
		}
		
		system("cls");
		gotoxy(7, 3); cout << "Ma nhan vien : " << manv;
		InDSHD(ds.dsnv[vitrinv]->nodehd);
		gotoxy(70, 3);
		cout << "F1 : Nhap HD";
		gotoxy(70, 4);
		cout << "F2 : Nhap CTHD";
		gotoxy(70, 5);
		cout << "F3 : Xem CTHD";
		gotoxy(70, 6);
		cout << "ESC: Thoat";
		return;
	}
}

//nhap cthd
void NhapSoHD_NhapCTHD(LISTNV &ds, LISTVT tree, char manv[10])
{
//	NhanVien nv;
	while (true)
	{
		char sohd[20];
		gotoxy(7, 5);
		cout << "Nhap so hoa don de them cthd : ";
		HienThiDauNhay();
		cin.getline(sohd, 21);
		ChuHoa(sohd);
		int vitrinv;
		vitrinv = ViTriNV(ds, manv);
		

		
		if(strcmp(sohd,"") == 0)
		{
			ThongBao("Hay nhap so hoa don de them cthd !", 7, 7);
			system("cls");
			gotoxy(7, 3); cout << "Ma nhan vien : " << manv;
			InDSHD(ds.dsnv[vitrinv]->nodehd);
			gotoxy(70, 3);
			cout << "F1 : Nhap HD";
			gotoxy(70, 4);
			cout << "F2 : Nhap CTHD";
			gotoxy(70, 5);
			cout << "F3 : Xem CTHD";
			gotoxy(70, 6);
			cout << "ESC: Thoat";
			return;
		}
		for (NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
		{
//			for(NODECTHD q = p; q != NULL; q = q->pNext)



//			clrscr();
//			cout << p->hd.SoHD << "\t" << sohd<<endl;
//			system("pause");

			
			if (strcmp(p->hd.SoHD, sohd) == 0)
			{
				AnDauNhay();
				NhapCTHD(ds, tree, p->hd.nodecthd, p->hd.Loai, sohd, manv);
//				system("cls");
				return;
			}
			
		}
		ThongBao("Khong co so hoa don nay !", 7, 7);
//			NhapCTHD_HD(ds, tree, p->hd.nodecthd, p->hd.Loai, p->hd.SoHD, manv);
			system("cls");
			gotoxy(7, 3); cout << "Ma nhan vien : " << manv;
			InDSHD(ds.dsnv[vitrinv]->nodehd);
			gotoxy(70, 3);
			cout << "F1 : Nhap HD";
			gotoxy(70, 4);
			cout << "F2 : Nhap CTHD";
			gotoxy(70, 5);
			cout << "F3 : Xem CTHD";
			gotoxy(70, 6);
			cout << "ESC: Thoat";
			return;
//		return;
	}
}
//*********************THONG KE************************
//*************************MAIN******************************
int main()
{
	bool check;
	int chon;
	int x = 0;
	
	LISTVT root = NULL;
	LISTNV listnv;
	listnv.n = 0;
	
	LISTVT tree;
	InitTree(tree);
	DocFileVatTu(tree);
	DocFileNhanVien(listnv);
	DocFileHoaDon(listnv);
	DocFileCTHD(listnv);
//	GhiFileCTHD(listnv);
	
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
							XoaVT(tree, listnv);
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
							ThemNV(listnv);
							break;
						case 2:
							XoaNV(listnv);
							break;
						case 3:
							SuaNV(listnv);
							break;
						case 4:
							XemDSNV_MaNV(listnv);
							break;
						case sodong3:
							break;
					}
				}
				while (chon3 != sodong3);
				break;
			case 4:
				InDSNV_TenHo(listnv);
				break;
			case 5:
				gotoxy(7, 3);
				char manv[10];
				cout << "Ma nhan vien : ";
				cin.getline(manv, 11);
				ChuHoa(manv);
				if(strcmp(manv,"") == 0)
				{
					ThongBao("Ma nhan vien !", 7, 5);
					break;
				}
//				bool kt = true;
//				char *manv;
//				manv = new char[10];
//				manv = NhapMa(22, 3, 20, 0, kt, false, false);
				
				if(KiemTraMaNV(listnv,manv) == -1)
				{
					ThongBao("Khong co nhan vien nay !", 7, 5);
					break;
				}
				
				int vitrinv;
				vitrinv = ViTriNV(listnv, manv); //tra ve nhan vien nay

//				if (vitrinv != -1)
//				{
//					if (p1->dsnv[vitrinv]->nodehd != NULL)
//					{
//						InDSHD(p1->dsnv[vitrinv]->nodehd);
//						gotoxy(30, 0);
//						cout << "Hien co " << demHDkVT(p1->dsnv[vitrinv]->nodehd) << " Hoa don khong co VT !";
//					}
//					else
//					{
//						BaoLoi("Danh sach dang trong !", 0, 1);
//					}
//				}
				gotoxy(70, 3);
				cout << "F1 : Nhap HD";
				gotoxy(70, 4);
				cout << "F2 : Nhap CTHD";
				gotoxy(70, 5);
				cout << "F3 : Xem CTHD";
				gotoxy(70, 6);
				cout << "ESC: Thoat";
				bool flag = true;
//				bool flg = true;
				while (flag)
				{
					while (_kbhit())
					{
						int chon = _getch();
//						if (chon == 224) chon = _getch();
//						if (chon == 0) chon = _getch();
						switch (chon)
						{
						case F1:
							InDSHD(listnv.dsnv[vitrinv]->nodehd);
							NhapHD(listnv, tree, manv);
							
							gotoxy(7, 3);
							cout << "Ma nhan vien : " << manv;
							gotoxy(70, 3);
							cout << "F1 : Nhap HD";
							gotoxy(70, 4);
							cout << "F2 : Nhap CTHD";
							gotoxy(70, 5);
							cout << "F3 : Xem CTHD";
							gotoxy(70, 6);
							cout << "ESC: Thoat";
							
							InDSHD(listnv.dsnv[vitrinv]->nodehd);								
							/*gotoxy(80, 3);
							cout << "F5: Xoa CTHD";*/
							
							//xoa chi tiet hoa don ms lap
							break;
						case F2:
							system("cls");
							gotoxy(7, 3);
							cout << "Ma nhan vien : " << manv;
							gotoxy(70, 3);
							cout << "F1 : Nhap HD";
							gotoxy(70, 4);
							cout << "F2 : Nhap CTHD";
							gotoxy(70, 5);
							cout << "F3 : Xem CTHD";
							gotoxy(70, 6);
							cout << "ESC: Thoat";
							
							InDSHD(listnv.dsnv[vitrinv]->nodehd);
							NhapSoHD_NhapCTHD(listnv, tree, manv);
							break;
						case F3:
							system("cls");
							gotoxy(7, 3);
							cout << "Ma nhan vien : " << manv;
							gotoxy(70, 3);
							cout << "F1 : Nhap HD";
							gotoxy(70, 4);
							cout << "F2 : Nhap CTHD";
							gotoxy(70, 5);
							cout << "F3 : Xem CTHD";
							gotoxy(70, 6);
							cout << "ESC: Thoat";
							
							InDSHD(listnv.dsnv[vitrinv]->nodehd);
							XemCTHD(listnv, manv);
							break;
						case ESC:
							flag = false;
							break;
						}
					}
				}	
		}
	}
	while(true);
	return 0;
}
