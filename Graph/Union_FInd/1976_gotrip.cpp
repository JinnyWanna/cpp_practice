#include <iostream>
#include <vector>

int get_parent(std::vector<int> &parent, int x) {
    if(x==parent[x]) return x;
    else {
        return parent[x] = get_parent(parent, parent[x]);
    }
}

void union_parent(std::vector<int> &parent, int x, int y) {
    x = get_parent(parent, x);
    y = get_parent(parent, y);
    if(x<y) {
        parent[y]=x;
    }
    else {
        parent[x]=y;
    }
}

bool find_parent(std::vector<int> &parent, int x, int y) {
    if(get_parent(parent,x)==get_parent(parent,y)) {
        return true;
    }
    else return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int city, plan;
    std::cin >> city >> plan;

    std::vector<int> parent(city+1);

    for(int i=1;i<=city;++i) {
        parent[i]=i;
    }

    for(int i=1;i<=city;++i) {
        for(int j=1;j<=city;++j) {
            int num;
            std::cin >> num;
            if(i==j) continue;
            if(num) {
                union_parent(parent,i,j);
            }
        }
    }
    int first;
    std::cin >> first;
    for(int i=1;i<plan;++i) {
        int num;
        std::cin >> num;
        if(!find_parent(parent,first,num)) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}