#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Sach
{
	string tenSach;
	string tenDocGia;
	int soLuongSach;
};

struct PhieuMuon
{
	string thoiGianMuon;
	string thoiGianTra;
};

void DocFileDanhSachSach(Sach* dsSach, int& dem)
{
	ifstream inFile("DanhSachSach.txt");
	if (inFile.is_open())
	{
		dem = 0;
		string line;
		while (getline(inFile, line))
		{
			string tenSach = "";
			string tenDocgia = "";
			string soLuong = "";
			int phan = 0;
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == ',')
				{
					phan++;
				}
				else
				{
					if (phan == 0)
					{
						tenSach = tenSach + line[i];
					}
					else if (phan == 1)
					{
						tenDocgia = tenDocgia + line[i];
					}
					else if (phan == 2)
					{
						soLuong = soLuong + line[i];
					}
				}
			}
			dsSach[dem].tenSach = tenSach;
			dsSach[dem].tenDocGia = tenDocgia;
			dsSach[dem].soLuongSach = stoi(soLuong);
			dem++;
		}
		inFile.close();
	}
	else
	{
		cout << "Khong the mo file DachSachSach.txt de doc!" << endl;
	}
}

void LuaChon(Sach* dsSach, PhieuMuon* dsPhieuMuon, int dem, string& luachon, int& soluongchon, bool& daluachon)
{
	string tenSachChon;
	string tenDocGiaChon;
	int soluongsach = 0;
	cout << "Tim sach theo ten sach hay la theo ten doc gia?" << endl;
	cout << "Vui long nhap tensach hoac docgia de chon: ";
	cin >> luachon;

	if (luachon == "tensach")
	{
		for (int i = 0; i < dem; i++)
		{
			cout << dsSach[i].tenSach << "," << dsSach[i].tenDocGia << "," << dsSach[i].soLuongSach;
			cout << endl;
		}
		cout << "Chon ten sach: ";
		cin >> tenSachChon;
		for (int i = 0; i < dem; i++)
		{
			if (tenSachChon == dsSach[i].tenSach)
			{
				soluongsach = dsSach[i].soLuongSach;
				break;  
			}
		}
		do {
			cout << "Chon so luong muon muon: ";
			cin >> soluongchon;
			if (soluongchon > soluongsach)
			{
				cout << "Nhap hon so luong sach hien co ! Vui long nhap lai!";
				cout << endl;
			}
		} while (soluongchon > soluongsach);
		cout << "Nhap ngay muon (dd/mm/yyyy): ";
		cin >> dsPhieuMuon->thoiGianMuon;
		cout << "Nhap ngay tra (dd/mm/yyyy): ";
		cin >> dsPhieuMuon->thoiGianTra;
		daluachon = true;
	}
	else if (luachon == "docgia")
	{
		cout << "Nhap ten doc gia: ";
		cin >> tenDocGiaChon;
		for (int i = 0; i < dem; i++)
		{
			if (tenDocGiaChon == dsSach[i].tenDocGia)
			{
				cout << dsSach[i].tenSach << "," << dsSach[i].tenDocGia << "," << dsSach[i].soLuongSach;
				cout << endl;
			}
		}
		cout << "Nhap ten sach: ";
		cin >> tenSachChon;
		for (int i = 0; i < dem; i++)
		{
			if (tenSachChon == dsSach[i].tenSach)
			{
				soluongsach = dsSach[i].soLuongSach;
				break;
			}
		}
		do {
			cout << "Chon so luong muon muon: ";
			cin >> soluongchon;
			if (soluongchon > soluongsach)
			{
				cout << "Nhap hon so luong sach hien co ! Vui long nhap lai!";
				cout << endl;
			}
		} while (soluongchon > soluongsach);
		cout << "Nhap ngay muon (dd/mm/yyyy): ";
		cin >> dsPhieuMuon->thoiGianMuon;
		cout << "Nhap ngay tra (dd/mm/yyyy): ";
		cin >> dsPhieuMuon->thoiGianTra;
		daluachon = true;
	}
}

void InFilePhieuMuon(PhieuMuon* dsPhieuMuon)
{
	ofstream outFile("PhieuMuon.txt", ios::app);
	if (outFile.is_open())
	{
		outFile << dsPhieuMuon->thoiGianMuon << " " << dsPhieuMuon->thoiGianTra << endl; 
		outFile.close();
	}
	else
	{
		cout << "Khong the mo file PhieuMuon.txt de ghi!" << endl;
	}
}

void XuLySoLuongSach(Sach* dsSach, int dem, string luachon, int soluongchon, bool daluachon)
{
	if (daluachon == true)
	{
		for (int i = 0; i < dem; i++)
		{
			dsSach[i].soLuongSach = dsSach[i].soLuongSach - soluongchon;
		}
	}
	ofstream outFile("DanhSachSach.txt", ios::out);
	if (outFile.is_open())
	{
		for (int i = 0; i < dem; i++)
		{
			outFile << dsSach[i].tenSach << "," << dsSach[i].tenDocGia << "," << dsSach[i].soLuongSach << endl;
		}
		outFile.close();
	}
	else
	{
		cout << "Khong the mo file DanhSachSach.txt de ghi!" << endl;
	}
}

void TinhQuaHanPhieuMuon(PhieuMuon* dsPhieuMuon)
{
	int ngayhientai = 12;        
	int thanghientai = 11;       
	int namhientai = 2025;      
	bool kiemtraquathoihan = false;
	string thoigiantra = dsPhieuMuon->thoiGianTra;
	string ngaytra = "";
	string thangtra = "";
	string namtra = "";
	int phantra = 0;

	for (int i = 0; i < thoigiantra.length(); i++)
	{
		if (thoigiantra[i] == '/' || thoigiantra[i] == '-')
		{
			phantra++;
		}
		else
		{
			if (phantra == 0)
			{
				ngaytra = ngaytra + thoigiantra[i];
			}
			if (phantra == 1)
			{
				thangtra = thangtra + thoigiantra[i];
			}
			if (phantra == 2)
			{
				namtra = namtra + thoigiantra[i];
			}
		}
	}

	int intNgayTra = stoi(ngaytra);
	int intThangTra = stoi(thangtra);
	int intNamTra = stoi(namtra);

	if (intNamTra < namhientai)
	{
		kiemtraquathoihan = true;
	}
	else if (intNamTra == namhientai)
	{
		if (intThangTra < thanghientai)
		{
			kiemtraquathoihan = true;
		}
		else if (intThangTra == thanghientai)
		{
			if (intNgayTra < ngayhientai)
			{
				kiemtraquathoihan = true;
			}
		}
	}

	if (kiemtraquathoihan)
	{
		cout << "Nguoi muon QUA HAN tra sach";
		cout << endl;
	}
	else
	{
		cout << "Nguoi muon chua qua han hoac tra dung han";
		cout << endl;
	}
}

int main()
{
	string luachon;
	int soluongchon = 0; 
	bool daluachon = false;
	int dem = 100;
	Sach* dsSach;
	PhieuMuon* dsPhieuMuon;
	dsSach = new Sach[dem];
	dsPhieuMuon = new PhieuMuon;

	DocFileDanhSachSach(dsSach, dem);
	LuaChon(dsSach, dsPhieuMuon, dem, luachon, soluongchon, daluachon);
	XuLySoLuongSach(dsSach, dem, luachon, soluongchon, daluachon);
	TinhQuaHanPhieuMuon(dsPhieuMuon);
	InFilePhieuMuon(dsPhieuMuon);

	delete[] dsSach;
	delete dsPhieuMuon;
	dsSach = nullptr;
	dsPhieuMuon = nullptr;

	return 0;
}