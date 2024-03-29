/**
 * @file GasCar.cpp
 * @author Michal Ľaš (xlasmi00)
 * @brief methods for Gas Car object
 * @date 2023-12-06
 *
 */

#include "GasCar.hpp"

/* static methods */

bool GasCar::canBeLoaded(ParcelBatch &parcels, const unsigned long batch_size) {
    return parcels.size(true, true) >= batch_size;
}

/* non-static methods */

GasCar::GasCar(
    ParcelBatch &parcels,
    unsigned long batch_size,
    Stat *operation_cost,
    Stat *total_cost,
    Store *garage
) : Car(
    parcels,
    batch_size,
    true,
    true,
    operation_cost,
    total_cost,
    garage
) {}

double GasCar::calculateOperationCost() {
    double distance, distance_deviation;
    if(parcels.toDistantLocation()) {
        distance = LONG_DISTANCE;
        distance_deviation = LONG_DISTANCE_DEVIATION;
    } else {
        distance = SHORT_DISTANCE;
        distance_deviation = SHORT_DISTANCE_DEVIATION;
    }

    return Uniform(MIN_DAILY_COURIER_SALARY, MAX_DAILY_COURIER_SALARY) +
        Normal(distance, distance_deviation) * CONSUMPTION * GAS_PRICE;
}
