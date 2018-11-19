#include <iostream>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>

using namespace std;

bool is_dir(const char* path);
void copyFile_(string inDir, string outDir);
void copyDir_(const char *inputDir, string outDir);

int main()
{

    cout << "Calea directorului sursa: ";
    string srcDir;
    getline(cin, srcDir); // Get from the keyboard the source path
    cout << "Calea directorului destinatie: ";
    string destDir;
    getline(cin, destDir); // Get from the keyboard the destination path
    copyDir_(srcDir.c_str(),  destDir); // first call for the function copyDir_

    return 0;



}

bool is_dir(const char* path) // Check if the path is a directory or a file
{
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

bool is_(const char* path) // checks if the path exists in the destination folder
{
    struct stat buf;
    return stat(path, &buf);
}

void copyFile_(const char* inDir,const char* outDir){
    string ind = inDir;
    string outd = outDir;
    if ( is_( outd.c_str() ) == 0 ) // If the file exists
    {
        struct stat out;
        struct stat in;
        stat(inDir, &in);
        stat(outDir, &out);
        if(in.st_mtime>out.st_mtime || in.st_size>out.st_size){ // if the last modify of the source file is higher than the destination
            DeleteFile(outd.c_str());
            CopyFile(ind.c_str(), outd.c_str(), 1); // delete and copy the new file
            cout << "--> Updated" ;
        }
        cout << "\n";
    }else{
        CopyFile(ind.c_str(),outd.c_str(),1); // only copy file cause it doesn't exist
    }
}

void copyDir_(const char *inputDir, string outDir)
{

    DIR *pDIR;
    struct dirent *entry;
    string tmpStr, tmpStrPath, outStrPath, inputDir_str = inputDir, outDIR_str = outDir, tmpOut;

    if (is_dir(inputDir) == false) // if the given dir at the start is a file it stops
    {
        cout << "This is not a folder " << endl;
        return;
    }

    if( pDIR = opendir(inputDir_str.c_str()) ) // Open directory "inputDir" (changes in base of the function calls)
    {

        while(entry = readdir(pDIR)) // get folders and files names
        {
            tmpStr = entry->d_name;

            if( strcmp(entry->d_name, ".")  != 0 && strcmp(entry->d_name, "..") != 0 )
            {
                tmpStrPath = inputDir_str;
                tmpStrPath.append( "\\" );
                tmpStrPath.append( tmpStr ); // Add file/folder name to the source "URL"
                tmpOut = outDIR_str;
                tmpOut.append( "\\" );
                tmpOut.append( tmpStr ); // Add file/folder name to the destination "URL"

                if ( is_( tmpOut.c_str() ) == 0 ) // Test if file/folder exists
                {
                    cout << entry->d_name;
                    if (is_dir(tmpStrPath.c_str())) // Test if is a file or a folder
                    {
                        cout << "\n";
                        copyDir_(tmpStrPath.c_str(), tmpOut); // Is a folder so we only open it
                    }else{
                        outStrPath = outDir;
                        outStrPath.append( "\\" );
                        outStrPath.append( tmpStr );
                        copyFile_(tmpStrPath.c_str(), outStrPath.c_str());  // Is a file so we in case it's different we update it
                    }
                }
                else
                {
                    cout << entry->d_name;
                    if (is_dir(tmpStrPath.c_str()))
                    {
                        cout << "--> Folder Created" << "\n";
                        // Create Folder on the destination path
                        outStrPath = outDir;
                        outStrPath.append( "\\" );
                        outStrPath.append( tmpStr );
                        mkdir(outStrPath.c_str()); // Create directory with the same name of the source

                        copyDir_(tmpStrPath.c_str(), outStrPath); // Give to this SAME function the new path to copy files in the new directory
                    }
                    else
                    {
                        cout << "--> File Copied"   << "\n";
                        // copy file on the destination path
                        outStrPath = outDir;
                        outStrPath.append( "\\" );
                        outStrPath.append( tmpStr );

                        copyFile_(tmpStrPath.c_str(), outStrPath.c_str()); // copy file to backup folder
                    }
                }
            }
        }
        closedir(pDIR); // closing dirent pointer to the source folder
    }
}
