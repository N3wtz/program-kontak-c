#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>

struct kontak
{
    char nama[100];
    char nomor[20];
    char email[100];
    char alamat[200];
} data;

void tambah();
void edit();
void cari();
void lihat();
void hapus();
void hapussemua();
void menu();
void garis();
void keluar();
char pilihan;

int main()
{
    system("COLOR 70");
    printf("\n|=======================================|");
    printf("\n|\t.::PROGRAM ASISTEN KONTAK::.\t|");
    printf("\n|\t\tVersion 1.1\t\t|");
    printf("\n|                                       |");
    printf("\n|\t\tcreated by:\t\t|");
    printf("\n|\t\tKELOMPOK 1\t\t|");
    printf("\n|\tS1 Teknik Informatika 2022\t|");
    printf("\n|\t    UNIVERSITAS UDAYANA\t\t|");
    printf("\n|=======================================|\n\n");

    int i;
    printf("Memulai Aplikasi ");
    char AppStarting[10] = ".....";
    for (i = 0; i < strlen(AppStarting); i++)
    {
        printf("%c", AppStarting[i]);
        Sleep(670);
    }
    system("cls");

    menu();
    return 0;
}

//-----------INI FUNGSI UNTUK MENU UTAMA-------------
void menu()
{
    int menu = 1; // Menu awal dipilih
    int ch;       // Untuk menyimpan input tombol

    do
    {
        system("cls");
        printf("\n============= Menu  Utama ==============\n\n");

        // Mencetak menu dengan menandai pilihan saat ini
        for (int i = 1; i <= 7; i++)
        {
            if (i == menu)
                printf("\t -> ");
            else
                printf("\t    ");

            switch (i)
            {
            case 1:
                printf("Tambah kontak\n");
                break;
            case 2:
                printf("Edit kontak\n");
                break;
            case 3:
                printf("Cari kontak\n");
                break;
            case 4:
                printf("Lihat kontak\n");
                break;
            case 5:
                printf("Hapus kontak\n");
                break;
            case 6:
                printf("Hapus semua \n");
                break;
            case 7:
                printf("Keluar [ESC] \n");
                break;
            }
        }
        garis();
        printf("\n");

        // Membaca input dari pengguna
        ch = getch();

        // Menggunakan panah atas dan bawah untuk navigasi menu
        if (ch == 224)
        {
            ch = getch();
            if (ch == 80)
            {
                if (menu < 7)
                    menu++;
                else
                    menu = 1;
            }
            else if (ch == 72)
            {
                if (menu > 1)
                    menu--;
                else
                    menu = 7;
            }
        }

        // Menekan enter untuk memilih menu
        if (ch == 13)
        {
            switch (menu)
            { // pilih menu----
            case 1:
                system("cls");
                fflush(stdin); // clear buffer----
                tambah();
                break;
            case 2:
                system("cls");
                fflush(stdin);
                edit();
                break;
            case 3:
                system("cls");
                fflush(stdin);
                cari();
                break;
            case 4:
                system("cls");
                fflush(stdin);
                lihat();
                break;
            case 5:
                system("cls");
                fflush(stdin);
                hapus();
                break;
            case 6:
                system("cls");
                fflush(stdin);
                hapussemua();
                break;
            case 7:
                system("cls");
                keluar();
                exit(0);
                break;
            }
        }
    } while (ch != 27); // Escape untuk keluar dari aplikasi
}

//-----------INI FUNGSI UNTUK MENAMBAH KONTAK-------------
void tambah()
{
    int i = 0;
    do
    {
        FILE *td;
        td = fopen("data.txt", "a");
        printf("\n============ Tambah  Kontak ============\n\n");

        printf("  Nama: ");
        fflush(stdin);
        gets(data.nama);
        for (i; i < strlen(data.nama); i++)
        {
            data.nama[i] = tolower(data.nama[i]);
        }

        printf("  Nomor: ");
        fflush(stdin);
        scanf("%s", data.nomor);

        printf("  Email: ");
        fflush(stdin);
        scanf("%s", data.email);

        printf("  Alamat: ");
        fflush(stdin);
        gets(data.alamat);

        fwrite(&data, sizeof(struct kontak), 1, td);
        printf("\nBerhasil menambahkan kontak.....\n");
        fclose(td);

        printf("[1] Tambah kontak lainnya\n[0] Kembali ke menu utama\n ");
        pilihan = getch();
        system("cls");
    } while (pilihan == '1');
}

//-----------INI MENU UNTUK MELIHAT KONTAK-------------
void lihat()
{
    char pilih;
    do
    {
        FILE *td;
        td = fopen("data.txt", "r");
        printf("\n============= List Kontak ==============");
        while (fread(&data, sizeof(struct kontak), 1, td))
        {

            printf("\n\t Nama : %s \n\t Nomor : %s\n\t Email : %s \n\t Alamat : %s \n", data.nama, data.nomor, data.email, data.alamat);
            garis();
        }

        fseek(td, 0, SEEK_END);
        if (ftell(td) == 0)
        {
            printf("\n\n\t..= Kontak masih kosong =..\n");
        }

        fclose(td);

        printf("\n[0] Kembali ke menu utama\n ");
        pilih = getch();
        system("cls");
    } while (pilih != '0');
}

//-----------INI MENU UNTUK CARI KONTAK-------------
void cari()
{
    char target[100];
    char *hasil;
    system("cls");

    do
    {
        int i = 0;
        fflush(stdin);
        FILE *td;
        td = fopen("data.txt", "r");
        printf("\n============= Cari kontak ==============\n");
        printf("\tKontak yang ingin dicari: ");
        gets(target);

        for (i; i < strlen(target); i++)
        {
            target[i] = tolower(target[i]);
            if (isspace(target[i]) || strlen(target) == 0)
            {
                garis();
                printf("\n\t   Input kosong\n");
                garis();
            }
            else
            {
                while (fread(&data, sizeof(struct kontak), 1, td))
                {
                    hasil = strstr(data.nama, target);
                    if (hasil)
                    {
                        printf("\n\t Nama : %s \n\t Nomor : %s\n\t Email : %s\n \t Alamat : %s\n", data.nama, data.nomor, data.email, data.alamat);
                        garis();
                    }
                }
                if (!hasil)
                {
                    garis();
                    printf("\n\t      data tiada\n");
                    garis();
                }
            }
        }

        printf("\n[1] Cari kontak lainnya\n[0] Kembali ke menu utama\n ");
        pilihan = getch();
        fclose(td);
        system("cls");
    } while (pilihan == '1');
}

//-----------INI MENU UNTUK DELETE KONTAK-------------
void hapus()
{
    do
    {
        fflush(stdin);
        FILE *td;
        FILE *tdcopy;
        char nakon[30];
        int benar = 0;
        int hasil;

        td = fopen("data.txt", "r");
        tdcopy = fopen("copy.txt", "w");
        printf("\n============= Hapus Kontak =============\n");
        printf("Masukkan nama kontak yang akan dihapus : ");
        scanf("%[^\n]", &nakon);
        while (fread(&data, sizeof(struct kontak), 1, td))
        {
            hasil = strcmp(nakon, data.nama);
            if (hasil == 0)
            {
                benar++;
            }
            else
            {
                fwrite(&data, sizeof(struct kontak), 1, tdcopy);
            }
        }
        fclose(td);
        fclose(tdcopy);

        if (benar)
        {
            remove("data.txt");
            rename("copy.txt", "data.txt");
            printf("\nKontak berhasil dihapus.....\n");
        }
        else
        {
            printf("\nNama kontak tidak ditemukan!\n");
        }

        printf("\n[1] Hapus kontak lainnya\n[0] Kembali ke menu utama\n ");
        pilihan = getch();
        system("cls");

    } while (pilihan == '1');
}

//-----------INI MENU UNTUK DELETE SEMUA KONTAK-------------
void hapussemua()
{
    fflush(stdin);
    FILE *td;
    FILE *tdcopy;
    char nakon[30];
    int benar = 0;
    int hasil;
    char pilih;
    td = fopen("data.txt", "r");
    tdcopy = fopen("copy.txt", "w");
    printf("\n========== Hapus Semua Kontak ==========\n");
    printf("Yakin hapus semua kontak?\n[y] Hapus Semua Kontak\n[n] Batal\nPilihan: ");
    scanf(" %c", &pilih);

    if (pilih == 'y')
    {

        while (fread(&data, sizeof(struct kontak), 1, td))
        {

            fwrite(&data, sizeof(struct kontak), 0, tdcopy);
        }

        fclose(td);
        fclose(tdcopy);

        remove("data.txt");
        rename("copy.txt", "data.txt");

        printf("\nSeluruh kontak berhasil dihapus.....\n");
        printf("\n[0] Kembali ke menu utama\n ");
        scanf(" %c", &pilih);
        system("cls");
        if (pilih == '0')
        {
        }
    }
    else
    {
        menu();
    }
}

//-----------INI MENU UNTUK EDIT KONTAK-------------
void edit()
{

    do
    {
        fflush(stdin);
        FILE *td;
        FILE *tdcopy;
        char nakon[30];
        int benar = 0;
        int hasil;

        td = fopen("data.txt", "r");
        tdcopy = fopen("copy.txt", "w");
        printf("\n============= Edit kontak ==============\n");
        printf("Masukkan nama kontak yang akan diedit : ");
        scanf("%[^\n]", &nakon);
        while (fread(&data, sizeof(struct kontak), 1, td))
        {
            hasil = strcmp(nakon, data.nama);
            if (hasil == 0)
            {
                benar++;
                printf("  Nama baru: ");
                fflush(stdin);
                gets(data.nama);

                printf("  Nomor baru: ");
                fflush(stdin);
                scanf("%s", data.nomor);

                printf("  Email baru: ");
                fflush(stdin);
                scanf("%s", data.email);

                printf("  Alamat baru: ");
                fflush(stdin);
                scanf("%s", data.alamat);
                fwrite(&data, sizeof(struct kontak), 1, tdcopy);
            }
            else
            {
                fwrite(&data, sizeof(struct kontak), 1, tdcopy);
            }
        }
        fclose(td);
        fclose(tdcopy);

        if (benar)
        {
            remove("data.txt");
            rename("copy.txt", "data.txt");
            printf("\nKontak berhasil diubah.....\n");
        }
        else
        {
            printf("\nNama kontak tidak ditemukan!");
        }
        printf("\n[1]cari kontak lainnya\n[0]Kembali ke menu utama\n ");
        pilihan = getch();
        system("cls");

    } while (pilihan == '1');
}

//-----------INI FUNGSI UNTUK PEMBATAS-------------
void garis()
{
    int i = 0;
    for (i; i < 40; i++)
    {
        printf("-");
    }
}

void keluar()
{
    int i;
    printf("=========== Sekian Terimakasih ===========\n\nMenutup aplikasi");
    char AppStarting[10] = ".....";
    for (i = 0; i < strlen(AppStarting); i++)
    {
        printf("%c", AppStarting[i]);
        Sleep(500);
    }
    system("cls");
}
