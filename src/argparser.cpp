/**
 * @file argparse.cpp
 * @author Michal Ľaš (xlasmi00)
 * @brief classes, function and methods for program argument parsing
 * @date 2023-12-03
 * 
 */


#include "argparser.hpp"

using namespace std;


ArgParser::ArgParser(int argc, char **argv): _argCount(argc), _progArgs(argv)
{
    this->__parsed = false;
    this->_short_opt = "h";
    this->_long_opt = {
        {"help", no_argument, nullptr, 'h'}
    };
    this->flags = {false};
}


ArgParser::~ArgParser()
{
}


ArgParser *ArgParser::GetInstance(int argc, char **argv)
{
    if(__instance == nullptr){
        __instance = new ArgParser(argc, argv);
    }
    return __instance;
}


arguments ArgParser::getArguments()
{
    // If arguments were already parsed just return them
    if (this->__parsed)
    {
        return this->args;
    }

    // option
    int op = 0; 

    // process program options (arguments)
    while((op = getopt_long(this->_argCount, this->_progArgs, this->_short_opt.c_str(), this->_long_opt.data(), nullptr)) != -1)
    {
        switch (op)
        {
        // help option
        case 'h':
            if (this->_argCount == 2) // single argument '-h' or '--help' is used
            {
                this->__printHelp();
            }
            else
            {
                // Error message
                exit(EXIT_FAILURE);
            }
            break;
        default:
            // Unknow argument
            break;
        }
    }
    
    return this->args;
}


void ArgParser::__printHelp()
{
    cout << "\n Hello World\n"
         << endl;
    exit(EXIT_SUCCESS);
}


/* END OF FILE */