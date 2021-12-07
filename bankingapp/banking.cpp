  #include <iostream>
  #include <fstream>
  #include <windows.h>
  #include <string>
  #include <stdio.h>
  #include <time.h> 


   
  using namespace std;
  void menu();
  void login();

  void changeColour(int colour)
  {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,colour);
  }

  bool fexists(string file) //function for checking file is exist or not
  {

    ifstream f;
    string accounts =("accounts\\");    
    file.insert(0,  accounts);
    f.open(file);

    bool f_exists = f.is_open();

    f.close();
    return f_exists;
  }

  string getLast(string loginCode) // getting last line of files
  {
    ifstream lasttext;
          
  lasttext.open(loginCode.c_str());
  if(lasttext.is_open()) 
  {
    lasttext.seekg(-1,ios_base::end);

    bool keepLooping = true;
    while(keepLooping) 
    {
      char ch;
      lasttext.get(ch);

      if((int)lasttext.tellg() <= 1) 
      {
      lasttext.seekg(0);
      keepLooping = false;
      }
      else if(ch == '\n') 
      {
      keepLooping = false;
      }
      else 
      {
      lasttext.seekg(-2,ios_base::cur);
      }
    }
    string lastLine; 
    getline(lasttext,lastLine);
    return (lastLine);
  }
    lasttext.close();
    return 0;
  }
  

  void clear()
  {
    system("cls");
  }

  void createAccount()
  { 
    string privateCode; 
    cout<<"Please create a 8 digit long private number (password): ";
    cin>>privateCode;
    if(privateCode.length()!=8 | privateCode[0]==privateCode[1]==privateCode[2]==privateCode[3])
    { clear();
      cout<<"Please enter 8 digit long private number or your password includes too many repeating numbers...";
      menu();
    }
    else
    {
    cout<<"Please Enter Your,\nName:\n";
    string Name;
    string Surname;    
    cin>>Name;
    cout<<"Please Enter Your,\nSurname:\n";
    cin>>Surname;
    srand (time(NULL));
    int random = rand() % 10000+1000;
    string password = to_string(random);
    if(Name.length()>2 && Surname.length()>2)
    { 
      string folderName = Name+Surname+password;
        if(fexists(folderName)==1)
        {
          cout<<"Your account already exists...";
          menu();
        }
        else
        {
          string s2 =("accounts\\");
          folderName.insert(0,  s2);
          ofstream Account(folderName.c_str());
          float balance=0;
          string transactionCode = Name+Surname+password;
            Account <<Name<<endl<<Surname<<endl;
            Account <<privateCode<<endl<<transactionCode<<endl<<balance;
            Account.close(); 
            folderName.erase(0, 10);
          cout<<"Your Transaction Code (IBAN) is: "<<transactionCode<<endl;
          cout<<"Your Private Code (password) is: "<<privateCode<<endl;
          menu();
        }
    }
    else
    {
      clear();
      cout<<"Please enter valid name or surname...";
      menu();
    }
    }
  }
  
  

  void menu()
  {
    
      
      char menu;
      
      changeColour(10);
      cout<<"\n Welcome to BYRSH Bank!"<<"\n"<<"*======================*"<<"\n";
      cout<<"| Create an Account.(C)|"<<endl;
      cout<<"|       Login.      (L)|"<<endl;
      cout<<"|       Exit.       (E)|"<<endl;
      cout<<"*----------------------*"<<endl;
      cout<<"\nPlease Login or Create a new account: ";




      cin>> menu;
      switch(menu)
      {
        case 'C':
          cout<< "Hello Stranger..."<<"\nLet's create you an Account!\n";
          createAccount();

        break; 

        
        case 'L':
          login();
          
        break;
        
        case 'E':
        {
          cout<<"\nSee you soon!!\n";
          exit(0);
        }
        break;

	    }
    
  }
  
  

  void login()
  { 
    string loginCode;
    cout<<"Please enter your Transaction Code: ";
    cin>>loginCode;
    ifstream login;
    string s2 =("accounts\\");
    loginCode.insert(0,  s2);
    login.open(loginCode.c_str());
    
    string private1 = "";
    string line;
    cout<<"Please enter your Private Code: ";
    cin>> private1;
    clear();
    ifstream f(loginCode.c_str());
    string s;

    for (int i = 1; i <= 3; i++)
    {
      getline(f, s);
      
    }

    if(login.is_open() && s==private1)
    {   
      string line;
      getline(login,line);  
      cout<<"\n\n****Welcome to your account "<<line<<"!***\n\n";
      Sleep(1000);

      for(;;)
     {
    
      changeColour(15);
      cout<<"\nPlease Select An Operation: ";
      cout<<"\n*======================*\n";
      cout<<"|      Deposit.     (D)|"<<endl;
      cout<<"|      Withdraw.    (W)|"<<endl;
      cout<<"|      Transfer.    (T)|"<<endl;
      cout<<"|  Balance Inquiry. (I)|"<<endl;
      cout<<"|  Balance History  (H)|"<<endl;
      cout<<"|      Sign Out     (S)|"<<endl;
      cout<<"*----------------------*"<<endl;

                 
      char loginMenu;
      cin>> loginMenu;              
      switch(loginMenu)
      {
        case 'I':
        {    
            changeColour(11);
            cout << "\n\nYour Account's Balance is: " << getLast(loginCode) << '\n';
            Sleep(2000);
            clear();
        
        }  
        break;

        case 'D':
        {
          
          
          float depositAmount;
          cout<<"Please enter the deposit amount: ";
          cin>>depositAmount;
          if(depositAmount<=0)
          { 
            changeColour(4);
            cout<<"\nYou can't deposit 0 or anything below it..."<<endl;
            Sleep(2500);
            clear();
          }
          else
          {
            cout<<"\n\n\nIn Progress\n\n\n";
            Sleep(1000);
            float lastAmount = stof(getLast(loginCode));
            depositAmount += lastAmount; 
            changeColour(11);                
            cout<<"Thank you... Your new amount is: "<< depositAmount<<endl;
            ofstream deposit;
            deposit.open(loginCode, fstream::app);
            deposit<<"\n"<<depositAmount;
            deposit.close();
            Sleep(2500);
            clear();
          }
          

        }
        break;
        
        case 'W':
        { 
          float amountWithdraw;
          cout<< "Please enter the amount:"<<endl;
          cin>>amountWithdraw;

          if(stof(getLast(loginCode))>0 | amountWithdraw>0)
          {
            
            getLast(loginCode);
            float currentAmount ;
            currentAmount = stof(getLast(loginCode));
            currentAmount -= amountWithdraw; 
            changeColour(11);
            cout<<amountWithdraw<<" Withdraw successfully completed\n";
            cout<<"Thank you... Your new amount is: "<<currentAmount;

            ofstream withdraw;
            withdraw.open(loginCode, fstream::app);
            withdraw<<"\n"<<currentAmount;
            withdraw.close();
            Sleep(2000);
              clear();
          }
          else
          {
            clear();
            changeColour(4);
            cout<<"\nYour balance isn't enough or \nyou can't withdraw an amount below zero...\n";
          }
          
        }
        break;

        case 'T':
        {
          if(stof(getLast(loginCode))>0)
          {
            float amountTransfer;
            string transferAcc;
            cout<< "Please enter Transaction Number of recipient:"<<endl;
            cin>>transferAcc;
            cout<< "Please enter the amount:"<<endl;
            cin>>amountTransfer;
            string s3 =("accounts\\");
            transferAcc.insert(0,  s3);
            if(0<amountTransfer | (stof(getLast(loginCode)) - amountTransfer)>0 )
            {
              
              ofstream to;
              to.open(transferAcc, fstream::app);
              
              if(getLast(transferAcc) == "" | transferAcc !=loginCode)
              {
                changeColour(4);
                cout<<"\nWe couldn't find Transaction Number that you entered or you're trying to do unauthorized process ...\nYour account might be stolen? safety exit activated.\n";
                to.close();
                remove(transferAcc.c_str());
                menu();
              }

              else
              {
                float transferTo = stof(getLast(transferAcc)) + amountTransfer;
                to<<"\n"<<transferTo;
                changeColour(11);
                cout<< "You've successfully transfered " <<amountTransfer; 
                cout<< "\nHave a nice dayy!!!!";
                Sleep(500);
                ofstream from;
                from.open(loginCode, fstream::app);
                float transferFrom = stof(getLast(loginCode)) - amountTransfer;
                from<<"\n"<<transferFrom;
                Sleep(2000);
                clear();
                from.close();
                to.close();
              }
            }

            else 
            {
              clear();
              changeColour(4);
              cout<<"\nYour balance isn't enough to transfer the amount...\n";
            }
          }

          else
          { 
            clear();
            changeColour(4);
            cout<<"\nYour balance isn't enough...\n";
          }
          


        }
        break;

        case 'E':
        {
          cout<<"See you soon!!\n";
          exit(0);
        }
        break;

        case 'H':
        {
          cout<<"\nWelcome to the Balance History...\n";
          cout<<"Now you can easily follow your transactions...\n";
          
          ifstream history;
          history.open(loginCode);
          string after;
          string text;

          for (int i = 1; i <= 4; i++)
          {
          getline(history, after);

          }
          int counter = 1;

          while(getline(history,text) && counter++)
          { changeColour(11);
            cout<<(counter-1)<<". Balance= "<<text<<endl;
          }

        }
        break;

        case 'S':
        {
          menu();
        }

	    }
     }
    }
  

    

    else
    {
      string question;
      changeColour(4);
      cout<<"You've entered the wrong Transaction code or password."<<endl<<"Do you have an account? Want to create one?(yes/no): "<<endl;
      cin>>question;
      if(question=="yes")
      {
        createAccount();
      }
      else if(question=="no")
      {
        menu();
      }
      else 
      { changeColour(4);
        cout<<"You've entered wrong answer.";
        menu();
      }    
      

    }
    login.close();
  }


  
  


int main()
  {
    menu();
  }
