#ifndef COMMAND_DECODER_H_
#define COMMAND_DECODER_H_

#define COMMAND_MAX_LEN 10

enum CommandCode {
    FS_HELLO,
    FS_RESET,
    FS_PACKETS_NR,
    FS_FREQUENCY,
    FS_PACKETS,
    FS_NONE
};

enum CommandCode decode_message(const char* msg);

#endif /* COMMAND_DECODER_H_ */