#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct point {
	int x;
	int y;
};

int dist(point A,point B) {
	return abs(A.x-B.x)+abs(A.y-B.y);
}
// dp를 앞부분 [0][0]부터 쌓아올려 [n][n]에 완성시켜야 한다는 고정관념이 있었음
// 깊이 탐색으로 앞부분 완성을 위해 뒷값을 끌어오는 발상*******
int dist_from_input_to_W(const std::vector<point> &input, const int N, const int W, int (*dp)[1001], int cur_police1, int cur_police2) {
	if(cur_police1==W||cur_police2==W) return 0; //종료지점~종료지점 0
	if(dp[cur_police1][cur_police2]!=-1) return dp[cur_police1][cur_police2]; // 탐색 깊이 제한 
	// 2^N회 반복을 막고 N*N회 반복으로 함수 종료하게 만들어줌

	int next=std::max(cur_police1,cur_police2)+1; // 다음 사건
	
	// 현재위치~다음위치 까지의 거리
	int dist1,dist2;

	// 0은 첫 위치, input벡터에 안들어있음, 예외처리
	if(cur_police1==0) dist1=dist({1,1},input[next]);
	else dist1=dist(input[cur_police1],input[next]);

	if(cur_police2==0) dist2=dist({N,N},input[next]);
	else dist2=dist(input[cur_police2],input[next]);

	dp[cur_police1][cur_police2]=std::min(dist_from_input_to_W(input,N,W,dp,next,cur_police2)+dist1,dist_from_input_to_W(input,N,W,dp,cur_police1,next)+dist2);
	
	return dp[cur_police1][cur_police2];
}

void minpath(std::vector<char> &ans, int cur_police1,int cur_police2, const int N, const int dp[][1001], const int W, const std::vector<point> &input) {
	if(cur_police1==W||cur_police2==W) return;

	int next=std::max(cur_police1,cur_police2)+1; 
	
	// 현재위치~다음위치 까지의 거리
	int dist1,dist2;


	if(cur_police1==0) dist1=dist({1,1},input[next]);
	else dist1=dist(input[cur_police1],input[next]);

	if(cur_police2==0) dist2=dist({N,N},input[next]);
	else dist2=dist(input[cur_police2],input[next]);
	
	if(dp[next][cur_police2]+dist1>dp[cur_police1][next]+dist2) {
		ans.push_back('2');
		minpath(ans,cur_police1,next,N,dp,W,input);
	}
	else {
		ans.push_back('1');
		minpath(ans,next,cur_police2,N,dp,W,input);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	std::vector<point> input;
	int N, W;
	std::cin >> N >> W;
	input.push_back({0,0});
	for(int i=0;i<W;++i) {
		int x,y;
		std::cin >> x >> y;
		input.push_back({x,y});
	}
	int dp[1001][1001];
	for(int i=0;i<=1000;++i) {
		std::fill(dp[i],dp[i]+1001,-1);
	}
	dist_from_input_to_W(input,N,W,dp,0,0);
	std::cout << dp[0][0] << '\n';

	std::vector<char> ans;
	minpath(ans,0,0,N,dp,W,input);
	for(int i=0;i<ans.size();++i) {
		std::cout << ans[i] <<'\n';
	}
	return 0;
}