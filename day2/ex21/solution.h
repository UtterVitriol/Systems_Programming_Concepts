#ifndef SOLUTION_H
#define SOLUTION_H
#include <stdint.h>
#include <stdbool.h>

#include "mmu.h"

typedef struct vAddr
{
        uint64_t offest : 12;
        uint64_t pt : 9;
        uint64_t pdt : 9;
        uint64_t pdpt : 9;
        uint64_t pml4 : 9;
        uint64_t pad : 16;
}vAddr;

union VirtualAddr
{
    struct vAddr sAddr;
    uint64_t iAddr;
};

uint64_t *get_data(mmu_t *p_mmu, uint64_t v_addr, bool is_supervisor);
bool check_perm(uint8_t p, uint8_t s, uint8_t myS, uint8_t e);

#endif