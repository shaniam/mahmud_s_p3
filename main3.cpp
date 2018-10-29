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
#include <time.h>
using namespace std;


//int knapSack(int i, int profit, int weight, vector<pair<int, int>> arr , int cap);
//bool promising(int i, int weight, int profit, vector<pair<int, int>> arr, int cap, int n, int maxprofit );
//float kwf2( int i, int weight, int profit,  vector<pair<int, int>> arr, int cap, int n);
bool promising(int i, int weight, int profit, vector<pair<int, int>> arr, int cap, int n, int maxprofit);
float kwf2( int i, int weight, int profit,    vector<pair<int, int>> arr, int cap, int n);
int max_profit;

pair<pair<int, int> ,vector<pair<int, int>>> greedyOne(vector<pair<int, int>> vecs, int cap){

	vector<pair<int,int>> arr={};
	vector<pair<float, int>> ret_arr={};
	float ratio;
	int i;
	for ( i=0; i<vecs.size(); i++){
		ratio=(float)vecs[i].second/vecs[i].first;
		arr.push_back(make_pair(ratio, i));
	}
	sort(arr.rbegin(), arr.rend());
	int curr=0;
	int max_profit=0;
	for (auto x : arr){
		if ((curr + vecs[x.second].first) <= cap){
			curr+=vecs[x.second].first;
			max_profit+=vecs[x.second].second;
			ret_arr.push_back(vecs[x.second]);
		}
	}
	pair<pair<int, int>,vector<pair<int, int>>> retVal=make_pair(make_pair( i, (int)max_profit),arr);
	return retVal;


}

pair<pair<int, int> ,vector<pair<int, int>>> greedyTwo(vector<pair<int, int>> vecs, int cap){
	pair<pair<int, int>,vector<pair<int, int>>> g1=greedyOne(vecs, cap);
	int mp1= g1.first.second;
	vector<pair<int, int>> ma1= g1.second;
	vector<pair<int, int>> maxing={};
	int profit=0;
	for (auto x : vecs){
		if (x.first<=cap && x.second>profit){
			profit=x.second;
			maxing={x};
		}
	}
	//cerr << mp1 << endl;
	if(profit<mp1){
		profit=mp1;
	}
	else{
		ma1=maxing;
	}
	pair<pair<int, int>, vector<pair<int, int>>> retVal= make_pair(make_pair( (int) vecs.size(), (int) profit), ma1);
	return retVal;
}

int knapSack(int i, int profit, int weight, vector<pair<int, int>> arr , int cap, int& max_profit){
	//int max_profit;
	//if (i==-1){
	//	//cerr << "hello" << endl;
	//	max_profit=greedyTwo(arr, cap).first.second;
	//}
	if (weight <= cap && profit > max_profit){
		max_profit=profit;
		}
	if (promising(i, weight, profit, arr, cap, arr.size() , max_profit)){
		knapSack(i+1, profit+arr[i+1].second, (weight + arr[i+1].first) , arr, cap, max_profit);
		knapSack(i+1, profit, weight, arr, cap, max_profit);
		//cerr << "goodbye " << endl;
	}
//	cerr << max_profit << endl;
	return max_profit;
}
bool promising(int i, int weight, int profit, vector<pair<int, int>> arr, int cap, int n, int maxprofit ){
	if (weight >= cap) {return false;}
	//cerr << "hello" << endl;
	float bound = kwf2(i+1, weight, profit, arr, cap, arr.size());
	return (bound>maxprofit);
}

float kwf2( int i, int weight, int profit,  vector<pair<int, int>> arr, int cap, int n){
	float bound = profit;
	//vector<float> x={};
	/*for (int j=0; j<i; j++){
		x.push_back(0);
	}
	for (int j=i; j <n; j++){
		if (weight<=cap){
			x.push_back(0); 
		}
	}*/
	float frac;
	while ( (weight < cap ) && (i<n)){
		if(weight + (arr[i].first) <= cap){
			//x[i]=1;
			weight = weight +arr[i].first;
			bound = bound + arr[i].second;
		}
		else{
			frac=(float)(cap-weight)/(arr[i].first);
			weight = cap;
			bound = bound + (arr[i].second * frac);

		}

		i++;
	}
//	cerr << bound << endl;
	return bound;
}


void read_plf(string namers, int arg, string outs){
	ifstream filen;
	ofstream out;
	out.open(outs);
	filen.open(namers);
	if (filen.is_open()==false){
		cerr << " file does not exist " << endl;
		return;
	}
	vector<pair<int, int>> vecs;
	int first, cap, price;
	int weight;
	filen >> first >> cap;
	int i=1;
	vector<int> ret;
	clock_t begin;
	clock_t end;
	pair<pair<int, int> ,vector<pair<int, int>>> ret1;
	while(!filen.eof()){
		if(i<=first){
			filen >>  weight >> price;
			pair<int, int> element=make_pair(weight,price);
			vecs.push_back(element);
			i++;
		}
		else{
			if (arg==0){
				begin=clock();
				ret1=greedyOne(vecs, cap);
				end=clock();
				if(ret1.first.second!=0){
					out <<  ret1.first.first << " " << ret1.first.second << " " << (float) (1000 * end-begin) / CLOCKS_PER_SEC  << " ms" << endl;
				}
			}
			else if(arg==1){
				begin=clock();
				ret1=greedyTwo(vecs, cap);
                                end=clock();
				if(ret1.first.second!=0){
                                        out <<  ret1.first.first << " " << ret1.first.second << " " << (float)(1000 * end-begin) / CLOCKS_PER_SEC  << " ms" << endl;
                                }
			}
			else if(arg==2){
				begin = clock();
				vector<pair<int, int>> arr={};
				vector<pair<int, int>> other={};
        			float ratio;
        			int i;
				//begin= clock();
        			for ( i=0; i<vecs.size(); i++){
                			ratio=(float)vecs[i].second/vecs[i].first;
                			arr.push_back(make_pair(ratio, i));
        			}
        			sort(arr.rbegin(), arr.rend());
				for (auto x : arr){
					other.push_back(vecs[x.second]);
				}
				pair<pair<int, int>,vector<pair<int, int>>> g2=greedyTwo(vecs, cap);
				//end = clock();
				int best=knapSack(-1,0,0, other, cap, g2.first.second);
				end = clock();
				out << vecs.size() << " " << best << " " << (float) (1000 * end-begin) / CLOCKS_PER_SEC  << " ms" << endl;
			}
			vecs={};
			i=1;
			filen >> first >> cap;
		}
		//i++;
		/*if (i == first){
			vecs={};
                        i=1;
                        filen >> first >> cap;
		}*/
	}
	filen.close();
	out.close();
}
int main(int argc, char* argv[]){
//	cerr << argv[2] << endl;
	read_plf(argv[1], stoi(argv[3]), argv[2]);

}
