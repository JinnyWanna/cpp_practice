#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::ios::sync_with_stdio(false); 
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	const int INF = 1000000000;
	const int MAX_city = 100 + 1;

	int n, m;
	std::cin >> n >> m;
	int map[MAX_city][MAX_city] ={0,};
    std::vector<int> ans[MAX_city][MAX_city];
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			if(i!=j) {
				map[i][j]=INF;
			}
            ans[i][j].push_back(i);
            ans[i][j].push_back(j);
		}
	}

	for(int i=0;i<m;++i) {
		int x, y, z;
		std::cin >> x >> y >> z;
		if(map[x][y]>z) {
			map[x][y]=z;
		}	
	}

	
	for(int k=1;k<=n;++k) {
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=n;++j) {
				if(i==j) continue;
				if(map[i][j]>map[i][k]+map[k][j]) {
					map[i][j]=map[i][k]+map[k][j];
					std::vector<int> t = ans[k][j];
					ans[i][j].clear();
					ans[i][j] = ans[i][k];
					for(int m=1;m<t.size();++m)
						ans[i][j].push_back(t[m]);
				}
			}
		}
	}

	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			if(map[i][j]==INF) {
				map[i][j]=0;
			}
			std::cout << map[i][j] << ' ';
		}
		std::cout << '\n';
	}

	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			if(map[i][j]==0) {
				std::cout << '0' <<'\n';
				continue;
			}
            std::cout << ans[i][j].size() << ' ';
            for(int k=0;k<ans[i][j].size();++k) {
                std::cout << ans[i][j][k] << ' ';
            }
            std::cout << '\n';
		}
	}
	
	return 0;
}