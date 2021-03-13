#pragma once

#include <iosfwd>

#include "common.h"

namespace jwbind {

class DescParser {
  ClassDesc desc;

public:
  DescParser(std::istream &);

  const ClassDesc &GetDescription() const;
  void PrintDesciption(std::ostream &) const;
};

} // namespace jwbind
