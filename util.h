#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>


class FileParser
{
public:
    FileParser();
    static std::vector<std::vector<int> >* readMatrix(std::string filename);
};

#endif // UTIL_H
