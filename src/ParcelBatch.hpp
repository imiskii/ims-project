/**
 * @file ParcelBatch.hpp
 * @author Adam Lazík (xlazik00@vutbr.cz)
 * @brief Definition of the ParcelBatch class which represent a batch of parcels
 * either to be shipped in a car or available in the depot storage
 * @date 2023-12-10
 *
 */

#pragma once

using namespace std;

class ParcelBatch
{
public:
    unsigned long parcels_to_distant_address = 0;
    unsigned long parcels_to_near_address = 0;
    unsigned long parcels_to_distant_zbox = 0;
    unsigned long parcels_to_near_zbox = 0;

    ParcelBatch() = default;
    ParcelBatch(const ParcelBatch &batch) = default;
    ParcelBatch(
        unsigned long parcels_to_distant_address,
        unsigned long parcels_to_near_address,
        unsigned long parcels_to_distant_zbox,
        unsigned long parcels_to_near_zbox
    );

    ParcelBatch operator-(const ParcelBatch &batch);
    ParcelBatch operator+(const ParcelBatch &batch);

    /**
     * @brief check if batch contains parcels shipped to distant location
     *
     * @return true if batch contains parcels shipped to distant location
     * @return false if batch does not parcels shipped to distant location
     */
    bool toDistantLocation();

    /**
     * @brief check if batch contains parcels shipped to address or pick-up
     * point
     *
     * @return true if batch contains parcels shipped to address or pick-up
     * point
     * @return false if batch does not parcels shipped to address or pick-up
     * point
     */
    bool toAddress();

    /**
     * @brief return number of parcels in a batch based on given parameters
     *
     * @param distant_location_allowed include parcels headed for distant
     * location in a batch
     * @param address_allowed include parcels headed for address or pick-up
     * point
     * @return unsigned long batch size
     */
    unsigned long size(
        const bool distant_location_allowed, const bool address_allowed
    );

    /**
     * @brief load batch with parcels from another batch based on given
     * parameters
     *
     * @param batch batch with parcels to be loaded
     * @param batch_size number of parcels to be loaded
     * @param distant_location_allowed parcels headed for distant location are
     * allowed
     * @param address_allowed parcels headed for address or pick-up point are
     * allowed
     */
    void load(
        ParcelBatch &batch,
        unsigned long batch_size,
        const bool distant_location_allowed,
        const bool address_allowed
    );

    /**
     * @brief print contents of the batch
     */
    void print();
};
