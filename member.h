#include <iostream>
using namespace std;

//�|����� 
class Member{
	public:
		Member(int = 1000, string = "A99", string = "P99", string = "Angela", int = 0);
		void setAll(int = 1000, string = "A99", string = "P99", string = "Angela", int = 0);
		void setNumber(int);
		int getNumber(); 
		string getAccount();
		string getPassword();
		string getName();
		void setBalance(int); //�ΨӲֿn���B 
		int getBalance(); //�ΨӲֿn���B 
		bool empty();
		void print(); //�C�L 
	private:
		int number; //�s�� 
		char account[15]; //�b�� 
		char password[15]; //�K�X
		char name[15]; //�m�W 
		int balance; //���B 
};
