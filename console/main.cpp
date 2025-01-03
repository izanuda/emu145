#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "chargemem.h"
#include "k145_com.h"

using namespace std;

const int K145IK13_M_SIZE = 36*4;
const int K145IR2_M_SIZE  = 1024;
const char *K145IK13_chip = "K145IK13";
const char *K145IR2_chip  = "K145IR2";

class IK13 : public K145
{
public:
    IK13();

    void clk(int phase) override;
    const char* about(void) const override;
};

IK13::IK13()
    : K145()
{
    M = new CHARGE_MEM(K145IK13_M_SIZE);
    M->set(0,'1');
}

void IK13::clk(int phase)
{
    M->clk(phase);
}

const char* IK13::about(void) const
{
    return K145IK13_chip;
}

class IR2 : public K145
{
private:

public:
    IR2();

    void clk(int phase) override;
    const char* about(void) const override;
};

IR2::IR2()
:K145()
{
    M = new CHARGE_MEM(K145IR2_M_SIZE);
}

void IR2::clk(int phase)
{
    M->clk(phase);
}

const char* IR2::about(void) const
{
    return K145IR2_chip;
}

class CGen
{
private:
    int CNT;
    int CYC;                       // Длина цикла в фазах подсчитывается после подключения к генратору комплекта
    K145 *TRG;

public:
    CGen();
    void clk(int qPh);
    void CYCLE(void);              // Генерировать клок на протяжении цикла магистрали комплекта
    void link(K145 *ms);
    void info(void) const;   // print information
    void schem(void) const;  // print schematic diagram
};


CGen::CGen()
: CNT(0), CYC(0), TRG(nullptr)
{}

void CGen::clk(int qPh)
{
    K145 *pChip;

    do{
        pChip = TRG; // начнем раздачу с ведущего чипа магистрали
        // Раздаем клок чипам до тех пор пока чип которому предназначен клок существует
        while(pChip != NULL)
        {
            pChip->clk(CNT);
            pChip = pChip->Target();
            if(pChip == TRG) break; // клок вернулся в ведущий чип магистрали, оборвем раздачу иначе будет кольцо!
        }
        CNT++;
        CNT &= 3;
    } while(--qPh > 0);
}

void CGen::CYCLE(void)
{
    clk(CYC);
}

void CGen::info(void) const
{
    char phase[5] = "1234";

    if(CNT != 0) phase[0] = ' ';
    if(CNT != 2) phase[2] = ' ';
    if(CNT < 2) phase[3] = ' ';	else  phase[1] = ' ';
    puts(phase);
}

void CGen::link(K145 *ms)
{
    K145 *pChip = ms;

    TRG = ms; CYC = 0;

    while(pChip != NULL)
    {
        CYC += pChip->M->Size();
        pChip = pChip->Target();
        if(pChip == TRG) break; // клок вернулся в ведущий чип магистрали, оборвем раздачу иначе будет кольцо!
    }

    CYC *= 4;
}

void CGen::schem(void) const
{
    int count = 1;
    K145 *pChip = TRG;
    while(pChip != NULL)
    {
        printf("%d: %s \n", count++, pChip->about());
        pChip = pChip->Target();
        if(pChip == TRG) break; // опрос ведущего чипа магистрали, оборвем опрос иначе будет кольцо!
    }
}


int main(void)
{
    K145 *pChip = nullptr;
    char cmd, ibuff[100];
    int	 par;

    CGen Gen;
    IR2 IR20, IR21;
    IK13 IK1302;

// Составляем комплект
    IR21.out_to(&IR20);      // к выходу магистрали K145IR2 DD1 подключаем вход магистрали K145IR2 DD0
    IK1302.out_to(&IR21);    // к выходу магистрали K145IK1302 подключаем вход магистрали K145IR2 DD1
    IR20.out_to(&IK1302);    // к выходу магистрали K145IR2 DD0 подключаем вход магистрали K145IK1302 (закольцовка)
// Раздача клока начнеться с K145IK1302
    Gen.link(&IK1302);     // к виртуальному выходу генератора подключаем ведущий K145IK13

    puts("emu145 start.\n>");
    do
    {
        fgets(ibuff, 100, stdin);
        par = 1;
        sscanf(ibuff, "%c%i", &cmd, &par);
        switch (cmd)
        {
            case 'f': Gen.info(); break;

            case 'T':
            case 't': Gen.clk(par); break;
            case 'C':
            case 'c': Gen.CYCLE(); break;
            case 'S':
            case 's': Gen.schem(); break;
            case 'm':
            case 'M':
                pChip = &IK1302;
                for(int i=1;i<par;i++)
                {
                  if(pChip == NULL) break;
                  pChip = pChip->Target();
                }
                printf("%s\n", pChip->about());
                pChip->M->show();
             break;
        };
    } while(cmd != 'q');
    return 0;
}

