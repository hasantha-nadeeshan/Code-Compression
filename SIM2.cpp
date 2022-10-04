/* On my honor, I have neither given nor received unauthorized aid on this assignment */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

vector<string> readInputFile(string filename){
    
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
string singleStringCreator(vector<string> input){
    string output;
    for(int i=0; i<input.size(); i++){
        output=output+input[i];
    }
    return output;
}
vector<string> instructionsSpliter(string input){
    vector<string> output;
    int i=0;
    while(i<input.size()){
        if(input.substr(i,3)=="000"){
            output.push_back(input.substr(i,5));
            i=i+5;
        }
        else if(input.substr(i,3)=="001"){
            output.push_back(input.substr(i,15));
            i=i+15;
        }
        else if(input.substr(i,3)=="010"){
            output.push_back(input.substr(i,11));
            i=i+11;
        }
        else if(input.substr(i,3)=="011"){
            output.push_back(input.substr(i,11));
            i=i+11;
        }
        else if(input.substr(i,3)=="100"){
            output.push_back(input.substr(i,16));
            i=i+16;
        }
        else if(input.substr(i,3)=="101"){
            output.push_back(input.substr(i,6));
            i=i+6;
        }
        else if(input.substr(i,3)=="110"){
            output.push_back(input.substr(i,35));
            i=i+35;
        }
        else{
            break;
        }
    }
    return output;
}

int main(){

    vector<string> inputs_original=readInputFile("compressed.txt");
    vector<string> dictionary = dictionaryCreator("compressed.txt");
    string input_str = singleStringCreator(inputs_original);
    vector<string> splited_inputs = instructionsSpliter(input_str);
    
    for(int i=0; i<splited_inputs.size();i++){
        cout<<splited_inputs[i]<<endl;
    }
}