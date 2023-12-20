#include <iostream>
#include <vector>

int get_parent(std::vector<int> &parent, int x) {
	if(parent[x]==x) return x;
	else {
		return parent[x]=get_parent(parent,parent[x]);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int n,m;
	std::cin >> n >> m;
	std::vector<int> point_parent(n);
	for(int i=0;i<n;++i) {
		point_parent[i]=i;
	}
	// 하나씩 입력받으면서 u-f돌림 다음 입력을 받았을때 
	//parent가 같은 두 노드를 입력받은 경우 횟수출력, return

	for(int i=1;i<=m;++i) {
		int x,y;
		std::cin >> x >> y;
		x=get_parent(point_parent,x);
		y=get_parent(point_parent,y);
		if(x==y) {
			std::cout << i << '\n';
			return 0;
		}
		if(x>y) point_parent[x]=y;
		else point_parent[y]=x;
	}

	std::cout << '0' <<'\n';

	return 0;
}