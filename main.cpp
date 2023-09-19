#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>


using namespace std;

#include "L2.cpp"

vector <string> convert_string(string s, string cur_let, string cur_status){
    string cur = "";
    vector <string> ans;
    int cnt = 0;
    for (int i = 0; i < s.size(); ++i){
        if (s[i] != ','){
            cur.push_back(s[i]);
        } else{
            if (cur == ""){
                if (cnt == 0) cur = cur_let;
                else if (cnt == 1) cur = 'N';
                else cur = cur_status;
            }
            cnt++;
            ans.push_back(cur);
            cur = "";
        }
    }
    if (cur == "") cur = cur_status;
    ans.push_back(cur);
    return ans;
}

void read_csv(vector <string> &input, string input_file_name){
    ifstream in(input_file_name);
    string el;
    while (getline(in, el)){
        input.push_back(el);
    }
}

void convert_to_table(map <string, map<string, vector <string>>> &table, vector<string> input, string &status){
    vector <string> alphabet;
    string cur_let = "";
    bool first = true;
    for (int i = 0; i < input[0].size(); ++i){
        if (input[0][i] == ';'){
            if (!first){
                alphabet.push_back(cur_let);
            } else{
                first = false;
            }
            
            cur_let = "";
        } else cur_let.push_back(input[0][i]);
    }
    if (cur_let != "") alphabet.push_back(cur_let);
    
    vector <string> statuses;
    for (int i = 1; i < input.size(); ++i){
        string now = "";
        int j = 0;
        while (input[i][j] != ';' && j < input[i].size()){
            now.push_back(input[i][j]);
            j++;
        }
        statuses.push_back(now);
    }
    
    for (int i = 1; i < input.size(); ++i){
        bool check = false;
        string cur = "";
        int alpha_num = 0;
        for (int j = 0; j < input[i].size(); ++j){
            if (!check){
                if (input[i][j] == ';') check = true;
            } else{
                if (input[i][j] != ';') cur.push_back(input[i][j]);
                else {
                    table[statuses[i - 1]][alphabet[alpha_num]] = convert_string(cur, alphabet[alpha_num], statuses[i - 1]);
                    alpha_num++;
                    cur = "";
                }
            }
        }
        table[statuses[i - 1]][alphabet[alpha_num]] = convert_string(cur, alphabet[alpha_num], statuses[i - 1]);
    }
    status = statuses[0];
    
    
}

void print(L2 word, Node * cur_place){
    Node * el = word.head;
    while (el != NULL){
        if (el == cur_place){
            cout << '|' << (*el).val << "| ";
        }
        else cout << (*el).val << ' ';
        el = (*el).next;
    }
}

void emulate(L2 &word, map <string, map<string, vector <string>>> table, int mode, string &status){
    Node * cur_place = word.head->next;

    while (true){

        if (mode == 1){
            print(word, cur_place);
            cout << status << '\n';
            cout << "Continue - 1\n";
            int a;
            while (true){
                cin >> a;
                if (a == 1) break;
            }
        }
        string letter = "";
        letter.push_back((*cur_place).val);
        vector <string> cur_cell = table[status][letter];
        (*cur_place).val = cur_cell[0][0];
        status = cur_cell[2];
        
        if (cur_cell[1] == "R") {
            if ((*cur_place).next == NULL){
                push_back(word, 'x');
            }
            cur_place = (*cur_place).next;
        } else if (cur_cell[1] == "L"){
            if ((*cur_place).prev == NULL){
                push_front(word, 'x');
            }
            cur_place = (*cur_place).prev;
        }

        

        if (status == "!") break;
    }
}

int main(int argc, char ** argv){
    int mode = -1; // 0 - full, 1 - step by step
    string input_file_name = "";
    for (int i = 1; i < argc; ++i){
        if ((string)argv[i] == "--full") {
            mode = 0;
        }
        else if ((string)argv[i] == "--step") mode = 1;
        else if ((string)argv[i] == "-i"){
            if (i < argc - 1) {
                input_file_name = argv[i + 1];
                i++;
            }
        }
    }
    if (mode == -1){
        cout << "Mode not selected\n";
        return 0;
    }   
    if (input_file_name == ""){
        cout << "No input file name\n";
        return 0;
    }
    
    
    map <string, map<string, vector <string>>> table;
    vector <string> input;
    read_csv(input, input_file_name);
    
    string status;
    convert_to_table(table, input, status);
    

    string word;
    cin >> word;
    L2 word_list;
    push_back(word_list, 'x');
    for (char el : word) push_back(word_list, el);
    push_back(word_list, 'x');
    emulate(word_list, table, mode, status);
    string output = "";
    Node * cur = word_list.head;
    while (cur != NULL){
        if ((*cur).val == 'x') output.push_back(' ');
        else output.push_back((*cur).val);
        cur = (*cur).next;
    }
    cout << output;
}