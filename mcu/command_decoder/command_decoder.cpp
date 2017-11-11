#include "command_decoder.h"
#include "tools/global_def.h"
#include <stdint.h>
#include <string.h>

struct Command {
    enum CommandCode code;
    char value[COMMAND_MAX_LEN];
};

#define COMMANDS_NR 5

struct Command Commands[COMMANDS_NR] = {
        {FS_HELLO,         "fshello"},
        {FS_RESET,         "fsreset"},
        {FS_PACKETS_NR,    "fspnum"},
        {FS_FREQUENCY,     "fsfreq"},
        {FS_PACKETS,       "fspget"}
};

enum CommandCode decode_message(const char* msg)
{
    if (!msg)
        return FS_NONE;
        
    uint32_t command_nr;
    for (command_nr = 0; command_nr < ARRAY_LEN(Commands); command_nr++)
    {
        enum CommandCode command_code = Commands[command_nr].code;
        char* command_value = Commands[command_nr].value;
        if (strcmp(command_value, msg) == 0)
            return command_code;
    }
    return FS_NONE;
}