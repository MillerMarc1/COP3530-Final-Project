/*#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
//one of the catergories we have pre selected
class Business {
public:
    string name;
    string city;
    int rating;
    int reviewCount;
    vector<string> categories;

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
    return 0;
}*/
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
    bool running = true;
    while(running==true){
        cout << "What city are you in?" << endl;
        string input;
        cin >> input;
        cout << "What business type are you looking for" << endl;
        string business;
        cin >> business;
        cout<<"What is the minimum star rating you are looking for?"<<endl;
        string rating;
        cin>>rating;
        int realRating=stoi(rating);
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
        auto iter = graph.begin();
        if(iter == graph.end()){
            cout << "No results found. Please try again" << endl;
            cout << " " << endl;
        }

        for(auto it =graph.begin();it!=graph.end();++it) {
            cout<<"Name: "<<it->first<<endl;
            cout << "Rating: " <<it->second.rating<< endl;
            cout <<"Number of Reviews: " << it->second.reviewCount << endl;
            cout<< " " << endl;

        }
    }




}