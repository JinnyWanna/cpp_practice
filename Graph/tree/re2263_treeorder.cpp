#include <iostream>
#include <vector>
#include <algorithm>
// 인덱스만 넣어서 풀어보자

void find_pre(int instart, int inend, int poststart, int postend, const std::vector<int> &inorder, const std::vector<int> &postorder) {
    //inleft는 0~idx-1 // inright는 idx+1~현 벡터 사이즈-1
    // post_left 0~idx-1 // postright idx~현 벡터 사이즈-2
	if(instart>inend) return;
    if(poststart>postend) return;

    int root=postorder[postend];
    std::cout << root << ' ';
	int idx=std::find(inorder.begin(),inorder.end(),root)-inorder.begin();
    int leftsize=idx-instart;

    find_pre(instart,idx-1,poststart,poststart+leftsize-1,inorder,postorder);
    find_pre(idx+1,inend,poststart+leftsize,postend-1,inorder,postorder);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int n;
	std::cin >> n;

	std::vector<int> inorder; // 중위순회 L ROOT R
	std::vector<int> postorder; // 후위순회 L R ROOT
	// 전위순회 ROOT L R

	for(int i=1;i<=n;++i) {
		int x;
		std::cin >> x;
		inorder.push_back(x);
	}
	for(int i=1;i<=n;++i) {
		int x;
		std::cin >> x;
		postorder.push_back(x);
	}

	find_pre(0,n-1,0,n-1,inorder,postorder);

	return 0;
}