#include "cmem.h"

cMem::cMem()
{
    clear();
}

void cMem::clear()
{
    for(int i = 0; i < MEM_BITLEN; ++i)
        memarray[i] = false;
}

bool cMem::pretick() const
{
    return memarray[0];
}

bool cMem::tick(bool rm)
{
    bool ret = memarray[0];

    for(int i = 0; i < (MEM_BITLEN - 1) ; ++i)
        memarray[i] = memarray[i + 1];
    memarray[MEM_BITLEN - 1] = rm;

    return ret;
}
