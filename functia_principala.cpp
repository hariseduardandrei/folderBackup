include citire.h
include copiere.h
int main() 
{
    cin << folder_sursa;
    citire::read_folder(folder_sursa);
    copiere::copy_folder(folder_sursa);
    return 0;
}