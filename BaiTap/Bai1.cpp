#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstdio>
using namespace std;

// Constants
const string TENSACH_OPTION = "tensach";
const string DOCGIA_OPTION = "docgia";
const int MAX_SACH = 100;
const int MIN_YEAR = 2000;
const int MAX_YEAR = 2100;

// Forward declarations
void GhiLog(string noidung);

// ==================== UTILITY HELPER ====================

// Chuyen doi so nguyen sang string (thay the to_string)
string IntToString(int num)
{
	char buffer[50];
	sprintf(buffer, "%d", num);
	return string(buffer);
}

// ==================== STRUCTURES ====================
struct Sach
{
	string tenSach;
	int soLuongConLai;
	int soLuongTongCong;
};

struct PhieuMuon
{
	string tenSach;
	string tenDocGia;
	int soLuongMuon;
	string ngayMuon;
	string ngayTra;
};

struct NgayThang
{
	int ngay;
	int thang;
	int nam;
};

// ==================== VALIDATION FUNCTIONS ====================

// Kiem tra chuoi co rong khong
bool KiemTraChuoiRong(const string& str)
{
	if (str.empty())
		return true;
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return false;
	}
	return true;
}

// Tach ngay thang nam tu chuoi
bool TachNgayThang(const string& chuoiNgay, NgayThang& nt)
{
	string ngay = "", thang = "", nam = "";
	int phan = 0;

	for (int i = 0; i < (int)chuoiNgay.length(); i++)
	{
		if (chuoiNgay[i] == '/' || chuoiNgay[i] == '-')
		{
			phan++;
			if (phan > 2)
				return false; // Qua nhieu dau phan cach
		}
		else if (chuoiNgay[i] >= '0' && chuoiNgay[i] <= '9')
		{
			if (phan == 0)
				ngay += chuoiNgay[i];
			else if (phan == 1)
				thang += chuoiNgay[i];
			else if (phan == 2)
				nam += chuoiNgay[i];
		}
		else
		{
			return false; // Ky tu khong hop le
		}
	}

	if (ngay.empty() || thang.empty() || nam.empty())
		return false;

	try
	{
		nt.ngay = stoi(ngay);
		nt.thang = stoi(thang);
		nt.nam = stoi(nam);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

// Kiem tra ngay thang hop le
bool KiemTraNgayHopLe(const string& chuoiNgay)
{
	NgayThang nt;
	if (!TachNgayThang(chuoiNgay, nt))
		return false;

	// Kiem tra thang
	if (nt.thang < 1 || nt.thang > 12)
		return false;

	// Kiem tra nam
	if (nt.nam < MIN_YEAR || nt.nam > MAX_YEAR)
		return false;

	// So ngay trong thang
	int ngayTrongThang[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// Nam nhuan
	bool namNhuan = (nt.nam % 4 == 0 && nt.nam % 100 != 0) || (nt.nam % 400 == 0);
	if (namNhuan)
		ngayTrongThang[1] = 29;

	// Kiem tra ngay
	if (nt.ngay < 1 || nt.ngay > ngayTrongThang[nt.thang - 1])
		return false;

	return true;
}

// Kiem tra sach co ton tai khong
int TimSach(Sach* dsSach, int dem, const string& tenSach)
{
	for (int i = 0; i < dem; i++)
	{
		if (dsSach[i].tenSach == tenSach)
			return i;
	}
	return -1; // Khong tim thay
}

// Kiem tra so luong hop le
bool KiemTraSoLuong(int soLuong, int soLuongMax)
{
	return soLuong > 0 && soLuong <= soLuongMax;
}

// So sanh 2 ngay thang (tra ve -1 neu nt1 < nt2, 0 neu bang, 1 neu nt1 > nt2)
int SoSanhNgayThang(const NgayThang& nt1, const NgayThang& nt2)
{
	if (nt1.nam != nt2.nam)
		return (nt1.nam < nt2.nam) ? -1 : 1;
	if (nt1.thang != nt2.thang)
		return (nt1.thang < nt2.thang) ? -1 : 1;
	if (nt1.ngay != nt2.ngay)
		return (nt1.ngay < nt2.ngay) ? -1 : 1;
	return 0;
}

// ==================== UTILITY FUNCTIONS ====================

// Lay thoi gian hien tai
void LayThoiGianHienTai(NgayThang& nt)
{
	time_t thoiGianHienTai = time(0);
	tm* thoiGianDocDuoc = localtime(&thoiGianHienTai);
	nt.ngay = thoiGianDocDuoc->tm_mday;
	nt.thang = thoiGianDocDuoc->tm_mon + 1;
	nt.nam = thoiGianDocDuoc->tm_year + 1900;
}

// Ghi log vao file
void GhiLog(string noidung)
{
	try
	{
		ofstream logFile("log.txt", ios::app);
		if (!logFile.is_open())
		{
			throw runtime_error("Khong the mo file log.txt de ghi!");
		}

		NgayThang nt;
		LayThoiGianHienTai(nt);
		time_t thoiGianHienTai = time(0);
		tm* thoiGianDocDuoc = localtime(&thoiGianHienTai);

		logFile << "[" << nt.ngay << "/" << nt.thang << "/" << nt.nam << " "
		        << thoiGianDocDuoc->tm_hour << ":"
		        << thoiGianDocDuoc->tm_min << ":"
		        << thoiGianDocDuoc->tm_sec << "] "
		        << noidung << endl;
		logFile.close();
	}
	catch (exception& e)
	{
		cout << "Loi ghi log: " << e.what() << endl;
	}
}

// Xoa khoang trang thua o dau va cuoi chuoi
string XoaKhoangTrangThua(const string& str)
{
	if (str.empty())
		return str;

	int dau = 0;
	int cuoi = (int)str.length() - 1;

	// Xoa khoang trang o dau
	while (dau < (int)str.length() && (str[dau] == ' ' || str[dau] == '\t'))
		dau++;

	// Xoa khoang trang o cuoi
	while (cuoi > dau && (str[cuoi] == ' ' || str[cuoi] == '\t'))
		cuoi--;

	return str.substr(dau, cuoi - dau + 1);
}

// ==================== FILE OPERATIONS ====================

// Doc file danh sach sach (parse CSV thu cong)
void DocFileDanhSachSach(Sach* dsSach, int& dem)
{
	try
	{
		ifstream inFile("DanhSachSach.txt");

		// Neu khong tim thay o thu muc hien tai, thu tim o thu muc cha
		if (!inFile.is_open())
		{
			inFile.open("../DanhSachSach.txt");
		}

		if (!inFile.is_open())
		{
			throw runtime_error("Khong the mo file DanhSachSach.txt de doc!");
		}

		dem = 0;
		string line;
		int soDong = 0;

		while (getline(inFile, line) && dem < MAX_SACH)
		{
			soDong++;

			if (KiemTraChuoiRong(line))
				continue; // Bo qua dong rong

			// Parse CSV thu cong
			string tenSach = "";
			string soLuongStr = "";
			int phan = 0;

			for (int i = 0; i < (int)line.length(); i++)
			{
				if (line[i] == ',')
				{
					phan++;
				}
				else
				{
					if (phan == 0)
					{
						tenSach += line[i];
					}
					else if (phan == 1)
					{
						soLuongStr += line[i];
					}
				}
			}

			// Xoa khoang trang thua
			tenSach = XoaKhoangTrangThua(tenSach);
			soLuongStr = XoaKhoangTrangThua(soLuongStr);

			// Kiem tra ten sach rong
			if (tenSach.empty())
			{
				GhiLog("Loi dong " + IntToString(soDong) + ": ten sach rong");
				continue;
			}

			// Kiem tra so luong rong
			if (soLuongStr.empty())
			{
				GhiLog("Loi dong " + IntToString(soDong) + ": thieu so luong");
				continue;
			}

			// Chuyen doi so luong
			int soLuong = 0;
			try
			{
				soLuong = stoi(soLuongStr);
				if (soLuong < 0)
				{
					GhiLog("Loi dong " + IntToString(soDong) + ": so luong am - " + tenSach);
					soLuong = 0;
				}
			}
			catch (...)
			{
				GhiLog("Loi chuyen doi so luong cho dong " + IntToString(soDong) + ": " + tenSach);
				soLuong = 0;
			}

			// Luu vao mang
			dsSach[dem].tenSach = tenSach;
			dsSach[dem].soLuongConLai = soLuong;
			dsSach[dem].soLuongTongCong = soLuong;
			dem++;
		}

		inFile.close();

		if (dem >= MAX_SACH)
		{
			GhiLog("CANH BAO: Da dat gioi han toi da " + IntToString(MAX_SACH) + " sach!");
		}

		GhiLog("Doc file DanhSachSach.txt thanh cong. Tong: " + IntToString(dem) + " sach.");
	}
	catch (exception& e)
	{
		cout << "Loi: " << e.what() << endl;
		GhiLog("Loi doc file: " + string(e.what()));
	}
}

// Ghi lai file danh sach sach
void GhiFileDanhSachSach(Sach* dsSach, int dem)
{
	try
	{
		ofstream outFile("DanhSachSach.txt", ios::out);
		if (!outFile.is_open())
		{
			throw runtime_error("Khong the mo file DanhSachSach.txt de ghi!");
		}

		for (int i = 0; i < dem; i++)
		{
			outFile << dsSach[i].tenSach << "," << dsSach[i].soLuongConLai << endl;
		}

		outFile.close();
		GhiLog("Cap nhat file DanhSachSach.txt thanh cong.");
	}
	catch (exception& e)
	{
		cout << "Loi: " << e.what() << endl;
		GhiLog("Loi ghi file DanhSachSach: " + string(e.what()));
	}
}

// Ghi phieu muon vao file
void GhiFilePhieuMuon(PhieuMuon* phieuMuon)
{
	try
	{
		ofstream outFile("PhieuMuon.txt", ios::app);
		if (!outFile.is_open())
		{
			throw runtime_error("Khong the mo file PhieuMuon.txt de ghi!");
		}

		outFile << phieuMuon->tenSach << "|"
		        << phieuMuon->tenDocGia << "|"
		        << phieuMuon->soLuongMuon << "|"
		        << phieuMuon->ngayMuon << "|"
		        << phieuMuon->ngayTra << endl;

		outFile.close();
		GhiLog("Ghi phieu muon thanh cong: " + phieuMuon->tenSach + " - " + phieuMuon->tenDocGia);
	}
	catch (exception& e)
	{
		cout << "Loi: " << e.what() << endl;
		GhiLog("Loi ghi file PhieuMuon: " + string(e.what()));
	}
}

// ==================== DISPLAY FUNCTIONS ====================

// Hien thi danh sach sach
void HienThiDanhSachSach(Sach* dsSach, int dem)
{
	cout << "\n========== DANH SACH SACH ==========" << endl;
	cout << "STT | Ten Sach                     | So Luong" << endl;
	cout << "----|------------------------------|----------" << endl;

	for (int i = 0; i < dem; i++)
	{
		cout << (i + 1) << "   | " << dsSach[i].tenSach;

		// Them khoang trang cho dep
		for (int j = (int)dsSach[i].tenSach.length(); j < 28; j++)
			cout << " ";

		cout << " | " << dsSach[i].soLuongConLai << endl;
	}
	cout << "====================================" << endl;
}

// Hien thi danh sach doc gia khong trung lap
void HienThiDanhSachDocGia(Sach* dsSach, int dem)
{
	cout << "\n========== DANH SACH DOC GIA ==========" << endl;

	// Su dung mang de luu danh sach doc gia da hien thi
	string* docGiaDaHienThi = new string[dem];
	int soLuongDocGia = 0;

	for (int i = 0; i < dem; i++)
	{
		// Kiem tra trung lap
		bool daTonTai = false;
		for (int j = 0; j < soLuongDocGia; j++)
		{
			if (docGiaDaHienThi[j] == dsSach[i].tenSach)
			{
				daTonTai = true;
				break;
			}
		}

		if (!daTonTai)
		{
			cout << (soLuongDocGia + 1) << ". " << dsSach[i].tenSach << endl;
			docGiaDaHienThi[soLuongDocGia] = dsSach[i].tenSach;
			soLuongDocGia++;
		}
	}

	cout << "=======================================" << endl;
	delete[] docGiaDaHienThi;
}

// ==================== INPUT FUNCTIONS ====================

// Nhap so luong muon
int NhapSoLuongMuon(int soLuongMax)
{
	int soLuong;

	do
	{
		cout << "Nhap so luong muon muon (1-" << soLuongMax << "): ";
		cin >> soLuong;
		cin.ignore(); // Xoa ky tu xuong dong

		if (soLuong <= 0)
		{
			cout << "So luong phai lon hon 0! Vui long nhap lai." << endl;
		}
		else if (soLuong > soLuongMax)
		{
			cout << "So luong vuot qua so sach hien co! Vui long nhap lai." << endl;
		}
	} while (!KiemTraSoLuong(soLuong, soLuongMax));

	return soLuong;
}

// Nhap ngay thang
string NhapNgayThang(const string& loaiNgay)
{
	string ngay;
	bool hopLe = false;

	do
	{
		cout << "Nhap " << loaiNgay << " (dd/mm/yyyy): ";
		getline(cin, ngay);
		ngay = XoaKhoangTrangThua(ngay);

		if (KiemTraNgayHopLe(ngay))
		{
			hopLe = true;
		}
		else
		{
			cout << "Ngay khong hop le! Vui long nhap dung dinh dang dd/mm/yyyy." << endl;
			GhiLog("Ngay khong hop le: " + ngay);
		}
	} while (!hopLe);

	return ngay;
}

// ==================== BUSINESS LOGIC ====================

// Xu ly muon sach theo ten sach
void MuonTheoTenSach(Sach* dsSach, int dem, PhieuMuon* phieuMuon, bool& thanhCong)
{
	HienThiDanhSachSach(dsSach, dem);

	cout << "\nNhap ten sach can muon: ";
	string tenSach;
	getline(cin, tenSach);
	tenSach = XoaKhoangTrangThua(tenSach);

	// Tim sach
	int viTri = TimSach(dsSach, dem, tenSach);

	if (viTri == -1)
	{
		cout << "Khong tim thay sach '" << tenSach << "' trong thu vien!" << endl;
		GhiLog("Khong tim thay sach: " + tenSach);
		thanhCong = false;
		return;
	}

	if (dsSach[viTri].soLuongConLai <= 0)
	{
		cout << "Sach '" << tenSach << "' da het! Khong the muon." << endl;
		GhiLog("Sach het: " + tenSach);
		thanhCong = false;
		return;
	}

	// Nhap thong tin muon
	cout << "\nNhap ten doc gia: ";
	string tenDocGia;
	getline(cin, tenDocGia);
	tenDocGia = XoaKhoangTrangThua(tenDocGia);

	if (tenDocGia.empty())
	{
		cout << "Ten doc gia khong duoc rong!" << endl;
		thanhCong = false;
		return;
	}

	int soLuongMuon = NhapSoLuongMuon(dsSach[viTri].soLuongConLai);
	string ngayMuon = NhapNgayThang("ngay muon");
	string ngayTra = NhapNgayThang("ngay tra");

	// Kiem tra ngay tra phai sau ngay muon
	NgayThang ntMuon, ntTra;
	TachNgayThang(ngayMuon, ntMuon);
	TachNgayThang(ngayTra, ntTra);

	if (SoSanhNgayThang(ntTra, ntMuon) <= 0)
	{
		cout << "CANH BAO: Ngay tra phai sau ngay muon!" << endl;
		GhiLog("CANH BAO: Ngay tra khong hop ly - Muon: " + ngayMuon + ", Tra: " + ngayTra);
	}

	// Luu phieu muon
	phieuMuon->tenSach = tenSach;
	phieuMuon->tenDocGia = tenDocGia;
	phieuMuon->soLuongMuon = soLuongMuon;
	phieuMuon->ngayMuon = ngayMuon;
	phieuMuon->ngayTra = ngayTra;

	// Cap nhat so luong
	dsSach[viTri].soLuongConLai -= soLuongMuon;

	cout << "\nMuon sach thanh cong!" << endl;
	GhiLog("Muon sach thanh cong: " + tenSach + " (" + IntToString(soLuongMuon) + " quyen) - " + tenDocGia);
	thanhCong = true;
}

// Kiem tra phieu muon co qua han khong
void KiemTraQuaHan(PhieuMuon* phieuMuon)
{
	NgayThang ngayTra, ngayHienTai;

	if (!TachNgayThang(phieuMuon->ngayTra, ngayTra))
	{
		cout << "\nLoi: Khong the doc ngay tra!" << endl;
		GhiLog("Loi doc ngay tra: " + phieuMuon->ngayTra);
		return;
	}

	LayThoiGianHienTai(ngayHienTai);

	int ketQua = SoSanhNgayThang(ngayHienTai, ngayTra);

	cout << "\n========== KIEM TRA QUA HAN ==========" << endl;
	cout << "Sach: " << phieuMuon->tenSach << endl;
	cout << "Doc gia: " << phieuMuon->tenDocGia << endl;
	cout << "Ngay muon: " << phieuMuon->ngayMuon << endl;
	cout << "Ngay tra: " << phieuMuon->ngayTra << endl;
	cout << "Ngay hien tai: " << ngayHienTai.ngay << "/" << ngayHienTai.thang << "/" << ngayHienTai.nam << endl;

	if (ketQua > 0)
	{
		cout << "\n*** QUA HAN TRA SACH ***" << endl;
		GhiLog("PHAT HIEN QUA HAN: " + phieuMuon->tenDocGia + " - " + phieuMuon->tenSach);
	}
	else if (ketQua == 0)
	{
		cout << "\nDung han tra sach hom nay!" << endl;
		GhiLog("Dung han tra: " + phieuMuon->tenDocGia + " - " + phieuMuon->tenSach);
	}
	else
	{
		cout << "\nChua den han tra sach." << endl;
		GhiLog("Chua den han: " + phieuMuon->tenDocGia + " - " + phieuMuon->tenSach);
	}

	cout << "=======================================" << endl;
}

// ==================== MAIN ====================

int main()
{
	GhiLog("=== BAT DAU CHUONG TRINH ===");

	// Khoi tao du lieu
	Sach* dsSach = new Sach[MAX_SACH];
	PhieuMuon* phieuMuon = new PhieuMuon;
	int dem = 0;
	bool thanhCong = false;

	// Doc file danh sach sach
	DocFileDanhSachSach(dsSach, dem);

	if (dem == 0)
	{
		cout << "Khong co sach nao trong he thong!" << endl;
		GhiLog("Khong co sach nao de muon.");
		delete[] dsSach;
		delete phieuMuon;
		return 0;
	}

	cout << "\n===== CHUONG TRINH QUAN LY MUON TRA SACH =====" << endl;
	cout << "Tong so sach trong thu vien: " << dem << endl;

	// Muon sach theo ten sach
	MuonTheoTenSach(dsSach, dem, phieuMuon, thanhCong);

	if (thanhCong)
	{
		// Ghi phieu muon
		GhiFilePhieuMuon(phieuMuon);

		// Cap nhat file danh sach sach
		GhiFileDanhSachSach(dsSach, dem);

		// Kiem tra qua han
		KiemTraQuaHan(phieuMuon);
	}

	// Giai phong bo nho
	delete[] dsSach;
	delete phieuMuon;
	dsSach = nullptr;
	phieuMuon = nullptr;

	GhiLog("=== KET THUC CHUONG TRINH ===");

	return 0;
}
