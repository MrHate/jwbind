#!/usr/bin/python3

def parse(rec):
    # Description bytes:
    # ---------------------------------------------
    # | MAGIC_WORD(4)      | CLASS_NAME_BYTES(4)  |
    # ---------------------------------------------
    # | ATTRIBUTE_COUNT(4) | METHOD_COUNT(4)      |
    # ---------------------------------------------
    # | CLASS_NAME ...                            |
    # ---------------------------------------------
    # | ATTRIBUTE_ENTRIES ...                     |
    # ---------------------------------------------
    # | METHOD_ENTRIES ...                        |
    # ---------------------------------------------
    # (x) = x bytes
    #
    # ATTRIBUTE_ENTRY {
    #   int32_t length
    #   byte[] name ; consists of attribute name and type (eg. In = "int32_t n")
    # }
    # 
    # METHOD_ENTRY {
    #   int32_t length
    #   byte[] name ; consists of method name and signature (eg. add2(I)II means "int32_t add2(int32_t, int32_t)")
    # }

    def readInt32(arr):
        return int.from_bytes(arr[:4], byteorder='little')
    
    assert rec[:4] == "SaNA", 'Missing magic word.'
    arr = bytearray(rec, 'utf-8')

    class_bytes = readInt32(arr[4:8])
    arr_count = readInt32(arr[8:12])
    method_count = readInt32(arr[12:16])

    pos = 16

    class_name = rec[pos:pos+class_bytes]
    pos += class_bytes

    attributes = []
    methods = []
    for i in range(arr_count):
        nbytes = readInt32(arr[pos:pos+4])
        pos += 4
        name = rec[pos:pos+nbytes]
        pos += nbytes

        attr_type = name[0]
        attr_name = name[1:]
        attributes.append((attr_name,attr_type))

    for i in range(method_count):
        nbytes = readInt32(arr[pos:pos+4])
        pos += 4
        name = rec[pos:pos+nbytes]
        pos += nbytes

        lpos = name.find('(')
        rpos = name.find(')')

        method_name = name[:lpos]
        method_retype = name[lpos+1:rpos]
        method_params = name[rpos+1:]
        methods.append((method_name, method_retype, method_params))

    return (class_name,attributes,methods)


if __name__ == "__main__":

    import sys

    if len(sys.argv) < 2:
        print("Argument expected:\n\tpython3 parser.py <path>")
        sys.exit(1)

    with open(sys.argv[1], errors="ignore") as desc:
        print(parse(desc.read()))
