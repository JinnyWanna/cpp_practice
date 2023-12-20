#include <iostream>
#include <algorithm>
#include <vector>
class pos {

public:
    int rank;
    int numb;
};

int compare_num(pos point1,pos point2) {
    return point1.numb<point2.numb;
}

int compare_rank(pos point1,pos point2) {
    return point1.rank<point2.rank;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::vector<pos> point_vec;
    int N;
    std::cin >> N;
    for(int i=0;i<N;++i) {
        int tmp;
        std::cin >> tmp;
        point_vec.push_back({i,tmp});
    }

    std::sort(point_vec.begin(),point_vec.end(),compare_num);

    int num=point_vec[0].numb;
    int cnt=0;
    for(int i=0;i<N;++i) {
        if(point_vec[i].numb==num) {
            point_vec[i].numb=cnt;
        }
        else {
            cnt+=1;
            num=point_vec[i].numb;
            point_vec[i].numb=cnt;
        }
    }

    std::sort(point_vec.begin(),point_vec.end(),compare_rank);

    for(int i=0;i<N;++i) {
        std::cout << point_vec[i].numb << ' ';
    }
    return 0;
}