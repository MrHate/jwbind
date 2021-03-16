#include <cassert>
#include <fstream>

#include "simple.h"

uint32_t SimpleWrapper::wrapper_count = 0;

void SimpleWrapper::Init(){
  if(wrapper_count++ == 0)
    wasm_runtime_init();
}

void SimpleWrapper::Deinit(){
  if(--wrapper_count == 0)
    wasm_runtime_destroy();
}

SimpleWrapper::SimpleWrapper(const std::string& name): mod_name(name), stack_size(8092), heap_size(8092) {
  Init();

  std::ifstream fin(name);
  assert(fin.good());

  std::string buffer; char ch;
  while(fin.get(ch)) buffer.push_back(ch);
  module = wasm_runtime_load(reinterpret_cast<const uint8_t*>(buffer.c_str()), buffer.size(), error_buf, sizeof(error_buf));
  assert(module);
  module_inst = wasm_runtime_instantiate(module, stack_size, heap_size, error_buf, sizeof(error_buf));
  exec_env = wasm_runtime_create_exec_env(module_inst, stack_size);
}

SimpleWrapper::~SimpleWrapper() {
  wasm_runtime_destroy_exec_env(exec_env);
  wasm_runtime_deinstantiate(module_inst);
  wasm_runtime_unload(module);

  Deinit();
}


void SimpleWrapper::InvokeMethod(const char* func, SimpleWrapper::ArgVec& args, uint32_t result_count) {
  auto func_inst = wasm_runtime_lookup_function(module_inst, func, NULL);
  wasm_val_t results[result_count];
  if(!wasm_runtime_call_wasm_a(exec_env, func_inst, result_count, results, args.size(), &args[0]))
    assert(0);
  args.resize(result_count);
  for(uint32_t i=0;i<result_count;++i)
    args[i] = results[i];
}

template <typename T>
wasm_val_t SimpleWrapper::WrapArg(T arg) {
  return wasm_val_t();
}

template <>
wasm_val_t SimpleWrapper::WrapArg(int32_t arg) {
  wasm_val_t res;
  res.kind = WASM_I32;
  res.of.i32 = arg;
  return res;
}