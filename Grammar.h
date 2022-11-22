#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <iostream>

std::vector<std::string> str_split(std::string toSplit, int max_split = INT32_MAX) {
    int i=0;
    std::vector<std::string> splitted;
    while(i < toSplit.size() && toSplit[i] == ' ') i++;
    int idx = i;
    for(; i < toSplit.size() && splitted.size() < max_split + 1; i++) {
        if(toSplit[i] == ' ') {
            int str_size = i - idx;
            splitted.push_back(toSplit.substr(idx, str_size));
            while(i < toSplit.size() && toSplit[i] == ' ') i++;
            idx = i;
        }
    }
    if(idx < toSplit.size()) {
        int str_size = i - idx;
        splitted.push_back(toSplit.substr(idx, str_size));
    }
    return splitted;
}

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

        // Read all non termials
        std::getline(file, line);
        
        // Read all termials
        std::getline(file, line);

        // Read starting non terminal
        std::getline(file, line);

        while(std::getline(file, line)){
            // Process current production
        }

    }
private:
    std::string startNT;
    std::unordered_set<std::string> terminals;
    std::unordered_set<std::string> nonTerminals;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions;
};
