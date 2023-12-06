/**
 * @file consts.hpp
 * @author Michal Ľaš (xlasmi00)
 * @brief Constants values and common functions for model simulation
 * @date 2023-12-06
 * 
 */


#ifndef CONSTS_H
#define CONSTS_H

#include <time.h>

using namespace std;


/******************** MACROS ********************/

#define SEED time(NULL)

/* Gas car */
#define GAS_CAR_CONSUMPTION 8.8 // 8,8 l/100km
#define GAS_CAR_MAX_DAY_DELIVERY 0 // parcels (1374)
#define GAS_CAR_MAX_DAY_DELIVERY_DEVIATION 0 // parcels (200)
#define GAS_PRICE 1.705 // 1.705€/l liters

/* Electric car */
#define ELECTRIC_CAR_CONSUMPTION 0.35 // 0.3547kWh/100km
#define ELECTRIC_CAR_MAX_DAY_DELIVERY 0 // parcels (1374)
#define ELECTRIC_CAR_MAX_DAY_DELIVERY_DEVIATION 0 // parcels (200)

#define COURIER_SALARY 0 // 1600€-2000€/month

/* Autonomus car */
#define AUTONOMUS_CAR_CONSUMPTION 0.084 // 0.084kWh/100km
#define AUTONOMUS_CAR_MAX_LOAD 600 // parcels
#define AUTONOMUS_CAR_MAX_DELIVERY_RANGE 180 // kilometers
#define AUTONOMUS_CAR_CHARGE_TIME 30 // minutes
#define AUTONOMUS_CAR_DELIVERY_TIME 4 // hours
#define AUTONOMUS_CAR_DELIVERY_TIME_DEVIATION 2 // hours

#define ELECTRICITY_PRICE 0.185 // 0.185€/1kWh

/* Delivery locations */
#define LOCKERS_POPULARITY 21 // percentage
#define ON_ADDRESS_POPULARITY 44 // percentage
#define PICK_UP_POINTS_POPULARITY 35 // percentage

/* Delivery distances */
#define LONG_DISTANCE 190 // kilometers
#define LONG_DISTANCE_DEVIATION 10 //
#define LOND_DISTANCE_PERCENTAGE 0 // percentage (2-8%)

#define SHORT_DISTANCE 140 // kilometers
#define SHORT_DISTANCE_DEVIATION 10 // kilometers
#define SHORT_DISTANCE_DEVIATION 0 // percentage (92-98%)



/****************** DATATYPES *******************/



/*********** FUNCTIONS AND CLASSES **************/



#endif // CONSTS_H