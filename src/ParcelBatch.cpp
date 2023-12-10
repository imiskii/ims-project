#include "ParcelBatch.hpp"
#include <algorithm>
#include "Formatter.hpp"

using namespace std;

ParcelBatch::ParcelBatch(
    unsigned long parcels_to_distant_address,
    unsigned long parcels_to_near_address,
    unsigned long parcels_to_distant_zbox,
    unsigned long parcels_to_near_zbox
) :
    parcels_to_distant_address(parcels_to_distant_address),
    parcels_to_near_address(parcels_to_near_address),
    parcels_to_distant_zbox(parcels_to_distant_zbox),
    parcels_to_near_zbox(parcels_to_near_zbox)
{
}

ParcelBatch ParcelBatch::operator-(const ParcelBatch &batch) {
    return ParcelBatch(
        parcels_to_distant_address - batch.parcels_to_distant_address,
        parcels_to_near_address - batch.parcels_to_near_address,
        parcels_to_distant_zbox - batch.parcels_to_distant_zbox,
        parcels_to_near_zbox - batch.parcels_to_near_zbox
    );
}

ParcelBatch ParcelBatch::operator+(const ParcelBatch &batch) {
    return ParcelBatch(
        parcels_to_distant_address + batch.parcels_to_distant_address,
        parcels_to_near_address + batch.parcels_to_near_address,
        parcels_to_distant_zbox + batch.parcels_to_distant_zbox,
        parcels_to_near_zbox + batch.parcels_to_near_zbox
    );
}

bool ParcelBatch::toDistantLocation() {
    return parcels_to_distant_address + parcels_to_distant_zbox;
}

bool ParcelBatch::toAddress() {
    return parcels_to_distant_address + parcels_to_near_address;
}

unsigned long ParcelBatch::size(const bool distant_location_allowed) {
    return parcels_to_near_address
        + parcels_to_near_zbox
        + (
            distant_location_allowed ?
            parcels_to_distant_address + parcels_to_distant_zbox : 0
        );
}

void ParcelBatch::load(
    ParcelBatch &batch,
    unsigned long load_size,
    const bool distant_location_allowed
) {
    while(load_size != 0) {
        unsigned long *unloading_parcel_type;
        unsigned long *loading_parcel_type;
        if(batch.parcels_to_distant_address && distant_location_allowed) {
            unloading_parcel_type = &batch.parcels_to_distant_address;
            loading_parcel_type = &parcels_to_distant_address;
        } else if (batch.parcels_to_distant_zbox && distant_location_allowed) {
            unloading_parcel_type = &batch.parcels_to_distant_zbox;
            loading_parcel_type = &parcels_to_distant_zbox;
        } else if (batch.parcels_to_near_address) {
            unloading_parcel_type = &batch.parcels_to_near_address;
            loading_parcel_type = &parcels_to_near_address;
        } else {
            unloading_parcel_type = &batch.parcels_to_near_zbox;
            loading_parcel_type = &parcels_to_near_zbox;
        }
        unsigned long partial_load_size = min(
            load_size, *unloading_parcel_type
        );

        *loading_parcel_type += partial_load_size;
        *unloading_parcel_type -= partial_load_size;
        load_size -= partial_load_size;
    }
}

void ParcelBatch::print() {
    Formatter::printSeparator();
    Formatter::align(
        "parcels to distant address: " + to_string(parcels_to_distant_address)
    );
    Formatter::align(
        "parcels to near address: " + to_string(parcels_to_near_address)
    );
    Formatter::align(
        "parcels to distant zbox: " + to_string(parcels_to_distant_zbox)
    );
    Formatter::align(
        "parcels to near zbox: " + to_string(parcels_to_near_zbox)
    );
    Formatter::printSeparator();
}
