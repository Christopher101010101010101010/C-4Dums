#ifndef CLASSES_HEADER_CBP_H_INCLUDED
#define CLASSES_HEADER_CBP_H_INCLUDED
#include <iostream>
#include <string>
#include <iomanip> // required for setprecision() for currency
#include <sstream> // required for ostringstream function. set_display().
using namespace std;

class Pet
{
    private:
        string pet_name;
        string pet_species;
        double pet_price;
        string display;
    public:
        string get_pet_name(){return pet_name;}
        string get_pet_species(){return pet_species;}
        double get_pet_price(){ostringstream conv; conv << setprecision(100) << pet_price;
                               string str_price = conv.str(); int prec = str_price.find(".", 0);
                               str_price = str_price.substr(0, prec+3);
                               double fixed_pet_price = stod(str_price);
                               return fixed_pet_price;}
        void get_cout_price(){cout << setprecision(2) << setiosflags(ios::fixed) << setiosflags(ios::showpoint);
                              cout << pet_price;} // do not directly pair with a cout statement. Ex) DO NOT cout << iter->get_cout_price()
        void set_pet_name(string a_pet_name){pet_name = a_pet_name;}
        void set_pet_species(string a_pet_species){pet_species = a_pet_species;}
        void set_pet_price(double a_pet_price){pet_price = a_pet_price;}
        string display_pet_data(){set_display(); return display;}
        void set_display(){ostringstream conv; conv << setprecision(100) << pet_price;
                           string str_price = conv.str(); int prec = str_price.find(".", 0);
                           str_price = str_price.substr(0, prec+3);
                           display = "Pet name: " + pet_name + "\nPet species: " + pet_species
                           + "\nPet price: $" + str_price;}
        Pet(string a_pet_name, string a_pet_species, double a_pet_price) : pet_name(a_pet_name),
                                                                           pet_species(a_pet_species),
                                                                           pet_price(a_pet_price) {}
        Pet();
        //~Pet(){}; further testing required before implementing deconstructor.
};

#endif // CLASSES_HEADER_CBP_H_INCLUDED
