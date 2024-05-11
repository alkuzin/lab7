/* MIT License
 *
 * Copyright (c) 2024 Alexander (@alkuzin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documen[i]on files (the "Software"), to deal
 * in the Software without restriction, including without limi[i]on the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

#include <iostream>
#include <iomanip>

#include <lab7/utils.hpp>
#include <lab7/chip.hpp>


Chip::Chip(const std::string& filename) : serial(io, filename) 
{
    serial.open(filename);

    if (!serial.is_open()) {
        std::cerr << "Invalid filename provided." << std::endl;
    }

    std::cout << "lab7: opened serial port" << std::endl;

    thread = std::thread(&Chip::thread_process, this);

    pins = {
        "RA2", "RA3", "RA4/T0CKI", "MCLR", "VSS", "RB0/INT",
        "RB1", "RB2", "RB3", "RB4", "RB5", "RB6", "RB7", 
        "VDD", "OSC2/CLKOUT", "OSC1/CLKIN", "RA0", "RA1"
    };

    state.assign(18, false);
}

Chip::~Chip()
{
    if (serial.is_open())
        serial.close();

    thread.detach();
    
    std::cout << "lab7: closed serial port" << std::endl;
}

const char *Chip::_get_state(int pos)
{
    const char *s;
    return s = (state[pos] ? COLOR_GREEN : COLOR_RED);
}

char Chip::_read_char(void)
{
    char c;
    
    boost::asio::read(serial, boost::asio::buffer(&c, 1));

    std::cout << "lab7: read character: " << c << std::endl;

    return c;
}

void Chip::thread_process(void)
{
    std::string recv_str;
    int  pos;
    char c;

    recv_str = "RA4/T0CKI";
    while (!is_sigint_received) {
        recv_str = "";
        while ((c = _read_char()) != '\r')
            recv_str += c;

        std::cout << "lab7: recv_str: \"" << recv_str << "\"\n";
        
        if (!recv_str.empty()) {
            
            pos = _is_valid(recv_str);
            
            if (pos == -1)
                std::cout << "lab7: incorrect pin name \"" << recv_str << "\"\n";
            else {
                state[pos] = true;
                _display_pins();
            }
        }
        exit(0);
    }
}

void Chip::_display_pin(size_t i, size_t j)
{
    std::printf("%*s |%s\u2588%s| %lu", WIDTH_ALIGNMENT, pins[i].c_str(), _get_state(i), COLOR_RESET, (i + 1));
    std::printf("%*lu |%s\u2588%s| ", WIDTH_ALIGNMENT, (j + 1), _get_state(j), COLOR_RESET);
    std::printf("%-*s\n", WIDTH_ALIGNMENT, pins[j].c_str());
    
    if (i != (PINS_SIZE >> 1) - 2)
        std::printf("%*s\n", WIDTH_ALIGNMENT, "\t      _|               |_");
}

void Chip::_display_pins(void)
{
    std::printf("%*s\n", WIDTH_ALIGNMENT, "\n\n\t\t___PIC16F8X____");
    std::printf("%*s\n", WIDTH_ALIGNMENT, "\t      _|               |_");

    for (size_t i = 0; i < (PINS_SIZE >> 1) - 1; i++)
        _display_pin(i, (PINS_SIZE - (i + 1)));
    
    std::printf("%*s\n\n\n", WIDTH_ALIGNMENT, "\t       |_______________|");
}

int  Chip::_is_valid(const std::string &pin)
{
    std::vector<std::string>::iterator it;

    it = std::find(pins.begin(), pins.end(), pin);

    if (it != pins.end())
        return std::distance(pins.begin(), it);
    
    return -1;
}