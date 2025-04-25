#include <iostream>

int countBit(int x){
    int numbits = 0;
    
    while(x){
        numbits += (x&1);
        x >>= 1;
    }

    return  numbits;
}

int main(){

    std::cout<<countBit(15)<<std::endl;

    return 0;
}