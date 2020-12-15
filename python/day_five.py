from bsp import linereader

inputfile = '/Users/lorajohns/CLionProjects/AOC2020/data/input5.txt'

lr = linereader(inputfile)

ids = sorted([loc.id for loc in lr])

print(max(ids))

target = None
for i in range(len(ids) - 2):
    if ids[i+1] - ids[i] > 1:
        target = ids[i] + 1
        break
print(target)
