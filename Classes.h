#ifndef CLASSES
#define CLASSES

// Including Libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// Globally defining the sizes of both Library and the Reserved books
int size_lib = 0;
int size_res = 0;

// Abstract Base Class Book
class Book {
protected:
	string bk_nam, auth_1stnam, sur_nam;
	
public:
	// Setter and Getter functions
	void set_bknam(string name) {
		bk_nam = name;
	}
	string get_bknam() {
		return bk_nam;
	}
	
	void set_auth1stnam(string name) {
		auth_1stnam = name;
	}
	string get_auth1stnam() {
		return auth_1stnam;
	}
	
	void set_surnam(string name) {
		sur_nam = name;
	}
	string get_surnam() {
		return sur_nam;
	}
	
	// Pure Virtual function show() causing the class to be Abstract
	virtual void show() = 0;
};

// Derived Class Library from Abstract Base Class Book
class Library : public Book {
protected:
	int copies;
	friend ostream &operator << (ostream &, Library &);
	
public:
	// Setter and Getter functions for the copies count
	void set_copies(int copy) {
		copies = copy;
	}
	int get_copies() {
		return copies;
	}
	
	// Redefinition of Pure Virtual function show()
	void show() {
		cout << "\t" << bk_nam << " || " << auth_1stnam << " " << sur_nam << " || " << copies << endl;
	}
};

// Friend function ostream
ostream &operator << (ostream &output, Library &temp) {
	output << "\t" << temp.bk_nam << " || " << temp.auth_1stnam << " " << temp.sur_nam << " || " << temp.copies << endl;
	
	return output;
}

// Derived Class Reserve from Abstract Base Class Book
class Reserve : public Book {
private:
	int res_by;
	friend ostream &operator << (ostream &, Reserve &);
	
public:
	// Setter and Getter functions for the Registreation numbers
	void set_resby(int reserve) {
		res_by = reserve;
	}
	int get_resby() {
		return res_by;
	}
	
	// Redifinition of Pure Virtual function show()
	void show() {
		cout << "\t" << res_by << " || " << bk_nam << " || " << auth_1stnam << " " << sur_nam << endl;
	}
};

// Friend function ostream
ostream &operator << (ostream &output, Reserve &temp) {
	output << "\t" << temp.res_by << " || " << temp.bk_nam << " || " << temp.auth_1stnam << " " << temp.sur_nam << endl;
	
	return output;
}

// Separate Class Student
class Student {
private:
	// Using Library and Reserve Objects
	Library* lib;
	Reserve* res;
	int reg_no;
	
public:
	// Constructor
	Student(Library* a, Reserve* b, int c) : lib{a}, res{b}, reg_no{c} {}
	
	//  Getter functions to get Library and Reserve
	Library* get_Library() {
		return lib;
	}
	
	Reserve* get_Reserve() {
		return res;
	}
	
	// Function for the student to reserve a book
	void reserve() {
		string name;
		bool tag = false, flag = true;
		
		cout << " *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n";
    	
    	// Display the Reserved books by the entered Registration number
    	for(int i = 0; i < size_res; i++) {
    		if(reg_no == res[i].get_resby()) {
    			cout << res[i];
			}
		}
		
		cout << "Enter the Book name for the book you wish to reserve or the Author's surname: ";
    	cin >> name;
		
		// This for-loop works and compares the given data
		for(int i = 0; i < size_lib; i++) {
			// If the book is found then this if statement works	
    		if(name == lib[i].get_bknam() || name == lib[i].get_surnam()) {
    			// For-loop to check if a book of this name has been already reserved by the entered Reg #
    			for(int j = 0; j < size_res; j++) {
    				if(reg_no == res[j].get_resby() && (name == res[j].get_bknam() || name == res[j].get_surnam())) {
    					tag = false;
    					flag = false;
    					break;
					}
				}
				// If the book was already registered by the entered Reg #
				if(flag == false) {
					break;
				}
    			tag = true;
    			// If the book has no available copies
    			if(lib[i].get_copies() == 0) {
    				flag == false;
				}
    			break;
			}
		}
		string book_name, auth1st_name, auth_surname;
		
		// If the book is available in the library and has available copies
		if(tag == true && flag == true) {
			for(int i = 0; i < size_lib; i++) {
				// Storing the book having the entered name in separate data members and decreasing the number of copies by one
				if(name == lib[i].get_bknam() || name == lib[i].get_surnam()) {
					lib[i].set_copies(lib[i].get_copies() - 1);
					book_name = lib[i].get_bknam();
					auth1st_name = lib[i].get_auth1stnam();
					auth_surname = lib[i].get_surnam();
					break;
				}
			}
			int regs[size_res];
			string booknames[size_res], auth1stnames[size_res], authsurnames[size_res];
			
			// Storing the existing data memebers in separate arrays
			for(int i = 0; i < size_res; i++) {
				regs[i] = res[i].get_resby();
				booknames[i] = res[i].get_bknam();
				auth1stnames[i] = res[i].get_auth1stnam();
				authsurnames[i] = res[i].get_surnam();
			}
			delete[] res;
			
			res = new Reserve[size_res + 1];
			
			// Storing the data back in the newly created array of one size greater
			for(int i = 0; i < size_res; i++) {
				res[i].set_resby(regs[i]);
				res[i].set_bknam(booknames[i]);
				res[i].set_auth1stnam(auth1stnames[i]);
				res[i].set_surnam(authsurnames[i]);
			}
			
			res[size_res].set_resby(reg_no);
			res[size_res].set_bknam(book_name);
			res[size_res].set_auth1stnam(auth1st_name);
			res[size_res].set_surnam(auth_surname);
			
			size_res++;
			
			cout << "The book has been reserved on your Registration Number.\n";
		}
		// If the book has already been reserved by the entered Reg #
		else if(tag == false && flag == false) {
			cerr << "You already have that book reserved.\n";
		}
		// If all the available copies have already been reserved
		else if(tag == true && flag == false) {
			cerr << "Unfortunately, all the available copies of that book have already been reserved.\n";
		}
		// If there is no book having that name in the library
		else if(tag == false && flag == true) {
			cerr << "There are no books of that name or Author's name in the library.\n";
		}
	}
	
	// Function for the student to return a book
	void return_bk() {
		string name;
		bool tag = false;
	
    	cout << " *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n";
    	
    	// Display the Reserved books by the entered Registration number
    	for(int i = 0; i < size_res; i++) {
    		if(reg_no == res[i].get_resby()) {
    			cout << res[i];
			}
		}
    	
    	cout << "Enter the Book name for the book you want to return or the Author's surname: ";
    	cin >> name;
    	
    	// Check if the book has been reserved by the entered Reg # or not
    	for(int i = 0; i < size_res; i++) {
    		if(reg_no == res[i].get_resby() && (name == res[i].get_bknam() || name == res[i].get_surnam())) {
    			tag = true;
    			break;
			}
		}
		// Book Reserved by the entered Reg #
		if(tag == true) {
			for(int i = 0; i < size_lib; i++) {
				if(name == lib[i].get_bknam() || name == lib[i].get_surnam()) {
					lib[i].set_copies(lib[i].get_copies() + 1);
					break;
				}
			}
			
			int j = 0;
			
			for(int i = 0; i < size_res; i++) {
				if(name == res[i].get_bknam() || name == res[i].get_surnam()) {
					continue;
				}
				else {
					res[j] = res[i];
					j++;
				}
			}
			size_res--;
			
			cout << "The book has been returned.\n";
		}
		// Book not Reserved by the entered Reg #
		else if(tag == false) {
			cerr << "You have no reserved books of that name or Author's name.\n";
		}
	}
};

// Function to Initialize the library array from the Library.csv
Library* initialize_lib() {
	fstream fin;

	Library* a = new Library[size_lib];
	
	fin.open("Library.csv", ios::in);
	
	string line, word;
	vector<string> row;
	
	for(int i = 0; i < size_lib; i++)
    {
        row.clear();

        getline(fin, line);

        stringstream s(line);

        while (getline(s, word, ','))
        {
            row.push_back(word);
        }   
        a[i].set_bknam(row[0]);
		a[i].set_auth1stnam(row[1]);
		a[i].set_surnam(row[2]);
		a[i].set_copies(stoi(row[3]));
	}
	fin.close();
	
	return a;
}

// Function to Initialize the Reserve array from the Reserved.csv
Reserve* initialize_res() {
	fstream fin;

	Reserve* b = new Reserve[size_res];
	
	fin.open("Reserved.csv", ios::in);
	
	string line, word;
	vector<string> row;
	
	for(int i = 0; i < size_res; i++)
    {
        row.clear();

        getline(fin, line);

        stringstream s(line);

        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        b[i].set_resby(stoi(row[0]));
        b[i].set_bknam(row[1]);
		b[i].set_auth1stnam(row[2]);
		b[i].set_surnam(row[3]);
	}
	fin.close();
	
	return b;
}

// Get the library array size from Library.csv file
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

// Get the reserve array size from Reserve.csv file
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

#endif