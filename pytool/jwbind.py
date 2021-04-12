#!/usr/bin/env python3

from parser import parse
from wparser import parseWasm
from codegen import codegen

import sys

#  if len(sys.argv) < 2:
#      print('Usage:\tjwbind <file>')
#      sys.exit(1)

raw = parseWasm(sys.argv[1])
desc = parse(raw)
codegen(desc)
