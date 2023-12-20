#include <iostream>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    const int MAX_city = 400 + 1;
    const int INF=100000000;
    int map[MAX_city][MAX_city] = {0,};
    int city, road;
    std::cin >> city >> road;
    for(int i=1;i<=city;++i) {
        for(int j=1;j<=city;++j) {
            if(i==j) continue;
            map[i][j]=INF;
        }
    }

    for(int i=0;i<road;++i) {
        int x,y,z;
        std::cin >> x >> y >> z;
        map[x][y]=z;
    }

    for(int k=1;k<=city;++k) {
        for(int i=1;i<=city;++i) {
            for(int j=1;j<=city;++j) {
                map[i][j]=std::min(map[i][j],map[i][k]+map[k][j]);
            }
        }
    }

    int ans=100000000;
    for(int i=1;i<=city;++i) {
        for(int j=i+1;j<=city;++j) {
            ans=std::min(ans,map[i][j]+map[j][i]);
        }
    }
    if(ans>=INF) {
        std::cout << "-1";
        return 0;
    }
    std::cout << ans;

    return 0;
}