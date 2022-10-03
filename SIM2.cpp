/* On my honor, I have neither given nor received unauthorized aid on this assignment */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

vector<string> readFile(string filename){
    
    fstream newfile;
    vector<string> original;
    newfile.open(filename,ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){ //checking whether the file is open
        string tp;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            if(tp=="xxxx"){ 
                break;
            }
            original.push_back(tp);
           
        }
    }
    
    return original;

}
vector<string> dictionaryCreator(string filename){
    fstream newfile;
    vector<string> original;
    newfile.open(filename,ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){ //checking whether the file is open
        string tp;
        bool is_dictionary_found = false;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            if(tp=="xxxx"){ 
                is_dictionary_found = true;
            }
            if(is_dictionary_found && tp!="xxxx"){
                original.push_back(tp);
            }
            
           
        }
    }
    
    return original;
}
int main(){

    vector<string> inputs_original=readFile("compressed.txt");
    vector<string> dictionary = dictionaryCreator("compressed.txt");

    for(int i=0; i<inputs_original.size();i++){
        cout<<inputs_original[i]<<endl;
    }
    cout<<"xxxx"<<endl;
    for(int i=0; i<dictionary.size();i++){
        cout<<dictionary[i]<<endl;
    }

}