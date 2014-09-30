libmtp tests
============================================
There is bunch of tests of the mtp library
* filelist.c looks for filelisting on the device and proves that `LIBMTP_Get_Filelisting_With_Callback()` doesn't put folders into the list.
* rawdevs.c works with `LIBMTP_Get_Files_And_Folders()` and proves that this function puts a content from inner folders to list for some reason.
