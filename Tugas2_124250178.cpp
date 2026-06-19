#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

const int kapasitasParkir = 3;

struct Kendaraan {
    string noPolisi;
    string namaPemilik;
    bool diParkiran;
    Kendaraan* left;
    Kendaraan* right;
};

struct StackNode {
    string aksi;              
    string noPolisi;          
    string noPolisiAntrian;   
    StackNode* next;
};

struct QueueNode {
    string noPolisi;
    QueueNode* next;
};

Kendaraan* root = NULL;
StackNode* topStack = NULL;
QueueNode* frontQueue = NULL;
QueueNode* rearQueue = NULL;

int jumlahParkir = 0;

void cls() {
    system("cls");
}

void garis() {
    cout << "--------------------------------------------------\n";
}

void headerMenu(string judul) {
    cls();
    garis();
    cout << " " << judul << endl;
    garis();
}

void jeda() {
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.get();
}

Kendaraan* buatNode(string noPolisi, string namaPemilik) {
    Kendaraan* baru = new Kendaraan;
    baru->noPolisi = noPolisi;
    baru->namaPemilik = namaPemilik;
    baru->diParkiran = false;
    baru->left = NULL;
    baru->right = NULL;
    return baru;
}

Kendaraan* cariKendaraan(Kendaraan* node, string noPolisi) {
	if (node == NULL) {
		return NULL;
	}
	
	if (noPolisi == node->noPolisi) {
		return node;
	} else if (noPolisi < node->noPolisi) {
		return cariKendaraan(node->left, noPolisi);
	} else {
		return cariKendaraan(node->right, noPolisi);
	}
}

void tambahKePTB(Kendaraan*& node, string noPolisi, string namaPemilik) {
    if (node == NULL) {
        node = buatNode(noPolisi, namaPemilik);
    } else if (noPolisi < node->noPolisi) {
        tambahKePTB(node->left, noPolisi, namaPemilik);
    } else if (noPolisi > node->noPolisi) {
        tambahKePTB(node->right, noPolisi, namaPemilik);
    }
}

void tampilInorder(Kendaraan* node) {
    if (node != NULL) {
        tampilInorder(node->left);
        cout << left << setw(18) << node->noPolisi << setw(15) << node->namaPemilik << (node->diParkiran ? "Di Parkiran" : "Di Luar Parkiran") << endl;
        tampilInorder(node->right);
    }
}

Kendaraan* cariTerkecil(Kendaraan* node) {
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }
    return node;
}

Kendaraan* hapusDariPTB(Kendaraan* node, string noPolisi) {
    if (node == NULL) {
        return NULL;
    }

    if (noPolisi < node->noPolisi) {
        node->left = hapusDariPTB(node->left, noPolisi);
    } else if (noPolisi > node->noPolisi) {
        node->right = hapusDariPTB(node->right, noPolisi);
    } else {
        if (node->left == NULL && node->right == NULL) {
            delete node;
            return NULL;
        } else if (node->left == NULL) {
            Kendaraan* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == NULL) {
            Kendaraan* temp = node->left;
            delete node;
            return temp;
        } else {
            Kendaraan* pengganti = cariTerkecil(node->right);

            node->noPolisi = pengganti->noPolisi;
            node->namaPemilik = pengganti->namaPemilik;
            node->diParkiran = pengganti->diParkiran;

            node->right = hapusDariPTB(node->right, pengganti->noPolisi);
        }
    }

    return node;
}

bool stackKosong() {
    return topStack == NULL;
}

void pushStack(string aksi, string noPolisi, string noPolisiAntrian = "") {
    StackNode* baru = new StackNode;
    baru->aksi = aksi;
    baru->noPolisi = noPolisi;
    baru->noPolisiAntrian = noPolisiAntrian;
    baru->next = topStack;
    topStack = baru;
}

bool popStack(string& aksi, string& noPolisi, string& noPolisiAntrian) {
    if (stackKosong()) {
        return false;
    }

    StackNode* hapus = topStack;

    aksi = hapus->aksi;
    noPolisi = hapus->noPolisi;
    noPolisiAntrian = hapus->noPolisiAntrian;

    topStack = topStack->next;
    delete hapus;

    return true;
}

bool queueKosong() {
    return frontQueue == NULL;
}

bool adaDiQueue(string noPolisi) {
    QueueNode* bantu = frontQueue;

    while (bantu != NULL) {
        if (bantu->noPolisi == noPolisi) {
            return true;
        }
        bantu = bantu->next;
    }

    return false;
}

void enqueue(string noPolisi) {
    QueueNode* baru = new QueueNode;
    baru->noPolisi = noPolisi;
    baru->next = NULL;

    if (queueKosong()) {
        frontQueue = baru;
        rearQueue = baru;
    } else {
        rearQueue->next = baru;
        rearQueue = baru;
    }
}

bool dequeue(string& noPolisi) {
    if (queueKosong()) {
        return false;
    }

    QueueNode* hapus = frontQueue;
    noPolisi = hapus->noPolisi;

    frontQueue = frontQueue->next;

    if (frontQueue == NULL) {
        rearQueue = NULL;
    }

    delete hapus;
    return true;
}

void enqueueDepan(string noPolisi) {
    QueueNode* baru = new QueueNode;
    baru->noPolisi = noPolisi;
    baru->next = frontQueue;

    frontQueue = baru;

    if (rearQueue == NULL) {
        rearQueue = baru;
    }
}

bool hapusDariQueue(string noPolisi) {
    QueueNode* bantu = frontQueue;
    QueueNode* sebelum = NULL;

    while (bantu != NULL) {
        if (bantu->noPolisi == noPolisi) {
            if (sebelum == NULL) {
                frontQueue = bantu->next;
            } else {
                sebelum->next = bantu->next;
            }

            if (bantu == rearQueue) {
                rearQueue = sebelum;
            }

            delete bantu;
            return true;
        }

        sebelum = bantu;
        bantu = bantu->next;
    }

    return false;
}

void tambahDataKendaraan() {
    headerMenu("              TAMBAH DATA KENDARAAN                 ");

    string noPolisi, namaPemilik;

    cout << "Masukkan Nomor Polisi : ";
    getline(cin, noPolisi);

    cout << "Masukkan Nama Pemilik : ";
    getline(cin, namaPemilik);

    if (cariKendaraan(root, noPolisi) != NULL) {
        cout << "\nData kendaraan sudah ada!\n";
    } else {
        tambahKePTB(root, noPolisi, namaPemilik);
        cout << "\nData kendaraan berhasil ditambahkan\n";
    }
}

void tampilKendaraan() {
    headerMenu("                 DATA KENDARAAN                 ");

    if (root == NULL) {
        cout << "Belum ada data kendaraan.\n";
        return;
    }

    cout << left << setw(18) << "Nomor Polisi" << setw(15) << "Nama Pemilik" << "Status" << endl;
    garis();

    tampilInorder(root);

    garis();
}

void kendaraanMasuk() {
    headerMenu("               CATAT KENDARAAN MASUK                 ");

    string noPolisi;

    cout << "Masukkan Nomor Polisi kendaraan masuk : ";
    getline(cin, noPolisi);

    Kendaraan* data = cariKendaraan(root, noPolisi);

    if (data == NULL) {
        cout << "\nKendaraan tidak ditemukan!\n";
        return;
    }

    if (data->diParkiran) {
        cout << "\nKendaraan sudah berada di parkiran.\n";
        return;
    }

    if (adaDiQueue(noPolisi)) {
        cout << "\nKendaraan sudah masuk ke dalam antrian.\n";
        return;
    }

    if (jumlahParkir < kapasitasParkir) {
        data->diParkiran = true;
        jumlahParkir++;

        pushStack("MASUK", noPolisi);

        cout << "\nKendaraan berhasil masuk\n";
    } else {
        enqueue(noPolisi);
        cout << "\nParkiran penuh, kendaraan masuk ke dalam antrian\n";
    }
}

void kendaraanKeluar() {
    headerMenu("                CATAT KENDARAAN KELUAR             ");

    string noPolisi;

    cout << "Masukkan Nomor Polisi kendaraan keluar : ";
    getline(cin, noPolisi);

    Kendaraan* data = cariKendaraan(root, noPolisi);

    if (data == NULL) {
        cout << "\nKendaraan tidak ditemukan!\n";
        return;
    }

    if (!data->diParkiran) {
        cout << "\nKendaraan sedang tidak berada di parkiran.\n";
        return;
    }

    data->diParkiran = false;
    jumlahParkir--;

    string noAntrian = "";

    if (!queueKosong()) {
        dequeue(noAntrian);

        Kendaraan* kendaraanAntri = cariKendaraan(root, noAntrian);

        if (kendaraanAntri != NULL) {
            kendaraanAntri->diParkiran = true;
            jumlahParkir++;
        }

        cout << "\nKendaraan berhasil keluar\n";
        cout << "Kendaraan berikutnya langsung masuk ke area parkir dari antrian\n";
    } else {
        cout << "\nKendaraan berhasil keluar\n";
    }

    pushStack("KELUAR", noPolisi, noAntrian);
}

void hapusDataKendaraan() {
    headerMenu("                 HAPUS DATA KENDARAAN             ");

    string noPolisi;

    cout << "Masukkan Nomor Polisi yang ingin dihapus : ";
    getline(cin, noPolisi);

    Kendaraan* data = cariKendaraan(root, noPolisi);

    if (data == NULL) {
        cout << "\nKendaraan tidak ditemukan!\n";
        return;
    }

    if (data->diParkiran) {
        jumlahParkir--;
    }

    hapusDariQueue(noPolisi);
    root = hapusDariPTB(root, noPolisi);

    cout << "\nData kendaraan berhasil dihapus\n";
}

void undoAksi() {
    headerMenu("            UNDO AKSI TERAKHIR            ");

    string aksi, noPolisi, noPolisiAntrian;

    if (!popStack(aksi, noPolisi, noPolisiAntrian)) {
        cout << "Tidak ada aksi untuk di-undo\n";
        return;
    }

    Kendaraan* data = cariKendaraan(root, noPolisi);

    if (data == NULL) {
        cout << "Data kendaraan pada riwayat sudah dihapus, undo dibatalkan.\n";
        return;
    }

    if (aksi == "MASUK") {
		if (data->diParkiran) {
			data->diParkiran = false;
        	jumlahParkir--;

        if (!queueKosong()) {
            string noAntrian;
            dequeue(noAntrian);
			
			Kendaraan* kendaraanAntri = cariKendaraan(root, noAntrian);

            if (kendaraanAntri != NULL) {
                kendaraanAntri->diParkiran = true;
                jumlahParkir++;
            }
        }
    }
		cout << "Undo: Kendaraan masuk dibatalkan\n";
    } else if (aksi == "KELUAR") {

    if (noPolisiAntrian != "") {

        Kendaraan* dataAntrian =
            cariKendaraan(root, noPolisiAntrian);

        if (dataAntrian != NULL &&
            dataAntrian->diParkiran) {

            dataAntrian->diParkiran = false;
            jumlahParkir--;

            enqueueDepan(noPolisiAntrian);
        }
    }

    if (!data->diParkiran) {
        data->diParkiran = true;
        jumlahParkir++;
    }
		cout << "Undo: Kendaraan keluar dibatalkan\n";
	}
}

void tampilAntrian() {
    headerMenu("               ANTRIAN KENDARAAN                 ");

    if (queueKosong()) {
        cout << "           Antrian kosong\n                  ";
        return;
    }

    QueueNode* bantu = frontQueue;
    int nomor = 1;

    while (bantu != NULL) {
        cout << nomor << ". " << bantu->noPolisi << " menunggu giliran masuk parkiran\n";
        bantu = bantu->next;
        nomor++;
    }
}

void menu() {
    int pilihan;

    do {
        cls();

        garis();
        cout << "        SISTEM PARKIR INAP BANDARA GSA             \n";
        garis();
        cout << "Kapasitas Parkir : " << kapasitasParkir << endl;
        cout << "Terisi           : " << jumlahParkir << endl;
        garis();
        cout << "1. Tambah Data Kendaraan\n";
        cout << "2. Tampil Kendaraan\n";
        cout << "3. Catat Kendaraan Masuk\n";
        cout << "4. Catat Kendaraan Keluar\n";
        cout << "5. Hapus Data Kendaraan\n";
        cout << "6. Undo Aksi Terakhir\n";
        cout << "7. Tampilkan Antrian Kendaraan\n";
        cout << "0. Keluar\n";
        garis();
        cout << "Pilih menu : ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tambahDataKendaraan();
                break;
            case 2:
                tampilKendaraan();
                break;
            case 3:
                kendaraanMasuk();
                break;
            case 4:
                kendaraanKeluar();
                break;
            case 5:
                hapusDataKendaraan();
                break;
            case 6:
                undoAksi();
                break;
            case 7:
                tampilAntrian();
                break;
            case 0:
                cls();
                garis();
                cout << "               Program selesai.\n";
                garis();
                break;
            default:
                headerMenu("MENU TIDAK TERSEDIA");
                cout << "Pilihan tidak tersedia.\n";
        }

        if (pilihan != 0) {
            jeda();
        }

    } while (pilihan != 0);
}

int main() {
    menu();
    return 0;
}
