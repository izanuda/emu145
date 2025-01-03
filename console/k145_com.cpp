#include "cascade.h"
#include "k145_com.h"

const char *unknown_chip  = "unknown chip";

K145::K145()
: CASCADE(), BUSi(nullptr), BUSo(nullptr), M(nullptr)
{
}

K145::~K145()
{
    delete M;
}


void K145::clk(int phase)
{
}

const char* K145::about(void) const
{
    return unknown_chip;
}

K145* K145::Target(void)
{
    return BUSo;
}

void K145::out_to(K145 *ms)
{
    BUSo = ms;
    ms->BUSi = this;
    ms->M->cascade(this);
}

char K145::get(void) const
{
    return M->get();
}
