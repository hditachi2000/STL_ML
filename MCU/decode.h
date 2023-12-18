#ifdef decode_H
#define decode_H
typedef struct {
        jpg_scale_t scale;
        jpg_reader_cb reader;
        jpg_writer_cb writer;
        void * arg;
        size_t len;
        size_t index;
} esp_jpg_decoder_t;
#endif