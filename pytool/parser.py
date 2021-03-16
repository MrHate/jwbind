#!/usr/bin/python3

def parse(rec):

    def readInt32(arr):
        return int.from_bytes(arr[:1], byteorder='little')
    
    assert rec[:4] == "SaNA", 'Missing magic word.'
    arr = bytearray(rec, 'utf-8')

    arr_count  = readInt32(arr[4:])
    method_count = readInt32(arr[5:])
    class_bytes = readInt32(arr[6:])

    pos = 7

    class_name = rec[pos:pos+class_bytes]
    pos += class_bytes

    print(class_bytes, class_name, arr_count, method_count)

    attributes = []
    methods = []
    for i in range(arr_count):
        nbytes = readInt32(arr[pos:])
        pos += 1
        name = rec[pos:pos+nbytes]
        pos += nbytes

        attr_type = name[0]
        attr_name = name[1:]
        attributes.append((attr_name,attr_type))

    for i in range(method_count):
        nbytes = readInt32(arr[pos:])
        pos += 1
        name = rec[pos:pos+nbytes]
        pos += nbytes

        lpos = name.find('(')
        rpos = name.find(')')

        method_name = name[:lpos]
        method_params = name[lpos+1:rpos]
        method_retype = name[rpos+1:]
        methods.append((method_name, method_retype, method_params))

    return (class_name,attributes,methods)

