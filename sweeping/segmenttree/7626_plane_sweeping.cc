#include <bits/stdc++.h>

typedef long long lint;

struct line {
    lint x;
    lint y1, y2;
    bool start; // true - 시작지점, false - 끝지점
};

struct treein {
    lint sum;
    lint cnt;
};

bool cmp(const line &l1, const line &l2) {
    if(l1.x == l2.x) return l1.y1 < l2.y1;

    return l1.x < l2.x;
}

bool ycmp(const lint &a, const lint &b) {
    return a < b;
}

std::vector<lint> ylist;

void update(std::vector<treein> &tree, int node, int left, int right, int start, int end, int value) {
    if(left > end || right < start) return;

    if(left <= start && end <= right) {
        tree[node].cnt += value;
    }
    else {
        int mid = (start + end) >> 1;
        update(tree,node<<1,left,right,start,mid,value);
        update(tree,(node<<1)|1,left,right,mid+1,end,value);
    }

    if(tree[node].cnt) { 
        tree[node].sum = ylist[end+1] - ylist[start]; // 저장한 맨 밑 노드에 길이 넣음
    }
    else {
        if(start != end) tree[node].sum = tree[node<<1].sum + tree[(node<<1)|1].sum;
    
        else tree[node].sum = 0;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<line> arr_vec;
    for(int i=0; i<N; ++i) {
        lint x1, y1, x2, y2;

        std::cin >> x1 >> x2 >> y1 >> y2;

        arr_vec.push_back({x1,y1,y2,true});
        arr_vec.push_back({x2,y1,y2,false});
        ylist.push_back(y1);
        ylist.push_back(y2);
    }

    std::sort(arr_vec.begin(),arr_vec.end(),cmp);  
    std::sort(ylist.begin(), ylist.end(), ycmp);
    ylist.erase(std::unique(ylist.begin(),ylist.end()), ylist.end());     

    const int height = (int)ceil(log2(ylist.size() + 1));
    std::vector<treein> tree(1<<(height+1),{0,0});

    lint ans = 0;
    for(int i=0; i<arr_vec.size(); ++i) {
        if(i) ans += (arr_vec[i].x - arr_vec[i-1].x) * tree[1].sum;

        int value = (arr_vec[i].start == true) ? 1 : -1;
        lint st = std::upper_bound(ylist.begin(), ylist.end(), arr_vec[i].y1) - ylist.begin() - 1;
        lint ed = std::upper_bound(ylist.begin(), ylist.end(), arr_vec[i].y2) - ylist.begin() - 1;
        update(tree,1,st,ed-1,0,ylist.size()-1,value);
    }

    std::cout << ans << '\n';   

    return 0;
}