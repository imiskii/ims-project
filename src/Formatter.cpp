/**
 * @file Formatter.cpp
 * @author Adam Lazík (xlazik00@vutbr.cz)
 * @brief Implementation of the Formatter class methods
 * @date 2023-12-10
 *
 */

#include "Formatter.hpp"
#include <iostream>
#include <iomanip>

void Formatter::printSeparator() {
    cout << "+----------------------------------------------------------+\n";
}

void Formatter::align(const string str) {
    cout << "| " << setw(57) << left << str << "|\n";
}

void Formatter::printHeading(const string title) {
    printSeparator();
    align(title);
}

void Formatter::printStatistic(const string stat) {
    printHeading(stat);
    printSeparator();
}
