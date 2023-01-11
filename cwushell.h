/**
 * @file cwushell.h
 * @author shiva(shresthashi@cwu.edu)
 * @brief 
 * @version 0.1
 * @date 2022-10-07
 * 
 * @copyright Copyright (c) 2022
 * 
 * Honor Code: I pledge that I have not copied from any other students or given to anyone else and this submission my individual work. 
 *              I have used internet platforms like stackoverflow to get some 
 *              of the code, but I have implemented my own way and understood the code.
 *


*/

#ifndef CWUSHELL_H
#define CWUSHELL_H

#include <string>
#include <vector>
using namespace std;

class shell{
    private: 
    string default_prompt;
    string prompt;
    string* cmds;
    int num_cmds;

    vector<string> parsing(const string& cmds);

    void prompt_help();
    void fileinfo_help();
    void exiting(vector<string> cmds);
    void manual();
    void osinfo_help();
    void set_cmds();
    void run_cmds(string cmds);

    int update_prompt(vector<string> cmds);
    int existing_cmds(vector<string> cmds);
    int fileinfo(vector<string> cmds);
    int osinfo(vector<string> cmds);

    public:
    shell();
    ~shell();
    int run_shell();
};

#endif
