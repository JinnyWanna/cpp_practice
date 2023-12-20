#include <iostream>
#include <vector>

int get_parent(std::vector<int> &parent,int x) {
    if(x==parent[x]) return x;
    else {
        return parent[x] = get_parent(parent,parent[x]);
    }
}

void union_parent(std::vector<int> &parent, int x, int y) {
    x = get_parent(parent, x);
    y = get_parent(parent, y);
    if(x<y) parent[y]=x;
    else parent[x]=y;
}

bool find_parent(std::vector<int> &parent, int x, int y) {
    x = get_parent(parent, x);
    y = get_parent(parent, y);
    if(x == y) return true;
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> parent(n+1);
    for(int i=0;i<=n;++i) {
        parent[i]=i;
    }

    for(int i=0;i<m;++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        if(x==0) {
            union_parent(parent,y,z);
        }
        else {
            if(find_parent(parent,y,z)) std::cout << "YES\n";
            else std::cout << "NO\n";
        }
    }

    return 0;
}