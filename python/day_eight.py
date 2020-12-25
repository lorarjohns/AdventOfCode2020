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


def split_instruction(code):
    instruction, n = code.split()
    n = int(n)
    return instruction, n


def execute(code, n, acc, current):
    if code == "nop":
        # advance to the next instruction
        current += 1
    elif code == "acc":
        # increase the accumulator and advance
        acc += n
        current += 1
    elif code == "jmp":
        current += n
    return acc, current


def find_repeat(lines):
    lines = list(enumerate(lines))
    acc = 0
    start = current = 0
    visited = set()
    # execute first instruction
    current_line = lines[start]
    visited.add(current_line[0])
    code, n = split_instruction(current_line[1])
    acc, current = execute(code, n, acc, current)
    while True:
        try:
            current_line = lines[current]
            # If we have been at this index before, break
            if current_line[0] in visited:
                break
            # Otherwise, add it to the seen positions and execute
            visited.add(current_line[0])
            code, n = split_instruction(current_line[1])
            acc, current = execute(code, n, acc, current)
        except IndexError:
            print(acc)
            break
    return acc


def solve_part_one(filename="../data/input8.txt"):
    lines = lines_list(filename)
    answer = find_repeat(lines)
    return answer


def solve_part_two(filename="../data/input8.txt"):
    lines = lines_list(filename)
    patch_code(lines)


def is_infinite_loop(lines):
    if find_repeat(lines):
        return True
    return False


def patch_code(lines):
    for i, line in enumerate(lines):
        code, n = split_instruction(line)
        if code == "nop":
            switch_nop_to_jmp = list(lines)
            switch_nop_to_jmp[i] = f"jmp {str(n)}"
            if is_infinite_loop(switch_nop_to_jmp):
                continue
            else:
                return find_repeat(switch_nop_to_jmp)
        elif code == "jmp":
            switch_jmp_to_nop = list(lines)
            switch_jmp_to_nop[i] = f"nop {str(n)}"
            if is_infinite_loop(switch_jmp_to_nop):
                continue
            else:
                return find_repeat(switch_jmp_to_nop)

if __name__ == "__main__":
    print(solve_part_one())