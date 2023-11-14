TCC?=cc
TCCFLAGS?=-lfl -I/opt/homebrew/opt/flex/include -L/opt/homebrew/opt/flex/lib
FLEX?=flex
BISON?=bison

FLEX_OUT=lex.yy.c
BISON_OUT=dtsl.tab.c
BISON_HEADER=dtsl.tab.h

SOURCES=$(FLEX_OUT) $(BISON_OUT) # main.c

TARGET?=dtsl

all: $(TARGET)

clean:
	rm -f $(TARGET) $(FLEX_OUT) $(BISON_OUT) $(BISON_HEADER)

$(FLEX_OUT): dtsl.l
	$(FLEX) -o $@ $^

$(BISON_OUT): dtsl.y
	$(BISON) --header=$(BISON_HEADER) -o $@ $^

$(TARGET): $(SOURCES)
	$(TCC) $(TCCFLAGS) $^ -o $@

