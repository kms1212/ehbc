#include "types.h"
#include "utils.h"

#define true            1
#define false           0

#define PKT_HEADER      0x02
#define PKT_FOOTER      0x03

// #define PKT_ENABLE_FOOTER

#define PKT_NODATA      0xC0

#define PKT_CMD_IDENT   0x00
#define PKT_CMD_MODE    0x01

#define PKT_CMD_READ    0x10
#define PKT_CMD_WRITE   0x11
#define PKT_CMD_STREAM  0x12

#define PKT_CMD_ACK     0x3C | PKT_NODATA
#define PKT_CMD_RESEND  0x3D | PKT_NODATA
#define PKT_CMD_ERR     0x3E | PKT_NODATA
#define PKT_CMD_DETECT  0x3F | PKT_NODATA

// Packet Format : DATA1[SIZE1], DATA2[SIZE2], {OPTIONAL_DATA[1]}, ...
//
// HEADER   : Packet header
// CMD      : Packet command
// LEN      : Packet command data length in byte
// DATA     : Packet command data
// CHKSUM   : Checksum of every 8-byte block of command data
// FOOTER   : Optional packet footer
//
// Packet with command data:
// HEADER[1], CMD[1], LEN[1], DATA[LEN], CHKSUM[ceil(LEN/8)], {FOOTER[1]}
//
// Packet without command data:
// HEADER[1], CMD[1], {FOOTER[1]}

/// @brief Checksum function (8B Maximum : 1B)
/// @param data Data buffer
/// @param sz   Block size
/// @return Checksum of the given data block
inline uint8_t pkt_chksum(const uint8_t* data, size_t sz) {
    return 0;
}

/// @brief Calculate packet size
/// @param cmd  Packet command
/// @param dlen Data length
/// @return Packet size
size_t pkt_calcsz(const uint8_t cmd, const size_t dlen) {
    const int data_en = cmd & PKT_NODATA != PKT_NODATA;
    const size_t chksumsz = iceil(dlen, 8, size_t);
#ifdef PKT_ENABLE_FOOTER
    return 3 + (data_en ? dlen + chksumsz : 0);
#else
    return 2 + (data_en ? dlen + chksumsz : 0);
#endif
}

/// @brief Create packet from raw data to buffer
/// @param cmd  Packet command
/// @param dbuf Command data pointer
/// @param dlen Data count to send
/// @param pbuf Packet data buffer
/// @param pbsz Packet data buffer size
/// @return Packet size written; 0 when overflow
size_t pkt_create(
    const uint8_t cmd,
    const uint8_t* dbuf, const size_t dlen,
    uint8_t* pbuf, const size_t pbsz
    ) {
    const size_t pktsz = pkt_calcsz(cmd, dlen);

    if (pbsz < pktsz) return 0;

    pbuf[0] = PKT_HEADER;
    pbuf[1] = cmd;
    
    if (cmd & PKT_NODATA != PKT_NODATA) {
        pbuf[2] = dlen;
        memcpy(pbuf + 3, dbuf, dlen);
        const size_t chksumsz = iceil(dlen, 8, size_t);
        for (int i = 0; i < chksumsz; i++) {
            const size_t blksz = (i == chksumsz - 1) ? dlen % 8 : 8;
            pbuf[dlen + 3 + i] = pkt_chksum(dbuf + 8 * i, blksz);
        }
#ifdef PKT_ENABLE_FOOTER
        pbuf[dlen + chksumsz + 3] = PKT_FOOTER;
#endif
    } else {
#ifdef PKT_ENABLE_FOOTER
        pbuf[2] = PKT_FOOTER;
#endif
    }
}

/// @brief Check packet integrity
/// @param pbuf Packet buffer
/// @param pbsz Packet size
/// @return true when passed packet integrity check
int pkt_check(const uint8_t* pbuf, const size_t pbsz) {
    if (pbuf[0] != PKT_HEADER) return false;
    if (pbuf[1] & PKT_NODATA == PKT_NODATA) {
#ifdef PKT_ENABLE_FOOTER
        return (pbsz == 3) && (pbuf[2] == PKT_FOOTER);
#else
        return pbsz == 2;
#endif
    } else {
        const uint8_t datasz = pbuf[2];
        const size_t chksumsz = iceil(datasz, 8, size_t);
#ifdef PKT_ENABLE_FOOTER
        if (pbsz != 3 + datasz + chksumsz) return false;
#else
        if (pbsz != 2 + datasz + chksumsz) return false;
#endif

        for (int i = 0; i < chksumsz; i++) {
            const size_t blksz = (i == chksumsz - 1) ? pbuf[2] % 8 : 8;
            if (pbuf[datasz + 3 + i] != pkt_chksum(pbuf + 8 * i, blksz))
                return false;
        }

#ifdef PKT_ENABLE_FOOTER
        return pbuf[3 + datasz + chksumsz] == PKT_FOOTER;
#endif
    }
}

uint8_t pkt_getcmd(const uint8_t* pbuf, const size_t pbsz) {
    
}
