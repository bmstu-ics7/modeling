from math import sqrt
from scipy.stats import chisquare


def get_characteristic(a, b):
    m = (a + b) / 2
    sigma = sqrt(((b - a) ** 2) / 12)
    return m, sigma


def frequency(numbers, a, b):
    m, sigma = get_characteristic(a, b)
    start, end = m - sigma, m + sigma
    count = sum(map(lambda x: 1 if start <= x <= end else 0, numbers))
    return count / len(numbers)


def ideal_frequency(a, b):
    m, sigma = get_characteristic(a, b)
    return (2 * sigma) / (b - a)


def hi(sequence):
    max_value = max(sequence)
    base = 1

    while max_value >= 1:
        max_value /= 10
        base *= 10

    freq_table = [0] * base
    for value in sequence:
        freq_table[value - base] += 1

    freq_table = [freq for freq in freq_table if freq != 0]
    chi2, prob = chisquare(freq_table)
    return chi2, prob
