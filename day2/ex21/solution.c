#include "mmu.h"
#include "solution.h"

#include <stdlib.h>
#include <stdio.h>

// bool mmu_store(mmu_t   *p_mmu,
//                uint64_t v_addr,
//                uint8_t *p_data,
//                size_t   size,
//                bool     is_supervisor)
// {

//     return false;
// }

bool mmu_load(mmu_t   *p_mmu,
              uint64_t v_addr,
              uint8_t *p_data,
              size_t   size,
              bool     is_supervisor)
{
  
    uint64_t *data = get_data(p_mmu, v_addr, is_supervisor);
    return false;
}

bool mmu_exec(mmu_t *p_mmu, uint64_t v_addr, bool is_supervisor)
{
    // present bit (executable or not)
    union VirtualAddr myaddr;

    myaddr.iAddr = v_addr;
    myaddr.sAddr.offest;
    
    uint64_t * pml4 = (uint64_t*)&p_mmu->pages[p_mmu->cr3 >> 12];

    uint64_t pml4e = (uint64_t)pml4[myaddr.sAddr.pml4];


    if(!check_perm((pml4e & 1), (pml4e & 4), is_supervisor, (pml4e >> 63)))
    {
        return false;
    }

    uint64_t pdptIDX = pml4e;
    pdptIDX = pdptIDX << 12;
    pdptIDX = pdptIDX >> 24;

    uint64_t *pdpt = (uint64_t*)&p_mmu->pages[pdptIDX];

    uint64_t pdpte = pdpt[myaddr.sAddr.pdpt];

    if(!check_perm((pdpte & 1), (pdpte & 4), is_supervisor, (pdpte >> 63)))
    {
        return false;
    }


    uint64_t pdIDX = pdpte;
    pdIDX = pdIDX << 12;
    pdIDX = pdIDX >> 24;   

    uint64_t *pd = (uint64_t*)&p_mmu->pages[pdIDX];
    uint64_t pde = pd[myaddr.sAddr.pdt];


    if(!check_perm((pde & 1), (pde & 4), is_supervisor, (pde >> 63)))
    {
        return false;
    }

    uint64_t ptIDX = pde;
    ptIDX = ptIDX << 12;
    ptIDX = ptIDX >> 24;

    uint64_t *pt = (uint64_t*)&p_mmu->pages[ptIDX];
    uint64_t pte = pt[myaddr.sAddr.pt];

    if(!check_perm((pte & 1), (pte & 4), is_supervisor, (pte >> 63)))
    {
        return false;
    }

    
   
    return true;
}

bool check_perm(uint8_t p, uint8_t s, uint8_t myS, uint8_t e)
{
    if(!p)
    {
        return false;
    }

    if(e)
    {
        return false;
    }

    if(!myS && !s)
    {
        return false;
    }

    return true;
}

uint64_t *get_data(mmu_t *p_mmu, uint64_t v_addr, bool is_supervisor)
{
     union VirtualAddr myaddr;

    myaddr.iAddr = v_addr;
    myaddr.sAddr.offest;
    
    uint64_t * pml4 = (uint64_t*)&p_mmu->pages[p_mmu->cr3 >> 12];

    uint64_t pml4e = (uint64_t)pml4[myaddr.sAddr.pml4];


    if(!check_perm((pml4e & 1), (pml4e & 4), is_supervisor, 0))
    {
        return NULL;
    }

    uint64_t pdptIDX = pml4e;
    pdptIDX = pdptIDX << 12;
    pdptIDX = pdptIDX >> 24;

    uint64_t *pdpt = (uint64_t*)&p_mmu->pages[pdptIDX];

    uint64_t pdpte = pdpt[myaddr.sAddr.pdpt];

    if(!check_perm((pdpte & 1), (pdpte & 4), is_supervisor, 0))
    {
        return NULL;
    }


    uint64_t pdIDX = pdpte;
    pdIDX = pdIDX << 12;
    pdIDX = pdIDX >> 24;   

    uint64_t *pd = (uint64_t*)&p_mmu->pages[pdIDX];
    uint64_t pde = pd[myaddr.sAddr.pdt];


    if(!check_perm((pde & 1), (pde & 4), is_supervisor, 0))
    {
        return NULL;
    }

    uint64_t ptIDX = pde;
    ptIDX = ptIDX << 12;
    ptIDX = ptIDX >> 24;

    uint64_t *pt = (uint64_t*)&p_mmu->pages[ptIDX];
    uint64_t pte = pt[myaddr.sAddr.pt];

    if(!check_perm((pte & 1), (pte & 4), is_supervisor, 0))
    {
        return NULL;
    }

    uint64_t pageIDX = pte;
    pageIDX = pageIDX << 12;
    pageIDX = pageIDX >> 24;

    uint64_t *data = (uint64_t*)&p_mmu->pages[pageIDX];
    
    printf("Data Addr: %p\n", data);
    
    return data;
}