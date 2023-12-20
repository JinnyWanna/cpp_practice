#include <cmath>
#include <iostream>
#include <vector>
// N switch 0~N-1
// 1. inverting switch A-1 ~ B-1 
// 2. find open_switch from C-1 ~ D-1
// Lazy propagation

typedef long long lint;

void lazy_update(int node, int start, int end, std::vector<int> &tree, std::vector<int> &lazy) {
    if(lazy[node] != 0) {
        if(lazy[node]%2 == 1) { // odd
            tree[node] = (end-start+1) - tree[node];

            if(start != end) {
                lazy[2*node] += lazy[node];            
                lazy[2*node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }

        else {
            if(start != end) {
                lazy[2*node] += lazy[node];
                lazy[2*node + 1] += lazy[node];
            }

            lazy[node] = 0;
        }
    }
}

void invert_update(int node, int start, int end, int left, int right, std::vector<int> &tree, std::vector<int> &lazy) {

    lazy_update(node,start,end,tree,lazy);

    if(right < start || end < left) return;

    if(left <= start && end <= right) {
        tree[node] = (end - start + 1) - tree[node];

        if(start != end) {
            lazy[2*node] += 1;
            lazy[2*node + 1] += 1;
        }

        return;
    }
    int mid = (start+end)/2;
    invert_update(2*node, start, mid, left, right, tree, lazy);
    invert_update(2*node+1, mid+1, end, left, right, tree, lazy);

    tree[node] = tree[2*node] + tree[2*node + 1];
}       

int find_open(int node, int start, int end, int left, int right, std::vector<int> &tree, std::vector<int> &lazy) {

    lazy_update(node,start,end,tree,lazy);

    if(right < start || end < left) return 0;

    if(left <= start && end <= right) return tree[node];

    int mid = (start+end)/2;
    return find_open(2*node, start, mid, left, right, tree, lazy) + find_open(2*node + 1, mid+1, end, left, right, tree, lazy);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    const int height = (int)ceil(log2(N)) + 1;

    std::vector<bool> arr(N+1, false); //
    std::vector<int> tree(1<<height, 0);
    std::vector<int> lazy(1<<height, 0);

    for(int i=0; i<M; ++i) {
        int O;
        std::cin >> O;

        if(O==0) {
            int S, T;
            std::cin >> S >> T;

            invert_update(1,0,N-1,S-1,T-1,tree,lazy);
        }

        else {
            int S, T;
            std::cin >> S >> T;

            std::cout << find_open(1,0,N-1,S-1,T-1,tree,lazy) << '\n';
        }
    }


    return 0;
}
