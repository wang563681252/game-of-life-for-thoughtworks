#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "../src/lifeGame.h"
#include <vector>

using namespace std;
using mapType = vector<vector<bool> >;

bool isTheSame(const mapType &lhs, const mapType &rhs) {
    for (int i = 0; i < lhs.size(); ++i) {
        for (int j = 0; j < lhs[i].size(); ++j) {
            if (lhs[i][j] != rhs[i][j])
                return false;
        }
    }
    return true;
}

bool judge(mapType cur, mapType res) {
    updateMap(cur);
    return isTheSame(cur, res);
}

TEST_CASE("Factorials are computed", "[factorial]") {
    mapType cur1 = vector<vector<bool> >(1, vector<bool>{1, 1, 1});
    mapType res1 = vector<vector<bool> >(1, vector<bool>{0, 1, 0});
    REQUIRE(judge(cur1, res1));

}