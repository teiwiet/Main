#include<iostream>
using namespace std;

int main(int argc,char** argv){
	if(argc !=2){
		cout << "wrong argument\n";
		return 0;
	}
	cout << argv[1] << endl;
	return 0;
}
