#include <iostream>
#include <algorithm>
#include <vector>

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    int ans_arr[501][501];
    int temp_arr[501];
    int size;
    std::cin >> size;
    
    for(int i=1;i<=size;++i) { // i는 행, 2행부터 size행까지 진행
        for(int j=1;j<=i;++j) { // j개 print -- 열
            std::cin >> temp_arr[j];
        }

        for(int j=1;j<=i;++j) {
            if(j==1) {
                ans_arr[i][j]=ans_arr[i-1][j]+temp_arr[j];
            }
            else if(j==i) {
                ans_arr[i][j]=ans_arr[i-1][j-1]+temp_arr[j];
            }

            else {
                ans_arr[i][j]=std::max(ans_arr[i-1][j-1],ans_arr[i-1][j])+temp_arr[j];
            }
        }
    }

    std::vector<int> vec(size+1);

    for(int i=1;i<=size;++i) {
        vec[i]=ans_arr[size][i];
    }

    std::sort(vec.begin(),vec.end());

    std::cout << vec[size];

    return 0;
}