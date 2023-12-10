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
     * @brief print the same separator as is used in Stat.Output()
     */
    static void printSeparator();

    /**
     * @brief print string to separator length surrounded by '|'
     * @param str string to print
     */
    static void align(const string str);

    /**
     * @brief print separator followed by aligned string
     * @param title string to print
     */
    static void printHeading(const string title);

    /**
     * @brief print heading followed by another separator
     * @param stat string to print
     */
    static void printStatistic(const string stat);
};
