#include <bitset>
#include <iostream>

#include "DescWriter.h"

namespace {
union {
  int32_t i32;
  char ch[4];
} converter;

void write_i32(std::ostream &out, int32_t i32) {
  converter.i32 = i32;
  out.write(converter.ch, 4);
}
} // namespace

namespace jwbind {

DescWriter::DescWriter(const ClassDesc &cd) : desc(cd) {}

void DescWriter::write(std::ostream &out) const {
  out << "SaNA";
  // write_i32(out, desc.className);
  // write_i32(out, desc.attributes.size());
  // write_i32(out, desc.methods.size());
  // for (const auto attr : desc.attributes) {
  //   write_i32(out, attr.name);
  //   write_i32(out, attr.global);
  //   write_i32(out, attr.flags);
  // }
  // for (const auto method : desc.methods) {
  //   write_i32(out, method.name);
  //   write_i32(out, method.func);
  //   write_i32(out, method.flags);
  // }
  const std::string className("testclass");
  write_i32(out, className.size());

  write_i32(out, 1);
  write_i32(out, 1);

  out << className;

  const std::string attr("In");
  write_i32(out, attr.size());
  out << attr;

  const std::string method("add2(I)II");
  write_i32(out, method.size());
  out << method;
}

} // namespace jwbind
