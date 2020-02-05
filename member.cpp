#include "member.h"

Member::Member(int n, string a, string p, string na, int b){
	setAll(n, a, p, na, b);
}

void Member::setAll(int n, string a, string p, string na, int b){
	number = n;
	for(int i=0;i<a.size();i++){
		account[i] = a[i];
	}
	account[a.size()] = '\0';
	 
	for(int i=0;i<p.size();i++){
		password[i] = p[i];
	}
	password[p.size()] = '\0';
	
	for(int i=0;i<na.size();i++){
		name[i] = na[i];
	}
	name[na.size()] = '\0';
	balance = b;
}

string Member::getAccount(){
	return account;
}

string Member::getPassword(){
	return password;
}

string Member::getName(){
	return name;
}
void Member::setNumber(int num){
	number = num;
} 
int Member::getNumber(){
	return number;
}

void Member::setBalance(int b){
	balance = b;
}

int Member::getBalance(){
	return balance;
}

bool Member::empty(){
	if(number == 1000) return true;
	return false;
}

void Member::print(){
	cout << number << "\t" << account << "\t" << password << "\t" << name << "\t" << balance << endl;
}
