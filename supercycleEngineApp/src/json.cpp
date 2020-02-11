
#include "json.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"

#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "cmnbase.hpp"

namespace io
{

JsonValue::JsonValue(std::string fname)
{
    io::LOG(io::DEBUG2) << "JsonValue::JsonValue() fname " << fname;

    init(fname);
}

void
JsonValue::init(std::string fname)
{
    io::LOG(io::DEBUG2) << "JsonValue::init() fname" << fname;

    filename = fname;

    std::ifstream ifs;
    Json::Reader reader;

    ifs.open(filename, std::ifstream::in);
    reader.parse(ifs, value);
    ifs.close();

    keys = value.getMemberNames();
}

JsonDBUF::JsonDBUF(std::string fname)
:   JsonValue(fname),
    PBDest(value[env::DBFIDX2Str.at(env::PBDest)]),
    PBMod(value[env::DBFIDX2Str.at(env::PBMod)]),
    PBState(value[env::DBFIDX2Str.at(env::PBState)])
{
    io::LOG(io::DEBUG2) << "JsonDBUF::JsonDBUF() fname " << fname;
    //init(fname);
    ProtVer = value[env::DBFIDX2Str.at(env::ProtVer)].asUInt();
    ProtNum = value[env::DBFIDX2Str.at(env::ProtNum)].asUInt();

    cmn::json2map(PBDest,PBDestId);
    cmn::json2map(PBMod,PBModId);
    cmn::json2map(PBState,PBStateId);

    io::LOG(io::INFO) << "JsonDBUF::JsonDBUF() cmn::map2str<std::string,uint>(PBDestId) " << cmn::map2str<std::string,uint>(PBDestId);
    io::LOG(io::INFO) << "JsonDBUF::JsonDBUF() cmn::map2str<std::string,uint>(PBModId) " << cmn::map2str<std::string,uint>(PBModId);
    io::LOG(io::INFO) << "JsonDBUF::JsonDBUF() cmn::map2str<std::string,uint>(PBStateId) " << cmn::map2str<std::string,uint>(PBStateId);
}

JsonEVT::JsonEVT(std::string fname)
:   JsonValue(fname)
{
    io::LOG(io::DEBUG2) << "JsonEVT::JsonEVT() fname " << fname;
    //init(fname);
    std::string line="";
    cmn::json2map(value,evtm);

    io::LOG(io::INFO) << "JsonDBUF::JsonDBUF() cmn::map2str<std::string,uint>(evtm) " << cmn::map2str<std::string,uint>(evtm);
}

/*
void
JsonDBUF::init(std::string fname)
{
    io::LOG(io::DEBUG2) << "JsonDBUF::init() fname" << fname;
    JsonValue::init(fname);
    ProtVer = value[env::DBFIDX2Str.at(env::ProtVer)].asUInt();
    ProtNum = value[env::DBFIDX2Str.at(env::ProtNum)].asUInt();
    //PBDest = value[env::DBFIDX2Str.at(env::PBDest)];
    //PBMod = value[env::DBFIDX2Str.at(env::PBMod)];
}
*/

} //namespace
