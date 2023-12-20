#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::vector<int> ans;
    std::vector<int> input;
    int N;
    std::cin >> N;
    
    std::vector<int> index(N+1);

    for(int i=0;i<N;++i) {
        int num;
        std::cin >> num;
        input.push_back(num);
    }
    ans.push_back(input[0]);
    index[0]=0;
    
    for(int i=1;i<N;++i) {
        int idx;
        if(input[i]>ans.back()) {
            ans.push_back(input[i]);
            index[i]=ans.size()-1;
        }
        else {
            idx=std::lower_bound(ans.begin(),ans.end(),input[i])-ans.begin();
            ans[idx]=input[i];
            index[i]=idx;
        }
    }
    std::stack<int> s;

    int find_idx=ans.size()-1;
    for(int i=N-1;i>=0;--i) {
        if(index[i]==find_idx) {
            s.push(input[i]);
            find_idx--;
        }
    }

    std::cout << ans.size() << '\n';
    for(int i=0;i<ans.size();++i) {
        std::cout << s.top() << ' ';
        s.pop();
    }
    return 0;
}