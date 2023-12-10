#pragma once

#include <string>

using namespace std;

class Formatter
{
private:
    /* data */
public:
    static void printSeparator();
    static void align(const string str);
    static void printHeading(const string title);
    static void printStatistic(const string stat);
};
