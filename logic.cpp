#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 4;

void clearBoard(vector<vector<int>>& board) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = 0;
}

void addRandomTile(vector<vector<int>>& board) {
    vector<pair<int, int>> emptyTile;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == 0) emptyTile.push_back({i, j});

    if (emptyTile.empty()) return;

    int index = rand() % emptyTile.size();
    int value = (rand() % 2 + 1) * 2;
    
    int x = emptyTile[index].first;
    int y = emptyTile[index].second;
    board[x][y] = value;
}

void printBoard(const vector<vector<int>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

void moveLeft(vector<vector<int>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        vector<int> row;
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] != 0) row.push_back(board[i][j]);

        for (int j = 0; j < (int)row.size() - 1; j++) {
            if (row[j] == row[j + 1]) {
                row[j] *= 2;
                row[j + 1] = 0;
            }
        }
        
        vector<int> newRow;
        for (int num : row) if (num != 0) newRow.push_back(num);
        while (newRow.size() < SIZE) newRow.push_back(0);
        
        board[i] = newRow;
    }
}

void moveRight(vector<vector<int>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        vector<int> row;
        for (int j = SIZE - 1; j >= 0; --j)
            if (board[i][j] != 0) row.push_back(board[i][j]);

        for (int j = 0; j < (int)row.size() - 1; j++) {
            if (row[j] == row[j + 1]) {
                row[j] *= 2;
                row[j + 1] = 0;
            }
        }
        
        vector<int> newRow;
        for (int num : row) if (num != 0) newRow.push_back(num);
        while (newRow.size() < SIZE) newRow.push_back(0);
        
        for (int j = 0; j < SIZE; ++j) board[i][SIZE - 1 - j] = newRow[j];
    }
}

void moveUp(vector<vector<int>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        vector<int> col;
        for (int j = 0; j < SIZE; ++j)
            if (board[j][i] != 0) col.push_back(board[j][i]);

        for (int j = 0; j < (int)col.size() - 1; j++) {
            if (col[j] == col[j + 1]) {
                col[j] *= 2;
                col[j + 1] = 0;
            }
        }
        
        vector<int> newCol;
        for (int num : col) if (num != 0) newCol.push_back(num);
        while (newCol.size() < SIZE) newCol.push_back(0);
        
        for (int j = 0; j < SIZE; ++j) board[j][i] = newCol[j];
    }
}

void moveDown(vector<vector<int>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        vector<int> col;
        for (int j = SIZE - 1; j >= 0; --j)
            if (board[j][i] != 0) col.push_back(board[j][i]);

        for (int j = 0; j < (int)col.size() - 1; j++) {
            if (col[j] == col[j + 1]) {
                col[j] *= 2;
                col[j + 1] = 0;
            }
        }
        
        vector<int> newCol;
        for (int num : col) if (num != 0) newCol.push_back(num);
        while (newCol.size() < SIZE) newCol.push_back(0);
        
        for (int j = 0; j < SIZE; ++j) board[SIZE - 1 - j][i] = newCol[j];
    }
}

bool isGameOver(const vector<vector<int>>& board) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == 2048) {
                cout << "You got this!\n";
                return true;
            }

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == 0) return false;

    for (int i = 0; i < SIZE - 1; ++i)
        for (int j = 0; j < SIZE - 1; ++j) {
            if (board[i][j] == board[i + 1][j] || board[i][j] == board[i][j + 1]) return false;
        }

    cout << "GAME OVER!\n";
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    srand(time(0));
    vector<vector<int>> board(SIZE, vector<int>(SIZE));
    clearBoard(board);
    addRandomTile(board);
    addRandomTile(board);

    while (true) {
        printBoard(board);
        if (isGameOver(board)) break;

        char direct;
        cin >> direct;
        
        switch (direct) {
            case 'w': moveUp(board); break;
            case 'a': moveLeft(board); break;
            case 's': moveDown(board); break;
            case 'd': moveRight(board); break;
            default: cout << "Press another key!" << endl; continue;
        }

        addRandomTile(board);
    }
    return 0;
}
