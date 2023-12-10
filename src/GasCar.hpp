/**
 * @file GasCar.hpp
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for GasCar.cpp
 * @date 2023-12-05
 *
 */

#ifndef GASCAR_H
#define GASCAR_H

#include "Car.hpp"

using namespace std;


/******************** MACROS ********************/


/****************** DATATYPES *******************/



/*********** FUNCTIONS AND CLASSES **************/


class GasCar : public Car
{
private:
    // 8.8 l / 100 km
    static constexpr double CONSUMPTION = 0.088;

public:
    /**
     * @brief check AutonomousCar::canBeLoaded()
     */
    static bool canBeLoaded(
        ParcelBatch &parcels, const unsigned long batch_size
    );

    /**
     * @brief check Car::Car()
     */
    GasCar(
        ParcelBatch &parcels,
        unsigned long batch_size,
        Stat *operation_cost,
        Stat *total_cost,
        Store *garage
    );

    double calculateOperationCost() override;
};





#endif // GASCAR_H
