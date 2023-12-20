#include <iostream>
#include <vector>
#include <queue>
// command D S L R 
// one register ~10000 num. d1d2d3d4 
// D - (num*2)%10000
// S - num-1 / if num=0 => num-1=9999;
// L - d2d3d4d1
// R - d4d1d2d3

// bfs // D,S,L,R 함수 만들기 // visited 이용 

int D(int num){
    return num*2%10000;
}

int S(int num){
    if(num==0) {
        return 9999;
    }
    else {
        return num-1;
    }
}

int L(int num){
    int d1=num/1000;
    return (num-(d1*1000))*10+d1; 
}

int R(int num){
    int d1=num/1000;
	int d2=num/100%10;
	int d3=num/10%10;
	int d4=num%10;

    return d4*1000+d1*100+d2*10+d3;
}

void bfs(int start,int end, bool visited[], std::queue<int> &Q, int before[], char path[]) {
    Q.push({start});
    visited[start]=true;
    while(!Q.empty()) {
        int cur=Q.front();
        Q.pop();

        if(cur==end) {
            std::vector<char> ans;
            while(before[cur]!=-1) {
                ans.push_back(path[cur]);
                cur=before[cur];
            }
            for(int i=ans.size()-1;i>=0;--i) {
                std::cout << ans[i];
            }
            std::cout << '\n';
        }
        int num=D(cur);
        if(!visited[num]) {
            Q.push({num});
            before[num]=cur;
            path[num]='D';
            visited[num]=true;
        }
        num=S(cur);
        if(!visited[num]) {
            Q.push({num});
            before[num]=cur;
            path[num]='S';
            visited[num]=true;
        }
        num=L(cur);
        if(!visited[num]) {
            Q.push({num});
            before[num]=cur;
            path[num]='L';
            visited[num]=true;
        }
        num=R(cur);
        if(!visited[num]) {
            Q.push({num});
            before[num]=cur;
            path[num]='R';
            visited[num]=true;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int T;
    std::cin >> T;
    for(int i=0;i<T;++i) {
        bool visited[10001];
        std::queue<int> Q;
        char path[10001];
        int before[10001];
        for(int i=0;i<=10000;++i) {
            visited[i]=false;
            before[i]=-1;
        }
        int start, end;
        std::cin >> start >> end;

        bfs(start,end,visited,Q,before,path);

    }

    return 0;
}