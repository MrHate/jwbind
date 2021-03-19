# jwbind

## Usage:
```
make  # update and deploy the toolchain

./jwbind <file>
```

## Requirements:
1. Gradle
2. JDK 8 or above
3. CMake and GCC/Clang
4. python3

## Overview
Record class description into one custom section of the output wasm module which will be parsed to generate class later.
```
 Description bytes:
 ---------------------------------------------
 | MAGIC_WORD(4)      | ATTRIBUTE_COUNT(1)   |
 ---------------------------------------------
 | METHOD_COUNT(1)    | CLASS_NAME_BYTES(1)  |
 ---------------------------------------------
 | CLASS_NAME ...                            |
 ---------------------------------------------
 | ATTRIBUTE_ENTRIES ...                     |
 ---------------------------------------------
 | METHOD_ENTRIES ...                        |
 ---------------------------------------------
 (x) = x bytes

 ATTRIBUTE_ENTRY: STRING_LENGTH(1) + DESC_STRING(STRING_LENGTH)
 METHOD_ENTRY: STRING_LENGTH(1) + DESC_STRING(STRING_LENGTH)

```
