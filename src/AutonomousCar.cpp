#include "AutonomousCar.hpp"
#include <cmath> // round

AutonomousCar::AutonomousCar(
    ParcelBatch &parcels,
    unsigned long batch_size,
    bool distant_location_allowed,
    Stat *parcels_shipped,
    Stat *operation_cost,
    Stat *total_cost,
    Store *garage
) : Car(
    parcels,
    batch_size,
    distant_location_allowed,
    parcels_shipped,
    operation_cost,
    total_cost,
    garage
)
{
}

AutonomousCar::~AutonomousCar()
{
}

bool AutonomousCar::canBeLoaded(ParcelBatch &parcels, const unsigned long batch_size) {
    return parcels.size(false) >= batch_size;
}

void AutonomousCar::Behavior() {
    Wait(Uniform(MIN_DELIVERY_TIME, MAX_DELIVERY_TIME) + RECHARGE_TIME);
    Car::Behavior();
}

double AutonomousCar::calculateOperationCost() {
    return Normal(SHORT_DISTANCE, SHORT_DISTANCE_DEVIATION) *
        CONSUMPTION * ELECTRICITY_PRICE;
}

int AutonomousCar::generateBatchSizeAutonomous() {
    return round(Uniform(
        MIN_PARCEL_BATCH_SIZE_AUTONOMOUS,
        MAX_PARCEL_BATCH_SIZE_AUTONOMOUS
    ));
}
