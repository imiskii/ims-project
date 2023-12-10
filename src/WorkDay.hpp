
#pragma once

#include <simlib.h>
#include "GasCar.hpp"
#include "ElectricCar.hpp"
#include "AutonomousCar.hpp"
#include "ParcelBatch.hpp"

class WorkDay : public Process
{
private:
    static constexpr double PARCELS_TO_DISTANT_LOCATION_MIN_RATIO = 0.02;
    static constexpr double PARCELS_TO_DISTANT_LOCATION_MAX_RATIO = 0.08;

    ParcelBatch start_parcels;
    ParcelBatch parcels;
    ParcelBatch *parcels_remaining;

    Store *gas_cars;
    Store *electric_cars;
    Store *autonomous_cars;

    Stat *gas_car_operation_cost;
    Stat *electric_car_operation_cost;
    Stat *autonomous_car_operation_cost;
    Stat *total_cost;

    static double generateParcelsToDistantLocationRatio();

    bool carAvailable();
    Car *selectBestCar();

    GasCar *newGasCar(const unsigned long batch_size);
    AutonomousCar *newAutonomousCar(
        const unsigned long batch_size, const bool address_allowed
    );
    ElectricCar *newElectricCar(const unsigned long batch_size);
    void printStart();
    void printStats();

public:
    static const int WORKDAY_START = 8; // work day starts at 8:00
    // parcels to addresses can only be delivered until 18:00
    static const int ADDRESS_DELIVERY_END = 18;
    // workday ends after 24 hours
    static const int WORKDAY_END = WORKDAY_START + 24;


    WorkDay(
        int parcels,
        int gas_cars,
        int electric_cars,
        int autonomous_cars,
        ParcelBatch *parcels_remaining
    );
    ~WorkDay() override;
    void Behavior() override;
};
