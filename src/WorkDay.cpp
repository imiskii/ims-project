#include "WorkDay.hpp"
#include "consts.hpp"
#include "GasCar.hpp"
#include "ElectricCar.hpp"
#include "AutonomousCar.hpp"
#include <cmath>
#include <iostream>
#include "Formatter.hpp"

using namespace std;

double WorkDay::generateParcelsToDistantLocationRatio() {
    return Uniform(
        PARCELS_TO_DISTANT_LOCATION_MIN_RATIO,
        PARCELS_TO_DISTANT_LOCATION_MAX_RATIO
    );
}

GasCar *WorkDay::newGasCar(const unsigned long batch_size) {
    return new GasCar(
        parcels,
        batch_size,
        gas_car_operation_cost,
        total_cost,
        gas_cars
    );
}

ElectricCar *WorkDay::newElectricCar(const unsigned long batch_size) {
    return new ElectricCar(
        parcels,
        batch_size,
        electric_car_operation_cost,
        total_cost,
        electric_cars
    );
}

AutonomousCar *WorkDay::newAutonomousCar(
    const unsigned long batch_size, const bool address_allowed
) {
    return new AutonomousCar(
        parcels,
        batch_size,
        autonomous_car_operation_cost,
        total_cost,
        autonomous_cars,
        address_allowed
    );
}

void WorkDay::printStart() {
    cout << "\n=== WORKDAY START ===\n";
    Formatter::printHeading("Parcels to ship");
    parcels.print();
    Formatter::printStatistic(
        "Total parcels to ship: " + to_string(parcels.size(true, true))
    );
}

void WorkDay::printStats() {
    ParcelBatch parcels_shipped = start_parcels - parcels;
    Formatter::printHeading("Parcels shipped");
    parcels_shipped.print();
    Formatter::printStatistic(
        "Total parcels shipped: " + to_string(parcels_shipped.size(true, true))
    );
    Formatter::printHeading("Parcels remaining");\
    parcels.print();
    Formatter::printStatistic(
        "Total parcels remaining: " + to_string(parcels.size(true, true))
    );
    gas_car_operation_cost->Output();
    Formatter::printStatistic(
        "Total gas car operation cost: " +
        to_string(gas_car_operation_cost->Sum())
    );
    electric_car_operation_cost->Output();
    Formatter::printStatistic(
        "Total electric car operation cost: " +
        to_string(electric_car_operation_cost->Sum())
    );
    autonomous_car_operation_cost->Output();
    Formatter::printStatistic(
        "Total autonomous car operation cost: " +
        to_string(autonomous_car_operation_cost->Sum())
    );
    Formatter::printStatistic("Total cost: " + to_string(total_cost->Sum()));
}

WorkDay::WorkDay(
    int parcels,
    int gas_cars,
    int electric_cars,
    int autonomous_cars,
    ParcelBatch *parcels_remaining
) : parcels_remaining(parcels_remaining)
{
    this->gas_cars = new Store("Gas cars", gas_cars);
    this->electric_cars = new Store("Electric cars", electric_cars);
    this->autonomous_cars = new Store("Autonomous cars", autonomous_cars);
    gas_car_operation_cost = new Stat("Gas car operation cost");
    electric_car_operation_cost = new Stat("Electric car operation cost");
    autonomous_car_operation_cost = new Stat("Autonomous car operation cost");
    total_cost = new Stat("Total cost");

    unsigned long parcels_to_zbox = round(PARCELS_TO_ZBOX_RATIO * parcels);
    unsigned long parcels_to_address = parcels - parcels_to_zbox;

    /* parcels to address */
    unsigned long p_to_distant_address = round(
        parcels_to_address * generateParcelsToDistantLocationRatio()
    );
    unsigned long p_to_near_address = parcels_to_address - p_to_distant_address;

    /* parcels to zbox */
    unsigned long p_to_distant_zbox = round(
        parcels_to_zbox * generateParcelsToDistantLocationRatio()
    );
    unsigned long p_to_near_zbox = parcels_to_zbox - p_to_distant_zbox;

    start_parcels = ParcelBatch(
        p_to_distant_address,
        p_to_near_address,
        p_to_distant_zbox,
        p_to_near_zbox
    ) + *parcels_remaining; // remainder from the previous day

    this->parcels =  ParcelBatch(start_parcels);

    printStart();
}

WorkDay::~WorkDay() {
    cout << "=== WORKDAY ENDED ===\n";
    printStats();

    *parcels_remaining = parcels;

    delete gas_cars;
    delete electric_cars;
    delete autonomous_cars;
    delete electric_car_operation_cost;
    delete autonomous_car_operation_cost;
    delete gas_car_operation_cost;
    delete total_cost;
}

void WorkDay::Behavior() {
    Car *available_car;
    while((available_car = selectBestCar()) != nullptr) {
        available_car->Activate();
    }

    int parcel_load_size = AutonomousCar::generateBatchSizeAutonomous();
    while(Time < WORKDAY_END) {
        Enter(*autonomous_cars);
        if(Time >= WorkDay::WORKDAY_END - AutonomousCar::maxOperationTime()) {
            Leave(*autonomous_cars);
            break;
        }
        bool address_allowed =
            Time <= ADDRESS_DELIVERY_END - AutonomousCar::maxOperationTime();
        if(AutonomousCar::canBeLoaded(
            parcels,
            parcel_load_size,
            address_allowed)
        ) {
            newAutonomousCar(parcel_load_size, address_allowed)->Activate();
            // next batch size
            parcel_load_size = AutonomousCar::generateBatchSizeAutonomous();
        } else {
            Leave(*autonomous_cars);
            break;
        }
    }

    Enter(*autonomous_cars, autonomous_cars->Capacity());
    Enter(*electric_cars, electric_cars->Capacity());
    Enter(*gas_cars, gas_cars->Capacity());
}

bool WorkDay::carAvailable() {
    return !(
        gas_cars->Full() && electric_cars->Full() && autonomous_cars->Full()
    );
}

Car *WorkDay::selectBestCar() {
    int parcel_load_size = Car::generateBatchSize();
    int parcel_load_size_autonomous =
        AutonomousCar::generateBatchSizeAutonomous();

    Car *car = nullptr;

    if(
        !gas_cars->Full() &&
        (parcels.toDistantLocation() ||
        (autonomous_cars->Full() && electric_cars->Full())) &&
        GasCar::canBeLoaded(parcels, parcel_load_size)
    ) {
        Enter(*gas_cars);
        car = newGasCar(parcel_load_size);
    } else if(
        AutonomousCar::canBeLoaded(parcels, parcel_load_size_autonomous, true)
        && !autonomous_cars->Full()
    ) {
        Enter(*autonomous_cars);
        car = newAutonomousCar(parcel_load_size_autonomous, true);
    } else if (
        !electric_cars->Full() &&
        ElectricCar::canBeLoaded(parcels, parcel_load_size)
    ) {
        Enter(*electric_cars);
        car = newElectricCar(parcel_load_size);
    }

    return car;
}
