#pragma once

#include <iosfwd>

#include "common.h"

namespace jwbind {

class DescWriter {
  const ClassDesc desc;

public:
  DescWriter(const ClassDesc &);

  void write(std::ostream &) const;
};

} // namespace jwbind
