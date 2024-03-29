/**
 * @file AutonomousCar.hpp
 * @author Adam Lazík (xlazik00@vutbr.cz)
 * @brief Definition of the AutonomousCar class which simulates behavior of an
 * autonomous car
 * @date 2023-12-10
 *
 */

#pragma once

#include "Car.hpp"

class AutonomousCar : public Car
{
private:
    // 0.25kWh / 100km
    static constexpr double CONSUMPTION = 0.0025;

    // time in hours
    static const int MIN_DELIVERY_TIME = 2;
    static const int MAX_DELIVERY_TIME = 6;

    // Average parcel batch size: 500
    // Deviation: 100
    static const int MIN_PARCEL_BATCH_SIZE_AUTONOMOUS = 400;
    static const int MAX_PARCEL_BATCH_SIZE_AUTONOMOUS = 600;

    // loading time in hours
    static const int MIN_LOADING_TIME = 0.5;
    static const int MAX_LOADING_TIME = 1;

public:
    /**
     * @brief return max possible time of autonomous car operation
     * (loading + delivering + rechrging)
     *
     * @return int maximum operation time
     */
    static int maxOperationTime();

    /**
     * @brief Determine if the car can be fully loaded based on available
     * parcels
     *
     * @param parcels all available parcels
     * @param batch_size generated batch size
     * @return true if car can be fully loaded
     * @return false if car cannot be fully loaded
     */
    static bool canBeLoaded(
        ParcelBatch &parcels,
        const unsigned long batch_size,
        const bool address_allowed
    );

    /**
     * @brief generate batch size for autonomous vehicle
     *
     * @return int generated batch size
     */
    static int generateBatchSizeAutonomous();

    /**
     * @brief see Car::Car()
     */
    AutonomousCar(
        ParcelBatch &parcels,
        unsigned long batch_size,
        Stat *operation_cost,
        Stat *total_cost,
        Store *garage,
        const bool address_allowed
    );

    void Behavior() override;
    double calculateOperationCost() override;
};
