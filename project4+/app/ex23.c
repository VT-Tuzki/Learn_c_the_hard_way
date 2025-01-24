#include <stdio.h>
#include <string.h>
#include "../include/dbg.h"
#include "../include/run_time.h"

#include "../include/duffs_device.h"
#include <sys/resource.h>
double diff_in_seconds(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int normal_copy(char *from, char *to, int count)
{
    int i = 0;

    for(i = 0; i < count; i++) {
        to[i] = from[i];
    }

    return i;
}

int duffs_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;

        switch(count % 8) {
            case 0: do { *to++ = *from++;
                        case 7: *to++ = *from++;
                        case 6: *to++ = *from++;
                        case 5: *to++ = *from++;
                        case 4: *to++ = *from++;
                        case 3: *to++ = *from++;
                        case 2: *to++ = *from++;
                        case 1: *to++ = *from++;
                    } while(--n > 0);
        }
    }

    return count;
}

int zeds_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;

        switch(count % 8) {
            case 0:
            again: *to++ = *from++;

            case 7: *to++ = *from++;
            case 6: *to++ = *from++;
            case 5: *to++ = *from++;
            case 4: *to++ = *from++;
            case 3: *to++ = *from++;
            case 2: *to++ = *from++;
            case 1: *to++ = *from++;
                    if(--n > 0) goto again;
        }
    }

    return count;
}

int valid_copy(char *data, int count, char expects)
{
    int i = 0;
    for(i = 0; i < count; i++) {
        if(data[i] != expects) {
            log_err("[%d] %c != %c", i, data[i], expects);
            return 0;
        }
    }

    return 1;
}

int define_duffs_device(char *from, char *to, int count)
{
    DUFFS_DEVICE8(from, to, count);
    return count;
}


#define COUNT 4000000
#define size_1gb (1024*1024*1024)
int main(int argc, char *argv[])
{
    struct rlimit limit;

    getrlimit (RLIMIT_STACK, &limit);
    printf ("\nStack Limit = %ld and %ld max\n", limit.rlim_cur, limit.rlim_max);

    printf("size: %d\n", COUNT);
    char from[COUNT] = {'a'};
    char to[COUNT] = {'c'};
    int rc = 0;

    // setup the from to have some stuff
    memset(from, 'x', COUNT);
    // set it to a failure mode
    memset(to, 'y', COUNT);
    check(valid_copy(to, COUNT, 'y'), "Not initialized right.");

    // use normal copy to
    macro_timer_start(normal_copy)
    rc = normal_copy(from, to, COUNT);
    macro_timer_end(normal_copy)
    check(rc == COUNT, "Normal copy failed: %d", rc);
    check(valid_copy(to, COUNT, 'x'), "Normal copy failed.");

    // reset
    memset(to, 'y', COUNT);

    // duffs version
    macro_timer_start(duffs_device)
    rc = duffs_device(from, to, COUNT);
    macro_timer_end(duffs_device)
    check(rc == COUNT, "Duff's device failed: %d", rc);
    check(valid_copy(to, COUNT, 'x'), "Duff's device failed copy.");

    // reset
    memset(to, 'y', COUNT);

    // my version
    macro_timer_start(zeds_device)
    rc = zeds_device(from, to, COUNT);
    macro_timer_end(zeds_device)
    check(rc == COUNT, "Zed's device failed: %d", rc);
    check(valid_copy(to, COUNT, 'x'), "Zed's device failed copy.");



// reset
    memset(to, 'y', COUNT);

    // my version
    macro_timer_start(define_duffs_device)
    rc = define_duffs_device(from, to, COUNT);
    macro_timer_end(define_duffs_device)
    check(rc == COUNT, "define_duffs_device failed: %d", rc);
    check(valid_copy(to, COUNT, 'x'), "define_duffs_device failed copy.");

    printf("memcpy,memmove,memset time test\n");
    memset(to, 'y', COUNT);

    macro_timer_start(memcpy)
    memcpy(to, from, COUNT);
    macro_timer_end(memcpy)

    memset(to, 'y', COUNT);
    macro_timer_start(memmove)
    memmove(to, from, COUNT);
    macro_timer_end(memmove)

    memset(to, 'y', COUNT);
    macro_timer_start(memset)
    memset(to, 'x', COUNT);
    macro_timer_end(memset)




    return 0;
error:
    return 1;
}