#include <iostream>
using namespace std;

void tampilanmhs(string array[], int n) { // Fungsi untuk menampilkan isi array
	for (int i = 0; i < n; i++) { // Perulangan
		cout << array[i] << " "; // Menampilkan nama mahasiswa
	}
	cout << endl;
}


void bubblesort(string array[], int n) { // Fungsi pengurutan data menggunakan Bubble Sort
	for (int i = 0; i < n - 1; i++) { // Pengulangan pengurutan
		for (int j = 0; j < n - i - 1; j++) { // Membandingkan elemen yang berdekatan
			if (array[j] > array[j+1]) { // Jika array sekarang lebih besar dari array berikutnya
				string temp = array[j+1]; // Menyimpan sementara nilai array[j+1]
				array[j+1] = array[j]; // Memindahkan array[j] ke posisi berikutnya
				array[j] = temp; // Memindahkan nilai sementara ke posisi array[j]
			}
		}
	}
}

void quicksort(string array[], int awal, int akhir) { // Fungsi pengurutan data menggunakan Quick Sort
	int low = awal, high = akhir; // Indeks awal (kiri) dan akhir (kanan)
	string pivot = array[(awal + akhir) / 2]; // Menentukan pivot
    do {
        while (array[low] > pivot) // Mengurutkan data kiri
            low++;
        while (array[high] < pivot) // Mengurutkan data kanan
            high--;
        if (low <= high) {
            swap(array[low], array[high]); // Menukar posisi
            low++; // Geser indeks awal
            high--; // Geser indeks akhir
        }
    } while (low <= high);
    if (awal < high) // Mengurutkan bagian kiri array
        quicksort(array, awal, high);
    if (low < akhir) // Mengurutkan bagian kanan array
        quicksort(array, low, akhir);
}

int main() {
	int n; // Variabel jumlah mahasiswa
	
	cout << "Masukkan jumlah mahasiswa\t: "; // User menginput jumlah mahasiswa
	cin >> n;
	cout << endl;
	
	string nama1[n]; // Array menyimpan nama mahasiswa untuk Bubble Sort
	string nama2[n]; // Array menyimpan nama mahasiswa untuk Quick Sort
	
	for (int i = 0; i < n; i++) { // Perulangan input nama mahasiswa 
		cout << "Masukkan nama mahasiswa ke-" << i+1 << "\t: "; // User menginput nama mahasiswa
		cin >> nama1[i];
		nama2[i] = nama1[i]; // Input nama 2 sama dengan nama 1
	}
	cout << endl;
	
	bubblesort(nama1, n); // Memanggil fungsi Bubble Sort
	quicksort(nama2, 0, n - 1); // Memanggil fungsi Quick Sort
	
	cout << "Nama mahasiswa setelah disort (Bubble Sort Asc)\t: " << endl;
	tampilanmhs(nama1, n); // Menampilkan isi array yang sudah diurutkan secara ascending
	cout << "Nama mahasiswa setelah disort (Quick Sort Desc)\t: " << endl;
	tampilanmhs(nama2, n); // Menampilkan isi array yang sudah diurutkan secara descending
	
}
