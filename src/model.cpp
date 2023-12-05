/**
 * @file model.cpp
 * @authors Adam Lazík (xlazik00@vutbr.cz), Michal Ľaš (xlasmi00@vutbr.cz)
 * @brief Implementation of simulation model for IMS project assignment 2023
 * @date 2023-12-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "model.hpp"
#include "argparser.hpp"

using namespace std;

int main(int argc, char **argv) {
    ArgParser *arg_parser = ArgParser::GetInstance(argc, argv);
    //struct arguments args = arg_parser->getArguments();
    arg_parser->getArguments();
    arg_parser->printArgs();
}
