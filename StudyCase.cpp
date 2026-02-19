#include <iostream>   
using namespace std; 

int main() {

    int n; //variabel untuk menyimpan panjang array
    
    //diminta memasukkan jumlah elemen array
    cout << "Masukkan jumlah elemen array\t: ";
    cin >> n;

    int arr[n]; //membuat array dengan panjang sesuai input
    int *ptr = arr; //pointer menunjuk alamat awal array

    //input nilai array
    cout << "Masukkan nilai elemen array\t: ";
    for(int i = 0; i < n; i++) {
        cin >> *(ptr + i); //array diisi dengan pointer
    }
    cout << endl;

    //menampilkan isi array
    cout << "Isi Array adalah: ";
    for(int i = 0; i < n; i++) {
        cout << *(ptr + i) << " "; //elemen ditampilkan dengan pointer
    }
    cout << endl;

    //mencari nilai maximum dan minimum
    int max = *ptr; //asumsi awal nilai maximum adalah elemen pertama
    int min = *ptr; //asumsi awal nilai minimum adalah elemen pertama

    for(int i = 0; i < n; i++) {
        if(*(ptr + i) > max) { //jika elemen lebih besar dari max
            max = *(ptr + i); //update nilai max
        }
        if(*(ptr + i) < min) { //jika elemen lebih kecil dari min
            min = *(ptr + i); //update nilai min
        }
    }

    //mencari jumlah dan rata-rata
    int jumlah = 0; //variabel untuk menyimpan total

    for(int i = 0; i < n; i++) {
        jumlah = jumlah + *(ptr + i); //menjumlahkan semua elemen
    }

    float rerata = (float)jumlah / n; //menghitung rata-rata

    //menampilkan hasil
    cout << "Nilai Maximum\t: " << max << endl;
    cout << "Nilai Minimum\t: " << min << endl;
    cout << "Jumlah  \t: " << jumlah << endl;
    cout << "Rata-Rata\t: " << rerata << endl;

    return 0;
}
