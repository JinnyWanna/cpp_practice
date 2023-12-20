#include <algorithm>
#include <iostream>
#include <vector>
#define fastio                        \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);

struct check {
    bool row[9][10] = {false, }; // [a][b] a행에 1~9숫자 존재
    bool col[9][10] = {false, };
    bool box[3][3][10] = {false, }; // [row][col][num] row행 col열번째 박스에 num이 존재

    void check_true(int x, int y, int num);

    void check_false(int x, int y, int num);
};

check input(std::vector<std::vector<int>>&);

int next_col(int row, int col);
int next_row(int row, int col);

void sudoku(const int row, const int col, check &checks, std::vector<std::vector<int>> &map) {
    
    if(row == 8 && col == 8) {
        for(int i=1;i<=9;++i) {
            if(!checks.row[row][i] && !checks.col[col][i] && !checks.box[row/3][col/3][i]) {
                map[8][8] = i;
            }
        }
    
        for(int i=0;i<9;++i) {
            for(int j=0;j<9;++j) {
                std::cout << map[i][j] << ' ';
            }
            std::cout << '\n';
        }
        exit(0);
    }
    if(map[row][col] != 0) {
        sudoku(next_row(row,col),next_col(row,col),checks,map);
        return;
    }
    else {
        for(int i=1;i<=9;++i) {
            if(!checks.row[row][i] && !checks.col[col][i] && !checks.box[row/3][col/3][i]) {
                checks.check_true(row,col,i);
                map[row][col] = i;

                sudoku(next_row(row,col),next_col(row,col),checks,map);

                checks.check_false(row,col,i);
                map[row][col] = 0;
            }
        }
    }
}

int main() {
    fastio;    
    
    std::vector<std::vector<int>> map(9,std::vector<int>(9,0));
    // 0~8까지 row, col 존재
    check checks = input(map);
    
    sudoku(0,0,checks,map);

    return 0; 
}

void check::check_true(int x, int y, int num) {
    row[x][num] = true;
    col[y][num] = true;
    box[x/3][y/3][num] = true;
}

void check::check_false(int x, int y, int num) {
    row[x][num] = false;
    col[y][num] = false;
    box[x/3][y/3][num] = false;
}

check input(std::vector<std::vector<int>> &map) {

    check ret;

    for(int i=0;i<9;++i) {
        for(int j=0;j<9;++j) {
            std::cin >> map[i][j];
            ret.check_true(i,j,map[i][j]);
        }
    }

    return ret;
}

int next_row(int row, int col) {
    if(col<8) {
        return row;
    }
    else {
        row += 1; 
        return row;
    }
    return 0;
}

int next_col(int row, int col) {
    if(col<8) {
        col += 1;
        return col;
    }
    else {
        col = 0;
        return col;
    }
    return 0;
}