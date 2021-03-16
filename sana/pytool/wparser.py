#!/usr/bin/python3

def parseWasm(name):
    with open(name, 'r', errors='ignore') as target:
        wb = target.read()
        return wb[wb.find('SaNA'):]

