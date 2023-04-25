#ifndef MMU_H
#define MMU_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MMU_PAGE_SIZE (4096)

typedef struct
{
    uint8_t data[MMU_PAGE_SIZE];
} page_t;

typedef struct
{
    uint64_t cr3;
    size_t   page_count;
    page_t  *pages;
} mmu_t;

// mmu_t has cr3 (First uint64)

bool mmu_store(mmu_t   *p_mmu,
               uint64_t v_addr,
               uint8_t *p_data,
               size_t   size,
               bool     is_supervisor);

bool mmu_load(mmu_t   *p_mmu,
              uint64_t v_addr,
              uint8_t *p_data,
              size_t   size,
              bool     is_supervisor);

bool mmu_exec(mmu_t *p_mmu, uint64_t v_addr, bool is_supervisor);

#endif /* MMU_H */