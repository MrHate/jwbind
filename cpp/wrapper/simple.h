#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

#include <wasm_c_api.h>
#include <wasm_export.h>

class SimpleWrapper {

  char error_buf[128];
  wasm_module_inst_t module_inst;
  wasm_function_inst_t func;
  wasm_exec_env_t exec_env;
  uint32_t stack_size, heap_size;

  // Privide a func cache to reduce frequent function looking up on same functions.
  std::unordered_map<const void*, wasm_function_inst_t> func_cache;


  // Reference count for WAMR init/deinit.
  static uint32_t wrapper_count;
  // Increase reference count for WAMR to init.
  static void Init();
  // Decrease reference count for WAMR to deinit.
  static void Deinit();

  // Instantiate a Wasm module with given name under the participation of module
  // cache.
  static wasm_module_inst_t InstantiateWasmModule(const std::string &name,
                                                  uint32_t stack_size,
                                                  uint32_t heap_size,
                                                  char *error_buf);

public:
  using ArgVec = std::vector<wasm_val_t>;

protected:
  explicit SimpleWrapper(const std::string &);
  ~SimpleWrapper();

  // Derived classes call func by.
  void InvokeMethod(const char *func, ArgVec &args, uint32_t result_count,
                    uint32_t arg_count);
  // Wrap args for WAMR func-calling interface.
  template <typename T> static void WrapArg(T arg, ArgVec &, uint32_t);
};
