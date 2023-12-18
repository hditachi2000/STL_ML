#include "convert.h"

#include <stddef.h>
#include <string.h>
#include "soc/efuse_reg.h"
#include "esp_heap_caps.h"
#include "sdkconfig.h"
#include "esp_jpg_decode.h"

#include "esp_system.h"

#if defined(ARDUINO_ARCH_ESP32) && defined(CONFIG_ARDUHAL_ESP_LOG)
#include "esp32-hal-log.h"
#define TAG ""
#else
#include "esp_log.h"
static const char* TAG = "to_bmp";
#endif

static const int BMP_HEADER_LEN = 54;

bool fmt2rgb888(const uint8_t *src_buf, size_t src_len, pixformat_t format, uint8_t * rgb_buf)
{
    int pix_count = 0;
    if(format == PIXFORMAT_JPEG) {
        return jpg2rgb888(src_buf, src_len, rgb_buf, JPG_SCALE_NONE);
    }
}

static bool jpg2rgb888(const uint8_t *src, size_t src_len, uint8_t * out, jpg_scale_t scale)
{
    rgb_jpg_decoder jpeg;
    jpeg.width = 0;
    jpeg.height = 0;
    jpeg.input = src;
    jpeg.output = out;
    jpeg.data_offset = 0;

    if(esp_jpg_decode(src_len, scale, _jpg_read, _rgb_write, (void*)&jpeg) != ESP_OK){
        return false;
    }
    return true;
}
