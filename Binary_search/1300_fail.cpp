#include <iostream>
#include <algorithm>


int main(void) {
	std::ios_base::sync_with_stdio(false); 
    std::cin.tie(nullptr); std::cout.tie(nullptr);

	int N,k;
	std::cin >> N >> k;

	int start = 1;
	int end = k;
	
    int ans = 0;
	while(start <= end) {
		int mid = (start + end) / 2;
		int cnt = 0;
		for(int i = 1; i <= N; ++i) {
			cnt+=std::min(N,mid/i);
        }
		if(cnt < k) { // 셌는데 k보다 작은수면 다시
			start = mid + 1;
        }
    	else { // 셌는데 k보다 크거나 같으면, ans안에 들어갈 수 있음.
            ans=mid;
			end = mid - 1;
		}
	}

    std::cout<<ans;
	
    return 0;
}