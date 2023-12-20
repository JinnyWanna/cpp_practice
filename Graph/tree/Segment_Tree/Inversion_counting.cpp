// https://loosie.tistory.com/328

#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

typedef long long lint;

struct pair {
    int value;
    int index;

    pair() : value(0), index(0) {}

    pair(int _value, int _index) : value(_value), index(_index) {}

    pair(const pair &p) {
        this->value = p.value;
        this->index = p.index;
    }
};

bool cmp(const pair &A, const pair &B) { 
    if(A.value == B.value) return A.index < B.index;
    // 왜 value가 같을때 index 작은게 먼저 정렬돼야 할까? // A.index > B.index면 틀림
    // 4
    // 2 3 2 1
    // 답 4
    return A.value < B.value;
}

// idx+1 ~ N-1 입력받을 예정
lint cnt(int node, int start, int end, int left, int right,
         std::vector<int> &tree) {
    if (right < start || end < left) return 0;

    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return cnt(2 * node, start, mid, left, right, tree) +
           cnt(2 * node + 1, mid + 1, end, left, right, tree);
}

void update(int node, int start, int end, int idx,
            std::vector<int> &tree) {
    if (idx < start || end < idx) return;

    tree[node] += 1;

    if (start == end) return;

    int mid = (start + end) / 2;
    update(node * 2, start, mid, idx, tree);
    update(node * 2 + 1, mid + 1, end, idx, tree);

}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    const int height = (int)ceil(log2(N)) + 1;

    std::vector<pair> arr;
    std::vector<int> tree(1 << height, 0);

    for (int i = 0; i < N; ++i) {
        int x;
        std::cin >> x;
        arr.push_back(pair(x, i));
    }

    std::sort(arr.begin(), arr.end(), cmp);

    lint sum = 0;
    for (int i = 0; i < N; ++i) {
        int idx = arr[i].index;
        sum += (lint)cnt(1, 0, N - 1, idx + 1, N - 1, tree);
        update(1, 0, N - 1, idx, tree);
    }

    std::cout << sum << '\n';

    return 0;
}