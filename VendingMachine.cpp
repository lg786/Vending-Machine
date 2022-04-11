#include <iostream>
#include <bits/stdc++.h>
#include <map>
using namespace std;

int main()
{

    vector <pair<string,pair<int,pair<int,int>>>> items={
        {"Lays",{1,{10,20}}},{"Kurkure",{2,{10,10}}},{"Cheetos",{3,{10,15}}},
        {"Hershey",{4,{10,100}}},{"Kitkat",{5,{10,30}}},{"Mars",{6,{10,5}}},
        {"Coke",{7,{10,35}}},{"Sting",{8,{10,25}}},{"Appy",{9,{10,80}}}
    };

    int choice;
    map<int,int> money;
    money.insert(pair<int, int>(5,10));
    money.insert(pair<int, int>(10,10));
    money.insert(pair<int, int>(20,10));
    money.insert(pair<int, int>(50,10));
    money.insert(pair<int, int>(100,10));

    cout << "Enter choice:\n1) Buy Items \n2) Refill Items \n3) Refill Money\n";
    cin >> choice;

    switch (choice)
    {
        case 1:
            while(true)
            {
                cout<<"Description\tID\tQuantity\tPrice\n";
                for(int i=0;i<9;i++)
                {
                    cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                }
                cout<<"\n\nEnter Item ID and Quantity for each item you want to purchase.\nWhen done please enter -1.\n\n";
                int itemCode=0,quantity=0;
                map<int,int> order;
                while(true)
                {
                    cin >> itemCode;
                    if(itemCode==-1)
                        break;
                    else if(order.find(itemCode)!=order.end())
                    {
                        cout<<"This item has already been purchased.\n";
                    }
                    else if(itemCode>=1 && itemCode<=9)
                    {
                        cin >> quantity;
                        if(quantity>items[itemCode-1].second.second.first)
                        {
                            cout << "Quantity you wish to purchase exceeds quantity in Vending Machine.\n Quantity Available: "<<items[itemCode-1].second.second.first<<endl;
                            cout << "If you wish to change your amount please re-enter the quantity else if you do not want to buy this item enter -1\n";
                            cin >> quantity;
                            if(quantity==-1)
                                continue;
                            else
                                order.insert(pair<int,int>(itemCode,quantity));
                        }
                        else
                            order.insert(pair<int,int>(itemCode,quantity));
                    }
                    else
                        cout << "Invalid Item ID\n";
                }
                if(order.empty()==false)
                {
                    cout << "Your order is below.\nItem ID \tQuantity\n";
                    map<int, int>::iterator itr;
                    for(itr=order.begin();itr!=order.end();++itr)
                        cout << itr->first << "\t\t" << itr->second << endl;
                    int confirm=-2;
                    cout << "Please confirm your order. Enter 1 to confirm, 0 to redo the order or -1 to exit." << endl;
                    cin >> confirm;
                    if (confirm==1)
                        break;
                    else if(confirm==-1)
                        return 0;
                    else if(confirm==0)
                        continue;
                }
                else
                    break;
            }
    }

    return 0;
}