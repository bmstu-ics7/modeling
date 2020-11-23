from numpy import random as nr
from . import exceptions as ex


class Uniform:
    def __init__(self, a, b):
        if not 0 <= a <= b:
            raise ex.ParameterError("Parameters must be 0 <= a <= b")
        self._a = a
        self._b = b

    def generate(self):
        return nr.uniform(self._a, self._b)


class Exponential:
    def __init__(self, lambd):
        self._lambda = 1 / lambd

    def generate(self):
        return nr.exponential(self._lambda)
