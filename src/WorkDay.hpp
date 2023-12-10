
#pragma once

#include <simlib.h>
#include "Car.hpp"
#include "ParcelBatch.hpp"

class WorkDay : public Process
{
private:
    static constexpr double PARCELS_TO_DISTANT_LOCATION_MIN_RATIO = 0.02;
    static constexpr double PARCELS_TO_DISTANT_LOCATION_MAX_RATIO = 0.08;

    ParcelBatch start_parcels;
    ParcelBatch parcels;

    bool to_address;
    bool to_distant_location;

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
    void resetFlags();

public:
    static const int WORKDAY_END = 24; // 24 hours in a work day

    WorkDay(int parcels, int gas_cars, int electric_cars, int autonomous_cars);
    ~WorkDay() override;
    void Behavior() override;
};
