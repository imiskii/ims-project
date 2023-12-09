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
        bool distant_location_allowed,
        Stat *parcels_shipped,
        Stat *operation_cost,
        Stat *total_cost,
        Store *garage
    );
    ~ElectricCar();
    double calculateOperationCost() override;
    static bool canBeLoaded(
        ParcelBatch &parcels, const unsigned long batch_size
    );
};
