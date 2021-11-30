ALLINC		+= 	$(CHIBIOS)/os/various/fault_handlers		\
				$(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/utils/
ALLCSRC 	+= 	$(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/utils/fault_handlers_v7m.c
ALLXASMSRC 	+= 	$(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/utils/hardfault_handler_v7m.S
