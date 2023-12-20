#include <iostream>
#include <algorithm>
#include <vector>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> A;

    for(int i=0;i<n;++i) {
        int num;
        std::cin >> num;
        A.push_back(num);
    }
    std::sort(A.begin(),A.end());
    int m;
    std::cin >> m;
    for(int i=0;i<m;++i) {
        int num;
        std::cin >> num;
        int ans=std::upper_bound(A.begin(),A.end(),num) - std::lower_bound(A.begin(),A.end(),num);
        std::cout << ans << ' ';
    }

    return 0;
}

/*
Upper, lower_bound 함수는 배열의 주소를 반환함, ex) 0x00E4FB24
따라서 배열의 첫번째 주소를 빼주면 인덱스를 구할수 있음.
그 주소 내부의 값을 변경(*std::upper_bound()=k) 하면 배열 내부의 값이 바뀜.
https://jackpot53.tistory.com/33
*/