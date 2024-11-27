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
