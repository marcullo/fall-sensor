#include "command_decoder.h"
#include "tools/global_def.h"
#include "string_data.h"
#include <stdint.h>

struct Command {
    enum CommandCode code;
    char* value;
};

struct Command Commands[] = {
        {FS_HELLO,          "fshello"},
        {FS_GOODBYE,        "fsbye"},
        {FS_RESET,          "fsreset"},
        {FS_REMOVE_PACKETS, "fspremove"},
        {FS_PACKETS_NR,     "fspnum"},
        {FS_FREQUENCY,      "fsfreq"},
        {FS_GET_PACKETS,    "fspget"}
};

/*----------------------------------------------------------------------------*/

enum CommandCode decode_message(const char* msg)
{
    if (!msg)
        return FS_NONE;

    uint32_t command_nr;
    for (command_nr = 0; command_nr < ARRAY_LEN(Commands); command_nr++)
    {
        enum CommandCode command_code = Commands[command_nr].code;
        char* command_value = Commands[command_nr].value;
        if (strncasecmp(command_value, msg) == 0)
            return command_code;
    }
    return FS_NONE;
}