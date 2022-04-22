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

    int choice=0;
    map<int,int> money;
    money.insert(pair<int, int>(5,10));
    money.insert(pair<int, int>(10,10));
    money.insert(pair<int, int>(20,10));
    money.insert(pair<int, int>(50,10));
    money.insert(pair<int, int>(100,10));

    while(choice!=7)
    {
        cout << "\nEnter choice:\n1) Buy Items \n2) Refill Items \n3) Refill Money\n4) Add denominations\n5) Delete Items\n6) Add Items\n7) Exit\n";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
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
                        else
                        {
                            cin >> quantity;
                            if(order.find(itemCode)!=order.end())
                                cout<<"This item has already been purchased.\n";
                            else if(itemCode>=1 && itemCode<=9)
                            {
                                while(quantity>items[itemCode-1].second.second.first)
                                {
                                    cout << "Quantity you wish to purchase exceeds quantity in Vending Machine.\nQuantity Available: "<<items[itemCode-1].second.second.first<<endl;
                                    cout << "If you wish to change your amount please re-enter the quantity else if you do not want to buy this item enter -1\n";
                                    cin >> quantity;
                                }
                                if(quantity==-1)
                                    continue;                                
                                else
                                    order.insert(pair<int,int>(itemCode,quantity));
                            }
                            else
                                cout << "Invalid Item ID\n";
                        }
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
                        cout << "\nThe machine accepts only certain denominations.\nPlease enter number of notes of each denomination you wish to pay with.\n";
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
                                cout << "Full amount not paid.\nPayment Amount Remaining:" << (cost-amt) << "\nPlease take your money back and re-enter your payment amount.\n"; 
                                pay.clear();
                                continue;
                            }
                            else
                            {
                                for(itr=pay.begin();itr!=pay.end();++itr)
                                {
                                    map<int,int> :: iterator it = money.find(itr->first);
                                    it->second=it->second+itr->second;
                                }
                                break;
                            }
                        }
                        if(amt>cost)
                        {
                            int chng=amt-cost;
                            map<int,int> change;
                            for(auto itr=money.rbegin();itr!=money.rend();++itr)
                            {
                                if((int)(chng/itr->first)!=0 && (int)(chng/itr->first)<=itr->second)
                                {
                                    change.insert(pair<int,int>(itr->first,(int)(chng/itr->first)));
                                    map<int,int> :: iterator it = money.find(itr->first);
                                    it->second=it->second-(chng/itr->first);
                                    chng=chng-((int)((chng/itr->first)))*itr->first;
                                }
                                else if((int)(chng/itr->first)!=0 && (int)(chng/itr->first)>itr->second)
                                {
                                    change.insert(pair<int,int>(itr->first,itr->second));
                                    chng=chng-(itr->first)*(itr->second);
                                    itr->second=0;
                                }
                            }
                            if(chng==0)
                            {
                                cout << "\nPayment Accepted.\nPlease accept your change.\nDenomination\tNumber of Notes\n";
                                for(itr=change.begin();itr!=change.end();++itr)
                                {
                                    cout << itr->first << "\t\t" << itr->second << endl;
                                }
                                cout << "\nThank you for using the Vending Machine.\n";
                                break;
                            }
                            else
                            {
                                cout << "\nNot enough change in the machine.\nPlease take your money back.\nYour order has been cancelled.";
                                for(itr=pay.begin();itr!=pay.end();++itr)
                                {
                                    map<int,int> :: iterator it = money.find(itr->first);
                                    it->second=it->second-itr->second;
                                }
                                for(itr=order.begin();itr!=order.end();++itr)
                                {
                                    items[itr->first-1].second.second.first=items[itr->first-1].second.second.first+itr->second;
                                }
                                break;
                            }
                        }
                        else
                        {
                            cout << "Payment Accepted.\nNo change has to be returned.\nThank you for using the Vending Machine.\n";
                            break;
                        }
                    }
                    else
                        break;
                } 
            }
                break;
            case 2:
            {
                map<int,int> restock;
                while (true)
                {
                    cout << "Displaying the current stocks of items :\n";
                    for(int i=0;i<9;i++)
                    {
                        cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                    }
                    cout<<"Enter item ID of item you want to restock and quantity by which you want to restock\nWhen done please enter -1.\n\n";
                    int itemCode=0,restockQuantity=0;
                        while(true)
                        {
                            cin >> itemCode;
                            if(itemCode==-1)
                                break;
                            else
                            { 
                                cin >> restockQuantity;
                               if(itemCode>=1 && itemCode<=9)
                                {
                                    while((restockQuantity+items[itemCode-1].second.second.first)>10)
                                    {
                                        if(items[itemCode-1].second.second.first=10)
                                        {
                                            cout << "This item is at max capacity, cannot restock";
                                        }
                                        else
                                        { 
                                            cout << "Quantity you wish to restock exceeds the maximum capacity of the item chosen\n The maz capacity for the chosen item is 10. Current quantity: "<<items[itemCode-1].second.second.first<<endl;
                                            cout << "If you wish to change the quantity please re-enter the quantity or else enter -1\n";
                                            cin >> restockQuantity;
                                            if(restockQuantity==-1)
                                                   continue;
                                            else
                                                items[itemCode-1].second.second.first = items[itemCode-1].second.second.first + restockQuantity;
                                                restock.insert(pair<int,int>(itemCode,restockQuantity));
                                        }
                                    }
                                }
        
                                else
                                cout << "Invalid Item ID\n";
                            }
                        }
                
                    if(restock.empty()==false)
                    {
                        cout << "\nYour restock request is below.\nDescription\tItem ID \tQuantity\n";
                         map<int, int>::iterator itr;
                         for(itr=restock.begin();itr!=restock.end();++itr)
                        cout << items[itr->first-1].first << "\t\t" << itr->first << "\t\t" << itr->second << endl;
                        int confirm=-2;
                         cout << "Please confirm your order. Enter 1 to confirm, 0 to redo the order or -1 to exit." << endl;
                        cin  >> confirm;
                        
                        if(confirm==-1)
                            return 0;
                        else if(confirm==0)
                        {
                        restock.clear();
                            items[itemCode-1].second.second.first = items[itemCode-1].second.second.first - restockQuantity;
                            continue;
                        }
                        
                        cout << "\nThe updated stock is below.\nDescription\tItem ID \tQuantity\n";
                        
                        
                        for(int i=0;i<9;i++)
                        {
                            cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                        }
                       break;
                       cout << "Thank you for using the Vending Machine.\n";

                    }
                    else
                    break;

                }

            }
            break;
            case 3: 
            {
                cout << "Denominations\tNumber of Notes\n";
                map<int, int>::iterator itr;
                for(itr=money.begin();itr!=money.end();++itr)
                {
                    cout << itr->first << "\t\t" << itr->second << endl;;
                }
                cout << "\nThe machine accepts only certain denominations.\nPlease enter number of notes of each denomination you wish to add in the machine\n" << endl;
                int num=0;
                map<int, int>::iterator itr1;
                for(itr1=money.begin();itr1!=money.end();)
                {
                    cout << "The machine has " << itr1->second <<" notes of Rs." << itr1->first << endl;
                    int nons=(itr1->second>=10)? 0 : (10-itr1->second);
                    cout << "You can add " << nons << " notes." << endl;
                    cout << "Enter the number of notes you wish to add of the denomination Rs." << itr1->first << endl;
                    cin >> num;
                    if(num>nons)
                    {
                        cout << "The total number of notes exceeds the limit. Please re-enter appropriate amount.\n";
                    }
                    else
                    {
                        itr1->second+=num;
                        itr1++;
                    }
                }
                cout << "Denominations\tNumber of Notes\n";
                map<int, int>::iterator itr2;
                for(itr2=money.begin();itr2!=money.end();++itr2)
                {
                    cout << itr2->first << "\t\t" << itr2->second << endl;;
                }
                cout << "Thank You! Money Updated!";
            }
            break;
            case 4:
            {
                cout << "Current Denominations:\n";
                map<int,int>::iterator itr;
                for(itr=money.begin();itr!=money.end();++itr)
                {
                    cout << itr->first << endl;
                }
                cout << "Enter Denominations and Quantity you wish to add. Enter -1 when done.\n";
                map<int,int> den;
                while(true)
                {
                    int denomination=0,quantity=0,confirm = -2;
                    cin >> denomination;
                    if(denomination==-1)
                    {
                        if(den.empty()==false)
                        {
                            cout << "Denominations\tNumber of Notes\n";
                            for(itr=den.begin();itr!=den.end();++itr)
                            {
                                cout << itr->first << "\t\t" << itr->second << endl;
                            }
                            cout << "Enter 1 to confirm, 0 to exit and -1 to Re-enter.\n";
                            cin >> confirm;
                            if(confirm==-1)
                            {
                                den.clear();
                                continue;
                            }
                            /*else if(confirm==0)
                            {
                                break;
                            }*/
                            else if(confirm==1)
                            {
                               for(itr=den.begin();itr!=den.end();++itr)
                                {
                                    money.insert(pair<int,int>(itr->first,itr->second));
                                } 
                                cout << "Denominations have been added to machine.\n";
                                for(itr=money.begin();itr!=money.end();++itr)
                                {
                                    cout << itr->first << "\t\t" << itr->second << endl;
                                } 
                                break;
                            }
                        }
                    }
                    else
                    {
                        cin >> quantity;
                        bool check=false;
                        for(itr=money.begin();itr!=money.end();++itr)
                        {
                            if(denomination==itr->first)
                            {
                                cout << "The Vending Machine already has this denomination.\n";
                                check=true;
                                break;
                            }
                        }
                        while(quantity>10)
                        {
                            cout << "The maximum number of notes is 10.\nKindly re-enter quantity or -1 if you do not want to add this denomination.\n";
                            cin >> quantity;
                            if(quantity==-1)
                                break;
                        }
                        if(check==false && quantity>=0 && quantity<=10)
                            den.insert(pair<int,int>(denomination,quantity));
                    }
                }
            }
           
            break;
            case 5:
            {   
                cout << "Current items stock";
                for(int i=0;i<9;i++)
                {
                    cout<<items[i].first<<"\t\t"<<items[i].second.first<<endl;
                }
                cout << "Enter itemID of item you want to clear:\nEnter - 1 when done\n";
                vector<int> dlt;
                int itemCode=0;             
                while (true) 
                {
                    cin >> itemCode;
                    if(itemCode==-1)
                    {
                        if(dlt.empty()==false)
                        {
                            for(int i=0;i<9;i++)
                            {
                                cout<<"Items to be cleared\n";
                                cout<<dlt[i];
                            }   
                            int confirm=-2;
                            cout << "Enter 1 to confirm your action, 0 to redo and -1 to exit";
                            if(confirm==-1)
                            return 0;
                            else if(confirm==0)
                            {
                                dlt.clear();
                                continue;                             
                            }
                            
                            
                            for(auto it1=dlt.begin();it1!=dlt.end();++it1)
                            {
                                
                                for(auto it2=items.begin();it2!=items.end();it2++)
                                    {
                                        
                                        for(*it1==it2->second.first)
                                        {
                                            items.erase(it2);
                                        }


                                    }
                                
                            }
                        }
                        else
                        break;
                    }
                    else
                        {
                            if(itemCode>=1 && itemCode<=9)
                            {
                                dlt.push_back(itemCode);
                            }
                            else 
                            cout << "Invalid output\n";                        
                        }
                   
                }
            
            break;
            }     
        }
    }
    return 0;
}
