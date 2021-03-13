#include <bitset>
#include <iostream>

#include "DescWriter.h"

namespace {
union {
  int16_t i16;
  char ch[2];
} converter;

void write_i16(std::ostream &out, int16_t i16) {
  converter.i16 = i16;
  out.write(converter.ch, 2);
}
} // namespace

namespace jwbind {

DescWriter::DescWriter(const ClassDesc &cd) : desc(cd) {}

void DescWriter::write(std::ostream &out) const {
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

  out << "SaNA";
  write_i16(out, desc.className);
  write_i16(out, desc.attributes.size());
  write_i16(out, desc.methods.size());
  for (const auto attr : desc.attributes) {
    write_i16(out, attr.name);
    write_i16(out, attr.global);
    write_i16(out, attr.flags);
  }
  for (const auto method : desc.methods) {
    write_i16(out, method.name);
    write_i16(out, method.func);
    write_i16(out, method.flags);
  }
}

} // namespace jwbind
