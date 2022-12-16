#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <fstream>
#include <iomanip>
#include <direct.h> // _mkdir()
#include <Windows.h> // CopyFile()

#include "fm_object_header.h"

using namespace std;

// Background functions

int byte_size(string directory_path) // size in file bytes, the bytes of file contents
{
    _finddata_t sub_data;
    vector<string> dir_paths;
    dir_paths.clear();
    int done = 0, rec_ff, rec_res, rec_f;
    string sub_dir, rec_temp, rec_file_path, rec_dir_path;
    int rec_accumulator = 0;

    do{
        if(done != 0)
        {
            sub_dir = dir_paths.back();
            directory_path = sub_dir;
            dir_paths.pop_back();
        }
        string dir_buff = directory_path + "/*.*";
        rec_ff = _findfirst(dir_buff.c_str(), &sub_data);
        if(rec_ff != -1)
        {
            rec_res = 0;
            while(rec_res != -1)
            {
                rec_temp = sub_data.name;
                rec_f = rec_temp.find_last_of('.');
                if(rec_f != -1)
                {
                    rec_file_path = directory_path + "/" + rec_temp;
                    if(rec_temp != "." && rec_temp != "..")
                    {
                        ifstream rec_in(rec_file_path.c_str(), ifstream::ate | ifstream::binary);
                        rec_accumulator += int(rec_in.tellg());
                    }
                }
                else{
                    rec_dir_path = directory_path + "/" + rec_temp;
                    dir_paths.push_back(rec_dir_path);
                }
                rec_res = _findnext(rec_ff, &sub_data);
            }
            _findclose(rec_ff);
        }
        done = dir_paths.size();
    }while(done != 0);
    return rec_accumulator;
}

int num_cont(string directory_path) // number of contents files and directories
{
    _finddata_t sub_data;
    vector<string> dir_paths;
    dir_paths.clear();
    int done = 0, rec_ff, rec_res, rec_f;
    string sub_dir, rec_temp, rec_file_path, rec_dir_path;
    int num_accumulator = 0;

    do{
        if(done != 0)
        {
            sub_dir = dir_paths.back();
            directory_path = sub_dir;
            dir_paths.pop_back();
        }
        string dir_buff = directory_path + "/*.*";
        rec_ff = _findfirst(dir_buff.c_str(), &sub_data);
        if(rec_ff != -1)
        {
            rec_res = 0;
            while(rec_res != -1)
            {
                rec_temp = sub_data.name;
                rec_f = rec_temp.find_last_of('.');
                if(rec_f != -1)
                {
                    //rec_file_path = directory_path + "/" + rec_temp;
                    if(rec_temp != "." && rec_temp != "..")
                    {
                        ++num_accumulator;
                    }
                    //cout<<endl<<rec_file_path<<endl;
                }
                else{
                    rec_dir_path = directory_path + "/" + rec_temp;
                    dir_paths.push_back(rec_dir_path);
                    ++num_accumulator;
                }
                rec_res = _findnext(rec_ff, &sub_data);
            }
            _findclose(rec_ff);
        }
        done = dir_paths.size();
    }while(done != 0);
    return num_accumulator;
}

bool check_input(string input, string path) // tight coupling avec explore()
{
    _finddata_t c_data;
    bool check;
    path = path + "/*.*";
    int c_ff = _findfirst(path.c_str(), &c_data);
    if(c_ff != -1)
    {
        int c_res = 0;
        while(c_res != -1)
        {
            string c_temp = c_data.name;
            if(input == c_temp)
            {
                check = true;
                return check;
            }
            c_res = _findnext(c_ff, &c_data);
        }
        _findclose(c_res);
    }
	check = false;
    return check;
}

vector<VTC> conv_to_VTC(vector<directory> dir_vect, vector<file_> fil_vect)
{
	vector<VTC> VTC_gen;
	vector<directory>::iterator iter_dir = dir_vect.begin();
	vector<file_>::iterator iter_fil = fil_vect.begin();
	string transpor_name, transpor_path, transpor_type;
	int transpor_size, transpor_num_content;
	string *ptr_tn, *ptr_tp, *ptr_tt;
	int *ptr_ts, *ptr_tnc;
	ptr_tn = &transpor_name;
	ptr_tp = &transpor_path;
	ptr_tt = &transpor_type;
	ptr_ts = &transpor_size;
	ptr_tnc = &transpor_num_content;
	while(iter_dir != dir_vect.end() || iter_fil != fil_vect.end())
	{
		if(iter_dir != dir_vect.end())
		{
			*ptr_tn = iter_dir->get_name();
			*ptr_tp = iter_dir->get_path();
			*ptr_ts = iter_dir->get_size();
			*ptr_tnc = iter_dir->get_num_content();
			VTC new_dir_obj(transpor_name, transpor_path, transpor_size, transpor_num_content);
			VTC_gen.push_back(new_dir_obj);
			iter_dir++;
		}
		if(iter_fil != fil_vect.end())
		{
			*ptr_tn = iter_fil->get_name();
			*ptr_tp = iter_fil->get_path();
			*ptr_ts = iter_fil->get_size();
			*ptr_tt = iter_fil->get_type();
			VTC new_fil_obj(transpor_name, transpor_path, transpor_size, transpor_type);
			VTC_gen.push_back(new_fil_obj);
			iter_fil++;
		}

	}
	ptr_tn = 0; 
	ptr_tp = 0;
	ptr_tt = 0;
	ptr_ts = 0;
	ptr_tnc = 0;

	return VTC_gen;
}

vector<directory> conv_VTC_dir(vector<VTC> a_VTC)
{
	vector<directory> return_dir;
	vector<VTC>::iterator iter_vtc = a_VTC.begin();
	string transpor_name, transpor_path, transpor_type;
	int transpor_size, transpor_num_content;
	string *ptr_tn, *ptr_tp, *ptr_tt;
	int *ptr_ts, *ptr_tnc;
	ptr_tn = &transpor_name;
	ptr_tp = &transpor_path;
	ptr_tt = &transpor_type;
	ptr_ts = &transpor_size;
	ptr_tnc = &transpor_num_content;
	while(iter_vtc != a_VTC.end())
	{
		*ptr_tt = iter_vtc->get_type();
		if(transpor_type == "d")
		{
			*ptr_tn = iter_vtc->get_name();
			*ptr_tp = iter_vtc->get_path();
			*ptr_ts = iter_vtc->get_size();
			*ptr_tnc = iter_vtc->get_num();
			directory dir_obj;
			dir_obj.set_dir(transpor_name, transpor_path, transpor_size, transpor_num_content);
			return_dir.push_back(dir_obj);
		}
		iter_vtc++;
	}
	ptr_tn = 0;
	ptr_tp = 0;
	ptr_tt = 0;
	ptr_ts = 0;
	ptr_tnc = 0;

	return return_dir;
}

vector<file_> conv_VTC_fil(vector<VTC> a_VTC)
{
	vector<file_> return_fil;
	vector<VTC>::iterator iter_vtc = a_VTC.begin();
	string transpor_name, transpor_path, transpor_type;
	int transpor_size, transpor_num_content;
	string *ptr_tn, *ptr_tp, *ptr_tt;
	int *ptr_ts, *ptr_tnc;
	ptr_tn = &transpor_name;
	ptr_tp = &transpor_path;
	ptr_tt = &transpor_type;
	ptr_ts = &transpor_size;
	ptr_tnc = &transpor_num_content;
	while(iter_vtc != a_VTC.end())
	{
		*ptr_tnc = iter_vtc->get_num();
		if(transpor_num_content == -1)
		{
			*ptr_tn = iter_vtc->get_name();
			*ptr_tp = iter_vtc->get_path();
			*ptr_ts = iter_vtc->get_size();
			*ptr_tt = iter_vtc->get_type();
			file_ fil_obj;
			fil_obj.set_file_(transpor_name, transpor_path, transpor_size, transpor_type);
			return_fil.push_back(fil_obj);
		}
		iter_vtc++;
	}
	ptr_tn = 0;
	ptr_tp = 0;
	ptr_tt = 0;
	ptr_ts = 0;
	ptr_tnc = 0;

	return return_fil;
}

void dir_copy(string directory_path, string copy_dir) 
{
	 _finddata_t sub_data;
    vector<string> dir_paths;
	vector<string> copy_paths;
    dir_paths.clear();
	copy_paths.clear();
	bool frt = true; // first run through
    int done = 0, rec_ff, rec_res, rec_f;
    string rec_temp, rec_file_path, rec_dir_path, direct, 
           dpath_to, path_from;
	
	dpath_to = copy_dir;
    do{
        if(done != 0)
        {
            directory_path = dir_paths.back();
            dir_paths.pop_back();
			copy_dir = copy_paths.back(); 
			copy_paths.pop_back();
        }
        string dir_buff = directory_path + "/*.*";
        rec_ff = _findfirst(dir_buff.c_str(), &sub_data);
        if(rec_ff != -1)
        {
            rec_res = 0;
            while(rec_res != -1)
            {
                rec_temp = sub_data.name;
                rec_f = rec_temp.find_last_of('.');
                if(rec_f != -1)
                {
                    if(rec_temp != "." && rec_temp != "..")
                    {
                        path_from = directory_path + "/" + rec_temp;
						dpath_to = copy_dir + "/" + rec_temp;
						CopyFile(path_from.c_str(), dpath_to.c_str(), TRUE);
                    }
                }
                else{
                    rec_dir_path = directory_path + "/" + rec_temp;
                    dir_paths.push_back(rec_dir_path);
					
					dpath_to = copy_dir + "/" + rec_temp;
					_mkdir(dpath_to.c_str());
					copy_paths.push_back(dpath_to);
                }
                rec_res = _findnext(rec_ff, &sub_data);
            }
            _findclose(rec_ff);
        }
        done = dir_paths.size();
    }while(done != 0);
}

bool seg_path(string input, string path)
{
	int i = 0, a = 0;
	string seg;

	i = path.find("/");
	seg = path.substr(0, i);
	if(seg == input)
	{
		return true;
	}
	while(i != -1 && a != -1)
	{
		a = path.find("/", i + 1);
		if(a != -1)
		{
			seg = path.substr(i + 1, a - i - 1);
		}
		else{
			seg = path.substr(i + 1);
		}
		if(seg == input)
		{
			return true;
		}
		if(a != -1)
		{
			i = path.find("/", a + 1);
			if(i != -1)
			{
				seg = path.substr(a + 1, i - a - 1);
			}
			else{
				seg = path.substr(a + 1);
			}
		}
		if(seg == input)
		{
			return true;
		}
	}
	return false;
}

string sep_path(string input, string path)
{
	string sep_path;
	int i = 0, a = 0;
	string seg;

	i = path.find("/");
	seg = path.substr(0, i);
	if(seg == input)
	{
		sep_path = path.substr(0, i);
	}
	while(i != -1 && a != -1)
	{
		a = path.find("/", i + 1);
		if(a != -1)
		{
			seg = path.substr(i + 1, a - i - 1);
			sep_path = path.substr(0, a);
		}
		else{
			seg = path.substr(i + 1);
			sep_path = path.substr(0, i);
		}
		if(seg == input)
		{
			return sep_path;
		}
		if(a != -1)
		{
			i = path.find("/", a + 1);
			if(i != -1)
			{
				seg = path.substr(a + 1, i - a - 1);
				sep_path = path.substr(0, i);
			}
			else{
				seg = path.substr(a + 1);
				sep_path = path.substr(0, a);
			}
		}
		if(seg == input)
		{
			return sep_path;
		}
	}
	return sep_path;
}

string sep_end_path(string input, string path)
{
	string sep_path;
	int i = 0, a = 0;
	string seg;

	i = path.find("/");
	seg = path.substr(0, i);
	if(seg == input)
	{
		sep_path = path.substr(i);
	}
	while(i != -1 && a != -1)
	{
		a = path.find("/", i + 1);
		if(a != -1)
		{
			seg = path.substr(i + 1, a - i - 1);
			sep_path = path.substr(a);
		}
		else{
			seg = path.substr(i + 1);
			sep_path = path.substr(i);
		}
		if(seg == input)
		{
			return sep_path;
		}
		if(a != -1)
		{
			i = path.find("/", a + 1);
			if(i != -1)
			{
				seg = path.substr(a + 1, i - a - 1);
				sep_path = path.substr(i);
			}
			else{
				seg = path.substr(a + 1);
				sep_path = path.substr(a);
			}
		}
		if(seg == input)
		{
			return sep_path;
		}
	}
	return sep_path;
}

// Test & VTC functions

void test_vects(vector<directory> dir_vect, vector<file_> fil_vect)
{
	vector<directory>::iterator iter_dir = dir_vect.begin();
	vector<file_>::iterator iter_fil = fil_vect.begin();
	while(iter_dir != dir_vect.end() || iter_fil != fil_vect.end())
	{
		cout << "!!!\n"; 
		if(iter_dir != dir_vect.end())
		{
			iter_dir->get_dir();
			iter_dir++;
		}
		cout << endl;
		if(iter_fil != fil_vect.end())
		{
			iter_fil->get_file_();
			iter_fil++;
		}
		cout << endl;
	}
}

void output_VTC(vector<VTC> a_VTC)
{
	vector<VTC>::iterator iter_vtc = a_VTC.begin();
	while(iter_vtc != a_VTC.end())
	{
		cout << "Name: " << iter_vtc->get_name() << endl
			 << "Path: " << iter_vtc->get_path() << endl
			 << "(file_ only) Type: " << iter_vtc->get_type() << endl
			 << "size, in bytes: " << iter_vtc->get_size() << endl
			 << "(directory only) number of contents: " << iter_vtc->get_num() << endl << endl;
		iter_vtc++;
	}
}

vector<VTC> sce_test(vector<VTC> a_VTC) // size based error check, error inwhich an unformatted/incomplete object is passed to and held by the VTC
{
	int pos = 0, sce = 0;
	vector<VTC>::iterator iter_vtc = a_VTC.begin();

	while(iter_vtc != a_VTC.end())
	{
		if(iter_vtc->get_size() == sce && iter_vtc->get_num() == sce)
		{
			a_VTC.erase(a_VTC.begin() + pos);
			iter_vtc = a_VTC.begin() + --pos;
		}
		pos++;
		iter_vtc++;
	}
	return a_VTC;
}

vector<VTC> tc_test(vector<VTC> a_VTC) // twinning check, check to remove any dupilicate objects being held in the VTC
{
	bool single = true;
	int opos = 0, ipos = 0;
	vector<VTC>::iterator iter_vtc1 = a_VTC.begin(), iter_vtc2 = a_VTC.begin();

	while(iter_vtc1 != a_VTC.end())
	{
		while(iter_vtc2 != a_VTC.end())
		{

			if(iter_vtc2->get_path() == iter_vtc1->get_path()
				&& iter_vtc2->get_name() == iter_vtc1->get_name()
				&& iter_vtc2->get_type() == iter_vtc1->get_type())
			{
				if(!single)
				{
					a_VTC.erase(a_VTC.begin() + ipos);
					iter_vtc2 = a_VTC.begin() + --ipos;
				}				
				else{
					single = false;
				}
			}
			ipos++;
			iter_vtc2++;
		}
		++opos = ipos;
		iter_vtc1++;
		iter_vtc2 = a_VTC.begin() + opos;
	}
	return a_VTC;
}

// Primary functions

vector<VTC> explore(vector<VTC> VTC1)
{
    //***Introduction
    cout << "Explore module" << endl;

    string direct, dir = "";
    _finddata_t data;
    bool fin = false , re = true;
    vector<directory> dir_vect;
    vector<file_> fil_vect;
    int ff, last_slash, res, a = 0;
    string input1, input2, st_menu_str = "Any file or directory of interest?\nIf so enter file name or directory name.\nIf not enter name of directory to explore, or back to exit.",
		   str_backward = "If you want to return to the previous directory type return.";
	
    do{
        cout << "C:/" << dir << endl << endl;
        direct = "C:/" + dir + "/*.*";
        ff = _findfirst(direct.c_str(), &data);
        if(ff != -1)
        {
            res = 0;
            while(res != -1)
            {
				if(a < 3)
				{
					cout << right << setw(35) << data.name << " || ";
					a++;
				}
				else{
					cout << right << setw(25) << data.name << " || " << endl;
					a = 0;
				}
                res = _findnext(ff, &data);
            }
            _findclose(ff);
        }
		a = 0;
        cout << endl << endl << st_menu_str << endl;
		if(dir != "")
		{
			cout << str_backward << endl;
		}
        getline(cin, input1);

        direct = "C:/" + dir;
        re = check_input(input1, direct);
        if(input1 == "exit")
        {
            break;
        }
        else{
			if(input1 == "return")
			{
				last_slash = dir.find_last_of("/");
				dir = dir.substr(0, last_slash);
				cout << "returning to previous directory..." << endl;
			}
			else{
				if(re)
			    {
			        int found_dot = input1.find('.');
			        if(found_dot == -1)
			        {
			           do{
			                cout << "Of interest or explore?" << endl;
			                getline(cin, input2);
			                if(input2 == "of interest")
			                {
								direct = direct + "/" + input1;
			                    last_slash = direct.find_last_of('/');
			                    string name = direct.substr(last_slash + 1);
								string path = direct.substr(0, last_slash);
			                    int bs = byte_size(direct.c_str());
			                    int num_content = num_cont(direct.c_str());
			                    directory new_obj;
			                    new_obj.set_dir(name, path, bs, num_content);
			                    dir_vect.push_back(new_obj);
			                }
			                else{
			                    if(input2 == "explore")
			                    {
									dir = dir + "/" + input1;
			                        fin = true;
			                    }
			                    else{
			                        if(input2 == "back")
			                        {
			                            cout << "backing out..." << endl;
			                        }
			                        else{
			                            cout << "invalid.\noptions: back, explore, of interest" << endl;
			                        }
			                    }
			                }
			           }while(input2 != "back" && !fin);
			        }
			        else{
			            if(found_dot != -1)
			            {
			                do{
			                    cout << "Of interest or back?" << endl;
			                    getline(cin, input2);
			                    if(input2 == "of interest")
			                    {
									direct = direct + "/" + input1;
			                        last_slash = direct.find_last_of('/');
			                        int dot_marker = direct.find_last_of('.');
									string name = direct.substr(last_slash + 1, dot_marker); 
									string path = direct.substr(0, last_slash);
			                        ifstream conv_in(direct.c_str(), ifstream::ate | ifstream::binary);
			                        int file_bs = int(conv_in.tellg());
			                        string type = direct.substr(dot_marker);
			                        file_ new_fil;
			                        new_fil.set_file_(name, path, file_bs, type);
			                        fil_vect.push_back(new_fil);
			                        fin = true;
			                    }
			                    else{
			                        if(input2 == "back")
			                        {
			                            cout << "backing out..." << endl;
			                        }
			                        else{
			                            cout << "invalid." << endl;
			                        }
			                    }
			                }while(input2 != "back" && !fin);
			            }
			        }
			    }
			    else{
			        cout << "INVALID. input doesn't match possible files or directories." << endl;
			    }
			}
        }
		system("cls");
    }while(input1 != "exit");
	//test_vects(dir_vect, fil_vect);
	VTC1 = conv_to_VTC(dir_vect, fil_vect);
	system("cls");
	return VTC1;
}

void save_VTC(vector<VTC> a_VTC)
{
	vector<VTC>::iterator iter_vtc = a_VTC.begin();
	string save_directory = "C:/Users/spidercolony/Desktop/fm_dat/fm_saves";
	string data_type = "/.txt";
	string file_name;
	int leng, number_found = a_VTC.size();

	if(_mkdir(save_directory.c_str()) == 0)
	{
		cout << "creating directory." << endl;
	}
	else{
		cout << "directory located." << endl;
	}
	cout << "File name: " << endl;
	cin >> file_name;
	leng = save_directory.length();
	save_directory.insert(leng, data_type);
	save_directory.insert(leng + 1, file_name);
	cout << "save location is " << save_directory << endl;
	ofstream outfile(save_directory.c_str());
	number_found  = a_VTC.size();
	outfile << number_found << endl;
	while(iter_vtc != a_VTC.end())
	{
		outfile << iter_vtc->get_name() << "|" << iter_vtc->get_num() << "|"
			<< iter_vtc->get_path() << "|" << iter_vtc->get_size() << "|"
			<< iter_vtc->get_type() << endl;
		iter_vtc++;
	}
	outfile.close();
}

vector<VTC> load_VTC(vector<VTC> a_VTC) // do-while?
{
	int a = 0, number_found;
	string t_name; // transport name
	string t_path; // transport path
	string t_type; // transport type
	int t_size; // transport size(bytes)
	int t_num; // transport number of contents
	string *ptr_name, *ptr_path, *ptr_type;
	int *ptr_size, *ptr_num;
	_finddata_t data;
	ptr_name = &t_name;
	ptr_path = &t_path;
	ptr_type = &t_type;
	ptr_size = &t_size;
	ptr_num = &t_num;
	string m_numOsiz, catch_line, file_name, save_directory = "C:/Users/spidercolony/Desktop/fm_dat/fm_saves", save_fil_ext = ".txt";
	int f_bar, s_bar, t_bar, fo_bar, length_sd = save_directory.length();
	save_directory.insert(length_sd, "/*");
	length_sd = save_directory.length();
	save_directory.insert(length_sd, save_fil_ext.c_str());
	int c_ff = _findfirst(save_directory.c_str(), &data);
    if(c_ff != -1)
    {
        int c_res = 0;
        while(c_res != -1)
        {
            if(data.name != "." && data.name != ".." && a < 3)
				{
					cout << right << setw(35) << data.name << " || ";
					a++;
				}
				else{
					if(data.name != "." && data.name != "..")
					{
						cout << right << setw(25) << data.name << " || " << endl;
						a = 0;
					}
				}
            c_res = _findnext(c_ff, &data);
        }
        _findclose(c_res);
    }
	cout << "\n\nFile name: ";
	cin >> file_name;
	save_directory.erase(save_directory.end() - 5, save_directory.end());
	length_sd = save_directory.length();
	save_directory.insert(length_sd, file_name.c_str());
	ifstream infile(save_directory.c_str());
	getline(infile, catch_line);
	number_found = stoi(catch_line);
	for(int i = 0; i < number_found; i++)
	{
		getline(infile, catch_line);
		f_bar = catch_line.find('|');
		s_bar = catch_line.find('|', f_bar + 1);
		t_bar = catch_line.find('|', s_bar + 1);
		fo_bar = catch_line.find('|', t_bar + 1);
		*ptr_name = catch_line.substr(0, f_bar);
		m_numOsiz = catch_line.substr(f_bar + 1, s_bar - f_bar - 1);
		*ptr_num = stoi(m_numOsiz);
		*ptr_path = catch_line.substr(s_bar + 1, t_bar - s_bar - 1);
		m_numOsiz = catch_line.substr(t_bar + 1, fo_bar - t_bar - 1);
		*ptr_size = stoi(m_numOsiz);
		*ptr_type = catch_line.substr(fo_bar + 1);
		VTC load_VTC(t_name, t_path, t_size, t_num, t_type);
		a_VTC.push_back(load_VTC);
	}
	system("cls");
	return a_VTC;
}

void copy_df(vector<VTC> a_VTC) // copy file or directory, using of interest objects
{
	//***Introduction
	cout << "\nCopy file or directory main module" << endl;

	string input, target_path, new_fil, new_dir, copy_dir = "C:/Users/spidercolony/Desktop/fm_dat/fm_copies";
	bool found;
	vector<VTC>::iterator iter_vtc;

	do{
		iter_vtc = a_VTC.begin();
		while(iter_vtc != a_VTC.end())
		{
			cout << "\nName: " << iter_vtc->get_name() << endl;
			cout << "Path: " << iter_vtc->get_path() << endl;
			cout << "size, in bytes: " << iter_vtc->get_size() << endl;
			if(iter_vtc->get_type() == "d")
			{
				cout << "Number of contents: " << iter_vtc->get_num() << endl;
			}
			else{
				cout << "Type: " << iter_vtc->get_type() << endl;
			}
			iter_vtc++;
		}
		if(_mkdir(copy_dir.c_str()) == 0)
		{
			cout << "\ncreating directory." << endl;
		}
		else{
			cout << "\nDirectory located." << endl;
		}
		cout << "\n|Name of file or directory would you like to copy?\nor exit" << endl;
		getline(cin, input);

		if(input != "exit")
		{
			
			iter_vtc = a_VTC.begin();
			found = false;
			while(iter_vtc != a_VTC.end())
			{
				if(iter_vtc->get_name() == input)
				{
					target_path = iter_vtc->get_path() + "/" + iter_vtc->get_name();
					found = true;
					break;
				}
				iter_vtc++;
			}
			if(found)
			{
				if(input.find(".") != -1)
				{
					new_fil = copy_dir + "/" + iter_vtc->get_name();
					CopyFile(target_path.c_str(), new_fil.c_str(), TRUE);
				}
				else{
					new_dir = copy_dir + "/" + iter_vtc->get_name();
					_mkdir(new_dir.c_str());
					dir_copy(target_path, new_dir);
				}
			} 
			else{
				cout << "invalid." << endl;
			}
		}
		system("cls");
	}while(input != "exit");
	//CopyFile(target_path+name, copy_path+name, overwrite(FALSE)/DON'T(TRUE));
}

vector<VTC> rename_df(vector<VTC> a_VTC)
{
	string orig_path, seg_path_var, new_path, set_path, end_path, input, input1, new_name, type, pause_key;
	int a = 0, last_slash;
	vector<VTC>::iterator iter_vtc = a_VTC.begin();

	do{
		cout << "Names of files and directories in VTC vector." << endl << endl;
		while(iter_vtc != a_VTC.end())
		{
			if(a < 5)
			{
				cout << right << setw(20) << iter_vtc->get_name() << "|||";
				a++;
			}
			else{
				cout << endl <<  right << setw(20) << iter_vtc->get_name() << "|||";
				a = 0;
			}
			iter_vtc++;
		}
		cout << "\n\nEnter name of the directory or file to select.\nor enter exit." << endl;
		do{
			getline(cin, input);
		}while(input == "");

		if(input != "exit")
		{
			system("cls");
			iter_vtc = a_VTC.begin();
			while(iter_vtc != a_VTC.end())
			{
				if(iter_vtc->get_name() == input)
				{
					orig_path = iter_vtc->get_path() + "/" + iter_vtc->get_name();				
					cout << orig_path << endl;
					break;
				}
				iter_vtc++;
			}
			cout << "re-enter name. Or enter parent directory name to modify.\nor back." << endl;
			do{
				getline(cin, input1);
			}while(input1 == "");
			while(input1 != "back")
			{
				if(input1 == iter_vtc->get_name())
				{
					system("cls");
					cout << orig_path << endl << endl;
					cout << "New name:\n be sure to include .txt, .dat, etc as part of the name." << endl;
					getline(cin, new_name);
					last_slash = orig_path.find_last_of("/");
					new_path = orig_path.substr(0, last_slash + 1);
					new_path += new_name;
					if(rename (orig_path.c_str(), new_path.c_str()) == 0)
					{
						iter_vtc->set_name(new_name);
						input = new_name;
						cout << "rename of\n" << orig_path << "\nto\n" << new_path <<"\nhas been processed." << endl << endl;
						cout << "Enter ok to continue." << endl;
						cin >> pause_key;
						pause_key = "";
					}
					else{
						cout << "error." << endl;
					}
				}
				else{
					if(seg_path(input1, orig_path))
					{
						seg_path_var = sep_path(input1, orig_path);
						system("cls");
						cout << seg_path_var << endl;
						//cout << "sep_end_path:: " << sep_end_path(input1, orig_path) << endl;
						cout << "New name: ";
						getline(cin, new_name);
						last_slash = seg_path_var.find_last_of("/");
						new_path = seg_path_var.substr(0, last_slash + 1);
						new_path += new_name;
						if(rename (seg_path_var.c_str(), new_path.c_str()) == 0)
						{
							cout << "\nrename of\n" << seg_path_var << "\nto\n" << new_path <<"\nhas been processed." << endl << endl;
							cout << "Enter ok to continue." << endl;
							cin >> pause_key;
							pause_key = "";
							end_path = sep_end_path(input1, orig_path);
							last_slash = end_path.find_last_of("/");
							end_path = end_path.substr(0, last_slash);
							set_path = new_path + end_path;
							iter_vtc->set_path(set_path.c_str());
						}
						else{
							cout << "error." << endl;
							cout << "Enter ok to continue." << endl;
							cin >> pause_key;
							pause_key = "";
						}
					}
					else{
						cout << "Invalid." << endl;
					}
				}
				system("cls");
				iter_vtc = a_VTC.begin();
				while(iter_vtc != a_VTC.end())
				{
					if(iter_vtc->get_name() == input)
					{
						orig_path = iter_vtc->get_path() + "/" + iter_vtc->get_name();				
						cout << orig_path << endl;
						break;
					}
					iter_vtc++;
				}
				cout << "re-enter name. Or enter parent directory name to modify.\nor back." << endl;
				do{
					getline(cin, input1);
				}while(input1 == "");
			}
		}
		system("cls");
	}while(input != "exit");
	
	return a_VTC;
}