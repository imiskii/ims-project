/**
 * @file WorkDay.hpp
 * @author Adam Lazík (xlazik00@vutbr.cz)
 * @brief Implementation of the WorkDay class represeting the model of this
 * project
 * @date 2023-12-10
 *
 */

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
    static constexpr double PARCELS_TO_ZBOX_RATIO = 0.21;

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

    static double __generateParcelsToDistantLocationRatio();

    /**
     * @brief Select best car based on car and parcels available
     * @return Car* selected car or nullptr if no car is available
     */
    Car *__selectBestCar();

    /**
     * @brief create new GasCar object based on the generated parcel size
     * @param batch_size generated parcel size
     * @return GasCar* pointer to the GasCar object
     */
    GasCar *__newGasCar(const unsigned long batch_size);

    /**
     * @brief create new ElectricCar object based on the generated parcel size
     * @param batch_size generated parcel size
     * @return ElectricCar* pointer to the ElectricCar object
     */
    ElectricCar *__newElectricCar(const unsigned long batch_size);

    /**
     * @brief create new AutonomousCar object based on the generated parcel size
     * and type of parcels being allowed in the parcel batch
     * @param batch_size generated parcel size
     * @param address_allowed packets headed for address or pick-up point
     * allowed
     * @return AutonomousCar* pointer to the AutonomousCar object
     */
    AutonomousCar *__newAutonomousCar(
        const unsigned long batch_size, const bool address_allowed
    );

    /**
     * @brief print out parameters given before the start of the model
     */
    void __printStart();

    /**
     * @brief print out statistics collected by the model
     */
    void __printStats();

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
