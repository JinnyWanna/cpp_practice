#include <iostream>
#include <algorithm>
#include <vector>
std::vector<int> A;
bool binary_search(int num,int start,int end) { // num 찾을 수 A 찾을 공간
    while(start<=end) {
        int mid=(start+end)/2;
        if(num==A[mid]) {
            return true;
        }
        else {
            if(A[mid]>num) {
                end=mid-1;
            }
            else {
                start=mid+1;
            }
        }
    }
    return false;
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    for(int i=1;i<=n;++i) {
        int num;
        std::cin >> num;
        A.push_back(num);
    }

    std::sort(A.begin(),A.end());
    
    int m;
    std::cin >> m;
    for(int i=1;i<=m;++i) {
        int num;
        std::cin >> num;
        if(binary_search(num,0,n-1)) {
            std::cout << '1' << '\n';
        }
        else {
            std::cout << '0' << '\n';
        }
    
    }


    return 0;
}