import numpy as np
import matplotlib.pyplot as plt

def ReadCsv(obv, ord, idx):
    assert(obv in ['k41', 'r42'])
    fName = f'{obv}tot_{ord}_Pseudo-{idx}.csv'
    arr = np.loadtxt(fName, delimiter=',')
    nTot, nPos, nNeg, nSame, pValue, sig = arr
    return pValue, sig

r42o3p = []
r42o5p = []
k41o3p = []
k41o5p = []
r42o3sig = []
r42o5sig = []
k41o3sig = []
k41o5sig = []

for i in range(1, 25):
    # R42, 3rd order
    a, b = ReadCsv('r42', 3, i)
    r42o3p.append(a)
    r42o3sig.append(b)
    # k41, 3rd order
    a, b = ReadCsv('k41', 3, i)
    k41o3p.append(a)
    k41o3sig.append(b)
    # R42, 5th order
    a, b = ReadCsv('r42', 5, i)
    r42o5p.append(a)
    r42o5sig.append(b)
    # k41, 5th order
    a, b = ReadCsv('k41', 5, i)
    k41o5p.append(a)
    k41o5sig.append(b)

fig, ax = plt.subplots()
ax.hist(r42o3sig, 50, (0, 5))
ax.set_xlabel('Significance')
ax.set_ylabel('Number of Simulations')
ax.set_title('C4/C2 - 3rd Order Polynomial')
fig.savefig('R42_3_sig.pdf')
    
ax.cla()
ax.hist(r42o5sig, 50, (0, 5))
ax.set_xlabel('Significance')
ax.set_ylabel('Number of Simulations')
ax.set_title('C4/C2 - 5th Order Polynomial')
fig.savefig('R42_5_sig.pdf')
    
ax.cla()
ax.hist(k41o3sig, 50, (0, 5))
ax.set_xlabel('Significance')
ax.set_ylabel('Number of Simulations')
ax.set_title('k4/k1 - 3rd Order Polynomial')
fig.savefig('k41_3_sig.pdf')
    
ax.cla()
ax.hist(k41o5sig, 50, (0, 5))
ax.set_xlabel('Significance')
ax.set_ylabel('Number of Simulations')
ax.set_title('k4/k1 - 5th Order Polynomial')
fig.savefig('k41_5_sig.pdf')



