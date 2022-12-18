obj-m += $(addsuffix .o, $(notdir $(basename $(wildcard $(BR2_EXTERNAL_MYDIR_PATH)/package/fpgautil/*.c))))
ccflags-y := -DDEBUG -g -std=gnu99 -Wno-declaration-after-statement

.PHONY: all clean


fpgautil: fpgautil.c
	$(CC) -o '$@' '$<'

clean:
	rm fpgautil
