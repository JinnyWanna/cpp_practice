#include <bits/stdc++.h>

typedef long long lint;

struct point {
    lint x;
    lint y;
};

bool cmp_y(const point &p1, const point &p2) {
    if(p1.y == p2.y) return p1.x < p2.x;

    return p1.y > p2.y;
}

// 큰 순서로 정렬
bool cmp(const point &p1, const point &p2) {
    if(p1.x == p2.x) return p1.y < p2.y;

    return p1.x < p2.x;
}
// st 0 ed n-1 node 1
lint cnt(std::vector<lint> &tree, int left, int right, int start, int end, int node) {
    if(right < start || end < left) return 0;

    if(left <= start && end <= right) return tree[node];

    int mid = (start+end) >> 1;

    return cnt(tree,left,right,start,mid,(node<<1)) + cnt(tree,left,right,mid+1,end,(node<<1)|1);
}

void update(std::vector<lint> &tree, int idx, int start, int end, int node) {
    if(idx < start || end < idx) return;
    
    tree[node]++;

    if(start == end) return;

    int mid = (start+end) >> 1; 
    update(tree,idx,start,mid,(node<<1));
    update(tree,idx,mid+1,end,(node<<1)|1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;

    while(tc--) {
        int n;
        std::cin >> n;

        const int height = (int)ceil(log2(n));

        std::vector<point> arr;
        std::vector<lint> tree(1<<(height+1), 0);

        for(int i=0; i<n; ++i) { // 0~n-1
            int x, y;
            std::cin >> x >> y;

            arr.push_back({x,y});
        }

        std::sort(arr.begin(), arr.end(), cmp_y);

        for(int i=0; i<arr.size(); ++i) {
            arr[i].y = i;
        } // idx setting

        std::sort(arr.begin(), arr.end(), cmp);
        lint ans(0);
        // 0~idx-1에 있는 수 cnt해서 더해주고, 맨 앞부터 배치하면서 sum_update 해주기 
        for(int i=0; i<arr.size(); ++i) {
            int idx = arr[i].y;

            ans += cnt(tree,0,idx-1,0,n-1,1);
            update(tree,idx,0,n-1,1);
        }

        std::cout << ans << '\n';
    }

    return 0;
}

/*
1
7
1 4
2 1
3 2
4 2
4 5
6 3
7 1
*/