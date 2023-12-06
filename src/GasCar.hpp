/**
 * @file GasCar.hpp
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for GasCar.c
 * @date 2023-12-05
 * 
 */


#include <simlib.h>


#ifndef GASCAR_H
#define GASCAR_H


using namespace std;


/******************** MACROS ********************/


/****************** DATATYPES *******************/



/*********** FUNCTIONS AND CLASSES **************/


class GasCar : Process
{
private:
    /* Private Attributes */
    static const double CONSUMPTION;
    /* Private Methods */

public:
    /* Public Attributes */

    /* Public Methods */
    GasCar();
    ~GasCar();
};





#endif // GASCAR_H