#!/usr/bin/python3

type_map = {
        'I' : 'int32_t',
        'V' : 'void'
        }
unpack_map = {
        'I' : 'i32'
        }

def codegen(desc):
    generateHeader(desc)
    generateBody(desc)

def generateHeader(desc):
    (class_name, _, methods) = desc
    wrapper_header = 'simple.h'
    wrapper_class = 'SimpleWrapper'

    def emitHead(f):
        f.write('#include \"{}\"\n\n'.format(wrapper_header))
        f.write('class {} : public {} {{\n'.format(class_name, wrapper_class))
        f.write('public:\n')
        f.write('\t{}(): {}(\"{}\") {{}}\n'.format(
            class_name,
            wrapper_class,
            '{}.wasm'.format(class_name))) # FIXME: wasm file locating.

    def emitTail(f):
        f.write('};\n')

    def emitAttributes(f):
        pass

    def emitMethods(f):

        def checkStatic(retype):
            flag = ''
            if retype[0] == '+':
                flag = 'static '
            return '{}{}'.format(flag, type_map[retype[-1]])
        
        def unpackParams(params):
            real_types = []
            for ch in params:
                real_types.append(type_map[ch])
            return ', '.join(real_types)

        for ent in methods:
            (method_name, method_retype, method_params) = ent
            f.write('\t{} {}({});\n'.format(
                checkStatic(method_retype),
                method_name,
                unpackParams(method_params)))


    with open(class_name + '.h', 'w') as target:
        emitHead(target)
        emitAttributes(target)
        emitMethods(target)
        emitTail(target)

def generateBody(desc):
    (class_name, _, methods) = desc

    def emitHeaders(f):
        f.write('#include \"{}\"\n\n'.format(class_name + '.h'))

    def emitMethods(f):
        for ent in methods:
            (method_name, method_retype, method_params) = ent
            arg_names = []

            def unpackParams(params):
                real_types = []
                i = 0
                for ch in params:
                    arg_name = 'arg{}'.format(i)
                    arg_names.append(arg_name)
                    i += 1
                    real_types.append('{} {}'.format(
                        type_map[ch],
                        arg_name))
                return ', '.join(real_types)

            f.write('{} {}({}) {{\n'.format(
                type_map[method_retype],
                '{}::{}'.format(class_name, method_name),
                unpackParams(method_params)))
            f.write('\tArgVec args;\n')
            for arg in arg_names:
                f.write('\targs.push_back(WrapArg({}));\n'.format(arg))
            f.write('\tInvokeMethod(\"{}\", args, {});\n'.format(
                method_name,
                0 if method_retype == 'V' else 1))
            if method_retype != 'V':
                f.write('\treturn args[0].of.{};\n'.format(
                    unpack_map[method_retype]))
            f.write('}\n\n')

    with open(class_name + '.cpp', 'w') as target:
        emitHeaders(target)
        emitMethods(target)

