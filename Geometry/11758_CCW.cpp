#include <iostream>
#include <vector>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int bv_x, bv_y;
	
	int base_x, base_y;
	std::cin >> base_x >> base_y;
	
	int tmpx, tmpy;
	std::cin >> tmpx >> tmpy;

	bv_x = tmpx-base_x;
	bv_y = tmpy-base_y;

	int x,y;
	std::cin >> x >> y;
	if(bv_x*(y-base_y)>bv_y*(x-base_x)) {
		std::cout << "1\n"; 
	}
	else if (bv_x*(y-base_y)<bv_y*(x-base_x)) {
		std::cout << "-1\n";
	}
	else {
		std::cout << "0\n";
	}

	return 0;
}