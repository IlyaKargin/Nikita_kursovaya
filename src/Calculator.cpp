
#include "Calculator.h"

#include <iostream>
#include <vector>
#include <limits>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/ioctl.h>

#include "ServerError.h"

void Calculator::math(int work_sock)
{
    uint32_t vectorNum;
    uint32_t vectorLenght;

    recv(work_sock, &vectorNum, sizeof(vectorNum), 0);
    // цикл векторов
    for (uint32_t j = 0; j < vectorNum; j++)
    {
        recv(work_sock, &vectorLenght, sizeof(vectorLenght), 0); // прием длинны для первого вектора

        std::vector<uint16_t> vector;
        vector.resize(vectorLenght);

        recv(work_sock, vector.data(), vector.size() * sizeof(uint16_t), 0);

        uint32_t result = 1;
        for(const auto el: vector)
            result*=el;
        send(work_sock, &result, sizeof(result), 0);
    }
    std::cout << "Program finish!" << std::endl;
    close(work_sock);
}