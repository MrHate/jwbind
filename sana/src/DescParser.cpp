#include <cassert>
#include <iostream>

#include "DescParser.h"

namespace {
union {
  int16_t i16;
  char ch[2];
} converter;

int16_t read_i16(std::istream &input) {
  input.read(converter.ch, 2);
  return converter.i16;
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

  desc.className = read_i16(input);

  int16_t attr_count = read_i16(input), method_count = read_i16(input);

  for (int16_t i = 0; i < attr_count; ++i)
    desc.attributes.push_back(
        AttrEntry{read_i16(input), read_i16(input), read_i16(input)});
  for (int16_t i = 0; i < method_count; ++i)
    desc.methods.push_back(
        MethodEntry{read_i16(input), read_i16(input), read_i16(input)});
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
