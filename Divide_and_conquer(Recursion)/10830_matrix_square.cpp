#include <iostream>

int N;
int tmp_cnt(-1);
bool cal_seq_arr[1000000]; 
int input_matrix[5][5];
int temp_arr[5][5]; //답arr
int cal_arr[5][5]; // 다음 연산에 사용할arr

void matrix(int mat1[5][5],int mat2[5][5]) {

    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            temp_arr[i][j]=0;
        }
    }
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            for(int k=0;k<N;++k) {
                temp_arr[i][j]+=mat1[i][k]*mat2[k][j];
            }
            temp_arr[i][j]=temp_arr[i][j]%1000;
        }
    }
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            cal_arr[i][j]=temp_arr[i][j];
        }
    }
    return;
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    long long int M;
    std::cin >> N >> M;

    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            std::cin >> input_matrix[i][j];
            cal_arr[i][j]=input_matrix[i][j];
        }
    }

    if(M==1) {
        for(int i=0;i<N;++i) {
            for(int j=0;j<N;++j) {
                std::cout << input_matrix[i][j]%1000 << ' ';
            }
            std::cout << '\n';
        }   
        return 0;
    }

    while(true) {
        if(M==1) break;
        tmp_cnt++;
        if(M%2==0) {
            cal_seq_arr[tmp_cnt]=false;
            M/=2;
        }
        else {
            cal_seq_arr[tmp_cnt]=true;
            M-=1;
        }   
    }

    for(int i=tmp_cnt;i>=0;--i) {
        if(!cal_seq_arr[i]) {
            matrix(cal_arr,cal_arr);
        }
        else {
            matrix(cal_arr,input_matrix);
        }
    }

    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            std::cout << temp_arr[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}