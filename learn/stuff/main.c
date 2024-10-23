#include<unistd.h>
#include<string.h>
int main(){
	char* lmao = "Hello World";
	write(1,lmao,strlen(lmao));
}
