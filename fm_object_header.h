// file manipulator object header file
#ifndef FM_OBJECT_HEADER_H_INCLUDED
#define FM_OBJECT_HEADER_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;

class File
{
private:
	string name;
	string path;
	int file_size; // size in Visual C++ = file_size in CodeBlocks
protected:
	string *ptr_name;
	string *ptr_path;
	int *ptr_size;
public:
	void set_name(string a_name);
	void set_path(string a_path);
	void set_size(int a_size);
	void set_all(string a_name, string a_path, int a_size);
	string get_name();
	string get_path();
	int get_size();
	void get_all();
	File() {name = ""; path = ""; file_size = 0;}; //file_size = size(in VSC++)
	File(string a_name, string a_path, int a_size)
		{name = a_name; path = a_path; file_size = a_size;};
	~File() {cout<<"\ndestructing File object" << endl; };
};

class directory : public File
{
private:
	int num_of_content; // number of files contained in the directory
protected:
	int *ptr_num;
public:
	void set_num_content(int a_num);
	void set_dir(string a_name, string a_path, int a_size, int a_num);
	int get_num_content();
	void get_dir();
	directory() {num_of_content = 0;};
	directory(string a_name, string a_path, int a_size, int a_num)
			 {File(a_name, a_path, a_size); num_of_content = a_num;};
	~directory() {cout<<"\ndestructing directory object\n";};
};

class file_ : public File
{
private:
	string type;
protected:
	string *ptr_type;
public:
	void set_type(string a_type);
	void set_file_(string a_name, string a_path, int a_size, string a_type);
	string get_type();
	void get_file_();
	file_() {type = "";};
	file_(string a_name, string a_path, int a_size, string a_type)
		 {File(a_name, a_path, a_size); type = a_type;};
	~file_() {cout<<"\ndestructing file_ object\n";};
};

// File function declarations
void File::set_name(string a_name)
{
	ptr_name = &a_name;
	name = *ptr_name;
	ptr_name = 0;
}
void File::set_path(string a_path)
{
	ptr_path = &a_path;
	path = *ptr_path;
	ptr_path = 0;
}
void File::set_size(int a_size)
{
	ptr_size = &a_size;
	file_size = *ptr_size; // file_size = size(in VSC++)
	ptr_size = 0;
}
void File::set_all(string a_name, string a_path, int a_size)
{
	set_name(a_name);
	set_path(a_path);
	set_size(a_size);
}
string File::get_name()
{
	ptr_name = &name;
	return *ptr_name;
	ptr_name = 0;
}
string File::get_path()
{
	ptr_path = &path;
	return *ptr_path;
	ptr_path = 0;
}
int File::get_size()
{
	ptr_size = &file_size; // file_size = size(in VSC++)
	return *ptr_size;
	ptr_size = 0;
}
void File::get_all()
{
	cout << "Name: " << get_name() << "\nPath: " << get_path()
		 << "\nSize: " << get_size() << endl;
}
// directory function declarations
void directory::set_num_content(int a_num)
{
	ptr_num = &a_num;
	num_of_content = *ptr_num;
	ptr_num = 0;
}
void directory::set_dir(string a_name, string a_path, int a_size, int a_num)
{
	set_all(a_name, a_path, a_size);
	set_num_content(a_num);
}
int directory::get_num_content()
{
	ptr_num = &num_of_content;
	return *ptr_num;
	ptr_num = 0;
}
void directory::get_dir()
{
	get_all();
	cout << "Number of Contents: " << get_num_content() << endl;
}
// file_ function declarations
void file_::set_type(string a_type)
{
	ptr_type = &a_type;
	type = *ptr_type;
	ptr_type = 0;
}
void file_::set_file_(string a_name, string a_path, int a_size, string a_type)
{
	set_all(a_name, a_path, a_size);
	set_type(a_type);
}
string file_::get_type()
{
	ptr_type = &type;
	return *ptr_type;
	ptr_type = 0;
}
void file_::get_file_()
{
	get_all();
	cout << "file type: " << get_type() << endl;
}

// VECTOR TRANSPORTATION CLASS
class VTC 
{
private:
	string name;
	string path;
	string type;
	int file_size;
	int num_of_content;
protected:
	string *ptr_name;
	string *ptr_path;
	string *ptr_type;
	int *ptr_size;
	int *ptr_num;
public:
	void set_name(string a_name);
	void set_path(string a_path);
	void set_type(string a_type);
	void set_size(int a_size);
	void set_num(int a_num);
	string get_name();
	string get_path();
	string get_type();
	int get_size();
	int get_num();
	VTC(){name = ""; path = ""; type = ""; file_size = 0; num_of_content = -1;};
	VTC(string a_name, string a_path, int a_size, int a_num)
		{name = a_name; path = a_path; file_size = a_size; num_of_content = a_num; type = "d";}; // d for directory
	VTC(string a_name, string a_path, int a_size, string a_type)
		{name = a_name; path = a_path; file_size = a_size; type = a_type; num_of_content = -1;};
	VTC(string a_name, string a_path, int a_size, int a_num, string a_type)
		{name = a_name; path = a_path; file_size = a_size; num_of_content = a_num; type = a_type;}
	~VTC(){};

};

//VTC Functions
void VTC::set_name(string a_name)
{
	ptr_name = &a_name;
	name = *ptr_name;
	ptr_name = 0;
}
void VTC::set_path(string a_path)
{
	ptr_path = &a_path;
	path = *ptr_path;
	ptr_path = 0;
}
void VTC::set_type(string a_type)
{
	ptr_type = &a_type;
	type = *ptr_type;
	ptr_type = 0;
}
void VTC::set_size(int a_size)
{
	ptr_size = &a_size;
	file_size = *ptr_size; // file_size = size(in VSC++)
	ptr_size = 0;
}
void VTC::set_num(int a_num)
{
	ptr_num = &a_num;
	num_of_content = *ptr_num;
	ptr_num = 0;
}
string VTC::get_name()
{
	ptr_name = &name;
	return *ptr_name;
	ptr_name = 0;
}
string VTC::get_path()
{
	ptr_path = &path;
	return *ptr_path;
	ptr_path = 0;
}
string VTC::get_type()
{
	ptr_type = &type;
	return *ptr_type;
	ptr_type = 0;
}
int VTC::get_size()
{
	ptr_size = &file_size; // file_size = size(in VSC++)
	return *ptr_size;
	ptr_size = 0;
}
int VTC::get_num()
{
	ptr_num = &num_of_content;
	return *ptr_num;
	ptr_num = 0;
}

#endif
