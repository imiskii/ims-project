/**
 * @file Formatter.hpp
 * @author Adam Lazík (xlazik00@vutbr.cz)
 * @brief Implementation of the Formatter class which provides functions to
 * format the given input and print formatted output
 * @date 2023-12-10
 *
 */

#pragma once

#include <string>

using namespace std;

class Formatter
{
public:
    /**
     * @brief 
     *
     */
    static void printSeparator();
    static void align(const string str);
    static void printHeading(const string title);
    static void printStatistic(const string stat);
};
