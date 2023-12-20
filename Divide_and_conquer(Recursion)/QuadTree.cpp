#include <iostream>
#include <string>

char arr[65][65]; // 1~64
std::string ans("");
void QuadTree(int row_start,int col_start,int size) {
    bool cut=false;
    int first_color=arr[row_start][col_start]; // 0 or 1
    for(int i=row_start;i<row_start+size;++i) {
        for(int j=col_start;j<col_start+size;++j) {
            if(arr[i][j]!=first_color) {
                cut=true;
                break;
            }
        }
        if(cut) break;
    }
    if(cut) {
        ans+="(";
        QuadTree(row_start,col_start,size/2);
        QuadTree(row_start,col_start+size/2,size/2);
        QuadTree(row_start+size/2,col_start,size/2);
        QuadTree(row_start+size/2,col_start+size/2,size/2);
        ans+=")"; 
    }
    else {
        if(first_color=='1') ans+="1";
        else ans+="0";
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
    if(N==1) {
        std::cout << arr[1][1];
        return 0;
    }
    QuadTree(1,1,N);
    std::cout << ans;
    return 0;
}