#include <iostream>
using namespace std;
class Good{
	public:
		Good(string = "熊大", double = 0.0, int = 300);
		void allSet(string = "熊大", double = 0.0, int = 300);
		void setCount(int);
		string getGoodname();
		double getPrice();
		int getCount();
	private:
		char goodname[20]; //品名
		double price; //價格 
		int count; //數量 
};
