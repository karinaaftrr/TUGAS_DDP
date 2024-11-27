#include <iostream>
#include <ncurses/curses.h>
#include <fstream>
#include <windows.h>
using namespace std;

const char* levelTeks[] = {
    "ilmu komputer",
    "anak ilmu komputer mantap",
    "disini anak unila, senggol dong",
    "semangka enak dimakan pakai sendok",
    "udah tidur siang bangun kesiangan lagi",
    "ayo jangan lupa belajar dasar-dasar pemrograman",
    "cobain belajar c++ dijamin sangat seru dan menyenangkan",
    "apa? uap pake python? pake c++ aja error mulu",
    "pengkodean adalah proses menulis instruksi agar komputer mengikuti sesuai perintah",
    "sistem bilangan biner menggunakan angka 0 dan 1 untuk merepresentasikan data",
    "komputer cepat, tapi saya yang lemot dalam menggunakannya",
    "Komputer gua cepet banget, cuma harus butuh wifi yang oke punya",
    "komputer saya sering lemot, kayaknya dia juga butuh kopi biar bisa bekerja dengan cepat",
    "yang semangat dong syntax error, yang semangat dong, maneh we sendiri aing mah capek pengen sare",
    "codingan mah kek main detektif cuy, setiap bug yang muncul selalu main petak umpet dengan pintar",
    "syntax error itu seperti pacar yang marah, salah sedikit langsung keluar peringatan, bikin bingung",
    "teknologi informasi (it) sangat berperan penting dalam meningkatkan efisiensi, pengelolaan data, dan komunikasi dalam berbagai aspek kehidupan modern",
    "jangan ragu jangan bimbang bersama anak ilmu komputer di jamin meriang dan seketika cosplay truk oleng menyala mental kuu",
    "dengan adanya pemanfaatan teknologi informasi (it) memungkinkan integrasi data, pengelolaan sistem, komunikasi global, serta otomatisasi proses dalam berbagai sektor kehidupan manusia",
    "Teknologi Informasi (IT) telah menjadi kunci utama dalam mempercepat inovasi, meningkatkan efisiensi kerja, memperluas komunikasi global, dan mendukung pengelolaan data secara optimal"
};

const int totalLevel = 20;
const char* fileSkor = "top_score.txt"; 
int nyawa = 3; 
int levelMaksTersedia = 1;  

void muatSkorTertinggi() {
    ifstream file(fileSkor);
    if (file) {
        string baris;
        mvprintw(1, 0, "== Highest Score =="); 
        int y = 2;
        while (getline(file, baris)) {
            mvprintw(y++, 0, "%s", baris.c_str());
        }
        file.close();
        getch();
    } else {
        mvprintw(1, 0, "There Are No Saved Scores Yet.");
        getch();
    }
}
void simpanSkorTertinggi(int level, double kataPerMenit, double waktu) {
    fstream file(fileSkor, ios::in | ios::out | ios::app);
    if (file) {
        file << "Level " << level << ": " << kataPerMenit << " KPM, " 
             << waktu << " second\n";
        file.close();
    }
}

void inisialisasiWarna() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);  
    init_pair(2, COLOR_GREEN, COLOR_BLACK);  
    init_pair(3, COLOR_RED, COLOR_BLACK);    
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); 
    init_pair(5, COLOR_CYAN, COLOR_BLACK);   
}

void animasiTeks(const char* teks) {
    clear();
    int panjangTeks = strlen(teks);
    int posisiX = (COLS - panjangTeks) / 2;
    int posisiY = LINES / 2;

    for (int warna = 1; warna <= 5; ++warna) {
        attron(COLOR_PAIR(warna) | A_BOLD);
        mvprintw(posisiY, posisiX, teks);
        attroff(COLOR_PAIR(warna) | A_BOLD);
        refresh();
        Sleep(500); 
    }
    Sleep(1500); 
}

void animasiTeksBaris(const char* teks, int mulaiY, int mulaiX, int pasanganWarna) {
    attron(COLOR_PAIR(5) | A_BOLD);
    int panjangTeks = strlen(teks);

    for (int i = 0; i < panjangTeks; ++i) {
        mvprintw(mulaiY, mulaiX + i, "%c", teks[i]); 
        refresh();
        Sleep(100); 
    }
    attroff(COLOR_PAIR(1) | A_BOLD);
}

void tampilkanMenuAwal() {
    int sorot = 0;
    const char* opsi[] = { "Start Game", "Top Scores", "Exit?" };
    int jumlahOpsi = sizeof(opsi) / sizeof(opsi[0]);

    while (true) {
        clear();
        animasiTeksBaris("=== TYPERACER'S GAME ===", LINES / 2 - 3, (COLS - 22) / 2, 2);

        for (int i = 0; i < jumlahOpsi; i++) {
            if (i == sorot) {
                attron(COLOR_PAIR(1) | A_REVERSE | A_BOLD);
            } else {
                attron(COLOR_PAIR(3) | A_BOLD);
            }
            mvprintw(LINES / 2 + i, (COLS - strlen(opsi[i])) / 2, opsi[i]);
            attroff(COLOR_PAIR(3) | A_REVERSE | A_BOLD);
            attroff(COLOR_PAIR(1) | A_BOLD);
        }

        refresh();
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                if (sorot > 0) sorot--;
                break;
            case KEY_DOWN:
                if (sorot < jumlahOpsi - 1) sorot++;
                break;
            case '\n':
                if (sorot == 0) {
                    return; 
                } else if (sorot == 1) {
                    clear();
                    muatSkorTertinggi(); 
                } else if (sorot == 2) {
                    endwin();
                    exit(0);
                }
                break;
            default:
                break;
        }
    }
}
