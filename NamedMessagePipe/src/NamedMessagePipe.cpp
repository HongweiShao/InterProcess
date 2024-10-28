#include "NamedMessagePipe.h"

NamedMessagePipe::NamedMessagePipe()
  : name(""), pipe_handle(INVALID_HANDLE_VALUE), is_server(false)
{
}

NamedMessagePipe::~NamedMessagePipe()
{
  this->close();
}

int NamedMessagePipe::create(const char *name, uint16_t read_buffer_size, uint16_t write_buffer_size, uint8_t max_num_connections)
{
  // Check parameters
  if (name == nullptr) return __LINE__;
  if (read_buffer_size == 0 || write_buffer_size == 0) return __LINE__;
  if (max_num_connections == 0) return __LINE__;
  
  // close previous pipe
  this->close();

  // Create the pipe
  strcpy_s(this->name, name);
  this->pipe_handle = CreateNamedPipeA(
    this->name,
    PIPE_ACCESS_DUPLEX,
    PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
    max_num_connections,
    read_buffer_size,
    write_buffer_size,
    0,
    NULL);
  if (this->pipe_handle == INVALID_HANDLE_VALUE) return __LINE__;

  

  this->is_server = true;
  
  return 0;
}

int NamedMessagePipe::listen()
{
  // check status
  if (!this->is_server) return __LINE__;
  if (pipe_handle == INVALID_HANDLE_VALUE) return __LINE__;

  if (ConnectNamedPipe(pipe_handle, NULL) == FALSE) return __LINE__;

  return 0;
}

int NamedMessagePipe::unlisten()
{
  if (!this->is_server) return __LINE__;
  if (pipe_handle == INVALID_HANDLE_VALUE) return __LINE__;

  if (DisconnectNamedPipe(pipe_handle) == FALSE) return __LINE__;

  return 0;
}

int NamedMessagePipe::connect(const char *name)
{
  // check parameters
  if (name == nullptr) return __LINE__;

  // check status
  this->close();

  this->pipe_handle = CreateFileA(
    name,
    GENERIC_READ | GENERIC_WRITE,
    0,
    NULL,
    OPEN_EXISTING,
    0,
    NULL);

  if (this->pipe_handle == INVALID_HANDLE_VALUE) return __LINE__;

  return 0;
}

int NamedMessagePipe::recv(char *buffer, uint16_t size)
{
  if (buffer == nullptr) return __LINE__;
  if (size == 0) return __LINE__;

  DWORD bytes_read = 0;
  if (ReadFile(pipe_handle, buffer, size, &bytes_read, NULL) == FALSE) return __LINE__;
  if (bytes_read == 0) return __LINE__;

  return 0;
}

int NamedMessagePipe::send(const char *buffer)
{
  if (buffer == nullptr) return __LINE__;
  if (strlen(buffer) == 0) return __LINE__;

  DWORD bytes_written = 0;
  if (WriteFile(pipe_handle, buffer, static_cast<DWORD>(strlen(buffer))+1, &bytes_written, NULL) == FALSE) return __LINE__;

  return 0;
}

int NamedMessagePipe::close()
{
  if (pipe_handle != INVALID_HANDLE_VALUE)
  {
    if (this->is_server)
    {
      DisconnectNamedPipe(pipe_handle);
    }
    CloseHandle(pipe_handle);
    this->pipe_handle = INVALID_HANDLE_VALUE;
    this->is_server = false;
  }

  return 0;
}
