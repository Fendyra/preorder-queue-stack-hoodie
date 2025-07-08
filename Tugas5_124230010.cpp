#include <iostream>
#include <cstdlib>
using namespace std;

#define True 1
#define False 0
// Limitasi Customer PO
#define max 100 

struct Preorder {
    int nomorOrder;
    string namaPelanggan;
    string ukuranHoodie; 
};

struct Packing {
    int nomorPacking;
    int nomorOrder;
    string namaPelanggan;
};

struct TypeQueue {
    Preorder info;
    TypeQueue* next;
};

struct TypeStack {
    Packing info;
    TypeStack* next;
};

TypeQueue* qdepan = nullptr;
TypeQueue* qbelakang = nullptr;
TypeStack* TopStack = nullptr;
int queue = 0;

void buatqueue();
int queuekosong();
void enqueue(Preorder IB);
void dequeue();
void cetakqueue();
void menu();

void initstack();
int stackkosong();
void pushstack(Packing packing);
void popstack();
void cetakstack();

void buatqueue() {
    qdepan = nullptr;
    qbelakang = nullptr;
}

int queuekosong() {
    return (qdepan == nullptr) ? True : False;
}

void enqueue(Preorder IB) {
    if (queue >= max) {
        cout << "Orderan sudah penuh, tidak bisa menambah item" << endl;
        return;
    }

    TypeQueue* NB = new TypeQueue();
    NB->info = IB;
    NB->next = nullptr;

    if (queuekosong()) {
        qdepan = NB;
    } else {
        qbelakang->next = NB;
    }
    qbelakang = NB;
    queue++; 
}

void dequeue() {
    if (!queuekosong()) {
        TypeQueue* hapus = qdepan;
        cout << "Barang sedang dalam proses pengiriman:" << endl;
        cout << "Nomor Order     : " << hapus->info.nomorOrder << endl;
        cout << "Nama Pelanggan  : " << hapus->info.namaPelanggan << endl;
        cout << "Ukuran Hoodie   : " << hapus->info.ukuranHoodie << endl << endl;

        qdepan = qdepan->next;
        delete hapus;
        queue--;

        if (queuekosong()) {
            qbelakang = nullptr;
        }
    } else {
        cout << "Orderan masih kosong" << endl;
    }
}

void cetakqueue() {
    if (queuekosong()) {
        cout << "Orderan kosong atau Orderan Customer Selesai" << endl;
    } else {
        TypeQueue* cur = qdepan;
        while (cur != nullptr) {
            cout << "Nomor Order     : " << cur->info.nomorOrder << endl;
            cout << "Nama Pelanggan  : " << cur->info.namaPelanggan << endl;
            cout << "Ukuran Hoodie   : " << cur->info.ukuranHoodie << endl << endl;
            cur = cur->next;
        }
    }
    cout << endl;
}

void initstack() {
    TopStack = nullptr;
}

int stackkosong() {
    return (TopStack == nullptr) ? True : False;
}

void pushstack(Packing packing) {
    TypeStack* NS = new TypeStack();
    NS->info = packing;
    NS->next = TopStack;
    TopStack = NS;
}

void popstack() {
    if (!stackkosong()) {
        TypeStack* hapus = TopStack;
        cout << "Packing sedang dikirim:" << endl;
        cout << "Nomor Packing  : " << hapus->info.nomorPacking << endl;
        cout << "Nomor Order    : " << hapus->info.nomorOrder << endl;
        cout << "Nama Pelanggan : " << hapus->info.namaPelanggan << endl << endl;

        TopStack = TopStack->next;
        delete hapus;
    } else {
        cout << "Stack packing masih kosong" << endl;
    }
}

void cetakstack() {
    if (stackkosong()) {
        cout << "Stack packing masih kosong" << endl;
    } else {
        TypeStack* cur = TopStack;
        while (cur != nullptr) {
            cout << "Nomor Packing  : " << cur->info.nomorPacking << endl;
            cout << "Nomor Order    : " << cur->info.nomorOrder << endl;
            cout << "Nama Pelanggan : " << cur->info.namaPelanggan << endl;
            cur = cur->next;
        }
    }
    cout << endl;
}

void menu() {
    int pilihan, n;
    Preorder value;
    Packing packingValue;
    
    do {
        cout << "----------=  PROGRAM PREORDER  =----------" << endl;
        cout << "+=========================================+" << endl;
        cout << "|               MENU PO HOODIE            |" << endl;   
        cout << "+=========================================+" << endl;
        cout << "|1. Tambah Orderan                        |" << endl;
        cout << "|2. Proses Pengiriman                     |" << endl;
        cout << "|3. Tampil List Orderan                   |" << endl;
        cout << "|4. Kembali                               |" << endl;
        cout << "|5. Tambah Packing                        |" << endl;
        cout << "|6. Tampil Packing                        |" << endl;
        cout << "|7. Kirim Packing                         |" << endl;
        cout << "|8. Exit Program                          |" << endl;
        cout << "+=========================================+" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
            case 1:
                cout << "Masukkan Jumlah Orderan PO Hoodie : ";
                cin >> n;
                for (int i = 0; i < n; ++i) {
                    cout << endl;
                    cout << "Masukkan Nomor Order\t: ";
                    cin >> value.nomorOrder;
                    cout << "Masukkan Nama Pelanggan\t: ";
                    cin >> value.namaPelanggan;
                    cout << "Masukkan Ukuran Hoodie\t: ";
                    cin >> value.ukuranHoodie;
                    enqueue(value);
                }
                break;

            case 2:
                dequeue();
                system("pause");
                system("cls");          
                menu();      
                break;

            case 3:
                cetakqueue();
                system("pause");
                system("cls");
                menu();
                break;

            case 4:
                return;

            case 5:
                cout << "Masukkan Jumlah Packing : ";
                cin >> n;
                cout << endl;
                for (int i = 0; i < n; ++i) {
                    cout << "Masukkan Nomor Packing : ";
                    cin >> packingValue.nomorPacking;
                    cout << "Masukkan Nomor Order   : ";
                    cin >> packingValue.nomorOrder;
                    cout << "Masukkan Nama Pelanggan: ";
                    cin >> packingValue.namaPelanggan;
                    pushstack(packingValue);
                    cout << endl;
                }
                break;

            case 6:
                cetakstack();
                system("pause");
                system("cls");
                menu();
                break;

            case 7:
                popstack();
                system("pause");
                system("cls");
                menu();
                break;

            case 8:
                cout << "Terimakasih telah menggunakan Program.." << endl;
                exit(0);
                break;

            default:
                cout << "Pilihan tidak valid" << endl;
                break;
        }
        system("pause");
        system("cls");
    } while (pilihan != 8);
}

int main() {
    buatqueue();
    initstack();
    menu();
    return 0;
}
