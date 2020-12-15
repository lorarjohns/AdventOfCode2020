from collections import defaultdict

"""
light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.

shiny gold => ['bright white', 'light red', 'dark orange', 'muted yellow']
"""


def get_input():
    with open("/Users/lorajohns/CLionProjects/AOC2020/data/input7.txt") as f:
        lines = f.readlines()
    return lines


def get_rules(lines):
    rules_dict = defaultdict(dict)
    for line in lines:
        outer_bag, _, items = line.rstrip(".\n").partition(" bags contain ")
        can_contain = rules_dict[outer_bag]
        if items != "no other bags":
            inner_bags = items.split(", ")
            for bag in inner_bags:
                num, adj, color, _ = bag.split()
                can_contain[f"{adj} {color}"] = int(num) 
    return rules_dict


def _invert_index(key, values, dict_):
    for val in values:  # iterate over keys
        dict_[val].add(key)


def make_inverted_index(rules_dict):
    inverted_idx = defaultdict(set)
    for outer_bag, inner_set in rules_dict.items():
        _invert_index(outer_bag, inner_set, inverted_idx)
    return inverted_idx


def _get_containing_types_helper(inverted_idx, start_bag, current_bag, result=set()):
    # base case: if we are cycling, stop
    if (current_bag == start_bag) and result:
        return
    containing_bags = inverted_idx.get(current_bag)
    # base case: no more dictionary items to look at
    if not containing_bags:
        return
    # recursion: check the containing bags for the containers
    for container in containing_bags:
        if container not in result:
            # try this subtree
            result.add(container)
            _get_containing_types_helper(inverted_idx, start_bag, container, result)
            # implicit backtrack


def get_containing_types(bag_type, rules=None, inverted=True):
    if not rules:
        rules = get_rules(get_input())
    result = set()
    graph = make_inverted_index(rules) if inverted else rules
    _get_containing_types_helper(graph, bag_type, bag_type, result)
    return result

def _get_inner_bag_sum_helper(rules, start_bag, current_bag, total=0):
    if (current_bag == start_bag) and total:
        return total
    inner_bags = rules.get(current_bag)
    if not inner_bags:
        return total
    for next_bag, count in inner_bags.items():
        total += count
        total += count * _get_inner_bag_sum_helper(rules, start_bag, next_bag, 0)
    return total

def get_inner_bag_sum(bag_type, rules=None):
    if not rules:
        rules = get_rules(get_input())
    total = _get_inner_bag_sum_helper(rules, bag_type, bag_type, 0)
    return total


test1 = """light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.""".split("\n")
test1_rules = get_rules(test1)
test1_sum = get_inner_bag_sum("shiny gold", test1_rules)

assert test1_sum == 32, f"test1 sum: {test1_sum}"

test2 = """shiny gold bags contain 2 dark red bags.
dark red bags contain 2 dark orange bags.
dark orange bags contain 2 dark yellow bags.
dark yellow bags contain 2 dark green bags.
dark green bags contain 2 dark blue bags.
dark blue bags contain 2 dark violet bags.
dark violet bags contain no other bags.""".split("\n")
test2_rules = get_rules(test2)
test2_sum = get_inner_bag_sum("shiny gold", test2_rules)

assert test2_sum == 126, f"test2 sum: {test2_sum}"

print(get_inner_bag_sum("shiny gold"))