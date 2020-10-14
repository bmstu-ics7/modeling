#!/usr/bin/env python3

from datetime import datetime


def random_digit():
    time = datetime.now()
    now_ms = time.microsecond % 60
    now_second = time.second
    now_minute = time.minute

    file = None
    if now_minute % 2 == 0:
        file = "even_table.csv"
    else:
        file = "odd_table.csv"

    with open(file) as opened:
        i = 0
        for row in opened:
            i += 1
            if i == now_second:
                return int(row[now_ms])

    return None


def table_random(count):
    result = 0
    for _ in range(count):
        digit = random_digit()
        result = result * 10 + digit
    return result


if __name__ == "__main__":
    try:
        print(table_random(5))
    except Exception:
        print("File error")
