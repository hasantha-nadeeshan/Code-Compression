else if(prefix=="001"){
            string dic_index= splited_inputs[i].substr(12,3);
            int location = binaryToDecimal(splited_inputs[i].substr(3,5));
            string dic_value = dictionary[binaryToDecimal(dic_index)];
            string temp_dic_value = dic_value.substr(0,location)+bitMaskCreator(splited_inputs[i].substr(location,4),dic_value.substr(location,4))+dic_value.substr(location+4);
            decompressed.push_back(temp_dic_value);
        }