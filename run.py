from build.module_name import *
import time
import numpy as np
from numpy.random import randint
import matplotlib.pyplot as plt
from tqdm import tqdm
from scipy.interpolate import make_interp_spline

##################### Initialization
sizes = np.linspace(1, 1e6, 10)
inputs = [randint(0, 10, int(i)) for i in sizes]
outputFFT=[]
outputFT=[]
timeFFT=[]
timeFT=[]
error=[]

##################### FFT Time & Output Caclulations
print("Analyzing FFT...")
for sample in tqdm(inputs):
    start = time.time()
    outputFFT.append(fft(sample))
    timeFFT.append(time.time() - start)
print('timeFFT = ', timeFFT[-1])
# print('timeFFT = ', outputFFT)
# print('timeFFT = ', outputFFT[-1])

##################### FT Time & Output Caclulations
print("Analyzing FT...")
for sample in tqdm(inputs):
    start = time.time()
    outputFT.append(dft(sample))
    timeFT.append(time.time()- start)
print('timeFT = ', timeFT[-1])
# print('timeFT = ', outputFT)
# print('timeFT = ', outputFT[-1])

##################### Error Calculations
for i in tqdm(range(len(outputFFT))):
    error.append(np.square(np.absolute(np.subtract(outputFT[i],outputFFT[i]))).mean())

##################### Time Complexity Plot
plt.subplot(211)
# Smoothing the curve
# 300 represents number of points to make between T.min and T.max
xnew = np.linspace(sizes.min(), sizes.max(), 300) 

spline_ft = make_interp_spline(sizes, timeFT, k=3)
ft_smooth = spline_ft(xnew)
plt.plot(xnew, ft_smooth, label='FT')

spline_fft = make_interp_spline(sizes, timeFFT, k=3)
fft_smooth = spline_fft(xnew)
plt.plot(xnew, fft_smooth, label='FFT')

plt.title('Time Complexity')
plt.xlabel('Input Size')
plt.ylabel('Time')
plt.legend()

##################### Output Error Plot
plt.subplot(212)
# Smoothing the curve
spline_error = make_interp_spline(sizes, error, k=3)
error_smooth = spline_error(xnew)

plt.plot(xnew, error_smooth, label='Error')
plt.title('Output Error')
plt.xlabel('Input Size')
plt.ylabel('Error')
plt.tight_layout()
plt.legend()
plt.show()
