#include <cmath>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

#include "DescParser.h"
#include "DescWriter.h"

using namespace jwbind;

int16_t rand_i16() {
  static int16_t mi16 = std::numeric_limits<short>::max();
  return rand() % mi16;
}

bool operator==(const MethodEntry &lhs, const MethodEntry &rhs) {
  return lhs.name == rhs.name && lhs.func == rhs.func && lhs.flags == rhs.flags;
}

bool operator==(const AttrEntry &lhs, const AttrEntry &rhs) {
  return lhs.name == rhs.name && lhs.global == rhs.global &&
         lhs.flags == rhs.flags;
}

int main() {
  const std::string filepath = "./test.desc";
  std::ofstream fout(filepath, std::ios::out | std::ios::binary);

  srand(time(0));
  const int mc = rand_i16() % 100 + 10, ac = rand_i16() % 100 + 10;
  std::vector<MethodEntry> methods;
  std::vector<AttrEntry> attributes;
  for (int i = 0; i < mc; ++i)
    methods.push_back(MethodEntry{rand_i16(), rand_i16(), rand_i16()});
  for (int i = 0; i < ac; ++i)
    attributes.push_back(AttrEntry{rand_i16(), rand_i16(), rand_i16()});

  const int16_t className = rand_i16();
  ClassDesc desc{className, attributes, methods};
  DescWriter writer(desc);
  writer.write(fout);
  fout.close();

  // std::ifstream fin(filepath, std::ios::in | std::ios::binary);
  // DescParser parser(fin);
  // const auto &rdesc = parser.GetDescription();
  // assert(rdesc.className == className);
  // for (int i = 0; i < mc; ++i)
  //   assert(rdesc.methods.at(i) == methods[i]);
  // for (int i = 0; i < ac; ++i)
  //   assert(rdesc.attributes.at(i) == attributes[i]);
  // parser.PrintDesciption(std::cout);

  return 0;
}
