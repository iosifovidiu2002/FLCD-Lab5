#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <algorithm>

std::vector<std::string> str_split(std::string toSplit, int max_split = INT32_MAX) {
    int i=0;
    std::vector<std::string> splitted;
    while(i < toSplit.size() && toSplit[i] == ' ') i++;
    int idx = i;
    for(; i < toSplit.size() && splitted.size() < max_split; i++) {
        if(toSplit[i] == ' ') {
            int str_size = i - idx;
            splitted.push_back(toSplit.substr(idx, str_size));
            while(i < toSplit.size() && toSplit[i] == ' ') i++;
            idx = i;
        }
    }
    if(idx < toSplit.size()) {
        int str_size = toSplit.size() - idx;
        splitted.push_back(toSplit.substr(idx, str_size));
    }
    return splitted;
}

class Grammar {
public:
    Grammar() = default;

    std::unordered_map<std::string, std::vector<std::vector<std::string>>> get_productions(){
        return productions;
    }

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
        auto non_terminals = str_split(line);
        std::copy(non_terminals.begin(),non_terminals.end(),std::inserter(nonTerminals, nonTerminals.end()));
        
        // Read all termials
        std::getline(file, line);
        auto terminals = str_split(line);
        std::copy(terminals.begin(),terminals.end(),std::inserter(this->terminals, this->terminals.end()));

        // Read starting non terminal
        std::getline(file, line);
        startNT = line;

        while(std::getline(file, line)){
            // Process current production
            auto prod_split = str_split(line, 2);
            auto lhs = prod_split[0];
            if(nonTerminals.find(lhs) == nonTerminals.end()){
                throw std::runtime_error("CFG check ");
            }
            if(productions.find(lhs) == productions.end()){
                productions[lhs] = {};
            }
            auto rhs = prod_split[2];
            auto rhs_split = str_split(rhs);
            std::vector<std::string> current_production_value;
            for(auto c : rhs_split){
                if(c == "|"){
                    productions[lhs].push_back(current_production_value);
                    current_production_value = {};
                } else{
                    current_production_value.push_back(c);
                }
            }
            productions[lhs].push_back(current_production_value);
        }
    }

    std::string getStartNT() {
        return startNT;
    }

    bool isNonTerminal(std::string elem) {
        return nonTerminals.find(elem) != nonTerminals.end();
    }

    std::vector<std::vector<std::string>> productions_for(std::string nonTerminal) {
        return productions[nonTerminal];
    };

    std::unordered_set<std::string> get_symbols() {
        std::unordered_set<std::string> result;
        std::set_union(
                terminals.begin(), terminals.end(),
                nonTerminals.begin(), nonTerminals.end(),
                std::inserter(result, result.begin())
                );
        return result;
    }

private:
    std::string startNT;
    std::unordered_set<std::string> terminals;
    std::unordered_set<std::string> nonTerminals;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions;
};
