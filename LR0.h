#include "Grammar.h"
#include <iostream>

struct LR0Item {
    std::string start_symbol;
    std::vector<std::string> left;
    std::vector<std::string> right;

    LR0Item(std::string _start_symbol,
            std::vector<std::string> _left,
            std::vector<std::string> _right):
        start_symbol(_start_symbol),
        left(_left),
        right(_right) {}

    bool operator== (const LR0Item &other) {
        if(start_symbol != other.start_symbol) return false;
        if(left.size() != other.left.size()) return  false;
        for(int i=0; i<left.size(); i++) {
            if(left[i] != other.left[i]) return false;
        }
        if(right.size() != other.right.size()) return false;
        for(int i=0; i<right.size(); i++) {
            if(right[i] != other.right[i]) return false;
        }
        return true;
    }
};

typedef std::vector<LR0Item> LR0State;
typedef std::vector<LR0State> LR0States;

void print(LR0State &state) {
    
    std::cout << "{ ";
    for(auto item: state) {
        std::cout << "[";
        std::cout << item.start_symbol << " -> ";
        for(auto elem: item.left) std::cout << elem;
        std::cout << ".";
        for(auto elem: item.right) std::cout << elem;
        std::cout << "]";
        if(!(item == state.back())) {
            std::cout << ", ";
        }
    }
    std::cout << " }\n";
}

bool state_exists_in(LR0States &states, LR0State &to_check) {
    print(to_check);
    for(auto &state: states) {
        if(state.size() != to_check.size()) {
            continue;
        }
        if(std::is_permutation(state.begin(), state.end(), to_check.begin())) 
        {
            return true;
        }
    }
    return false;
}

class LR0 {
public:
    LR0(Grammar &grammar): _grammar(grammar) {}

    LR0State closure(LR0State startItem) {
        LR0State C = startItem;
        int solved_idx = 0;
        while(solved_idx < C.size()) {
            for(;solved_idx < C.size(); solved_idx++) {
                auto itemProd = C[solved_idx];
                if(itemProd.right.size() <= 0) continue;
                auto B = itemProd.right[0];
                if(!_grammar.isNonTerminal(B)) continue;
                for(auto prod: _grammar.productions_for(B)) {
                    LR0Item new_item(B, std::vector<std::string>(), prod); 
                    if(std::find(C.begin(), C.end(), new_item) != C.end()) continue;
                    C.push_back(new_item);
                }
            }
        }
        return C;
    }

    LR0State go_to(LR0State state, std::string symbol) {
        LR0State adjusted_state;
        for(auto item: state) {
            if(item.right.size() <= 0) continue;
            if(item.right[0] != symbol) continue;
            LR0Item new_item(
                    item.start_symbol,
                    item.left, 
                    std::vector<std::string>(
                        item.right.begin()+1, 
                        item.right.end())
                    );
            new_item.left.push_back(symbol);
            adjusted_state.push_back(new_item);
        }
        return closure(adjusted_state);
    }

    LR0States col_can() {
        LR0States C;
        LR0Item starting_item(
                "S'",
                std::vector<std::string>(),
                {_grammar.getStartNT()});
        C.push_back(closure({starting_item}));
        int solved_idx = 0;
        auto symbols = _grammar.get_symbols();
        while(solved_idx < C.size()) {
            for(;solved_idx < C.size(); solved_idx++) {
                auto state = C[solved_idx];
                for(auto symbol: symbols) {
                    auto new_state = go_to(state, symbol);
                    if(new_state.size() <= 0) {
                        continue;
                    }
                    if(state_exists_in(C, new_state)) {
                        continue;
                    }
                    C.push_back(new_state);
                }
            }
        }
        return C;
    }

private:
    Grammar &_grammar;
};
