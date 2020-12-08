/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-03
 */

#pragma once

#include <string>
#include <vector>
#include <map>

namespace io
{

  class CSVStrData
  {
  public:
    CSVStrData(){};

  private:
    friend class CSVStrMap;
    int init(std::string file);
    std::vector<std::string> _rows;
    std::string _header;
    std::string _file;
    size_t _getNumOfLines(std::ifstream &ifs);
  };

  class CSVStrMap
  {
  public:
    CSVStrMap(){};
    int init(std::string file);
    std::map<std::string, std::string> getRowMap();
    std::map<std::string, std::string> checkRowMapNext();
    size_t getRowId() { return _row_id; };
    size_t getCycleId() { return _cycle_id; };
    std::string getFile() { return _csvstr._file; };

  private:
    std::map<std::string, std::string> _readRowMap(const size_t l_rowid);
    CSVStrData _csvstr;
    size_t _row_id = 0, _cycle_id = 0;
    void _iterator();
    std::vector<std::vector<std::string>> _rows;
    std::vector<std::string> _header;
  };

} // namespace io
