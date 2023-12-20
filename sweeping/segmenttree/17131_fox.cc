#include <bits/stdc++.h>

typedef long long lint;

struct Point {
    int x;
    int y;
    int id;
};

bool CmpIndex(const Point &p1, const Point &p2) {
    if(p1.y == p2.y) return p1.x < p2.x; 

    return p1.y < p2.y;
}

bool Cmp_sweepleft(const Point &p1, const Point &p2) {
    if(p1.x == p2.x) return p1.y < p2.y;

    return p1.x < p2.x;
}

bool Cmp_sweepright(const Point &p1, const Point &p2) {
    if(p1.x == p2.x) return p1.y < p2.y;

    return p1.x > p2.x;
}

// node 1 st 0 end n-1
lint cnt(std::vector<lint> &tree, int left, int right, int node, int start, int end) {

    if(end < left || right < start) return 0;

    if(left <= start && end <= right) return tree[node];

    int mid = (start+end) >> 1;
    return cnt(tree, left, right, (node<<1), start, mid) + cnt(tree, left , right, (node<<1)|1, mid+1, end);
}

void update(std::vector<lint> &tree, int idx, int node, int start, int end) {
    if(idx < start || end < idx) return;

    tree[node]++;

    if(start==end) return;

    int mid = (start+end) >> 1;
    update(tree, idx, (node<<1), start, mid);
    update(tree, idx, (node<<1)|1, mid+1, end);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    const int height = (int)ceil(log2(N));

    std::vector<Point> arr;
    std::vector<lint> tree(1<<(height+1), 0);

    for(int i=0;i<N;++i) {
        int x, y;
        std::cin >> x >> y;

        arr.push_back({x, y, i});

    }


    std::sort(arr.begin(),arr.end(),CmpIndex);

// start idx setting
    std::vector<bool> idx_same(N+1,false);
    for(int i=1;i<N;++i) {
        if(arr[i].y == arr[i-1].y) idx_same[i] = true;
    }

    for(int i=0;i<N;++i) {
        if(idx_same[i] == true) {
            arr[i].y = arr[i-1].y;
            continue;
        }
        arr[i].y = i;
    }
// end idx setting

    std::vector<lint> left_cnt(N+1, 0);

    std::sort(arr.begin(), arr.end(), Cmp_sweepleft);

    for(int i=0; i<N; ++i) {    
        int idx = arr[i].y;
        left_cnt[arr[i].id] = cnt(tree, idx+1, N-1, 1, 0, N-1); 
        update(tree, idx, 1, 0, N-1);
    }

    std::sort(arr.begin(), arr.end(), Cmp_sweepright);
    tree = std::vector<lint>(1<<(height+1), 0);
    lint ans(0);

    for(int i=0; i<N; ++i) {
        int idx = arr[i].y;

        ans += (cnt(tree, idx+1, N-1, 1, 0, N-1) * left_cnt[arr[i].id]) % (lint)(pow(10,9)+7);
        ans %= (lint)(pow(10,9)+7);

        update(tree, idx, 1, 0, N-1);
    }

    std::cout << ans << '\n';
    return 0;
}