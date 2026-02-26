#include <iostream>
using namespace std;

struct Buku {
	string nama;
	int harga;
};

int main() {
	int pilihan;
	
	Buku bk[8] = { 
		{"Algoritma", 100000},
		{"Bisnis", 50000},
		{"English", 35000},
		{"Manajemen", 40000},
		{"Olahraga", 30000},
		{"Pancasila", 50000}, 
		{"Statistika", 70000}
	};
		
	int daftarbuku = 7;
	string cari;
	bool found = false;
	
	cout << "====== TOKO BUKU ALGO ======" << endl;
	cout << "1. Pencarian Biner" << endl;
	cout << "2. Pencarian Sekuensial" << endl;
	cout << "Pilih Pencarian: ";
	cin >> pilihan;
	cout << endl;
	
	if (pilihan == 1) {
		int i = 0; //kiri
		int j = daftarbuku - 1; //kanan
		int k; //tengah
		
		cout << "Masukkan Nama Buku yang Dicari: ";
		cin >> cari;
		
		found = false;
		
		while ((!found) && (i <= j)) {
			k = (i + j) / 2;
			if (cari == bk[k].nama) {
				found = true;
			} else {
				if (cari < bk[k].nama) {
					j = k - 1;
				} else {
					i = k + 1;
				}
			}
		}
		
		if (found) {
			cout << "Buku Ditemukan! Harga Buku = Rp" << bk[k].harga << endl;
		} else {
			cout << "Buku Tidak Ditemukan!" << endl;
		}
	}
	
	else if (pilihan == 2) {
		cout << "Metode Sekuensial:" << endl;
		cout << "1. Pencarian Tanpa Sentinel" << endl;
		cout << "2. Pencarian Dengan Sentinel" << endl;
		cout << "Pilih Metode: ";
		cin >> pilihan;
		cout << endl;
		
		if (pilihan == 1) {
			cout << "Masukkan Nama Buku yang Dicari: ";
			cin >> cari;
			
			int i = 0;
			bool found = false;
			
			while (i < daftarbuku && found == false) {
				if (bk[i].nama == cari) {
					found = true;
				} else {
					i++;
				}
			}
			
			if (found == true) {
				cout << "Buku Ditemukan! Harga Buku = Rp" << bk[i].harga << endl;
			} else {
				cout << "Buku Tidak Ditemukan!" << endl;
			}
		}
		
		else if (pilihan == 2) {
			cout << "Masukkan Nama Buku yang Dicari: ";
			cin >> cari;
			
			int i = 0;
			bk[daftarbuku].nama = cari;
			
			while (bk[i].nama != cari) {
				i++;
			}
			
			if (i < daftarbuku) {
				cout << "Buku Ditemukan! Harga Buku = Rp" << bk[i].harga << endl;
			} else {
				cout << "Buku Tidak Ditemukan!" << endl;
			}
		}
	}
	cout << endl;
	cout << "Terima Kasih Atas Kunjungan Anda!" << endl;
	
	
	return 0;
	
}

