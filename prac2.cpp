#include <bits/stdc++.h>

typedef long long lint;

struct point {
    lint x, y;
    lint w;
};

struct treenode {
    lint sum, lmax, rmax, totalmax;
};

bool cmp(const point &p1, const point &p2) {
    if(p1.y == p2.y) return p1.x < p2.x;

    return p1.y < p2.y;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<point> arr;
    std::vector<int> compact_x;
    std::vector<int> compact_y;

    for(int i=0; i<N; ++i) {
        lint x, y, w;
        std::cin >> x >> y >> w;
    
        arr.push_back({x,y,w});
        compact_x.push_back(x);
        compact_y.push_back(y);
    }

    // 1 ~ N(중복 없을경우) 으로 좌표압축

    std::sort(compact_x.begin(),compact_x.end());
    std::sort(compact_y.begin(),compact_y.end());

    compact_x.erase(std::unique(compact_x.begin(),compact_x.end()),compact_x.end());
    compact_y.erase(std::unique(compact_y.begin(),compact_y.end()),compact_y.end());
        
    for(int i=0;i<N;++i) {
        arr[i].x = std::upper_bound(compact_x.begin(),compact_x.end(),arr[i].x) - compact_x.begin();
        arr[i].y = std::upper_bound(compact_y.begin(),compact_y.end(),arr[i].y) - compact_y.begin();
    }

    std::sort(arr.begin(),arr.end(),cmp);

    for(int i=0; i<compact_y.size(); ++i) { // y 두개를 고르자


        for(int j=i; j<compact_y.size(); ++j) {

        }
    }
    
    return 0;
}