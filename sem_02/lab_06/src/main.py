#!/usr/bin/env python3

from queueing_system.distribution import RandomGenerator
from queueing_system.generator import GenerateRequest
from queueing_system.processor import ProcessRequest
from queueing_system.modeller import Model
from prettytable import PrettyTable


def main():
    t_clients = 3
    dt_clients = 2

    t_terminal = 4
    dt_terminal = 3

    t_window1 = 10
    dt_window1 = 5

    t_window2 = 15
    dt_window2 = 5

    t_window3 = 15
    dt_window3 = 10

    t_window4 = 20
    dt_window4 = 10

    t_window5 = 20
    dt_window5 = 5

    t_room = 10
    dt_room = 5

    clients_number = 500

    min_result = None
    max_result = None
    min_sum = None
    max_sum = None

    for i in range(1000):
        clients = GenerateRequest(
            RandomGenerator(t_clients, dt_clients),
            "entry",
            clients_number,
        )

        terminals = [
            ProcessRequest(
                RandomGenerator(t_terminal, dt_terminal),
                "terminal1",
                0.1,
                max_queue_size=1,
            ),
            ProcessRequest(
                RandomGenerator(t_terminal, dt_terminal),
                "terminal2",
                0.1,
                max_queue_size=1,
            ),
        ]

        windows = [
            ProcessRequest(
                RandomGenerator(t_window1, dt_window1),
                "window1",
                0.05,
                max_queue_size=5,
                end=False
            ),
            ProcessRequest(
                RandomGenerator(t_window2, dt_window2),
                "window2",
                0.05,
                max_queue_size=5,
                end=False
            ),
            ProcessRequest(
                RandomGenerator(t_window3, dt_window3),
                "window3",
                0.05,
                max_queue_size=5,
                end=True
            ),
            ProcessRequest(
                RandomGenerator(t_window4, dt_window4),
                "window4",
                0.05,
                max_queue_size=5,
                end=True
            ),
            ProcessRequest(
                RandomGenerator(t_window5, dt_window5),
                "window5",
                0.05,
                max_queue_size=5,
                end=True
            ),
        ]

        room = [
            ProcessRequest(
                RandomGenerator(t_room, dt_room),
                "room",
                end=True,
            ),
        ]

        model = Model(clients, terminals, windows, room)
        result = model.event_mode()
        summ = 0

        if min_result is None:
            min_result = result.copy()
            max_result = result.copy()
            min_sum = sum(result.values())
            max_sum = sum(result.values())
        else:
            for key in result.keys():
                summ += result[key]
                if result[key] < min_result[key]:
                    min_result[key] = result[key]
                if result[key] > max_result[key]:
                    max_result[key] = result[key]
            if summ < min_sum:
                min_sum = summ
            if summ > max_sum:
                max_sum = summ

    print()
    print(
        "Общее количество отказов находится в промежутке "
        f"[{min_sum}; {max_sum}] "
        f"[{round(min_sum / clients_number * 100, 2)}%; "
        f"{round(max_sum / clients_number * 100, 2)}%]"
    )
    print()

    table = PrettyTable()
    table.field_names = ["Этап", "min", "max"]
    table.align = "l"
    table.add_row([
        "Отказы на входе",
        min_result['entry'],
        max_result['entry'],
    ])
    table.add_row([
        "Отказы на терминале 1",
        min_result['terminal1'],
        max_result['terminal1'],
    ])
    table.add_row([
        "Отказы на терминале 2",
        min_result['terminal2'],
        max_result['terminal2'],
    ])
    table.add_row([
        "Отказы при распределении очереди",
        min_result['query_window'],
        max_result['query_window'],
    ])
    table.add_row([
        "Отказы на окне 1",
        min_result['window1'],
        max_result['window1'],
    ])
    table.add_row([
        "Отказы на окне 2",
        min_result['window2'],
        max_result['window2'],
    ])
    table.add_row([
        "Отказы на окне 3",
        min_result['window3'],
        max_result['window3'],
    ])
    table.add_row([
        "Отказы на окне 4",
        min_result['window4'],
        max_result['window4'],
    ])
    table.add_row([
        "Отказы на окне 5",
        min_result['window5'],
        max_result['window5'],
    ])
    table.add_row([
        "Отказы в очереди в кабинет",
        min_result['room'],
        max_result['room'],
    ])
    table.add_row([
        "Отказы в кабинете",
        min_result['room'],
        max_result['room'],
    ])
    print(table)


if __name__ == "__main__":
    main()
