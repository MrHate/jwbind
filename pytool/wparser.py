#!/usr/bin/env python3

def parseWasm(name):
    import subprocess
    result = subprocess.run(['./cpp/build/out/wparser', name], stdout=subprocess.PIPE)
    return result.stdout.decode(encoding="utf-8", errors="ignore")

    # with open(name, 'r', errors='ignore') as target:
    #     wb = target.read()
    #     return wb[wb.find('SaNA'):]

if __name__ == '__main__':
    import sys
    print(parseWasm(sys.argv[1]))
