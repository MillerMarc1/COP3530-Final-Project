#include <iostream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;
//one of the catergories we have pre selected
class Business {
public:
    string name;
    string city;
    int rating;
    int reviewCount;
    vector<string> categories;



    // void importData();
    // void mostExpensive(vector<Business> vect);

};

class comparator{
public:
    bool operator()(const Business& var1, const Business& var2){
        return var1.rating < var2.rating;
    }
};

int main() {

    ifstream file;
    file.open("yelp_academic_dataset_business.json");
    string name;
    string city;
    string line;

    string star;
    string reviewCount;

    string restOfData;

    Business newBusiness;
    vector<Business> allBusinesses;


    string temp1;
    string temp2;
    int entries =0;


    while (getline(file, line)) {

        //create lego variable (lego.num = number ex.)

        stringstream data(line);
        getline(data, temp1, ':');
        getline(data, temp2, ':');
        getline(data, name, ',');

        string nameCropped = name.substr(1, name.size()-2);
        newBusiness.name = nameCropped;

        getline(data, temp1, ',');
        getline(data, temp2, ':');
        getline(data, city,',');

        string cityCropped = city.substr(1, city.size()-2);
        newBusiness.city = cityCropped;

        getline(data, temp1, ':');
        getline(data, temp1, ':');
        getline(data, temp1, ':');
        getline(data, temp1, ':');
        getline(data, temp1, ':');
        getline(data, star, ',');
        newBusiness.rating = stoi(star);

        getline(data, temp1, ':');
        getline(data, reviewCount, ',');
        newBusiness.reviewCount = stoi(reviewCount);

        getline(data, restOfData);
        string toLoad = restOfData.substr(restOfData.find("categories"));
        string categories = toLoad.substr(13,'\\');
        string categoryList = categories.substr(0, categories.find("\","));

        string toInsert = "";
        vector<string> catVector;
        for(int i=0; i<=categoryList.length(); i++){
            if(categoryList[i]==','|| i==categoryList.length()){
                if(toInsert == "Shopping" || toInsert == "Arts & Entertainment" || toInsert == "Gyms" || toInsert == "Desserts" || toInsert == "Health & Medical" || toInsert == "Salons" || toInsert == "Nightlife"|| toInsert == "Pets"){
                    catVector.push_back(toInsert);
                }
                if(toInsert == "Restaurant"||toInsert == "Restaurants"){
                    toInsert = "Restaurant";
                    catVector.push_back(toInsert);
                }
                toInsert = "";
                i++;
            }
            else if(categoryList[i]!=' ' && (categoryList[i+1]!='&' || categoryList[i+1]!='E' || categoryList[i+1]!='M')){
                toInsert = toInsert + categoryList[i];
            }
            else if(categoryList[i]==' '){
                toInsert = toInsert + categoryList[i];
            }
        }
        if(catVector.size()==0){
            catVector.push_back("Other");
        }
        newBusiness.categories = catVector;

        allBusinesses.push_back(newBusiness);

        entries++;

    }
    int count =0;
    bool run = true;
    do{
        cout << "------Yelper Helper------"<<endl;
if(count!=0){
    string test;
    getline(cin, test);
}
        cout << "What city are you in?" << endl;
        string input;
        cin.sync();
        getline(cin,input);
        cout << "What business type are you looking for" << endl;
        string business;
        getline(cin,business);
        cout<<"What is the minimum star rating you are looking for?"<<endl;
        string rating;
        cin>>rating;
        int realRating=stoi(rating);
count++;


        map<string, Business> graph;
        for (int i = 0; i < allBusinesses.size(); i++) {
            if (allBusinesses[i].city == input && allBusinesses[i].rating>=realRating) {
                for(int j=0;j<allBusinesses[i].categories.size();j++){
                    if(allBusinesses[i].categories[j]==business){
                        graph[allBusinesses[i].name]=allBusinesses[i];
                    }
                }

            }
        }
        if(graph.begin()==graph.end()){
           cout<< "No results found. Please try again."<< endl;
        }
        else{
            cout << "Data Structure: Map" << endl;
        }

        for(auto it =graph.begin();it!=graph.end();++it) {

            string stars;
            string blankStars;
            if(it->second.rating==1){
                stars = "★";
                blankStars= "☆☆☆☆";
            }
            else if(it->second.rating==2){
                stars = "★★";
                blankStars = "☆☆☆";
            }
            if(it->second.rating==3){
                stars = "★★★";
                blankStars = "☆☆";
            }
            if(it->second.rating==4){
                stars = "★★★★";
                blankStars= "☆";
            }
            if(it->second.rating==5){
                stars = "★★★★★";
                blankStars="";
            }

            cout<< "Name: " << it->first << endl;
            cout<<"Rating: "<<stars +blankStars<< endl;
            cout<<"Number of Reviews: "<<it->second.rating << endl;
            cout << " " << endl;

        }


        cout << endl << endl;


        priority_queue <Business, vector<Business>, comparator> pq;
        for (int i = 0; i < allBusinesses.size(); i++) {
            if (allBusinesses[i].city == input && allBusinesses[i].rating>=realRating) {
                for(int j=0;j<allBusinesses[i].categories.size();j++){
                    if(allBusinesses[i].categories[j]==business){
                        string businessName = allBusinesses[i].name;
                        int businessRating = allBusinesses[i].rating;
                        pq.push(allBusinesses[i]);
                    }
                }
            }
        }

if(pq.empty()!=true){
    cout << "Data Structure: Priority Queue" << endl;
}
     while (pq.empty() == false){
         string stars;
         string blankStars;
         if(pq.top().rating==1){
             stars = "★";
             blankStars= "☆☆☆☆";
         }
         else if(pq.top().rating==2){
             stars = "★★";
             blankStars= "☆☆☆";
         }
         if(pq.top().rating==3){
             stars = "★★★";
             blankStars="☆☆";
         }
         if(pq.top().rating==4){
             stars = "★★★★";
             blankStars="☆";
         }
         if(pq.top().rating==5){
             stars = "★★★★★";
             blankStars="";
         }

         cout<<"Name: "<< pq.top().name << endl;
         cout<<"Rating: "<< stars + blankStars << endl;
         cout<<"Number of Reviews: "<<pq.top().reviewCount << endl;
         cout << " " << endl;

            pq.pop();
        }


    }while(run==true);





}