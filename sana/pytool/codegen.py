#!/usr/bin/python3

typeMap = {
        'I' : 'int32_t',
        'V' : 'void'
        }

def codegen(desc):
    generateHeader(desc)
    generateBody(desc)

def generateHeader(desc):
    (class_name, attributes, methods) = desc

    def emitHead(f):
        f.write('#include \"simple.h\"\n\n')
        f.write('class {} {{\npublic:\n'.format(class_name))

    def emitTail(f):
        f.write('};\n')

    def emitAttributes(f):
        for ent in attributes:
            (attr_name, attr_type) = ent
            f.write('\t{} {};\n'.format(
                typeMap[attr_type],
                attr_name))

    def emitMethods(f):
        
        def unpackParams(params):
            real_types = []
            for ch in params:
                real_types.append(typeMap[ch])
            return ','.join(real_types)

        for ent in methods:
            (method_name, method_retype, method_params) = ent
            f.write('\t{} {}({});\n'.format(
                typeMap[method_retype],
                method_name,
                unpackParams(method_params)))


    with open(class_name + '.h', 'w') as target:
        emitHead(target)
        emitAttributes(target)
        emitMethods(target)
        emitTail(target)

def generateBody(desc):
    pass

if __name__ == "__main__":

    import sys
    from parser import parse

    if len(sys.argv) < 2:
        print("Argument expected:\n\tpython3 codegen.py <path>")
        sys.exit(1)

    with open(sys.argv[1], errors="ignore") as desc:
        codegen(parse(desc.read()))
