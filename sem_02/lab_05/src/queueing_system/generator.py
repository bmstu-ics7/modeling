class GenerateRequest:
    def __init__(self, generator, count):
        self.random_generator = generator
        self.num_requests = count
        self.receivers = []
        self.next = 0

    def generate_request(self):
        self.num_requests -= 1
        for receiver in self.receivers:
            if receiver.receive_request():
                return receiver
        return None

    def delay(self):
        return self.random_generator.generate()
