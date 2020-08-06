/* gcc.ld - GCC linker script */

/* HEADER_SIZE defines the alignment needed for INTVEC; default to 256 */
HEADER_SIZE = DEFINED(HEADER_SIZE) ? HEADER_SIZE : 256;

/* Set the default size of PSSTORE to 0 bytes */
PSSTORE_SIZE = DEFINED(PSSTORE_SIZE) ? PSSTORE_SIZE : 0;

  ASSERT ( PSSTORE_SIZE >= 0 , "

======================================================================
======== LINKER ERROR: PSSTORE_SIZE must be >= 0
======================================================================
" )

/* Use the default bootloader size from the gcc-cfg.ld file */
BTL_SIZE = DEFINED(BTL_SIZE) ? BTL_SIZE : DEFAULT_BTL_SIZE;

/* Do not reserve any space for the bootloader if it lives in the DI page */
BTL_SIZE = DEFINED(GECKO_INFO_PAGE_BTL) ? 0 : BTL_SIZE;
BTL_SIZE = DEFINED(APP_GECKO_INFO_PAGE_BTL) ? 0 : BTL_SIZE;
BTL_SIZE = DEFINED(STA_GECKO_INFO_PAGE_BTL) ? 0 : BTL_SIZE;
BTL_SIZE = DEFINED(LOCAL_STORAGE_GECKO_INFO_PAGE_BTL) ? 0 : BTL_SIZE;

/* Do not reserve any space for the bootloader if NULL_BTL is defined */
BTL_SIZE = DEFINED(NULL_BTL) ? 0 : BTL_SIZE;

  ASSERT ( BTL_SIZE >= 0, "

======================================================================
======== LINKER ERROR: BTL_SIZE must be >= 0
======================================================================
" )

/* LOCKBITS occupy the top flash page on Series2 family which         */
/* have an 8kB FLASH_PAGE_SIZE. The linker should set                 */
/* LOCKBITS_IN_MAINFLASH_SIZE to 8kB if compiling/linking             */
/* for a Series 2 family.  Otherwise LOCKBITS_IN_MAINFLASH_SIZE is 0  */
/* since LOCKBITS_IN_MAINFLASH_SIZE is not used.                      */
DEFAULT_LOCKBITS_IN_MAINFLASH_SIZE = 0;
LOCKBITS_IN_MAINFLASH_SIZE = DEFINED(LOCKBITS_IN_MAINFLASH_SIZE) ? LOCKBITS_IN_MAINFLASH_SIZE : DEFAULT_LOCKBITS_IN_MAINFLASH_SIZE;

/* Set the default size of the SimEEPROM to 0 bytes */
SIMEEPROM_SIZE = DEFINED(SIMEEPROM_SIZE) ? SIMEEPROM_SIZE : 0;

  ASSERT ( SIMEEPROM_SIZE >= 0 , "

======================================================================
======== LINKER ERROR: SIMEEPROM_SIZE must be >= 0
======================================================================
" )

/* Set the default size of the long token section to 0 bytes */
LONGTOKEN_SIZE = DEFINED(LONGTOKEN_SIZE) ? LONGTOKEN_SIZE : 0;

  ASSERT ( LONGTOKEN_SIZE >= 0 , "

======================================================================
======== LINKER ERROR: LONGTOKEN_SIZE must be >= 0
======================================================================
" )

/* Check if we're using a local storage bootloader, either legacy or Gecko. */
USING_LOCAL_STORAGE_BTL = DEFINED(LOCAL_STORAGE_BTL) ? 1 : 0;
USING_LOCAL_STORAGE_BTL = DEFINED(LOCAL_STORAGE_GECKO_INFO_PAGE_BTL) ? 1 : USING_LOCAL_STORAGE_BTL;

/* Calculate the default size of internal storage area. It is 0 if we aren't  */
/* using a local storage bootloader, otherwise roughly half of the app space. */
DEFAULT_INTERNAL_STORAGE_SIZE = ((MFB_TOP - MFB_BOTTOM + 1) - LOCKBITS_IN_MAINFLASH_SIZE - PSSTORE_SIZE - LONGTOKEN_SIZE - SIMEEPROM_SIZE - BTL_SIZE)/ 2 + FLASH_PAGE_SIZE;
DEFAULT_INTERNAL_STORAGE_SIZE = ((DEFAULT_INTERNAL_STORAGE_SIZE - 1) | (FLASH_PAGE_SIZE - 1)) + 1;
DEFAULT_INTERNAL_STORAGE_SIZE = USING_LOCAL_STORAGE_BTL ? DEFAULT_INTERNAL_STORAGE_SIZE : 0;

/* Figure out the actual size of the internal storage area. If the user gives */
/* us a size, we use that. If not, we use the default calculated above.       */
INTERNAL_STORAGE_SIZE = DEFINED(INTERNAL_STORAGE_SIZE) ? INTERNAL_STORAGE_SIZE : DEFAULT_INTERNAL_STORAGE_SIZE;

  ASSERT ( INTERNAL_STORAGE_SIZE >= 0, "

======================================================================
======== LINKER ERROR: INTERNAL_STORAGE_SIZE must be >= 0
======================================================================
" )

/* Map out all of the regions we use in our applications */
SECTIONS {

  /* Create an initialized and uninitialize BAT region to support NULL_BTL */
  .bat.noinit MFB_BOTTOM (NOLOAD) :
  {
    KEEP( *(.bat.noinit) );
    . = ALIGN(2);  /* Align each segment to a Flash word boundary */
    PROVIDE(__BAT_NOINIT__end = .);
  }>flash
  .bat.init MFB_BOTTOM :
  {
    KEEP( *(.bat .bat.*) );
    . = ALIGN(2);  /* Align each segment to a Flash word boundary */
    PROVIDE(__BAT_INIT__end = .);
  }>flash

  /* Pick the region for the BAT that was actually used */
  PROVIDE(__BAT__begin = MFB_BOTTOM);
  PROVIDE(__BAT__size = MAX(SIZEOF(.bat.noinit), SIZEOF(.bat.init)));
  PROVIDE(__BAT__end = MFB_BOTTOM + MAX(SIZEOF(.bat.noinit), SIZEOF(.bat.init)));

  /* The location of the AAT should be either right after the bootloader or */
  /* right after the BAT if there is no bootloader. */
  . = MAX((MFB_BOTTOM + BTL_SIZE), .);
  .aat . :
  {
    PROVIDE(__AAT__begin = .);
    KEEP( *(.aat .aat.*) );
    . = ALIGN(2);  /* Align each segment to a Flash word boundary */
    PROVIDE(__AAT__end = .);
  }>flash
  PROVIDE(__AAT__size = SIZEOF(.aat));

  . = ALIGN(HEADER_SIZE);
  .intvec . :
  {
    PROVIDE(__INTVEC__begin = .);
    KEEP( *(.intvec .intvec.*) );
    . = ALIGN(2);  /* Align each segment to a Flash word boundary */
    PROVIDE(__INTVEC__end = .);
  }>flash
  PROVIDE(__INTVEC__size = SIZEOF(.intvec));

  .vectors . :
  {
    PROVIDE(__VECTORS__begin = .);
    KEEP( *(.vectors .vectors.*) );
    . = ALIGN(2);  /* Align each segment to a Flash word boundary */
    PROVIDE(__VECTORS__end = .);
  }>flash
  PROVIDE(__VECTORS__size = SIZEOF(.vectors));

  .text . :
  {
    KEEP(*(.init))
    KEEP(*(.fini))

    PROVIDE(__TEXT__begin = .);
    * (.text .text.*);
    . = ALIGN(2);  /* Align each segment to a Flash word boundary */
    PROVIDE(__TEXT__end = .);
  }>flash
  PROVIDE(__TEXT__size = SIZEOF(.text));

  .rodata . :
  {
    PROVIDE(__CONST__begin = .);
    * (.rodata .rodata.*);
    . = ALIGN(2);  /* Align each segment to a Flash word boundary */
    PROVIDE(__CONST__end = .);
  }>flash
  PROVIDE(__CONST__size = SIZEOF(.rodata));

  .data_init . :
  {
    PROVIDE(__DATA_INIT__begin = .);
    PROVIDE(__etext = .);

    /* No need to place anything here explicitly */
    /* Just reserve room for .data to relocate here */

    PROVIDE(__DATA_INIT__end = __DATA_INIT__begin + SIZEOF(.data));
  }>flash
  . += SIZEOF(.data);
  PROVIDE(__DATA_INIT__size = SIZEOF(.data));

  ASSERT ( . < MFB_TOP - SIMEEPROM_SIZE - INTERNAL_STORAGE_SIZE - LONGTOKEN_SIZE - PSSTORE_SIZE - LOCKBITS_IN_MAINFLASH_SIZE + 1 , "

======================================================================
======== LINKER ERROR: Not enough flash (Application space)
======================================================================
" )

  . = MFB_TOP - SIMEEPROM_SIZE - INTERNAL_STORAGE_SIZE - LONGTOKEN_SIZE - PSSTORE_SIZE - LOCKBITS_IN_MAINFLASH_SIZE + 1;
  .simee ALIGN(FLASH_PAGE_SIZE) (NOLOAD) :
  {
    KEEP( * (.simee .simee.*) );
  }>flash
  OUR_BEGIN = (SIZEOF(.simee) == 0) ? 0 : ADDR(.simee);
  PROVIDE(__SIMEE__begin = OUR_BEGIN);
  PROVIDE(__SIMEE__end = OUR_BEGIN + SIZEOF(.simee));
  PROVIDE(__SIMEE__size = SIZEOF(.simee));

  ASSERT ( __SIMEE__size == SIMEEPROM_SIZE , "

======================================================================
======== LINKER ERROR: SIMEEPROM_SIZE is misconfigured
======================================================================
" )

  . = MFB_TOP - INTERNAL_STORAGE_SIZE - LONGTOKEN_SIZE - PSSTORE_SIZE - LOCKBITS_IN_MAINFLASH_SIZE + 1;
  .internal_storage . (NOLOAD) :
  {
    * (.internal_storage .internal_storage.*);
  }>flash
  OUR_BEGIN = (SIZEOF(.internal_storage) == 0) ? 0 : ADDR(.internal_storage);
  PROVIDE(__INTERNAL_STORAGE__begin = OUR_BEGIN);
  PROVIDE(__INTERNAL_STORAGE__end = OUR_BEGIN + SIZEOF(.internal_storage));
  PROVIDE(__INTERNAL_STORAGE__size = SIZEOF(.internal_storage));

  ASSERT ( __INTERNAL_STORAGE__size == INTERNAL_STORAGE_SIZE , "

======================================================================
======== LINKER ERROR: INTERNAL_STORAGE_SIZE is misconfigured
======================================================================
" )

  . = MFB_TOP - LONGTOKEN_SIZE - PSSTORE_SIZE - LOCKBITS_IN_MAINFLASH_SIZE + 1;
  .longtoken (NOLOAD) :
  {
    * (.longtoken .longtoken.*) ;
  }>flash
  OUR_BEGIN = (SIZEOF(.longtoken) == 0) ? 0 : ADDR(.longtoken);
  PROVIDE(__LONGTOKEN__begin = OUR_BEGIN);
  PROVIDE(__LONGTOKEN__end = OUR_BEGIN + SIZEOF(.longtoken));
  PROVIDE(__LONGTOKEN__size = SIZEOF(.longtoken));

  ASSERT ( __LONGTOKEN__size == LONGTOKEN_SIZE , "

======================================================================
======== LINKER ERROR: LONGTOKEN_SIZE is misconfigured
======================================================================
" )

  . = MFB_TOP - PSSTORE_SIZE - LOCKBITS_IN_MAINFLASH_SIZE + 1;
  .psstore ALIGN(FLASH_PAGE_SIZE) (NOLOAD) :
  {
    KEEP( * (.psstore .psstore.*) );
  }>flash
  OUR_BEGIN = (SIZEOF(.psstore) == 0) ? 0 : ADDR(.psstore);
  PROVIDE(__PSSTORE__begin = OUR_BEGIN);
  PROVIDE(__PSSTORE__end = OUR_BEGIN + SIZEOF(.psstore));
  PROVIDE(__PSSTORE__size = SIZEOF(.psstore));

  ASSERT ( __PSSTORE__size == PSSTORE_SIZE , "

======================================================================
======== LINKER ERROR: PSSTORE_SIZE is misconfigured
======================================================================
" )

  . = MFB_TOP - LOCKBITS_IN_MAINFLASH_SIZE + 1;
  .lockbits_in_mainflash ALIGN(FLASH_PAGE_SIZE) (NOLOAD) :
  {
    * (.lockbits_in_mainflash .lockbits_in_mainflash.*);
  }>flash
  OUR_BEGIN = (LOCKBITS_IN_MAINFLASH_SIZE == 0) ? 0 : ADDR(.lockbits_in_mainflash);
  PROVIDE(__LOCKBITS_IN_MAINFLASH__begin = OUR_BEGIN);
  PROVIDE(__LOCKBITS_IN_MAINFLASH__end = OUR_BEGIN + SIZEOF(.lockbits_in_mainflash));
  PROVIDE(__LOCKBITS_IN_MAINFLASH__size = SIZEOF(.lockbits_in_mainflash));

  ASSERT ( __LOCKBITS_IN_MAINFLASH__size == LOCKBITS_IN_MAINFLASH_SIZE, "

======================================================================
======== LINKER ERROR: LOCKBITS_IN_MAINFLASH_SIZE is misconfigured
======================================================================
" )


  /* Sanity check */
  ASSERT (. <= MFB_TOP + 1 , "

======================================================================
======== LINKER ERROR: Not enough flash
======================================================================
" )

  /* --------------------------------------------------------------------*/

  . = FIB_BOTTOM;
  .fat . (NOLOAD) :
  {
    PROVIDE(__FAT__begin = .);
    KEEP ( *(.fat .fat.*) );
    PROVIDE(__FAT__end = .);
  }
  PROVIDE(__FAT__size = SIZEOF(.fat));

  /* --------------------------------------------------------------------*/

  . = RAM_BOTTOM;

  .resetinfo RAM_BOTTOM (NOLOAD) :
  {
    PROVIDE(__RESETINFO__begin = .);
    * (.resetinfo .resetinfo.*);
    PROVIDE(__RESETINFO__end = .);
  }>ram
  PROVIDE(__RESETINFO__size = SIZEOF(.resetinfo));

  /* EFR32xG22 may zero out the high portion of RAM after reset, meaning that
     data we wish to preserve across resets should be in the lower addresses.
     Since we are already preserving the reset info block, it makes sense to
     place the (new) __NO_INIT__ section adjacent to it. For legacy purposes, we
     are keeping the old section where it was and will select between the two in
     C code.
  */
  .noinitnew . (NOLOAD) :
  {
    * (.noinitnew .noinitnew.*);
  }>ram
  OUR_BEGIN = (SIZEOF(.noinitnew) == 0) ? 0 : ADDR(.noinitnew);
  PROVIDE(__NO_INIT_NEW__begin = OUR_BEGIN);
  PROVIDE(__NO_INIT_NEW__end = OUR_BEGIN + SIZEOF(.noinitnew));
  PROVIDE(__NO_INIT_NEW__size = SIZEOF(.noinitnew));

  .emheap ALIGN(8) (NOLOAD) :
  {
    PROVIDE(__EMHEAP__begin = .);
    KEEP (* (.emheap .emheap.*) );
    PROVIDE(__EMHEAP__end = .);
  }>ram
  PROVIDE(__EMHEAP__size = SIZEOF(.emheap));

  .guard_region ALIGN(0x20) (NOLOAD) :
  {
    PROVIDE(__GUARD_REGION__begin = .);
    KEEP ( *(.guard_region .guard_region.*) );
    PROVIDE(__GUARD_REGION__end = .);
  }>ram
  PROVIDE(__GUARD_REGION__size = SIZEOF(.guard_region));

  .cstack ALIGN(8) (NOLOAD):
  {
    PROVIDE(__CSTACK__begin = .);
    KEEP( *(.cstack .cstack.*) );
    PROVIDE(__StackTop = .);
    PROVIDE(__stack = __StackTop);
    PROVIDE(__CSTACK__end = .);
    __StackLimit = __CSTACK__end;
  }>ram
  PROVIDE(__CSTACK__size = SIZEOF(.cstack));

  .data . : AT(__DATA_INIT__begin)
  {
    PROVIDE(__data_start__ = .);
    PROVIDE(__DATA__begin = .);
    . = ALIGN(4);
    PROVIDE (__ram_func_section_start = .);
    * (.ram .ram.*);
    PROVIDE (__ram_func_section_end = .);

    /* preinit data */
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP(*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);

    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    PROVIDE_HIDDEN (__init_array_end = .);

    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array))
    PROVIDE_HIDDEN (__fini_array_end = .);

    * (.data .data.*);
    . = ALIGN(2);  /* Align each segment to a Flash word boundary */
    PROVIDE(__data_end__ = .);
    PROVIDE(__DATA__end = .);
  }>ram
  PROVIDE(__DATA__size = SIZEOF(.data));

  .memp . (NOLOAD) :
  {
    PROVIDE(_smemp = .);
    KEEP( * (.bss.memp*) );
    KEEP( *memp.o(.bss) );
  }>ram
  PROVIDE(_memp_size = SIZEOF(.memp));

  .bss . (NOLOAD) :
  {
    PROVIDE(__BSS__begin = .);
    PROVIDE(__bss_start__ = .);
    * (.bss .bss.*);
    * (COMMON);
    * (.platform .platform.*);
    PROVIDE(__bss_end__ = .);
    PROVIDE(__BSS__end = .);
  }>ram
  PROVIDE(__BSS__size = SIZEOF(.bss));

  /* Legacy __NO_INIT__ section. See comment above .noinitnew. */
  .noinitlegacy . (NOLOAD) :
  {
    * (.noinitlegacy .noinitlegacy.*);
  }>ram
  OUR_BEGIN = (SIZEOF(.noinitlegacy) == 0) ? 0 : ADDR(.noinitlegacy);
  PROVIDE(__NO_INIT_LEGACY__begin = OUR_BEGIN);
  PROVIDE(__NO_INIT_LEGACY__end = OUR_BEGIN + SIZEOF(.noinitlegacy));
  PROVIDE(__NO_INIT_LEGACY__size = SIZEOF(.noinitlegacy));

  .heap . (COPY) :
  {
    __HeapBase = .;
    __end__ = .;
    end = __end__;
    _end = __end__;
    KEEP(*(.heap*))
    __HeapLimit = .;
  }>ram

  .debugChannel . (NOLOAD) :
  {
    * (DEBUG_CHANNEL DEBUG_CHANNEL.*)
  }>ram
  OUR_BEGIN = (SIZEOF(.debugChannel) == 0) ? 0 : ADDR(.debugChannel);
  PROVIDE(__DEBUG_CHANNEL__begin = OUR_BEGIN);
  PROVIDE(__DEBUG_CHANNEL__end = OUR_BEGIN + SIZEOF(.debugChannel));
  PROVIDE(__DEBUG_CHANNEL__size = SIZEOF(.debugChannel));

  RAM_GUARD = RAM_TOP - UNUSED_RAM_SIZE ;

  ASSERT ( . < RAM_GUARD + 1, "

======================================================================
======== LINKER ERROR: Not enough RAM
======================================================================
" )

  . = RAM_TOP - UNUSED_RAM_SIZE;
  UNRETAINED_RAM (NOLOAD) :
  {
    PROVIDE(__UNRETAINED_RAM__begin = .);
    * (UNRETAINED_RAM UNRETAINED_RAM.*)
    PROVIDE(__UNRETAINED_RAM__end = .);
  }>ram
  PROVIDE(__UNRETAINED_RAM__size = SIZEOF(UNRETAINED_RAM));

  ASSERT ( . < RAM_TOP + 1 , "

======================================================================
======== LINKER ERROR: Not enough RAM (Unretained)
======================================================================
" )

  __RAM__end = .;
  PROVIDE(end = .);
  PROVIDE(_end = .);
}
