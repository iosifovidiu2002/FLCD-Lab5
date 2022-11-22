#include "Grammar.h"
#include <assert.h>

using namespace std;

void test(string str, vector<string> expected) {
    cout << "Started test for: " << str << '\n';
    auto result = str_split(str);
    assert(result.size() == expected.size());
    for(int i=0; i<result.size(); i++) {
        assert(result[i] == expected[i]);
    }
    cout << "Test passed !!!\n";
}

int main() {
    test("Ana are mere", {"Ana","are","mere"});
    test("  Ana  are mere  ", {"Ana","are","mere"});
    test("", {});
    test(" A B C D", {"A", "B", "C", "D"});
}
