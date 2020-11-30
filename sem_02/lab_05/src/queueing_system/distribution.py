from numpy import random as nr


class RandomGenerator:
    def __init__(self, begin, delta=0):
        self.begin = begin
        self.d = delta

    def generate(self):
        if (self.d == 0):
            return self.begin
        return nr.uniform(self.begin - self.d, self.begin + self.d)
