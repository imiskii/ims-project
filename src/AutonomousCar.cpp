/**
 * @file AutonomousCar.cpp
 * @author Adam Lazík (xlazik00@vutbr.cz)
 * @brief Implementation of the AutonomousCar class methods
 * @date 2023-12-10
 *
 */

#include "AutonomousCar.hpp"
#include <cmath> // round()

/* static methods */

int AutonomousCar::maxOperationTime() {
    return RECHARGE_TIME + MAX_DELIVERY_TIME;
}

bool AutonomousCar::canBeLoaded(ParcelBatch &parcels, const unsigned long batch_size) {
    return parcels.size(false) >= batch_size;
}

int AutonomousCar::generateBatchSizeAutonomous() {
    return round(Uniform(
        MIN_PARCEL_BATCH_SIZE_AUTONOMOUS,
        MAX_PARCEL_BATCH_SIZE_AUTONOMOUS
    ));
}

/* non-static methods */

AutonomousCar::AutonomousCar(
    ParcelBatch &parcels,
    unsigned long batch_size,
    Stat *operation_cost,
    Stat *total_cost,
    Store *garage
) : Car(
    parcels,
    batch_size,
    false,
    operation_cost,
    total_cost,
    garage
) {}

void AutonomousCar::Behavior() {
    Wait(Uniform(MIN_DELIVERY_TIME, MAX_DELIVERY_TIME) + RECHARGE_TIME);
    Car::Behavior();
}

double AutonomousCar::calculateOperationCost() {
    return Normal(SHORT_DISTANCE, SHORT_DISTANCE_DEVIATION) *
        CONSUMPTION * ELECTRICITY_PRICE;
}
