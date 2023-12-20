#include <iostream>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    const int MAX_city=100+1;
    const int INF=100000000;

    int map[MAX_city][MAX_city];
    int city, bus;
    std::cin >> city >> bus;

    for(int i=1;i<=city;++i) {
        for(int j=1;j<=city;++j) {
            if(i==j) {
                map[i][j]=0;
                continue;
            }       
            map[i][j]=INF;
        }
    }

    for(int i=0;i<bus;++i) {
        int x,y,z;
        std::cin >> x >> y >> z;
        if(map[x][y]>z)
            map[x][y]=z;
    }

    for(int k=1;k<=city;++k) {
        for(int i=1;i<=city;++i) {
            for(int j=1;j<=city;++j) {
                map[i][j]=std::min(map[i][j],map[i][k]+map[k][j]);
            }
        }
    }

    for(int i=1;i<=city;++i) {
        for(int j=1;j<=city;++j) {
            if(map[i][j]==INF) {
                std::cout << "0 ";
                continue;
            }
            std::cout << map[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}