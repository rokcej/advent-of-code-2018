import numpy as np
from scipy import signal

with open("input") as f:
	lines = [[1 if c == "#" else 0 for c in l] for l in f.read().splitlines()]
algorithm = np.array(lines[0])
image = np.array(lines[2:])

kernel = np.array([[1<<(i*3+j) for j in range(3)] for i in range(3)])
for i in range(2):
	fill = 0 if i % 2 == 0 else algorithm[0] # Value outside of image
	indices = signal.convolve2d(image, kernel, mode="full", boundary="fill", fillvalue=fill)
	image = algorithm[indices]
print(np.sum(image))
