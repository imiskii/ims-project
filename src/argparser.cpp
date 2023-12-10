/**
 * @file argparse.cpp
 * @author Michal Ľaš (xlasmi00)
 * @brief classes, function and methods for program argument parsing
 * @date 2023-12-03
 *
 */


#include "argparser.hpp"
#include "Formatter.hpp"
#include <cstring>

using namespace std;


ArgParser::ArgParser(int argc, char **argv): _argCount(argc), _progArgs(argv)
{
    this->__parsed = false;
    this->_short_opt = "hd:g:e:a:p:";
    this->_long_opt = {
        {"help", no_argument, nullptr, 'h'},
        {"days", required_argument, nullptr, 'd'},
        {"gas_cars", required_argument, nullptr, 'g'},
        {"electric_cars", required_argument, nullptr, 'c'},
        {"autonomous_cars", required_argument, nullptr, 'a'},
        {"parcel", required_argument, nullptr, 'p'}
    };
    // set implicit arg values to 0
    memset(&this->args, 0, sizeof(struct arguments));
    this->args.days = 1;
    this->flags = {false};
}

ArgParser *ArgParser::GetInstance(int argc, char **argv)
{
    static ArgParser *__instance = nullptr;
    if(__instance == nullptr){
        __instance = new ArgParser(argc, argv);
    }
    return __instance;
}

int ArgParser::__parseUnsignedInt(char *str) {
    char *endptr;
    int value = strtol(str, &endptr, 10);
    if(*endptr || value < 0) {
        cerr << "'" << str << "' is not valid unsigned integer." << endl;
        exit(EXIT_FAILURE);
    }
    return value;
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
            // single argument '-h' or '--help' is used
            if (this->_argCount == 2) {
                this->__printHelp();
            } else {
                cerr << "no arguments allowed with -h|--help." << endl;
                exit(EXIT_FAILURE);
            }
            break;
        case 'd':
            args.days = __parseUnsignedInt(optarg);
            break;
        case 'g':
            args.gas_cars = __parseUnsignedInt(optarg);
            break;
        case 'e':
            args.electric_cars = __parseUnsignedInt(optarg);
            break;
        case 'a':
            args.autonomous_cars = __parseUnsignedInt(optarg);
            break;
        case 'p':
            args.parcels = __parseUnsignedInt(optarg);
            break;
        default:
            exit(EXIT_FAILURE); // error message comes from getopt
            break;
        }
    }

    if(args.autonomous_cars + args.electric_cars + args.gas_cars == 0) {
        cerr << "At least one car type must be specified." << endl;
        exit(EXIT_FAILURE);
    } else if (args.parcels == 0) {
        cerr << "Number of parcels must be specified." << endl;
        exit(EXIT_FAILURE);
    } else if (args.days == 0) {
        cerr << "Number days must be a positive integer." << endl;
        exit(EXIT_FAILURE);
    }

    this->__parsed = true;
    return this->args;
}

// DEBUG PRINT
void ArgParser::printArgs() {
    if(!__parsed) {
        return;
    }
    Formatter::printSeparator();
    Formatter::align("Days: " + to_string(args.days));
    Formatter::align("Gas cars: " + to_string(args.gas_cars));
    Formatter::align("Electric cars: " + to_string(args.electric_cars));
    Formatter::align("Autonomous cars: " + to_string(args.autonomous_cars));
    Formatter::align("Parcels per day: " + to_string(args.parcels));
    Formatter::printSeparator();
}

void ArgParser::__printHelp()
{
    cout << "Usage: \n"
         << "./main -p|--parcels PARCELS -g|-e|-a CARS [OPTIONS]\n"
         << "\n-p|--parcels PARCELS\n"
         << "   Number of parcels per day to run the simulation with.\n"
         << "   PARCELS must be a positive integer.\n"
         << "\n-g|-e|-a CARS\n"
         << "   Number of cars to run the simulation with. At least\n"
         << "   one car type must be specified. Car types are\n"
         << "   explained below.\n"
         << "   CARS must be a positive integer.\n"
         << "\nOPTIONS:\n"
         << "-d|--days\n"
         << "   Number of days to run the simulation on.\n"
         << "   Default value: 1\n"
         << "-g|--gas_cars\n"
         << "   Number of gas cars to run the simulation with\n"
         << "   Default value: 0\n"
         << "-e|--electric_cars\n"
         << "   Number of electric cars to run the simulation with\n"
         << "   Default value: 0\n"
         << "-a|--autonomous_cars\n"
         << "   Number of autonomous cars to run the simulation with\n"
         << "   Default value: 0"
         << endl;
    exit(EXIT_SUCCESS);
}


/* END OF FILE */
