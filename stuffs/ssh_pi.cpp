#include<iostream>
#include<cstring> 
#include<cstdlib>

using namespace std;

int main(){
	string ip2 = "192.168.1.17";
	string ip4 = "192.168.1.18";
	string username = "teiwiet";
	int pi;
	cout << "pi : ";
	cin >> pi;
	string command = "";
	if(pi == 2){
	command = "ssh " + username + "@" + ip2;
	}
	else if(pi == 4 ){
	command = "ssh " + username + "@" + ip4;
	}
	system(command.c_str());
}
