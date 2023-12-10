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

    bool toDistantLocation();

    bool toAddress();

    unsigned long size(const bool distant_location_allowed);

    void load(
        ParcelBatch &batch,
        unsigned long batch_size,
        const bool distant_location_allowed
    );

    void print();
};
