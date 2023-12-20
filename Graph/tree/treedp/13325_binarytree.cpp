#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct data {
	int value;
	int next;

	data(int _value, int _next) : value(_value), next(_next) {}

	data() : value(0), next(0) {}

	data(const data &D) {
		this->value = D.value;
		this->next = D.next;
	}
};

void dfs(int cur, std::vector<std::vector<data>> &edge, std::vector<int> &dp) {

	for(auto i=edge[cur].begin();i<edge[cur].end();++i ) {
		dfs(i->next,edge,dp);
	}

	if(edge[cur].size() == 0) {
		return;
	}

	if(dp[edge[cur][0].next]+edge[cur][0].value>dp[edge[cur][1].next]+edge[cur][1].value) {
		edge[cur][1].value=dp[edge[cur][0].next]+edge[cur][0].value-dp[edge[cur][1].next];
	}

	else {
		edge[cur][0].value=dp[edge[cur][1].next]+edge[cur][1].value-dp[edge[cur][0].next];
	}
	dp[cur]=dp[edge[cur][0].next]+edge[cur][0].value;
	return;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int k;
	std::cin >> k;

	std::vector<int> dp(pow(2,k+1),0); // 1~2^k+1 - 1 번 노드
	// 첫노드 1
	std::vector<std::vector<data>> edge(pow(2,k+1),std::vector<data>()); 
	for(int i=1 ; i<=pow(2,k)-1 ; ++i) {
		int x, y;
		std::cin >> x >> y;
		edge[i].push_back(data(x,i*2));
		edge[i].push_back(data(y,i*2+1));
	}

	dfs(1,edge, dp);
	int sum=0;

	for(int i=1;i<=pow(2,k)-1;++i) {
		sum += edge[i][0].value + edge[i][1].value;
	}

	std::cout << sum << '\n';

	return 0;
}