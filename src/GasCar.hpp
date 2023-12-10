/**
 * @file GasCar.hpp
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for GasCar.c
 * @date 2023-12-05
 *
 */


#include "Car.hpp"


#ifndef GASCAR_H
#define GASCAR_H


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
    /* Public Attributes */

    /* Public Methods */
    GasCar(
        ParcelBatch &parcels,
        unsigned long batch_size,
        bool distant_location_allowed,
        Stat *operation_cost,
        Stat *total_cost,
        Store *garage
    );

    ~GasCar();
    static bool canBeLoaded(
        ParcelBatch &parcels, const unsigned long batch_size
    );

    double calculateOperationCost() override;
};





#endif // GASCAR_H
