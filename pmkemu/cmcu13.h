//
//  cmcu13.h
//  m145ik13
//
//  Created by Felix Lazarev on 12/30/11.
//  Copyright 2011 Felix Lazarev. All rights reserved.
//

#ifndef cmcu13_h
#define cmcu13_h

#include <QObject>
#include <QString>

#define MCU_BITLEN  168

typedef union{
    struct{
        unsigned int a_r:1;
        unsigned int a_m:1;
        unsigned int a_st:1;
        unsigned int a_nr:1;
        unsigned int a_10nl:1;
        unsigned int a_s:1;
        unsigned int a_4:1;

        unsigned int b_s:1;
        unsigned int b_ns:1;
        unsigned int b_s1:1;
        unsigned int b_6:1;
        unsigned int b_1:1;

        unsigned int g_l:1;
        unsigned int g_nl:1;
        unsigned int g_nt:1;

        unsigned int r0:3;
        unsigned int r_1:1;
        unsigned int r_2:1;
        unsigned int m:1;
        unsigned int l:1;

        unsigned int s:2;
        unsigned int s1:2;

        unsigned int st:2;

        unsigned int pad:4;
    } bits;

    unsigned int raw;
} ucmd_u;


class cMCU
{
public:
    cMCU(const QString &name, bool debug = false);
    ~cMCU();

    void init();
    void pretick(bool rin);
    bool tick(bool rin, bool k1, bool k2, unsigned int * dcycle, bool * syncout, unsigned char * segment);    //execute 1 tick of cpu,
                    // parameters:  rin - input register;
                    //              k1 -- input pin K1 or H!!!
                    //              k2 -- input pin K2
                    //              *dcycle  -- current D cycle, output
                    //              *syncout -- synchronization output for slaves
                    //              *segment -- bit to display
                    //              *point   -- decimal point
                    //return value = output register
    bool strobe();
    ucmd_u  ucrom[68];              //ucommand rom
    unsigned char asprom[128][9];   //synchro sequence rom
    unsigned int cmdrom[256];       //macrocommand rom   -- format (asp0)|(asp1<<8)|(asp2<<16)|(modflag<<24)
    bool debugme;

public:
    bool rm[MCU_BITLEN];
    bool rr[MCU_BITLEN];
    bool rst[MCU_BITLEN];
    bool rs[4];
    bool rs1[4];
    bool rh[4];
    bool dispout[4];
    bool rl;
    bool rt;
    bool latchk1;
    bool latchk2;
    unsigned int sigma; //so we can calculate normally
    bool carry;
    ucmd_u  u_command;
    unsigned int command;
    QString myname;
    QString disassm;
    unsigned char asp;
    unsigned char cur_ucmd;
    bool was_t_qrd;

    void disassemble();

public:
    unsigned int icount;
    unsigned int dcount;
    unsigned int ecount;
    unsigned int ucount;
    unsigned char cptr;
};


#endif
