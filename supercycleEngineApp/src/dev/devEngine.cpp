/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "engine.hpp"
#include "ioblock.hpp"
#include "cmnbase.hpp"
#include "iocVars.hpp"
#include "ioblock.hpp"
#include "devStringoutCtrl.hpp"

static long initEngine()
{
  iocVars2IO();
  return 0;
}

static long ioEngine(aSubRecord *prec)
{
  // Configure new cycle
  io::RegisteredIOBlock().dbSync(RegisteredStrOutMap);
  // Change the table if requested
  sctableSwitch(io::RegisteredIOBlock());
  // Engine cycle
  engineCycle(io::RegisteredIOBlock());
  // Update the meta
  epicsUInt64 *pvalaU64 = (epicsUInt64 *)prec->vala;
  epicsUInt32 *pvalaU32 = (epicsUInt32 *)prec->vala;
  pvalaU64[0] = (epicsUInt64)io::RegisteredIOBlock().cId; // 0,1
  pvalaU32[2] = (epicsUInt32)io::RegisteredIOBlock().cPeriod;
  // Update the Dbuf - neva , novb (max)
  prec->nevb = cmn::vec2p<epicsUInt32>(prec->valb, io::RegisteredIOBlock().dbuf.vallist());
  prec->nevc = cmn::vec2p<epicsUInt32>(prec->valc, io::RegisteredIOBlock().Seq.getSeqTst());
  prec->nevd = cmn::vec2p<epicsUInt32>(prec->vald, io::RegisteredIOBlock().Seq.getSeqEvt());
  prec->neve = cmn::vec2p<epicsUInt32>(prec->vale, io::RegisteredIOBlock().Seq.getSeqVec());

  return 0;
}

// Register the function
extern "C"
{
  epicsRegisterFunction(initEngine);
  epicsRegisterFunction(ioEngine);
}
