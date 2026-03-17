#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
using namespace std;

struct katalogProduk {
	char nama[60];
	char kategori[30];
	double harga;
	int stok;
	float rating;
};
katalogProduk katalog[100];

int jmlproduk = 0;

void bacaFile();
void simpanFile();
void tambahProduk();
void tampilkanProduk();
void bubbleSort();
void quickSort (int low, int high);
int partition (int low, int high);
void cariProduk();

int main() {
	int pilihan;
	char kembali;
	
	bacaFile();
	
	do {
		system("cls");
		
		cout << "----------------------------------" << endl;
		cout << "| SISTEM KATALOG PRODUK SHOPEASE |" << endl;
		cout << "----------------------------------" << endl;
		cout << "| " << left << setw(31) << "1. Tambah Produk Baru" << "|" << endl;
		cout << "| " << left << setw(31) << "2. Tampilkan Daftar Produk" << "|" << endl;
		cout << "| " << left << setw(31) << "3. Cari Produk" << "|" << endl;
		cout << "| " << left << setw(31) << "4. Keluar & Simpan" << "|" << endl;
		cout << "----------------------------------" << endl;
		cout << "Pilih Menu: ";
		cin >> pilihan;
		cout << endl;
		
		system("cls");
		
		switch (pilihan) {
			case 1:
				tambahProduk();
				break;
			case 2:
				tampilkanProduk();
				break;
			case 3: 
				cariProduk();
				break;
			case 4:
				simpanFile();
				cout << "Data berhasil disimpan. Terima kasih, program telah selesai!" << endl;
				cout << endl;
				return 0;
				
			default:
				cout << "Pilihan tidak tersedia";
		}
		
		do {
			cout << "Kembali ke Menu Utama? (y/n): ";
			cin >> kembali;
		} while (kembali != 'y' && kembali != 'Y' && kembali != 'n' && kembali != 'N');
		
	} while (kembali == 'y' || kembali == 'Y');
}

void bacaFile() {
	FILE *pf = fopen("shopease_db.txt", "r");
	
	if(pf == NULL) return;
	
	while (fscanf(pf, " %[^|]|%[^|]|%lf|%d|%f\n", katalog[jmlproduk].nama, katalog[jmlproduk].kategori, 
	&katalog[jmlproduk].harga, &katalog[jmlproduk].stok, &katalog[jmlproduk].rating) != EOF) {
		jmlproduk++;
	}
	fclose(pf);
}

void simpanFile() {
	FILE *pf = fopen("shopease_db.txt", "w");
	for(int i = 0; i < jmlproduk; i++) {
		fprintf(pf, "%s|%s|%.0lf|%d|%.1f\n", katalog[i].nama, katalog[i].kategori, 
		katalog[i].harga, katalog[i].stok, katalog[i].rating);
	}
	fclose(pf);
}

void tambahProduk() {
	cin.ignore();
	
	cout << "---------------------------------" << endl;
	cout << "\tTAMBAH PRODUK" << endl;
	cout << "---------------------------------" << endl;
	cout << left << setw(15) << "Nama Produk" << ": ";
	cin.getline(katalog[jmlproduk].nama, 60);
	cout << left << setw(15) << "Kategori" << ": ";
	cin.getline(katalog[jmlproduk].kategori, 30);
	cout << left << setw(15) << "Harga" << ": ";
	cin >> katalog[jmlproduk].harga;
	cout << left << setw(15) << "Stok" << ": ";
	cin >> katalog[jmlproduk].stok;
	cout << left << setw(15) << "Rating" << ": ";
	cin >> katalog[jmlproduk].rating;
	cout << "---------------------------------" << endl;
	cout << endl;
	
	jmlproduk++;
	
	simpanFile();
	
	cout << "Produk berhasil ditambahkan!" << endl;
	cout << endl;
}

void bubbleSort() {
	for(int i = 0; i < jmlproduk - 1; i++) {
		for(int j = 0; j < jmlproduk - 1; j++) {
			if(strcmp(katalog[j].nama, katalog[j + 1].nama) > 0) {
				katalogProduk temp = katalog[j];
				katalog[j] = katalog[j + 1];
				katalog[j + 1] = temp;
			}
		}
	}
}

int partition(int low, int high) {
	float pivot = katalog[high].rating;
	int i = low - 1;
	
	for(int j = low; j < high; j++) {
		if(katalog[j].rating > pivot) {
			i++;
			
			katalogProduk temp = katalog[i];
			katalog[i] = katalog[j];
			katalog[j] = temp;
		}
	}
	katalogProduk temp = katalog[i + 1];
	katalog[i + 1] = katalog[high];
	katalog[high] = temp;
	
	return i + 1;
}

void quickSort(int low, int high) {
	if(low < high) {
		int pi = partition(low, high);
		
		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}

void tampilkanProduk() {
	int mode;
	system("cls");
	
	cout << "------------------------------------------" << endl;
	cout << "| " << setw(39) << left << "SORTING KATALOG PRODUK SHOPEASE" << "|" << endl;
	cout << "------------------------------------------" << endl;
	cout << "| " << left << setw(39) << "1. Nama Produk (Bubble Sort Asc)" << "|" << endl;
	cout << "| " << left << setw(39) << "2. Rating (Quick Sort Desc)" << "|" << endl;
	cout << "------------------------------------------" << endl;
	cout << "Pilih mode: ";
	cin >> mode;
	cout << endl;
	
	if(mode == 1) {
		bubbleSort();
	} else if(mode == 2) {
		quickSort(0, jmlproduk - 1);
	}
	cout << "-----------------------------------------------------------------" << endl;
	cout << "| " << left << setw(18) << "Nama" << "| " << setw(13) << "Kategori" << "| " << setw(10) << "Harga" << "| " << setw(6)  << "Stok" << "| " << setw(6)  << "Rating" << " |" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	for(int i = 0; i < jmlproduk; i++) {
		cout << "| " << left << setw(18) << katalog[i].nama << "| " << setw(13) << katalog[i].kategori << "| " << setw(10) << katalog[i].harga << "| " << setw(6)  << katalog[i].stok << "| " << setw(6)  << katalog[i].rating << " |" << endl;
	}
	cout << "-----------------------------------------------------------------" << endl;
	cout << endl;
}

void cariProduk() {
	char cari[60];
    bool ditemukan = false;
    
    cin.ignore();
	system("cls");
	
	cout << "MENCARI PRODUK (SEQUENTIAL SEARCH)" << endl;
	cout << endl;
    cout << "Masukkan nama produk: ";
    cin.getline(cari, 60);
    cout << endl;

    for(int i = 0; i < jmlproduk; i++) {
		if(strcmp(cari, katalog[i].nama) == 0) {
			
			cout << "----------------------------------" << endl;
			cout << " Produk Ditemukan " << endl;
			cout << "----------------------------------" << endl;
			cout << left << setw(15) << " Nama"     << ": " << katalog[i].nama << endl;
			cout << left << setw(15) << " Kategori" << ": " << katalog[i].kategori << endl;
			cout << left << setw(15) << " Harga"    << ": " << katalog[i].harga << endl;
			cout << left << setw(15) << " Stok"     << ": " << katalog[i].stok << endl;
			cout << left << setw(15) << " Rating"   << ": " << katalog[i].rating << endl;
			cout << "----------------------------------" << endl;
			cout << endl;
			
            ditemukan = true;
		}
	} if(! ditemukan) {
		cout << "Produk tidak ditemukan!" << endl;
	}
}
