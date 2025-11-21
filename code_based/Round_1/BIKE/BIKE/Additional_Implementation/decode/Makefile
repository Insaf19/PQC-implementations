include ../inc.mk

SSRC = converts.S  
ifdef CONSTANT_TIME
    SSRC += secure_decode${SUF}.S
else
    SSRC += decode${SUF}.S 
endif
CSRC = decode.c

include ../rules.mk