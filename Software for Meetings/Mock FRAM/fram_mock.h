//
// Mock FRAM for example
// Lee A. Congdon
// 24 June 2022
//

#ifndef FRAM_MOCK_H
#define FRAM_MOCK_H

#define FRAM_DEFAULT_ADDRESS (0x50)
#define FRAM_MEMORY_SIZE 32768

#include <cstddef>

class Fram {
public:
    Fram(void);

    bool begin(int i2caddr = FRAM_DEFAULT_ADDRESS, void *Bus = NULL);
    bool write(std::size_t addr, int value);
    int read(std::size_t  addr);
    bool write(std::size_t addr, int *buffer, std::size_t num);
    bool read(std::size_t addr, int *buffer, std::size_t num);

protected:
    int _i2caddr = 0;
    const std::size_t _memory_size = FRAM_MEMORY_SIZE;
    int _memory[FRAM_MEMORY_SIZE];

};

#endif