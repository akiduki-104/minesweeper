#include <bits/stdc++.h>
using namespace std;
#define MINE 10 // 爆弾数
#define WD 9 // 盤面横数
#define HT 9 // 盤面縦数
vector<vector<bool> > open(HT + 2, vector<bool>(WD + 2, 0)); //開いているか
vector<vector<bool> > mine(HT + 2, vector<bool>(WD + 2, 0)); //爆弾位置
vector<vector<bool> > opn(HT + 2, vector<bool>(WD + 2, 0)); //連続オープンチェック
vector<vector<int> > ct(HT + 2, vector<int>(WD + 2, 0)); //周囲の爆弾
const vector<string> zen = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
const int dx[8] = { 1, 0, -1, 0, 1, -1, -1, 1 };
const int dy[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };
queue<pair<int, int> > li; //連続オープンリスト
int cnt = 0; //未開のマス;
random_device seed_gen;
mt19937 engine(seed_gen()); //乱数

void resetboad()
{
    for (int i = 0; i < HT + 2; i++) {
        for (int j = 0; j < WD + 2; j++) {
            open[i][j] = 0;
            mine[i][j] = 0;
            opn[i][j] = 0;
        }
    }

    for (int i = 0; i < MINE; i++) {
        int wd = engine() % WD + 1, ht = engine() % HT + 1;
        if (mine[ht][wd] == 1) {
            continue;
        }
        mine[ht][wd] = 1;
        for (int i = 0; i < 8; i++) {
            ct[ht + dy[i]][wd + dx[i]]++;
        }
    }
}
void plt()
{
    cnt = 0;
    for (int i = 0; i < HT + 1; i++) {
        if (i == 0) {
            cout << "　１２３４５６７８９" << endl;
            continue;
        }
        for (int j = 0; j < WD + 1; j++) {
            if (j == 0) {
                cout << ;
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
void op()
{
    while (!li.empty()) {
        int a, b;
        a = li.front().first;
        b = li.front().second;
        li.pop();
        if (ct[a][b] == 0) {
            opn[a][b] = 1;
            for (int i = 0; i < 8; i++) {
                open[a + dy[i]][b + dx[i]] = 1;
                if (ct[a + dy[i]][b + dx[i]] == 0 && a + dy[i] > 0 && a + dy[i] < HT + 1 && b + dx[i] > 0 && b + dx[i] < WD + 1 && opn[a + dy[i]][b + dx[i]] == 0) {
                    li.push(make_pair(a + dy[i], b + dx[i]));
                }
            }
        }
    }
}

int main()
{
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
            if (a < 1 || a > 9 || b < 1 || b > 9) {
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
            li.push({ a, b });
            op();
        }
        do {
            cout << "続けますか？[yes][no]" << endl;
            cin >> s;
        } while (s != "yes" && s != "no");
    }
}
