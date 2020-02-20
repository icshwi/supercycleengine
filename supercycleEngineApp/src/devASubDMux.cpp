#include <stdio.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <algorithm> // std::min

#include <stdio.h>
#include <string.h>

//static void copyArrs(epicsUInt32 *inarr, epicsUInt32 *outarr, epicsUInt32 n)
//{
//    for (int i = 0; i < n; ++i)
//        outarr[i] = inarr[i];
//}

//static long initDMux(aSubRecord *pRecord)
//{
//    return 0;
//}

// 1 to 4 DMUX
static long ioASubDMux(aSubRecord *prec)
{
    //epicsUInt32 *b = (epicsUInt32 *)prec->b;

    switch (prec->val)
    {
    case 0:
        memcpy(prec->vala, prec->a, std::min(prec->nea, prec->nova) * sizeof(epicsUInt32));
        break;
    case 1:
        memcpy(prec->valb, prec->a, std::min(prec->nea, prec->novb) * sizeof(epicsUInt32));
        break;
    case 2:
        memcpy(prec->valc, prec->a, std::min(prec->nea, prec->novc) * sizeof(epicsUInt32));
        break;
    case 3:
        memcpy(prec->vald, prec->a, std::min(prec->nea, prec->novd) * sizeof(epicsUInt32));
        break;
    default:
        break;
    }

    return prec->val;
}

// Register the function

//epicsRegisterFunction(initDMux);
epicsRegisterFunction(ioASubDMux);