#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <iostream>

class Grammar {
public:
    Grammar() = default;
    void read_grammar(std::string file_path) {
        std::ifstream file;

        try{
            file.open(file_path);
        } catch (std::ios_base::failure& e){
            std::cout << e.what() << '\n';
        }

        std::string line; 
    }
private:
    std::unordered_set<std::string> terminals;
    std::unordered_set<std::string> nonTerminals;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions;
};
