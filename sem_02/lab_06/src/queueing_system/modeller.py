from .processor import ProcessRequest


class Model:
    def __init__(self, clients, terminals, windows, room):
        self.clients = clients
        self.terminals = terminals
        self.windows = windows
        self.room = room

    def event_mode(self):
        clients = self.clients

        clients.receivers = self.terminals.copy()
        self.terminals[0].receivers = self.windows.copy()
        self.terminals[1].receivers = self.windows.copy()
        self.windows[0].receivers = self.room.copy()
        self.windows[1].receivers = self.room.copy()

        clients.next = clients.delay()
        self.terminals[0].next = self.terminals[0].delay()

        blocks = []
        blocks += [clients]
        blocks += self.terminals
        blocks += self.windows
        blocks += self.room

        refusals = {}
        for block in blocks:
            refusals[block.name] = 0
        refusals["query_window"] = 0

        while clients.num_requests >= 0:
            current_time = clients.next
            for block in blocks:
                if 0 < block.next < current_time:
                    current_time = block.next

            for block in blocks:
                if current_time == block.next:
                    if not isinstance(block, ProcessRequest):
                        next_clients = clients.generate_request()

                        if next_clients is not None:
                            next_clients.next = \
                                current_time + next_clients.delay()
                        else:
                            refusals[block.name] += 1
                        clients.next = current_time + clients.delay()
                    else:
                        next_process = block.process_request()
                        if block.queue == 0:
                            block.next = 0
                        else:
                            block.next = current_time + block.delay()

                        if next_process == "ban":
                            if block.name.find("terminal") != -1:
                                refusals["query_window"] += 1
                            else:
                                refusals[block.name] += 1
                            continue

                        if block.end:
                            continue

                        if next_process is not None:
                            next_process.next = \
                                current_time + next_process.delay()
                        else:
                            refusals[block.name] += 1

        return refusals
