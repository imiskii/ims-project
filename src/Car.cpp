#include "Car.hpp"
#include <cmath> //round()

//DEBUG
#include <iostream>

using namespace std;

Car::Car(
    ParcelBatch &parcels,
    unsigned long batch_size,
    bool distant_location_allowed,
    Stat *operation_cost,
    Stat *total_cost,
    Store *garage
) :
    operation_cost(operation_cost),
    total_cost(total_cost),
    garage(garage)
{
    this->parcels.load(parcels, batch_size, distant_location_allowed);
}

Car::~Car()
{
}

void Car::Behavior() {
    //DEBUG
    // cerr << "car.Behavior()\n";
    const double op_cost = calculateOperationCost();
    (*operation_cost)(op_cost);
    (*total_cost)(op_cost);
    Leave(*garage);
}

double Car::calculateOperationCost() {
    return 0; // overwritten in child classes
}

int Car::generateBatchSize() {
    return round(Uniform(MIN_PARCEL_BATCH_SIZE, MAX_PARCEL_BATCH_SIZE));
}
