/**
 * @file Car.cpp
 * @author Adam Lazík (xlazik00@vutbr.cz)
 * @brief Implementation of the Car class methods
 * @date 2023-12-10
 *
 */

#include "Car.hpp"
#include <cmath> //round()

using namespace std;

/* static methods */

int Car::generateBatchSize() {
    return round(Uniform(MIN_PARCEL_BATCH_SIZE, MAX_PARCEL_BATCH_SIZE));
}

/* non-static methods */

Car::Car(
    ParcelBatch &parcels,
    unsigned long batch_size,
    const bool distant_location_allowed,
    const bool address_allowed,
    Stat *operation_cost,
    Stat *total_cost,
    Store *garage
) :
    operation_cost(operation_cost),
    total_cost(total_cost),
    garage(garage)
{
    this->parcels.load(
        parcels, batch_size, distant_location_allowed, address_allowed
    );
}

void Car::Behavior() {
    const double op_cost = calculateOperationCost();
    (*operation_cost)(op_cost);
    (*total_cost)(op_cost);
    Leave(*garage);
}
