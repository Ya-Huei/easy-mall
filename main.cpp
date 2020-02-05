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
	cout << "�п��: " << endl; 
	cout << "1. �n�J" << endl;
	cout << "2. �ӽбb��" << endl;
	cout << "3. �R���b��" << endl;
	cout << "4. �h�X" << endl;
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
	ifstream ior("������s.data", ios::in | ios::binary);
	ofstream iow("��Ʀ���.txt", ios::out);
	iow << setw(5) << "�s��" << setw(15) << "�b��" << setw(15) << "�K�X" << setw(15) << "�m�W" << setw(15) << "���B" << endl;
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
	fstream iof("������s.data", ios::in | ios::out | ios::binary);
	if( !iof ){
		cerr << "�ɮ׵L�k�}��" << endl;
		exit(1); 
	}
	string acc, pas;
	cout << "�b�� :"; 
	cin >> acc;
	Member tmp, failtmp;//failtmp�Χ@�^�ǪŪ�Member 
	iof.seekg(0);
	iof.read(reinterpret_cast<char*>(&tmp), sizeof(Member));
	while(!iof.eof()){
		if(tmp.getAccount() == acc){
			cout << "�K�X :"; 
			cin >> pas;
			if(tmp.getPassword() == pas){
				if(tmp.getAccount() == "brownboss"){
					cout << "����  �z�^�ӤF" << endl;
					return tmp;
				}
				else{ 
					cout << "�w��A" <<endl;
					return tmp;
				}
			}
			else{
				cout << "�K�X���~" <<endl; 
				return failtmp;
			}
		}
		iof.read(reinterpret_cast<char*>(&tmp),sizeof(Member));
	}
	cout <<"�d�L���b��"<<endl;
	return failtmp; 
}

void newaccount(){
	fstream iof("������s.data", ios::in | ios::binary);
	if( !iof ){
		cerr << "�ɮ׵L�k�}��" << endl;
		exit(1); 
	}
	int num;
	string acc, pas, name;
	double bal;
	Member d, tmp;
	cout << "�п�J�b���B�K�X�Ωm�W: " << endl; 
	cin >> acc >> pas >> name;
	iof.seekg(0);
	iof.read(reinterpret_cast<char*>(&tmp), sizeof(Member));
	while(!iof.eof()){
		if(tmp.getAccount() == acc){
			cout << "���b���w�Q���U�L"<<endl;
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
	fstream iow("������s.data",ios::out | ios::app | ios::binary);
	if( !iow ){
		cerr << "�ɮ׵L�k�}��" << endl;
		exit(1); 
	}
	
	d.setAll(num, acc, pas, name);
	if(num > 1000 && num < 1101){
		iow.seekp(0, ios::end);
		iow.write( reinterpret_cast<char*>(&d), sizeof(Member));
	}
	cout <<"�b�����U����"<<endl;
	iow.close();
}

void deleteAccount(){
	fstream iof("������s.data", ios::in | ios::out | ios::binary);
	if( !iof ){
		cerr << "�ɮ׵L�k�}��" << endl;
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
		cerr << "��Ƥ��s�b" << endl;
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
	cout << "�п��: " << endl; 
	cout << "1. �ʶR" << endl;
	cout << "2. �h�f" << endl;
	cout << "3. ���b" << endl; 
	cout << "4. ���}" << endl;
	cout << "�Y�L���b�ӿ�����}, �ʶR�����N����" <<endl; 
	cin >> choice;
	return choice;
}

void afterlogin(Member log){
	fstream iof("���~��Ƨ�s.data", ios::in | ios::binary); //Ū 
	if(!iof){
		cerr << "�ɮ׵L�k�}��" << endl;
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
		cout << "----------------�i�J���󤶭�----------------" << endl;
		Boss(Goods);
		iof.close(); 
		fstream iow("���~��Ƨ�s.data", ios::out | ios::binary); //�g 
		if(!iow){
			cerr << "�ɮ׵L�k�}��" << endl;
			exit(1); 
		} 
		iow.seekp(0);
		for(int i = 0; i < Goods.size(); i++){
			tmpGood = Goods[i];
			iow.write(reinterpret_cast<char*>(&tmpGood), sizeof(Good));
			}
		iow.close();
		iow.open("���~���.txt", ios::out);
		if(!iow){
			cerr << "�ɮ׵L�k�}��" << endl;
			exit(1); 
		}
		iow << setw(5) << "���~�W��" << setw(20) << "���~����" << setw(20) << "���~�ƶq" << endl;
		iow << endl;
		for(int i = 0; i < Goods.size(); i++){
			iow << setw(5) << Goods[i].getGoodname() << setw(20) << Goods[i].getPrice() << setw(20) << Goods[i].getCount() << endl; 
		}
		iow.close();
		Goods.clear(); //�M��iof.eof == true 
		return;
	}
	cout << "----------------�i�J�ʪ�����----------------" << endl; 
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
				iof.open("���~��Ƨ�s.data", ios::out | ios::binary);
				if(!iof){
					cerr << "�ɮ׵L�k�}��" << endl;
					exit(1);
				}
				iof.seekp(0);
				for(int i = 0; i < Goods.size(); i++){
					iof.write(reinterpret_cast<char*>(&Goods[i]), sizeof(Good));
				}
				iof.close();
				iof.open("���~���.txt", ios::out);
				if(!iof){
					cerr << "�ɮ׵L�k�}��" << endl;
					exit(1); 
				}
				iof << setw(5) << "���~�W��" << setw(20) << "���~����" << setw(20) << "���~�ƶq" << endl;
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
		cout << "�п�J�n�ʶR���ӫ~�W�٤μƶq" << endl;
		for(int i = 0; i < Goods.size(); i++){ //�C�X�{�����~ 
			cout << i + 1 << ". " << Goods[i].getGoodname() << "\t" << Goods[i].getPrice() << "\t" << Goods[i].getCount() << endl;
		}
		cin >> pname; 
		for (int i = 0; i < Goods.size(); i++){
			if (Goods[i].getGoodname() == pname){   //�����f  �N���R 
				getGood = true;
				cout << "�аݻݭn�ʶR�h�֦����~" << endl;
				cin >> pnumber;
				if((Goods[i].getCount() - pnumber) < 0){
					cout << "�ܩ�p, �w�s����, �ثe�ӫ~�ƶq�u��" << Goods[i].getCount() << "��" << endl; 
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
			cout << "��p�d�L���f" <<endl; 
		}
		cout << "�O�_�ٻݭn�ʶR(1.Yes,2.No)" <<endl;
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
		cout << "�п�J�n�h�f���ӫ~�W��" << endl;
		for(int i = 0; i < BuyList.size(); i++){
				cout << i + 1 << ". " << BuyList[i].getGoodname() << "\t" << BuyList[i].getPrice() << "\t" << BuyList[i].getCount() << endl;
		}
		cin >> pname;
		for(int i = 0; i < BuyList.size(); i++){
			if(BuyList[i].getGoodname() == pname){
				getBuy = true;
				cout << "�п�J�n�h�f���ƶq" << endl;
				cin >> pnumber;
				if((BuyList[i].getCount() - pnumber) < 0){
					cout << "�ܩ�p,�z���ʶR�M�椺�S���������ӫ~�i�h,�ƶq�u��" << BuyList[i].getCount() << "��" << endl; 
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
					cout << "�����~�w�h�f����" << endl; 
				}
			}
		}
		if(getBuy == false){
			cout << "��p, �ʶR�M�椺�L���f" <<endl; 
		}
		cout << "�O�_�ٻݭn�h�f(1.Yes,2.No)" <<endl;
		cin >> ret; 
	} 
}

void checkout(vector<Good> & BuyList, Member log){
	int balance = 0;
	int pos=0;
	Member tmpMem;
	cout << "�A�ҭn�ʶR���ӫ~�p�U: " << endl;
	for(int i = 0; i < BuyList.size(); i++){
		cout << i + 1 << ". " << BuyList[i].getGoodname() << "\t" << BuyList[i].getPrice() << "\t" << BuyList[i].getCount() << endl;
		balance += BuyList[i].getPrice() * BuyList[i].getCount();
	}
	cout << "�`���B�� :" << balance << endl;
	cout << "�ӫ~�@����X, ���o�h�f" << endl;
	
	fstream iof("������s.data", ios::in | ios::out | ios::binary);
	if(!iof){
		cerr << "�}���ɮץ���" << endl;
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
	cout << "�п��: " << endl;
	cout << "1. �i�f" << endl;
	cout << "2. �U�[���~" << endl;
	cout << "3. �s�W���~" << endl;
	cout << "4. �C�L�w�s" << endl;
	cout << "5. �C�X�������" << endl; 
	cout << "6. �h�X" << endl;
	cin >> choice;
	return choice;
}
enum Choicesboss {NEW = 3, PRINT, MEMBERBOSS, ENDENDEND};
void Boss(vector<Good> &Goods){
	string name; //�~�W
	double price; //���� 
	int count; //�ƶq
	int choice;
	int btmp; //��b�ɮפ��ĴX�Ӧ�m 
	fstream iof;
	Good tmpGood;
	Member tmpMember;
	
	while ((choice = Boss_menu()) != ENDENDEND){
		bool getGood = false; //�T�{���S�����f 
		switch (choice){
		case 1://�i�f
			cout << "����z�ݭn�i�f���򲣫~" << endl;
			cin >> name;
			for (int i = 0; i < Goods.size(); i++){
				if (Goods[i].getGoodname() == name){   //�����f  �N�i�f
					cout << "�аݻݭn�i�h�֦����~" << endl;
					cin >> count;
					Goods[i].setCount(Goods[i].getCount() + count); //�W�[���~�ƶq 
					getGood = true;
				}
			}
			if (getGood == false){ //�S���f
				cout << "�ܩ�p�d�L���f" << endl;
			}
			break;
		case 2://�U�[ 
			cout << "����z�ݭn�U�[���򲣫~" << endl;
			cin >> name;
			for (int i = 0; i < Goods.size(); i++){
				if (Goods[i].getGoodname() == name){   //�����f  �N�h�f
					btmp = i;
					getGood = true; 
					Goods.erase( Goods.begin() + btmp );  //��������
				}
			}
			if (getGood == false){ //�S���f
				cout << "�ܩ�p�d�L���f" << endl;
			}
			break;
		case 3://�s�W���~
			cout << "����z�ݭn�s�W���򲣫~" << endl;
			cin >> name;
			for (int i = 0; i < Goods.size(); i++){
				if (Goods[i].getGoodname() == name){   //�����f ���s�W
					cout << "�w�����f���F" << endl;
					getGood = true;
				}
			}
			if (getGood == false){ //�S���f  �N�s�W
				cout << "�п�J�s���~������" << endl;
				cin >> price;
				Good gtmp(name, price, 300);
				Goods.push_back(gtmp); //�b���ڷs�W 
			}
			break;
		case 4: //�C�L�w�s
			cout << setw(5) << "���~�W��" << setw(20) << "���~����" << setw(20) << "�s�f" << endl;  
			for(int i = 0; i < Goods.size(); i++){
				cout << setw(5) << Goods[i].getGoodname() << setw(20) << Goods[i].getPrice() << setw(20) << Goods[i].getCount() << endl;
			}
			break;
		case 5: //�C�X�������(�]�t���O�`���B)
			 iof.open("������s.data", ios::in | ios::binary);
			 if(!iof){
				cerr << "�ɮ׵L�k�}��" << endl;
				exit(1); 
			 }
			 cout << setw(5) << "�s��" << setw(15) << "�b��" << setw(15) << "�K�X" << setw(15) << "�m�W" << setw(15) << "���B" << endl;
			 iof.seekg(0);
			 iof.read(reinterpret_cast<char*>(&tmpMember), sizeof(Member));
			 while(!iof.eof()){
			 	cout << setw(5) << tmpMember.getNumber() << setw(15) << tmpMember.getAccount() << setw(15) << tmpMember.getPassword() << setw(15) << tmpMember.getName() << setw(15) << tmpMember.getBalance() << endl;
			 	iof.read(reinterpret_cast<char*>(&tmpMember), sizeof(Member));
			 }
			 iof.close(); 
			 break;
		default:
			cout << "��J���~" << endl;
			break;
		}
	}
}
