#include "command_decoder.h"
#include "globals.h"
#include "utils/string_utils.h"
#include <stdint.h>
#include <stdio.h>

struct Command {
    enum CommandCode code;
    char* value;
    char* description;
};

const struct Command Commands[] = {
        {FS_HELLO,          "fshello", "check if the device is waiting for command"},
        {FS_GOODBYE,        "fsbye", "disconnect"},
        {FS_RESET,          "fsreset", "reset (switch supply)"},
        {FS_PACKETS_NR,     "fspnum", "get number of packets saved on SD card and ready for a transfer to a PC"},
        {FS_GET_PACKETS,    "fspget", "transfer all measurement packets (and delete locally afterwards)"},
        {FS_REMOVE_PACKETS, "fspremove", "delete all packets saved on SD card"},
        {FS_GET_CONFIG,     "fscfgget", "get currently running configuration"},
        {FS_SET_CONFIG,     "fscfgset", "set configuration (and save it to a file) using a JSON format"},
        {FS_RESTORE_CONFIG, "fscfgrestore", "restore configuration file to a default form"},

        {FS_HELP,           "fshelp", "call this list"},
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

bool decoder_get_next_command_info(char* dest, uint32_t len)
{
    static int cnt = -1;
    
    if (!dest || len < COMMAND_INFO_MAX_LEN)
        return false;
    if (cnt > FS_HELP) {
        cnt = -1;
        return false;
    }
    
    if (cnt < 0)
    {
        sprintf(dest, "\r\nList of available commands:"); 
    }
    else
    {
        sprintf(dest, "%s\r\n   %s", Commands[cnt].value, Commands[cnt].description); 
    }
        
    cnt++;
    return true;
}