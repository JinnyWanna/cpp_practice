#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    
    std::vector<int> seq(n);
    for(int i=0;i<n;++i) {
        std::cin >> seq[i];
    }
    int find;
    std::cin >> find;

    std::sort(seq.begin(),seq.end());
    
    int start = 0;
    int end = n-1;
    int count = 0;

    while(start<end) {
        if(seq[start]+seq[end]==find) {
            start++;
            end--;
            count++;
        }
        else if(seq[start]+seq[end]>find) {
            end--;
        }
        else {
            start++;
        }
    }
    std::cout << count;
    return 0;
}