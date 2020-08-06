# Change Log

All notable changes to the bootloader will be documented in this file. The
version number given in the Change Log is on the format `major`.`minor`.`patch`.

## 1.10.2 - 2020-02

### Changed
 - The size of ParserContext_t for Series-2 devices has been increased to 524 bytes
   to support certificate based authentication of GBL images.
 - Added certificate support for secure boot and GBL image parser for EFR32xG22.
 - Added a function `bootloader_getCertificateVersion` for reading certificate version of the bootloader on Series-2 devices.
 - BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE is added to btl_interface_storage.h, which indicates the size re-
   quired to store verification context.

## 1.10.1 - 2020-01

### Changed
 - The RMU reset level for soft resets is configured to be EXTENDED on Series-1 devices.

## 1.10.0 - 2019-12

### Added
 - Initial support for EFR32xG22 has been added in this release.
 - Added an AppBuilder plugin option APPLICATION_VERIFICATION_SKIP_EM4_RST to skip
   verification of the application only if the device has been to EM4.
 - Added certificate support for secure boot and GBL image parser for EFR32xG21.
 - Added first stage binaries for xG13 and xG14 devices that works with the second stage bootloader placed in the main flash.
 - Added EZSP GPIO plugin.
 - Added EUART driver.

### Changed
 - The size of ParserContext_t for EFR32xG21 has been increased to 524 bytes to support
   certificate based authentication of GBL images.

## 1.9.1 - 2019-07

### Changed
 - On devices with support for secure key storage, the ECDSA signature verification
   of the application is by default performed by using this key. If the public key
   is not stored in secure storage, Gecko Bootloader will fall back to the public key
   stored in the manufacturing token space. This fallback can be disabled by setting
   the AppBuilder plugin option BOOTLOADER_FALLBACK_LEGACY_KEY to false.

## 1.9.0 - 2019-06

### Added
 - The communication bootloader checks the version of the upgrade image
   before starting the bootloader upgrade process.
 - Added a new internal storage bootloader sample application
   bootloader-storage-internal-single-2048k for devices with 2 MB internal flash.
 - Added compability check of the struct ApplicationProperties_t using
   major APPLICATION_PROPERTIES_VERSION.
 - The postbuild script of the bootloader is updated to generate CRC’ed version
   of the combined bootloader for Series-1 devices.

## 1.8.2 - 2019-02

### Added
 - Added support for successive flash lock of the application and bootloader area
   on Series-2 devices.

### Changed
 - When performing bootloader upgrade, the application survives if the location
   where the application resides does not overlap with the bootloader upgrade
   area, which is fixed on Series 1 devices and is configurable on Series 2 devices.
 - Before the bootloader upgrade process starts, CRC32 checksum on the bootloader
   upgrade image is verified.

### Fixed
  - Fixed an issue with resuming an aborted upgrade in the legacy EBLv2 parser.

## 1.8.0 - 2018-12

### Added
 - Initial support for EFR32xG21 has been added in this release.
 - The standalone EZSP-SPI bootloader now supports bootloader upgrade.

### Changed
 - Microsecond delay is modified to work more robustly. The microsecond delay
   function supports different HFRCO bands. The maximum error of the microsecond
   delay is reduced to be less than 20 %.
 - The default SPI frequency is increased to 6400000.
 - Improved ECDSA signature check

### Removed
 - The enumeration value `BootloaderType_t::NONE` that was deprecated in 1.2.0
   has been removed.

## 1.7.0 - 2018-09

### Added
 - The GBL image parser will call a callback when an Application Tag is received.
   If the return value of this callback is `false`, the parser will abort, and
   reject the upgrade image. The default implementation of the callback does not
   perform any validation, and accepts all images.
 - A simple implementation of the GBL application upgrade callback has been added,
   checking the application version and product ID.
 - An option to time out and reset back into the application has been added to
   the XMODEM communication plugin. The BTL_XMODEM_IDLE_TIMEOUT AppBuilder plugin
   option can be used to configure an optional timeout value in seconds. If the
   host hasn't initiated communication with the bootloader within this window,
   the bootloader will abort the firmware upgrade process and return to the
   application.

## 1.6.0 - 2018-05

### Added
 - The GBL parser now supports LZMA compressed programming tags. Decompression
   is only supported when running in the context of the bootloader, not using
   the application interface. Verification of a GBL file containing compressed
   tags is supported in both modes of operation.
 - A version of the GBL parser without support for AES encrypted files has been
   added. This version of the parser can be used to save flash space if
   upgrade image encryption is not required.
 - A version of the storage library without support for multiple storage slots
   has been added. This version of the storage library can be used to save flash
   space if only a single storage slot is used.

### Changed
 - CRC32 is now performed using the GPCRC peripheral rather than a software
   implementation. This should increase performance.

### Fixed
 - When using HFXO as the clock source for HFPERCLK, the SPI driver did not
   calculate the correct clock divider, causing an incorrect baud rate.
 - Data in GBL Metadata tags was not correctly returned in the metadata
   callback.
 - The first stage bootloader could fail to apply a bootloader upgrade if
   power was lost during the upgrade. The window for failure opened when the
   first page of the main bootloader was erased, and closed when the new main
   bootloader was completely written. The first stage bootloader is now more
   resilient to power loss.

## 1.5.0 - 2018-02

### Added
 - Initial support for EFM32TG11 has been added in this release.

### Changed
 - All memory accesses in the Gecko bootloader are now aligned.

## 1.4.1 - 2017-12

### Added

 - Added more prebuilt bootloader binaries for EFR32 in default configuration.

## 1.4.0 - 2017-09

### Added
 - Support for EFR32xG14, EFM32PG1, EFM32PG12, EFM32JG1, EFM32JG12 and
   EFM32GG11 has been added in this release.

### Changed
 - The Gecko bootloader now uses HAL Configuration headers for peripheral
   configuration, rather than its own set of #defines. Support for the
   Hardware Configurator has also been integrated into the Application Builder
   for the Gecko bootloader. This allows for graphical configuration.
 - All cryptographic operations using the CRYPTO hardware accelerator protect
   critical operations using critical sections, allowing preemption of CRYPTO
   operations when using the application interface.
 - The `bootloader_getImageInfo` function now returns an error code if the
   storage slot is invalid or empty.

### Fixed
 - When verifying an LZ4 compressed image in storage using the application
   interface, the bootloader could erroneously touch application RAM outside
   the allocated context.
 - An issue preventing bootloader upgrades from working when applied in a GBL
   file together with a compressed application image has been resolved.

## 1.3.0 - 2017-07

### Changed
 - The GBL and EBL upgrade image parsing support has been split out from the
   core bootloader library `libbootloader` into two libraries `libparser` and
   `libparser-eblv2`. The former supports GBL only, the latter supports both
   GBL and the legacy EBL format. Selection of which library to use is done
   by selecting the "Image Parser" or "Image Parser with legacy EBL support"
   plugin in AppBuilder. Users who previously enabled EBL support by checking
   "Allow legacy format" in the Image Parser plugin, should use the new
   "Image Parser with legacy EBL support" plugin instead.

### Fixed
 - The image parser for GBL files could fail to write data to address 0x8004
   if the word at that address started with 0xFF.
 - The LZ4 decompressor for compressed GBL files could in rare cases repeat
   the wrong byte when decompressing certain repeated patterns.

## 1.2.0 - 2017-06

### Added
 - The GBL parser now supports LZ4 compressed programming tags. Decompression
   is only supported when running in the context of the bootloader, not using
   the application interface. Verification of a GBL file containing compressed
   tags is supported in both modes of operation.

### Changed
 - The `parser_parse` function takes a flags argument, which is used to signal
   whether tags such as the LZ4 compressed tag should be parsed (decompressed)
   or skipped over. If `flags = PARSER_FLAG_PARSE_CUSTOM_TAGS`, custom tags will
   be fully parsed. If `flags = 0`, custom tags will be treated as binary blobs
   that are passed over.
 - Enumeration values with too generic names have been renamed to prevent naming
   collisions with other software components. In `BootloaderType_t`, `NONE` has
   been renamed `NO_BOOTLOADER`. In `BootloaderStorageType_t`, `CUSTOM` has been
   renamed `CUSTOM_STORAGE`.
 - Main bootloader main function has been refactored to allow running a
   bootloader that supports both storage and communication. When both a storage
   and a communication plugin is enabled, the storage plugin will run first. If
   it reports anything other than a firmware upgrade success, the communication
   plugin will run.

### Deprecated
 - The enumeration values `BootloaderType_t::NONE` and
   `BootloaderStorageType_t::CUSTOM` are deprecated.

### Fixed
 - A false verification failure using the `bootloader_verifyApplication`
   function for CRC-checksummed application images that did not start at the
   beginning of the application area in main flash has been fixed.
 - Prebuilt sample bootloader binaries were previously added to all
   bootloader projects in Simplicity Studio. These have now been moved to a
   different location to avoid cluttering up the projects.
 - Default enable pin for UART on BRD4165B changed from PA5 to PA4 to reflect
   actual board configuration.

## 1.1.0 - 2017-06

### Added
 - The `bootloader_verifyApplication` function now supports verifying all
   applications. If secure boot is enforced, the function will only return
   `true` if the cryptographic signature of the application is valid. Else, the
   application is verified according to the signature type present in the
   application ApplicationProperties_t structure.
 - The SPI flash storage plugin now supports graphical configuration of SPI
   flash write protect and hold pins. Configuring these pins is required for the
   bootloader to successfully communicate with the stacked flash in the
   EFR32MG1[BP][67]32 SiPs.

### Changed
 - The internal flash write routine `flash_writeBuffer` now returns `true`
   if given a zero-length buffer to write. This improves the backwards
   compatibility of the behavior of the bootloader interface for internal
   storage bootloaders.
 - The added capability of `bootloader_verifyApplication` means that it will now
   return `true` instead of `false` when verifying an unsigned application when
   secure boot is _not_ enabled.

### Fixed
 - The Bluetooth in-place OTA bootloader sample configuration was erroneously
   not visible for EFR32MG1 in Simplicity Studio
 - The image parser for legacy EBL files would silently fail to completely apply
   upgrade images containing zero-length ERASEPROG tags, which Simplicity
   Commander sometimes could output (sequences of "FD03000400000000" near the end of
   the EBL file). If zero-length ERASEPROG tags were present, data would not be
   flashed to the word starting at address 0x8004.
 - The image parser for legacy EBL files would fail to indicate that the image
   contained an application upgrade, causing the storage plugin to abort
   the upgrade process, even though the image was valid.

## 1.0.0 - 2017-03
### Added
 - Initial release of Gecko Bootloader

## Change Type Descriptions
The following change types are used in this document to describe changes
### Added
- New features added to this release
### Changed
- Changes in existing functionality
### Deprecated
- Functionality that has been deprecated, and may be removed in a future release
### Removed
- Functionality that was removed in this release
### Fixed
- Bugs that were fixed in this release
### Security
- Security critical changes and fixes that should be highlighted in this release
