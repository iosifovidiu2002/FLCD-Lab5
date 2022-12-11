#include "LR0.h"

int main(){
    Grammar g = Grammar();
    g.read_grammar("g2.txt");

    for(auto pair : g.get_productions()){
        for (auto prod : pair.second){
            std::string full_prod = "";
            for(auto t: prod){
                full_prod += t + " ";
            }
            std::cout << pair.first << " -> " << full_prod << "\n";
        }
    }    

   LR0 lr0(g); 

   auto actions = lr0.generate_actions();
   auto states = lr0.col_can();

   for(auto action : actions){
    std::cout << "State:\n";
    print(states[action.first]);
    std::cout << "Action: " << action.second.type << "\n";
   }
}
