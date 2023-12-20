#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <stack>

std::vector<int> input_vec;
std::vector<int> size_vec;
std::stack<int> stack;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N;
    std::cin >> N;
    std::vector<int> input_vec(N);
    std::vector<int> ans_vec(N);
    std::stack<int> stack;

    for(int i=0;i<N;++i) {
        std::cin >> input_vec[i];
    }

    for(int i=0;i<N;++i) {
        while(!stack.empty()&&input_vec[stack.top()]<input_vec[i]) {
            ans_vec[stack.top()]=input_vec[i];
            stack.pop();
        }
        stack.push(i);
    }
    for(int i=0;i<N;++i) {
        if(!ans_vec[i]) {
            ans_vec[i]=-1;
        }
    }
    
    for(int i=0;i<N;++i) {
        std::cout << ans_vec[i] << ' ';
    }

    return 0;
}
