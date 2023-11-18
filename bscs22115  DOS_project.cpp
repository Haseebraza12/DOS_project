#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
#include<vector>
#include<algorithm>
#include<ctime>
#include <stdexcept>

using namespace std;
void introduction()
{
	cout << "\t\t\t\tCoded by:" << "Haseeb-Ur-Rehman & Ibrahim Nadeem" << endl;
	cout << "\t\t\t\tRoll No:" << "bscs22115 & bscs22071" << endl;
}   
class DOS
{
private:
    void displayPrompt() const
    {
        cout << "V:\\> ";
    }
    struct Folder
    {
        string Folder_Name;
        Folder* parent;
        time_t creation_time;
        string path;
        string owner;
        bool ishidden;
        map<string, Folder*> subfolders;  // Map to store subfolders
        map<string, File*> files;

    };
    struct File
    {
        string File_Name;
        Folder* parentFolder;
        time_t creation_time;
        string path;
        string owner;
        int size;

    };
	
	struct Tree
	{
        Folder* root;
	};
   
public:
    void run() {
        cout << "\"From The River To The Sea..Hamas\"" << endl;
        while (true) {
            displayPrompt();

            string userInput;
            getline(cin, userInput);
/*
            if (userInput == "exit") {
                cout << "Exiting program." << endl;
                break;
            }
            if (userInput == "list") {
                cout << "Listing files in virtual drive..." << endl;
            }
            else if (userInput.substr(0, 3) == "cd ") {
                // Implement change directory logic
                string newDirectory = userInput.substr(3);
                cout << "Changing directory to " << newDirectory << "..." << endl;
            }
            else {
                cout << "Command not recognized: " << userInput << endl;
            }*/
        }
    }
   
	
};
int main()
{
    introduction();
    DOS ds;
    ds.run();
    
   
}