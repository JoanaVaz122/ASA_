#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rectangle {
    int width; 
    int height;
    int value;
};



int max_value(int X, int Y, vector<Rectangle>& Pecas){

    //tratamento de erros
    if (X <= 0 || Y <= 0) {
        return 0; //se a peça tiver uma medida a 0s
    }

    for (int i = 0; i < Pecas.size(); i++){ //se uma das medidas da peça for 0 
        if (Pecas[i + 1] != nullptr) {
            if (Pecas[i].width == 0 || Pecas[i].height == 0){
                i++;
            }
        }else{
            return 0;
        }
    }


    //codigo para fazer as funcionalidades

    std::vector<std::vector<int>> memo(X, std::vector<int>(Y, 0));

    for (int i = 0; i < Pecas.size(); i++){


        if (X % Pecas[i].width == 0 ){ // corte vertical

             //deixar a peca como esta

        }else{
            //rodar a peca
        }
        
}
}