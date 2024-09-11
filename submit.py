import os

# configuration
targetDir = '/path'
obv = 'r42' # should be one of 'r42' 'k[2-4]1'
err = 'tot' # should be one of 'tot' 'stat' 'sys'
ord = 5 # 2 to 5
taskTag = 'Pseudo'
nEntries = 1000
rdSeedStart = 1000 # the random seeds come from rdSeedStart to rdSeedStart+nEntries

assert(obv in ['r42', 'k21', 'k31', 'k41'])
assert(err in ['tot', 'stat', 'sys'])
assert(ord >= 2 and ord <= 5)
assert(nEntries >= 1)
assert(rdSeedStart >= 0)

print('Submit System')
print(f'{targetDir=}')
print(f'{obv=}')
print(f'{err=}')
print(f'{ord=}')
print(f'{taskTag=}')
print(f'{nEntries=}')
print(f'Random seed range: {rdSeedStart} to {nEntries+rdSeedStart}')

print('Prapering job files')
if os.path.exists(targetDir):
    os.system(f'rm -rf {targetDir}')
os.mkdir(targetDir)

os.system(f'cp run {targetDir}/run')
for i in range(nEntries):
    jobFile = f'{targetDir}/{i}.job'
    os.system(f'cp con.job {jobFile}')
    os.system(f'sed -i "s|__OBV__|{obv}|g" {jobFile}')
    os.system(f'sed -i "s|__MER__|{err}|g" {jobFile}')
    os.system(f'sed -i "s|__ORD__|{ord}|g" {jobFile}')
    os.system(f'sed -i "s|__TASKTAG__|{taskTag}|g" {jobFile}')
    os.system(f'sed -i "s|__RDSEED__|{rdSeedStart+i}|g" {jobFile}')

print('Submitting jobs')
for i in range(nEntries):
    os.system(f'cd {targetDir} && condor_submit {i}.job')

print('All done!')
