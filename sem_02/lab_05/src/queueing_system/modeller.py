from .processor import ProcessRequest


class Model:
    def __init__(self, generator, operators, computers):
        self.generator = generator
        self.operators = operators
        self.computers = computers

    def event_mode(self):
        refusals = 0
        generated_requests = self.generator.num_requests
        generator = self.generator

        generator.receivers = self.operators.copy()
        self.operators[0].receivers = [self.computers[0]]
        self.operators[1].receivers = [self.computers[0]]
        self.operators[2].receivers = [self.computers[1]]

        generator.next = generator.delay()
        self.operators[0].next = self.operators[0].delay()

        blocks = [
            generator,
            self.operators[0],
            self.operators[1],
            self.operators[2],
            self.computers[0],
            self.computers[1],
        ]

        while generator.num_requests >= 0:
            current_time = generator.next
            for block in blocks:
                if 0 < block.next < current_time:
                    current_time = block.next

            for block in blocks:
                if current_time == block.next:
                    if not isinstance(block, ProcessRequest):
                        next_generator = generator.generate_request()
                        if next_generator is not None:
                            next_generator.next = \
                                current_time + next_generator.delay()
                        else:
                            refusals += 1
                        generator.next = current_time + generator.delay()
                    else:
                        block.process_request()
                        if block.queue == 0:
                            block.next = 0
                        else:
                            block.next = current_time + block.delay()

        return {"refusal_percentage": refusals / generated_requests * 100,
                "refusals": refusals}
