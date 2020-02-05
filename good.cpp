#include "good.h"

Good::Good(string g, double p, int c){
	allSet(g, p, c);
}

void Good::allSet(string g, double p, int c){
	for (int i = 0; i < g.size(); i++){
		goodname[i] = g[i];
	} 
	goodname[g.size()] = '\0';
	price = p;
	count = c;
}

void Good::setCount(int c){
	count = c;
}

string Good::getGoodname(){
	return goodname;
}

double Good::getPrice(){
	return price;
}

int Good::getCount(){
	return count;
}
