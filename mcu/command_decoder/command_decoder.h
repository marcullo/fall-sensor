#ifndef COMMAND_DECODER_H_
#define COMMAND_DECODER_H_

#include <stdint.h>

#define COMMAND_MAX_LEN         40
#define COMMAND_INFO_MAX_LEN    120

/* it is important to keep order of the enum as is */
enum CommandCode {
    FS_HELLO,
    FS_GOODBYE,
    FS_RESET,
    FS_PACKETS_NR,
    FS_GET_PACKETS,
    FS_REMOVE_PACKETS,
    FS_GET_CONFIG,
    FS_SET_CONFIG,
    FS_RESTORE_CONFIG,
    FS_HELP,
    FS_NONE
};

enum CommandCode decode_message(const char* msg);
bool decoder_get_next_command_info(char* dest, uint32_t len);

#endif /* COMMAND_DECODER_H_ */