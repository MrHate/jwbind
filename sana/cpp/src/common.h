#pragma once

#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

/*
 * Description bytes:
 * ---------------------------------------------
 * |   MAGIC_WORD(4)    | CLASS_NAME_INDEX(4)  |
 * ---------------------------------------------
 * | ATTRIBUTE_COUNT(4) |    METHOD_COUNT(4)   |
 * ---------------------------------------------
 * | ATTRIBUTE_ENTRIES ...                     |
 * ---------------------------------------------
 * | METHOD_ENTRIES ...                        |
 * ---------------------------------------------
 * (x) = x bytes
 *
 */

namespace jwbind {

using Index = int16_t;
using Flag = int16_t;

enum {
  PUBLIC = 1 << 0,
  PRIVATE = 1 << 1,
  PROTECTED = 1 << 2,
};

struct AttrEntry {
  Index name;
  Index global;
  Flag flags;
};

struct MethodEntry {
  Index name;
  Index func;
  Flag flags;
};

struct SuperClassEntry {
  Index name;
  Flag flags;
};

struct ClassDesc {
  Index className;
  std::vector<AttrEntry> attributes;
  std::vector<MethodEntry> methods;
  std::vector<std::string> stringRefs;
};

} // namespace jwbind
