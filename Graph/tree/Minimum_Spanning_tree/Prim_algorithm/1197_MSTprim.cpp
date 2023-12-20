#include <iostream>
#include <vector>
#include <queue>
/* prim algorithm?
pick 1 node, from it to move minimum cost node .
check visited. if visited = false , ans+=cost , 
if visited = true , continue .
if pQ is empty, return.
*/

struct Vpair {
	int next;
	int cost;

	Vpair() : next(0), cost(0) {}
	Vpair(int next, int cost) : next(next), cost(cost) {}

	Vpair(const Vpair &pair) {
		this->next = pair.next;
		this->cost = pair.cost;
	}
};

struct Qpair {
	int curnode;
	int cost;

	Qpair(int _curnode, int _cost) : curnode(_curnode), cost(_cost) {}
	
	Qpair(const Qpair &pair) {
		this->curnode = pair.curnode;
		this->cost = pair.cost;
	}
};

struct cmp{
	bool operator()(const Qpair &A, const Qpair &B){
		return A.cost > B.cost;
	}
};

void prim(const std::vector<std::vector<Vpair>> &edge, std::vector<bool> &visited, int &ans) {
	std::priority_queue<Qpair, std::vector<Qpair>, cmp> pQ;
	pQ.push(Qpair(1,0));

	while(!pQ.empty()) {
		Qpair now(pQ.top());
		pQ.pop();

		if(visited[now.curnode] == true) continue;
		visited[now.curnode]=true;
		ans+=now.cost;

		for(auto i = edge[now.curnode].begin();i<edge[now.curnode].end();++i) {
			if(!visited[i->next]) {
				pQ.push(Qpair(i->next,i->cost));
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int V, E;
	std::cin >> V >> E;

	std::vector<std::vector<Vpair>> edge(V+1,std::vector<Vpair>());
	std::vector<bool> visited(V+1,false);
	int ans(0);

	for(int i=0;i<E;++i) {
		int A, B, C;
		std::cin >> A >> B >> C;
		edge[A].push_back(Vpair(B,C));
		edge[B].push_back(Vpair(A,C));
	}

	prim(edge,visited,ans);

	std::cout << ans << '\n';

	return 0;
}
