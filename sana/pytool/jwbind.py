from parser import parse
from wparser import parseWasm
from codegen import codegen

import sys

codegen(parse(parseWasm(sys.argv[1])))
