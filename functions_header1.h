#ifndef FUNCTIONS_HEADER_H_INCLUDED
#define FUNCTIONS_HEADER_H_INCLUDED
#include "classes_header.h" // for class Pet access
#include <iostream> // necessary for all functions
#include <vector>   // necessary for dealing with vectors
#include <cstdlib>  // required for 'atoi' function. input_to_vector().
#include <sstream>  // required for converting string to double. search_vector().
#include <fstream>  // required for infile/outfile functions. save_vector() and load_vector().
#include <direct.h> // required for _mkdir(). save_vector().
#include <io.h>     // required for _finddata_t and accompanying functions.
#include <iomanip>  // required for setw(). list_vector(). required for setprecision() and other formatting.
#include <math.h>   // required for llround(). input_to_vector().
using namespace std;
//be_aware - modify_vector_object() breaks under pressure, especially with the doubles. --add try&catch
// 3/28/2016 - permission to open output file denied.
void formatting()
{
    cout << setprecision(2) << setiosflags(ios::fixed) << setiosflags(ios::showpoint);
}
void pause_function()
{
    string continue_string;
    string call_array[3] = {"exit", "back", "continue"};
    cout << "Enter back, continue, or exit. ";
    do{
        getline(cin, continue_string);
    } while (continue_string == "");
    for(unsigned int i = 0; i < continue_string.length(); i++)
    {
        continue_string[i] = tolower(continue_string[i]);
    }
    do{
        if(continue_string != call_array[0] && continue_string != call_array[1] && continue_string != call_array[2])
        {
            cout << "\nInvalid input. Please enter exit, back, or continue." << endl;
        }
        else{
            system("cls");
        }
    }while(continue_string != call_array[0] && continue_string != call_array[1] && continue_string != call_array[2]);
}
void string_to_double(string input_string, double output_double)
{
    stringstream conv;
    conv << input_string;
    conv >> output_double;
}
void input_to_vector(vector<Pet> & a_pet_vector)
{
    char catch_input[100];
    int number_filtered = 0;
    string name;
    string species;
    double price;
    string *ptr_name;
    string *ptr_species;
    double *ptr_price;
    ptr_name = &name;
    ptr_species = &species;
    ptr_price = &price;
    string array_exit[2] = {"Exit", "exit"};

    do{
        cout << "Number of pets to add? ";
        cin >> catch_input;
        if(isdigit(catch_input[0]))
        {
            number_filtered = atoi(catch_input);
        }
        else{
            cout << "invalid input." << endl;
        }
    }while(!isdigit(catch_input[0]));
    for(int i = 0; i < number_filtered; i++)
    {
        cout << i+1 << ". Pet\nName: ";
        cin >> *ptr_name;
        cout <<"Species: ";
        cin >> *ptr_species;
        if(name == array_exit[0] || name == array_exit[1] || species == array_exit[0] || species == array_exit[1])
        {
            break;
        }
        else{
            cout << "Price: ";
            cin >> catch_input;
            if(isdigit(catch_input[0]))
            {
                *ptr_price = atof(catch_input);
            }
            else{
                *ptr_price = 0.0;
                cout << "Invalid input. Setting price to $0.0" << endl;
            }

            a_pet_vector.push_back(Pet(name, species, price));
        }
    }
    pause_function();
}
void list_vector(vector<Pet> & a_pet_vector)
{
    int a = 0;
    const string divider = "-----------------------------------------";
    int vector_size = a_pet_vector.size();
    vector<Pet>::iterator iter = a_pet_vector.begin();
    formatting();

    cout << divider << endl;
    cout << "Vector information.\t\t\t|" << endl;
    cout << "\tNumber of objects in vector: "
         << setw(3) << left << vector_size << "|" << endl;
    cout << divider << endl;
    while(iter != a_pet_vector.end())
    {
        cout << "Object " << a+1 << "|\tName: " << setw(18) << left << iter->get_pet_name() << "|" << endl;
        cout << "\t|\tSpecies: " << setw(15) << left << iter->get_pet_species() << "|" << endl;
        cout << "\t|\tPrice: $" << setw(16) << left; iter->get_cout_price(); cout << "|" << endl; // first attempt with get_cout_price()
        cout << "\t|" << setw(32) << right << "|" << endl;
        iter++;
        a++;
    }
    cout << divider << endl;
    pause_function();
}
void search_control_break(vector<Pet> & a_pet_vector, string the_key) // tightly coupled with search_vector()
{
    int cut_off = 0;
    int number_found = a_pet_vector.size();
    double conv_double = 0.0;
    stringstream conv;
    const string not_found = "Pet not located in vector.";
    conv.str("");
    const string array_upper_calls[2] = {"Exit", "Back"};
    const string array_lower_calls[2] = {"exit", "back"};
    vector<Pet>::iterator iter = a_pet_vector.begin();
    formatting();

    conv << the_key;
    conv >> conv_double;
    while(iter != a_pet_vector.end())
    {
        if(the_key == iter->get_pet_name() || the_key == iter->get_pet_species() || conv_double == iter->get_pet_price())
        {
           cout << "\n" << iter->display_pet_data() << endl;
           //break;
        }
        else{
            cut_off++;
        }
        iter++;
    }
    if(cut_off == number_found && the_key != array_upper_calls[0] && the_key != array_lower_calls[0] && the_key != array_upper_calls[1] && the_key != array_lower_calls[1])
    {
       cout << not_found << endl;
    }
}
void search_vector(vector<Pet> & a_pet_vector)
{
    string key;
    const string array_upper_calls[4] = {"Options", "Dump_Vector", "Back", "Exit"};
    const string array_lower_calls[4] = {"options", "dump_vector", "back", "exit"};
    const string options_line = "\nSearch options include: Dump_Vector and search a pet's name, species, or price.";
    formatting();

    do{
        key == "";

        cout << "search: " << endl;
        do{
            getline(cin, key);
        }while(key == "");
        if(key == array_upper_calls[1] || key == array_lower_calls[1])
        {
            cout << endl;
            vector<Pet>::iterator iter = a_pet_vector.begin();
            while(iter != a_pet_vector.end())
            {
                cout << iter->get_pet_name() << endl;
                cout << iter->get_pet_species() << endl;
                cout << iter->get_pet_price() << endl
                     << endl;
                iter++;
            }
        }
        else{
            if(key == array_upper_calls[0] || key == array_lower_calls[0])
            {
                cout << options_line << endl;
            }
            else{
                if(key != array_lower_calls[2] && key != array_lower_calls[3] && key != array_upper_calls[2] && key != array_upper_calls[3])
                {
                    search_control_break(a_pet_vector, key);
                }
            }
        }
        cout << endl;
    }while(key != array_upper_calls[3] && key != array_lower_calls[3] && key != array_upper_calls[2] && key != array_lower_calls[2]);
    pause_function();
}
void modify_vector_object(vector<Pet> & a_pet_vector)
{
    int cut_off = 0;
    int number_found = a_pet_vector.size();
    double conv_double = 0.0;
    unsigned int a;
    double mod_double;
    double *ptr_mod_double;
    ptr_mod_double = &mod_double;
    stringstream conv_mod;
    conv_mod.str("");
    const string array_upper_calls[2] = {"Exit", "Back"};
    const string array_lower_calls[2] = {"exit", "back"};
    const string array_modification_calls[3] = {"name", "price", "species"};
    const string invalid_mod_input = "Invalid input. Try name, price, species, or back";
    vector<Pet>::iterator iter = a_pet_vector.begin();
    string the_key;
    string ext_modification_key;
    string int_modification_key;
    //char catch_input[100];

    do{
        the_key == "";
        cout << "Enter name, price, or species of the Pet you want to modify" << endl;
        do{
        getline(cin, the_key);
        }while(the_key == "");

        if(the_key == array_upper_calls[0] || the_key == array_upper_calls[1] || the_key == array_lower_calls[0] || the_key == array_lower_calls[1])
        {
            cout << "backing out..." << endl;
        }
        else{
            string_to_double(the_key, conv_double);
            while(iter != a_pet_vector.end())
            {
                if(the_key == iter->get_pet_name() || the_key == iter->get_pet_species() || conv_double == iter->get_pet_price())
                {
                    cout << "\n" << iter->display_pet_data() << endl;
                    int_modification_key == "";
                    ext_modification_key == "";
                    cout << "\nWhich property to modify? ";
                    do{
                        getline(cin, ext_modification_key);
                    }while(ext_modification_key == "");
                    for(a = 0; a < ext_modification_key.length(); a++)
                    {
                        ext_modification_key[a] = tolower(ext_modification_key[a]);
                    }
                    if(ext_modification_key == array_modification_calls[1])
                    {
                        cout << "Change price to: ";
                        cin >> int_modification_key;

                        if(int_modification_key != array_upper_calls[0] && int_modification_key != array_upper_calls[1] && int_modification_key != array_lower_calls[0] && int_modification_key != array_lower_calls[1])
                        {
                            if(isdigit(int_modification_key[0]))
                            {
                                *ptr_mod_double = atof(int_modification_key.c_str());
                            }
                            else{
                                *ptr_mod_double = 0.0;
                                cout << "Invalid input. Setting price to $0.00" << endl;
                            }
                            iter->set_pet_price(mod_double);
                        }
                    }
                    else{
                        if(ext_modification_key == array_modification_calls[0])
                        {
                            cout << "Change name to: ";
                            cin >> int_modification_key;
                            if(int_modification_key != array_upper_calls[0] && int_modification_key != array_upper_calls[1] && int_modification_key != array_lower_calls[0] && int_modification_key != array_lower_calls[1])
                            {
                                iter->set_pet_name(int_modification_key);
                            }
                        }
                        else{
                            if(ext_modification_key == array_modification_calls[2])
                            {
                                cout << "Change species to: ";
                                cin >> int_modification_key;
                                if(int_modification_key != array_upper_calls[0] && int_modification_key != array_upper_calls[1] && int_modification_key != array_lower_calls[0] && int_modification_key != array_lower_calls[1])
                                {
                                    iter->set_pet_species(int_modification_key);
                                }
                            }
                            else{
                                if(ext_modification_key == array_upper_calls[0] || ext_modification_key == array_upper_calls[1] || ext_modification_key == array_lower_calls[0] || ext_modification_key == array_lower_calls[1])
                                {
                                    cout << "backing out..." << endl;
                                }
                                else{
                                    cout << invalid_mod_input << endl;
                                }
                            }
                        }
                    }
                }
                else{
                    cut_off++;
                }
                iter++;
            }
            if(cut_off == number_found)
            {
                cout << "not found. Possibly invalid input." << endl;
            }

            iter = a_pet_vector.begin();
        }
    }while(the_key != array_upper_calls[0] && the_key != array_upper_calls[1] && the_key != array_lower_calls[0] && the_key != array_lower_calls[1]);
}
void dump_file_names(string directory) // tightly coupled with load_vector() and save_vector()
{
    _finddata_t files;
    string file_name;
	if(directory.substr(directory.length() - 4) != ".txt")
	{
		directory = directory + "/.txt";
	}
	int file_name_placement = directory.length() - 4;

    directory.insert(file_name_placement, "*");
    int next_return_value = 0;

    cout << "Files found:" << endl;
    int return_value = _findfirst(directory.c_str(), &files); // vsf is Vector Save Files
    if(return_value != -1)
    {
         while(next_return_value != -1)
        {
            file_name = files.name;
            file_name.erase(file_name.end()-4, file_name.end());
            cout << file_name << endl;
            next_return_value = _findnext(return_value, &files);
        }
        _findclose(return_value);
    }
}
void save_vector(vector<Pet> & a_pet_vector)
{
    vector<Pet>::iterator iter = a_pet_vector.begin();
    string directory = "C:/Users/spidercolony/Desktop/saved_data_files"; // 46characters long
    string sub_directory = "/vsf"; // 4char-long
    string data_type = "/.txt"; // 5char-long
    string file_name;
    int number_found;
	
    if(_mkdir(directory.c_str()) == 0)
    {
        cout << "creating directory. " << directory << endl;
    }
    else{
        cout << "directory located." << endl;
    }
    directory.insert(46, sub_directory);
    if(_mkdir(directory.c_str()) == 0)
    {
        cout << "creating sub_directory. " << directory << endl;
    }
    else{
        cout << "sub_directory located." << endl;
		dump_file_names(directory);
    }
    cout << "|Save| File name:" << endl;
    cin >> file_name;
    directory.insert(50, data_type);
    directory.insert(51, file_name);
    cout << "save location is " << directory << endl;
    ofstream outfile(directory.c_str());
    number_found = a_pet_vector.size();
    outfile << number_found << endl;
    while(iter != a_pet_vector.end())
    {
        outfile << iter->get_pet_name() << endl;
        outfile << iter->get_pet_species() << endl;
        outfile << iter->get_pet_price() << endl;
        iter++;
    }
    outfile.close();
    pause_function();
}
void load_vector(vector<Pet> & a_pet_vector)
{
    int number_found;
    string variable_1_found;
    string variable_2_found;
    double variable_3_found;
    string directory = "C:/Users/spidercolony/Desktop/saved_data_files/vsf/.txt"; // vsf is Vector Save Files
    string file_name;

    dump_file_names(directory);
    cout << "|Load| File name:" << endl;
    cin >> file_name;
    if(file_name != "exit" && file_name != "Exit")
    {
        directory.insert(51, file_name);
        cout << "Loading data from:\n\t" << directory << endl;
        ifstream infile(directory.c_str());
        if(infile.fail())
        {
            cout << "Couldn't load file." << endl;
        }
        else{
            infile >> number_found;
            for(int i = 0; i < number_found; i++)
            {
                infile >> variable_1_found;
                infile >> variable_2_found;
                infile >> variable_3_found;
                a_pet_vector.push_back(Pet(variable_1_found, variable_2_found,
                                           variable_3_found));
            }
            cout << "Loaded " << number_found << " objects to vector." << endl;
        }
        infile.close();
    }
    pause_function();
}

#endif // FUNCTIONS_HEADER_H_INCLUDED
