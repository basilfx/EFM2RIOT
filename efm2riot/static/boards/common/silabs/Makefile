MODULE = boards_common_silabs

ifneq (,$(filter aem,$(USEMODULE)))
  DIRS += drivers/aem
endif

ifneq (,$(filter bc,$(USEMODULE)))
  DIRS += drivers/bc
endif

ifneq (,$(filter pic,$(USEMODULE)))
  DIRS += drivers/pic
endif

include $(RIOTBASE)/Makefile.base
