#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename);
    string textline;
    while (getline(source,textline)){
        char format[] = "%[^:]: %d %d %d";
        char name[100];
        int a, b, c;
        sscanf(textline.c_str(), format, name, &a, &b, &c);
        names.push_back(name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
}

void getCommand(string &command, string &key){
    string cmd;
    char cmdl[100];
    char keyl[100];
    char format[] = "%s %[^\n]";
    cout << "Please input your command: ";
    getline(cin,cmd);
    sscanf(cmd.c_str(), format, cmdl, keyl);
    command = cmdl;
    key = keyl;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    int result = -1;
    for(unsigned int i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key)
            result = i;
    }
    if(result != -1){
        cout << names[result] << "'s score = " << scores[result] << endl;
        cout << names[result] << "'s grade = " << grades[result] << endl;
    }else
        cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < grades.size(); i++){
        if(grades[i] == *key.c_str())
            cout << names[i] << " (" <<scores[i] << ")\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
