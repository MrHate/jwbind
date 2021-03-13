sana
=================

Record unified class description into the data segments of WebAssembly modules under the inspiration of Java class file layout.

```
Description bytes:
---------------------------------------------
|   MAGIC_WORD(4)    | CLASS_NAME_INDEX(4)  |
---------------------------------------------
| ATTRIBUTE_COUNT(4) |    METHOD_COUNT(4)   |
---------------------------------------------
| ATTRIBUTE_ENTRIES ...                     |
---------------------------------------------
| METHOD_ENTRIES ...                        |
---------------------------------------------
(x) = x bytes
```

1. The records are stored as the last data segments of each WebAssembly in binary form.
2. Each index of a record refers to a certain entry of a WebAssembly module.
