#!/usr/bin/env python3

# codegen.py generate target cpp header and source file according
# to given class description.

import os

type_map = {
    'V': 'void',
    'I': 'int32_t',
    'J': 'int64_t',
    'F': 'float',
    'D': 'double',
}
unpack_map = {
    'I': 'i32',
    'J': 'i64',
    'F': 'f32',
    'D': 'f64',
}

max_arg_len = 0


def codegen(desc, name):
    name, _ = os.path.splitext(name)
    generateBody(desc, name)
    generateHeader(desc, name)


def generateHeader(desc, class_name):
    (_, _, methods) = desc
    wrapper_header = 'simple.h'
    wrapper_class = 'SimpleWrapper'

    def emitHead(f):
        f.write('#include \"{}\"\n\n'.format(wrapper_header))
        f.write('class {} : public {} {{\n'.format(class_name, wrapper_class))
        f.write('static ArgVec args;\n')
        f.write('public:\n')
        global max_arg_len
        f.write('\t{}(): {}(\"{}\") {{}}\n'.format(
            class_name,
            wrapper_class,
            '{}.wasm'.format(class_name)))

    def emitTail(f):
        f.write('};\n')

    def emitAttributes(f):
        pass

    def emitMethods(f):
        f.write('\n')
        has_static_method = False

        def emitStaticInstance(ff):
            ff.write('\n\tstatic {}& staticInstance() {{\n'.format(class_name))
            ff.write('\t\tstatic {} _inst;\n'.format(class_name))
            ff.write('\t\treturn _inst;\n'.format(class_name))
            ff.write('\t}\n')

        def checkStatic(retype):
            flag = ''
            if retype[-1] == '+':
                nonlocal has_static_method
                has_static_method = True
                flag = 'static '
            return '{}{}'.format(flag, type_map[retype[0]])

        def unpackParams(params):
            real_types = []
            for ch in params:
                real_types.append(type_map[ch])
            return ', '.join(real_types)

        for ent in methods:
            (method_name, method_retype, method_params) = ent
            if method_name == '<clinit>' or method_name == '<start>':
                continue
            f.write('\t{} {}({});\n'.format(
                checkStatic(method_retype),
                method_name,
                unpackParams(method_params)))

        if has_static_method:
            emitStaticInstance(f)

    with open(class_name + '.h', 'w') as target:
        emitHead(target)
        emitAttributes(target)
        emitMethods(target)
        emitTail(target)


def generateBody(desc, class_name):
    (_, _, methods) = desc

    def emitHeaders(f):
        f.write('#include \"{}\"\n\n'.format(class_name + '.h'))

    def emitMethods(f):
        for ent in methods:
            (method_name, method_retype, method_params) = ent
            if method_name == '<clinit>' or method_name == '<start>':
                continue
            is_static = method_retype[-1] == '+'
            method_retype = method_retype[0]
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
            # f.write('\tArgVec args({});\n'.format(len(arg_names)))
            arg_pos = 0
            global max_arg_len
            arg_len = len(arg_names)
            max_arg_len = max(arg_len, max_arg_len)
            for arg in arg_names:
                f.write('\tWrapArg({}, args, {});\n'.format(arg, arg_pos))
                arg_pos += 1
            f.write('\t{}InvokeMethod(\"{}\", args, {}, {});\n'.format(
                'staticInstance().' if is_static else '',
                method_name,
                0 if method_retype == 'V' else 1,
                arg_len))
            if method_retype != 'V':
                f.write('\treturn args[0].of.{};\n'.format(
                    unpack_map[method_retype]))
            f.write('}\n\n')

    def emitStaticMemberDefinition(f):
        f.write('SimpleWrapper::ArgVec {}::args({});\n'.format(
            class_name,
            max_arg_len
        ))

    with open(class_name + '.cpp', 'w') as target:
        emitHeaders(target)
        emitMethods(target)
        emitStaticMemberDefinition(target)
