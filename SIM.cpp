/* On my honor, I have neither given nor received unauthorized aid on this assignment */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;
//for compress
vector<string> readFile(string filename){
    
    fstream newfile;
    vector<string> original;
    newfile.open(filename,ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){ //checking whether the file is open
        string tp;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            original.push_back(tp);
           
        }
    }
    
    return original;

}
void writeFile(string filename,vector<string> input, vector<string> dictionary){
    ofstream file;
	file.open(filename, ios::out);
	for(int i=0;i<input.size();++i){
		file<<input[i]<<endl;
	}
    file<<"xxxx"<<endl;
    for(int i=0;i<dictionary.size();++i){
		file<<dictionary[i]<<endl;
	}
	file.close();

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
int getDirectMatchDictionaryIndex(string input, vector<string>dictionary){
    string index = "";
    for(int i=0; i < dictionary.size(); i++){
        if(input == dictionary[i]){
            return i;
        }
    }
}
vector<int> missedMatchedInfo(string input, vector<string>dictionary){
    int dictionary_index =0;
    vector<int> output;

    for(int i=0; i < dictionary.size(); i++){
        int count = 0;
        vector<int> temp_output;
        vector<int> miss_matched_location;
        for(int j=0; j < input.length(); j++){
            if(input[j] != dictionary[i][j]){
                count++;
                miss_matched_location.push_back(j);
            }
            
        }
        if(count == 1){
            temp_output.push_back(1);
            for(int k=0 ;k<miss_matched_location.size();k++){
                temp_output.push_back(miss_matched_location[k]);
            }
            temp_output.push_back(i);
            output = temp_output;
            break;
        }
        else if(count == 2 && miss_matched_location[1]-miss_matched_location[0]==1){         //2 miss matches
            temp_output.push_back(2);
            temp_output.push_back(miss_matched_location[0]);
            temp_output.push_back(i);
            if(output.size()==0){
                output = temp_output;
            }
            else if (temp_output[0] == output[0]){
                if(output.size()>temp_output.size()){
                    output = temp_output;
                }
            }
            else if(temp_output[0] < output[0]){
                output = temp_output;
            }
               
        }
        else if((count == 3 && miss_matched_location[1]-miss_matched_location[0]==miss_matched_location[2]-miss_matched_location[1] )||(count==2 && miss_matched_location[1]-miss_matched_location[0]==2)){ //3 consecutive miss matches
            temp_output.push_back(3);
            temp_output.push_back(miss_matched_location[0]);
            temp_output.push_back(i);
            if(output.size()==0){
                output = temp_output;
            }
            else if(output[0]>temp_output[0]){
                output = temp_output;
            }
            else if(output[0]<temp_output[0] && output.size()>temp_output.size()){
                output = temp_output;
            }
            
        }
        else if((count == 4 && (miss_matched_location[1]-miss_matched_location[0]==miss_matched_location[2]-miss_matched_location[1]) && (miss_matched_location[2]-miss_matched_location[1]==miss_matched_location[3]-miss_matched_location[2]))
                ||(count==2 && miss_matched_location[1]-miss_matched_location[0]<4 )
                ||(count==3 && miss_matched_location[1]-miss_matched_location[0]==2 && miss_matched_location[2]-miss_matched_location[1]==1) 
                ||(count==3 && miss_matched_location[1]-miss_matched_location[0]==1 && miss_matched_location[2]-miss_matched_location[1]==2)){ //4 consecutive miss matche
            temp_output.push_back(4);
            temp_output.push_back(miss_matched_location[0]);
            temp_output.push_back(i);
            if(output.size()==0){
                output = temp_output;
            }
            else if(output[0]<temp_output[0]){
                output = temp_output;
            }
           
        }
        else if(count==2 && miss_matched_location[1]-miss_matched_location[0]!=1){                   //different location miss matched 2
            temp_output.push_back(2);
            for(int k=0 ;k<miss_matched_location.size();k++){
                temp_output.push_back(miss_matched_location[k]);
            }
            temp_output.push_back(i);
            if(output.size()==0){
                output = temp_output;
            }
        }
            
    
    }
    
    return output;
}
string prefixSelector(string input){
    if(input=="DR"){
        return "101";
    }
    else if(input=="SMM"){
        return "010";
    }
    else if(input=="DMMCON"){
        return "011";
    }
    else if(input=="FMM" || input=="TMM"){
        return "001";
    }
    else if(input=="DMMNCON"){
        return "100";
    }
    else if(input=="RLE"){
        return "000";
    }
    else{
        return "110";
    }
}
int startingLocationCorrection(int location){
    if (location+3>31){
        return location+31-(location+3);
    }
    return location;
}
string decimaleToBinary(int n,int len){
    long long ans = 0;
    int remainder, i = 1;

    // Until the value of n becomes 0.
    while(n!=0){
        remainder = n % 2;
        ans += remainder*i;
        i = i * 10;
        n = n / 2;
    }
    if(to_string(ans).size() != len){
        string output=to_string(ans);
        for(i=0; i<len-to_string(ans).size();i++){
            output = "0"+output;
        }
        return output;
    }
    return to_string(ans);
    
	
    
}
vector<string> enableRLE(vector<string> input, string (*function)(int,int)){
    vector<string> output;
    int i=0;
    while (i <input.size()) {
        int count = 0;
        if(i<input.size()-4) {
            
            output.push_back(input[i]);
            
            for (int j=i+1; j<i+5; j++){
                if(input[j]==input[i] && count+i+1==j){
                    count=count+1;
                }
            }
            
            if(count>0){
                output.push_back("000"+function(count-1,2));
                i=i+count+1;
            }
            else{
                ++i;
            }
            
        }
        else if(i==input.size()-4){
             output.push_back(input[i]);
            
            for (int j=i+1; j<i+4; j++){
                if(input[j]==input[i] && count+i+1==j){
                    count=count+1;
                }
            }
            
            if(count>0){
                output.push_back("000"+function(count-1,2));
                i=i+count+1;
            }
            else{
                ++i;
            }
        }
        else if(i==input.size()-3){
             output.push_back(input[i]);
            
            for (int j=i+1; j<i+3; j++){
                if(input[j]==input[i] && count+i+1==j){
                    count=count+1;
                }
            }
            
            if(count>0){
                output.push_back("000"+function(count-1,2));
                i=i+count+1;
            }
            else{
                ++i;
            }
        }
        else if(i==input.size()-2){
             output.push_back(input[i]);
            
            for (int j=i+1; j<i+2; j++){
                if(input[j]==input[i] && count+i+1==j){
                    count=count+1;
                }
            }
            
            if(count>0){
                output.push_back("000"+function(count-1,2));
                i=i+count+1;
            }
            else{
                ++i;
            }
        }
        else if(i==input.size()-1){
            output.push_back(input[i]);
            ++i;   
        }     
        else{
            ++i;
        }
        
        
    }
    return output;
}
string superStringCreator(vector<string> input, int len){
    string output;
    for(int i=0; i<input.size();i++){
        output=output+input[i];
    }

    if(output.size()%len!=0){
        int remainder = output.size()%len;
        for(int j=0; j<remainder;j++){
            output=output+"1";
        }
    }
    return output;
}
vector<string> outputCreator(string input, int len){
    vector<string> output;
    for(int i=0; i<input.size();i=i+len){
        output.push_back(input.substr(i,len));
    }
    return output;
}


//for decompress
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
void writeDecompressed(vector<string> input, string filename){
    ofstream file;
	file.open(filename, ios::out);
	for(int i=0;i<input.size();++i){
		file<<input[i]<<endl;
	}
	file.close();
}

//for both
string bitMaskCreator(string input, string dictionary){
    string output="";
    for(int i=0; i<input.length(); i++){
        int num1 = stoi(input.substr(i,1));
        int num2 = stoi(dictionary.substr(i,1));
        output=output+to_string(num1 ^ num2);
    }
    return output;
}

int main(int argc, char* argv[]){

    if(atoi(argv[1]) == 1){             //for compress
        vector<string> inputs_original;
        vector<string> dictionary;
        vector<string> compressed_short;
        vector<bool> isCompressed;
        vector<string> output_without_RLE;
        vector<string> output_with_RLE;
        string concatenated_output;

        inputs_original = readFile("original.txt");
        dictionary = buildDictionary(inputs_original);
        for(int i= 0; i <inputs_original.size(); i++){          //checking direct matching
            string output="";
            if(isDirectMatch(inputs_original[i], dictionary)){
                isCompressed.push_back(true);
                int index = getDirectMatchDictionaryIndex(inputs_original[i], dictionary);
                compressed_short.push_back("DR"+to_string(index));
                output=prefixSelector("DR")+decimaleToBinary(index,3);
                output_without_RLE.push_back(output);
            }
            else{
            isCompressed.push_back(false);
            compressed_short.push_back("0");
            output_without_RLE.push_back("0");
            }
            
        }
        
        for (int i=0; i<inputs_original.size(); i++){           //multiple missed match checking

            if (!isCompressed[i]){
                vector<int> missed_match_info = missedMatchedInfo(inputs_original[i],dictionary);
                if(missed_match_info.size()>0){
                    isCompressed[i]=true;
                
                    if(missed_match_info[0]==1){        //single miss matched
                        compressed_short[i]="SMM-"+to_string(missed_match_info[1])+"-"+to_string(missed_match_info[2]); 
                        output_without_RLE[i]=prefixSelector("SMM")+decimaleToBinary(missed_match_info[1],5)+decimaleToBinary(missed_match_info[2],3);
                    }
                    else if(missed_match_info[0]==2 && missed_match_info.size()==3){      //2 miss matched consecutive
                        compressed_short[i]="DMMCON-"+to_string(missed_match_info[1])+"-"+to_string(missed_match_info[2]);
                        output_without_RLE[i]=prefixSelector("DMMCON")+decimaleToBinary(missed_match_info[1],5)+decimaleToBinary(missed_match_info[2],3);
                    }
                    else if(missed_match_info[0]==3){      //3 miss matched consecutive
                        compressed_short[i]="TMM-"+to_string(missed_match_info[1])+"-"+to_string(missed_match_info[2]);
                        output_without_RLE[i]=prefixSelector("TMM")+decimaleToBinary(startingLocationCorrection(missed_match_info[1]),5)+bitMaskCreator(inputs_original[i].substr(startingLocationCorrection(missed_match_info[1]),4),dictionary[missed_match_info[2]].substr(startingLocationCorrection(missed_match_info[1]),4))+decimaleToBinary(missed_match_info[2],3);
                    }
                    else if(missed_match_info[0]==4){      //4 miss matched consecutive
                        compressed_short[i]="FMM-"+to_string(missed_match_info[1])+"-"+to_string(missed_match_info[2]);
                        output_without_RLE[i]=prefixSelector("FMM")+decimaleToBinary(startingLocationCorrection(missed_match_info[1]),5)+bitMaskCreator(inputs_original[i].substr(startingLocationCorrection(missed_match_info[1]),4),dictionary[missed_match_info[2]].substr(startingLocationCorrection(missed_match_info[1]),4))+decimaleToBinary(missed_match_info[2],3);
            
                    }
                    else if (missed_match_info[0]==2 && missed_match_info.size()==4){     //2 miss matched non consecutive
                        compressed_short[i]="DMMNCON-"+to_string(missed_match_info[1])+"-"+to_string(missed_match_info[2])+"-"+to_string(missed_match_info[3]);
                        output_without_RLE[i]=prefixSelector("DMMNCON")+decimaleToBinary(missed_match_info[1],5)+decimaleToBinary(missed_match_info[2],5)+decimaleToBinary(missed_match_info[3],3);
                    
                    }
                    
                }
                if(compressed_short[i]=="0") {
                        compressed_short[i]="ORG-"+inputs_original[i];
                        output_without_RLE[i]=prefixSelector("ORG")+inputs_original[i];
                        
                    
                }
            }
            

        }

        output_with_RLE = enableRLE(output_without_RLE,&decimaleToBinary);
        concatenated_output = superStringCreator(output_with_RLE,32);
        
        writeFile("cout.txt",outputCreator(concatenated_output,32),dictionary);

    }



    else if(atoi(argv[1]) == 2){            //for decompress 
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
                string temp_dic_value =dic_value.replace(location1,1,notChanger(dic_value.substr(location1,1)));
                temp_dic_value =temp_dic_value.replace(location2,1,notChanger(dic_value.substr(location2,1)));
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
                    decompressed.push_back(decompressed[decompressed.size()-1]);
                }
            }     
            else{
                decompressed.push_back("0");
            }
        }
        writeDecompressed(decompressed,"dout.txt");
    }
    
}

