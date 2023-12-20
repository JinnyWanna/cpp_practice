#include <iostream>
#include <stack>
#include <vector>
#include <string>
// 1~n 까지 수에 push, pop 를 몇번 수행해야 
int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> input_vec;
    std::stack<int> stack;
    input_vec.push_back(0);
    std::string ans;
    for(int i=0;i<n;++i) {
        int num;
        std::cin >> num;
        input_vec.push_back(num);
    }
    int cur_stack(1);
    for(int i=1;i<=n;++i){
        while(true) {
            if(stack.empty()) {
                stack.push(cur_stack);
                ans+="+\n";                
                cur_stack++;
            }

            if(input_vec[i]>stack.top()) {
                stack.push(cur_stack);
                ans+="+\n";
                cur_stack++;
            }
            else if(input_vec[i]==stack.top()) {
                stack.pop();
                ans+="-\n";
                break;
            }
            else {
                std::cout << "NO";
                return 0;
            }
        }
    }

    std::cout << ans;
    return 0;
}