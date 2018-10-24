#include <iostream>
#include <utility>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <ctime>
#include <functional>
using namespace std;

vector<int> greedyOne(vector<pair<int, int>> vecs, int cap){

	vector<pair<float,int>> arr={};
	float ratio;
	int i;
	for ( i=0; i<vecs.size(); i++){
		ratio=(float)vecs[i].first/vecs[i].second;
		arr.push_back(make_pair(ratio, i));
	}
	sort(arr.rbegin(), arr.rend());
	int curr=0;
	int max_profit=0;
	for (auto x : arr){
		if ((curr + vecs[x.second].first) <= cap){
			curr+=vecs[x.second].first;
			max_profit+=vecs[x.second].second;
		}
		else{
		break;
		}
	}
	cerr << vecs.size() << endl;
	cerr << max_profit << endl;
	vector<int> retVal={i};
	retVal.push_back(max_profit);
	return retVal;


}

vector<int> greedyTwo(vector<pair<int, int>> vecs, int cap){
	return {};
}
vector<int> knapSack(vector<pair<int, int>> vecs, int cap){
	return {};
}

void read_plf(string namers, int arg){
	ifstream filen;
	filen.open(namers);
	if (filen.is_open()==false){
		cerr << " file does not exist " << endl;
	}
	vector<pair<int, int>> vecs;
	int first, cap, price;
	int weight;
	filen >> first >> cap;
	int i=1;
	//vector<pair<int, int>> eval;
	while(!filen.eof()){
		if(i<=first){
			filen >>  weight >> price;
			pair<int, int> element=make_pair(weight,price);
			vecs.push_back(element);
		}
		else{
			if (arg==0){
				greedyOne(vecs, cap);
			}
			else if(arg==1){
				greedyTwo(vecs, cap);
			}
			else if(arg==2){
				knapSack(vecs, cap);
			}
			vecs={};
			i=0;
			filen >> first >> cap;
		}
		i++;
	}
	filen.close();
}
int main(int argc, char* argv[]){
	
	read_plf(argv[1], stoi(argv[2]));

}
