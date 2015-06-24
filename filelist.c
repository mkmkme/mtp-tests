#include <stdio.h>
#include <libmtp.h>
#include <inttypes.h>

const char* const get_type(LIBMTP_filetype_t type)
{
    if (type == LIBMTP_FILETYPE_FOLDER)
        return "FOLDER";
    else
        return "not folder :)";
}

int main(void)
{
    LIBMTP_mtpdevice_t *device = LIBMTP_Get_First_Device();
    if (!device) {
        fputs("Oops, no devices!\n", stderr);
        return 1;
    }
    LIBMTP_file_t *files = LIBMTP_Get_Filelisting_With_Callback(device, NULL, NULL);
    if (!files) {
        fputs("Oops, cannot get filelisting!\n", stderr);
        return 2;
    }
    LIBMTP_file_t *file = files, *tmp = NULL;
    while (file) {
        if (file->parent_id == 0)
            printf("File %s. Type: %s. Size: %"PRIu64"\n", file->filename, get_type(file->filetype), file->filesize);
        tmp = file;
        file = file->next;
        LIBMTP_destroy_file_t(tmp);
    }
    return 0;
}
