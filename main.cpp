#include "Grammar.h"

int main(){
    Grammar g = Grammar();
    g.read_grammar("g1.txt");

    for(auto pair : g.get_productions()){
        for (auto prod : pair.second){
            std::string full_prod = "";
            for(auto t: prod){
                full_prod += t + " ";
            }
            std::cout << pair.first << " -> " << full_prod << "\n";
        }
    }    
}
