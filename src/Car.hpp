#pragma once

#include <simlib.h>
#include "ParcelBatch.hpp"
#include "consts.hpp"

class Car : public Process
{
protected:
    // monthly salary divided by 20 work days in a month (in euros)
    static constexpr double MIN_DAILY_COURIER_SALARY = 1600.0 / 20;
    static constexpr double MAX_DAILY_COURIER_SALARY = 2000.0 / 20;

    // distance in km
    static constexpr double LONG_DISTANCE = 190;
    static constexpr double LONG_DISTANCE_DEVIATION = 10;
    static constexpr double SHORT_DISTANCE = 140;
    static constexpr double SHORT_DISTANCE_DEVIATION = 10;

    // fuel costs
    // 0.185 € / 1 kWh
    static constexpr double ELECTRICITY_PRICE = 0.185;
    // 1.705€ / l liter
    static constexpr double GAS_PRICE = 1.705;

    // Average parcel batch size: 1374
    // Deviation: 200
    static const int MIN_PARCEL_BATCH_SIZE = 1174;
    static const int MAX_PARCEL_BATCH_SIZE = 1574;

    ParcelBatch parcels;
    Stat *operation_cost;
    Stat *total_cost;
    Store *garage;

public:
    Car(
        ParcelBatch &parcels,
        unsigned long batch_size,
        bool distant_location_allowed,
        Stat *operation_cost,
        Stat *total_cost,
        Store *garage
    );

    virtual double calculateOperationCost() = 0;
    void Behavior() override;
    static int generateBatchSize();
};
