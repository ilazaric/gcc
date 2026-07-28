BOOT_CFLAGS := -O3 -fno-omit-frame-pointer $(filter-out -O%, $(BOOT_CFLAGS))
