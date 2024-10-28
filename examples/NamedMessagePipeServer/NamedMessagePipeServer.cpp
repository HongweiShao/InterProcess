#include <iostream>

#include "NamedMessagePipe.h"

int main()
{
    std::cout << "Starting NamedMessagePipeServer..." << std::endl;

    char pipe_name[] = "\\\\.\\pipe\\MyPipe";

    NamedMessagePipe pipe;
    std::cout << pipe.create(pipe_name, 1024, 1024, 1) << std::endl;

    std::cout << "Named pipe: " << pipe_name << " is created." << std::endl;

    // Wait for a client to connect
    std::cout << pipe.listen() << std::endl;

    char buffer[1024];
    pipe.recv(buffer, 1024);
    std::cout << "Message from client: " << buffer << std::endl;
    pipe.send("Hello from server");
    
    // Close the pipe
    pipe.close();

    std::cout << "NamedMessagePipeServer is stopped." << std::endl;
    
    return 0;
}