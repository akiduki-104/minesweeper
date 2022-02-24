#include <C:/MinGW/bits/stdc++.h>
using namespace std;
#define     MINE    10         // 爆弾数
#define     WD     9          // 盤面横数
#define     HT      9          // 盤面縦数
vector<vector<bool>> open(HT + 2, vector<bool>(WD + 2, 0));//開いているか
vector<vector<bool>> mine(HT + 2, vector<bool>(WD + 2, 0));//爆弾位置
vector<vector<bool>> opn(HT + 2, vector<bool>(WD + 2, 0));//連続オープンチェック
vector<vector<int>> ct(HT + 2, vector<int>(WD + 2, 0));//周囲の爆弾
vector<string> zen = { "０","１","２","３","４","５","６","７","８","９" };
queue<pair<int, int>> li;//連続オープンリスト
int cnt=0;//未開のマス;

void resetboad() {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < HT + 2; i++) {
		for (int j = 0; j < WD + 2; j++) {
			open[i][j] = 0;
			mine[i][j] = 0;
			opn[i][j] = 0;
		}
	}

	for (int i = 0; i < MINE; i++) {
		int wd = rand() % WD + 1, ht = rand() % HT + 1;
		if (mine[ht][wd] == 1) {
			
			
			continue;
		}
		mine[ht][wd] = 1;
		ct[ht-1][wd-1]++;
		ct[ht - 1][wd]++;
		ct[ht-1][wd + 1]++;
		ct[ht][wd - 1]++;
		ct[ht][wd+ 1]++;
		ct[ht+1][wd - 1]++;
		ct[ht+1][wd ]++;
		ct[ht+1][wd + 1]++;
	}
}
void plt() {
	cnt = 0;
	for (int i = 0; i < HT + 1; i++) {
		if (i == 0) {
			cout << " １２３４５６７８９" << endl;
			continue;
		}
		for (int j = 0; j < WD + 1; j++) {
			if (j == 0) {
				cout << i;
				continue;
			}
			if (open[i][j] && mine[i][j]) {
				cout << "×";
			}
			else if (open[i][j]) {
				cout << zen[ct[i][j]];
			}
			else {
				cout << "□";
				cnt++;
			}
		}
		cout << endl;
	}
}
void op() {
	while (!li.empty()) {
		
		int a, b;
		a = li.front().first;
		b = li.front().second;
		li.pop();
		if (ct[a][b] == 0) {
			opn[a][b] = 1;
			for (int i =a-1; i <= a + 1; i++) {
				
				for (int j = b - 1; j <= b + 1; j++) {
					
					if (i == a && j == b) {
						continue;
					}
					open[i][j] = 1;
					if (ct[i][j] == 0&&i>0&&i<10&&j>0&&j<10&&opn[i][j]==0) {
						li.push({ i,j });
					}
					
				}
			}
		}
	}
}

int main(){
	string s;
	cout << "スタートする場合は[yes]を入力してください" << endl;
	cin >> s;
	while (s == "yes") {
		resetboad();
		while (1) {
			plt();
			if (cnt == MINE) {
				cout << "CLEAR!!!" << endl;
				break;
			}
			int a, b;
			cin >> a >> b;
			if (a < 1 || a>9 || b < 1 || b>9) {
				cout << "ERROR : out of range" << endl;
				continue;
			}
			if (open[a][b]) {
				cout << "ERROR : already opened" << endl;
				continue;
			}
			if (mine[a][b]) {
				open[a][b] = 1;
				plt();
				cout << "GAME OVER" << endl;
				break;
			}
			open[a][b] = 1;
			li.push({ a,b });
			op();
		}



		cout << "続けますか？[yes][no]" << endl;
		cin >> s;
	}
}
