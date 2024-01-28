/**
 * @file argparse.hpp
 * @author Michal Ľaš (xlasmi00)
 * @brief Header file for argparse.cpp
 * @date 2023-10-19
 *
 */


#include <getopt.h>
#include <vector>
#include <string>
#include <iostream>



#ifndef ARGPARSE_H
#define ARGPARSE_H


using namespace std;


/******************** MACROS ********************/


/****************** DATATYPES *******************/


// parsed program arguments
struct arguments
{
    size_t days;
    size_t gas_cars;
    size_t autonomous_cars;
    size_t electric_cars;
    size_t parcels;
};


// argument flags (tells if program argument was given)
struct arg_flags
{
    bool h_flag;
};

/*********** FUNCTIONS AND CLASSES **************/


class ArgParser
{
protected:
    // Flag telling if program arguments were already parsed
    bool __parsed;

    /**
     * @brief Construct a new Arg Parser object
     *
     * @param argc number of arguments
     * @param argv pointer to array with arguments
     */
    ArgParser(int argc, char **argv);

private:
    /* Private Attributes */


    vector<option> _long_opt;   // Long program options
    string _short_opt;          // Short program options
    int _argCount;              // number of arguments
    char **_progArgs;           // program arguments
    /* Private Methods */

    /**
     * @brief print program help info
     *
     */
    void __printHelp();

    /**
     * @brief parse given given argument and return its unsigned
     * integer value. If argument is not a valid unsigned integer,
     * exit with error code 1.
     *
     * @param str argument expected to be unsigned integer
     * @return int value of the argument
     */
    int __parseUnsignedInt(char *str);

public:
    ArgParser(ArgParser &other) = delete;
    void operator=(const ArgParser &) = delete;

    /* Public Attributes */
    arguments args;     // parsed program arguments
    arg_flags flags;    // program arguments flags telling if the argument was given

    /* Public Methods */

    /**
     * @brief Get the Instance object
     *
     * @param argc number of program arguments
     * @param argv program arguments
     * @return ArgParser* ArgParser class instance
     */
    static ArgParser *GetInstance(int argc, char **argv);

    /**
     * @brief Parse program arguments
     *
     * @return arguments struct with parsed program arguments
     */
    arguments getArguments();

    /**
     * @brief Print parsed argumnets
     *
     */
    void printArgs();
};

#endif // ARGPARSE_H
