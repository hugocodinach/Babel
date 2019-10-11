/*
** EPITECH PROJECT, 2018
** CPP_plazza_2018
** File description:
** word_array.cpp
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <vector>

int sep_ot_not(char c, char *sep)
{
    for (int ct = 0; sep[ct] != '\0'; ct ++)
        if (c == sep[ct] || sep[ct] == '\0')
            return 84;
    return 0;
}

void pass_not_sep(std::string str, char *sep, int *ct, int *nbr)
{
    (*nbr) = (*nbr) + 1;
    for (int ctb = (*ct); str[ctb] != '\0'; ctb ++) {
        if (sep_ot_not(str[ctb], sep) == 84) {
            return;
        }
            (*ct) = (*ct) + 1;
    }
}

std::vector<std::string> word_array(std::string str, char *sep)
{
    std::vector<int> size;
    std::vector<int> ptr;
    int nbr = 0;
    std::vector<std::string> tab;

    for (int ct = 0; str[ct] != '\0'; ct ++) {
        if (sep_ot_not(str[ct], sep) == 0) {
            ptr.push_back(ct);
            pass_not_sep(str, sep, &ct, &nbr);
            size.push_back(ct);
            if (str[ct] == '\0')
                break;
        }
    }
    for (unsigned int ct = 0; ct != ptr.size(); ct ++) {
        tab.push_back(str.substr(ptr[ct], size[ct] - ptr[ct]));
    }
    return tab;
}