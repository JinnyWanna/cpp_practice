#include <cmath>
#include <iostream>
#include <vector>

typedef long long lint;

const lint MOD = 1000000007;

lint dfs(int cur, int start, int end, std::vector<lint> &arr,
         std::vector<lint> &segtree) {
    if (start == end) return segtree[cur] = arr[start];
    int mid = (start + end) / 2;

    return segtree[cur] = (dfs(cur<<1, start, mid, arr, segtree)) *
                          (dfs((cur<<1) + 1, mid + 1, end, arr, segtree)) % MOD;
}

lint seg_sum(int cur, int start, int end, int left, int right,
             std::vector<lint> &segtree) {
    if (left > end || right < start) return 1;

    if (left <= start && end <= right) return segtree[cur];

    int mid = (start + end) / 2;
    return (seg_sum(cur<<1, start, mid, left, right, segtree)) *
           (seg_sum((cur<<1) + 1, mid + 1, end, left, right, segtree)) % MOD;
}

lint change_val(int cur, int start, int end, lint value, 
                int idx, std::vector<lint> &segtree) {
    if (idx < start || end < idx) return segtree[cur];
    if(start == end) return segtree[cur] = value;
    int mid = (start + end) / 2;
    
    return segtree[cur] = change_val(cur<<1,start,mid,value,idx,segtree)*change_val((cur<<1)+1,mid+1,end,value,idx,segtree) % MOD;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, M, K;

    std::cin >> N >> M >> K;

    const int height = (int)ceil(log2(N));

    std::vector<lint> segtree(1 << (height + 1), 0);
    std::vector<lint> arr(N + 1, 0);

    for (int i = 0; i < N; ++i) {
        std::cin >> arr[i];
    }  // 0번째 수 ~ N-1 번째 수

    dfs(1, 0, N - 1, arr, segtree);

    for (int i = 0; i < M + K; ++i) {
        lint x, y, z;
        std::cin >> x >> y >> z;
        if (x == 1) {
            arr[y - 1] = z;
            change_val(1, 0, N - 1, z, y - 1, segtree);
        } else if (x == 2) {
            int big = y>z ? y:z;
            int small = y>z ? z:y;
            std::cout << seg_sum(1, 0, N - 1, small - 1, big - 1, segtree) << '\n';
        }
    }

    return 0;
}