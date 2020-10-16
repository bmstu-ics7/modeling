#!/usr/bin/env python3

import sys
import argparse
from prettytable import PrettyTable
from table_method import table_random
from program_method import program_random
import criterion


def create_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--count', required=True, type=int)
    return parser


def main():
    parser = create_parser()
    args = parser.parse_args(sys.argv[1:])

    table_random_one = list()
    table_random_two = list()
    table_random_thr = list()
    progr_random_one = list()
    progr_random_two = list()
    progr_random_thr = list()

    table = PrettyTable()
    table.field_names = [
        "\033[1mN\033[0m",
        "\033[1mТабл. 1 цифра\033[0m",
        "\033[1mТабл. 2 цифры\033[0m",
        "\033[1mТабл. 3 цифры\033[0m",
        "\033[1mПрогр. 1 цифра\033[0m",
        "\033[1mПрогр. 2 цифры\033[0m",
        "\033[1mПрогр. 3 цифры\033[0m",
    ]

    for i in range(args.count):
        table_random_one.append(table_random(1))
        table_random_two.append(table_random(2))
        table_random_thr.append(table_random(3))
        progr_random_one.append(program_random(1))
        progr_random_two.append(program_random(2))
        progr_random_thr.append(program_random(3))

        table.add_row([
            i + 1,
            table_random_one[-1],
            table_random_two[-1],
            table_random_thr[-1],
            progr_random_one[-1],
            progr_random_two[-1],
            progr_random_thr[-1],
        ])

    print(table)

    table_frequency = PrettyTable()
    table_frequency.field_names = [
        "\033[1mЧастотный критерий\033[0m",
        "\033[1mТабл. 1 цифра\033[0m",
        "\033[1mТабл. 2 цифры\033[0m",
        "\033[1mТабл. 3 цифры\033[0m",
        "\033[1mПрогр. 1 цифра\033[0m",
        "\033[1mПрогр. 2 цифры\033[0m",
        "\033[1mПрогр. 3 цифры\033[0m",
    ]

    table_frequency.add_row([
        "Полученный результат",
        "{:.4f}".format(criterion.frequency(table_random_one, 0, 9)),
        "{:.4f}".format(criterion.frequency(table_random_two, 10, 99)),
        "{:.4f}".format(criterion.frequency(table_random_thr, 100, 999)),
        "{:.4f}".format(criterion.frequency(progr_random_one, 0, 9)),
        "{:.4f}".format(criterion.frequency(progr_random_two, 10, 99)),
        "{:.4f}".format(criterion.frequency(progr_random_thr, 100, 999)),
    ])

    table_frequency.add_row([
        "Ожидаемый результат",
        "{:.4f}".format(criterion.ideal_frequency(0, 9)),
        "{:.4f}".format(criterion.ideal_frequency(10, 99)),
        "{:.4f}".format(criterion.ideal_frequency(100, 999)),
        "{:.4f}".format(criterion.ideal_frequency(0, 9)),
        "{:.4f}".format(criterion.ideal_frequency(10, 99)),
        "{:.4f}".format(criterion.ideal_frequency(100, 999)),
    ])

    print(table_frequency)

    table_xi = PrettyTable()
    table_xi.field_names = [
        "\033[1mКритерий хи квадрат\033[0m",
        "\033[1mТабл. 1 цифра\033[0m",
        "\033[1mТабл. 2 цифры\033[0m",
        "\033[1mТабл. 3 цифры\033[0m",
        "\033[1mПрогр. 1 цифра\033[0m",
        "\033[1mПрогр. 2 цифры\033[0m",
        "\033[1mПрогр. 3 цифры\033[0m",
    ]

    chi_table_one = criterion.calc_hi(table_random_one)
    chi_table_two = criterion.calc_hi(table_random_two)
    chi_table_thr = criterion.calc_hi(table_random_thr)
    chi_progr_one = criterion.calc_hi(progr_random_one)
    chi_progr_two = criterion.calc_hi(progr_random_two)
    chi_progr_thr = criterion.calc_hi(progr_random_thr)

    table_xi.add_row([
        "chi^2",
        "{:.4f}".format(chi_table_one[0]),
        "{:.4f}".format(chi_table_two[0]),
        "{:.4f}".format(chi_table_thr[0]),
        "{:.4f}".format(chi_progr_one[0]),
        "{:.4f}".format(chi_progr_two[0]),
        "{:.4f}".format(chi_progr_thr[0]),
    ])

    table_xi.add_row([
        "p",
        "{:.4f}".format(chi_table_one[1] * 100),
        "{:.4f}".format(chi_table_two[1] * 100),
        "{:.4f}".format(chi_table_thr[1] * 100),
        "{:.4f}".format(chi_progr_one[1] * 100),
        "{:.4f}".format(chi_progr_two[1] * 100),
        "{:.4f}".format(chi_progr_thr[1] * 100),
    ])

    print(table_xi)


if __name__ == "__main__":
    main()
