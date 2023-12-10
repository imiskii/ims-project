/**
 * @file ElectricCar.cpp
 * @author Adam Lazík (xlazik00@vutbr.cz)
 * @brief Implementation of the ElectricCar class methods
 * @date 2023-12-10
 *
 */


#include "ElectricCar.hpp"

/* static methods */

bool ElectricCar::canBeLoaded(ParcelBatch &parcels, const unsigned long batch_size) {
    return parcels.size(false, true) >= batch_size;
}

/* non_static methods*/

ElectricCar::ElectricCar(
    ParcelBatch &parcels,
    unsigned long batch_size,
    Stat *operation_cost,
    Stat *total_cost,
    Store *garage
) : Car(
    parcels,
    batch_size,
    false,
    true,
    operation_cost,
    total_cost,
    garage
)
{
}

double ElectricCar::calculateOperationCost() {
    return Uniform(MIN_DAILY_COURIER_SALARY, MAX_DAILY_COURIER_SALARY) +
        Normal(SHORT_DISTANCE, SHORT_DISTANCE_DEVIATION)
            * CONSUMPTION * ELECTRICITY_PRICE;
}
