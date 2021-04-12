#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>

#include <binaryen-c.h>

namespace {
BinaryenModuleRef module;

void readModuleFromBinaryFile(const char *filename) {
  std::ifstream fin(filename);
  assert(fin.good());

  std::stringstream strm;
  strm << fin.rdbuf();
  auto bytes = strm.str();
  std::vector<char> vec(bytes.begin(), bytes.end());

  module = BinaryenModuleRead(&vec[0], vec.size());
  fin.close();
}

void unfoldFunctions() {}

void displayDebugMessages() { BinaryenModulePrint(module); }

void cleanup() { BinaryenModuleDispose(module); }
} // namespace

int main(int argc, char **argv) {
  assert(argc >= 2);

  readModuleFromBinaryFile(argv[1]);
  displayDebugMessages();
  unfoldFunctions();
  displayDebugMessages();
  cleanup();

  return 0;
}
