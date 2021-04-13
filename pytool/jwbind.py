#!/usr/bin/env python3

# jwbind.py is the entry python script to drive the backend
# part including parsing class description and code generation.

from parser import parse
from wparser import parseWasm
from codegen import codegen

import sys

#  if len(sys.argv) < 2:
#      print('Usage:\tjwbind <file>')
#      sys.exit(1)

raw = parseWasm(sys.argv[1])
desc = parse(raw)
codegen(desc, sys.argv[1])
