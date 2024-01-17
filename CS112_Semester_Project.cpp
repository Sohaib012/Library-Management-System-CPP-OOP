#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Classes.h"

using namespace std;

void get_lib_size() {
	fstream fin;
	
	fin.open("Library.csv", ios::in);
	
	string line;
	
	while(fin) {
		getline(fin,line);
		
		size_lib++;
	}
	
	fin.close();
}

void get_res_size() {
	fstream fin;
	
	fin.open("Reserved.csv", ios::in);
	
	string line;
	
	while(fin) {
		getline(fin,line);
		
		size_res++;
	}
	
	fin.close();
}

void do_again(Library* lib, Reserve* res) {
	Book* bk;

	cout << " *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n"
		<< "\tBook Title: || Author Name: || Copies Currently Remaining:\n"
		<< "\t----------------------------------------------------------\n";
		
	for(int i = 0; i < size_lib; i++) {
		bk = &lib[i];
		bk->show();
		bk++;
	}
	cout << " *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n";
	
	int reg_no;
	string act;
	bool tag = false;
	char redo;
	
	cout << "\nEnter your Registration number: ";
	cin >> reg_no;
	
	for(int i = 0; i < size_res; i++) {	
		if(reg_no == res[i].get_resby()) {
			tag = true;
		}
	}
	if(tag == true) {
		cout << "Welcome back, ";
	}
	else if(tag == false) {
		cout << "Welcome ";
	}
	
	cout << reg_no << " to the library.\n";
	
	Student stu(lib, res, reg_no);
	
	cout << "What would you like to do? [1.Reserve a new book, 2.Return a book, 3.Quit]: ";
	cin >> act;
	
	if(act == "1") {
		stu.reserve();
		
		cout << "Would you like to continue? [Y or N]: ";
		cin >> redo;
		
		if(redo == 'Y' || redo == 'y') {
			cout << "\nAfter changes, the Remaining Books Available are:\n";
			do_again(lib, res);
		}
	}
	else if(act == "2") {
		if(tag == false) {
			cout << "You have no books reserved from the library.\n";
		}
		else if(tag == true) {
			stu.return_bk();
		}
		
		cout << "Would you like to continue? [Y or N]: ";
		cin >> redo;
		
		if(redo == 'Y' || redo == 'y') {
			cout << "\nAfter changes, the Remaining Books Available are:\n";
			do_again(lib, res);
		}
	}
	else if(act == "3") {
		cout << "\nSee you next time.\n";
	}
	else {
		cerr << "\nWrong input, try again.\n";
		do_again(lib, res);
	}
}

void store(Library* lib, Reserve* res) {
	fstream fout;
	
	fout.open("Library.csv", ios::out);
	
	for(int i = 0; i < size_lib; i++) {
		fout << lib[i].get_bknam() << "," << lib[i].get_auth1stnam() << "," << lib[i].get_surnam() << "," << lib[i].get_copies() << endl;
	}
	
	fout.close();
	
	fout.open("Reserved.csv", ios::out);
	
	for(int i = 0; i < size_res; i++) {
		fout << res[i].get_resby() << "," << res[i].get_bknam() << "," << res[i].get_auth1stnam() << "," << res[i].get_surnam() << endl;
	}
	
	fout.close();
	
	cout << "\nThank you for using our Library.\n"
		<< " *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n";
}

int main() {
	get_lib_size();
	get_res_size();
	
	Library* lib = new Library[--size_lib];
	Reserve* res = new Reserve[--size_res];
	
	lib = initialize_lib();
	res = initialize_res();
	
	cout << "The Books Currently available are:\n";
	do_again(lib, res);
	
	store(lib, res);
}