TCC?=cc
TCCFLAGS?=

SOURCES=main.c

TARGET?=binsplit

all: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SOURCES)
	$(TCC) $^ -o $@
