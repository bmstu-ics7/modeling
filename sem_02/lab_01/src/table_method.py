#!/usr/bin/env python3

from datetime import datetime


def get_number(row, now_ms, count):
    first_digit = row[now_ms % 60]
    number = "1" if first_digit == "0" else first_digit

    for j in range(1, count):
        number += row[(now_ms + j) % 60]
    return int(number)


def table_random(count):
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
                return get_number(row, now_ms, count)

    return None


if __name__ == "__main__":
    try:
        print(table_random(5))
    except Exception:
        print("File error")
