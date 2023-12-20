#include <iostream>
//n이 주어지면 {1,1},{1,0}의 n-2제곱 행렬을 구하면 된다
int tmp_cnt(-1);
bool cal_seq_arr[10000]={false,};

void matrix(long long int (*mat1)[2],long long int (*mat2)[2]) {
    long long int temp_arr[2][2]={0,};

    for(int i=0;i<2;++i) {
        for(int j=0;j<2;++j) {
            for(int k=0;k<2;++k) {
                temp_arr[i][j]+=(mat1[i][k]*mat2[k][j]);
            }
            temp_arr[i][j]%=1000000007;
        }
    }
    for(int i=0;i<2;++i) {
        for(int j=0;j<2;++j) {
            mat1[i][j]=temp_arr[i][j];
        }
    }
    
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    long long int n;
    std::cin >> n;
    if(n==0) {
        std::cout << 0;
        return 0;
    }
    else if(n==1) {
        std::cout << 1;
        return 0;
    }

    long long int arr[2][2]={1,1,1,0};
    long long int res_arr[2][2]={1,1,1,0};
    n-=2;
    while(n>0) {
        if(n==1) break;
        tmp_cnt++;
        if(n%2==0) {
            cal_seq_arr[tmp_cnt]=false;
            n/=2;
        }
        else {
            cal_seq_arr[tmp_cnt]=true;
            n-=1;
        }   
    }

    for(int i=tmp_cnt;i>=0;--i) {
        if(!cal_seq_arr[i]) {
            matrix(arr,arr);
        }
        else {
            matrix(arr,res_arr);
        }
    }

    std::cout << (arr[0][0]+arr[0][1])%1000000007;
 
    return 0;
}