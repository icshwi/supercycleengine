/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#pragma once

/**
 * Debug Log - Generic Plugin
 *
 * Changes the loglevels during runtime.
 * Tested with cmn::tst::epics_now()
 * Usage example:
 *   dlog::Config::instance().init(level, timestamp_func);
 *   dlog::Print(dlog::INFO) << " debugvar " << debugvar;
 */

#include <iostream>
#include <functional>

namespace dlog
{
  enum LevelTypes
  {
    DEBUG3,
    DEBUG2,
    DEBUG1,
    DEBUG,
    INFO,
    WARNING,
    ERROR
  };
  class Config
  {
  public:
    Config();
    void init(dlog::LevelTypes *level, std::function<std::string()> timestamp, bool headers = true);
    static Config &instance();

  private:
    friend class Print;
    dlog::LevelTypes _lv = INFO;
    dlog::LevelTypes *_level = &_lv;
    bool _headers = true;
    std::function<std::string()> _tstf;
  };

  class Print
  {
  public:
    Print(dlog::LevelTypes level = dlog::INFO);
    ~Print();

    template <typename T>
    Print &operator<<(const T &msg)
    {
      if (_msglevel >= *_config._level)
        std::cout << msg;

      return *this;
    };

  private:
    dlog::Config &_config = dlog::Config::instance();
    dlog::LevelTypes _msglevel;
  };

} // namespace dlog