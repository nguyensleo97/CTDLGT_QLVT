#include <iostream>
#include <stdio.h>
#include<fstream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <Windows.h>
#include <mylib.h>
#include<time.h>

using namespace std;

const int MAXNV = 500;
const int MAXVT = 500;
const int sodong = 9;
const int sodong1 = 4;
const int sodong3 = 4;
const int sodong5 = 3;
const int cot = 2;
const int dong = 6;
const int Up = 72;
const int Down = 80;
const int SPACE = 32;
const int ENTER = 13;
const int ESC = 27;
const int BACKSPACE = 8;

/**********************************************KHAI BAO CAU TRUC**************************************************************/
struct Date
{
	int Ngay, Thang, Nam;
};

//---cthoadon--- danh sach lien ket don
struct CTHoaDon
{
	char MaVT[10];
	float SoLuong;
	float DonGia;
	float VAT;
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
	char Ho[40];
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

char MenuCha[sodong][50] = {  "1. Nhap vat tu",
							  "2. In danh sach vat tu ton kho",
							  "3. Nhap nhan vien",
							  "4. In danh sach nhan vien",
							  "5. Lap hoa don nhap/xuat",
							  "6. In hoa don",
							  "7. Thong ke hoa don trong khoang tg",
							  "8. In 10 vat tu doanh thu cao nhat",
							  "9. Thong ke doanh thu trong 1 thang" };

char Menu1[sodong1][50] = {  "1. Them vat tu",
							 "2. Xoa vat tu",
							 "3. Sua vat tu",
							 "4. Thoat" };
							
char Menu3[sodong3][50] = {	 "1. Them nhan vien",
							 "2. Xoa nhan vien",
							 "3. Sua nhan vien",
							 "4. Thoat" };
							 
char Menu5[sodong5][50] = {  "1. Nhap hoa don",
							 "2. Nhap chi tiet hoa don",
							 "3. Thoat" };
							 

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
			case 13:
				return chon+1;
			case 27:
				system("cls");
				return sodong;
		} 
	} while (1);
};

void GiaoDien_InDSVT (int y, int n, string c)
{
	for (int i = 8; i<= 98; i++)
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

	gotoxy(37, y);
	cout << c;
	gotoxy(15, 2 + y);
	cout << "Ma Vat Tu";
	gotoxy(38, 2 + y);
	cout << "Ten Vat Tu";
	gotoxy(63, 2 + y);
	cout << "Don Vi Tinh";
	gotoxy(83, 2 + y);
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
	for (int i = 8; i <= 60; i++)
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
		gotoxy(25, 2 + i + y);
		cout << char(179);
		gotoxy(48, 2 + i + y);
		cout << char(179);
		gotoxy(60, 2 + i + y);
		cout << char(179);
	}

	gotoxy(25, 0 + y);
	cout << c;
	gotoxy(12, 2 + y);
	cout << "So Hoa Don";
	gotoxy(32, 2 + y);
	cout << "Ngay Lap";
	gotoxy(51, 2 + y);
	cout << "Loai";
}

void GiaoDien_LapHD(int y, int n, string c)
{
	system("cls");
	for (int i = 8; i <= 60; i++)
	{
		gotoxy(i, 2 + y);
		cout << char(196); //ngang
		gotoxy(i, n + 1 + y);
		cout << char(196);
	}

	for (int i = 0; i < n; i++)
	{
		gotoxy(8, 2 + i + y);
		cout << char(179); //doc
		gotoxy(25, 2 + i + y);
		cout << char(179);
		gotoxy(48, 2 + i + y);
		cout << char(179);
		gotoxy(60, 2 + i + y);
		cout << char(179);
	}

	gotoxy(29, 0 + y);
	cout << c;
	gotoxy(12, 2 + y);
	cout << "So Hoa Don";
	gotoxy(32, 2 + y);
	cout << "Ngay Lap";
	gotoxy(51, 2 + y);
	cout << "Loai";
}

void GiaoDien_LapCTHD(int y, int n, string c)
{
	for (int i = 63; i <= 115; i++)
	{
		gotoxy(i, 2 + y);
		cout << char(196);
		gotoxy(i, n + 1 + y);
		cout << char(196);
	}

	for (int i = 0; i < n; i++)
	{
		gotoxy(63, 2 + i + y);
		cout << char(179);
		gotoxy(73, 2 + i + y);
		cout << char(179);
		gotoxy(83, 2 + i + y);
		cout << char(179);
		gotoxy(103, 2 + i + y);
		cout << char(179);
		gotoxy(110, 2 + i + y);
		cout << char(179);
		gotoxy(115, 2 + i + y);
		cout << char(179);
	}

	gotoxy(85, 0 + y);
	cout << c;
	gotoxy(65, 2 + y);
	cout << "Ma Vat Tu";
	gotoxy(75, 2 + y);
	cout << "So luong";
	gotoxy(90, 2 + y);
	cout << "Don gia";
	gotoxy(105, 2 + y);
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

void ThongBao(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
	Sleep(3000);
	gotoxy(x, y);
	clreol();
	gotoxy(x, y);
}

//cho phep nhap chuoi, so, khoang trong
string NhapChuoi (string &temp)
{
	int key;
	while (true)
	{
		while (_kbhit())
		{
			key = _getch();
			if (key != 224)
			{
				if ((key >= 48 && key < 122) || key == SPACE)
				{
					cout << (char)key;
					temp += (char)key;
				}
				else if (key == 13)
				{
					if(temp == "")
					{
						ThongBao("khong duoc bo trong ma vat tu !", 9, 5);
					}
					else return temp;
				}
				else if (key == 8)
				{
					cout << "\b" << " " << "\b";
					temp.erase(temp.length() - 1, 1);
				}
				else if (key == 27)
				{
					return "";
				}
			}
			else
			{
				key = getch();
			}
		}
	}
	return temp;
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
				else if (key == 13)
				{
					return x;
				}
				else if (key == 8)
				{
					cout << "\b" << " " << "\b";
					x /= 10;
				}
				else if (key == 27)
				{
					system("cls");
					return -1;
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

//hien thi dau nhay len
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
				else if (key == 13)
				{
					return x;
				}
				else if (key == 8)
				{
					cout << "\b" << " " << "\b";
					x /= 10;
				}
				else if (key == 27)
				{
					system("cls");
					x = -1;
					return -1;
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
				else if (key == 13)
				{
					return temp;
				}
//				else if (key == 8)
//				{
//					cout << "\b" << " " << "\b";
//					temp.erase(temp.length() - 1, 1);
//				}
				else if (key == 27)
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
//tim kiem ma vat tu neu trung
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

//______________________THEM VAT TU___________________________
//in danh sach vat tu
void InDSVT(LISTVT tree, int& i)
{
	GiaoDien_InDSVT(8, 30, "DANH SACH VAT TU");
	if(tree!=NULL)
	{
		gotoxy(15, 11 + i);
		cout << tree->vt.MaVT;
		gotoxy(35, 11 + i);
		cout << tree->vt.TenVT;
		gotoxy(65, 11 + i);
		cout << tree->vt.DVT;
		gotoxy(85, 11 + i);
		cout << tree->vt.SLT;

		i++;
		InDSVT(tree->pLeft, i);
		InDSVT(tree->pRight, i);
	}
	AnDauNhay();
}

//ham them vat tu
void ThemVT(LISTVT &tree)
{
	int x = 0;
	system("cls");
	InDSVT(tree, x);
	
	while(true)
	{
		VatTu vt;
		GiaoDien_InDSVT(0, 3, "NHAP  VAT TU                                       ESC: Thoat");
		HienThiDauNhay();
		gotoxy(15, 3);
		cin.getline(vt.MaVT, 11);
		if(strcmp(vt.MaVT,"") == 0)
		{
			ThongBao("Hay nhap ma vat tu !", 9, 6);
//			ThemVT(tree);
			continue;
		}
		if(TimKiemMaVT(tree, vt) != NULL)
		{
			ThongBao("Da co vat tu nay roi !", 9, 6);
			ThemVT(tree);
//			continue;
		}
		gotoxy(35, 3);
		cin.getline(vt.TenVT, 51);
		gotoxy(65, 3);
		cin.getline(vt.DVT, 11);
		gotoxy(85, 3);
		vt.SLT = 0;
		ChiNhapSo(vt.SLT);
		
		InsertVatTu(tree,vt);
		GhiFileVatTu(tree);
		
		ThongBao("Them vat tu thanh cong !", 9, 6);
		
		int x1 = 0;
		system("cls");
		InDSVT(tree, x1);
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
		}
	}
}

//ham xoa vat tu
void XoaVT(LISTVT &tree)
{
	while(true)
	{
		VatTu vt;
		if(tree == NULL)
		{
			ThongBao("Danh sach vat tu rong !", 9, 5);
			return;
		}
		int x = 0;
		system("cls");
		InDSVT(tree,x);
		
		HienThiDauNhay();
		gotoxy(9,3);
		cout << "Nhap ma vat tu can xoa : ";
		cin.getline(vt.MaVT, 11);
		
		ListVatTu* node;
		node = TimKiemMaVT(tree,vt);
		if(strcmp(vt.MaVT,"") == 0)
		{
			ThongBao("Hay nhap ma vat tu !", 9, 5);
			continue;
		}
		if(node == NULL)
		{
			ThongBao("Khong tim thay vat tu da nhap !", 9, 5);
			continue;
		}
		//kiem tra khoa ngoai, mavt trong cthd
		
		DeleteVatTu(tree,vt);
		GhiFileVatTu(tree);
		
		ThongBao("Xoa vat tu thanh cong !", 9, 5);
		
		system("cls");
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
			ThongBao("Danh sach vat tu rong !", 9, 5);
			return;
		}
		int x = 0;
		InDSVT(tree, x);
		HienThiDauNhay();
		gotoxy(9,3);
		cout << "Nhap ma vat tu can sua : ";
		cin.getline(vt.MaVT, 11);
		if(strcmp(vt.MaVT,"") == 0)
		{
			ThongBao("Hay nhap ma vat tu !", 9, 5);
			continue;
		}
		if(TimKiemMaVT(tree,vt) == NULL)
		{
			ThongBao("Khong co vat tu nay !", 9, 5);
			system("cls");
			continue;
		}
		ListVatTu *p = TimKiemMaVT(tree,vt);
		if (p != NULL)
		{
			system("cls");
			GiaoDien_InDSVT(0, 3, "SUA THONG TIN VAT TU");
			int x1 = 0;
			InDSVT(tree,x1);
			gotoxy(15,3);
			cout << vt.MaVT;
//			gotoxy(85,3);
//			cout << vt.SLT;
			HienThiDauNhay();
			char TenVT[50];
			gotoxy(35, 3);
			cin.getline(TenVT, 51);
			char DVT[10];
			gotoxy(65, 3);
			cin.getline(DVT, 11);
			
			strcpy(p->vt.TenVT,TenVT);
			strcpy(p->vt.DVT,DVT);
		}
		GhiFileVatTu(tree);
		ThongBao("Sua vat tu thanh cong !", 9, 6);
		system("cls");
	}
}

//_________________SAP XEP VAT TU____________________
//in ds vat tu- ten tang dan
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
void InDSVTTK_Ten(LISTVT &tree)
{
	int key;
	if ( tree == NULL)
	{
		ThongBao("Danh sach rong !", 9, 5);
		return;
	}
	GiaoDien_InDSVT(0, 30, "DANH SACH VAT TU TON KHO THEO TEN                  ESC: Thoat");
	VatTu vt[MAXVT];
	int n = 0;
	getDSVT(tree, vt, n);
	SX_TenVT(vt, n);
	for (int i = 0; i < n; i++)
	{
		gotoxy(15, 3 + i);
		cout << vt[i].MaVT;
		gotoxy(35, 3 + i);
		cout << vt[i].TenVT;
		gotoxy(65, 3 + i);
		cout << vt[i].DVT;
		gotoxy(85, 3 + i);
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
	GiaoDien_InDSNV(8,30, "DANH SACH NHAN VIEN");
	for (int i = 0; i<ds.n; i++)
	{
		gotoxy(15, 11 + i);
		cout << ds.dsnv[i]->MaNV;
		gotoxy(35, 11 + i);
		cout << ds.dsnv[i]->Ho;
		gotoxy(65, 11 + i);
		cout << ds.dsnv[i]->Ten;
		gotoxy(85, 11 + i);
		cout << ds.dsnv[i]->Phai;
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
int ViTriNV(LISTNV ds, char manv[])
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

//___________________THEM NHAN VIEN___________________
//ham them nhan vien
void ThemNV(LISTNV &ds)
{
	NhanVien nv;
	if(FullDSNV(ds) == 1)
	{
		ThongBao("Danh sach day !", 9, 5);
		return;
	}
	int ktra = 0;
	for (; ds.n<MAXNV;)
	{
		InDSNV(ds);
		GiaoDien_InDSNV(0, 3, "NHAP NHAN VIEN                                    ESC: Thoat");
		HienThiDauNhay();
		gotoxy(15, 3);
		cin.getline(nv.MaNV,11);
		if(strcmp(nv.MaNV,"") == 0)
		{
			ThongBao("Hay nhap ma nhan vien !", 9, 6);
//			ThemNV(ds);
			continue;
		}
		if(KiemTraMaNV(ds, nv.MaNV) == 1)
		{
			ThongBao("Da co nhan vien nay roi !", 9, 6);
			system("cls");
//			ThemNV(ds);
			continue;
		}
		gotoxy(35, 3);
		cin.getline(nv.Ho,41);
//		if(strcmp(nv.Ho, "") == 0)
//		{
//			ThongBao("Hay nhap Ho nhan vien !", 9, 6);
//			continue;
//		}
		gotoxy(65, 3);
		cin.getline(nv.Ten,11);
//		if(strcmp(nv.Ten, "") == 0)
//		{
//			ThongBao("Hay nhap Ten nhan vien !", 9, 6);
//			continue;
//		}
		gotoxy(85, 3);
		int Phai = 0;
		ChiNhap0or1(nv.Phai);
		
		ds.dsnv[ds.n] = new NhanVien;
		strcpy(ds.dsnv[ds.n]->MaNV,nv.MaNV);
		strcpy(ds.dsnv[ds.n]->Ho,nv.Ho);
		strcpy(ds.dsnv[ds.n]->Ten, nv.Ten);
		ds.dsnv[ds.n]->Phai = nv.Phai;
		
		ThongBao("Them nhan vien thanh cong !", 9, 6);
		system("cls");
		ds.n++;
		GhiFileNhanVien(ds);
		InDSNV(ds);
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
		char manv[10];
		gotoxy(9, 3);
		cout << "Nhap ma nhan vien can xoa : ";
		cin.getline(manv,11);
		int kt = ViTriNV(ds,manv);
		if(strcmp(manv,"") == 0)
		{
			ThongBao("Hay nhap ma nhan vien !", 9, 5);
			continue;
		}
		if(KiemTraMaNV(ds, manv) != 1)
		{
			ThongBao("Khong co nhan vien nay !", 9, 5);
			system("cls");
			continue;
		}
		
		//ktra nhan vien: neu da lap hoa don thi ko xoa duoc
			
		for (int i = kt; i < ds.n; i++)
		{
			ds.dsnv[i] = ds.dsnv[i + 1];
		}
		ds.n--;
		
		GhiFileNhanVien(ds);
		ThongBao("Xoa nhan vien thanh cong !", 9, 6);
		system("cls");
		InDSNV(ds);
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
		char manv[10];
		gotoxy(9, 3);
		cout << "Nhap ma nhan vien can sua : ";
		cin.getline(manv,11);
		system("cls");
		InDSNV(ds);
		int kt = ViTriNV(ds,manv);
		if(strcmp(manv,"") == 0)
		{
			ThongBao("Hay nhap ma nhan vien !", 9, 5);
			continue;
		}
		else if(KiemTraMaNV(ds, manv) != 1)
		{
			ThongBao("Khong co nhan vien nay !", 9, 5);
			system("cls");
			continue;
		}
		else
		{
			GiaoDien_InDSNV(0,3, "SUA THONG TIN NHAN VIEN");
			gotoxy(15, 3);
			cout << ds.dsnv[kt]->MaNV;
			char Ho[40];
			gotoxy(35, 3);
			cin.getline(nv.Ho, 41);
//			if(strcmp(nv.Ho, "") == 0)
//			{
//				ThongBao("Hay nhap Ho nhan vien !", 9, 6);
//				continue;
//			}
			char Ten[10];
			gotoxy(65, 3);
			cin.getline(nv.Ten, 11);
//			if(strcmp(nv.Ho, "") == 0)
//			{
//				ThongBao("Hay nhap Ho nhan vien !", 9, 6);
//				continue;
//			}
			int Phai;
			gotoxy(85, 3);
			ChiNhap0or1(nv.Phai);
			
			//xu ly them thong tin moi nhap de sua
			strcpy(ds.dsnv[kt]->Ho, nv.Ho);
			strcpy(ds.dsnv[kt]->Ten,nv.Ten);
			ds.dsnv[kt]->Phai = nv.Phai;
		}
		GhiFileNhanVien(ds);
		ThongBao("Sua nhan vien thanh cong !", 9, 6);
		system("cls");
		InDSNV(ds);
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
	GiaoDien_InDSNV(0, 30, "DANH SACH NHAN VIEN THEO TEN HO                   ESC: Thoat");
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
		cout << ds.dsnv[i]->Phai;
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
		NODECTHD dsCTHD;
		hd.nodecthd = dsCTHD;
		
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
void InDSHD(NODEHD &first)
{
	AnDauNhay();
	GiaoDien_InHD(12, 15, "DANH SACH HOA DON");
	int k = 0;
	for(NODEHD p = first; p != NULL; p = p->pNext)
	{
		int demvt = 0;
//		for(int i = 0; i < p->hd.nodecthd; i++)
//		{
//			demvt++;
//		}
		gotoxy(12, 15 + k);
		cout << p->hd.SoHD;
		gotoxy(32, 15 + k);
		cout << p->hd.NgayLap.Ngay << "/" << p->hd.NgayLap.Thang << "/" << p->hd.NgayLap.Nam;
		gotoxy(51, 15 + k);
		if (p->hd.Loai == 'n' || p->hd.Loai == 'N')
		{
			cout << "Nhap";// << demvt;
		}
		if (p->hd.Loai == 'x' || p->hd.Loai == 'X')
		{
			cout << "Xuat";// << demvt;
		}
		k++;
	}
}

//xu ly nhap hoa don
void NhapHD(LISTNV &ds, LISTVT tree, char manv[10])
{
	GiaoDien_LapHD(6, 3, "LAP HOA DON"); //6: cach vien tren //3:so dong
	HoaDon hd;
	gotoxy(12, 9);
	char sohd[20];
	char loai;
	cin.getline(sohd, 21);
	if(strcmp(sohd,"") == 0)
	{
		ThongBao("Hay nhap so hoa don !", 9, 12);
		NhapHD(ds,tree,manv);
	}
	
	int vitrinv = ViTriNV(ds,manv);
//	for(int i = 0; i < ds.n; i++)
//	{
		for(NODEHD p = ds.dsnv[vitrinv]->nodehd; p != NULL; p = p->pNext)
		{
			if(strcmp(p->hd.SoHD,sohd) == 0)
			{
				ThongBao("Da co so hoa don nay !", 9, 12);
				NhapHD(ds,tree,manv);
			}
		}
//	}
	
	Date date = Now();
	gotoxy(29, 9);
	cout << date.Ngay;
	gotoxy(32, 9);
	cout << "/";
	gotoxy(34, 9);
	cout << date.Thang;
	gotoxy(37, 9);
	cout << "/";
	gotoxy(39, 9);
	cout << date.Nam;
	gotoxy(51, 9);
	hd.Loai = ChiNhapNorX(loai);
	
	strcpy(hd.SoHD, sohd);
	hd.NgayLap = date;
	hd.Loai = loai;
	NODECTHD dsCTHD;
	hd.nodecthd = dsCTHD;
			
	InsertHD(ds.dsnv[vitrinv]->nodehd, TaoNodeHD(hd));
	InDSHD(ds.dsnv[vitrinv]->nodehd);
	
	GhiFileHoaDon(ds);
	
//	for(int i = 0; i < ds.n; i++)
//	{
//		for (NODEHD p = ds.dsnv[i]->nodehd; p != NULL; p = p->pNext)
//		{
//			if (strcpy(p->hd.SoHD,sohd) == 0)
//			{
////				NhapCTHD(tree, p->hd.ds_CTHD, dsVT, loai, p->info.soHD, maNV);
//			}
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

//doc file chi tiet hoa don
void DocFileCTHD(LISTNV &ds)
{
	string data;
	fstream f;
	f.open("dschitiethoadon.txt", ios::in);
	char sohd[20];
	if(f == NULL)
	{
		return;
	}
	getline(f, data);
	strcpy(sohd, data.c_str());
	int vitri;
	while (!f.eof() && sohd != NULL)
	{
		CTHoaDon cthd;
		getline(f,data);
		if(data.size() == 0)
		{
			break;
		}
		strcpy(cthd.MaVT, data.c_str());
		f >> cthd.SoLuong;
		f.ignore();
		f >> cthd.DonGia;
		f.ignore();
		f >> cthd.VAT;
		f.ignore();
		
		//xu ly danh sach chi tiet hoa don
//		NODECTHD dsCTHD;
//		hd.nodecthd = dsCTHD;
//		
//		vitri = ViTriNV(ds, manv);
//		InsertHD(ds.dsnv[vitri]->nodehd, TaoNodeHD(hd));
		
		f >> sohd;
		f.ignore();
	}
	f.close();
}

//ghi file chi tiet hoa don
void GhiFileCTHD(LISTNV ds)
{
	fstream f;
	f.open("dschitiethoadon.txt", ios::out);
//	NODEHD nodeHD;
	
//	for(int i = 0; i < ds.n; i++)
//	{
//		if(ds.dsnv[i]->nodecthd != NULL)//ktra nv da lap hoa don chua
//		{
//			nodeCTHD = ds.dsnv[i]->nodecthd;//da lap roi -> gan node tam
//		}
//		else
//		{
//			nodeHD = NULL;//chua lap hoa don
//		}
//		while(nodeHD != NULL)
//		{
//			f << ds.dsnv[i]->MaNV << endl;
//			f << nodeHD->hd.SoHD << endl;
//			f << nodeHD->hd.NgayLap.Ngay << endl;
//			f << nodeHD->hd.NgayLap.Thang << endl;
//			f << nodeHD->hd.NgayLap.Nam << endl;
//			f << nodeHD->hd.Loai << endl;
//			
//			nodeHD = nodeHD->pNext;
//		}
//	}
	f.close();
}

//in ds cthd
void InDSCTHD(NODECTHD &first)
{
	AnDauNhay();
	GiaoDien_LapCTHD(12, 15, "DANH SACH CHI TIET HOA DON");
	int k = 0;
	for(NODECTHD p = first; p != NULL; p = p->pNext)
	{
		gotoxy(12, 15 + k);
		cout << p->cthd.MaVT;
		gotoxy(32, 15 + k);
		cout << p->cthd.SoLuong;
		gotoxy(51, 15 + k);
		cout << p->cthd.DonGia;
		gotoxy(105, 15 + k);
		cout << p->cthd.VAT;
		k++;
	}
}

//ham nhap chi tiet hoa don
void NhapCTHD(LISTNV ds, LISTVT &tree, NODECTHD &nodeCTHD )
{
	char manv[10];
	char sohd[20];
	char loai;
//	dsCTHD.n = 0;
	gotoxy(70, 7);
	cout << "ESC: ket thuc nhap CTHD";
	GiaoDien_LapCTHD(12, 15, "LAP CHI TIET HOA DON");
	
	HienThiDauNhay();
	char mavt[10];
	cin.getline(mavt, 11);
	gotoxy(65, 15);
	if (strcmp(mavt, "") == 0)
	{
		ThongBao("Hay nhap ma vat tu !", 9, 5);
		return;
	}
	
	
	
	
}

//*************************MAIN******************************
int main()
{
	int chon;
	
	LISTVT root = NULL;
	LISTNV listnv;
	listnv.n = 0;
	
	LISTVT tree;
	InitTree(tree);
	DocFileVatTu(tree);
	DocFileNhanVien(listnv);
	DocFileHoaDon(listnv);
	GhiFileHoaDon(listnv);
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
							XoaVT(tree);
							break;
						case 3:
							SuaVT(tree);
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
				int vt;

				gotoxy(9, 3);
				char manv[10];
				cout << "Nhap ma nhan vien : ";
				cin.getline(manv, 11);
				if(strcmp(manv,"") == 0)
				{
					ThongBao("Hay nhap ma nhan vien !", 9, 5);
					break;
				}
				if(KiemTraMaNV(listnv,manv) == -1)
				{
					ThongBao("Khong co nhan vien nay !", 9, 5);
					break;
				}
				
				vt = ViTriNV(listnv, manv); //tra ve nhan vien nay

//				for(int i = 0; i < listnv.n; i++)
//				{
					if (vt != -1)
					{
//						if (p1->dsnv[i]->nodehd != NULL)
//						{
//							InDSHD(p1->dsnv[i]->nodehd);
//							gotoxy(30, 0);
//							cout << "Hien co " << demHDkVT(p1->dsnv[i]->nodehd) << " Hoa don khong co VT !";
//						}
//						else
//						{
//							BaoLoi("Danh sach dang trong !", 0, 1);
//						}
						gotoxy(70, 3);
						cout << "F1: Them HD";
						gotoxy(70, 4);
						cout << "F4: Xem CTHD";
						gotoxy(70, 5);
						cout << "ESC: Thoat";
						bool flag = true;
						bool flg = true;
						while (flag)
						{
							while (_kbhit())
							{
								int ch = _getch();
								if (ch == 224) ch = _getch();
								if (ch == 0) ch = _getch();
								switch (ch)
								{
								case 59:
									gotoxy(9, 3);
									cout << "Nhan vien : " << manv;
									NhapHD(listnv, tree, manv);
									
									gotoxy(9, 3);
									cout << "Nhan vien : " << manv;
									gotoxy(70, 3);
									cout << "F1: Them HD";
									gotoxy(70, 4);
									cout << "F4: Xem CTHD";
									gotoxy(70, 5);
									cout << "ESC: Thoat";
		
									InDSHD(listnv.dsnv[vt]->nodehd);
									
									/*gotoxy(80, 3);
									cout << "F5: Xoa CTHD";*/
		
									//xoa chi tiet hoa don ms lap
		
									break;
								case 62:
									gotoxy(9, 3);
									cout << "Nhan vien : " << manv;
									gotoxy(70, 3);
									cout << "F1: Them HD";
									gotoxy(70, 4);
									cout << "F4: Xem CTHD";
									gotoxy(70, 5);
									cout << "ESC: Thoat";
									
									InDSHD(listnv.dsnv[vt]->nodehd);
//									xemCTHDHD(p1);
									break;
								case 27:
									flag = false;
									break;
								}
							}
						}
					}
//				}	
			}
	}
	while(true);
	return 0;
}
