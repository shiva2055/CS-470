/**
 * @file cwushell.cpp
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
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdlib.h>
#include "cwushell.h"
#include <sstream>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/vfs.h>
#include <time.h>

using namespace std;
shell::shell(){
    default_prompt = "CWU SHEll";
    
    prompt = default_prompt;
    num_cmds = 5;
    set_cmds();
}
// this function sets command in an array 
void shell:: set_cmds(){
    cmds = new string [num_cmds];
    
    cmds[0] = "exit";
    cmds[1] = "prompt";
    cmds[2] = "fileinfo";
    cmds[3] = "osinfo";
    cmds[4] = "manual";
}

shell::~shell(){
    delete [] cmds;
}
int shell:: run_shell(){
    cout<< "Starting Lab1 CWU shell. Please enter 'manual' for help\n";
    string cmds = "";

    while(true) {
        cout << prompt << "> " ;
        getline (cin, cmds);
        //calling fork function 
        pid_t pid = fork();

        // checking for invalid pid
        if(pid == -1){
            cout << "It could not be forked";
            return 1;
        }
        // child 
        else if(pid == 0){
            run_cmds(cmds);
        }
        //parent
        else {
            int status = 0;
            wait(&status);
            status = status >> 5;
            return status;
        }
}
}
//prints manual 
void shell:: manual() {
    cout << "\n\tWelcome to cwushell Manual!!!!" <<endl;
    cout << "************************************************************" <<endl;
    cout << "\nThis shell runs as normal terminal works with some special command" << endl;
    cout << "It accepts standard linux commands as well as serveral built in special commands"<< endl;
    cout << "\nprompt [new_name_0f_prompt] : changes the current shell prompt to new prompt"<<endl;
    cout << "\nIf there is no parameter while changeing prompt, it will reset to the default shell prompt."<< endl;
    cout << "\nfileinfo[OPTION]: Displays file information." << endl;
    cout << "\nosinfo[OPTION]: Displays OS  information." << endl;
    cout << "\nexit [n]: It terminates the cwushell. User can put any number n as argument for the exit value\n"<< endl;
}
//string input and parses string n executes the internal linux commands
void shell::run_cmds(string cmds){
    vector<string> parsed_cmds = parsing(cmds);

    if(existing_cmds(parsed_cmds) == -1){
        //calling system() to execute linux commands 
        system(cmds.c_str());
    }

}
int shell:: existing_cmds(vector<string> command){
    int i;
    int temp = -1;

    for (int i = 0; i< num_cmds; i++){
        if(command[0].compare(cmds[i]) == 0){
            temp = i;
            break;
        }
    }
    if(temp >=0 && command.size()>3){
                cout<< "Error in the command parameters. Enter '-h' or '--help' for more info"<<endl; 
                return 0;
             }
   
    switch(temp){
        case -1:
        command.clear();
        return -1;
        case 0:
            exiting(command);
             
            break;
        case 1:
            update_prompt(command);
           
            break;
        case 2:
            fileinfo(command);

        case 3:
            osinfo(command);
           
            break; 
        case 4:
            manual();
           
    }
    command.clear();
    return 0;
}
// this function parses the string literal to different tokens
vector<string> shell :: parsing(const string& cmds){
    vector <string> words{};
    string myline;
    // using stringstream to parse the cmds
    stringstream sstream(cmds);
    string word;
    //this takes each token until another string lateral is found no matter how many spaces are there 
    while(sstream >> word){ 
        // pusing in words vector <string>
        words.push_back(word);
    }
    // returns the parsed words in form of vector <string>
    return words;
  
}
void shell::exiting(vector<string> cmds){
    int temp;
    // if only exit is input then puts 0 as exit parameter
    if(cmds.size() ==1 ){
        exit(0); 
    }

    try{
        // if integer value is given after exit, it takes that string and changes to int and puts exit parameter as input
        temp = stoi(cmds[1]);// changes string to int
        exit(temp);
        
    // catchs any invalid arguments
    }catch (invalid_argument const&){
        exit(0);
    }
    
}
int shell:: fileinfo( vector<string> cmds){
     // calls cpu_info_help() finction if input is -h or --help
    struct stat fd;
    char* c = const_cast<char*>(cmds[1].c_str());
    char* c2 = const_cast<char*>(cmds[2].c_str());
    if(cmds.size() == 1 || cmds[1] == "-h"|| cmds[1] == "--help"){
        fileinfo_help();
    }
    
    if((cmds.size() == 2)  && (stat(c, &fd) == 0)) {
        
        cout <<  "Inode number of " << c << " is:\t" << (fd.st_ino) <<endl;
        if(S_ISREG(fd.st_mode)){
                cout<< "Type of file is:\t" << "Regular file"<<endl;
                
            }
            else if(S_ISDIR(fd.st_mode)){
                cout<< "Type of file is:\t" << "Regular file"<<endl;
               
            }
            else if(S_ISLNK(fd.st_mode)){
                cout<< "Type of file is:\t" << "Regular file"<<endl;
                
            }
            else if(S_ISSOCK(fd.st_mode)){
                cout<< "Type of file is:\t" << "Regular file"<<endl;
                
            }
            else{
                cout << "Different file type than regular, directory, symlink\n";
                
            }
        printf("Last file modification:   %s", ctime(&fd.st_mtime));
          
        
    }
    if(cmds.size() == 3) {
    
        if((cmds[1].compare("-i") ==0) && (stat(c2, &fd) == 0)){   
        //printf("I-node number:            %ld\n", (long) sb.st_ino);//cout <<  buf.f_files;
          cout <<  "Inode number of " << c2 << " is:\t" << (fd.st_ino) <<endl;
            //MSDOS_SUPER_MAGIC  

        }
        else if ((cmds[1].compare("-t") ==0) && (stat(c2, &fd) == 0)){
            if(S_ISREG(fd.st_mode)){
                cout<< "Type of file is:\t" << "Regular file"<<endl;
                return 0;
            }
            else if(S_ISDIR(fd.st_mode)){
                cout<< "Type of file is:\t" << "Regular file"<<endl;
                return 0;
            }
            else if(S_ISLNK(fd.st_mode)){
                cout<< "Type of file is:\t" << "Regular file"<<endl;
                return 0;
            }
            else if(S_ISSOCK(fd.st_mode)){
                cout<< "Type of file is:\t" << "Regular file"<<endl;
                return 0;
            }
            else{
                cout << "Different file type than regular, directory, symlink\n";
                return 0;
            }
        }
        else if(cmds[1].compare("-m") ==0){
            printf("Last file modification:   %s", ctime(&fd.st_mtime));
            return 0;
        }
        else{
            cout << "Unknown switch. Use fileinfo --help for more info\n";

        }

    }
      return 0;
}
int shell:: osinfo(vector<string> cmds){
     // calls cpu_info_help() finction if input is -h or --help
    if(cmds.size() == 1 || cmds[1] == "-h"|| cmds[1] == "--help"){
        osinfo_help();
        return 0;
    }
    if(cmds.size() >2){
         cout << "more parameter in the OSinfo. See osinfo help\n";
         return 0;
    }
    struct statfs buf;
    
    
    int status = 0;
    if(cmds[1].compare("-T") ==0) 
    {   
        cout <<  "the type of file system is:\t"<< buf.f_type  << endl;
        
    }
    else if (cmds[1].compare("-b") ==0){
        cout<< "Total number of blocks:\t" << buf.f_blocks<<endl;
    }
    else if(cmds[1].compare("-s") ==0){
        cout<< "Maximum length  of characters osinfo filenames:\t" << buf.f_namelen<<endl;
    }
    else{
        cout << "Unknown switch. Use osinfo --help for more info\n";

    }
    return 0;
    
}
void shell:: fileinfo_help(){
    cout << "\nUsage: fileinfo [OPTION] [filename]"<< endl;
    cout << "Prints information about file information" << endl;
    cout << "**************************************************"<<endl;
    cout << "-i \t Prints inode number of file"<<endl;
    cout << "-t \t Prints type of file pointed by file name"<<endl;
    cout << "-m \t Prints last modification of the data of the file " <<endl;
}
void shell:: osinfo_help(){
    cout << "\nUsage: osinfo [OPTION]"<< endl;
    cout << "Prints information about operationg information" << endl;
    cout << "**************************************************"<<endl;
    cout << "-T \t Prints type of file system  (e.g. DOS, FAT, FAT32, EXT2, etc)"<<endl;
    cout << "-b \t Prints total number of blocks in file system"<<endl;
    cout << "-s \t Prints maximum number of characters in filename" <<endl;

}
void shell:: prompt_help(){
    cout << "\nUsage: prompt [Name]"<< endl;
    cout << "changes name of the prompt" << endl;
}
int shell:: update_prompt(vector<string> cmds){
      // this checks if only prompt is inputed it changes prompt name back to default
    if(cmds.size() >2){
         cout << "more parameter in the prompt. See prompt help\n";
         return 0;
    }
    if(cmds.size() ==1 ){
        this -> prompt = default_prompt;
    }
    // calls prompt_help() function for detail help on using prompt command
    else if(cmds[1] == "-h" || cmds[1] == "--help"){
        prompt_help();
        return 0;
    }
    // changes prompt to given input
    else {
        this->prompt = cmds[1];
    }
    //clears the cmds
    cmds.clear();
    return 0;
   
}
