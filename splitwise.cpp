//splitwise app

//#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

class comparator {
    public:
    bool operator () (pair<string,int> p1, pair<string,int> p2){
        return p1.second < p2.second;
    }
};

int main(){
    int transactions, friends;
    map <string, int> m; //maintaining net amount for all friends 

    cout<<"Enter number of friends : ";
    cin>>friends;
    cout<<"Enter total number of transactions : ";
    cin>>transactions;

    string x,y;
    int amount;
    cout<<"Please enter information for all the transactions according to prompts.\n";

    int i=1;
    while(transactions--){
        cout<<"Transaction-"<<i++<<endl;
        cout<<"Name of the person who has to pay : ";
        cin>>x;
        cout<<"Name of person who has to take the money : ";
        cin>>y;
        cout<<"Amount : ";
        cin>>amount;
        if(m.count(x)==0){
            m[x]=0;
        }
        if(m.count(y)==0){
            m[y]=0;
        }
        m[x] -= amount;
        m[y] += amount;
    }

    multiset < pair<string,int>, comparator > s;
    for(auto p : m){
        string person = p.first;
        int amount = p.second;
        if(m[person]!=0){
            s.insert(make_pair(person, amount));
        }
    }

    int total_trans = 0;
    cout<<"\n------------------------SOLUTION--------------------------\n";

    while(!s.empty()){
        auto start = s.begin();
        auto end = s.end();
        end--;
        string debit_person = start->first;
        int debit_amt = start->second;
        string credit_person = end->first;
        int credit_amt = end->second;
        s.erase(start);
        s.erase(end);
        int amount_settled = min(abs(debit_amt), abs(credit_amt));
        debit_amt += amount_settled;
        credit_amt -= amount_settled;
        total_trans++; // one successful transaction has been performed
        cout<<"Transaction-"<<total_trans<<" : \n";
        cout<<debit_person<<" should pay "<<amount_settled<<" to "<<credit_person<<".\n";
        if(debit_amt!=0){
            s.insert(make_pair(debit_person, debit_amt));
        }
        if(credit_amt!=0){
            s.insert(make_pair(credit_person, credit_amt));
        }
    }
    cout<<"\nTotal number of transactions will be: "<<total_trans<<".\n";

    return 0;
}