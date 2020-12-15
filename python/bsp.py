import typing


class Location:
    def __init__(self, row, col):
        self.row = row
        self.col = col
        self.id = self._get_id(self.row, self.col)

    def __repr__(self):
        return f"{self.row}::{self.col}::{self.id}"

    @staticmethod
    def _get_id(row, col):
        return row*8 + col


def _to_binary(s: str) -> str:
    translation_table = s.maketrans({"F": "0", "B": "1", "L": "0", "R": "1"})
    return s.translate(translation_table)


def linereader(filename: str) -> typing.Tuple[str]:
    """read input and yield strings split into two strings
    representing 7 bits and 3 bits, respectively

    Args:
        filename (str): path to input

    Yields:
        tuple(str): FB and LR positions
    """
    with open(filename, "r") as f:
        for line in f:
            line = _to_binary(line.rstrip("\n"))
            yield Location(int(line[:7], 2), int(line[7:], 2), )

# F/0 means left/lower half
# B/1 means right/upper half

class BSPNode:
    def __init__(self):
        """constructor that declares data for current node, left and right subtrees"""
        self.left = None
        self.right = None
        self.data = []


class BSP:
    def __init__(self):
        """Initialize binary tree"""
        self.tree = BSPNode()

    
