/*
** EPITECH PROJECT, 2018
** NWP_myftp_2018
** File description:
** CCP_plazza_2018/include/TOOLS.hpp
*/

#ifndef _TOOLS_HPP_
#define _TOOLS_HPP_

#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>

std::vector<std::string> word_array(std::string str, char *sep);

#endif