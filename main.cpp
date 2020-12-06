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
#include <chrono>
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

        auto start = std::chrono::high_resolution_clock::now();
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
        auto stop = std::chrono::high_resolution_clock::now();

        if(graph.begin()==graph.end()){
            cout<< "No results found. Please try again."<< endl;
        }
        else{
            auto time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
            cout << "Data Structure: Map" << endl;
            cout << "Time taken: " << time << " microseconds." << endl;
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


        start = std::chrono::high_resolution_clock::now();
        priority_queue <Business, vector<Business>, comparator> pq;
        for (int i = 0; i < allBusinesses.size(); i++) {
            if (allBusinesses[i].city == input && allBusinesses[i].rating>=realRating) {
                for(int j=0;j<allBusinesses[i].categories.size();j++){
                    if(allBusinesses[i].categories[j]==business){
                        string businessName = allBusinesses[i].name;
                        int businessRating = allBusinesses[i].rating;
                        /*   if(allBusinesses[i].rating==5){
                               vect5.push_back(allBusinesses[i]);
                           }
                           if(allBusinesses[i].rating==4){
                               vect4.push_back(allBusinesses[i]);
                           }*/
                        pq.push(allBusinesses[i]);
                    }
                }
            }
        }
        stop = std::chrono::high_resolution_clock::now();

        vector<Business> vect5;
        vector<Business> vect4;
        vector<Business> vect3;
        vector<Business> vect2;
        vector<Business> vect1;
        int numberOfBusinesses = 0;
        if(pq.empty()!=true) {
            cout << "Data Structure: Priority Queue" << endl;
            auto time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
            cout << "Time taken: " << time << " microseconds." << endl;

            while (pq.empty() == false && numberOfBusinesses<25) {
/*        string stars;
        string blankStars;
        if (pq.top().rating == 1) {
            stars = "★";
            blankStars = "☆☆☆☆";
        } else if (pq.top().rating == 2) {
            stars = "★★";
            blankStars = "☆☆☆";
        }
        if (pq.top().rating == 3) {
            stars = "★★★";
            blankStars = "☆☆";
        }
        if (pq.top().rating == 4) {
            stars = "★★★★";
            blankStars = "☆";
        }
        if (pq.top().rating == 5) {
            stars = "★★★★★";
            blankStars = "";
        }*/

                if (pq.top().rating == 5) {
                    vect5.push_back(pq.top());
                } else if (pq.top().rating == 4) {
                    vect4.push_back(pq.top());
                } else if (pq.top().rating == 3) {
                    vect3.push_back(pq.top());
                } else if (pq.top().rating == 2) {
                    vect2.push_back(pq.top());
                } else if (pq.top().rating == 1) {
                    vect1.push_back(pq.top());
                }
                pq.pop();
                numberOfBusinesses++;
            }
        }
        /*  cout<<"Name: "<< pq.top().name << endl;
          cout<<"Rating: "<< stars + blankStars << endl;
          cout<<"Number of Reviews: "<<pq.top().reviewCount << endl;
          cout << " " << endl;*/

        // std::sort(vect5.begin()->reviewCount, vect5.end()->reviewCount);
        if (vect5.empty() == false) {
            std::sort(vect5.begin(),
                      vect5.end(),
                      [](const Business &lhs, const Business &rhs) {
                          return lhs.reviewCount > rhs.reviewCount;
                      }
            );
        }

        if (vect4.empty() == false) {
            std::sort(vect4.begin(), vect4.end(), [](const Business &lhs, const Business &rhs) {
                return lhs.reviewCount > rhs.reviewCount;
            });
        }

        if (vect3.empty() == false) {
            std::sort(vect3.begin(),
                      vect3.end(),
                      [](const Business &lhs, const Business &rhs) {
                          return lhs.reviewCount > rhs.reviewCount;
                      }
            );
        }

        if (vect2.empty() == false) {
            std::sort(vect2.begin(),
                      vect2.end(),
                      [](const Business &lhs, const Business &rhs) {
                          return lhs.reviewCount > rhs.reviewCount;
                      }
            );
        }

        if (vect1.empty() == false) {
            std::sort(vect1.begin(),
                      vect1.end(),
                      [](const Business &lhs, const Business &rhs) {
                          return lhs.reviewCount > rhs.reviewCount;
                      }
            );
        }

        int j =0;
        int k=0;
        int l = 0;
        int m=0;
        int n=0;

        for (int i = 0; i < numberOfBusinesses; i++) {


            if (j<vect5.size()) {
                cout << "Name: " << vect5[j].name << endl;

                string stars;
                string blankStars;
                if (vect5[j].rating == 1) {
                    stars = "★";
                    blankStars = "☆☆☆☆";
                } else if (vect5[j].rating == 2) {
                    stars = "★★";
                    blankStars = "☆☆☆";
                }
                if (vect5[j].rating == 3) {
                    stars = "★★★";
                    blankStars = "☆☆";
                }
                if (vect5[j].rating == 4) {
                    stars = "★★★★";
                    blankStars = "☆";
                }
                if (vect5[j].rating == 5) {
                    stars = "★★★★★";
                    blankStars = "";
                }
                cout << "Rating: " << stars << blankStars << endl;
                cout << "Number of Reviews: " << vect5[j].reviewCount << endl;
                cout << " " << endl;
                j++;
            } else if (k<vect4.size()) {
                cout << "Name: " << vect4[k].name << endl;

                string stars;
                string blankStars;
                if (vect4[k].rating == 1) {
                    stars = "★";
                    blankStars = "☆☆☆☆";
                } else if (vect4[k].rating == 2) {
                    stars = "★★";
                    blankStars = "☆☆☆";
                }
                if (vect4[k].rating == 3) {
                    stars = "★★★";
                    blankStars = "☆☆";
                }
                if (vect4[k].rating == 4) {
                    stars = "★★★★";
                    blankStars = "☆";
                }
                if (vect4[k].rating == 5) {
                    stars = "★★★★★";
                    blankStars = "";
                }

                cout << "Rating: " << stars << blankStars << endl;
                cout << "Number of Reviews: " << vect4[k].reviewCount << endl;
                cout << " " << endl;
                k++;
            } else if (l<vect3.size()) {
                cout << "Name: " << vect3[l].name << endl;

                string stars;
                string blankStars;
                if (vect3[l].rating == 1) {
                    stars = "★";
                    blankStars = "☆☆☆☆";
                } else if (vect3[l].rating == 2) {
                    stars = "★★";
                    blankStars = "☆☆☆";
                }
                if (vect3[l].rating == 3) {
                    stars = "★★★";
                    blankStars = "☆☆";
                }
                if (vect3[l].rating == 4) {
                    stars = "★★★★";
                    blankStars = "☆";
                }
                if (vect3[l].rating == 5) {
                    stars = "★★★★★";
                    blankStars = "";
                }
                cout << "Rating: " << stars << blankStars << endl;
                cout << "Number of Reviews: " << vect3[l].reviewCount << endl;
                cout << " " << endl;
                l++;
            } else if (m<vect2.size()) {
                cout << "Name: " << vect2[m].name << endl;

                string stars;
                string blankStars;
                if (vect2[m].rating == 1) {
                    stars = "★";
                    blankStars = "☆☆☆☆";
                } else if (vect2[m].rating == 2) {
                    stars = "★★";
                    blankStars = "☆☆☆";
                }
                if (vect2[m].rating == 3) {
                    stars = "★★★";
                    blankStars = "☆☆";
                }
                if (vect2[m].rating == 4) {
                    stars = "★★★★";
                    blankStars = "☆";
                }
                if (vect2[m].rating == 5) {
                    stars = "★★★★★";
                    blankStars = "";
                }
                cout << "Rating: " << stars << blankStars << endl;
                //cout << "Rating: " << vect2[m].rating << endl;
                cout << "Number of Reviews: " << vect2[m].reviewCount << endl;
                cout << " " << endl;
                m++;
            } else if (n<vect1.size()) {
                cout << "Name: " << vect1[n].name << endl;

                string stars;
                string blankStars;
                if (vect1[n].rating == 1) {
                    stars = "★";
                    blankStars = "☆☆☆☆";
                } else if (vect1[n].rating == 2) {
                    stars = "★★";
                    blankStars = "☆☆☆";
                }
                if (vect1[n].rating == 3) {
                    stars = "★★★";
                    blankStars = "☆☆";
                }
                if (vect1[n].rating == 4) {
                    stars = "★★★★";
                    blankStars = "☆";
                }
                if (vect1[n].rating == 5) {
                    stars = "★★★★★";
                    blankStars = "";
                }
                cout << "Rating: " << stars << blankStars << endl;

                // cout << "Rating: " << vect1[n].rating << endl;
                cout << "Number of Reviews: " << vect1[n].reviewCount << endl;
                cout << " " << endl;
                n++;
            }

        }
        //     }

        //    pq.pop();


    }while(run==true);





}