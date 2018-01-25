# convert rgb pixels in raw file to grayscale
# (3 bytes to 1 byte per pixel)
import os
from array import array

fname = 'sam46orig.raw'
outname = 'sam46.raw'

data = array('B')
px, grayscale = [],[]
with open(fname, 'rb') as f:
    data.fromfile(f, os.stat(fname).st_size)
px = [data[i:i + 3] for i in range(0, len(data), 3)]
grayscale = [int(0.2989 * p[0] + 0.5870 * p[1] + 0.1140 * p[2]) for p in px]
for i in xrange(len(grayscale)):
	if grayscale[i] > 235:
		grayscale[i] = 0x0f
	else: grayscale[i] = 0xff
with open(outname, 'wb') as f:
    f.write(bytearray(grayscale))
print 'done!'
