
#include "WorkDay.hpp"
#include "consts.hpp"
#include "GasCar.hpp"
#include "ElectricCar.hpp"
#include "AutonomousCar.hpp"
#include <cmath>

//DEBUG
#include <iostream>

using namespace std;

double WorkDay::generateParcelsToDistantLocationRatio() {
    return Uniform(
        PARCELS_TO_DISTANT_LOCATION_MIN_RATIO,
        PARCELS_TO_DISTANT_LOCATION_MAX_RATIO
    );
}

WorkDay::WorkDay(
    int parcels,
    int gas_cars,
    int electric_cars,
    int autonomous_cars
) {
    cout << "\n=== WORKDAY START ===\n";

    this->gas_cars = new Store("Gas cars", gas_cars);
    this->electric_cars = new Store("Electric cars", electric_cars);
    this->autonomous_cars = new Store("Autonomous cars", autonomous_cars);
    parcels_shipped = new Stat("Parcels shipped");
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
    );

    this->parcels = ParcelBatch(start_parcels);

    resetFlags();

    cout << "+----------------------------------------------------------+\n"
         << "| Parcels to ship                                          |\n"
         << "+----------------------------------------------------------+\n";
    this->parcels.print();
}

WorkDay::~WorkDay() {
    cout << "=== WORKDAY ENDED ===\n";
    ParcelBatch parcels_shipped = start_parcels - parcels;
    cout << "+----------------------------------------------------------+\n"
         << "| Parcels shipped                                          |\n"
         << "+----------------------------------------------------------+\n";
    parcels_shipped.print();
    cout << "+----------------------------------------------------------+\n"
         << "| Total parcels shipped : "
         << parcels_shipped.size(true) << "\n"
         << "+----------------------------------------------------------+\n";
    cout << "+----------------------------------------------------------+\n"
         << "| Parcels remaining                                        |\n"
         << "+----------------------------------------------------------+\n";
    parcels.print();
    cout << "+----------------------------------------------------------+\n"
         << "| Total parcels remaining : "
         << parcels.size(true) << "\n"
         << "+----------------------------------------------------------+\n";
    gas_car_operation_cost->Output();
    cout << "+----------------------------------------------------------+\n"
         << "| Total gas car operation cost : "
         << gas_car_operation_cost->Sum() << "\n"
         << "+----------------------------------------------------------+\n";
    electric_car_operation_cost->Output();
    cout << "+----------------------------------------------------------+\n"
         << "| Total electric car operation cost : "
         << electric_car_operation_cost->Sum() << "\n"
         << "+----------------------------------------------------------+\n";
    autonomous_car_operation_cost->Output();
    cout << "+----------------------------------------------------------+\n"
         << "| Total autonomous car operation cost : "
         << autonomous_car_operation_cost->Sum() << "\n"
         << "+----------------------------------------------------------+\n";

    // FIXME: Varible length
    cout << "+----------------------------------------------------------+\n"
         << "| Total cost : " << total_cost->Sum() << "\n"
         << "+----------------------------------------------------------+\n";

    delete gas_cars;
    delete electric_cars;
    delete autonomous_cars;
    delete this->parcels_shipped;
    delete electric_car_operation_cost;
    delete autonomous_car_operation_cost;
    delete gas_car_operation_cost;
    delete total_cost;
    //cerr << "WorkdDay deleted.\n";
}

void WorkDay::Behavior() {
    Car *available_car;
    while((available_car = selectBestCar()) != nullptr) {
        available_car->Activate();
    }

    int parcel_load_size = AutonomousCar::generateBatchSizeAutonomous();

    while(AutonomousCar::canBeLoaded(parcels, parcel_load_size)) {
        Enter(*autonomous_cars);
        if(Time > 24 - AutonomousCar::MAX_DELIVERY_TIME -
            AutonomousCar::RECHARGE_TIME
        ) {
            Leave(*autonomous_cars);
            break;
        }
        (new AutonomousCar(
            parcels, parcel_load_size, false, parcels_shipped, autonomous_car_operation_cost, total_cost, autonomous_cars
        ))->Activate();
        parcel_load_size = AutonomousCar::generateBatchSizeAutonomous();
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
        (to_distant_location ||
        (autonomous_cars->Full() && electric_cars->Full())) &&
        GasCar::canBeLoaded(parcels, parcel_load_size)
    ) {
        Enter(*gas_cars);
        car = new GasCar(
            parcels, parcel_load_size, true, parcels_shipped, gas_car_operation_cost, total_cost, gas_cars
        );
    } else if(
        AutonomousCar::canBeLoaded(parcels, parcel_load_size_autonomous) &&
        !autonomous_cars->Full()
    ) {
        Enter(*autonomous_cars);
        car = new AutonomousCar(
            parcels, parcel_load_size_autonomous, false, parcels_shipped, autonomous_car_operation_cost, total_cost, autonomous_cars
        );
    } else if (
        !electric_cars->Full() &&
        ElectricCar::canBeLoaded(parcels, parcel_load_size)
    ) {
        Enter(*electric_cars);
        car = new ElectricCar(
            parcels, parcel_load_size, false, parcels_shipped, electric_car_operation_cost, total_cost, electric_cars
        );
    }

    //DEBUG
    //cerr << "returning car.\n";
    resetFlags();
    return car;
}

void WorkDay::resetFlags() {
    to_address = parcels.toAddress();
    to_distant_location = parcels.toDistantLocation();
}
