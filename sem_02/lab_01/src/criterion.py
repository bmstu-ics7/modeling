from math import sqrt


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
