from operator import or_, and_
from functools import reduce

infile = "/Users/lorajohns/CLionProjects/AOC2020/data/input6.txt"


def read_groups(infile):
    group = []
    for line in open(infile):
        if line != "\n":
            group.append(set(line.rstrip("\n")))
        else:
            yield group
            group.clear()
    else:
        yield group


def combine_sets(op, sets):
    return reduce(op, sets)


total = intersect = 0
for s in read_groups(infile):
    total += len(combine_sets(or_, s))
    intersect += len(combine_sets(and_, s))

print(total, intersect)
