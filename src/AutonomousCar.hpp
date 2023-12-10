#pragma once

#include "Car.hpp"

class AutonomousCar : public Car
{
private:
    // 0.084kWh / 100km
    static constexpr double CONSUMPTION = 0.00084; // TODO: check value

public:
    static const int MIN_DELIVERY_TIME = 2;
    static const int MAX_DELIVERY_TIME = 6;
    static constexpr double RECHARGE_TIME = 0.5; // TODO: check value

    // Average parcel batch size: 500
    // Deviation: 100
    static const int MIN_PARCEL_BATCH_SIZE_AUTONOMOUS = 400;
    static const int MAX_PARCEL_BATCH_SIZE_AUTONOMOUS = 600;

    AutonomousCar(
        ParcelBatch &parcels,
        unsigned long batch_size,
        bool distant_location_allowed,
        Stat *operation_cost,
        Stat *total_cost,
        Store *garage
    );
    ~AutonomousCar();
    static bool canBeLoaded(
        ParcelBatch &parcels, const unsigned long batch_size
    );

    void Behavior() override;
    double calculateOperationCost() override;
    static int generateBatchSizeAutonomous(); // different batch size limits
};
