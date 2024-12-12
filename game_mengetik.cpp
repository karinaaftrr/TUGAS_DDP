#include <ncurses/curses.h>
#include <fstream>
#include <string>
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
        mvprintw(1, 1, "== Highest Score =="); 
        int y = 2;
        while (getline(file, baris)) {
            mvprintw(y++, 0, "%s", baris.c_str());
        }
        file.close();
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
    for (int f = 0; f < 5; f++) {
        switch (f) { 
            case 0: attron(COLOR_PAIR(1)); 
			break;  
            case 1: attron(COLOR_PAIR(6)); 
			break; 
            case 2: attron(COLOR_PAIR(3)); 
			break;  
            case 3: attron(COLOR_PAIR(4)); 
			break; 
            case 4: attron(COLOR_PAIR(5));
			 break; 
        }
        mvprintw(10, (COLS - 80) / 2, "  ||         ||   |||||||   ||         |||||       |||||     ||||||||||   |||||||   ");
        mvprintw(11, (COLS - 80) / 2, "  ||         ||   ||        ||       ||     ||   ||     ||   ||  ||  ||   ||        ");
        mvprintw(12, (COLS - 80) / 2, "  ||   |||   ||   |||||||   ||       ||          ||     ||   ||  ||  ||   |||||||   ");
        mvprintw(13, (COLS - 80) / 2, "  ||   |||   ||   |||||||   ||       ||          ||     ||   ||  ||  ||   |||||||   ");
        mvprintw(14, (COLS - 80) / 2, "  ||   |||   ||   ||        ||       ||     ||   ||     ||   ||  ||  ||   ||        ");
        mvprintw(15, (COLS - 80) / 2, "     | _  _ |     |||||||   |||||||    |||||       |||||     ||  ||  ||   |||||||   ");
        mvprintw(16, (COLS - 80) / 2, "                                                                                     ");

        attroff(COLOR_PAIR(1) | COLOR_PAIR(6) | COLOR_PAIR(3) | COLOR_PAIR(4) | COLOR_PAIR(5)); 
        refresh();
        Sleep(1500);
    }  
    int posisiY = 18; 
    int posisiX = (COLS - 15) / 2; 
    for (int i = 0; i <= 3; i++) {
        mvprintw(posisiY, posisiX, "-------------------");
        mvprintw(posisiY + 1, posisiX, "[                 ]");
        mvprintw(posisiY + 2, posisiX, "-------------------");

        for (int j = 0; j <= 15; j++) {
            mvprintw(posisiY + 1, posisiX + j + 1, ">");
            refresh();
            Sleep(200); 
        }
    }
    refresh();
}

void animasiTeksBaris(const char* teks, int mulaiY, int mulaiX, int pasanganWarna) {
    attron(COLOR_PAIR(1));
    int panjangTeks = strlen(teks);

    for (int i = 0; i < panjangTeks; ++i) {
        mvprintw(mulaiY, mulaiX + i, "%c", teks[i]); 
        refresh();
        Sleep(100); 
    }
    attroff(COLOR_PAIR(1));
}

void tampilkanMenuAwal() {
    int sorot = 0;
    const char* opsi[] = { "Start Game", "Top Scores", "Exit?" };
    int jumlahOpsi = sizeof(opsi) / sizeof(opsi[0]);
    bool isMenuAwalDitampilkan = false; 
    clear();
    animasiTeksBaris("=== TYPERACER'S GAME ===", LINES / 2 - 3, (COLS - 22) / 2, 2);
    refresh();  
    while (true) {
        clear();
	attron(COLOR_PAIR(1)); 
        mvprintw(LINES / 2 - 3, (COLS - 22) / 2, "=== TYPERACER'S GAME ===");              
        if (!isMenuAwalDitampilkan) {
            isMenuAwalDitampilkan = true; 
        }
        for (int i = 0; i < jumlahOpsi; i++) {
            if (i == sorot) {
                attron(COLOR_PAIR(1) | A_REVERSE);
            } else {
                attron(COLOR_PAIR(3));
            }
            mvprintw(LINES / 2 + i, (COLS - strlen(opsi[i])) / 2, opsi[i]);
            attroff(COLOR_PAIR(3));
            attroff(COLOR_PAIR(1) | A_REVERSE); 
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
                    isMenuAwalDitampilkan = false;			 
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


int tampilkanMenuLevel() {
    int sorot = 0;
    const int baris = 5, kolom = 4;
    const int levelPerHalaman = baris * kolom;

    while (true) {
        clear();
        mvprintw(LINES / 2 - baris / 2 - 2, (COLS - 18) / 2, "=== Select Levels ===");

        int mulaiY = (LINES - baris) / 2;
        int mulaiX = (COLS - (kolom * 15)) / 2;

        for (int barisIndex = 0; barisIndex < baris; ++barisIndex) {
            for (int kolomIndex = 0; kolomIndex < kolom; ++kolomIndex) {
                int indeks = barisIndex * kolom + kolomIndex;
                if (indeks >= totalLevel) break;

                int posisiY = mulaiY + barisIndex;
                int posisiX = mulaiX + kolomIndex * 15;

                if (indeks == sorot) {
                    attron(A_REVERSE | A_BOLD);
                }
                if (indeks < levelMaksTersedia) {
                    mvprintw(posisiY, posisiX, "Level %d", indeks + 1);
                } else {
                    mvprintw(posisiY, posisiX, "locked");
                }
                attroff(A_REVERSE | A_BOLD);
            }
        }

        refresh();

        int ch = getch();
        switch (ch) {
            case KEY_UP:
                if (sorot >= kolom) sorot -= kolom;
                break;
            case KEY_DOWN:
                if (sorot + kolom < totalLevel) sorot += kolom;
                break;
            case KEY_LEFT:
                if (sorot % kolom > 0) sorot--;
                break;
            case KEY_RIGHT:
                if (sorot % kolom < kolom - 1 && sorot + 1 < totalLevel) sorot++;
                break;
            case '\n':
                if (sorot < levelMaksTersedia) {
                    return sorot + 1;
                }
                break;
            default:
                break;
        }
    }
}

bool mainkanLevel(int level) {
    clear();
    const char* teksTarget = levelTeks[level - 1];

    mvprintw(2, (COLS - strlen(teksTarget)) / 2, teksTarget);
     mvprintw(LINES - 3, COLS - 15, "------------"); 
    mvprintw(LINES - 4, COLS - 15, "[Ur Life: %d]", nyawa);  
    mvprintw(LINES - 5, COLS - 15, "------------"); 
    refresh();

    string input;
    int ch;
    DWORD startTime = GetTickCount(); 

    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) { 
            if (!input.empty()) {
                input.pop_back();
                int inputLen = input.length();
                mvprintw(4, (COLS - strlen(teksTarget)) / 2 + inputLen, " ");
                move(4, (COLS - strlen(teksTarget)) / 2 + inputLen);
            }
        } else {
            input.push_back(ch);
        }

        for (size_t i = 0; i < input.length(); ++i) {
            if (i < strlen(teksTarget) && input[i] == teksTarget[i]) {
                attron(COLOR_PAIR(2) | A_BOLD); 
            } else {
                attron(COLOR_PAIR(3) | A_BOLD); 
            }
            mvprintw(4, (COLS - strlen(teksTarget)) / 2 + i, "%c", input[i]);
            attroff(COLOR_PAIR(2) | A_BOLD);
            attroff(COLOR_PAIR(3) | A_BOLD);
        }
        refresh();
    }

    DWORD endTime = GetTickCount();  
    double waktu = (endTime - startTime) / 1000.0;

    clear();
    if (input == teksTarget) {
        double kataPerMenit = (input.length() / 5.0) / (waktu / 60.0);
        mvprintw(LINES / 2 - 1, (COLS - 30) / 2, "Level %d succed!", level);
        mvprintw(LINES / 2, (COLS - 50) / 2, "Time: %.2f Second | Speed: %.2f KPM", waktu, kataPerMenit);
        mvprintw(LINES / 2 + 2, (COLS - 30) / 2, "Press any button to continue.");
        refresh();
        simpanSkorTertinggi(level, kataPerMenit, waktu);  
        levelMaksTersedia++;  
        getch();
        return true;
    } else {
        mvprintw(LINES / 2, (COLS - 30) / 2, "Wrong text! ur life will be reduced.");
        nyawa--; 
        if (nyawa <= 0) {
            mvprintw(LINES / 2 + 1, (COLS - 30) / 2, "Game over!.");
            refresh();
            getch();
            return false;
        }
        mvprintw(LINES / 2 + 1, (COLS - 30) / 2, "Press any button to continue.");
        refresh();
        getch();
        return true;
    }
}

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    inisialisasiWarna();

    animasiTeks("");

    tampilkanMenuAwal();
        while (true) {
            int level = tampilkanMenuLevel();
            if (level == -1) break;
            if (!mainkanLevel(level)) break;
        }
    
        endwin();
        return 0;
}
