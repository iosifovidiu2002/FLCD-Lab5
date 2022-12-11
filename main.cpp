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

   for(auto &state:states) {
       print(state);
   }
}
