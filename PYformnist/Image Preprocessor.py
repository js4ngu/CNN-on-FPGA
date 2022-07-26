import numpy as np
from PIL import Image

# Read image
img = Image.open('PYformnist/test.jpg').convert("L")
img.show()

img = np.rot90(img)
img = np.rot90(img)
img = np.rot90(img)
img = np.flip(img, axis=1) 

img = np.resize(img, (1, 784))
test_data = ((np.array(img) / 255) - 1) * -1
x = np.array(test_data)

np.savetxt('PYformnist/testdata.txt',x, fmt='%1.6f', delimiter = ',')
print(x)
print(x.shape)