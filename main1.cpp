#include <iostream>
#include <vector>
#include "classes_header.h" // class Pet
#include "functions_header.h" // all modules/methods used

using namespace std;

int main()
{
    string key_external;
    string key_internal;
    string user_check;
    string password_check;
    const string user = "Chris02356";
    const string password = "topher001";
    const string ext_options_statement = "Options include: view, input, save, load, options, back, and exit. Type back or modify to change data.";
    const string int_options_statement = "Options include: search, list, back, and exit.";
    const string invalid_input_statement = "Input invalid. Try options.";
    const string array_calls[9] = {"back", "exit", "input", "list", "load", "options", "search", "save", "view"};
    vector<Pet> main_vector;
    unsigned int i;

    do{
        cout << "username: ";
        getline(cin, user_check);
        cout << "password: ";
        getline(cin, password_check);
        if(user_check == user && password_check == password)
        {
            do{
                system("cls");
                key_external == "";
                cout << "Input, view, save, or load data?" << endl;
                do{
                    getline(cin, key_external);
                }while(key_external == "");
                for(i = 0; i < key_external.length(); i++)
                {
                     key_external[i] = tolower(key_external[i]);
                }
                if(key_external == array_calls[8])
                {
                    do{
                        key_internal == "";
                        cout << "search or list data?" << endl;
                        do{
                            getline(cin, key_internal);
                        }while(key_internal == "");
                        for(i = 0; i < key_internal.length(); i++)
                        {
                            key_internal[i] = tolower(key_internal[i]);
                        }
                        if(key_internal == array_calls[6])
                        {
                            search_vector(main_vector);
                        }
                        else{
                            if(key_internal == array_calls[3])
                            {
                                list_vector(main_vector);
                            }
                            else{
                                if(key_internal == array_calls[5])
                                {
                                    cout << int_options_statement << endl;
                                }
                                else{
                                    if(key_internal != array_calls[0] && key_internal != array_calls[1])
                                    {
                                        cout << invalid_input_statement << endl;
                                    }
                                }
                            }
                        }
                        cout << endl;
                    }while(key_internal != array_calls[0] && key_internal != array_calls[1]);
                }
                else{
                    if(key_external == array_calls[2])
                    {
                        input_to_vector(main_vector);
                    }
                    else{
                        if(key_external == array_calls[4])
                        {
                            load_vector(main_vector);
                        }
                        else{
                            if(key_external == array_calls[7])
                            {
                                save_vector(main_vector);
                            }
                            else{
                                if(key_external == array_calls[5])
                                {
                                    cout << ext_options_statement << endl;
                                    cin >> key_internal;
                                    for(i = 0; i < key_internal.length(); i++)
                                    {
                                        key_internal[i] = tolower(key_internal[i]);
                                    }
                                    if(key_internal == "modify")
                                    {
                                        while(key_internal != array_calls[0])
                                        {
                                            modify_vector_object(main_vector);
                                            cout << "Type back or modify to change data." << endl;
                                            cin >> key_internal;
                                            for(i = 0; i < key_internal.length(); i++)
                                            {
                                                key_internal[i] = tolower(key_internal[i]);
                                            }
                                        }
                                    }
                                    else{
                                        if(key_internal != array_calls[0])
                                        {
                                            cout << "Invalid input." << endl;
                                        }
                                    }
                                }
                                else{
                                   if(key_external != array_calls[0] && key_external != array_calls[1])
                                   {
                                        cout << invalid_input_statement << endl;
                                   }
                                }
                            }
                        }
                    }
                }
                cout << endl;
            }while(key_external != array_calls[0] && key_external != array_calls[1]);
        }
        else{
            for(i = 0; i < user_check.length(); i++)
            {
                user_check[i] = tolower(user_check[i]);
            }
            for(i = 0; i < password_check.length(); i ++)
            {
                password_check[i] = tolower(password_check[i]);
            }
            if(user_check == array_calls[1] || password_check == array_calls[1])
            {
                cout << "Exiting." << endl;
            }
            else{
                cout << invalid_input_statement << endl;
            }
        }
    }while(user_check != array_calls[1] && password_check != array_calls[1]);
    return 0;
}
