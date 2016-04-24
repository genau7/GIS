#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <queue>
#include <stdio.h>
#include <limits.h>

class FileParser
{
public:
    FileParser();
    static std::vector<std::vector<int> >* readMatrix(std::string filename);
};

#endif // UTIL_H
