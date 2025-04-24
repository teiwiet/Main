#include<iostream>
#include<string.h>
#include<stdint.h>
using namespace std;
unsigned int a = 10;
uint32_t a = 10;
void printRed(char* s){
	cout << "\033[31m" << s << "\033[0m";
}
int main(int argc,char** argv){
	string s;
	cin >> s;
	printRed(s);
}
