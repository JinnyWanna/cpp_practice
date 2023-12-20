#include <iostream>
//number of cases of queen
int sum=0;
int used_arr[16]; // same row(used_arr), column(i) cannot use ; index


int check_row(int N,int current_col) {
    for(int i=1;i!=current_col&&i<=N;++i) {
        if(used_arr[current_col]==used_arr[i]) // have same number --> false
            return false;
    }
    return true;
}
int check_diag(int cur_row,int cur_col,int N) {
    int check=cur_row+cur_col;
    for(int i=1;i!=cur_col&&i<=N;++i) {
        if((i+used_arr[i])==check+2||i+used_arr[i]==check-2||i+used_arr[i]==check)
            return false;
    }

    return true;
}
void Nqueen(int N,int K) {
    if(K==N) {
        sum++;
        return;
    }
    for(int i=1;i<=N;++i) {
        for(int j=1;j<=N;++j) {
            if(used_arr[i]==-100) { // check column // check row // check diag
                used_arr[i]=j;             
                if(check_diag(used_arr[i],i,N)&&check_row(N,i)) {
                    Nqueen(N,K+1);
                    used_arr[i]=false;
                }
            }
        }
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); std::cout.tie(NULL);

    int N;
    std::cin >> N;
    for(int i=1;i<=N;++i) {
        used_arr[i]=-100;
    }
    Nqueen(N,0);
    std::cout << sum;
    return 0;
}