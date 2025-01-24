#ifndef __DUFFS_DEVICE_H
#define __DUFFS_DEVICE_H


#define connect(a, b) a##b
#define unique_name(name) connect(name, cases)

#define duffs_device8_case(n) case n: *to++ = *from++;

#define DUFFS_DEVICE_AUTO_CASE_0
#define DUFFS_DEVICE_AUTO_CASE_1 duffs_device8_case(1) DUFFS_DEVICE_AUTO_CASE_0
#define DUFFS_DEVICE_AUTO_CASE_2 duffs_device8_case(2) DUFFS_DEVICE_AUTO_CASE_1
#define DUFFS_DEVICE_AUTO_CASE_3 duffs_device8_case(3) DUFFS_DEVICE_AUTO_CASE_2
#define DUFFS_DEVICE_AUTO_CASE_4 duffs_device8_case(4) DUFFS_DEVICE_AUTO_CASE_3
#define DUFFS_DEVICE_AUTO_CASE_5 duffs_device8_case(5) DUFFS_DEVICE_AUTO_CASE_4
#define DUFFS_DEVICE_AUTO_CASE_6 duffs_device8_case(6) DUFFS_DEVICE_AUTO_CASE_5
#define DUFFS_DEVICE_AUTO_CASE_7 duffs_device8_case(7) DUFFS_DEVICE_AUTO_CASE_6


#define DUFFS_DEVICE8_(from, to, count, name) \
    do {    \
        int connect(n, name) = (count + 7) / 8; \
        switch(count % 8) { \
            case 0: do { *to++ = *from++; \
                        DUFFS_DEVICE_AUTO_CASE_7 \
                    } while(--connect(n, name) > 0); \
        } \
    } while(0)


#define DUFFS_DEVICE8(from, to, count) \
    DUFFS_DEVICE8_(from, to, count, unique_name(__func__))

#endif