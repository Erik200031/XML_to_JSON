#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::string path {"input.xml"};
    std::cout<<"Enter File path -> ";
    std::cin>>path;
    std::ifstream fin;
    std::ofstream fout;
    std::vector<std::vector<std::string>> text;
    fin.open(path);
    if(!fin.is_open()) {
        std::cout << "File not open";
        abort();
    }
    else if(fin.is_open()) {
        while(!fin.eof()){
            std::string str;
            getline(fin,str);
            std::stringstream s(str);
            std::vector<std::string> tmp;
            while(!s.eof()){
                s>>str;
                tmp.push_back(str);   
            }
            text.push_back(tmp);
        }
    }
    int index = -1; 
    for (int i = 0; i < text.size(); i++)
    {
        for (int j = 0; j < text[i].size(); j++)
        {

            index = -1;
            index = text[i][j].find('=');
            if(index != -1) {
                if(text[i][j][text[i][j].size()-1] != '>') {
                    text[i][j][index] = ':';
                    text[i][j].insert(index, "\"");
                    text[i][j].insert(0, "\"");
                }
                else {
                    text[i][j][index] = ':';
                    text[i][j].insert(index, "\"");
                    text[i][j].insert(0, ", \"");
                }
                text[i][0][0] = '"';
                text[i][0] += '"';
                text[i][text[i].size()-1][text[i][text[i].size()-1].size()-1] = ' ';
            }
            index = -1;
            index = text[i][j].find("<");
            if(index != -1 && text[i][j][index+1] == '/') {
                int tmp_index = -1;
                tmp_index = text[i][j].find('>');
                if(tmp_index != -1) {
                    text[i][j].erase(index,tmp_index+1);
                text[i][j] = "}";
                }
            }
            if(text[i][j][0] == '<' && text[i][j][1] != '/') {
                index = -1;
                index = text[i][j].find('>');
                if (index != -1) {
                    int tmp_index = -1;
                    tmp_index = text[i+1][j].find('<');
                    if(tmp_index != -1) {
                        if(i < text.size()-1 && text[i+1][j][tmp_index+1] != '/' && text[i+1][j][tmp_index+2] != text[i][j][1]) {
                            text[i][j].insert(index+1,"\" : \n{");
                        }
                        else {
                            text[i][j].insert(index+1,"\" : ");
                        }
                    }
                    text[i][j][0] = '"';
                    text[i][j][index] = ' ';
                }
            }
        }  
    }
    




    fout.open("output.json");
    for (int i = 0; i < text.size(); i++)
    {
        for (int j = 0; j < text[i].size(); j++)
        {
            fout << text[i][j]<<" ";
        }
        fout << std::endl;
    }
    



    fin.close();
    fout.close();
    return 0;
}
  