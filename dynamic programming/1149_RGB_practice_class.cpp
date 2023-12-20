#include <iostream>
#include <algorithm>
// class 연습
class cost {
    private:
        int cost_red;
        int cost_green;
        int cost_blue;
    public:
        void set_cost(int red,int green,int blue);
        int get_red();
        int get_green();
        int get_blue();
};

void cost::set_cost(int red,int green,int blue) {
    cost_red=red;
    cost_green=green;
    cost_blue=blue;
}

inline int cost::get_red() {
    return cost_red;
}
inline int cost::get_green() {
    return cost_green;
}
inline int cost::get_blue() {
    return cost_blue;
}
int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int house;
    std::cin >> house;
    cost house_arr[1001];
    for(int i=1;i<=house;++i) {
        int R,G,B;
        std::cin >> R >> G >> B;
        house_arr[i].set_cost(R,G,B); 
    }  
    int net_cost[1001][3];
    net_cost[1][0]=house_arr[1].get_red(); net_cost[1][1]=house_arr[1].get_green();
    net_cost[1][2]=house_arr[1].get_blue();
    for(int i=2;i<=house;++i) {
        net_cost[i][0]=house_arr[i].get_red()+std::min(net_cost[i-1][1],net_cost[i-1][2]);
        net_cost[i][1]=house_arr[i].get_green()+std::min(net_cost[i-1][2],net_cost[i-1][0]);
        net_cost[i][2]=house_arr[i].get_blue()+std::min(net_cost[i-1][0],net_cost[i-1][1]);
    }
    int min=std::min(std::min(net_cost[house][0],net_cost[house][1]),net_cost[house][2]);
    std::cout << min;

    return 0;
}