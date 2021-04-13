#!/usr/bin/env python3

import sys

with open(sys.argv[1], 'r') as target:
    target = target.read()

within_class = target[target.find('class'):].replace('private', 'private static').replace('public', '@Export public static').replace('static static', 'static')



imports = 'import de.inetsoftware.jwebassembly.api.annotation.Export;'
print("{}\n\npublic {}".format(
    imports,
    within_class
))