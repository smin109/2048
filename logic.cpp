#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;

const int SIZE = 4;

void clearBoard(vector < vector < int > >& board) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) board[i][j] = 0;
}

void addRandomTile(vector < vector < int > >& board) {
    vector < pair < int, int > > emptyTile;

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == 0) emptyTile.push_back({i, j});

    if (!emptyTile.empty()) {
        srand(time(0));
        int index = rand() % emptyTile.size();
        int value = (rand() % 2 + 1) * 2;

        int x = emptyTile[index].first;
        int y = emptyTile[index].second;
        board[x][y] = value;
    }
}

void moveLeft(vector < vector < int > >& board) {
    for (int i = 0; i < SIZE; ++i) {
        vector < int > row;
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] != 0) row.push_back(board[i][j]);

        // 합치기
        for (int j = 0; j < row.size() - 1; ++j) {
            if (row[j] == row[j + 1]) {
                row[j] *= 2;
                row.erase(row.begin() + j + 1);
                row.push_back(0);
            }
        }

        while (row.size() < SIZE) {
            row.push_back(0);
        }

        // 결과를 board에 반영
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = row[j];
        }
    }
}

void moveRight(vector < vector < int > >& board) {
    for (int i = 0; i < SIZE; ++i) {
        vector < int > row;
        for (int j = SIZE - 1; j >= 0; --j)
            if (board[i][j] != 0) row.push_back(board[i][j]);

        // 합치기
        for (int j = 0; j < row.size() - 1; ++j) {
            if (row[j] == row[j + 1]) {
                row[j] *= 2;
                row.erase(row.begin() + j + 1);
                row.push_back(0);
            }
        }

        while (row.size() < SIZE) {
            row.push_back(0);
        }

        // 결과를 board에 반영
        for (int j = 0; j < SIZE; ++j) {
            board[i][SIZE - 1 - j] = row[j];
        }
    }
}

void moveUp(vector < vector < int > >& board) {
    for (int i = 0; i < SIZE; ++i) {
        vector < int > col;
        for (int j = 0; j < SIZE; ++j)
            if (board[j][i] != 0) col.push_back(board[j][i]);

        // 합치기
        for (int j = 0; j < col.size() - 1; ++j) {
            if (col[j] == col[j + 1]) {
                col[j] *= 2;
                col.erase(col.begin() + j + 1);
                col.push_back(0);
            }
        }

        while (col.size() < SIZE) {
            col.push_back(0);
        }

        // 결과를 board에 반영
        for (int j = 0; j < SIZE; ++j) {
            board[j][i] = col[j];
        }
    }
}

void moveDown(vector < vector < int > >& board) {
    for (int i = 0; i < SIZE; ++i) {
        vector < int > col;
        for (int j = SIZE - 1; j >= 0; --j)
            if (board[j][i] != 0) col.push_back(board[j][i]);

        // 합치기
        for (int j = 0; j < col.size() - 1; ++j) {
            if (col[j] == col[j + 1]) {
                col[j] *= 2;
                col.erase(col.begin() + j + 1);
                col.push_back(0);
            }
        }

        while (col.size() < SIZE) {
            col.push_back(0);
        }

        // 결과를 board에 반영
        for (int j = SIZE - 1; j >= 0; --j) {
            board[j][i] = col[SIZE - 1 - j];
        }
    }
}

void printBoard(const vector < vector < int > >& board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << '\t';
        }
        cout << endl;
    }
}

bool isgameOver(const vector < vector < int > >& board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 2048) {
                cout << "You got this!" << endl;
                return true;
            }
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) return true;  // 빈 칸이 있으면 계속 진행 가능
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return false;  // 아래와 합칠 수 있으면
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return false;  // 오른쪽과 합칠 수 있으면
        }
    }

    cout << "GAME OVER!" << endl;
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    vector < vector < int > > board(SIZE, vector < int >(SIZE));

    clearBoard(board);
    addRandomTile(board);
    addRandomTile(board);

    while (true) {
        printBoard(board);

        if (isgameOver(board)) break;

        char direct; cin >> direct;

        switch (direct) {
            case 'w':
                moveUp(board);
                break;
            case 'a':
                moveLeft(board);
                break;
            case 's':
                moveDown(board);
                break;
            case 'd':
                moveRight(board);
                break;

            default:
                cout << "Press another key!" << endl;
        }

        addRandomTile(board);  // 이동 후 랜덤 타일 추가
    }

    return 0;
}
