 #include <bits/stdc++.h>

using namespace std ;

int main(){
    int f;
    cout<<"Please Enter a number"<<" "; cin>>f ;

    cout<<"The factors are "<<" ";
    for (int i =1 ;i<=f;i++){
        if ((f%i) == 0){
            cout<<i<<" ";
        }
    }
    return 0;

}
