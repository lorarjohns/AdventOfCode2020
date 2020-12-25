import aoc


def has_two_sum(target, preamble):
    summands = set()
    for num in preamble:
        if target - num in summands:
            return True
        else:
            summands.add(num)
    return False


def find_invalid_num(lines, preamble_len=25):
    # preamble_lines = lines[0:preamble_length]
    # encoded_lines = lines[preamble_length:]
    lines = [int(n) for n in lines]
    for i, line in enumerate(lines):
        if i < preamble_len:
            continue
        preamble = lines[i-preamble_len:i]
        if not has_two_sum(line, preamble):
            return line


def solve_part_one():
    lines = aoc.lines_list("../data/input9.txt")
    ans = find_invalid_num(lines)
    print(ans)