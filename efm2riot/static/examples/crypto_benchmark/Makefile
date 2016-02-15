# name of your application
APPLICATION = hwaes_benchmark

# If no BOARD is found in the environment, use this default:
BOARD ?= slstk3401a

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Include packages
USEMODULE += crypto
USEMODULE += cipher_modes

# Required features
FEATURES_REQUIRED = periph_rtt

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP -DCRYPTO_AES

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
