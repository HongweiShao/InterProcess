#ifndef NamedMessagePipe_h
#define NamedMessagePipe_h

#include <cstdint>
#include <windows.h>

#include "NamedMessagePipeLibrary.h"

// 仅考虑双向消息管道
class NAMEDMSGPIPELIB_API NamedMessagePipe
{
private:
  static const int MAX_PIPE_NAME_LENGTH = 256;

  char name[MAX_PIPE_NAME_LENGTH];
  HANDLE pipe_handle;

  bool is_server;

public:
  NamedMessagePipe();
  ~NamedMessagePipe();

  int create(const char *name, uint16_t read_buffer_size, uint16_t write_buffer_size, uint8_t max_num_connections = 1);

  int listen();
  int unlisten();

  int connect(const char *name);

  int recv(char *buffer, uint16_t size);
  int send(const char *buffer);

  int close();
};

#endif // NamedMessagePipe_h