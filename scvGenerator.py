#!/usr/bin/env python
# encoding: utf-8
import random
start = 1
stop = 50
step = 0.5
precision = 0.5
f = 1 / precision

x = []
for _ in xrange(1000000):
x.append("{0:.2f}".format(random.randrange(start*f, stop*f, step*f)/f))

with open('file.csv', 'w') as f:
f.write(";".join(x))
