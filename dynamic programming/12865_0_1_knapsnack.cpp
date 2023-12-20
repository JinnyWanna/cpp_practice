#include <iostream>
#include <vector>
#include <algorithm>

int dp[101][100001];

class product {
public:
    int weight;
    int value;
};

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::vector<product> input_vec;
    int n,k;
    std::cin >> n >> k;
    input_vec.push_back({0,0});
    for(int i=1;i<=n;++i) {
        int weight, val;
        std::cin >> weight >> val;
        input_vec.push_back({weight,val});
    } // data input
// 무게는 k에 저장되어있으니 굳이 따로 저장할필요 없음
// k 무게를 이용 가능했을때 최대의 가치를 구하자.
// n은 1부터, 1일땐 1번물건만 이용했을때. 2일땐, 1번,2번 물건을 이용....
    for(int i=1;i<=n;++i) {
        for(int j=1;j<=k;++j) {
            if(j>=input_vec[i].weight) 
                dp[i][j]=std::max(dp[i-1][j],dp[i-1][j-input_vec[i].weight]+input_vec[i].value);
            else dp[i][j]=dp[i-1][j];
        } // 2번 물건을 이용할때, 이전 물건들로만 채웠을때 나올수 있는 최댓값 vs 이번 물건을 꼭 이용했을때 나오는 최댓값
    }
    std::cout << dp[n][k];
    return 0;
}

/*

#include <iostream>
#include <algorithm>
using namespace std;
int d[100001];
int w[102];
int v[102];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, k;

	cin>> n >>k ;
	for(int i = 1; i <= n; i++){
		cin >> w[i] >> v[i];
	}
	for(int i = 1; i <= n; i++){
		for(int j = k; j >= 1; j--){
			if(w[i] <= j){
				d[j] = max(d[j], d[j - w[i]] + v[i]);
			}
		}
	}
	cout << d[k];
	
}

*/