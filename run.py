import ctypes

library = ctypes.CDLL('./lib.so')

library.connect()

# library.dft()
