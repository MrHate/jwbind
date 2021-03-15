#include <cassert>
#include <iostream>

#include "DescParser.h"

namespace {
union {
  int32_t i32;
  char ch[4];
} converter;

int32_t read_i32(std::istream &input) {
  input.read(converter.ch, 4);
  return converter.i32;
}
} // namespace

namespace jwbind {

DescParser::DescParser(std::istream &input) {
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
  char ch;
  input >> ch;
  assert(ch == 'S');
  input >> ch;
  assert(ch == 'a');
  input >> ch;
  assert(ch == 'N');
  input >> ch;
  assert(ch == 'A');

  desc.className = read_i32(input);

  int32_t attr_count = read_i32(input), method_count = read_i32(input);

  for (int32_t i = 0; i < attr_count; ++i)
    desc.attributes.push_back(
        AttrEntry{read_i32(input), read_i32(input), read_i32(input)});
  for (int32_t i = 0; i < method_count; ++i)
    desc.methods.push_back(
        MethodEntry{read_i32(input), read_i32(input), read_i32(input)});
}

const ClassDesc &DescParser::GetDescription() const { return desc; }

void DescParser::PrintDesciption(std::ostream &out) const {
  out << std::string(10, '-') << std::endl
      << "class name: " << desc.className << std::endl
      << "attribute count: " << desc.attributes.size() << std::endl
      << "method count: " << desc.methods.size() << std::endl
      << std::string(10, '-') << std::endl;
}
} // namespace jwbind
