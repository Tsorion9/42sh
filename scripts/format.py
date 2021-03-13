#!/usr/bin/env python

############################################################
# This script can be used for formatting results of        #
# norminette_linux                                         #   
############################################################

import sys
import os
import re

try:
	filepath = sys.argv[1]
except:
	print("Usage: {} file".format(sys.argv[0]))
	sys.exit()
	

if not os.path.isfile(filepath):
	print("File path {} does not exist. Exiting...".format(filepath))
	sys.exit()

def parse_err_str(line):
	msg = line.split(':')[1]
	line_number = re.findall(r'\d+', line.split(':')[0])
	if (len(line_number) == 0):
		return (0, msg)
	return (line_number[0], msg)

with open(filepath) as fp:
	for line in fp:
		line = line[:-1]
		fields = line.split(' ')
		if (fields[0] == "Norme:"):
			filename = fields[1]
		elif (fields[0] == "Error"):
			line_number, msg = parse_err_str(line)
			print("{}:{} {}".format(filename, line_number, msg))
