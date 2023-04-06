// ABDUL RIYAN
// CEO OF ORANGE INC.
// ICHIRAKU RAMEN BILL GENERATOR
// C++
// 05/04/2023


#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>
#include<fstream>
#include<chrono>
#include<ctime>
#include<dirent.h>
using namespace std;

struct Item {
    string name;
    double price;
};

void displayItemList(vector<Item>& itemList) {
    cout << "************************************************************" << endl;
    cout << "                            MENU                          " << endl;
    cout << "************************************************************" << endl;
    cout << "Here's a list of items available today:" << endl;
    cout << left << setw(10) << "Item No." << setw(20) << "Item Name" << setw(10) << "Price" << endl;
    cout << "------------------------------------------------------------" << endl;

    for (int i = 0; i < itemList.size(); i++) {
        cout << left << setw(10) << (i+1) << setw(20) << itemList[i].name << "Rs. " << itemList[i].price << endl;
    }

    cout << "------------------------------------------------------------" << endl;
}


void generateBill(vector<Item>& itemList, vector<int>& itemIndices, vector<int>& itemQuantities, string customerName, string date, string time) {
    
    
    auto now = chrono::system_clock::now();
    time_t timestamp = chrono::system_clock::to_time_t(now);

    stringstream ss;    
    string folderName = "Bills/";
    ss << put_time(localtime(&timestamp), "%Y-%m-%d_%H-%M-%S");
    string filename = folderName + "bill_" + customerName + "_" + ss.str() + ".txt";

    
    
    
    double Amount = 0,GST,TotalAmount;
    cout << "********************************* BILL **************************************" << endl;
    cout << left << setw(20) << "Item Name" << setw(10) << "      Price" << "          Quantity" <<"           "<< "Amount" <<endl;
    cout << "\n-----------------------------------------------------------------------------" << endl;
    
    for (int i = 0; i < itemIndices.size(); i++) {
        int index = itemIndices[i];
        int quantity = itemQuantities[i];
        cout << left << setw(20) << itemList[index].name << "   Rs. " << itemList[index].price <<"               "<< quantity << "                "<<itemList[index].price*quantity<<endl;
        Amount += round(itemList[index].price * quantity * 1000) / 1000;
        GST = 0.18*Amount;
        TotalAmount = GST + Amount;
    }

        cout << "\n-----------------------------------------------------------------------------"<<endl;
        cout << right << setw(20) << "                           Amount       : Rs. " << Amount << endl;
        cout << right << setw(20) << "                           GST          : Rs. " << GST << endl;
        cout << right << setw(20) << "                           Total Amount : Rs. " << TotalAmount << endl;
        cout << "*****************************************************************************" << endl;

    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile <<"                              ICHIRAKU RAMEN                                  ";
        outputFile << "\n\nCUSTOMER NAME : " << customerName << endl;
        outputFile << "DATE : " << date << endl;
        outputFile << "TIME : " << time << "\n\n";

        outputFile << "********************************* BILL **************************************" << endl;
        outputFile<< left << setw(20) << "Item Name" << setw(10) << "      Price" << "          Quantity" <<"           "<< "Amount" <<endl;
        outputFile << "\n-----------------------------------------------------------------------------" << endl;

        for (int i = 0; i < itemIndices.size(); i++) {
            int index = itemIndices[i];
            int quantity = itemQuantities[i];
            outputFile << left << setw(20) << itemList[index].name << "   Rs. " << itemList[index].price <<"               "<< quantity << "               "<<itemList[index].price*quantity<<endl;
        }

        outputFile << "\n-----------------------------------------------------------------------------"<<endl;
        outputFile << right << setw(20) << "                           Amount       : Rs. " << Amount << endl;
        outputFile << right << setw(20) << "                           GST          : Rs. " << GST << endl;
        outputFile << right << setw(20) << "                           Total Amount : Rs. " << TotalAmount << endl;
        outputFile << "*****************************************************************************" << endl;
        outputFile<<"\n\n\n=>OPEN ALL DAYS 7 AM TO 12 PM!"<<endl;
        outputFile<<"=>CONTACT : +91 8100xxx188"<<endl;
        outputFile<<"=>EMAIL   : ichirakuramen@gmail.com";

        outputFile.close();

    } else {
        cout << "Unable to save the bill to a file" << endl;
    }
}



int main(){

    int choice_1,choice_2,choice_3,itemNo, quantity;
    string customerName;

    time_t now = time(0); 
    char* dt = ctime(&now); 
    string date(dt, dt + 10); 
    string time(dt + 11, dt + 19); 


    DIR* dir = opendir("Bills");
    if (dir){
        closedir(dir);
    }
    else {
        int status = mkdir("Bills"); 
    }



    vector<Item> itemList = {{"Veg Ramen", 120}, {"Chicken Ramen", 180}, {"Special Ramen", 250},{"Char Siu & Eggs",150},{"Miso Soup", 100}, {"Sake", 120}};


    vector<int> itemIndices;
    vector<int> itemQuantities;


    cout <<"\n\n\n";
    cout << "*****************************************************************************" << endl;
    cout << "                             Welcome to Ichiraku Ramen                       " << endl;
    cout << "*****************************************************************************" << endl;
    cout <<"\n\n\n";


    while(1>0){
        cout<<"Press :\n1)Proceed To Buy\n2)Help\n3)Exit\n";
        cout<<"Your Input : ";
        cin>>choice_1;
        cout<<"\n\n\n";

        if(choice_1==1){
            displayItemList(itemList);
            while(1>0){
                cout<<"\n\n\n";
                cout << "Enter the item number to purchase (0 to exit) : ";
                cin >> itemNo;

                if (itemNo == 0) {
                        break;
                }else if (itemNo < 1 || itemNo > itemList.size()) {
                        cout << "Invalid item number. Please enter a valid item number." << endl;
                        continue;
                }

                cout << "Enter the quantity: ";
                cin >> quantity;
                itemIndices.push_back(itemNo - 1);
                itemQuantities.push_back(quantity);
            }

            if (itemIndices.empty()) {
                cout << "No items purchased. Thank you for visiting our shop!" << endl;
            }else {
                cout<<"\nCUSTOMER NAME : ";
                cin.ignore();
                getline(cin,customerName);
                cout<<"\n\n\n";
                generateBill(itemList, itemIndices, itemQuantities,customerName,date,time);
                cout<<"Thank You For Visiting Us!";
                cout<<"\n\n\n";
            }
                
        }else if(choice_1==2){
                while(1>0){
                    cout<<"Press :\n1)How To Buy \n2)Customer Care\n3)About Us\n4)Go Back\n";
                    cout<<"Your Input : ";
                    cin>>choice_2;
                    cout<<"\n\n\n";
                        if(choice_2==1){
                            cout<<"The list with the available items in the shop is provided to you.\nPls select the index number of the item and the quantity\nThank You!.\n\n\n";    
                        }else if(choice_2==2){
                            cout<<"Email us at : riyanop786@gmail.com\nCall : +91 8100xxx188\n\n\n";
                        }else if(choice_2==3){
                            cout<<"I am ABDUL RIYAN, CEO of Orange Inc.\nOrange Inc. is a startup formed of High School Students from SLHS.\n\n\n";
                        }else if(choice_2==4){
                            break;
                        }else{
                            cout<<"Enter a valid command\n";
                        }
                }
        }else if(choice_1==3){
                    break;
        }else{
                cout<<"Please enter a valid command\n";
            }
    }

    return 0;

}
