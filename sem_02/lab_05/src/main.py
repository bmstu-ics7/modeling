#!/usr/bin/env python3

from queueing_system.distribution import RandomGenerator
from queueing_system.generator import GenerateRequest
from queueing_system.processor import ProcessRequest
from queueing_system.modeller import Model


def main():
    min_p = 100
    max_p = 0
    min_r = 300
    max_r = 0

    for i in range(1000):
        time_clients = 10
        delta_time_clients = 2

        first_operator = 20
        second_operator = 40
        third_operator = 40

        first_computer = 15
        second_computer = 30

        delta_first_operators = 5
        delta_second_operators = 10
        delta_third_operators = 20

        clients_number = 300

        generator = GenerateRequest(
            RandomGenerator(time_clients, delta_time_clients),
            clients_number,
        )

        operators = [
            ProcessRequest(
                RandomGenerator(first_operator, delta_first_operators),
                max_queue_size=1,
            ),
            ProcessRequest(
                RandomGenerator(second_operator, delta_second_operators),
                max_queue_size=1,
            ),
            ProcessRequest(
                RandomGenerator(third_operator, delta_third_operators),
                max_queue_size=1,
            ),
        ]

        computers = [
            ProcessRequest(RandomGenerator(first_computer)),
            ProcessRequest(RandomGenerator(second_computer)),
        ]

        model = Model(generator, operators, computers)
        result = model.event_mode()

        if (min_p > result['refusal_percentage']):
            min_p = result['refusal_percentage']
        if (max_p < result['refusal_percentage']):
            max_p = result['refusal_percentage']
        if (min_r > result['refusals']):
            min_r = result['refusals']
        if (max_r < result['refusals']):
            max_r = result['refusals']

    min_p = round(min_p, 5)
    max_p = round(max_p, 5)
    print("Процент отказа находится в промежутке [{0}; {1}]"
          .format(min_p, max_p))
    print("Число клиентов, получивших отказ находится в промежутке [{0}; {1}]"
          .format(min_r, max_r))


if __name__ == "__main__":
    main()
