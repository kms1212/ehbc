

#define DEFINE_BUSOPS_BEGIN(bus) \
    struct bus##_operations { \
        error_t     (*init)(); \
        error_t     (*deinit)(); \
        error_t     (*read)(); \
        error_t     (*write)(); \
        error_t     (*transmit)(); \
        error_t     (*receive)(); \
        error_t     (*cfgread)(); \
        error_t     (*cfgwrite)();

#define DEFINE_BUS_BEGIN(bus) \
    struct bus { \
        enum bus_status bstat; \
        struct bus##_operations* bops;

#define DEFINE_BUS_END \
    };
