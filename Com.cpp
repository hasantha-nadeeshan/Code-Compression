#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

vector<string> readFile(){
    
    fstream newfile;
    vector<string> original;
    newfile.open("original.txt",ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){ //checking whether the file is open
        string tp;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            original.push_back(tp);
            //cout << tp << "\n"; //print the data of the string
        }
    }
    
    //cout << "Size : " << original.size();
    return original;

}

vector<string> buildDictionary(vector<string> original){

    vector<string> duplicates;
    vector<int> no_of_duplicates;
    vector<string> final_duplicates;
    vector<int> final_no_of_duplicates;

    int temp1,temp2,pass = 0;
    string temp3 = "";

    for(int i = 0; i < original.size(); i++){
        int count = 0;
        for(int j = 0; j < original.size(); j++){
            if(original[i] == original[j]){
                count++;
            }
        }
        if(count>1){
            int duplicate_count = 0;
            for(int k = 0; k <duplicates.size(); k++){
                if(original[i]==duplicates[k]){
                    duplicate_count++;
                }
            }
            if(duplicate_count==0){
                duplicates.push_back(original[i]);
                no_of_duplicates.push_back(count);
            }
          
        }
    }
    for(int i = 0; i < no_of_duplicates.size();i++){
        temp1 = no_of_duplicates[i];
        int local_max = temp1;
        int local_max_index = i;
        for(int j = 0; j <no_of_duplicates.size();j++){
            temp2 = no_of_duplicates[j];
            if(temp2>local_max){
                local_max = temp2;
                local_max_index = j;
            }
        }
        // cout <<local_max<<"-";
        // cout <<local_max_index<<"\n" ;
        final_no_of_duplicates.push_back(local_max);
        final_duplicates.push_back(duplicates[local_max_index]);
        no_of_duplicates[local_max_index]=0;
    }
    
    // for (int i = 0; i < final_duplicates.size(); i++){
    //     cout <<final_duplicates.at(i)<<'-';
    //     cout <<final_no_of_duplicates.at(i)<<"\n";
    // }
    return final_duplicates;
    
}
bool isDirectMatch(string input, vector<string> dictionary){
    bool isMatch = false;
    for(int i=0; i < dictionary.size(); i++){
        if(input == dictionary[i]){
            isMatch = true;
        }
    }
    return isMatch;
}
string getDirectMatchDictionaryIndex(string input, vector<string>dictionary){
    string index = "";
    for(int i=0; i < dictionary.size(); i++){
        if(input == dictionary[i]){
            index = to_string(i);
            return index;
        }
    }
}
vector<int> singleMissedMatchInfo(string input, vector<string>dictionary){
    int dictionary_index =0;
    vector<int> output;

    for(int i=0; i < dictionary.size(); i++){
        int count = 0;
        vector<int> miss_matched_location;
        for(int j=0; j < input.length(); j++){
            if(input[j] != dictionary[i][j]){
                count++;
                miss_matched_location.push_back(j);
            }
            
        }
        if(count == 1){
            output.push_back(1);
            for(int k=0 ;k<miss_matched_location.size();k++){
                output.push_back(miss_matched_location[k]);
            }
            output.push_back(i);
            break;
        }
    }
    
    return output;
}
int main(){

    vector<string> inputs_original;
    vector<string> dictionary;
    vector<string> compressed_short;
    vector<bool> isCompressed;
    vector<int> no_of_missed_matched;
    vector<int> relavant_dictionary;

    inputs_original = readFile();
    dictionary = buildDictionary(inputs_original);
    for(int i= 0; i <inputs_original.size(); i++){          //checking direct matching
        if(isDirectMatch(inputs_original[i], dictionary)){
            isCompressed.push_back(true);
            compressed_short.push_back("DR"+getDirectMatchDictionaryIndex(inputs_original[i], dictionary));
        }
        else{
           isCompressed.push_back(false);
           compressed_short.push_back("0");
        }
        
    }
    
    for (int i=0; i<inputs_original.size(); i++){           //single missed match checking

        if (!isCompressed[i]){
            vector<int> single_missed_match_info = singleMissedMatchInfo(inputs_original[i],dictionary);
            if(single_missed_match_info.size()>0){
                isCompressed[i]=true;
               // cout<<to_string(i+1)<<"--"<<inputs_original[i]<<" has a "<<to_string(single_missed_match_info[0])<<" missed match with dictonary index "<<to_string(single_missed_match_info[2]+1)<<" at location "<<to_string(single_missed_match_info[1])<<endl;
               if(single_missed_match_info[0]==1){
                    compressed_short[i]="SMM-"+to_string(single_missed_match_info[1])+"-"+to_string(single_missed_match_info[2]);  
                }
            }
        }
        

    }

    for(int i=0; i<compressed_short.size(); i++){
        cout<<compressed_short[i]<<endl;
    }
    
}

