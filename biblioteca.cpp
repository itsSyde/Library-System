#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;

// Helper function to preprocess book names and search queries
string preprocess(const string& str) {
    string result;
    for (char c : str) {
        if (isalnum(c)) { // Check if character is alphanumeric
            result += tolower(c); // Convert to lowercase and add to result
        }
    }
    return result;
}

// Function to check user login credentials
bool userLogin(const string& userID, const string& password, string& userName) {
    ifstream file("users.txt");
    if (file.is_open()) {
        string storedID, storedPassword, name;
        while (file >> name >> storedID >> storedPassword) {
            if (userID == storedID && password == storedPassword) {
                userName = name;
                cout << "Welcome, " << name << "!" << endl;
                return true;
            }
        }
        cout << "Incorrect ID or password. Please try again." << endl;
        return false;
    } else {
        cout << "Error: Unable to open user database." << endl;
        return false;
    }
}

// Function to check admin login credentials
bool adminLogin(const string& adminID, const string& password) {
    ifstream file("admin.txt");
    if (file.is_open()) {
        string storedID, storedPassword;
        while (file >> storedID >> storedPassword) {
            if (adminID == storedID && password == storedPassword) {
                cout << "Welcome, Administrator!" << endl;
                return true;
            }
        }
        cout << "Incorrect admin ID or password. Please try again." << endl;
        return false;
    } else {
        cout << "Error: Unable to open admin database." << endl;
        return false;
    }
}

// Function to display all books stored in a file
void viewAllBooks(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string bookCode, bookStatus, bookName;
        while (file >> bookCode >> bookStatus >> bookName) {
            cout << "Book code: " << bookCode << " ----- " << "Status: " << bookStatus << " ----- " << "Book Name: " << bookName << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

// Function to handle book borrowing
void borrowBook(const string& userID) {
    cout << "Please enter the book code of the book you want to borrow: ";
    string bookCode;
    cin >> bookCode;

    ifstream bookFile("books.txt");
    ofstream tempFile("temp.txt");
    ofstream borrowedFile("borrowed_books.txt", ios::app);
    if (bookFile.is_open() && tempFile.is_open() && borrowedFile.is_open()) {
        string storedCode, status, bookName;
        bool bookFound = false;
        while (bookFile >> storedCode >> status >> bookName) {
            if (bookCode == storedCode) {
                bookFound = true;
                if (status == "Available") {
                    status = "N/A";
                    borrowedFile << userID << " " << bookCode << endl;
                    cout << "Great choice! You have booked " << bookName << "." << endl;
                } else {
                    cout << "Sorry, the book is unavailable." << endl;
                }
            }
            tempFile << storedCode << " " << status << " " << bookName << endl;
        }
        bookFile.close();
        tempFile.close();
        borrowedFile.close();

        remove("books.txt");
        rename("temp.txt", "books.txt");

        if (!bookFound) {
            cout << "Book with code " << bookCode << " not found." << endl;
        }
    } else {
        cout << "Unable to open books database." << endl;
    }
}

// Function to handle book returning
void returnBook(const string& userID) {
    cout << "Please enter the book code of the book you want to return: ";
    string bookCode;
    cin >> bookCode;

    ifstream bookFile("books.txt");
    ofstream tempFile("temp.txt");
    ifstream borrowedFile("borrowed_books.txt");
    ofstream tempBorrowedFile("temp_borrowed_books.txt");

    if (bookFile.is_open() && tempFile.is_open() && borrowedFile.is_open() && tempBorrowedFile.is_open()) {
        string storedCode, status, bookName;
        string borrowerID, borrowedCode;
        bool bookFound = false;
        bool validReturn = false;

        while (borrowedFile >> borrowerID >> borrowedCode) {
            if (borrowedCode == bookCode) {
                if (borrowerID == userID) {
                    validReturn = true;
                } else {
                    tempBorrowedFile << borrowerID << " " << borrowedCode << endl;
                }
            } else {
                tempBorrowedFile << borrowerID << " " << borrowedCode << endl;
            }
        }

        while (bookFile >> storedCode >> status >> bookName) {
            if (bookCode == storedCode) {
                bookFound = true;
                if (validReturn && status == "N/A") {
                    status = "Available";
                    cout << "Thank you for returning the book '" << bookName << "' with book code '" << bookCode << "'." << endl;
                } else if (!validReturn) {
                    cout << "You are not the one who borrowed this book or the book is already available." << endl;
                }
            }
            tempFile << storedCode << " " << status << " " << bookName << endl;
        }

        bookFile.close();
        tempFile.close();
        borrowedFile.close();
        tempBorrowedFile.close();

        remove("books.txt");
        rename("temp.txt", "books.txt");

        remove("borrowed_books.txt");
        rename("temp_borrowed_books.txt", "borrowed_books.txt");

        if (!bookFound) {
            cout << "Book with code " << bookCode << " not found." << endl;
        }
    } else {
        cout << "Unable to open databases." << endl;
    }
}

// Function to add a new book
void addBook() {
    // Automatically assigning the next available book code
    int nextBookCode = 1;
    ifstream bookFile("books.txt");
    if (bookFile.is_open()) {
        string code, status, name;
        while (bookFile >> code >> status >> name) {
            int bookCode = stoi(code);
            if (bookCode >= nextBookCode) {
                nextBookCode = bookCode + 1;
            }
        }
        bookFile.close();
    } else {
        cout << "Unable to open books database." << endl;
        return;
    }

    // Asking for the book's name
    cout << "Enter the name of the book: ";
    string name;
    cin.ignore(); // Clearing input buffer
    getline(cin, name);

    // Replace spaces with hyphens in the book name
    for (char& c : name) {
        if (c == ' ') {
            c = '-';
        }
    }

    // Appending the new book to the file
    ofstream bookFileAppend("books.txt", ios::app);
    if (bookFileAppend.is_open()) {
        bookFileAppend << nextBookCode << " Available " << name << endl;
        cout << "Book added successfully." << endl;
        bookFileAppend.close();
    } else {
        cout << "Unable to open books database." << endl;
    }
}

// Function to remove a book
void removeBook() {
    cout << "Enter the book code to remove: ";
    string code;
    cin >> code;
    
    ifstream inFile("books.txt");
    ofstream tempFile("temp.txt");
    if (inFile.is_open() && tempFile.is_open()) {
        string storedCode, status, name;
        bool bookFound = false;
        while (inFile >> storedCode >> status >> name) {
            if (code == storedCode) {
                bookFound = true;
                cout << "Book '" << name << "' with code " << code << " removed." << endl;
            } else {
                tempFile << storedCode << " " << status << " " << name << endl;
            }
        }
        inFile.close();
        tempFile.close();

        remove("books.txt");
        rename("temp.txt", "books.txt");

        if (!bookFound) {
            cout << "Book with code " << code << " not found." << endl;
        }
    } else {
        cout << "Unable to open books database." << endl;
    }
}

// Function to view all users
void viewAllUsers() {
    ifstream file("users.txt");
    if (file.is_open()) {
        string name, userID, password;
        while (file >> name >> userID >> password) {
            cout << "ID: " << userID << " ----- " << "User: " << name << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file: users.txt" << endl;
    }
}

// Function to add a new user
void addUser() {
    // Automatically assigning the next available user ID
    int nextUserID = 1;
    ifstream userFile("users.txt");
    if (userFile.is_open()) {
        string userID, name, password;
        while (userFile >> name >> userID >> password) {
            int currentID = stoi(userID);
            if (currentID >= nextUserID) {
                nextUserID = currentID + 1;
            }
        }
        userFile.close();
    } else {
        cout << "Unable to open user database." << endl;
        return;
    }

    // Asking for the user's name and password
    cout << "Enter name: ";
    string name;
    cin.ignore(); // Clearing input buffer
    getline(cin, name);
    
    cout << "Enter password: ";
    string password;
    cin >> password;

    // Appending the new user to the file
    ofstream userFileAppend("users.txt", ios::app);
    if (userFileAppend.is_open()) {
        userFileAppend << name << " " << nextUserID << " " << password << endl;
        cout << "User added successfully. Their ID is: " << nextUserID << endl;
        userFileAppend.close();
    } else {
        cout << "Unable to open user database." << endl;
    }
}

// Function to remove a user
void removeUser() {
    cout << "Enter the user ID to remove: ";
    string userID;
    cin >> userID;
    
    ifstream inFile("users.txt");
    ofstream tempFile("temp.txt");
    if (inFile.is_open() && tempFile.is_open()) {
        string name, storedID, password;
        bool userFound = false;
        while (inFile >> name >> storedID >> password) {
            if (userID == storedID) {
                userFound = true;
                cout << "User '" << name << "' with ID " << userID << " removed." << endl;
            } else {
                tempFile << name << " " << storedID << " " << password << endl;
            }
        }
        inFile.close();
        tempFile.close();

        remove("users.txt");
        rename("temp.txt", "users.txt");

        if (!userFound) {
            cout << "User with ID " << userID << " not found." << endl;
        }
    } else {
        cout << "Unable to open user database." << endl;
    }
}

// Function to search books by name
void searchBooksByName(const string& filename) {
    cout << "Enter the name of the book you are looking for: ";
    string searchName;
    cin.ignore(); // Clearing input buffer
    getline(cin, searchName);

    string processedSearchName = preprocess(searchName);

    ifstream file(filename);
    if (file.is_open()) {
        string bookCode, bookStatus, bookName;
        bool bookFound = false;
        while (file >> bookCode >> bookStatus >> bookName) {
            string processedBookName = preprocess(bookName);
            if (processedBookName.find(processedSearchName) != string::npos) {
                cout << "Book code: " << bookCode << " ----- " << "Status: " << bookStatus << " ----- " << "Book Name: " << bookName << endl;
                bookFound = true;
            }
        }
        file.close();
        if (!bookFound) {
            cout << "No book found with the name: " << searchName << endl;
        }
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

int main() {
    while (true) {
        cout << "----------------------------------------------------" << endl;
        cout << "              Welcome to Bibioteca!                 " << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Please select one of the following options:" << endl;
        cout << "1) Log in as User" << endl;
        cout << "2) Log in as Administrator" << endl;
        cout << "3) Exit" << endl;
        cout << "----------------------------------------------------" << endl;

        int loginChoice;
        cin >> loginChoice;

        string userID, password, userName;

        if (loginChoice == 1) {
            // User login
            cout << "Please enter your user ID: ";
            cin >> userID;
            cout << "Please enter your password: ";
            cin >> password;

            if (!userLogin(userID, password, userName)) {
                continue;
            }

            // Options Menu for Users
while (true) {
    cout << "----------------------------------------------------" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1) View all Books" << endl;
    cout << "2) Borrow a Book" << endl;
    cout << "3) Return a Book" << endl;
    cout << "4) Search for a Book by Name" << endl; // New option
    cout << "5) Logout" << endl;
    cout << "----------------------------------------------------" << endl;

    int choice;
    cin >> choice;

    if (choice == 1) {
        viewAllBooks("books.txt");
    } else if (choice == 2) {
        borrowBook(userID);
    } else if (choice == 3) {
        returnBook(userID);
    } else if (choice == 4) {
        searchBooksByName("books.txt"); // New feature call
    } else if (choice == 5) {
        break; // Logout
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}

        } else if (loginChoice == 2) {
            // Administrator login
            cout << "Please enter your admin ID: ";
            cin >> userID;
            cout << "Please enter your password: ";
            cin >> password;
            if (userID == "admin" && password == "adminpass") {
                cout << "Administrator login successful." << endl;

                // Options Menu for Administrators
                while (true) {
                    cout << "----------------------------------------------------" << endl;
                    cout << "What would you like to do?" << endl;
                    cout << "1) View all Books" << endl;
                    cout << "2) Add a Book" << endl;
                    cout << "3) Remove a Book" << endl;
                    cout << "4) View all Users" << endl;
                    cout << "5) Add a User" << endl;
                    cout << "6) Remove a User" << endl;
                    cout << "7) Logout" << endl;
                    cout << "----------------------------------------------------" << endl;

                    int choice;
                    cin >> choice;

                    if (choice == 1) {
                        viewAllBooks("books.txt");
                    } else if (choice == 2) {
                        addBook();
                    } else if (choice == 3) {
                        removeBook();
                    } else if (choice == 4) {
                        viewAllUsers();
                    } else if (choice == 5) {
                        addUser();
                    } else if (choice == 6) {
                        removeUser();
                    } else if (choice == 7) {
                        break; // Logout
                    } else {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            } else {
                cout << "Incorrect admin ID or password. Please try again." << endl;
            }
        } else if (loginChoice == 3) {
            break; // Exit program
        } else
         {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

