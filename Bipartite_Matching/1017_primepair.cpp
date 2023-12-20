#include <bits/stdc++.h>

void eratos(std::vector<bool> &prime_number) {
	prime_number[1] = false;

	for(int i=2; i*i <= 2000; ++i) {
		if(prime_number[i] == true) {
			for(int j=2; i*j <= 2000; ++j) {
				prime_number[i*j] = false;
			}
		}
	}
}

bool dfs(int Anode, std::vector<int> &BtoAmatch, std::vector<bool> &prime_number ,std::vector<int> &Aarr, std::vector<int> &Barr, std::vector<bool> &visited, const int N) {
	for(int Bnode = 0; Bnode < N/2; ++Bnode) {
		if(!prime_number[Aarr[Anode] + Barr[Bnode]]) continue;

		if(visited[Bnode] == true) continue;
		visited[Bnode] = true;

		if(BtoAmatch[Bnode] == -1 || dfs(BtoAmatch[Bnode], BtoAmatch, prime_number, Aarr, Barr, visited, N)) {
			BtoAmatch[Bnode] = Anode;

			return true;
		}
	}

	return false;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);
// set prime
	std::vector<bool> prime_number(2001, true);

	eratos(prime_number);
// main
	int N;
	std::cin >> N;

	std::vector<int> Aarr; //
	std::vector<int> Barr; //

	std::vector<int> AtoBmatch(N+1, -1);
	std::vector<int> BtoAmatch(N+1, -1);
// input numbers
	int a, eo = 1;
	std::cin >> a;
	Aarr.push_back(a); // 첫수는 Aarr

	if(a%2 == 0) { // a가 짝수면
		eo = 0;
	} // eo가 0인경우, Aarr가 짝수

	for(int i=1; i<N; ++i) {
		int x;
		std::cin >> x;

		if(x%2 != eo) {
			Barr.push_back(x);
		}
		else {
			Aarr.push_back(x);
		}
	}

	if(Barr.size() != Aarr.size()) {
		std::cout << "-1\n"; 
		return 0;
	}

	std::sort(Barr.begin(), Barr.end());

// bipartite matching
	std::vector<int> ans;

	for(int i=0; i<N/2; ++i) {
		AtoBmatch = std::vector<int>(N+1, -1);
		BtoAmatch = std::vector<int>(N+1, -1);

		if(prime_number[Aarr[0] + Barr[i]] == true) {
			AtoBmatch[0] = i;
			BtoAmatch[i] = 0;
			
			int prime = 1;

			for(int j=1; j<N/2; ++j) {
				
				std::vector<bool> visited((N/2)+1, false);
				visited[i] = true; // 0번 노드와 i 연결, i는 다신 못건들게
				
				if(dfs(j,BtoAmatch, prime_number, Aarr, Barr, visited, N)) {
					prime++;
				}
				
			}

			if(prime == (N/2)) {
				ans.push_back(i);
			}
		}
	}

	if(ans.size() == 0) {
		std::cout << "-1\n";
	}
	else {
		for(auto i : ans) {	
			std::cout << Barr[i] << ' ';
		}
	}

	return 0;
}