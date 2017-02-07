#!/usr/bin/python

import sys
import subprocess
import os.path

params = []

for i in range(2,len(sys.argv)):
	if sys.argv[i] == "-tree":
		params.append("-tree")
	if sys.argv[i] == "-symb":
                params.append("-symb")

result = subprocess.call(["./asl_compiler",sys.argv[1]]+params)

if result == 0:
	my_file = sys.argv[1] + ".code"
	if os.path.isfile(my_file):
		subprocess.call(["./virtual_machine",my_file])

