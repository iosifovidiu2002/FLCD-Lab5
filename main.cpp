#include "LR0.h"

int main(){
    Grammar g = Grammar();
    g.read_grammar("lr0.txt");

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

   auto states = lr0.col_can();
   auto actions = lr0.generate_actions(states);
   
//    for(auto action : actions){
//     if(action.second.type == ActionType::reduce){
//         assert(action.second.start_symbol != "");
//         std::cout << action.second.start_symbol << " " << action.second.position << "\n";
//     }
//    }

    auto output = lr0.parse_input({"$", "c", "b", "b", "a"});

    for(auto prod : output){
        std::cout << prod.first << " -> ";
        for(auto c : prod.second){
            std::cout << c << " ";
        }
        std::cout << "\n";
    }

}
