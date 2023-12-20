#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int M, x, BIT = 0;
    std::cin >> M;

    std::string input;
    while (M--) {
        std::cin >> input;

        if (input == "add") {
            std::cin >> x;
            BIT |= (1 << x);
        }

        else if (input == "remove") {
            std::cin >> x;
            BIT &= ~(1 << x);
        }

        else if (input == "check") {
            std::cin >> x;
            if (BIT & (1 << x))
                std::cout << "1\n";
            else
                std::cout << "0\n";
        }

        else if (input == "toggle") {
            std::cin >> x;
            BIT ^= (1 << x);
        }

        else if (input == "all") {
            BIT = (1 << 21) - 1;
        }

        else if (input == "empty") {
            BIT = 0;
        }

        input.clear();
    }

    return 0;
}