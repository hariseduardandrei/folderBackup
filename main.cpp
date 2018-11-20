#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <iostream>

using namespace std;

bool is_directory(const char *entry_path);

void list_directory(const char *source_directory);

int main()
{
    string source_directory;

    cout << "Calea directorului: ";
    getline(cin, source_directory);

    // source_directory = "/Users/eduard/Desktop/deaCpp";

    list_directory(source_directory.c_str());

    return 0;
}

void list_directory(const char *source_directory)
{
    DIR *directory;
    struct dirent *entry_interator;
    string entry_path, entry_name, source_directory_copy;

    if (is_directory(source_directory) == false)
    {
        return;
    }

    if ((directory = opendir(source_directory)))
    {
        while ((entry_interator = readdir(directory)))
        {
            entry_name = entry_interator->d_name;
            if (strcmp(entry_name.c_str(), ".") != 0 && strcmp(entry_name.c_str(), "..") != 0)
            {
                cout << entry_name<<endl;
                source_directory_copy = source_directory;
                entry_path = source_directory_copy.append("/").append(entry_name);
                if (is_directory(entry_path.c_str()))
                {
                    list_directory(entry_path.c_str());
                }
            }
        }
        closedir(directory);
    }
}

bool is_directory(const char *entry_path)
{
    struct stat path_status;
    stat(entry_path, &path_status);
    return S_ISDIR(path_status.st_mode);
}