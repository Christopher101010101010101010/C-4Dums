#include <iostream>
//#include <windows.h> // For CODEBLOCKS edition of File_Manipulator
#include <vector>

#include "fm_function_header.h"
#include "fm_object_header.h"

using namespace std;
/*NEXT STEP(S):		idea, make directory and copy files/directories into new locale
					'C://.../...' might want to fix the '//' someday, may cause problems in field. just saying.
					List saved "of interest" directories and files and copy, rename, etc through a listing function..?
				*/

void intro()
{
	const string intro = "Started 5/12/2016\tFile_Manipulator";
	const string l_mod = "last modified: 5/28/2016"; // l_mod stands for last modified
	cout << intro << endl << l_mod << endl << endl;
}

// Testing function(s)
void testing01() // testing module, for setters and getters, from 5/12/2016 & 5/13/2016
{
	File mpf; // mpf stands for my parent file
	directory mdir; // mdir stands for my directory
	file_ mtf; // mtf stands for my text file

    // File parent class testing
	mpf.set_name("my_txt");
	mpf.set_path("//user/folder1/folder2/");
	mpf.set_size(100);
	cout << "get_name() returns: " << mpf.get_name()
		<< "\nget_path() returns: " << mpf.get_path() << "\nget_size() returns: " << mpf.get_size() << endl;

	mpf.set_all("text1", "//my_user/desktop/", 125);
	mpf.get_all();

	cout << endl << endl;
    // directory child class testing
	mdir.set_dir("my_folder", "C://my_doc/", 4590, 5);
	mdir.get_dir();
	mdir.set_num_content(987);
	cout << "set_num_content(987) || get_num_content() returns: " << mdir.get_num_content() << endl;

	cout << endl << endl;
    // file_ child class testing
	mtf.set_file_("my_dat", "C://Program Files/", 2340, ".dat");
	mtf.get_file_();
	mtf.set_type(".pdf");
	cout << "set_type(.pdf) || get_type() returns: " << mtf.get_type() << endl;
}

void testing02() /* 5/12 - 5/21/2016
				   byte_size(), num_content(), explore(), check_input(), save_VTC(), load_VTC(),
				   conv_VTC_dir(), and conv_VTC_fil().*/
{
	/*byte_size() testing
	int accum = 0; // 5/13/2015
	string path_bst = "C:/Program Files (x86)/Mozilla Firefox"; // path_bst is path byte size testing
	accum = byte_size(path_bst);
	cout << path_bst << "\n~" << accum << " file bytes" << endl; //file bytes are the number of bytes that make up the directory's files.*/

	/*num_content() testing
	int num_content = 0; // 5/14/2016
	string path_nct = "C:/Program Files (x86)/Mozilla Firefox"; //path_nct is path num of contents testing
	num_content = num_cont(path_nct);
	cout << path_nct << "\nNumber of Contents: " << num_content << " files  and directories." << endl;*/
	/*began explore() testing*/

	/*check_input testing
	string input = "BSU_folder"; // 5/16/2016
	string dir = "C:/Users/spidercolony/Desktop";
	cout << check_input(input.c_str(), dir.c_str()) << endl;*/


	/*explore() testing
	vector<VTC> my_transportation; // 5/16 - 5/17/2016, ...
	my_transportation = explore(my_transportation);
	output_VTC(my_transportation);*/

	/*save_VTC() testing
	save_VTC(my_transportation); // 5/18/2016
	*/

	/*conv from vtc to dir & file testing
	vector<directory> my_dirs;					// 5/20/2016
	my_dirs = conv_VTC_dir(my_transportation);
	vector<directory>::iterator iter_dir = my_dirs.begin();
	cout << "\n\nVTC\n";
	output_VTC(my_transportation);
	cout << "\n\ndir\n";
	while(iter_dir != my_dirs.end())
	{
		iter_dir->get_dir();
		iter_dir++;
	}
	cout << endl << endl;
	vector<file_> my_fil;
	my_fil = conv_VTC_fil(my_transportation);
	vector<file_>::iterator iter_fil = my_fil.begin();
	cout << "\n\nfil\n";
	while(iter_fil != my_fil.end())
	{
		iter_fil->get_file_();
		iter_fil++;
	}	*/

	/*load vtc testing
	my_transportation = load_VTC(my_transportation); // 5/20 - 5/21/2016 
	output_VTC(my_transportation);*/
}

void testing03() // testing ideas for main()
{
	vector<VTC> main_VTC;
	string main_input = "", main_calls[6] = {"copy", "exit", "explore", "load", "rename", "save"};
	unsigned int i, control_integer;
	
	do{
		cout << "Explore, copy, rename, load, save? " << endl;	
		do{
			getline(cin, main_input);
			for(i = 0; i < main_input.length(); i++)
			{
				main_input[i] = tolower(main_input[i]);
			}
		}while(main_input == "");	
		for(i = 0; i < 6; i++)
		{
			if(main_input == main_calls[i])
			{
				control_integer = i + 1;
				break;
			}
			else{
				control_integer = -1;
			}
		}
		switch (control_integer)
		{
			case 1:
				copy_df(main_VTC);
				break;
			case 2:
				cout << "Exiting." << endl;
				break;
			case 3:
			{
				main_VTC = explore(main_VTC);
				main_VTC = sce_test(main_VTC);
				main_VTC = tc_test(main_VTC);
			}
				break;
			case 4:
			{
				main_VTC = load_VTC(main_VTC);
				main_VTC = sce_test(main_VTC);
				main_VTC = tc_test(main_VTC);
			}
				break;
			case 5:
			{
				main_VTC = rename_df(main_VTC);
				main_VTC = sce_test(main_VTC);
				main_VTC = tc_test(main_VTC);
			}
				break;
			case 6:
				save_VTC(main_VTC);
				break;
			default:
				cout << "Invalid." << endl;
				break;
		}
		system("cls");
	}while(main_input != main_calls[1]);
}

int main()
{
	//***Introduction
	intro();

    /***Testing
	testing01(); // 5/12/2016
	testing02(); // check function notes for details*/

    /*copy_df() testing
	vector<VTC> a_VTC;
	a_VTC = explore(a_VTC);
	copy_df(a_VTC);
	/*dir_copy("C:/Users/spidercolony/Music/the girl with the dragon tattoo");*/
	
	/*testing menu setup
	testing03();*/

	/*rename_df() testing
	// 5/26/2016
	string path = "C:/Users/spidercolony/Desktop/fm_dat/fm_saves/save01.txt";
	string input = "Users";
	cout << seg_path(input, path) << endl;
	cout << sep_path(input, path) << endl;

	vector<VTC> my_VTC;
	my_VTC = explore(my_VTC);
	my_VTC = rename_df(my_VTC);*/

	testing03(); //5/28/2016

	system("pause");
	return 0;
}
