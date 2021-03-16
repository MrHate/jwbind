sana
=================

Record unified class description into the data segments of WebAssembly modules under the inspiration of Java class file layout.

```
 Description bytes:
 ---------------------------------------------
 | MAGIC_WORD(4)      | ATTRIBUTE_COUNT(4)   |
 ---------------------------------------------
 | METHOD_COUNT(4)    | CLASS_NAME_BYTES(4)  |
 ---------------------------------------------
 | CLASS_NAME ...                            |
 ---------------------------------------------
 | ATTRIBUTE_ENTRIES ...                     |
 ---------------------------------------------
 | METHOD_ENTRIES ...                        |
 ---------------------------------------------
 (x) = x bytes

 ATTRIBUTE_ENTRY {
   int32_t length
   byte[] name ; consists of attribute name and type (eg. In = "int32_t n")
 }
 
 METHOD_ENTRY {
   int32_t length
   byte[] name ; consists of method name and signature (eg. add2(II)I means "int32_t add2(int32_t, int32_t)")
 }

```
