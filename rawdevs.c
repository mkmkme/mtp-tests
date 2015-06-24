#include <libmtp.h>
#include <stdlib.h>
#include <inttypes.h>

const char* const get_type(LIBMTP_filetype_t type) {
    switch (type) {
        case LIBMTP_FILETYPE_FOLDER:
            return "FOLDER";
        case LIBMTP_FILETYPE_WAV:
            return "WAV";
        case LIBMTP_FILETYPE_MP3:
            return "MP3";
        case LIBMTP_FILETYPE_WMA:
            return "WMA";
        case LIBMTP_FILETYPE_OGG:
            return "OGG";
        case LIBMTP_FILETYPE_AUDIBLE:
            return "AUDIBLE";
        case LIBMTP_FILETYPE_MP4:
            return "MP4";
        case LIBMTP_FILETYPE_UNDEF_AUDIO:
            return "UNDEF_AUDIO";
        case LIBMTP_FILETYPE_WMV:
            return "WMV";
        case LIBMTP_FILETYPE_AVI:
            return "AVI";
        case LIBMTP_FILETYPE_MPEG:
            return "MPEG";
        case LIBMTP_FILETYPE_ASF:
            return "ASF";
        case LIBMTP_FILETYPE_QT:
            return "QT";
        case LIBMTP_FILETYPE_UNDEF_VIDEO:
            return "UNDE_VIDEO";
        case LIBMTP_FILETYPE_JPEG:
            return "JPEG";
        case LIBMTP_FILETYPE_JFIF:
            return "JFIF";
        case LIBMTP_FILETYPE_TIFF:
            return "TIFF";
        case LIBMTP_FILETYPE_BMP:
            return "BMP";
        case LIBMTP_FILETYPE_GIF:
            return "GIF";
        case LIBMTP_FILETYPE_PICT:
            return "PICT";
        case LIBMTP_FILETYPE_PNG:
            return "PNG";
        case LIBMTP_FILETYPE_VCALENDAR1:
            return "VCALENDAR1";
        case LIBMTP_FILETYPE_VCALENDAR2:
            return "VCALENDAR2";
        case LIBMTP_FILETYPE_VCARD2:
            return "VCARD2";
        case LIBMTP_FILETYPE_VCARD3:
            return "VCARD3";
        case LIBMTP_FILETYPE_WINDOWSIMAGEFORMAT:
            return "WINDOWSIMAGEFORMAT";
        case LIBMTP_FILETYPE_WINEXEC:
            return "WINEXEC";
        case LIBMTP_FILETYPE_TEXT:
            return "TEXT";
        case LIBMTP_FILETYPE_HTML:
            return "HTML";
        case LIBMTP_FILETYPE_FIRMWARE:
            return "FIRMWARE";
        case LIBMTP_FILETYPE_AAC:
            return "AAC";
        case LIBMTP_FILETYPE_MEDIACARD:
            return "MEDIACARD";
        case LIBMTP_FILETYPE_FLAC:
            return "FLAC";
        case LIBMTP_FILETYPE_MP2:
            return "MP2";
        case LIBMTP_FILETYPE_M4A:
            return "M4A";
        case LIBMTP_FILETYPE_DOC:
            return "DOC";
        case LIBMTP_FILETYPE_XML:
            return "XML";
        case LIBMTP_FILETYPE_XLS:
            return "XLS";
        case LIBMTP_FILETYPE_PPT:
            return "PPT";
        case LIBMTP_FILETYPE_MHT:
            return "MHT";
        case LIBMTP_FILETYPE_JP2:
            return "JP2";
        case LIBMTP_FILETYPE_JPX:
            return "JPX";
        case LIBMTP_FILETYPE_ALBUM:
            return "ALBUM";
        case LIBMTP_FILETYPE_PLAYLIST:
            return "PLAYLIST";
        case LIBMTP_FILETYPE_UNKNOWN:
        default:
            return "UNKNOWN!";

    }
}

int main(void)
{
    LIBMTP_raw_device_t *rawdevs;
    int numofrawdevs;
    LIBMTP_Init();
    if (LIBMTP_Detect_Raw_Devices(&rawdevs, &numofrawdevs) != LIBMTP_ERROR_NONE) {
        printf("Oops, cannot get devices list!\n");
        return -1;
    }
    LIBMTP_mtpdevice_t *dev = LIBMTP_Open_Raw_Device_Uncached(&rawdevs[0]);
    if (!dev) {
        printf("Oops, cannot open raw device!\n");
        return 1;
    }
    if (LIBMTP_Get_Storage(dev, LIBMTP_STORAGE_SORTBY_FREESPACE) == -1) {
        printf("Oops, cannot get storages!\n");
        free(dev);
        return 2;
    }
    LIBMTP_devicestorage_t *sts;
    for (sts = dev->storage; sts; sts = sts->next) {
        printf("Looking for storage: %s\n", sts->StorageDescription);
        LIBMTP_file_t *ff = LIBMTP_Get_Files_And_Folders(dev, sts->id, 0);
        if (!ff) {
            printf("Oops, filelisting for this storage is NULL!\n");
             continue;
        }
        LIBMTP_file_t *file = ff, *tmp = NULL;
        while (file) {
            //if (file->parent_id == 0) {
                printf("File %s, size=%"PRIu64", id=%"PRIu32", type=%s\n",
                        file->filename, file->filesize, 
                        file->item_id,
                        get_type(file->filetype));
           //}
            tmp = file;
            file = file->next;
            LIBMTP_destroy_file_t(tmp);
        }
    }
    printf("Done!\n");
    free(rawdevs);
    return 0;
}
