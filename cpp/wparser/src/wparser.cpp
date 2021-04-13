#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <binaryen-c.h>
#include <wasm.h>
#include <wasm-binary.h>

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

// void outputBinary(const std::string &filename) {
//   auto mod = reinterpret_cast<wasm::Module *>(module);
//   std::ofstream fout(filename);
//   assert(fout.good());
//   wasm::BufferWithRandomAccess buffer;
//   wasm::WasmBinaryWriter writer(mod, buffer);
//   writer.write();
//   char buff[buffer.size()];
//   std::copy_n(buffer.begin(), buffer.size(), buff);
//   fout.write(buff, buffer.size());
//   fout.close();
// }

// As WAMR cannot correctly work with externref presently,
// replace all externref type into i32 here.
// void replaceExternref(const std::string &filename) {
  // auto mod = reinterpret_cast<wasm::Module *>(module);
  // mod->userSections.resize(0);
  // for(auto &table : mod->tables)
  //   table->type = wasm::Type::funcref;
  // for(auto &func : mod->functions) {
  //   std::initializer_list<wasm::Type> types;
  //   for(auto i = func->sig.params.begin(); i != func->sig.params.end(); ++i)
  //     if(*i == wasm::Type::externref)
  //       *const_cast<wasm::Type*>(&(*i)) = wasm::Type::i32;
  // }
  // outputBinary(filename);
// }

void displayDebugMessages() { BinaryenModulePrint(module); }

void cleanup() { BinaryenModuleDispose(module); }
} // namespace

int main(int argc, char **argv) {
  assert(argc >= 2);

  readModuleFromBinaryFile(argv[1]);
  // displayDebugMessages();
  unfoldFunctions();
  // replaceExternref(std::string(argv[1]) + std::string(".bak"));
  // displayDebugMessages();
  cleanup();

  return 0;
}
