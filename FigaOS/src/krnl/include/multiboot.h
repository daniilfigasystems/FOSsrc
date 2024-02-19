#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#define MULTIBOOT_MAGIC_HEADER      0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC  0x2BADB002

/* The Multiboot header. */
typedef struct {
    unsigned int magic;
    unsigned int flags;
    unsigned int checksum;
    unsigned int header_addr;
    unsigned int load_addr;
    unsigned int load_end_addr;
    unsigned int bss_end_addr;
    unsigned int entry_addr;
} MULTIBOOT_HEADER;

/* The symbol table for a.out. */
typedef struct {
    unsigned int tabsize;
    unsigned int strsize;
    unsigned int addr;
    unsigned int reserved;
} AOUT_SYMBOL_TABLE;

/* The section header table for ELF. */
typedef struct {
    unsigned int num;
    unsigned int size;
    unsigned int addr;
    unsigned int shndx;
} ELF_SECTION_HEADER_TABLE;

typedef struct {
    /* required, defined in entry.asm */
    unsigned int flags;

    /* available low-high memory from BIOS, present if flags[0] is set(MEMINFO in entry.asm) */
    unsigned int mem_low;
    unsigned int mem_high;

    /* "root" partition, present if flags[1] is set(BOOTDEVICE in entry.asm) */
    unsigned int boot_device;

    /* kernel command line, present if flags[2] is set(CMDLINE in entry.asm) */
    unsigned int cmdline;

    /* no of modules loaded, present if flags[3] is set(MODULECOUNT in entry.asm) */
    unsigned int modules_count;
    unsigned int modules_addr;

    /* symbol table info, present if flags[4] & flags[5] is set(SYMT in entry.asm) */
    union {
        AOUT_SYMBOL_TABLE aout_sym;
        ELF_SECTION_HEADER_TABLE elf_sec;
    } u;

    /* memory mapping, present if flags[6] is set(MEMMAP in entry.asm) */
    unsigned int mmap_length;
    unsigned int mmap_addr;

    /* drive info, present if flags[7] is set(DRIVE in entry.asm) */
    unsigned int drives_length;
    unsigned int drives_addr;

    /* ROM configuration table, present if flags[8] is set(CONFIGT in entry.asm) */
    unsigned int config_table;

    /* boot loader name, present if flags[9] is set(BOOTLDNAME in entry.asm) */
    unsigned int boot_loader_name;

    /* Advanced Power Management(APM) table, present if flags[10] is set(APMT in entry.asm) */
    unsigned int apm_table;

    /* video info, present if flags[11] is set(VIDEO in entry.asm) */
    unsigned int vbe_control_info;
    unsigned int vbe_mode_info;
    unsigned short vbe_mode;
    unsigned short vbe_interface_seg;
    unsigned short vbe_interface_off;
    unsigned short vbe_interface_len;

    /* video framebufer info, present if flags[12] is set(VIDEO_FRAMEBUF in entry.asm)  */
    unsigned long framebuffer_addr;
    unsigned int framebuffer_pitch;
    unsigned int framebuffer_width;
    unsigned int framebuffer_height;
    unsigned char framebuffer_bpp;
    unsigned char framebuffer_type;  // indexed = 0, RGB = 1, EGA = 2

} MULTIBOOT_INFO;


typedef enum {
    MULTIBOOT_MEMORY_AVAILABLE = 1,
    MULTIBOOT_MEMORY_RESERVED,
    MULTIBOOT_MEMORY_ACPI_RECLAIMABLE,
    MULTIBOOT_MEMORY_NVS,
    MULTIBOOT_MEMORY_BADRAM
} MULTIBOOT_MEMORY_TYPE;

typedef struct {
    unsigned int size;
    unsigned int addr_low;
    unsigned int addr_high;
    unsigned int len_low;
    unsigned int len_high;
    MULTIBOOT_MEMORY_TYPE type;
} MULTIBOOT_MEMORY_MAP;

#endif