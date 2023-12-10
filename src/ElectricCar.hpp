/**
 * @file ElectricCar.hpp
 * @author Adam Lazík (xlazik00@vutbr.cz)
 * @brief Definition of the ElectricCar class which simulates behavior of an
 * electric car
 * @date 2023-12-10
 *
 */

#pragma once

#include "Car.hpp"

class ElectricCar : public Car
{
private:
    // 0.3547 kWh / 100 km
    static constexpr double CONSUMPTION = 0.003547;

public:
    /**
     * @brief determine if the electric car can be loaded
     * same syntax as AutonomousCar::canBeLoaded()
     */
    static bool canBeLoaded(
        ParcelBatch &parcels, const unsigned long batch_size
    );

    /**
     * @brief see Car::Car()
     */
    ElectricCar(
        ParcelBatch &parcels,
        unsigned long batch_size,
        Stat *operation_cost,
        Stat *total_cost,
        Store *garage
    );

    double calculateOperationCost() override;
};
