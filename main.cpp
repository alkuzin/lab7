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

#include <filesystem>
#include <iostream>
#include <csignal>

#include <lab7/chip.hpp>
#include <lab7/utils.hpp>

volatile int is_sigint_received;


int main(void)
{
    try {
        std::string filename;

        is_sigint_received = 0;
        signal(SIGINT, sigint_handler);
        signal(SIGSEGV, sigsegv_handler);

        filename = "/dev/ttyUSB0";

        if (!std::filesystem::exists(filename)) {
            std::cerr << "lab7: incorrect filename: \"" << filename << "\"!\n";
            exit(EXIT_FAILURE);
        }

        Chip chip(filename);

        chip.thread_process();
    }
    catch(const std::exception& e) {
        std::cerr << "lab7: " << e.what() << std::endl;
    }

    return 0;
}