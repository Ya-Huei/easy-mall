#include <iostream>
using namespace std;

//會員資料 
class Member{
	public:
		Member(int = 1000, string = "A99", string = "P99", string = "Angela", int = 0);
		void setAll(int = 1000, string = "A99", string = "P99", string = "Angela", int = 0);
		void setNumber(int);
		int getNumber(); 
		string getAccount();
		string getPassword();
		string getName();
		void setBalance(int); //用來累積金額 
		int getBalance(); //用來累積金額 
		bool empty();
		void print(); //列印 
	private:
		int number; //編號 
		char account[15]; //帳號 
		char password[15]; //密碼
		char name[15]; //姓名 
		int balance; //金額 
};
