#include <iostream>
using namespace std;

int bis(int x, int m);
int bic(int x, int m);

int bis(int x, int m){

    return (x | m);
}

int bic(int x, int m){
    
    return (x & ~m);
}

int bool_or(int x, int y) {
    int result = bis(x,y);
    return result;
}

int bool_xor(int x, int y) {
    int result = bis ( bic(x,y) , bic(y,x) );
    return result;
}
   
int main(){
    cout<<bool_or(5,6)<<"\n";
    cout<<bool_xor(5,6)<<"\n";
    return 0;
}