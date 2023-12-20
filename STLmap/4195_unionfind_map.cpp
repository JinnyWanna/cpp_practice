#include <iostream>
#include <vector>
#include <string>
#include <map>
// map 중복 허용 x map<key, value> key 기준 정렬, 오름차순
//operator[]: map[key]=value; 가능함

int get_parent(std::vector<int> &parent, int x) {
	if(parent[x]==x) return x;
	else return parent[x]=get_parent(parent,parent[x]);
}

void union_parent(std::vector<int> &parent, std::vector<int> &answer, int x, int y) {
	x=get_parent(parent,x);
	y=get_parent(parent,y);
	if(x<y) {
		parent[y]=x;
		answer[x] += answer[y];
	}
	else if(x>y){ // 부모가 다를때만 해야함 같을때 하면 무한증가
		parent[x]=y;
		answer[y] += answer[x];
	}
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	for(int t=0;t<T;++t) {
		int F;
		std::cin >> F;
		
		std::map<std::string,int> name;
		std::vector<int> parent(2*F+1);
		std::vector<int> answer(2*F+1);
		int idx=0;

		for(int i=0;i<=2*F;++i) {
			parent[i]=i;
			answer[i]=1;
		}

		for(int i=0;i<F;++i) {
			std::string str1, str2;
			std::cin >> str1 >> str2;
			std::map<std::string,int>::iterator iter; // iterator로 주소값 저장
			int idx1, idx2;
			iter=name.find(str1); // find 못한경우 end iter반환.
			if(iter==name.end()) {
				// 없는경우 end위치에 key:str1, value:idx push
				name[str1]=++idx;
				idx1=idx;
			}
			else {
				idx1=iter->second;
			}
			iter=name.find(str2);
			if(iter==name.end()) {
				name[str2]=++idx;
				idx2=idx;
			}
			else {
				idx2=iter->second;
			}
			union_parent(parent,answer,idx1,idx2);
			int ans = get_parent(parent,idx1);
			std::cout << answer[ans] << '\n';
		}
	}	

    return 0;
}