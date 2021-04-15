#include <cassert>
// #include <iostream>
#include <fstream>
#include <memory>

#include "simple.h"

// typedef struct wasm_val_t {
//   wasm_valkind_t kind;
//   union {
//     int32_t i32;
//     int64_t i64;
//     float f32;
//     double f64;
//     struct wasm_ref_t* ref;
//   } of;
// } wasm_val_t;

uint32_t SimpleWrapper::wrapper_count = 0;

void SimpleWrapper::Init() {
  if (wrapper_count++ == 0)
    wasm_runtime_init();
}

void SimpleWrapper::Deinit() {
  if (--wrapper_count == 0)
    wasm_runtime_destroy();
}

SimpleWrapper::SimpleWrapper(const std::string &name)
    : stack_size(8092), heap_size(8092) {
  module_inst = InstantiateWasmModule(name, stack_size, heap_size, error_buf);
  exec_env = wasm_runtime_create_exec_env(module_inst, stack_size);
}

SimpleWrapper::~SimpleWrapper() {
  wasm_runtime_destroy_exec_env(exec_env);
  wasm_runtime_deinstantiate(module_inst);
}

using wasm_module_sp = std::shared_ptr<WASMModuleCommon>;

wasm_module_inst_t SimpleWrapper::InstantiateWasmModule(const std::string &name,
                                                        uint32_t stack_size,
                                                        uint32_t heap_size,
                                                        char *error_buf) {
  static std::unordered_map<std::string, wasm_module_sp> module_cache;
  // std::cout << "Init module: " << name << std::endl;

  auto it = module_cache.find(name);
  while (it == module_cache.end()) {
    // std::cout << "Load module: " << name << std::endl;
    Init();

    std::ifstream fin(name);
    assert(fin.good());

    std::string buffer;
    char ch;
    while (fin.get(ch))
      buffer.push_back(ch);
    auto module =
        wasm_runtime_load(reinterpret_cast<const uint8_t *>(buffer.c_str()),
                          buffer.size(), error_buf, sizeof(error_buf));
    assert(module);

    module_cache[name] = wasm_module_sp(module, [](wasm_module_t p) {
      wasm_runtime_unload(p);
      Deinit();
    });

    it = module_cache.find(name);
  }
  auto pm = it->second;
  return wasm_runtime_instantiate(pm.get(), stack_size, heap_size, error_buf,
                                  sizeof(error_buf));
}

void SimpleWrapper::InvokeMethod(const char *func_name,
                                 SimpleWrapper::ArgVec &args,
                                 uint32_t result_count, uint32_t arg_count) {
  // Check function cache first.
  auto it = func_cache.find(func_name);
  while (it == func_cache.end()) {
    func_cache[func_name] = wasm_runtime_lookup_function(module_inst, func_name, NULL);
    it = func_cache.find(func_name);
  }
  auto func_inst = it->second;
  // auto func_inst = wasm_runtime_lookup_function(module_inst, func_name, NULL);

  // Call through WAMR and process results.
  wasm_val_t results[result_count];
  if (!wasm_runtime_call_wasm_a(exec_env, func_inst, result_count, results,
                                arg_count, &args[0]))
    assert(0);
  args.resize(result_count);
  for (uint32_t i = 0; i < result_count; ++i)
    args[i] = results[i];
}

// ======================= Arg wrapping template functions
// ========================

template <typename T>
void SimpleWrapper::WrapArg(T arg, ArgVec &vec, uint32_t i) {}

template <> void SimpleWrapper::WrapArg(int32_t arg, ArgVec &vec, uint32_t i) {
  wasm_val_t &res = vec[i];
  res.kind = WASM_I32;
  res.of.i32 = arg;
}

template <> void SimpleWrapper::WrapArg(int64_t arg, ArgVec &vec, uint32_t i) {
  wasm_val_t &res = vec[i];
  res.kind = WASM_I64;
  res.of.i64 = arg;
}

template <> void SimpleWrapper::WrapArg(float arg, ArgVec &vec, uint32_t i) {
  wasm_val_t &res = vec[i];
  res.kind = WASM_F32;
  res.of.f32 = arg;
}

template <> void SimpleWrapper::WrapArg(double arg, ArgVec &vec, uint32_t i) {
  wasm_val_t &res = vec[i];
  res.kind = WASM_F64;
  res.of.f64 = arg;
}
