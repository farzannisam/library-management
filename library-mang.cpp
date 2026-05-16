#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book
{
private:
    int bookID;
    char title[50];
    char author[50];
    char publisher[50];
    float price;
    int quantity;
    int available;
    char category[30];

public:

    void addBook()
    {
        cout << "\nEnter Book ID: ";
        cin >> bookID;

        cin.ignore();

        cout << "Enter Book Title: ";
        cin.getline(title, 50);

        cout << "Enter Author Name: ";
        cin.getline(author, 50);

        cout << "Enter Publisher: ";
        cin.getline(publisher, 50);

        cout << "Enter Category: ";
        cin.getline(category, 30);

        cout << "Enter Price: ";
        cin >> price;

        cout << "Enter Quantity: ";
        cin >> quantity;

        available = quantity;

        cout << "\nBook Added Successfully!\n";
    }

    void displayBook()
    {
        cout << "\n===================================";
        cout << "\nBook ID      : " << bookID;
        cout << "\nTitle        : " << title;
        cout << "\nAuthor       : " << author;
        cout << "\nPublisher    : " << publisher;
        cout << "\nCategory     : " << category;
        cout << "\nPrice        : " << price;
        cout << "\nQuantity     : " << quantity;
        cout << "\nAvailable    : " << available;
        cout << "\n===================================\n";
    }

    int getBookID()
    {
        return bookID;
    }

    char* getTitle()
    {
        return title;
    }

    char* getAuthor()
    {
        return author;
    }

    void issueBook()
    {
        if(available > 0)
        {
            available--;

            cout << "\nBook Issued Successfully!\n";
        }
        else
        {
            cout << "\nBook Not Available!\n";
        }
    }

    void returnBook()
    {
        if(available < quantity)
        {
            available++;

            cout << "\nBook Returned Successfully!\n";
        }
        else
        {
            cout << "\nAll Copies Already Present!\n";
        }
    }

    void updateBook()
    {
        cin.ignore();

        cout << "\nEnter New Publisher: ";
        cin.getline(publisher, 50);

        cout << "Enter New Price: ";
        cin >> price;

        cout << "Enter New Quantity: ";
        cin >> quantity;

        if(available > quantity)
        {
            available = quantity;
        }

        cout << "\nBook Updated Successfully!\n";
    }
};

void addBookRecord()
{
    Book b;

    ofstream outFile("library.dat", ios::binary | ios::app);

    b.addBook();

    outFile.write(reinterpret_cast<char*>(&b), sizeof(b));

    outFile.close();
}

void displayBooks()
{
    Book b;

    ifstream inFile("library.dat", ios::binary);

    while(inFile.read(reinterpret_cast<char*>(&b), sizeof(b)))
    {
        b.displayBook();
    }

    inFile.close();
}

void searchBook()
{
    Book b;

    char keyword[50];

    bool found = false;

    cin.ignore();

    cout << "\nEnter Book Title or Author: ";
    cin.getline(keyword, 50);

    ifstream inFile("library.dat", ios::binary);

    while(inFile.read(reinterpret_cast<char*>(&b), sizeof(b)))
    {
        if(strcmp(b.getTitle(), keyword) == 0 ||
           strcmp(b.getAuthor(), keyword) == 0)
        {
            b.displayBook();

            found = true;
        }
    }

    inFile.close();

    if(!found)
    {
        cout << "\nBook Not Found!\n";
    }
}

void issueBookRecord()
{
    Book b;

    int id;

    bool found = false;

    cout << "\nEnter Book ID to Issue: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    while(file.read(reinterpret_cast<char*>(&b), sizeof(b)))
    {
        if(b.getBookID() == id)
        {
            b.issueBook();

            int pos = (-1) * static_cast<int>(sizeof(b));

            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&b), sizeof(b));

            found = true;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nBook Not Found!\n";
    }
}

void returnBookRecord()
{
    Book b;

    int id;

    bool found = false;

    cout << "\nEnter Book ID to Return: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    while(file.read(reinterpret_cast<char*>(&b), sizeof(b)))
    {
        if(b.getBookID() == id)
        {
            b.returnBook();

            int pos = (-1) * static_cast<int>(sizeof(b));

            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&b), sizeof(b));

            found = true;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nBook Not Found!\n";
    }
}

void updateBookRecord()
{
    Book b;

    int id;

    bool found = false;

    cout << "\nEnter Book ID to Update: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    while(file.read(reinterpret_cast<char*>(&b), sizeof(b)))
    {
        if(b.getBookID() == id)
        {
            b.updateBook();

            int pos = (-1) * static_cast<int>(sizeof(b));

            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&b), sizeof(b));

            found = true;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nBook Not Found!\n";
    }
}

void deleteBookRecord()
{
    Book b;

    int id;

    bool found = false;

    cout << "\nEnter Book ID to Delete: ";
    cin >> id;

    ifstream inFile("library.dat", ios::binary);

    ofstream outFile("temp.dat", ios::binary);

    while(inFile.read(reinterpret_cast<char*>(&b), sizeof(b)))
    {
        if(b.getBookID() == id)
        {
            found = true;
        }
        else
        {
            outFile.write(reinterpret_cast<char*>(&b), sizeof(b));
        }
    }

    inFile.close();

    outFile.close();

    remove("library.dat");

    rename("temp.dat", "library.dat");

    if(found)
    {
        cout << "\nBook Deleted Successfully!\n";
    }
    else
    {
        cout << "\nBook Not Found!\n";
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n====================================";
        cout << "\n     LIBRARY MANAGEMENT SYSTEM";
        cout << "\n====================================";

        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Update Book";
        cout << "\n7. Delete Book";
        cout << "\n8. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addBookRecord();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                issueBookRecord();
                break;

            case 5:
                returnBookRecord();
                break;

            case 6:
                updateBookRecord();
                break;

            case 7:
                deleteBookRecord();
                break;

            case 8:
                cout << "\nExiting Program...\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 8);

    return 0;
}