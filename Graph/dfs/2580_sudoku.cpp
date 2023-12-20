#include <iostream>
/* 가로축 전부 비교, 세로축 전부 비교, 존재하는 3x3배열 비교하여 들어가야 하는 숫자 찾기.
*/
int arr[9][9]; //배열이 0인경우 들어가서 체크 // col row
int temp_arr[3][3];
bool temp_col_num[11];
bool temp_row_num[11];
bool temp_arr_num[11]; // 1 2 3 4 5 6 7 8 9 이용
void copy(int, int);
    
void sudoku(int col, int row) {
    for(int i=0;i<9;++i) { // col 숫자 저장
        if(arr[col][i]) temp_col_num[arr[col][i]]=true;
    }
    for(int i=0;i<9;++i) { // row 숫자 저장
        if(arr[i][row]) temp_row_num[arr[i][row]]=true;
    }

    for(int i=0;i<3;++i) {
        for(int j=0;j<3;++j) {
            if(temp_arr[i][j]) temp_arr_num[temp_arr[i][j]]=true;
        }
    }

    for(int i=1;i<10;++i) {
        if(!temp_arr_num[i]&&!temp_col_num[i]&&!temp_row_num[i]) {
            arr[col][row]=i;
            return;
        }
    }
    return;
}

bool stop() {
    for(int a=0;a<9;++a) {
        for(int b=0;b<9;++b) {
            if(!arr[a][b]) return false; 
        }
    }
    return true;
}
int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); std::cout.tie(NULL);

    for(int i=0;i<9;++i) {
        for(int j=0;j<9;++j) {
            std::cin >> arr[i][j];
        }
    }
    bool for_break=false;
    while(1) {
        for(int i=0;i<9;++i) {
            for(int j=0;j<9;++j) {
                if(!arr[i][j]) {
                    copy(i,j);
                    sudoku(i,j); // 2 2    
                }
            }
        }
        if(stop()) break;
    }

    for(int i=0;i<9;++i) {
        for(int j=0;j<9;++j) {
            std::cout << arr[i][j] << ' ';
        }
        std::cout <<'\n';
    }



    return 0;
}

void copy(int col, int row) {
    if(col>=0&&col<3) {
        if(row>=0&&row<3) {
            for(int i=0;i<3;++i) {
                for(int j=0;j<3;++j) {
                    temp_arr[i][j]=arr[i][j];
                }
            }
        }
        else if(row>=3&&row<6) {
            for(int i=0;i<3;++i) {
                for(int j=3;j<6;++j) {
                    temp_arr[i][j]=arr[i][j];
                }
            }
        }            
        else if(row>=6&&row<9) {
            for(int i=0;i<3;++i) {
                for(int j=6;j<9;++j) {
                    temp_arr[i][j]=arr[i][j];
                }
            }
        }            
    }
    else if(col>=3&&col<6) {
        if(row>=0&&row<3) {
            for(int i=3;i<6;++i) {
                for(int j=0;j<3;++j) {
                    temp_arr[i][j]=arr[i][j];
                }
            }
        }
        else if(row>=3&&row<6) {
            for(int i=3;i<6;++i) {
                for(int j=3;j<6;++j) {
                    temp_arr[i][j]=arr[i][j];
                }
            }
        }            
        else if(row>=6&&row<9) {
            for(int i=3;i<6;++i) {
                for(int j=6;j<9;++j) {
                    temp_arr[i][j]=arr[i][j];
                }
            }
        }                    
    }
    else if(col>=6&&col<9) {
        if(row>=0&&row<3) {
            for(int i=6;i<9;++i) {
                for(int j=0;j<3;++j) {
                    temp_arr[i][j]=arr[i][j];
                }
            }
        }
        else if(row>=3&&row<6) {
            for(int i=6;i<9;++i) {
                for(int j=3;j<6;++j) {
                    temp_arr[i][j]=arr[i][j];
                }
            }
        }            
        else if(row>=6&&row<9) {
            for(int i=6;i<9;++i) {
                for(int j=6;j<9;++j) {
                    temp_arr[i][j]=arr[i][j];
                }
            }
        }                    
    }
}