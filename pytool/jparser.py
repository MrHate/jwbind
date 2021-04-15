#!/usr/bin/env python3

# jparser.py parses java source code at the first pass to add necessary annotation
# and static marks.

import sys

with open(sys.argv[1], 'r') as target:
    target = target.read()

within_class = target[target.find('class'):].replace('private', 'private static').replace(
    'public', '@Export public static').replace('@Export public static static', '@ExportStatic public static')


imports = 'import de.inetsoftware.jwebassembly.api.annotation.Export;\nimport de.inetsoftware.jwebassembly.api.annotation.ExportStatic;'
print("{}\n\npublic {}".format(
    imports,
    within_class
))
