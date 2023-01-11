/**
 * @file main.cpp
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
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "cwushell.h"

using namespace std;

int main(){
    int status;
    //calling shell class
    shell* cwu = new shell();

    //running the shell and storing its value to status
    status = cwu -> run_shell();
    return status;
}