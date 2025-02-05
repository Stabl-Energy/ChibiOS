*****************************************************************************
*** Files Organization                                                    ***
*****************************************************************************

--{root}                        - ChibiOS directory.
  +--readme.txt                 - This file.
  +--documentation.html         - Shortcut to the web documentation page.
  +--license.txt                - GPL license text.
  +--demos/                     - Demo projects, one directory per platform.
  +--docs/                      - Documentation.
  |  +--common/                 - Documentation common build resources.
  |  +--hal/                    - Builders for HAL.
  |  +--nil/                    - Builders for NIL.
  |  +--rt/                     - Builders for RT.
  +--ext/                       - External libraries, not part of ChibiOS.
  +--os/                        - ChibiOS components.
  |  +--common/                 - Shared OS modules.
  |  |  +--abstractions/        - API emulator wrappers.
  |  |  |  +--cmsis_os/         - CMSIS OS emulation layer for RT.
  |  |  |  +--nasa_osal/        - NASA Operating System Abstraction Layer.
  |  |  +--ext/                 - Vendor files used by the OS.
  |  |  +--ports/               - RTOS ports usable by both RT and NIL.
  |  |  +--startup/             - Startup support.
  |  +--ex/                     - EX component.
  |  |  +--dox/                 - EX documentation resources.
  |  |  +--include/             - EX header files.
  |  |  +--devices /            - EX complex drivers.
  |  +--hal/                    - HAL component.
  |  |  +--boards/              - HAL board support files.
  |  |  +--dox/                 - HAL documentation resources.
  |  |  +--include/             - HAL high level headers.
  |  |  +--lib/                 - HAL libraries.
  |  |  |  +--complex/          - HAL collection of complex drivers.
  |  |  |  |  +--mfs/           - HAL managed flash storage driver.
  |  |  |  |  +--serial_nor/    - HAL managed flash storage driver.
  |  |  |  +--fallback/         - HAL fall back software drivers.
  |  |  |  +--peripherals/      - HAL peripherals interfaces.
  |  |  |  +--streams/          - HAL streams.
  |  |  +--osal/                - HAL OSAL implementations.
  |  |  |  +--lib/              - HAL OSAL common modules.
  |  |  +--src/                 - HAL high level source.
  |  |  +--ports/               - HAL ports.
  |  |  +--templates/           - HAL driver template files.
  |  |     +--osal/             - HAL OSAL templates.
  |  +--oslib/                  - RTOS modules usable by both RT and NIL.
  |  |  +--include/             - OSLIB high level headers.
  |  |  +--src/                 - OSLIB high level source.
  |  |  +--templates/           - OSLIB configuration template files.
  |  +--nil/                    - NIL RTOS component.
  |  |  +--dox/                 - NIL documentation resources.
  |  |  +--include/             - NIL high level headers.
  |  |  +--src/                 - NIL high level source.
  |  |  +--templates/           - NIL configuration template files.
  |  +--rt/                     - RT RTOS component.
  |  |  +--dox/                 - RT documentation resources.
  |  |  +--include/             - RT high level headers.
  |  |  +--src/                 - RT high level source.
  |  |  +--templates/           - RT configuration template files.
  |  +--various/                - Various portable support files.
  +--test/                      - Kernel test suite source code.
  |  +--lib/                    - Portable test engine.
  |  +--hal/                    - HAL test suites.
  |  |  +--testbuild/           - HAL build test and MISRA check.
  |  +--nil/                    - NIL test suites.
  |  |  +--testbuild/           - NIL build test and MISRA check.
  |  +--rt/                     - RT test suites.
  |  |  +--testbuild/           - RT build test and MISRA check.
  |  |  +--coverage/            - RT code coverage project.
  +--testex/                    - EX integration test demos.
  +--testhal/                   - HAL integration test demos.

*****************************************************************************
*** Releases and Change Log                                               ***
*****************************************************************************

*** Next ***
- NEW: Added a new CH_CFG_HARDENING_LEVEL option to RT.
- NEW: Added a chXXXDispose() function to all objects in NIL.
- NEW: Added a chXXXDispose() function to all objects in RT.
- NEW: Added VFS-related commands to the shell, disabled by default.
- NEW: Added a new VFS subsystem (Virtual File System), it allows to assemble
       trees of files from multiple "File System Drivers" into a single tree
       and access it as a whole.
- NEW: Added MEM_NATURAL_ALIGN macro to RT and NIL.
- NEW: Added static initializer for virtual timers in RT.
- NEW: Added new function chHeapIntegrityCheck().
- NEW: Added EFL driver implementation for STM32G4xx.
- NEW: Function chCoreGetStatusX() changed to return a memory region object
       instead of a simple size.
- NEW: RT and NIL upgraded to support the enhanced OSLIB.
- NEW: Memory areas/pointers checker functions added to OSLIB.
- NEW: STM32G0B1 USBv2 driver.
- NEW: USBv1 driver optimization and removal of a potential race condition
       (not demonstrated).
- NEW: Added elfAcquireBus()/eflReleaseBus() functions to EFL driver.
- NEW: Increased stacks size in RT test suite from 128 to 192. added an
       option to override the stack size by defining THREADS_STACK_SIZE
       in the makefile.
- NEW: Added STM32L073RZ-Nucleo64 to USB-CDC "multi" demo. Removed old demo.
- NEW: Added an STM32 WDG "multi" demo. Removed all old WDG demos.
- NEW: Added option to copy vectors in RAM on GCC startup for ARMv6-M,
       ARMv7-M and ARMv8-M-ML.
- NEW: On STM32WBxx added a check on STM32_LSI_ENABLE required by IWDG.
- NEW: Added SPIv2 support also to STM32WB and STM32WL.
- FIX: Fixed PWR_CR2_USV not set in STM32L4+ mcuconf.h file (bug #1207)
       (backported to 21.11.1).
- FIX: Fixed USB not enabled on STM32F103x6 (bug #1206)
       (backported to 20.3.5)(backported to 21.11.1).
- FIX: Fixed RT test suite build fails when CH_CFG_USE_TIMESTAMP is FALSE
       (bug #1205)(backported to 21.11.1).
- FIX: Fixed wrong number of CAN filters for STM32L496/9A6 (bug #1204)
       (backported to 20.3.5)(backported to 21.11.1).
- FIX: Fixed DMA stream not disabled in STM32 QUADSPIv1 driver (bug #1203)
       (backported to 20.3.5)(backported to 21.11.1).
- FIX: Fixed I2C4 DMA streams for STM32L496 (bug #1202)
       (backported to 20.3.5)(backported to 21.11.1).
- FIX: Fixed STM32_SDMMC2_NUMBER on STM32H7 (bug #1201)
       (backported to 20.3.5)(backported to 21.11.1).
- FIX: Fixed STM32G0B1 demo application hangs debuggers (bug #1200)
       (backported to 21.11.1).
