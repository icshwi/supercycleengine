#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "engine.hpp"
#include "ioblock.hpp"
#include "cmnbase.hpp"

extern io::IOBlock io_block;

//static long initEngine(aSubRecord *pRecord)
//{
//    //aSubRecord *prec = (aSubRecord *)pRecord;
//    //prec->valu = &enabled;
//    return 0;
//}

static long ioEngine(aSubRecord *prec)
{
    epicsUInt64 IdCycle = engineCycle(io_block);
    // Update the meta
    epicsUInt64 *pvalaU64 = (epicsUInt64 *)prec->vala;
    epicsUInt32 *pvalaU32 = (epicsUInt32 *)prec->vala;

    pvalaU64[0] = IdCycle; // 0,1
    pvalaU32[2] = (epicsUInt32)io_block.sc_prd_us;
    pvalaU32[3] = (epicsUInt32)env::DATAS;

    // Update the Dbuf
    // neva , novb (max)
    prec->nevb = cmn::vec2p<epicsUInt32>(prec->valb, io_block.dbuf.vallist());
    prec->nevc = cmn::vec2p<epicsUInt32>(prec->valc, io_block.SEQ.getSeqTst());
    prec->nevd = cmn::vec2p<epicsUInt32>(prec->vald, io_block.SEQ.getSeqEvt());

    return 0;
}

// Register the function

//epicsRegisterFunction(initEngine);
epicsRegisterFunction(ioEngine);
