import numpy as np
from PIL import Image

arr = np.loadtxt("C:/JS/CNN-on-FPGA/PYformnist/a.txt", delimiter=',')
arr = ((arr * 255) + 1)

arr = np.reshape(arr, (28, 28))
arr = np.rot90(arr)
arr = np.rot90(arr)
arr = np.rot90(arr)

arr = np.flip(arr, axis=1) 
im = Image.fromarray(arr)
im.show()

print(arr)
