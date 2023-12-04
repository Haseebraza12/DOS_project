#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include<windows.h>
#include<fstream>
using namespace std;

class DOS
{
private:
    void introduction()
    {
        cout << "\t\t\t\tAuthor: Haseeb-Ur-Rehman & Ibrahim Nadeem" << endl;
        cout << "\t\t\t\tRoll No: bscs22115 & bscs22071" << "\n\n";
        cout << "Apni personal Windows [Version 10.0.18363.900]\n"
            << "(v)2023 Apni Corporation.All rights reserved.\n\n";
    }

    string ToLower(string s)
    {
        for (int i = 0; i < s.size(); i++)
        {
            s[i] = tolower(s[i]);
        }
        return s;
    }
    void version() const
    {
        cout << "DOS Program Version: 10.0.18363.900" << endl;
    }
    void SetConsoleColor()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    }


    class File
    {
    public:
        string name;
        vector<File*> Files;
        File* parent;
        bool hidden;
        time_t creation_time;
        string path;
        File(string n = "", string p = "", File* parent = nullptr, vector<File*> Fls = vector<File*>())
        {
            name = n;
            this->parent = parent;
            Files = Fls;
            hidden = false;
            path = p;
        }
    };

    class Folder
    {
    public:
        string name;
        vector<Folder*> Folders;
        vector<File*> Files;
        Folder* parent;
        bool hidden;
        time_t creation_time;
        string path;

        Folder(string n = "", string p = "", Folder* parent = nullptr, vector<Folder*> Fdr = vector<Folder*>(), vector<File*> Fls = vector<File*>()) {
            name = n;
            this->parent = parent;
            Folders = Fdr;
            Files = Fls;
            hidden = false;
            path = p;
            creation_time = time(nullptr);  // Set creation_time to the current time
        }

        void remove_file(string name)
        {
            for (int i = 0; i < Files.size(); i++)
            {
                if (Files[i]->name == name)
                {
                    swap(Files[i], Files[Files.size() - 1]);
                    Files.pop_back();
                }
            }
        }

        void remove_directory_recursive()
        {
            // Remove files in the current directory
            Files.clear();

            // Recursively remove subdirectories
            for (Folder* subfolder : Folders)
            {
                subfolder->remove_directory_recursive();
            }

            // Clear the list of subdirectories
            Folders.clear();
        }

        void remove_folder(string name)
        {
            for (int i = 0; i < Folders.size(); i++)
            {
                if (Folders[i]->name == name)
                {
                    swap(Folders[i], Folders[Folders.size() - 1]);
                    Folders.pop_back();
                }
            }
        }

        void Empty_dir()
        {
            Files.clear();
            Folders.clear();
        }

        File* find_file(string name)
        {
            for (int i = 0; i < Files.size(); i++)
            {
                if (Files[i]->name == name)
                {
                    return Files[i];
                }
            }
            return nullptr;
        }

        Folder* find_folder(string name)
        {
            for (int i = 0; i < Folders.size(); i++)
            {
                if (Folders[i]->name == name)
                {
                    return Folders[i];
                }
            }
            return nullptr;
        }

        void insert_folder(Folder* F)
        {
            Folders.push_back(F);
        }

        void insert_file(File* F)
        {
            Files.push_back(F);
        }
    };

    class Tree
    {
    public:
        Folder* root;
        Folder* CF;

        Tree()
        {
            root = new Folder("V");
            CF = root;
        }

        void Insert(Folder* F)
        {
            CF->Folders.push_back(F);
            // CF = F; // Move into the newly created folder
            // Print the updated path
            Print("\\>");
        }

        void Path(Folder* F)
        {
            string _path = CF->name;
            Folder* _parent = CF->parent;
            while (_parent != nullptr)
            {
                _path = _parent->name + "/" + _path;
                _parent = _parent->parent;
            }
            F->path = _path;
        }

        void Print(string prompt = "\\>")
        {
            if (CF->name == "V")
                cout << "V:" << prompt;
            else
                cout << "V:" << CF->path.substr(2, CF->path.length()) << "\\" << CF->name << prompt;
        }

        bool Folder_Check(string name)
        {
            for (int i = 0; i < CF->Folders.size(); i++)
            {
                if (CF->Folders[i]->name == name)
                    return true;
            }
            return false;
        }

        void ChangeDirectory(string dir)
        {
            if (dir == ".")
            {
                // Print working directory
                Print("\\>");
            }
            else if (dir == "..")
            {
                // Move to the previous directory
                if (CF->parent != nullptr)
                {
                    CF = CF->parent;
                    Print("\\>");
                }
                else
                {
                    cout << "Already at the root directory." << endl;
                }
            }
            else if (dir == "\\")
            {
                // Move to the root directory
                CF = root;
                Print("\\>");
            }
            else
            {
                // Change to the specified directory
                Folder* newDir = CF->find_folder(dir);
                if (newDir != nullptr)
                {
                    CF = newDir;
                    Print("\\>");
                }
                else
                {
                    cout << "Directory not found: " << dir << endl;
                }
            }
        }
        void Remove_Directory(string dir)
        {
            // Find the directory to be removed
            Folder* dirToRemove = CF->find_folder(dir);

            if (dirToRemove != nullptr)
            {
                // Remove the directory and its content recursively
                dirToRemove->remove_directory_recursive();

                // Remove the directory from the parent's list of subdirectories
                CF->remove_folder(dir);

                cout << "Directory removed successfully: " << dir << endl;
                Print("\\>");
            }
            else
            {
                cout << "Directory not found: " << dir << endl;
            }
        }

        void DisplayDirectoryContents()
        {
            // Display subdirectories
            cout << "Directories:" << endl;
            for (Folder* subfolder : CF->Folders)
            {
                cout << "  <DIR>   " << subfolder->name << endl;
            }

            // Display files
            cout << "Files:" << endl;
            for (File* file : CF->Files)
            {
                cout << "         " << file->name << endl;
            }
        }
        void print_tree(Folder* node) const
        {
            if (node == nullptr)
            {
                cout << "Invalid directory." << endl;
                return;
            }
            string sp = "-";

            cout << sp << " Directory of V:\\" << ((node->parent) ? node->parent->name : "") << "\\" << node->name << endl;

            for (int i = 0; i < node->Folders.size(); ++i)
            {
                cout << sp << "---DIR>\t" << node->Folders[i]->name << endl;
            }

            for (int i = 0; i < node->Files.size(); ++i)
            {
                cout << sp << "----" << node->Files[i]->name << endl;
            }

            for (int i = 0; i < node->Folders.size(); ++i)
            {
                print_tree(node->Folders[i]);
                cout << sp + "----";
            }
        }
        void Create_File(string fileName)
        {
            // Check if the file already exists
            if (CF->find_file(fileName) != nullptr)
            {
                cout << "File already exists: " << fileName << endl;
                Print("\\>");
                return;
            }

            // Create a new file with the full path
            File* newFile = new File(fileName, CF->path + "\\" + CF->name + "\\" + fileName, nullptr);

            // Prompt the user to enter contents for the file
            cout << "Enter the contents of the file. Type '\\end' on a new line to finish." << endl;

            string line;
            while (getline(cin, line))
            {
                if (line == "\\end")
                {
                    break;
                }
                newFile->name += "\n" + line;
            }

            // Insert the new file into the current directory
            CF->insert_file(newFile);

            cout << "File created successfully: " << fileName << endl;
            Print("\\>");
        }
        void delete_File(string fileName)
        {
            // Find the file to be deleted
            File* fileToDelete = nullptr;

            for (File* file : CF->Files)
            {
                if (file->name == fileName || file->path == CF->path + "\\" + CF->name + "\\" + fileName)
                {
                    fileToDelete = file;
                    break;
                }
            }

            if (fileToDelete != nullptr)
            {
                // Remove the file from the current directory
                CF->remove_file(fileName);

                cout << "File deleted successfully: " << fileName << endl;
                Print("\\>");
            }
            else
            {
                cout << "File not found: " << fileName << endl;
                Print("\\>");
            }
        }
        void Format_everything()
        {
            // Remove files in the current directory
            root->Files.clear();

            // Recursively remove subdirectories
            for (Folder* subfolder : root->Folders)
            {
                subfolder->remove_directory_recursive();
            }

            // Clear the list of subdirectories
            root->Folders.clear();

            CF = root;  // Set current folder back to the root
            cout << "Directory formatted successfully." << endl;
            Print("\\>");
        }
        void Rename_File(string currentName, string newName)
        {
            // Find the file to be renamed
            File* fileToRename = nullptr;

            for (File* file : CF->Files)
            {
                if (file->name == currentName || file->path == CF->path + "\\" + CF->name + "\\" + currentName)
                {
                    fileToRename = file;
                    break;
                }
            }

            if (fileToRename != nullptr)
            {
                // Update the file's name
                fileToRename->name = newName;

                cout << "File renamed successfully: " << currentName << " to " << newName << endl;
                Print("\\>");
            }
            else
            {
                cout << "File not found: " << currentName << endl;
                Print("\\>");
            }
        }
        void PrintWorkingDirectory()
        {
            cout << "Current directory: " << CF->path << "\\" << CF->name << endl;
        }
       


 
        void help()
        {
            string helpInfo = R"(
            ATTRIB      Displays file (name provided as input) attributes.
            CD          Displays the name of or changes the current directory. See details below.
            CD.         Prints working directory (i.e. your current directory in your tree structure)
            CD..        Change directory to the previous directory
            CD\         Changes directory to the root directory (i.e. V:\>)
            CONVERT     Asks two types and converts the extension of all files of one type to another type.
            COPY        Copies one file in the current directory to another location (directory). See details below.
            CREATE      Creates a file with the name provided and allows the user to enter contents of the file.
            DEL         Deletes a file whose name is provided in input.
            DIR         Displays a list of files and subdirectories in a directory.
            EDIT        Opens a file (loads into a linked list) and allows the user to edit and save the contents of the file. See bullet 5 below
            EXIT        Quits the program
            FIND        Searches for a file in your current virtual directory whose name is provided as input.
            FINDF       Searches for a text string in the currently open file or the file whose name is provided as input.
            FINDSTR     Searches for strings in all files of your current virtual directory, prints names of files with the string
            FORMAT      Formats the current virtual directory i.e. empties the current directory and all subdirectories.
            HELP        Provides Help information for all these commands.
            LOADTREE    Load a given tree in your tree structure. Given tree is in a file named tree.txt
            MKDIR       Creates a virtual directory.
            MOVE        Moves one file (whose name is provided as input) from one directory to another directory.
            PPRINT      Adds a text file to the priority-based print queue and displays the current priority queue.
            PROMPT      Changes the Windows command prompt (for example from V:\> to V$).
            PRINT       Adds a text file to the print queue and displays the current queue.
            PQUEUE      Shows the current state of the priority-based print queue, with time left for each element
            PWD         Prints working directory
            QUEUE       Shows the current state of the print queue, with time left for each element
            RENAME      Renames a file whose current and new name are provided as input.
            RMDIR       Removes a directory along with its contents. Consider setting the respective sibling links 
            SAVE        Saves the currently open file to disk.
            TREE        Displays the complete directory structure.
            VER         Displays the version of your program.
        )";
            cout << helpInfo << endl;
        }
    };

public:
    Tree t;

    DOS() {}

    void Print()
    {

        t.Print();
    }

    void run()
    {
        introduction();
        Print();
        bool quit = false;
        while (!quit)
        {
            quit = input();
        }
    }


    bool input()
    {
        string cmd;
        getline(cin, cmd);

        // Check if there is a space in the command
        size_t spacePos = cmd.find(' ');
        string opt = (spacePos != string::npos) ? cmd.substr(0, spacePos) : cmd;

        opt = ToLower(opt);

        if (opt == "mkdir")
        {
            // Extract the folder name after "mkdir "
            string folderName = (spacePos != string::npos) ? cmd.substr(spacePos + 1) : "";
            t.Insert(new Folder(folderName, t.CF->path + "\\" + t.CF->name, t.CF));
        }
        else if (opt == "attrib")
        {
            // Extract the file name after "attrib "
            string fileName = (spacePos != string::npos) ? cmd.substr(spacePos + 1) : "";
            File* file = t.CF->find_file(fileName);
            if (file != nullptr)
            {
                // Display file attributes or perform other actions as needed
                cout << "Attributes for file " << file->name << ": [Implement your logic here]" << endl;
            }
            else
            {
                cout << "File not found: " << fileName << endl;
            }
        }
        else if (opt == "cd")
        {
            // Extract the directory name after "cd "
            string dirName = (spacePos != string::npos) ? cmd.substr(spacePos + 1) : "";
            t.ChangeDirectory(dirName);
        }
        else if (opt == "cd.")
        {
            // Print working directory
            t.Print("\\>");
        }
        else if (opt == "help")
        {
            t.help();
            t.Print("\\>");
        }
        else if (opt == "exit")
        {
            return true;
        }
        else if (opt == "color")
        {
            SetConsoleColor();
            t.Print("\\>");
        }
        else if (opt == "cd..")
        {
            t.ChangeDirectory("..");
        }
        else if (opt == "cd\\")  // Check for "CD\" command
        {
            t.ChangeDirectory("\\");
        }
        else if (opt == "rmdir")
        {
            string dirName = (spacePos != string::npos) ? cmd.substr(spacePos + 1) : "";
            t.Remove_Directory(dirName);
        }
        else if (opt == "dir")
        {
            t.DisplayDirectoryContents();
            t.Print("\\>");
        }
        else if (opt == "tree")
        {
            t.print_tree(t.root);
        }
        else if (opt == "create")
        {
            // Extract the file name after "create "
            string fileName = (spacePos != string::npos) ? cmd.substr(spacePos + 1) : "";
            t.Create_File(fileName);
        }
        else if (opt == "del")
        {

            string fileName = (spacePos != string::npos) ? cmd.substr(spacePos + 1) : "";
            t.delete_File(fileName);
        }
        else if (opt == "ver")
        {

            version();
        }
        else if (opt == "format")
        {
            t.Format_everything();
        }
        else if (opt == "rename")
        {
            // Extract the current and new file names after "rename "
            string currentName = "", newName = "";
            size_t spacePos2 = cmd.find(' ', spacePos + 1);
            if (spacePos2 != string::npos)
            {
                currentName = cmd.substr(spacePos + 1, spacePos2 - spacePos - 1);
                newName = cmd.substr(spacePos2 + 1);
            }

            t.Rename_File(currentName, newName);
        }
        
                    
        return false;
    }
};

int main()
{
    DOS D;
    D.run();

    return 0;
}