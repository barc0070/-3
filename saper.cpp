#include <iostream>;
#include <fstream>;
#include <string>;
using namespace std;

int field[100][100]; 
int p_field[100][100];
int row = 9, col = 9, k = 10;

void set_field() {
	srand(time(nullptr));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) { 
			field[i][j] = 0; 
			p_field[i][j] = -3; 
		}
	}
	for (int i = 0; i < k; i++) {
		int x = rand() % row;
		int y = rand() % col;
		if (field[x][y] == 0) field[x][y] = -1; 
		else i--; 
	}
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++) {
			if (field [i][j]!= -1)
			{
				for (int i2 = i - 1; i2 <= i + 1; i2++) { 
					for (int j2 = j - 1; j2 <= j + 1; j2++) {
						if (i2 >= 0 && j2 >= 0 && i2 < row && j2 < col && field[i2][j2] == -1) {  
							field[i][j]++; 
						}
					}
				}
			}
		}
	}
	cout << "field is ready!"<<'\n';
	ofstream out; 
	out.open("E:\\games\\saper.txt");
	if (out.is_open()) {
		out << "    ";
		for (int j = 0; j < col; j++) {
			out << (j + 1) << ")  ";
		}
		out << '\n';
		for (int i = 0; i < row; i++) {
			out << (1 + i) << ")  ";
			for (int j = 0; j < col; j++) {
				if (field[i][j] == -1) out << "*   ";
				else out << field[i][j] << "   ";
			}
			out << '\n';
		}
		cout << "Field has successfully saved to file!" << '\n';
	}
	else cout << "Error"<<'\n';
	out.close();
}



void print_field() {
	system("cls");
cout << "\\o - open, \\f - flag,\\n - new game, \\q - quit game\n"; 
	cout << "   ";
	for (int j = 0; j < col; j++) {
		cout << (j + 1) << ") "; 
	}
	cout << '\n';
	for (int i = 0; i < row; i++) {
		cout << (1 + i) << ") "; 
		for (int j = 0; j < col; j++) {
			if (p_field[i][j] == -3) cout << "_   ";
			else if (p_field[i][j] == -2) cout << "f  ";
			else if (p_field[i][j] == -1) cout << "*  ";
			else cout << p_field[i][j] << "  "; 
		}
		cout << '\n';
	}
}

void set_flag(int x, int y) {
	if (p_field[x][y] == -2)p_field[x][y] = -3;
	else if (p_field[x][y] == -3) p_field[x][y] = -2; 
	print_field();
}

void dfs_open(int x, int y) {
	if (p_field[x][y] > -2) return; 
	p_field[x][y] = field[x][y];
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (i >= 0 && j >= 0 && i < row && j < col && (i != x || j != y))
			{
				if (field[i][j] > 0) p_field[i][j] = field[i][j];
				if (field[i][j] == 0) dfs_open(i, j);
			} 
		}
	}
}

bool open_cell(int x, int y) {
	if (x >= 0 && y >= 0 && x < row && y < col && p_field[x][y] < -1) {
		if (field[x][y] == -1) return false;
		else if (field[x][y] > 0) p_field[x][y] = field[x][y];
		else dfs_open(x, y);
	}
	print_field();
	return true;
}

void end_game(bool is_victory) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			p_field[i][j] = field[i][j];
		} 
	}
	print_field();
	if (is_victory) cout << "You won! Press Enter any string to restart";
	else cout << "You lost! Press Enter ane string to restart";
	string c;
	cin >> c; 
}

bool defused () {
	int num_k = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (p_field[i][j] == -3) num_k++;
		} 
	}
	if (num_k == k) return true;
	else return false;
}

int main(){
	while(true)
	{
		set_field();
		print_field();
		while (true) {
			string command; 
			cin >> command;
			if (command == "\\o") {
				int x, y;
				cin >> x >> y;
				x--; y--;
				if (!open_cell(x, y)) {
					end_game(false); 
					break;
				}
				if (defused()) {
					end_game(true);
					break;
				}
			}
			else if (command == "\\f") {
				int x, y;
				cin >> x >> y; 
				x--; y--;
				if (x >= 0 && y >= 0 && x < row&& y < col) set_flag(x, y);
			}
			else if (command == "\\n") { 
				break;
			}
			else if (command == "\\q") { 
				return 0;
			}
		}
	}
}