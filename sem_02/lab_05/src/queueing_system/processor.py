class ProcessRequest:
    def __init__(self, generator, max_queue_size=-1):
        self.random_generator = generator
        self.queue = 0
        self.received = 0
        self.max_queue = max_queue_size
        self.processed = 0
        self.next = 0

    def receive_request(self):
        if self.max_queue == -1 or self.max_queue > self.queue:
            self.queue += 1
            self.received += 1
            return True
        return False

    def process_request(self):
        if self.queue > 0:
            self.queue -= 1
            self.processed += 1

    def delay(self):
        return self.random_generator.generate()
