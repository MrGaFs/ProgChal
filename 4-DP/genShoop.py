#!/usr/bin/env python

import sys

print str(4999*2+1)

for i in range(1, 5000):
	sys.stdout.write(str(i) + ' ')

sys.stdout.write("5000")

for i in range(1, 5000):
	sys.stdout.write(' ' + str(5000-i))
