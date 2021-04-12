#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <binaryen-c.h>
#include <wasm.h>

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

void unfoldFunctions() {
  for (const auto section :
       reinterpret_cast<wasm::Module *>(module)->userSections)
    if (section.name == "SaNA") {
      fprintf(stdout, "SaNA");
      fwrite(std::string(section.data.begin(), section.data.end()).c_str(),
             section.data.size(), 1, stdout);
      fflush(stdout);
      return;
    }
  assert(0);
}

void displayDebugMessages() { BinaryenModulePrint(module); }

void cleanup() { BinaryenModuleDispose(module); }
} // namespace

int main(int argc, char **argv) {
  assert(argc >= 2);

  readModuleFromBinaryFile(argv[1]);
  // displayDebugMessages();
  unfoldFunctions();
  // displayDebugMessages();
  cleanup();

  return 0;
}
