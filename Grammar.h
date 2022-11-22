#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>

class Grammar {
public:
    Grammar() = default;
    void read_grammar(std::string file_path) {
        
    }
private:
    std::unordered_set<std::string> terminals;
    std::unordered_set<std::string> nonTerminals;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions;
};
