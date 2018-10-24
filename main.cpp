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

pair<pair<int, int> ,vector<pair<int, int>>> greedyOne(vector<pair<int, int>> vecs, int cap){

	vector<pair<int,int>> arr={};
	vector<pair<int, int>> ret_arr={};
	float ratio;
	int i;
	for ( i=0; i<vecs.size(); i++){
		ratio=(float)vecs[i].second/vecs[i].first;
		arr.push_back(make_pair(ratio, i));
	}
	sort(arr.rbegin(), arr.rend());
/*	for (auto x : arr){
			cerr << x.first << endl;
		}*/
	int curr=0;
	int max_profit=0;
	for (auto x : arr){
		/*if(curr > cap){
			break;
		}*/
		if ((curr + vecs[x.second].first) <= cap){
			curr+=vecs[x.second].first;
			max_profit+=vecs[x.second].second;
			ret_arr.push_back(vecs[x.second]);
		}
		else{
		break;
		}
		//if(curr>cap){
		//	break;
		//}
	}
//	cerr << vecs.size() << endl;
//	cerr << max_profit << endl;
	pair<pair<int, int>,vector<pair<int, int>>> retVal=make_pair(make_pair( i, (int)max_profit),arr);
	//etVal.push_back(max_profit);
	return retVal;


}

vector<int> greedyTwo(vector<pair<int, int>> vecs, int cap){
	int mp1=greedyOne(vecs, cap).first.second;
	int profit=0;
	for (auto x : vecs){
		if (x.first<=cap && x.second>profit){
			profit=x.second;
		}
	}
	if(profit<mp1){
		profit=mp1;
	}
	vector <int> retVal={vecs.size()};
	retVal.push_back(profit);
//	cerr << retVal[0] << " " << retVal[1] << endl;
	return retVal;
}
vector<int> knapSack(vector<pair<int, int>> vecs, int cap){
	return {};
}

void read_plf(string namers, int arg, string outs){
	ifstream filen;
	ofstream out;
	out.open(outs);
	filen.open(namers);
	if (filen.is_open()==false){
		cerr << " file does not exist " << endl;
	}
	vector<pair<int, int>> vecs;
	int first, cap, price;
	int weight;
	filen >> first >> cap;
	int i=1;
	vector<int> ret;
	pair<pair<int, int> ,vector<pair<int, int>>> ret1;
	//vector<pair<int, int>> eval;
	while(!filen.eof()){
		if(i<=first){
			filen >>  weight >> price;
			pair<int, int> element=make_pair(weight,price);
			vecs.push_back(element);
		}
		else{
			if (arg==0){
				ret1=greedyOne(vecs, cap);
				if(ret1.first.second!=0){
					out <<  ret1.first.first << " " << ret1.first.second<< endl;
				}
			}
			else if(arg==1){
				ret=greedyTwo(vecs, cap);
				if(ret[1]!=0){
                                        out <<  ret[0] << " " << ret [1] << endl;
                                }
			}
			else if(arg==2){
		
				ret=knapSack(vecs, cap);
				if(ret[1]!=0){
                                        out <<  ret[0] << " " << ret [1] << endl;
                                }
			}
			vecs={};
			i=0;
			filen >> first >> cap;
		}
		i++;
	}
	filen.close();
	out.close();
}
int main(int argc, char* argv[]){
//	cerr << argv[2] << endl;
	read_plf(argv[1], stoi(argv[3]), argv[2]);

}
