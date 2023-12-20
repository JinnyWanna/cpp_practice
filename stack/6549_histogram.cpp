#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
// 17298 오큰수랑 같음
int main() {

    while(true) {
        int n;
        std::cin >> n;
        if(n==0) break;

        std::vector<long long int> input_vec(n+2);
        for(int i=1;i<=n;++i) {
            std::cin >> input_vec[i];
        }
        input_vec[n+1]=0;
        std::stack<int> stack;
        stack.push(0);
        long long int ans(0);
        for(int i=1;i<=n+1;++i) {
            while(!stack.empty()&&input_vec[stack.top()]>input_vec[i]) {
                int height(input_vec[stack.top()]);
                stack.pop();
                int width=i-stack.top()-1;
                if(ans<width*height) {
                    ans=width*height;
                }
            }
            stack.push(i);
        }

        std::cout << ans << '\n';

    }

    return 0;
}

///왜틀렸는지 모르겠음