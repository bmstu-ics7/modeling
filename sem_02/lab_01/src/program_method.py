#!/usr/bin/env python3

from random import randint


def program_random(count):
    start = 0 if count == 1 else 10 ** (count - 1)
    end = 10 ** count - 1
    return randint(start, end)


if __name__ == "__main__":
    print(program_random(5))
