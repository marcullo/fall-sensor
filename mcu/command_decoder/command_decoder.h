#ifndef COMMAND_DECODER_H_
#define COMMAND_DECODER_H_

#define COMMAND_MAX_LEN 40

enum CommandCode {
    FS_HELLO,
    FS_GOODBYE,
    FS_RESET,
    FS_REMOVE_PACKETS,
    FS_PACKETS_NR,
    FS_FREQUENCY,
    FS_GET_PACKETS,
    FS_NONE
};

enum CommandCode decode_message(const char* msg);

#endif /* COMMAND_DECODER_H_ */