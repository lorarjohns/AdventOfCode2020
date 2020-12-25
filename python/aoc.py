from pathlib import Path


def lines_generate(filename):
    for line in Path(filename).open():
        line = line.strip("\n")
        if line != "":
            yield line


def lines_list(filename):
    lines = []
    for line in Path(filename).open():
        line = line.strip("\n")
        if line != "":
            lines.append(line)
    return lines
