#include <iostream>
#include <stack>
#include <string>
// .이 나올때까지 입력받아야 함
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    while(true) {
        std::string str;
        std::getline(std::cin,str,'.');
        std::stack<char> stack;

        if(str=="\n") {
            return 0;
        }
        bool ok=false;
        int len(str.length());
        for(int i=0;i<len;++i) {
            if(str[i]=='(') {
                stack.push('(');
            }
            else if(str[i]=='[') {
                stack.push('[');
            }
            else if(str[i]==')') {
                if(!stack.empty()&&stack.top()=='(') {
                    stack.pop();
                }
                else {
                    ok=true;
                    break;
                }
            }
            else if(str[i]==']') {
                if(!stack.empty()&&stack.top()=='[') { // empty 없으면 true
                    stack.pop();
                }
                else {
                    ok=true;
                    break;
                }
            }
        }
        if(stack.empty()&&!ok)
            std::cout << "yes"<< '\n';
        else
            std::cout << "no" <<'\n';
    }
    return 0;
}
