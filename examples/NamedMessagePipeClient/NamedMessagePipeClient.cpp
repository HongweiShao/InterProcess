#include <iostream>

#include "NamedMessagePipe.h"

int main()
{
    NamedMessagePipe pipe;

    if (pipe.connect("\\\\.\\pipe\\MyPipe") != 0)
    {
      return 1;
    }

    std::cout << "Connected to pipe" << std::endl;

    // Send a message
    pipe.send("Hello, server!");

    char buffer[1024];
    pipe.recv(buffer, 1024);
    std::cout << "Received: " << buffer << std::endl;

    // Close the pipe
    pipe.close();

    return 0;
}