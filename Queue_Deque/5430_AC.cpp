#include <iostream>
#include <deque>
#include <queue>
#include <algorithm>
#include <string>

void change(bool &A) {
    if(!A) {
        A=true;
        return;
    }
    else {
        A=false;
        return;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int T;
    std::cin >> T;
    
    for(int i=0;i<T;++i) {
        std::string function;
        std::deque<int> DQ;
        bool front_back=false; // false 면 front // true면 back // R함수 들어갔을때 순서바꾸는 용도

        std::cin >> function;
        int n;
        std::cin >> n;
        std::string input;
        std::cin >> input;
        int firstindex;
        int secondindex;
        int a=0;
        std::string s = "";
        for (int i = 0; i<input.length();i++) {
            if (isdigit(input[i])) {
                s += input[i];
            }
            else {
                if (!s.empty()) {
                    DQ.push_back(stoi(s));
                    s = "";
                }
            }
        }
        int length=function.length();
        for(int i=0;i<length;++i) {
            if(function[i]=='R') {
                change(front_back);   
            }
            else if(function[i]=='D') {
                if(DQ.empty()) {
                    std::cout << "error" << '\n';
                    break;
                }

                else {
                    if(!front_back) { //front_back이 false 면 front부터 제거
                    // 이후 출력도 front부터 해야함 **
                        DQ.pop_front();
                    }
                    else if(front_back) {
                        DQ.pop_back();
                    }
                }
            }
            if(i==length-1) { // length-1(마지막)까지 진행했으면 출력하자
                if(!front_back) {
                    std::cout << '[';
                    int printsize=DQ.size();
                    for(int i=0;i<printsize;++i) {
                        std::cout << DQ.front();
                        DQ.pop_front();
                        if(i!=printsize-1) {
                            std::cout << ',';
                        }
                    }
                    std::cout << ']' << '\n';
                }

                else if(front_back) {
                    std::cout << '[';
                    int printsize=DQ.size();
                    for(int i=0;i<printsize;++i) {
                        std::cout << DQ.back();
                        DQ.pop_back();
                        if(i!=printsize-1) {
                            std::cout << ',';
                        }
                    }
                    std::cout << ']' << '\n';
                }
            }
        }
    }

    return 0;
}
