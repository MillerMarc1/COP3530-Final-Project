#include <iostream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;
int main() {
   ifstream file;
   string holder;
   string holder2;
   string holder3;
   //map<string,string>data;
    map<string, vector<pair<string, string>>> data;//our graph
   file.open("yelp_academic_dataset_business.json");
    getline(file,holder,'{');
    //int x=3;

   while(!file.eof()){

       getline(file,holder2,':');
       getline(file,holder3,',');
       data[holder].push_back(make_pair(holder2, holder3));
       //cout<<holder<<endl;
       //cout<<holder2<<endl;
   }
    for(auto it =data.begin();it!=data.end();++it) {
         if(it->first=="\"name\""){
             //cout<<it->second<<endl;
         }
    }


}
