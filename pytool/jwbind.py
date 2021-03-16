from parser import parse
from wparser import parseWasm
from codegen import codegen

import sys

#  if len(sys.argv) < 2:
#      print('Usage:\tjwbind <file>')
#      sys.exit(1)

codegen(parse(parseWasm(sys.argv[1])))
