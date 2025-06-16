#include<iostream>
using namespace std;

int main(){
	int size = sizeof(0b00000000000000000000000000000001)/sizeof(int);
	cout << size;
}
