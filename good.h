#include <iostream>
using namespace std;
class Good{
	public:
		Good(string = "���j", double = 0.0, int = 300);
		void allSet(string = "���j", double = 0.0, int = 300);
		void setCount(int);
		string getGoodname();
		double getPrice();
		int getCount();
	private:
		char goodname[20]; //�~�W
		double price; //���� 
		int count; //�ƶq 
};
