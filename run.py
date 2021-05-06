from build.module_name import *
import time
import numpy as np
from numpy.random import randint
import matplotlib.pyplot as plt
from tqdm import tqdm
from scipy.interpolate import make_interp_spline

##################### Initialization
samples=[]
NumberOfData=[]
outputFFT=[]
outputFT=[]
timeFFT=[]
timeFT=[]
error=[]
for i in range(4):
    samples.append([randint(1,10000) for _ in range(2**(4+i*3))])   
    NumberOfData.append(len(samples[i]))
print('NumberOfData = ', NumberOfData)

##################### FFT Time & Output Caclulations
print("Analyzing FFT...")
for sample in tqdm(samples):
    start = time.time()
    outputFFT.append(fft(sample))
    timeFFT.append(time.time() - start)
print('timeFFT = ', timeFFT[-1])

##################### FT Time & Output Caclulations
print("Analyzing FT...")
for sample in tqdm(samples):
    start = time.time()
    outputFT.append(dft(sample))
    timeFT.append(time.time()- start)
print('timeFT = ', timeFT[-1])

##################### Error Calculations
for i in tqdm(range(len(outputFFT))):
    error.append(np.square(np.absolute(np.subtract(outputFT[i],outputFFT[i]))).mean())
print('error = ', error)

##################### Time Complexity Plot
plt.subplot(211)

# Smoothing the curve
# 300 represents number of points to make between X.min and X.max
xnew = np.linspace(min(NumberOfData), max(NumberOfData), 300) 
spline_ft = make_interp_spline(NumberOfData, timeFT, k=3)
ft_smooth = spline_ft(xnew)
plt.plot(xnew, ft_smooth, label='FT')
spline_fft = make_interp_spline(NumberOfData, timeFFT, k=3)
fft_smooth = spline_fft(xnew)
plt.plot(xnew, fft_smooth, label='FFT')
plt.title('Time Complexity')
plt.xlabel('Input Size')
plt.ylabel('Time')
plt.legend()

##################### Output Error Plot
plt.subplot(212)
# Smoothing the curve
spline_error = make_interp_spline(NumberOfData, error, k=3)
error_smooth = spline_error(xnew)
plt.plot(xnew, error_smooth, label='Error')
plt.title('Output Error')
plt.xlabel('Input Size')
plt.ylabel('Error')
plt.tight_layout()
plt.legend()
plt.show()
