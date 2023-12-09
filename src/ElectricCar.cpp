#include "ElectricCar.hpp"

ElectricCar::ElectricCar(
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

ElectricCar::~ElectricCar()
{
}

double ElectricCar::calculateOperationCost() {
    return Uniform(MIN_DAILY_COURIER_SALARY, MAX_DAILY_COURIER_SALARY) +
        Normal(SHORT_DISTANCE, SHORT_DISTANCE_DEVIATION)
            * CONSUMPTION * ELECTRICITY_PRICE;
}

bool ElectricCar::canBeLoaded(ParcelBatch &parcels, const unsigned long batch_size) {
    return parcels.size(false) >= batch_size;
}
