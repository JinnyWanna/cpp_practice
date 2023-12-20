#include <iostream>
#include <queue>

struct cmp {
    bool operator()(int a,int b) { // 작은수부터 꺼낸다
        return a>b;
    }
};

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);


    int N;
    std::cin >> N;

    std::priority_queue<int,std::vector<int>> pQ;
    std::priority_queue<int,std::vector<int>,cmp> pQ2;

    for(int i=1;i<=N;++i) { 
        if(i%2!=0) {
            int num;
            std::cin >> num;
            pQ.push(num);
            if(!pQ2.empty()&&pQ.top()>pQ2.top()) {
                int temp=pQ.top();
                pQ.pop();
                pQ.push(pQ2.top());
                pQ2.pop();
                pQ2.push(temp);
            }
            std::cout  << pQ.top() << '\n';
        }

        else {
            int num;
            std::cin >> num;
            pQ2.push(num);
            if(pQ.top()>pQ2.top()) {
                int temp=pQ.top();
                pQ.pop();
                pQ.push(pQ2.top());
                pQ2.pop();
                pQ2.push(temp);
            }
            std::cout << pQ.top() << '\n';
        }
    }

    return 0;
}

// maxheap, minheap을 떠올린 이유.
/*
pq에서 가운데를 우선순위 높혀서 출력하기는 어려움.
따라서 가운데를 출력할 방법이 필요한데, sort를 할 경우 시간초과나므로
무조건 pq를 이용해야 함.
가운데를 출력하기 위해선 큰수들과 작은수들을 반반씩 나눠서 저장하고,
작은수중에 가장 큰 수를 출력하면 그게 가운데수가 됨을 알 수 있다.
반반씩 나누기 위해 번갈아가면서 저장하는데, 큰수와 작은수를 완전히 분리하기 위해
큰 수중 가장 작은수와 작은수중 가장 큰수를 비교하여 정렬하는 작업이 필요하다.
*/