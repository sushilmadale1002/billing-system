#include<bits/stdc++.h>
using namespace std;

class item {
    int id;
    string name;
    int price;
    int stock;
    public:
    //reads files and transfers data of file in vector
    friend void file_to_vector(vector<item> &v)
    {
        item a, tem;
        fstream read;
        read.open("list.csv", ios::in);
        string temp, temp2 ,word, line;
        while(read>>temp)
        {
            temp2.clear();
            for(int i=0; i<temp.size()-1;i++)
            {
                temp2.push_back(temp[i]);
            }
            tem.id = stoi(temp2);
            getline(read, line);
            stringstream s(line);
            getline(s, word, ',');
            tem.name = word;
            getline(s, word, ',');
            tem.price = stoi(word);
            getline(s, word, ',');
            tem.stock = stoi(word);
            v.push_back(tem);
        }
    }

    //adds new item in shop's list
    //adds new item in vector
    friend void add_in_vector(vector<item> &v)
    {
        item temp;
        int id, price, stock;
        string name;
        cout<<"Enter Item ID : ";
        cin>>id;
        cout<<"Enter Item Name : ";
        cin.ignore();
        getline(cin, name);
        cout<<"Enter Item Price : ";
        cin>>price;
        cout<<"Enter stock available : ";
        cin>>stock;
        temp.id = id;
        temp.name = " " + name;   //
        temp.price = price;
        temp.stock = stock;
        v.push_back(temp);
        cout<<endl<<name<<" "<<"Stock "<<stock<<" added successfully"<<endl<<endl;
        vector_to_file(v);
    }
    
    // stores data of vector in CSV file
    friend void vector_to_file(vector<item> &v)
    {
        fstream write;
        write.open("new_list.csv", ios::out);
        for(auto &i : v)
        {
            int ID, PRICE, STOCK;
            string NAME;
            ID = i.id;
            NAME = i.name;
            PRICE = i.price;
            STOCK = i.stock;
            write<<ID<<",";
            write<<NAME<<", ";
            write<<PRICE<<", ";
            write<<STOCK<<"\n";
        }
        remove("list.csv");
        rename("new_list.csv", "list.csv");
    }

    // updates the list
    friend void update(vector<item> &v)
    {
        int i_id;
        char parameter;
        cout<<"Enter the id of the product to update : ";
        cin>>i_id;
        cout<<"Enter the parameter to update : ";
        cout<<"id(i)/name(n)/price(p)/stock(s): ";
        cin>>parameter;
        if(parameter != 'i' && parameter != 'n' && parameter != 'p' && parameter != 's')
        {
            cout<<"Enter valid choice\n";
            update(v);
        }
        for(auto &i : v)
        {
            if(i.id == i_id)
            {
                if(parameter == 'i')
                {
                    int new_id;
                    cout<<"Enter updated id : ";
                    cin>>new_id;
                    i.id = new_id;
                }
                else if(parameter == 'n')
                {
                    string new_name;
                    cout<<"Enter updated name : ";
                    cin.ignore();
                    getline(cin, new_name);
                    i.name = " " + new_name;
                }
                else if(parameter == 'p')
                {
                    int new_price;
                    cout<<"Enter updated price : ";
                    cin>>new_price;
                    i.price = new_price;
                }
                else if(parameter == 's')
                {
                    int new_stock;
                    cout<<"Enter updated stock : ";
                    cin>>new_stock;
                    i.stock = new_stock;
                }
            }
        }

        vector_to_file(v);
    }

    // displays list in table on terminal
    friend void display_vector(vector<item> &v)
    {
        // display all items using vector
        cout<<left<<setw(10)<<"ID"<<left<<setw(35)<<" Name"<<left<<setw(10)<<"Price"<<left<<setw(10)<<"Stock"<<endl;
        for(auto i : v)
        {
            cout<<left<<setw(10)<<i.id<<left<<setw(35)<<i.name<<left<<setw(10)<<i.price<<left<<setw(10)<<i.stock<<endl;
        }
    }

    //makes bill
    //creates bill.txt file and writes bill there
    friend void make_bill(vector<item> &v)
    {
        vector<item> bill;
        int final_amount=0;
        fstream write;
        write.open("bill.txt", ios::out);
        // write<<"---------------------Bill No: "<<bill_no<<"-----------------------"<<endl;
        write<<endl;
        write<<"                      GCEK's Grocery Shop                  "<<endl;
        write<<endl;
        write<<"------------------------------------------------------------------------"<<endl;
        write<<"No.   Name                            Price     Quantity       Net Price"<<endl;
        write<<"------------------------------------------------------------------------"<<endl;
        // write<<right<<setw(8)<<"Sr. No."<<left<<setw(20)<<"Name"<<left<<setw(10)<<"Price"<<left<<setw(10)<<"N"<<left<<setw(10)<<"Net Price"<<endl;
        int count = 1;
        int id, num;
        char choice;
        while(true)
        {
            display_vector(v);
            cout<<"Add items ? [y/n] : ";
            cin>>choice;
            if(choice == 'n' || choice == 'N') 
            {
                vector_to_file(v);
                break;
            }
            cout<<"Enter the ID of the product to purchace : ";
            cin>>id;
            cout<<"Enter number of items to purchace : ";
            cin>>num;
            int flag = 0;
            for(auto &i : v)
            {
                if(i.id == id)
                {
                    flag = 1;
                    if(num <= i.stock)
                    {
                        bill.push_back(i);
                        // system("clear");
                        cout<<endl<<i.name<<" "<<"Quantity : "<<num<<" added to cart"<<endl<<endl;
                        i.stock -= num;
                        final_amount += (num*i.price);
                        write<<left<<setw(5)<<(count++)<<left<<setw(35)<<i.name<<left<<setw(10)<<i.price<<left<<setw(15)<<num<<left<<setw(10)<<(num*i.price)<<endl;
                        // write<<(count++)<<" "<<i.name<<" "<<i.price<<" "<<num<<" "<<(num*i.price)<<endl;
                        write<<"------------------------------------------------------------------------"<<endl;
                    }
                    else {
                        cout<<"Not sufficient quantity available."<<endl;
                        cout<<"Do you want to purchace available quantity ? yes(y)/no(n) : ";
                        char option;
                        cin>>option;
                        if(option == 'y'){
                            bill.push_back(i);
                            cout<<endl<<i.name<<" "<<"Quantity : "<<i.stock<<" added to cart"<<endl<<endl;
                            final_amount += (i.stock*i.price);
                            write<<left<<setw(5)<<(count++)<<left<<setw(35)<<i.name<<left<<setw(10)<<i.price<<left<<setw(15)<<i.stock<<left<<setw(10)<<(i.stock*i.price)<<endl;
                            // write<<(count++)<<" "<<i.name<<" "<<i.price<<" "<<num<<" "<<(num*i.price)<<endl;
                            write<<"----------------------------------------------------------------------"<<endl;
                            i.stock -= i.stock;
                        }
                    }
                }

            } if(flag == 0) {
                cout<<endl<<"Enter valid item id. "<<endl<<endl;

            }
        }
        write<<"Total : "<<final_amount<<" Rs"<<endl;
        int gst = final_amount*0.18;
        write<<"GST : "<<gst<<" Rs"<<endl;
        write<<"Amount to pay : "<<final_amount + gst<<" Rs"<<endl;
        write<<"Visit Agian"<<endl;
        write<<"Thank you!"<<endl;
    }

    // displays bill on terminal
    friend void display_bill(vector<item> &v)
    {
        string line;
        fstream read;
        read.open("bill.txt", ios::in);
        while(!read.eof())
        {
            getline(read, line);
            cout<<line<<endl;
        }
    }

    friend void add_stock(vector<item> &v)
    {
        int flag = 0;
        int ID;
        int NEW_STOCK;
        cout<<"Enter id of the item : ";
        cin>>ID;
        for(auto &i : v){
            if(ID == i.id){
                cout<<"Enter new stock quantity : ";
                cin>>NEW_STOCK;
                i.stock += NEW_STOCK;
                flag = 1;
            }
        }
        if(flag == 0){
            cout<<endl<<"Enter valid item id"<<endl<<endl;
            // add_stock(v);
        }

    }
};

int main()
{
    vector<item> v;

    file_to_vector(v);
    

    cout<<"-------------------------------------------------------------------------------------------------"<<endl;
    cout<<"---------------------------------   Welcome to GCEK's Grocery Shop   ----------------------------"<<endl;
    cout<<"-------------------------------------------------------------------------------------------------"<<endl;
    int option;
    string op;
    do
    {
        cout<<endl;
        cout<<"1. Display all items     2. Make a bill      3. Add new items        4. Update list      5. Add stock        6. Exit"<<endl;
        cout<<"Choose an option : ";
        cin>>option;

        switch (option)
        {
        case 1:
            // system("clear");
            cout<<endl;
            display_vector(v);
            break;
        case 2:
            // system("clear");
            make_bill(v);
            // system("clear");
            display_bill(v);
            break;
        case 3:
            system("clear");
            display_vector(v);
            add_in_vector(v);
            break;
        case 4:
            system("clear");
            display_vector(v);
            update(v);
            break;
        case 5:
            add_stock(v);
            vector_to_file(v);
            break;
        case 6:
            vector_to_file(v);
            return 0;
        default:
            cout<<"Enter valid option"<<endl;
            break;
        }
        
    }while(option != 6);

    vector_to_file(v);
}