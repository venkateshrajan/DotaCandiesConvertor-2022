#include <iostream>
#include <vector>

#define MAX_LEVEL 5

// These are all the candies you have
// Feed in order {Blue, Orange, Green, Purple, Red}
std::vector<int> c = { 5, 5, 0, 3, 6 };

// These are all the candies you want
// Feed in order {Blue, Orange, Green, Purple, Red}
std::vector<int> w = { 3, 3, 4, 1, 5 };

int r[4][2][5] = { {{0, 2, 0, 1, 0}, {3, 0, 1, 0, 0}},
{{0, 1, 0, 1, 0}, {3, 0, 0, 0, 0}},
{{1, 1, 0, 0, 0}, {0, 0, 1, 1, 0}},
{{0, 0, 2, 0, 1}, {0, 1, 0, 3, 0}} };

bool solve(std::vector<int> v, int level)
{
    if (level > MAX_LEVEL)
        return false;
    for (int i=0; i<5; i++) {
        std::cout<< v[i] << " ";
    }

    std::cout<< std::endl;

    bool matched = true;
    for (int i = 0; i < 5; i++) {
        if (v[i] < w[i]) {
            matched = false;
            break;
        }
    }

    if (matched)
        return true;

    // use this recipe and call solve
    for (int i = 0; i < 4; i++) {
        std::vector<int> v1(v);
        bool recipeApplied = true;
        for (int j = 0; j < 5; j++) {
            if (v1[j] < r[i][0][j]) {
                recipeApplied = false;
                break;
            }

            v1[j] -= r[i][0][j];
            v1[j] += r[i][1][j];

        }

        if (recipeApplied) {
            std::cout<< "applying: " << i << std::endl;
            if (solve(v1, level+1))
                return true;
            std::cout<< "reverting: " << i << std::endl;
        }
    }

    // For custom recipe
    for (int i = 0; i < 5; i++) {
        std::vector<int> v1(v);
        for (int j = 0; j < 5; j++) {
            if (v1[i] < 3)
                continue;

            v1[i] -= 3;
            v1[j] += 1;
            std::cout<< "applying 3 " << i << std::endl;
            if (solve(v1, level+1))
                return true;
            std::cout<< "reverting 3 " << i << std::endl;
        }
    }

    return false;
}

int main() {
    if (!solve(c, 0))
        std::cout << "unsolvable" << std::endl;
    else
        std::cout << "Matched";
    return 0;
}