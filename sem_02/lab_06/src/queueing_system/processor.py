from random import shuffle
from numpy import random as nr


class ProcessRequest:
    def __init__(self, generator, name, ban_probality=0, max_queue_size=-1, end=False):
        self.random_generator = generator
        self.queue = 0
        self.received = 0
        self.max_queue = max_queue_size
        self.processed = 0
        self.next = 0
        self.receivers = []
        self.end = end
        self.name = name
        self.ban_probality = ban_probality

    def receive_request(self):
        if self.max_queue == -1 or self.max_queue > self.queue:
            self.queue += 1
            self.received += 1
            return True
        return False

    def process_request(self):
        if nr.sample() < self.ban_probality:
            return "ban"
        if self.queue > 0:
            self.queue -= 1
            self.processed += 1
        shuffle(self.receivers)
        for receiver in self.receivers:
            if receiver.receive_request():
                return receiver
        return None

    def delay(self):
        return self.random_generator.generate()
