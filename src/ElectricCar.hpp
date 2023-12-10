#pragma once

#include "Car.hpp"

class ElectricCar : public Car
{
private:
    // 0.3547 kWh / 100 km
    static constexpr double CONSUMPTION = 0.003547;

public:
    ElectricCar(
        ParcelBatch &parcels,
        unsigned long batch_size,
        Stat *operation_cost,
        Stat *total_cost,
        Store *garage
    );
    double calculateOperationCost() override;
    static bool canBeLoaded(
        ParcelBatch &parcels, const unsigned long batch_size
    );
};
