#include "decode.h"

#include "esp_system.h"
#if ESP_IDF_VERSION_MAJOR >= 4 // IDF 4+
#if CONFIG_IDF_TARGET_ESP32 // ESP32/PICO-D4
#include "esp32/rom/tjpgd.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/tjpgd.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/tjpgd.h"
#elif CONFIG_ESP_ROM_HAS_JPEG_DECODE // available since IDF 4.4
#include "rom/tjpgd.h"  // latest IDFs have `rom/` includes available
#else
#include "tjpgd.h"  // using software decoder
#endif
#else // ESP32 Before IDF 4.0
#include "rom/tjpgd.h"
#endif

#if defined(ARDUINO_ARCH_ESP32) && defined(CONFIG_ARDUHAL_ESP_LOG)
#include "esp32-hal-log.h"
#define TAG ""
#else
#include "esp_log.h"
static const char* TAG = "esp_jpg_decode";
#endif

esp_err_t esp_jpg_decode(size_t len, jpg_scale_t scale, jpg_reader_cb reader, jpg_writer_cb writer, void * arg)
{
    static uint8_t work[3100];
    JDEC decoder;
    esp_jpg_decoder_t jpeg;

    jpeg.len = len;
    jpeg.reader = reader;
    jpeg.writer = writer;
    jpeg.arg = arg;
    jpeg.scale = scale;
    jpeg.index = 0;

    JRESULT jres = jd_prepare(&decoder, _jpg_read, work, 3100, &jpeg);
    if(jres != JDR_OK){
        ESP_LOGE(TAG, "JPG Header Parse Failed! %s", jd_errors[jres]);
        return ESP_FAIL;
    }

    uint16_t output_width = decoder.width / (1 << (uint8_t)(jpeg.scale));
    uint16_t output_height = decoder.height / (1 << (uint8_t)(jpeg.scale));

    //output start
    writer(arg, 0, 0, output_width, output_height, NULL);
    //output write
    jres = jd_decomp(&decoder, _jpg_write, (uint8_t)jpeg.scale);
    //output end
    writer(arg, output_width, output_height, output_width, output_height, NULL);

    if (jres != JDR_OK) {
        ESP_LOGE(TAG, "JPG Decompression Failed! %s", jd_errors[jres]);
        return ESP_FAIL;
    }
    //check if all data has been consumed.
    if (len && jpeg.index < len) {
        _jpg_read(&decoder, NULL, len - jpeg.index);
    }

    return ESP_OK;
}
