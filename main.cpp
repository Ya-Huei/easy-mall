#include "member.h"
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "good.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

enum Choices {LOGIN = 1, NEWACCOUNT, DELETEACCOUNT, END};
int menu(){
	int choice;
	cout << "請選擇: " << endl; 
	cout << "1. 登入" << endl;
	cout << "2. 申請帳號" << endl;
	cout << "3. 刪除帳號" << endl;
	cout << "4. 退出" << endl;
	cin >> choice;
	return choice;
}
Member login();
void newaccount();
void deleteAccount();
int afterLoginMenu();
void afterlogin(Member);
void purchase(vector<Good> &,vector<Good> &);
void returngood(vector<Good> &, vector<Good> &);
void checkout(vector<Good> &, Member);
void Boss(vector<Good> &);
int main(int argc, char** argv) { 
	int choice;
	while((choice = menu()) != END){
		switch(choice){
			case LOGIN: 
				afterlogin(login());
				break;
			case NEWACCOUNT: 
				newaccount();
				break;
			case DELETEACCOUNT:
				deleteAccount();
			default: break;
		}
	}
	ifstream ior("成員更新.data", ios::in | ios::binary);
	ofstream iow("資料成員.txt", ios::out);
	iow << setw(5) << "編號" << setw(15) << "帳號" << setw(15) << "密碼" << setw(15) << "姓名" << setw(15) << "金額" << endl;
	Member tmp;
	ior.seekg(0);
	ior.read(reinterpret_cast<char*>(&tmp), sizeof(Member));
	while(!ior.eof()){
		if(tmp.getName() == "Angela"){
			ior.read(reinterpret_cast<char*>(&tmp), sizeof(Member));
			continue;
		}
		iow << setw(5) << tmp.getNumber() << setw(15) << tmp.getAccount() << setw(15) << tmp.getPassword() << setw(15) << tmp.getName() << setw(15) << tmp.getBalance() << endl;
		ior.read(reinterpret_cast<char*>(&tmp), sizeof(Member));
	}
		
	return 0;
}
Member login(){
	fstream iof("成員更新.data", ios::in | ios::out | ios::binary);
	if( !iof ){
		cerr << "檔案無法開啟" << endl;
		exit(1); 
	}
	string acc, pas;
	cout << "帳號 :"; 
	cin >> acc;
	Member tmp, failtmp;//failtmp用作回傳空的Member 
	iof.seekg(0);
	iof.read(reinterpret_cast<char*>(&tmp), sizeof(Member));
	while(!iof.eof()){
		if(tmp.getAccount() == acc){
			cout << "密碼 :"; 
			cin >> pas;
			if(tmp.getPassword() == pas){
				if(tmp.getAccount() == "brownboss"){
					cout << "老闆  您回來了" << endl;
					return tmp;
				}
				else{ 
					cout << "歡迎你" <<endl;
					return tmp;
				}
			}
			else{
				cout << "密碼錯誤" <<endl; 
				return failtmp;
			}
		}
		iof.read(reinterpret_cast<char*>(&tmp),sizeof(Member));
	}
	cout <<"查無此帳號"<<endl;
	return failtmp; 
}

void newaccount(){
	fstream iof("成員更新.data", ios::in | ios::binary);
	if( !iof ){
		cerr << "檔案無法開啟" << endl;
		exit(1); 
	}
	int num;
	string acc, pas, name;
	double bal;
	Member d, tmp;
	cout << "請輸入帳號、密碼及姓名: " << endl; 
	cin >> acc >> pas >> name;
	iof.seekg(0);
	iof.read(reinterpret_cast<char*>(&tmp), sizeof(Member));
	while(!iof.eof()){
		if(tmp.getAccount() == acc){
			cout << "此帳號已被註冊過"<<endl;
			iof.clear();
			iof.close();
			return;
		}
		iof.read(reinterpret_cast<char*>(&tmp), sizeof(Member));
	}
	iof.clear();
	iof.seekg(sizeof(Member),ios::end);
	iof.read(reinterpret_cast<char*>(&tmp), sizeof(Member));
	num = tmp.getNumber() + 1;
	iof.close();
	fstream iow("成員更新.data",ios::out | ios::app | ios::binary);
	if( !iow ){
		cerr << "檔案無法開啟" << endl;
		exit(1); 
	}
	
	d.setAll(num, acc, pas, name);
	if(num > 1000 && num < 1101){
		iow.seekp(0, ios::end);
		iow.write( reinterpret_cast<char*>(&d), sizeof(Member));
	}
	cout <<"帳號註冊完成"<<endl;
	iow.close();
}

void deleteAccount(){
	fstream iof("成員更新.data", ios::in | ios::out | ios::binary);
	if( !iof ){
		cerr << "檔案無法開啟" << endl;
		exit(1); 
	}
	int number;
	Member d, e;
	cin >> number;
	e.setNumber(number);
	number = number - 1000;
	iof.seekg((number-1)*sizeof(Member));
	iof.read(reinterpret_cast<char*>(&d), sizeof(Member));
	
	if(d.empty()){
		cerr << "資料不存在" << endl;
		return;
	}
	d.print();
	iof.seekp((number-1)*sizeof(Member));
	iof.write(reinterpret_cast<char*>(&e), sizeof(Member));	
	iof.close();
}

enum Choicestwo {PURCHASE = 1, RETURNGOOD, CHECKOUT, ENDEND};
int afterLoginMenu(){
	int choice;
	cout << "請選擇: " << endl; 
	cout << "1. 購買" << endl;
	cout << "2. 退貨" << endl;
	cout << "3. 結帳" << endl; 
	cout << "4. 離開" << endl;
	cout << "若無結帳而選擇離開, 購買紀錄將取消" <<endl; 
	cin >> choice;
	return choice;
}

void afterlogin(Member log){
	fstream iof("產品資料更新.data", ios::in | ios::binary); //讀 
	if(!iof){
		cerr << "檔案無法開啟" << endl;
		exit(1); 
	}
	Good tmpGood;
	vector<Good> Goods;
	vector<Good> BuyList;
	iof.seekg(0);
	iof.read(reinterpret_cast<char*>(&tmpGood), sizeof(Good));
	while(!iof.eof()){
		Goods.push_back(tmpGood);
		iof.read(reinterpret_cast<char*>(&tmpGood), sizeof(Good));
	}
	if(log.getName() == "Angela"){
		iof.close();
		return;
	}
	if(log.getName() == "brownboss"){
		cout << "----------------進入老闆介面----------------" << endl;
		Boss(Goods);
		iof.close(); 
		fstream iow("產品資料更新.data", ios::out | ios::binary); //寫 
		if(!iow){
			cerr << "檔案無法開啟" << endl;
			exit(1); 
		} 
		iow.seekp(0);
		for(int i = 0; i < Goods.size(); i++){
			tmpGood = Goods[i];
			iow.write(reinterpret_cast<char*>(&tmpGood), sizeof(Good));
			}
		iow.close();
		iow.open("產品資料.txt", ios::out);
		if(!iow){
			cerr << "檔案無法開啟" << endl;
			exit(1); 
		}
		iow << setw(5) << "產品名稱" << setw(20) << "產品價格" << setw(20) << "產品數量" << endl;
		iow << endl;
		for(int i = 0; i < Goods.size(); i++){
			iow << setw(5) << Goods[i].getGoodname() << setw(20) << Goods[i].getPrice() << setw(20) << Goods[i].getCount() << endl; 
		}
		iow.close();
		Goods.clear(); //清除iof.eof == true 
		return;
	}
	cout << "----------------進入購物介面----------------" << endl; 
	int choice;
	iof.close();
	while((choice = afterLoginMenu()) != ENDEND){
		switch(choice){
			case PURCHASE: 
				purchase(BuyList, Goods);
				break;
			case RETURNGOOD: 
				returngood(BuyList, Goods);
				break;
			case CHECKOUT:
				checkout(BuyList, log);
				iof.open("產品資料更新.data", ios::out | ios::binary);
				if(!iof){
					cerr << "檔案無法開啟" << endl;
					exit(1);
				}
				iof.seekp(0);
				for(int i = 0; i < Goods.size(); i++){
					iof.write(reinterpret_cast<char*>(&Goods[i]), sizeof(Good));
				}
				iof.close();
				iof.open("產品資料.txt", ios::out);
				if(!iof){
					cerr << "檔案無法開啟" << endl;
					exit(1); 
				}
				iof << setw(5) << "產品名稱" << setw(20) << "產品價格" << setw(20) << "產品數量" << endl;
				iof << endl;
				for(int i = 0; i < Goods.size(); i++){
					iof << setw(5) << Goods[i].getGoodname() << setw(20) << Goods[i].getPrice() << setw(20) << Goods[i].getCount() << endl; 
				}
				iof.close();
				return;
			default: break;
		}
	}
}

void purchase(vector<Good> &BuyList, vector<Good> &Goods){
	Good tmpBuy;
	int sum = 0,buy = 1;
	bool getGood = false, getBuy = false;
	string pname;
	int pnumber;
	while(buy==1){
		cout << "請輸入要購買的商品名稱及數量" << endl;
		for(int i = 0; i < Goods.size(); i++){ //列出現有物品 
			cout << i + 1 << ". " << Goods[i].getGoodname() << "\t" << Goods[i].getPrice() << "\t" << Goods[i].getCount() << endl;
		}
		cin >> pname; 
		for (int i = 0; i < Goods.size(); i++){
			if (Goods[i].getGoodname() == pname){   //有此貨  就給買 
				getGood = true;
				cout << "請問需要購買多少此產品" << endl;
				cin >> pnumber;
				if((Goods[i].getCount() - pnumber) < 0){
					cout << "很抱歉, 庫存不足, 目前商品數量只剩" << Goods[i].getCount() << "個" << endl; 
				}
				else{
					Goods[i].setCount(Goods[i].getCount()-pnumber);
					for(int j = 0; j < BuyList.size(); j++){
						if(BuyList[j].getGoodname() == pname){
							tmpBuy.allSet(Goods[i].getGoodname(), Goods[i].getPrice(), BuyList[j].getCount() + pnumber);
							BuyList[j] = tmpBuy;
							getBuy = true;
						}
					}
					if(getBuy == false){
						tmpBuy.allSet(Goods[i].getGoodname(), Goods[i].getPrice(), pnumber);
						BuyList.push_back(tmpBuy);
					}
					getBuy == false;
				}
			}
		}
		if(getGood == false){
			cout << "抱歉查無此貨" <<endl; 
		}
		cout << "是否還需要購買(1.Yes,2.No)" <<endl;
		cin >> buy; 
	}
}

void returngood(vector<Good> &BuyList, vector<Good> &Goods){
	Good tmpGood;
	int ret = 1;
	string pname;
	int pnumber;
	bool getBuy = false;
	while(ret == 1){
		cout << "請輸入要退貨的商品名稱" << endl;
		for(int i = 0; i < BuyList.size(); i++){
				cout << i + 1 << ". " << BuyList[i].getGoodname() << "\t" << BuyList[i].getPrice() << "\t" << BuyList[i].getCount() << endl;
		}
		cin >> pname;
		for(int i = 0; i < BuyList.size(); i++){
			if(BuyList[i].getGoodname() == pname){
				getBuy = true;
				cout << "請輸入要退貨的數量" << endl;
				cin >> pnumber;
				if((BuyList[i].getCount() - pnumber) < 0){
					cout << "很抱歉,您的購買清單內沒有足夠的商品可退,數量只剩" << BuyList[i].getCount() << "個" << endl; 
				}
				else{
					if((BuyList[i].getCount() - pnumber) == 0){
						BuyList.erase(BuyList.begin()+i);
					}
					else{
						BuyList[i].setCount(BuyList[i].getCount() - pnumber);
						for(int j = 0; j < Goods.size(); j++){
							if(Goods[j].getGoodname() == pname){
								Goods[j].setCount(Goods[j].getCount() + pnumber);
							}
						}
					}
					cout << "此物品已退貨完成" << endl; 
				}
			}
		}
		if(getBuy == false){
			cout << "抱歉, 購買清單內無此貨" <<endl; 
		}
		cout << "是否還需要退貨(1.Yes,2.No)" <<endl;
		cin >> ret; 
	} 
}

void checkout(vector<Good> & BuyList, Member log){
	int balance = 0;
	int pos=0;
	Member tmpMem;
	cout << "你所要購買的商品如下: " << endl;
	for(int i = 0; i < BuyList.size(); i++){
		cout << i + 1 << ". " << BuyList[i].getGoodname() << "\t" << BuyList[i].getPrice() << "\t" << BuyList[i].getCount() << endl;
		balance += BuyList[i].getPrice() * BuyList[i].getCount();
	}
	cout << "總金額為 :" << balance << endl;
	cout << "商品一但售出, 不得退貨" << endl;
	
	fstream iof("成員更新.data", ios::in | ios::out | ios::binary);
	if(!iof){
		cerr << "開啟檔案失敗" << endl;
		exit(1); 
	}
	iof.seekg(0);
	iof.read(reinterpret_cast<char*>(&tmpMem), sizeof(Member));
	while (!iof.eof()){
		if (tmpMem.getName() == log.getName()){
			log.setBalance(log.getBalance() + balance);
			break;
		}
		pos++;
		iof.read(reinterpret_cast<char*>(&tmpMem), sizeof(Member));
	}
	iof.clear();
	iof.seekp(pos*sizeof(Member));
	iof.write(reinterpret_cast<char*>(&log), sizeof(Member));
	iof.close();
}

int Boss_menu(){
	int choice;
	cout << "請選擇: " << endl;
	cout << "1. 進貨" << endl;
	cout << "2. 下架產品" << endl;
	cout << "3. 新增產品" << endl;
	cout << "4. 列印庫存" << endl;
	cout << "5. 列出成員資料" << endl; 
	cout << "6. 退出" << endl;
	cin >> choice;
	return choice;
}
enum Choicesboss {NEW = 3, PRINT, MEMBERBOSS, ENDENDEND};
void Boss(vector<Good> &Goods){
	string name; //品名
	double price; //價格 
	int count; //數量
	int choice;
	int btmp; //算在檔案中第幾個位置 
	fstream iof;
	Good tmpGood;
	Member tmpMember;
	
	while ((choice = Boss_menu()) != ENDENDEND){
		bool getGood = false; //確認有沒有此貨 
		switch (choice){
		case 1://進貨
			cout << "老闆您需要進貨什麼產品" << endl;
			cin >> name;
			for (int i = 0; i < Goods.size(); i++){
				if (Goods[i].getGoodname() == name){   //有此貨  就進貨
					cout << "請問需要進多少此產品" << endl;
					cin >> count;
					Goods[i].setCount(Goods[i].getCount() + count); //增加產品數量 
					getGood = true;
				}
			}
			if (getGood == false){ //沒此貨
				cout << "很抱歉查無此貨" << endl;
			}
			break;
		case 2://下架 
			cout << "老闆您需要下架什麼產品" << endl;
			cin >> name;
			for (int i = 0; i < Goods.size(); i++){
				if (Goods[i].getGoodname() == name){   //有此貨  就退貨
					btmp = i;
					getGood = true; 
					Goods.erase( Goods.begin() + btmp );  //擦除那行
				}
			}
			if (getGood == false){ //沒此貨
				cout << "很抱歉查無此貨" << endl;
			}
			break;
		case 3://新增產品
			cout << "老闆您需要新增什麼產品" << endl;
			cin >> name;
			for (int i = 0; i < Goods.size(); i++){
				if (Goods[i].getGoodname() == name){   //有此貨 不新增
					cout << "已有此貨物了" << endl;
					getGood = true;
				}
			}
			if (getGood == false){ //沒此貨  就新增
				cout << "請輸入新產品的價格" << endl;
				cin >> price;
				Good gtmp(name, price, 300);
				Goods.push_back(gtmp); //在尾巴新增 
			}
			break;
		case 4: //列印庫存
			cout << setw(5) << "產品名稱" << setw(20) << "產品價格" << setw(20) << "存貨" << endl;  
			for(int i = 0; i < Goods.size(); i++){
				cout << setw(5) << Goods[i].getGoodname() << setw(20) << Goods[i].getPrice() << setw(20) << Goods[i].getCount() << endl;
			}
			break;
		case 5: //列出成員資料(包含消費總金額)
			 iof.open("成員更新.data", ios::in | ios::binary);
			 if(!iof){
				cerr << "檔案無法開啟" << endl;
				exit(1); 
			 }
			 cout << setw(5) << "編號" << setw(15) << "帳號" << setw(15) << "密碼" << setw(15) << "姓名" << setw(15) << "金額" << endl;
			 iof.seekg(0);
			 iof.read(reinterpret_cast<char*>(&tmpMember), sizeof(Member));
			 while(!iof.eof()){
			 	cout << setw(5) << tmpMember.getNumber() << setw(15) << tmpMember.getAccount() << setw(15) << tmpMember.getPassword() << setw(15) << tmpMember.getName() << setw(15) << tmpMember.getBalance() << endl;
			 	iof.read(reinterpret_cast<char*>(&tmpMember), sizeof(Member));
			 }
			 iof.close(); 
			 break;
		default:
			cout << "輸入錯誤" << endl;
			break;
		}
	}
}
