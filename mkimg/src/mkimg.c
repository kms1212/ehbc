#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <getopt.h>

#include <sys/mount.h>

#include <cjson/cJSON.h>

#define strtype_t           uint16_t
#define STRTYPE_ERROR       0x0000
#define STRTYPE_ASCII       0x0001
#define STRTYPE_BINARY      0x0002
#define STRTYPE_OCTAL       0x0003
#define STRTYPE_HEX         0x0004
#define STRTYPE_PROPERTY    0x0005
#define STRTYPE_MACRO       0x0006
#define STR_OPT_AVAILABLE   0x8000


static char* infile;
static char outfile[256] = "output";

char operation = 'p';

static const struct option lopts[] = {
    // name         has_arg flag        val
    { "help",       0,      &operation, 'h' },
    { "out",        1,      0,          'o' },
    { NULL,         0,      0,          0   }
};

static int isbin(char c) {
    return (c < '0' || c > '1') ? 0 : 1;
}

static int isoct(char c) {
    return (c < '0' || c > '7') ? 0 : 1;
}

static int ishex(char c) {
    return ((c < '0' || c > '9') && (c < 'A' || c > 'F') && (c < 'a' || c > 'f')) ? 0 : 1;
}

static size_t getvalendidx(char* str, size_t len, int quote) {
    size_t valueend;
    for (valueend = 2; (str[valueend] != '/' && valueend < len); valueend++) {}
    return quote ? valueend - 1 : valueend;
}

static int getvaloption(char* str, size_t len, uint16_t* optlist) {
    size_t optstart = getvalendidx(str, len, FALSE) + 2;
    char optkwd[16] = "";

    for (size_t i = optstart; i < len;) {
        int kwdidx = 0;
        for (; (str[i] != ',' && i < len && kwdidx < 15); i++)
            optkwd[kwdidx] = str[i];
        optkwd[kwdidx + 1] = 0;

        
    }
}


static strtype_t getstrtype(char* str, size_t len) {
    if (len < 3)
        return STRTYPE_ERROR;

    size_t    valueend = 0;
    strtype_t tempresult = STRTYPE_ERROR;

    switch (str[0]) {
    case 'a': {  // format: a'<data>'[/<options>]
        size_t quoteclose = memchr(str + 2, '\'', len);
        if (str[1] == '\'' && quoteclose != NULL) {
            quoteclose -= (size_t)str;
            tempresult = STRTYPE_ASCII;
            valueend = quoteclose + 1;
        } else {
            return STRTYPE_ERROR;
        }
        break;
    }
    case '0': {  // format: 0{b|o|x}<data>[/<options>]
        switch (str[1]) {
        case 'b':
            for (valueend = 2; (str[valueend] != '/' && valueend < len); valueend++)
                if (!isbin(str[valueend]))
                    return STRTYPE_ERROR;
            tempresult = STRTYPE_BINARY;
            break;
        case 'o':
            for (valueend = 2; (str[valueend] != '/' && valueend < len); valueend++)
                if (!isoct(str[valueend]))
                    return STRTYPE_ERROR;
            tempresult = STRTYPE_OCTAL;
            break;
        case 'x':
            for (valueend = 2; (str[valueend] != '/' && valueend < len); valueend++)
                if (!ishex(str[valueend]))
                    return STRTYPE_ERROR;
            tempresult = STRTYPE_HEX;
            break;
        default:
            return STRTYPE_ERROR;
        }
        break;
    }
    case 'b': {  // format: b'<data>'[/<options>]
        size_t quoteclose = memchr(str + 2, '\'', len);
        if (str[1] == '\'' && quoteclose != NULL) {
            quoteclose -= (size_t)str;
            for (valueend = 2; valueend < quoteclose; valueend++)
                if (!isbin(str[valueend]))
                    return STRTYPE_ERROR;
            tempresult = STRTYPE_BINARY;
            valueend++;
            break;
        } else {
            return STRTYPE_ERROR;
        }
        break;
    }
    case 'o': {  // format: o'<data>'[/<options>]
        size_t quoteclose = memchr(str + 2, '\'', len);
        if (str[1] == '\'' && quoteclose != NULL) {
            quoteclose -= (size_t)str;
            for (valueend = 2; valueend < quoteclose; valueend++)
                if (!isoct(str[valueend]))
                    return STRTYPE_ERROR;
            tempresult = STRTYPE_OCTAL;
            valueend++;
            break;
        } else {
            return STRTYPE_ERROR;
        }
        break;
    }
    case 'x': {  // format: x'<data>'[/<options>]
        size_t quoteclose = memchr(str + 2, '\'', len);
        if (str[1] == '\'' && quoteclose != NULL) {
            quoteclose -= (size_t)str;
            for (valueend = 2; valueend < quoteclose; valueend++)
                if (!ishex(str[valueend]))
                    return STRTYPE_ERROR;
            tempresult = STRTYPE_HEX;
            valueend++;
            break;
        } else {
            return STRTYPE_ERROR;
        }
        break;
    }
    case 'p': {  // format: p'property'[/<options>]
        size_t quoteclose = memchr(str + 2, '\'', len);
        if (str[1] == '\'' && quoteclose != NULL) {
            quoteclose -= (size_t)str;
            tempresult = STRTYPE_PROPERTY;
            valueend = quoteclose + 1;
            break;
        } else {
            return STRTYPE_ERROR;
        }
        break;
    }
    case '$': {  // format: $<macro>[/<options>]
        size_t macroend = memchr(str + 1, '/', len);
        valueend = macroend == NULL ? len : macroend - (size_t)str;
        tempresult = STRTYPE_MACRO;
        break;
    }
    default:
        return STRTYPE_ERROR;
    }

    if (len > valueend + 1) {
        if (str[valueend] == '/')
            return tempresult | STR_OPT_AVAILABLE;
        else
            return STRTYPE_ERROR;
    } else {
        return tempresult;
    }
}

static size_t getstrintvalue(char* str, size_t len, uint64_t* value) {
    strtype_t strtype = getstrtype(str, len);
    switch(strtype) {
        case STRTYPE_BINARY:
        case STRTYPE_OCTAL:
        case STRTYPE_HEX:
            switch (str[0]) {
            case '0': {  // format: 0{b|o|x}<data>[/<options>]
                switch (str[1]) {
                case 'b': {
                    size_t valueend = getvalendidx(str, len, FALSE);

                    
                    break;
                }
                case 'o':
                    for (valueend = 2; (str[valueend] != '/' && valueend < len); valueend++)
                        if (!isoct(str[valueend]))
                            return STRTYPE_ERROR;
                    tempresult = STRTYPE_OCTAL;
                    break;
                case 'x':
                    for (valueend = 2; (str[valueend] != '/' && valueend < len); valueend++)
                        if (!ishex(str[valueend]))
                            return STRTYPE_ERROR;
                    tempresult = STRTYPE_HEX;
                    break;
                default:
                    return STRTYPE_ERROR;
                }
                break;
            }
            case 'b': {  // format: b'<data>'[/<options>]
                size_t quoteclose = memchr(str + 2, '\'', len);
                if (str[1] == '\'' && quoteclose != NULL) {
                    quoteclose -= (size_t)str;
                    for (valueend = 2; valueend < quoteclose; valueend++)
                        if (!isbin(str[valueend]))
                            return STRTYPE_ERROR;
                    tempresult = STRTYPE_BINARY;
                    valueend++;
                    break;
                } else {
                    return STRTYPE_ERROR;
                }
                break;
            }
            case 'o': {  // format: o'<data>'[/<options>]
                size_t quoteclose = memchr(str + 2, '\'', len);
                if (str[1] == '\'' && quoteclose != NULL) {
                    quoteclose -= (size_t)str;
                    for (valueend = 2; valueend < quoteclose; valueend++)
                        if (!isoct(str[valueend]))
                            return STRTYPE_ERROR;
                    tempresult = STRTYPE_OCTAL;
                    valueend++;
                    break;
                } else {
                    return STRTYPE_ERROR;
                }
                break;
            }
            case 'x': {  // format: x'<data>'[/<options>]
                size_t quoteclose = memchr(str + 2, '\'', len);
                if (str[1] == '\'' && quoteclose != NULL) {
                    quoteclose -= (size_t)str;
                    for (valueend = 2; valueend < quoteclose; valueend++)
                        if (!ishex(str[valueend]))
                            return STRTYPE_ERROR;
                    tempresult = STRTYPE_HEX;
                    valueend++;
                    break;
                } else {
                    return STRTYPE_ERROR;
                }
                break;
            }
            }
            break;
        default:
            return 0;
    }
}

static void usage(const char* argv0, int detailed) {
    printf("Usage: %s [options] [file] [-o/--out outfile]\n", argv0);
    if (detailed) {
        puts(
            "  -h  --help          Print this message\n"
            "  -o  --out           Override output file name\n");
    }
}

static int process_args(int argc, char* argv[]) {
    while (1) {
        int c;
        c = getopt_long(argc, argv, "o:h", lopts, NULL);
        if (c == -1)
            break;

        switch (c) {
        case 'o': {
            int len = strnlen(optarg, 256);
            strncpy(outfile, optarg, len);
            outfile[len] = 0;
            break;
        }
        case 'h': {
            usage(argv[0], TRUE);
            return 0;
        }
        default: {
            printf("%s: illegal option -- %c\n", argv[0], c);
            usage(argv[0], FALSE);
            return 0;
        }
        }
    }
    for (int i = optind; i < argc; i++) {
        if (i == optind) {
            infile = argv[i];
        } else {
            printf("%s: illegal non-option argument -- %s\n", argv[0], argv[i]);
            usage(argv[0], FALSE);
            return 1;
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    int err = process_args(argc, argv);

    if (err) return err;

    if (operation == 'p') {
        FILE* srcfp = fopen(infile, "r");
        fseek(srcfp, 0, SEEK_END);
        int srclen = ftell(srcfp);
        fseek(srcfp, 0, SEEK_SET);

        char* filebuf = (char*)malloc(srclen);
        fread(filebuf, srclen, 1, srcfp);
        free(filebuf);


        cJSON* srcjson = cJSON_ParseWithLength(filebuf, srclen);

        cJSON* rootobj = cJSON_GetObjectItemCaseSensitive(srcjson, "filename");
        if (cJSON_IsString(rootobj) && (rootobj->valuestring != NULL)) {
            
        }

        cJSON_Delete(srcjson);
    }

    return 0;
}
