#include <bits/stdc++.h>
// find idx 1~N

struct treeinfo {
	int min_val;
	int idx;

	treeinfo() : min_val(0), idx(-1) {}

	treeinfo(int _min_val, int _idx) : min_val(_min_val), idx(_idx) {}

	treeinfo(const treeinfo &t) {
		min_val = t.min_val;
		idx = t.idx;
	}
};

void set_tree(int node, int start, int end, std::vector<treeinfo> &tree, std::vector<int> &arr) {
	if(start == end) {
		tree[node].min_val = arr[start];
		tree[node].idx = start;

		return;
	}

	int mid = (start + end) / 2;

	set_tree(node * 2, start, mid, tree, arr);
	set_tree((node * 2) + 1, mid+1, end, tree, arr);

	if(tree[node * 2].min_val < tree[(node * 2) + 1].min_val) {
		tree[node].min_val = tree[node * 2].min_val;
		tree[node].idx = tree[node * 2].idx;
	}

	else if(tree[node * 2].min_val == tree[(node * 2) + 1].min_val) {
		tree[node].min_val = tree[node * 2].min_val;
		tree[node].idx = std::min(tree[node * 2].idx, tree[(node * 2) + 1].idx);
	}

	else {
		tree[node].min_val = tree[(node * 2) + 1].min_val;
		tree[node].idx = tree[(node * 2) + 1].idx;	
	}
}

void update_query(int node, int start, int end, int change_idx, int change_num, std::vector<treeinfo> &tree) {
	if(change_idx < start || end < change_idx) return;

	if(start == end) {
		tree[node].min_val = change_num;
		return;
	}

	int mid =(start+end) / 2;

	update_query(2* node, start, mid, change_idx, change_num, tree);
	update_query((2*node)+1, mid+1, end, change_idx, change_num, tree);

	if(tree[node * 2].min_val < tree[(node * 2) + 1].min_val) {
		tree[node].min_val = tree[node * 2].min_val;
		tree[node].idx = tree[node * 2].idx;
	}

	else if(tree[node * 2].min_val == tree[(node * 2) + 1].min_val) {
		tree[node].min_val = tree[node * 2].min_val;
		tree[node].idx = std::min(tree[node * 2].idx, tree[(node * 2) + 1].idx);
	}

	else {
		tree[node].min_val = tree[(node * 2) + 1].min_val;
		tree[node].idx = tree[(node * 2) + 1].idx;	
	}
}

treeinfo find_min(int node, int start, int end, int left, int right, std::vector<treeinfo> &tree) {
	if(end < left || right < start) return treeinfo(INT_MAX, -1);

	if(left <= start && end <= right) {
		return tree[node];
	}

	int mid = (start + end) / 2;

	treeinfo A = find_min(2*node, start, mid, left, right, tree);			
	treeinfo B = find_min((2*node)+1, mid+1, end, left, right, tree);

	if(A.min_val < B.min_val) return A;

	else if(A.min_val > B.min_val) return B;

	else {
		if(A.idx < B.idx) return A;
		else return B;
	}

}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    const int height = (int)ceil(log2(N)) + 1;

    std::vector<int> arr(N + 1, 0);
    std::vector<treeinfo> tree(1 << height, treeinfo());

	for(int i=1; i<=N; ++i) {
		std::cin >> arr[i];
	}

	set_tree(1, 1, N, tree, arr);

	int M;
	std::cin >> M;

	for(int i=0; i<M; ++i) {
		int que, x, y;
		std::cin >> que >> x >> y;

		if(que == 1) { // idx x을 y로 바꿔
			update_query(1,1,N,x,y,tree);
		}

		else {
			std::cout << find_min(1,1,N,x,y,tree).idx << '\n';
		}
	}

    return 0;
}