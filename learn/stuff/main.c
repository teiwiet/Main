#include<stdio.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<unistd.h>
#include<string.h>
int main(){
	char* lmao = "Hello World";
	write(1,lmao,strlen(lmao));
}
