#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int rows = 20;
const int cols = 40;

char board[rows][cols];

int pacman_row, pacman_col;
int num_dots = 0;

void initialize_board();
void print_board();
bool move_pacman(int, int);

int main() {

	srand(time(NULL));
	initialize_board();

	while (num_dots > 0) { // Bütün yemlər yeyilənə qədər dövr işləyəcək

		print_board();
		char move = _getch(); // Klaviaturadan hərəkət etdirmək

		int move_row = 0, move_col = 0;
		if (move == 'w') { //Yuxarı
			move_row = -1; 
		}
		else if (move == 'a') { //Sol
			move_col = -1;
		}
		else if (move == 's') { //Aşağı
			move_row = 1;
		}
		else if (move == 'd') { //Sağ
			move_col = 1;
		}
		if (move_pacman(move_row, move_col)) { // Pockman'in hərəkət etməsi
			num_dots = num_dots;
		}
		else {
			cout << endl << "Oyun bitdi! :/" << endl;
			return 0;
		}
	}
	cout << endl << "Tebrikler, qazandiniz! :))" << endl;
	cout << "Yeyilen yem sayi : " << 40 - num_dots << endl;
	return 0;
}

void initialize_board() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
				board[i][j] = '#'; // Boardın sərhəd divarları
			}
			else {
				int random_num = rand() % 100;
				if (random_num < 80) {
					board[i][j] = ' '; // Boşluqlar
				}
				else if (random_num < 90) {
					board[i][j] = '.'; // Yeməklər
					num_dots++;
				}
				else {
					board[i][j] = '#'; // Divarlar
				}
			}
		}
	}
	// Pockmanin başlanğıc yerinin random seçilməsi
	do {
		pacman_row = rand() % rows;
		pacman_col = rand() % cols;
	} while (board[pacman_row][pacman_col] != ' ');
	board[pacman_row][pacman_col] = 'C'; // Pockman
}

void print_board() {
	system("cls");
	cout << "========== Pockman oyununa xos geldiniz ! ==========" << endl;
	cout << "Oyunun qaydalari ile tanis olun : " << endl;
	cout << "1. C herfi sizin Pockman'dir." << endl;
	cout << "2. W - yuxari, S - asagi, A - sola, D - saga hereketdir." << endl;
	cout << "3. Divarlara deydikde oyun bitecek." << endl;
	cout << "4. Sadece butun yemekleri yedikde oyunu qazanacaqsiniz." << endl;
	cout << "====================================================" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
}

bool move_pacman(int move_row, int move_col) {
	int new_row = pacman_row + move_row;
	int new_col = pacman_col + move_col;
	if (board[new_row][new_col] == '#') { // Divara dəyib dəymədiyini yoxlamaq
		return false;
	}
	if (board[new_row][new_col] == '.') { // Yeməyi yeyib yemədiyini yoxlamaq
		num_dots--;
		board[new_row][new_col] = ' '; // Yeyilən yeməyin yerinə boşluq qoyulması
	}
	board[pacman_row][pacman_col] = ' '; // Əvvəlki yerin boşluq olaraq güncəllənməsi
	pacman_row = new_row;
	pacman_col = new_col;
	board[pacman_row][pacman_col] = 'C'; // Yeni yerin pockman olaraq güncəllənməsi
	return true;
}