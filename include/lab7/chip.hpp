/* MIT License
 *
 * Copyright (c) 2024 Alexander (@alkuzin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
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

#ifndef _LAB_7_CHIP_HPP_
#define _LAB_7_CHIP_HPP_

#include <string>
#include <vector>
#include <thread>

#include <boost/asio.hpp>
#include <lab7/utils.hpp>


class Chip
{
    // boost::asio::io_service  io;
    // boost::asio::serial_port serial;
    std::thread thread;
    std::vector<bool> state;
    std::vector<std::string> pins;

    public:
        Chip(const std::string& filename);
        ~Chip(void);

        void thread_process(void);

    private:
        char _read_char(void);
        int  _is_valid(const std::string &pin);
        void _display_pins(void);
        const char *_get_state(int pos);
        void _display_pin(size_t i, size_t j);
};

#endif // _LAB_7_CHIP_HPP_