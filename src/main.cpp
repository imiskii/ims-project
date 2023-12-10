/**
 * @file main.cpp
 * @authors Adam Lazík (xlazik00@vutbr.cz), Michal Ľaš (xlasmi00@vutbr.cz)
 * @brief Implementation of simulation model for IMS project assignment 2023
 * @date 2023-12-02
 *
 */

#include <iostream>
#include <simlib.h>
#include "argparser.hpp"
#include "WorkDay.hpp"

using namespace std;

int main(int argc, char **argv) {
    ArgParser *arg_parser = ArgParser::GetInstance(argc, argv);
    struct arguments args = arg_parser->getArguments();
    cout << "=== SIMULATION START ===\n";
    arg_parser->printArgs();

    RandomSeed(time(nullptr));
    ParcelBatch parcels_remaining;

    for (size_t i = 0; i < args.days; ++i) {
        Init(WorkDay::WORKDAY_START, WorkDay::WORKDAY_END);
        (new WorkDay(
            args.parcels,
            args.gas_cars,
            args.electric_cars,
            args.autonomous_cars,
            &parcels_remaining)
        )->Activate();
        Run();
    }
    cout << "=== SIMULATION ENDED ===\n";
}
