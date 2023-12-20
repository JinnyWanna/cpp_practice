#include <iostream>
#include <string>
#include <vector>
// pi[i]는 주어진 문자열의 0~i 까지의 부분 문자열 중에서 prefix == suffix가 될 수 있는 부분 문자열 중에서 가장 긴 것의 길이
// (이때 prefix가 0~i  까지의 부분 문자열과 같으면 안된다.)

std::vector<int> getPi(std::string str) {
	int m = str.length();
	std::vector<int> pi(m,0);
	
	for(int i=1, j=0;i<m;++i) {
		while(j>0 && str[i] != str[j]) 
			j = pi[j-1];
		if(str[i] == str[j]) 
			pi[i] = ++j;
	}

	return pi;
}

std::vector<int> kmp(std::string text, std::string pattern) {
	std::vector<int> ans;
	auto pi = getPi(pattern);
	int n = text.length(), m = pattern.length();

	for(int i=0, j=0;i<n;++i) {
		while(j>0 && text[i] != pattern[j])
			j = pi[j-1];

		if(text[i] == pattern[j]) {
			if(j==m-1) {
				ans.push_back(i-m+1);
				j=pi[j];
			}
			else j++;
		}
	}

	return ans;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	std::string T, P;
	std::getline(std::cin, T);
	std::getline(std::cin, P);

	std::vector<int> ans = kmp(T,P);

	std::cout << ans.size() << '\n';
	for(auto i=ans.begin();i<ans.end();++i) {
		std::cout << *i+1 << ' ';
	}

	return 0;
}