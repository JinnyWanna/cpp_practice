#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

int arr[129][129];
int cnt_blue(0);
int cnt_white(0);
void cutting(int row_start,int row_end,int col_start,int col_end) {
    int cur_color=arr[row_start][col_start]; // 0 or 1
    bool morecut(false);
    for(int i=row_start;i<=row_end;++i) {
        for(int j=col_start;j<=col_end;++j) {
            if(arr[i][j]!=cur_color) {
                morecut=true;
                break;
            }
        }
        if(morecut) break;
    }

    if(morecut) {
        cutting(row_start,(row_start+row_end)/2,col_start,(col_start+col_end)/2);
        cutting((row_start+row_end)/2+1,row_end,(col_start+col_end)/2+1,col_end);
        cutting(row_start,(row_start+row_end)/2,(col_start+col_end)/2+1,col_end);
        cutting((row_start+row_end)/2+1,row_end,col_start,(col_start+col_end)/2);
    }
    else {
        if(cur_color==1) cnt_blue++;
        else cnt_white++;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    for(int i=1;i<=N;++i) {
        for(int j=1;j<=N;++j) {
            std::cin >> arr[i][j];
        }
    }

    cutting(1,N,1,N);

    std::cout << cnt_white << '\n' << cnt_blue;
    return 0;
}
