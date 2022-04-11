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
            map<int,int> order;
            while(true)
            {
                cout<<"Description\tID\tQuantity\tPrice\n";
                for(int i=0;i<9;i++)
                {
                    cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                }
                cout<<"\n\nEnter Item ID and Quantity for each item you want to purchase.\nWhen done please enter -1.\n\n";
                int itemCode=0,quantity=0;
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
                            cout << "Quantity you wish to purchase exceeds quantity in Vending Machine.\nQuantity Available: "<<items[itemCode-1].second.second.first<<endl;
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
                    cout << "\nYour order is below.\nDescription\tItem ID \tQuantity\n";
                    map<int, int>::iterator itr;
                    for(itr=order.begin();itr!=order.end();++itr)
                        cout << items[itr->first-1].first << "\t\t" << itr->first << "\t\t" << itr->second << endl;
                    int confirm=-2;
                    cout << "Please confirm your order. Enter 1 to confirm, 0 to redo the order or -1 to exit." << endl;
                    cin >> confirm;
                    //if (confirm==1)
                       // break;
                    if(confirm==-1)
                        return 0;
                    else if(confirm==0)
                    {
                        order.clear();
                        continue;
                    }
                    int cost=0;
                    for(itr=order.begin();itr!=order.end();++itr)
                    {
                        items[itr->first-1].second.second.first=items[itr->first-1].second.second.first-itr->second;
                        cost=cost+itr->second*items[itr->first-1].second.second.second;
                    }
                    cout << "\nFinal Price to Pay: " << cost << endl;
                    cout << "\nThe machine accepts only certain denominations.\nPlease enter number of notes of each denomination you wish to pay with.";
                    int amt=0;
                    map<int,int> pay;
                    while(true)
                    {
                        for(itr=money.begin();itr!=money.end();++itr)
                        {
                            cout << "Enter the number of notes of the denomination Rs." << itr->first << endl;
                            cin >> amt;
                            pay.insert(pair<int,int>(itr->first,amt));
                        }
                        amt=0;
                        for(itr=pay.begin();itr!=pay.end();++itr)
                        {
                            amt=amt+itr->first*itr->second;
                        }
                        if(amt<cost)
                        {
                            cout << "Full amount not paid\n"; 
                            continue;
                        }
                        else
                        {
                            for(itr=pay.begin();itr!=pay.end();++itr)
                            {
                                money.insert(pair<int,int>(itr->first,itr->second+money.find(itr->first)->second));
                            }
                            break;
                        }
                    }
                    if(amt>cost)
                    {
                        int chng=amt-cost;
                        map<int,int> change;
                        for(itr=money.end();itr!=money.begin();--itr)
                        {
                            if((int)(chng/itr->first)!=0 && (int)(chng/itr->first)<=itr->second)
                            {
                                change.insert(pair<int,int>(itr->first,(int)(chng/itr->first)));
                                chng=chng-((int)((chng/itr->first)))*itr->first;
                            }
                            else if((int)(chng/itr->first)!=0 && (int)(chng/itr->first)>itr->second)
                            {
                                change.insert(pair<int,int>(itr->first,itr->second));
                                chng=chng-(itr->first)*(itr->second);
                            }
                        }
                        cout << "\n Please accept your change.\nDenomination\tNumber of Notes\n";
                        for(itr=change.begin();itr!=change.end();++itr)
                        {
                            cout << itr->first << "\t\t" << itr->second << endl;
                        }
                        cout << "\nThank you for using the Vending Machine.\n";
                        break;
                    }
                    else
                    {
                        cout << "Payment Accepted.\nThank you for using the Vending Machine.\n";
                        return 0;
                    }
                }
                else
                    break;
            }
            
    }

    return 0;
}