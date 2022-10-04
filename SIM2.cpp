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
string bitMaskCreator(string input, string dictionary){
    string output="";
    for(int i=0; i<input.length(); i++){
        int num1 = stoi(input.substr(i,1));
        int num2 = stoi(dictionary.substr(i,1));
        output=output+to_string(num1 ^ num2);
    }
    return output;
}
int binaryToDecimal(string input){
    string output;
    int n = stoi(input);
    int num = n;
    int dec_value = 0;
    int base = 1;
    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
 
        dec_value += last_digit * base;
 
        base = base * 2;
    }
 
    return dec_value;
}
string notChanger(string input){
    if(input == "0"){
        return "1";
    }
    else{
        return "0";
    }
}



int main(){

    vector<string> inputs_original=readInputFile("compressed.txt");
    vector<string> dictionary = dictionaryCreator("compressed.txt");
    string input_str = singleStringCreator(inputs_original);
    vector<string> splited_inputs = instructionsSpliter(input_str);
    vector<string> decompressed;
    for(int i=0; i<splited_inputs.size();i++){
        string prefix = splited_inputs[i].substr(0,3);
        if(prefix=="101"){          //direct match
            string dic_index= splited_inputs[i].substr(3,3);
            string dic_value = dictionary[binaryToDecimal(dic_index)];
            decompressed.push_back(dic_value);
        }
        else if(prefix=="110"){         //not compressed - originals
            decompressed.push_back(splited_inputs[i].substr(3));
        }
         else if(prefix=="100"){        
            string dic_index= splited_inputs[i].substr(13,3);
            int location1 = binaryToDecimal(splited_inputs[i].substr(3,5));
            int location2 = binaryToDecimal(splited_inputs[i].substr(8,5));
            string dic_value = dictionary[binaryToDecimal(dic_index)];
            string temp_dic_value = dic_value.substr(0,location1)+notChanger(dic_value.substr(location1,1))+dic_value.substr(location1+1,location2-location1-1)+notChanger(dic_value.substr(location2))+dic_value.substr(location2+1);
            decompressed.push_back(temp_dic_value);
        }
        else if(prefix=="001"){
            string dic_index= splited_inputs[i].substr(12,3);
            int location = binaryToDecimal(splited_inputs[i].substr(3,5));
            string dic_value = dictionary[binaryToDecimal(dic_index)];
            string temp_dic_value =dic_value.replace(location,4,bitMaskCreator(splited_inputs[i].substr(8,4),dic_value.substr(location,4)));
            decompressed.push_back(temp_dic_value);
        }
         else if(prefix=="011"){
            string dic_index= splited_inputs[i].substr(8,3);
            int location = binaryToDecimal(splited_inputs[i].substr(3,5));
            string dic_value = dictionary[binaryToDecimal(dic_index)];
            string temp_dic_value = dic_value.substr(0,location)+notChanger(dic_value.substr(location,1))+notChanger(dic_value.substr(location+1,1))+dic_value.substr(location+2);
            decompressed.push_back(temp_dic_value);
        }
        else if(prefix=="010"){
            string dic_index= splited_inputs[i].substr(8,3);
            int location = binaryToDecimal(splited_inputs[i].substr(3,5));
            string dic_value = dictionary[binaryToDecimal(dic_index)];
            string temp_dic_value = dic_value.substr(0,location)+notChanger(dic_value.substr(location,1))+dic_value.substr(location+1);
            decompressed.push_back(temp_dic_value);
        }
       
       
        else if(prefix=="000"){
            int itterations=binaryToDecimal(splited_inputs[i].substr(3,2))+1;

            for(int j=0; j<itterations; j++){
                decompressed.push_back(decompressed[i-1]);
            }
        }
      
        else{
            decompressed.push_back("0");
        }
    }

    for(int i=0; i<decompressed.size();i++){
        cout<<decompressed[i]<<endl;
    }
    
    
}