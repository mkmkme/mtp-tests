#include <stdio.h>
#include <libmtp.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    LIBMTP_Init();
    printf("Searching for device...\n");
    LIBMTP_mtpdevice_t* device = LIBMTP_Get_First_Device();
    if (!device) {
        printf("Oops, no devices!\n");
        return 1;
    }
    const int id = 10494;
    int r = 0;
    LIBMTP_BeginEditObject(device, id);
    char s[64] = "The quick brown fox jumps over lazy dog\n";
    printf("Calling for LIBMTP_SendPartialObject...\n");
    r = LIBMTP_SendPartialObject(device, id, 0, (unsigned char *)s, strlen(s));
    if (r < 0) {
        printf("Oops, an error!\n");
        goto cleanup;
    } else
        printf("LIBMTP_SendPartialObject done successfully!\n");
    LIBMTP_EndEditObject(device, id);
cleanup:
    LIBMTP_Dump_Errorstack(device);
    LIBMTP_Clear_Errorstack(device);
    LIBMTP_Release_Device(device);
    return r < 0 ? -1 : 0;
}
