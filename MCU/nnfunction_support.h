
#ifndef _ARM_NNFUNCTIONS_H
#define _ARM_NNFUNCTIONS_H

// #include "arm_nn_math_types.h"

#ifndef ARM_NN_MATH_TYPES_H

#define ARM_NN_MATH_TYPES_H

#include <limits.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @brief Translate architecture feature flags to CMSIS-NN defines
 *
 */

// CMSIS-NN uses the same macro names as CMSIS-DSP
#if (defined(__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1))
    #ifndef ARM_MATH_DSP
        #define ARM_MATH_DSP 1
    #endif
#endif

#if defined(__ARM_FEATURE_MVE)
    #ifndef ARM_MATH_MVEI
        #define ARM_MATH_MVEI 1
    #endif
#endif

/**
 *
 * @brief Limits macros
 *
 */

#define NN_Q31_MAX ((int32_t)(0x7FFFFFFFL))
#define NN_Q15_MAX ((int16_t)(0x7FFF))
#define NN_Q7_MAX ((int8_t)(0x7F))
#define NN_Q31_MIN ((int32_t)(0x80000000L))
#define NN_Q15_MIN ((int16_t)(0x8000))
#define NN_Q7_MIN ((int8_t)(0x80))

#ifdef __cplusplus
}
#endif

#endif /*ifndef ARM_NN_MATH_TYPES_H */

// #include "arm_nn_types.h"

#ifndef _ARM_NN_TYPES_H
#define _ARM_NN_TYPES_H

#include <stdint.h>

/** Enum for specifying activation function types */
typedef enum
{
    ARM_SIGMOID = 0, /**< Sigmoid activation function */
    ARM_TANH = 1,    /**< Tanh activation function */
} arm_nn_activation_type;

/** Function return codes */
typedef enum
{
    ARM_CMSIS_NN_SUCCESS = 0,        /**< No error */
    ARM_CMSIS_NN_ARG_ERROR = -1,     /**< One or more arguments are incorrect */
    ARM_CMSIS_NN_NO_IMPL_ERROR = -2, /**<  No implementation available */
    ARM_CMSIS_NN_FAILURE = -3,       /**<  Logical error */
} arm_cmsis_nn_status;

/** CMSIS-NN object to contain the width and height of a tile */
typedef struct
{
    int32_t w; /**< Width */
    int32_t h; /**< Height */
} cmsis_nn_tile;

/** CMSIS-NN object used for the function context. */
typedef struct
{
    void *buf;    /**< Pointer to a buffer needed for the optimization */
    int32_t size; /**< Buffer size */
} cmsis_nn_context;

/** CMSIS-NN object to contain the dimensions of the tensors */
typedef struct
{
    int32_t n; /**< Generic dimension to contain either the batch size or output channels.
                     Please refer to the function documentation for more information */
    int32_t h; /**< Height */
    int32_t w; /**< Width */
    int32_t c; /**< Input channels */
} cmsis_nn_dims;

/** CMSIS-NN object to contain LSTM specific input parameters related to dimensions */
typedef struct
{
    int32_t max_time;
    int32_t num_inputs;
    int32_t num_batches;
    int32_t num_outputs;
} cmsis_nn_lstm_dims;

/** CMSIS-NN object for the per-channel quantization parameters */
typedef struct
{
    int32_t *multiplier; /**< Multiplier values */
    int32_t *shift;      /**< Shift values */
} cmsis_nn_per_channel_quant_params;

/** CMSIS-NN object for the per-tensor quantization parameters */
typedef struct
{
    int32_t multiplier; /**< Multiplier value */
    int32_t shift;      /**< Shift value */
} cmsis_nn_per_tensor_quant_params;

/** CMSIS-NN object for the quantized Relu activation */
typedef struct
{
    int32_t min; /**< Min value used to clamp the result */
    int32_t max; /**< Max value used to clamp the result */
} cmsis_nn_activation;

/** CMSIS-NN object for the convolution layer parameters */
typedef struct
{
    int32_t input_offset;  /**< Zero value for the input tensor */
    int32_t output_offset; /**< Zero value for the output tensor */
    cmsis_nn_tile stride;
    cmsis_nn_tile padding;
    cmsis_nn_tile dilation;
    cmsis_nn_activation activation;
} cmsis_nn_conv_params;

/** CMSIS-NN object for Depthwise convolution layer parameters */
typedef struct
{
    int32_t input_offset;  /**< Zero value for the input tensor */
    int32_t output_offset; /**< Zero value for the output tensor */
    int32_t ch_mult;       /**< Channel Multiplier. ch_mult * in_ch = out_ch */
    cmsis_nn_tile stride;
    cmsis_nn_tile padding;
    cmsis_nn_tile dilation;
    cmsis_nn_activation activation;
} cmsis_nn_dw_conv_params;
/** CMSIS-NN object for pooling layer parameters */
typedef struct
{
    cmsis_nn_tile stride;
    cmsis_nn_tile padding;
    cmsis_nn_activation activation;
} cmsis_nn_pool_params;

/** CMSIS-NN object for Fully Connected layer parameters */
typedef struct
{
    int32_t input_offset;  /**< Zero value for the input tensor */
    int32_t filter_offset; /**< Zero value for the filter tensor. Not used */
    int32_t output_offset; /**< Zero value for the output tensor */
    cmsis_nn_activation activation;
} cmsis_nn_fc_params;

/** CMSIS-NN object for SVDF layer parameters */
typedef struct
{
    int32_t rank;
    int32_t input_offset;  /**< Zero value for the input tensor */
    int32_t output_offset; /**< Zero value for the output tensor */
    cmsis_nn_activation input_activation;
    cmsis_nn_activation output_activation;
} cmsis_nn_svdf_params;

/** CMSIS-NN object for Softmax s16 layer parameters */
typedef struct
{
    const int16_t *exp_lut;
    const int16_t *one_by_one_lut;
} cmsis_nn_softmax_lut_s16;

/** LSTM guard parameters */
typedef struct
{
    int32_t input_variance;
    int32_t forget_variance;
    int32_t cell_variance;
    int32_t output_variance;
} cmsis_nn_lstm_guard_params;

/** LSTM scratch buffer container */
typedef struct
{
    int16_t *input_gate;
    int16_t *forget_gate;
    int16_t *cell_gate;
    int16_t *output_gate;
} cmsis_nn_lstm_context;

/** Quantized clip value for cell and projection of LSTM input. Zero value means no clipping. */
typedef struct
{
    int16_t cell;
    int8_t projection;
} cmsis_nn_lstm_clip_params;

/** CMSIS-NN object for quantization parameters */
typedef struct
{
    int32_t multiplier; /**< Multiplier value */
    int32_t shift;      /**< Shift value */
} cmsis_nn_scaling;

/** CMSIS-NN norm layer coefficients */
typedef struct
{
    int16_t *input_weight;
    int16_t *forget_weight;
    int16_t *cell_weight;
    int16_t *output_weight;
} cmsis_nn_layer_norm;

/** Parameters for integer LSTM, as defined in TFLM */
typedef struct
{
    int32_t time_major; /**< Nonzero (true) if first row of data is timestamps for input */
    cmsis_nn_scaling input_to_input_scaling;
    cmsis_nn_scaling input_to_forget_scaling;
    cmsis_nn_scaling input_to_cell_scaling;
    cmsis_nn_scaling input_to_output_scaling;
    cmsis_nn_scaling recurrent_to_input_scaling;
    cmsis_nn_scaling recurrent_to_forget_scaling;
    cmsis_nn_scaling recurrent_to_cell_scaling;
    cmsis_nn_scaling recurrent_to_output_scaling;
    cmsis_nn_scaling cell_to_input_scaling;
    cmsis_nn_scaling cell_to_forget_scaling;
    cmsis_nn_scaling cell_to_output_scaling;
    cmsis_nn_scaling projection_scaling;
    cmsis_nn_scaling hidden_scaling;
    cmsis_nn_scaling layer_norm_input_scaling;  /**< layer normalization for input layer */
    cmsis_nn_scaling layer_norm_forget_scaling; /**< layer normalization for forget gate */
    cmsis_nn_scaling layer_norm_cell_scaling;   /**< layer normalization for cell */
    cmsis_nn_scaling layer_norm_output_scaling; /**< layer normalization for outpus layer */

    int32_t cell_state_shift;
    int32_t hidden_offset;
    int32_t output_state_offset;

    cmsis_nn_lstm_clip_params clip;
    cmsis_nn_lstm_guard_params guard;
    cmsis_nn_layer_norm layer_norm;

    /* Effective bias is precalculated as bias + zero_point * weight.
    Only applicable to when input/output are s8 and weights are s16 */
    const int32_t *i2i_effective_bias; /**< input to input effective bias */
    const int32_t *i2f_effective_bias; /**< input to forget gate effective bias */
    const int32_t *i2c_effective_bias; /**< input to cell effective bias */
    const int32_t *i2o_effective_bias; /**< input to output effective bias */

    const int32_t *r2i_effective_bias; /**< recurrent gate to input effective bias */
    const int32_t *r2f_effective_bias; /**< recurrent gate to forget gate effective bias */
    const int32_t *r2c_effective_bias; /**< recurrent gate to cell effective bias */
    const int32_t *r2o_effective_bias; /**< recurrent gate to output effective bias */

    const int32_t *projection_effective_bias;

    /* Not precalculated bias */
    const int32_t *input_gate_bias;
    const int32_t *forget_gate_bias;
    const int32_t *cell_gate_bias;
    const int32_t *output_gate_bias;

    /* Activation min and max */
    cmsis_nn_activation activation;

} cmsis_nn_lstm_params;

#endif // _ARM_NN_TYPES_H


#define USE_INTRINSIC

#ifdef __cplusplus
extern "C" {
#endif


arm_cmsis_nn_status arm_convolve_wrapper_s8(const cmsis_nn_context *ctx,
                                            const cmsis_nn_conv_params *conv_params,
                                            const cmsis_nn_per_channel_quant_params *quant_params,
                                            const cmsis_nn_dims *input_dims,
                                            const int8_t *input_data,
                                            const cmsis_nn_dims *filter_dims,
                                            const int8_t *filter_data,
                                            const cmsis_nn_dims *bias_dims,
                                            const int32_t *bias_data,
                                            const cmsis_nn_dims *output_dims,
                                            int8_t *output_data);

/**
 * @brief Get the required buffer size for arm_convolve_wrapper_s8
 *
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                Range of conv_params->input_offset  : [-127, 128]
 *                                Range of conv_params->output_offset : [-128, 127]
 * @param[in]      input_dims     Input (activation) dimensions. Format: [N, H, W, C_IN]
 * @param[in]      filter_dims    Filter dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the spatial
 *                                filter dimensions
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 *
 * @return         The function returns required buffer size(bytes)
 *
 */
int32_t arm_convolve_wrapper_s8_get_buffer_size(const cmsis_nn_conv_params *conv_params,
                                                const cmsis_nn_dims *input_dims,
                                                const cmsis_nn_dims *filter_dims,
                                                const cmsis_nn_dims *output_dims);

/**
 * @brief Get the required buffer size for arm_convolve_wrapper_s8 for Arm(R) Helium Architecture case.
 *        Refer to arm_convolve_wrapper_s8_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_convolve_wrapper_s8_get_buffer_size().
 *
 */
int32_t arm_convolve_wrapper_s8_get_buffer_size_mve(const cmsis_nn_conv_params *conv_params,
                                                    const cmsis_nn_dims *input_dims,
                                                    const cmsis_nn_dims *filter_dims,
                                                    const cmsis_nn_dims *output_dims);

/**
 * @brief Get the required buffer size for arm_convolve_wrapper_s8 for processors with DSP extension.
 *        Refer to arm_convolve_wrapper_s8_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_convolve_wrapper_s8_get_buffer_size().
 *
 */
int32_t arm_convolve_wrapper_s8_get_buffer_size_dsp(const cmsis_nn_conv_params *conv_params,
                                                    const cmsis_nn_dims *input_dims,
                                                    const cmsis_nn_dims *filter_dims,
                                                    const cmsis_nn_dims *output_dims);

/**
 * @brief s16 convolution layer wrapper function with the main purpose to call the optimal kernel available in
 *        cmsis-nn to perform the convolution.
 *
 * @param[in, out] ctx            Function context that contains the additional buffer if required by the function.
 *                                arm_convolve_wrapper_s8_get_buffer_size will return the buffer_size if required
 *                                The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                conv_params->input_offset  : Not used
 *                                conv_params->output_offset : Not used
 * @param[in]      quant_params   Per-channel quantization info.
 *                                It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data     Input (activation) data pointer. Data type: int16
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the
 *                                spatial filter dimensions
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Bias data pointer. Data type: int64
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data    Output data pointer. Data type: int16
 *
 * @return     The function returns either
 *                  <code>ARM_CMSIS_NN_ARG_ERROR</code> if argument constraints fail. or,
 *                  <code>ARM_CMSIS_NN_SUCCESS</code> on successful completion.
 *
 */
arm_cmsis_nn_status arm_convolve_wrapper_s16(const cmsis_nn_context *ctx,
                                             const cmsis_nn_conv_params *conv_params,
                                             const cmsis_nn_per_channel_quant_params *quant_params,
                                             const cmsis_nn_dims *input_dims,
                                             const int16_t *input_data,
                                             const cmsis_nn_dims *filter_dims,
                                             const int8_t *filter_data,
                                             const cmsis_nn_dims *bias_dims,
                                             const int64_t *bias_data,
                                             const cmsis_nn_dims *output_dims,
                                             int16_t *output_data);

/**
 * @brief Get the required buffer size for arm_convolve_wrapper_s16.
 *
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                conv_params->input_offset  : Not used
 *                                conv_params->output_offset : Not used
 * @param[in]      input_dims     Input (activation) dimensions. Format: [N, H, W, C_IN]
 * @param[in]      filter_dims    Filter dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the spatial
 *                                filter dimensions
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 *
 * @return         The function returns required buffer size(bytes)
 *
 */
int32_t arm_convolve_wrapper_s16_get_buffer_size(const cmsis_nn_conv_params *conv_params,
                                                 const cmsis_nn_dims *input_dims,
                                                 const cmsis_nn_dims *filter_dims,
                                                 const cmsis_nn_dims *output_dims);

/**
 * @brief Get the required buffer size for arm_convolve_wrapper_s16 for for processors with DSP extension.
 *        Refer to arm_convolve_wrapper_s16_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_convolve_wrapper_s16_get_buffer_size().
 *
 */
int32_t arm_convolve_wrapper_s16_get_buffer_size_dsp(const cmsis_nn_conv_params *conv_params,
                                                     const cmsis_nn_dims *input_dims,
                                                     const cmsis_nn_dims *filter_dims,
                                                     const cmsis_nn_dims *output_dims);

/**
 * @brief Get the required buffer size for arm_convolve_wrapper_s16 for Arm(R) Helium Architecture case.
 *        Refer to arm_convolve_wrapper_s16_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_convolve_wrapper_s16_get_buffer_size().
 *
 */
int32_t arm_convolve_wrapper_s16_get_buffer_size_mve(const cmsis_nn_conv_params *conv_params,
                                                     const cmsis_nn_dims *input_dims,
                                                     const cmsis_nn_dims *filter_dims,
                                                     const cmsis_nn_dims *output_dims);

/**
 * @brief Basic s8 convolution function
 * @param[in, out] ctx            Function context that contains the additional buffer if required by the function.
 *                                arm_convolve_s8_get_buffer_size will return the buffer_size if required.
 *                                The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                Range of conv_params->input_offset  : [-127, 128]
 *                                Range of conv_params->output_offset : [-128, 127]
 * @param[in]      quant_params   Per-channel quantization info.
 *                                It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data     Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the
 *                                spatial filter dimensions
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Optional bias data pointer. Data type: int32
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data    Output data pointer. Data type: int8

 * @return     The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 * @details
 *    1. Supported framework: TensorFlow Lite micro
 *    2. Additional memory is required for optimization. Refer to argument 'ctx' for details.
 *
 */
arm_cmsis_nn_status arm_convolve_s8(const cmsis_nn_context *ctx,
                                    const cmsis_nn_conv_params *conv_params,
                                    const cmsis_nn_per_channel_quant_params *quant_params,
                                    const cmsis_nn_dims *input_dims,
                                    const int8_t *input_data,
                                    const cmsis_nn_dims *filter_dims,
                                    const int8_t *filter_data,
                                    const cmsis_nn_dims *bias_dims,
                                    const int32_t *bias_data,
                                    const cmsis_nn_dims *output_dims,
                                    int8_t *output_data);

/**
 * @brief Get the required buffer size for s8 convolution function
 *
 * @param[in]       input_dims            Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]       filter_dims           Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK
 * are the spatial filter dimensions
 * @return          The function returns required buffer size(bytes)
 *
 */
int32_t arm_convolve_s8_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims);

/**
 * @brief Basic s16 convolution function
 * @param[in, out] ctx            Function context that contains the additional buffer if required by the function.
 *                                arm_convolve_s16_get_buffer_size will return the buffer_size if required.
 *                                The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                conv_params->input_offset  : Not used
 *                                conv_params->output_offset : Not used
 * @param[in]      quant_params   Per-channel quantization info.
 *                                It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data     Input (activation) data pointer. Data type: int16
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the
 *                                spatial filter dimensions
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Optional bias data pointer. Data type: int64
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data    Output data pointer. Data type: int16

 * @return     The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 * @details
 *    1. Supported framework: TensorFlow Lite micro
 *    2. Additional memory is required for optimization. Refer to argument 'ctx' for details.
 *
 */
arm_cmsis_nn_status arm_convolve_s16(const cmsis_nn_context *ctx,
                                     const cmsis_nn_conv_params *conv_params,
                                     const cmsis_nn_per_channel_quant_params *quant_params,
                                     const cmsis_nn_dims *input_dims,
                                     const int16_t *input_data,
                                     const cmsis_nn_dims *filter_dims,
                                     const int8_t *filter_data,
                                     const cmsis_nn_dims *bias_dims,
                                     const int64_t *bias_data,
                                     const cmsis_nn_dims *output_dims,
                                     int16_t *output_data);
/**
 * @brief Optimized s16 convolution function
 * @param[in, out] ctx            Function context that contains the additional buffer if required by the function.
 *                                arm_convolve_fast_s16_get_buffer_size will return the buffer_size if required.
 *                                The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                conv_params->input_offset  : Not used
 *                                conv_params->output_offset : Not used
 * @param[in]      quant_params   Per-channel quantization info.
 *                                It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data     Input (activation) data pointer. Data type: int16
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the
 *                                spatial filter dimensions. (filter_dims->w * filter_dims->h * input_dims->c) must not
 exceed 512
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Optional bias data pointer. Data type: int64
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data    Output data pointer. Data type: int16

 * @return     The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 * @details
 *    1. Supported framework: TensorFlow Lite micro
 *    2. Additional memory is required for optimization. Refer to argument 'ctx' for details.
 *    3. Implementation supports kernel volumes (filter width * filter height * input channels) < 512.
 *
 */

arm_cmsis_nn_status arm_convolve_fast_s16(const cmsis_nn_context *ctx,
                                          const cmsis_nn_conv_params *conv_params,
                                          const cmsis_nn_per_channel_quant_params *quant_params,
                                          const cmsis_nn_dims *input_dims,
                                          const int16_t *input_data,
                                          const cmsis_nn_dims *filter_dims,
                                          const int8_t *filter_data,
                                          const cmsis_nn_dims *bias_dims,
                                          const int64_t *bias_data,
                                          const cmsis_nn_dims *output_dims,
                                          int16_t *output_data);

/**
 * @brief Get the required buffer size for s16 convolution function
 *
 * @param[in]       input_dims    Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]       filter_dims   Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK
 *                                are the spatial filter dimensions
 * @return          The function returns required buffer size(bytes)
 *
 */
int32_t arm_convolve_s16_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims);

/**
 * @brief Get the required buffer size for fast s16 convolution function
 *
 * @param[in]       input_dims    Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]       filter_dims   Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK
 *                                are the spatial filter dimensions
 * @return          The function returns required buffer size(bytes)
 *
 */
int32_t arm_convolve_fast_s16_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims);

/**
 * @brief Fast s8 version for 1x1 convolution (non-square shape)
 *
 * @param[in, out] ctx           Function context that contains the additional buffer if required by the function.
 *                               arm_convolve_1x1_s8_fast_get_buffer_size will return the buffer_size if required.
 *                               The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      conv_params   Convolution parameters (e.g. strides, dilations, pads,...).
 *                               Range of conv_params->input_offset  : [-127, 128]
 *                               Range of conv_params->output_offset : [-128, 127]
 * @param[in]      quant_params  Per-channel quantization info.
 *                               It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims    Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data    Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims   Filter tensor dimensions. Format: [C_OUT, 1, 1, C_IN]
 * @param[in]      filter_data   Filter data pointer. Data type: int8
 * @param[in]      bias_dims     Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data     Optional bias data pointer. Data type: int32
 * @param[in]      output_dims   Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data   Output data pointer. Data type: int8
 *
 * @return     The function returns either
 *                  <code>ARM_CMSIS_NN_ARG_ERROR</code> if argument constraints fail. or,
 *                  <code>ARM_CMSIS_NN_SUCCESS</code> on successful completion.
 *
 * @details
 *   - Supported framework : TensorFlow Lite Micro
 *   - The following constrains on the arguments apply
 *      -# conv_params->padding.w = conv_params->padding.h = 0
 *      -# conv_params->stride.w = conv_params->stride.h = 1
 *
 */
arm_cmsis_nn_status arm_convolve_1x1_s8_fast(const cmsis_nn_context *ctx,
                                             const cmsis_nn_conv_params *conv_params,
                                             const cmsis_nn_per_channel_quant_params *quant_params,
                                             const cmsis_nn_dims *input_dims,
                                             const int8_t *input_data,
                                             const cmsis_nn_dims *filter_dims,
                                             const int8_t *filter_data,
                                             const cmsis_nn_dims *bias_dims,
                                             const int32_t *bias_data,
                                             const cmsis_nn_dims *output_dims,
                                             int8_t *output_data);

/**
 * @brief Get the required buffer size for arm_convolve_1x1_s8_fast
 *
 * @param[in]       input_dims            Input (activation) dimensions
 * @return          The function returns the required buffer size in bytes
 *
 */
int32_t arm_convolve_1x1_s8_fast_get_buffer_size(const cmsis_nn_dims *input_dims);

/**
 * @brief s8 version for 1x1 convolution with support for non-unity stride values
 *
 * @param[in, out] ctx           Function context that contains the additional buffer if required by the function.
 *                               None is required by this function.
 * @param[in]      conv_params   Convolution parameters (e.g. strides, dilations, pads,...).
 *                               Range of conv_params->input_offset  : [-127, 128]
 *                               Range of conv_params->output_offset : [-128, 127]
 * @param[in]      quant_params  Per-channel quantization info.
 *                               It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims    Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data    Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims   Filter tensor dimensions. Format: [C_OUT, 1, 1, C_IN]
 * @param[in]      filter_data   Filter data pointer. Data type: int8
 * @param[in]      bias_dims     Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data     Optional bias data pointer. Data type: int32
 * @param[in]      output_dims   Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data   Output data pointer. Data type: int8
 *
 * @return     The function returns either
 *                  <code>ARM_CMSIS_NN_ARG_ERROR</code> if argument constraints fail. or,
 *                  <code>ARM_CMSIS_NN_SUCCESS</code> on successful completion.
 * @details
 *   - Supported framework : TensorFlow Lite Micro
 *   - The following constrains on the arguments apply
 *      -# conv_params->padding.w = conv_params->padding.h = 0
 *
 */
arm_cmsis_nn_status arm_convolve_1x1_s8(const cmsis_nn_context *ctx,
                                        const cmsis_nn_conv_params *conv_params,
                                        const cmsis_nn_per_channel_quant_params *quant_params,
                                        const cmsis_nn_dims *input_dims,
                                        const int8_t *input_data,
                                        const cmsis_nn_dims *filter_dims,
                                        const int8_t *filter_data,
                                        const cmsis_nn_dims *bias_dims,
                                        const int32_t *bias_data,
                                        const cmsis_nn_dims *output_dims,
                                        int8_t *output_data);

/**
 * @brief 1xn convolution
 *
 * @param[in, out] ctx           Function context that contains the additional buffer if required by the function.
 *                               arm_convolve_1_x_n_s8_get_buffer_size will return the buffer_size if required
 *                               The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      conv_params   Convolution parameters (e.g. strides, dilations, pads,...).
 *                               Range of conv_params->input_offset  : [-127, 128]
 *                               Range of conv_params->output_offset : [-128, 127]
 * @param[in]      quant_params  Per-channel quantization info.
 *                               It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims    Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data    Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims   Filter tensor dimensions. Format: [C_OUT, 1, WK, C_IN] where WK is the horizontal
 *                               spatial filter dimension
 * @param[in]      filter_data   Filter data pointer. Data type: int8
 * @param[in]      bias_dims     Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data     Optional bias data pointer. Data type: int32
 * @param[in]      output_dims   Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data   Output data pointer. Data type: int8
 *
 * @return     The function returns either
 *                  <code>ARM_CMSIS_NN_ARG_ERROR</code> if argument constraints fail. or,
 *                  <code>ARM_CMSIS_NN_SUCCESS</code> on successful completion.
 *
 * @details
 *   - Supported framework : TensorFlow Lite Micro
 *   - The following constrains on the arguments apply
 *      -# input_dims->n equals 1
 *      -# ouput_dims->w is a multiple of 4
 *      -# Explicit constraints(since it is for 1xN convolution)
 *      -## input_dims->h equals 1
 *      -## output_dims->h equals 1
 *      -## filter_dims->h equals 1
 *@todo  Remove constraint on output_dims->w to make the function generic.
 *
 */
arm_cmsis_nn_status arm_convolve_1_x_n_s8(const cmsis_nn_context *ctx,
                                          const cmsis_nn_conv_params *conv_params,
                                          const cmsis_nn_per_channel_quant_params *quant_params,
                                          const cmsis_nn_dims *input_dims,
                                          const int8_t *input_data,
                                          const cmsis_nn_dims *filter_dims,
                                          const int8_t *filter_data,
                                          const cmsis_nn_dims *bias_dims,
                                          const int32_t *bias_data,
                                          const cmsis_nn_dims *output_dims,
                                          int8_t *output_data);

/**
 * @brief Get the required additional buffer size for 1xn convolution
 *
 * @param[in]       input_dims            Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]       filter_dims           Filter tensor dimensions. Format: [C_OUT, 1, WK, C_IN] where WK is the
 *                                        horizontal spatial filter dimension
 * @return          The function returns required buffer size(bytes)
 *
 */
int32_t arm_convolve_1_x_n_s8_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims);

/**
 * @brief Wrapper function to pick the right optimized s8 depthwise convolution function
 *
 * @param[in, out] ctx             Function context (e.g. temporary buffer). Check the function
 *                                 definition file to see if an additional buffer is required.
 *                                 Optional function {API}_get_buffer_size() provides the buffer
 *                                 size if required.
 *                                 The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      dw_conv_params  Depthwise convolution parameters (e.g. strides, dilations, pads,...)
 *                                 dw_conv_params->dilation is not used.
 *                                 Range of dw_conv_params->input_offset : [-127, 128]
 *                                 Range of dw_conv_params->output_offset : [-128, 127]
 * @param[in]      quant_params    Per-channel quantization info.
 *                                 It contains the multiplier and shift values to be applied to each
 *                                 output channel
 * @param[in]      input_dims      Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                                 Batch argument N is not used and assumed to be 1.
 * @param[in]      input_data      Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims     Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in]      filter_data     Filter data pointer. Data type: int8
 * @param[in]      bias_dims       Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data       Bias data pointer. Data type: int32
 * @param[in]      output_dims     Output tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in, out] output_data     Output data pointer. Data type: int8
 * @return     The function returns
 *                <code>ARM_CMSIS_NN_SUCCESS</code>   -  Successful completion.
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 *    - Picks one of the the following functions
 *        -# arm_depthwise_conv_s8()
 *        -# arm_depthwise_conv_3x3_s8() - Cortex-M CPUs with DSP extension only
 *        -# arm_depthwise_conv_s8_opt()
 *    - Check details of arm_depthwise_conv_s8_opt() for potential data that can be accessed outside of the
 * boundary.
 */
arm_cmsis_nn_status arm_depthwise_conv_wrapper_s8(const cmsis_nn_context *ctx,
                                                  const cmsis_nn_dw_conv_params *dw_conv_params,
                                                  const cmsis_nn_per_channel_quant_params *quant_params,
                                                  const cmsis_nn_dims *input_dims,
                                                  const int8_t *input_data,
                                                  const cmsis_nn_dims *filter_dims,
                                                  const int8_t *filter_data,
                                                  const cmsis_nn_dims *bias_dims,
                                                  const int32_t *bias_data,
                                                  const cmsis_nn_dims *output_dims,
                                                  int8_t *output_data);

/**
 * @brief Get size of additional buffer required by arm_depthwise_conv_wrapper_s8()
 *
 * @param[in]      dw_conv_params  Depthwise convolution parameters (e.g. strides, dilations, pads,...)
 *                                 Range of dw_conv_params->input_offset : [-127, 128]
 *                                 Range of dw_conv_params->input_offset : [-128, 127]
 * @param[in]      input_dims      Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                                 Batch argument N is not used and assumed to be 1.
 * @param[in]      filter_dims     Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in]      output_dims     Output tensor dimensions. Format: [1, H, W, C_OUT]
 * @return                         Size of additional memory required for optimizations in bytes.
 *
 */
int32_t arm_depthwise_conv_wrapper_s8_get_buffer_size(const cmsis_nn_dw_conv_params *dw_conv_params,
                                                      const cmsis_nn_dims *input_dims,
                                                      const cmsis_nn_dims *filter_dims,
                                                      const cmsis_nn_dims *output_dims);

/**
 * @brief Get size of additional buffer required by arm_depthwise_conv_wrapper_s8() for processors with DSP extension.
 *        Refer to arm_depthwise_conv_wrapper_s8_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_depthwise_conv_wrapper_s8_get_buffer_size().
 *
 */
int32_t arm_depthwise_conv_wrapper_s8_get_buffer_size_dsp(const cmsis_nn_dw_conv_params *dw_conv_params,
                                                          const cmsis_nn_dims *input_dims,
                                                          const cmsis_nn_dims *filter_dims,
                                                          const cmsis_nn_dims *output_dims);

/**
 * @brief Get size of additional buffer required by arm_depthwise_conv_wrapper_s8() for Arm(R) Helium Architecture case.
 *        Refer to arm_depthwise_conv_wrapper_s8_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_depthwise_conv_wrapper_s8_get_buffer_size().
 *
 */
int32_t arm_depthwise_conv_wrapper_s8_get_buffer_size_mve(const cmsis_nn_dw_conv_params *dw_conv_params,
                                                          const cmsis_nn_dims *input_dims,
                                                          const cmsis_nn_dims *filter_dims,
                                                          const cmsis_nn_dims *output_dims);

/**
 * @brief Basic s8 depthwise convolution function that doesn't have any constraints on the input dimensions.
 *
 * @param[in, out] ctx             Function context (e.g. temporary buffer). Check the function
 *                                 definition file to see if an additional buffer is required.
 *                                 Optional function {API}_get_buffer_size() provides the buffer
 *                                 size if an additional buffer is required exists if additional memory is.
 *                                 The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      dw_conv_params  Depthwise convolution parameters (e.g. strides, dilations, pads,...)
 *                                 dw_conv_params->dilation is not used.
 *                                 Range of dw_conv_params->input_offset : [-127, 128]
 *                                 Range of dw_conv_params->input_offset : [-128, 127]
 * @param[in]      quant_params    Per-channel quantization info.
 *                                 It contains the multiplier and shift values to be applied to each
 *                                 output channel
 * @param[in]      input_dims      Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 *                                 Batch argument N is not used.
 * @param[in]      input_data      Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims     Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in]      filter_data     Filter data pointer. Data type: int8
 * @param[in]      bias_dims       Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data       Bias data pointer. Data type: int32
 * @param[in]      output_dims     Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[in, out] output_data     Output data pointer. Data type: int8
 * @return     The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 */
arm_cmsis_nn_status arm_depthwise_conv_s8(const cmsis_nn_context *ctx,
                                          const cmsis_nn_dw_conv_params *dw_conv_params,
                                          const cmsis_nn_per_channel_quant_params *quant_params,
                                          const cmsis_nn_dims *input_dims,
                                          const int8_t *input_data,
                                          const cmsis_nn_dims *filter_dims,
                                          const int8_t *filter_data,
                                          const cmsis_nn_dims *bias_dims,
                                          const int32_t *bias_data,
                                          const cmsis_nn_dims *output_dims,
                                          int8_t *output_data);

/**
 * @brief Basic s16 depthwise convolution function that doesn't have any constraints on the input dimensions.
 *
 * @param[in, out] ctx             Function context (e.g. temporary buffer). Check the function
 *                                 definition file to see if an additional buffer is required.
 *                                 Optional function {API}_get_buffer_size() provides the buffer
 *                                 size if an additional buffer is required.
 *                                 exists if additional memory is.
 *                                 The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      dw_conv_params  Depthwise convolution parameters (e.g. strides, dilations, pads,...)
 *                                 conv_params->input_offset  : Not used
 *                                 conv_params->output_offset : Not used
 * @param[in]      quant_params    Per-channel quantization info.
 *                                 It contains the multiplier and shift values to be applied to each
 *                                 output channel
 * @param[in]      input_dims      Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 *                                 Batch argument N is not used.
 * @param[in]      input_data      Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims     Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in]      filter_data     Filter data pointer. Data type: int8
 * @param[in]      bias_dims       Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data       Bias data pointer. Data type: int64
 * @param[in]      output_dims     Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[in, out] output_data     Output data pointer. Data type: int16
 * @return     The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 */
arm_cmsis_nn_status arm_depthwise_conv_s16(const cmsis_nn_context *ctx,
                                           const cmsis_nn_dw_conv_params *dw_conv_params,
                                           const cmsis_nn_per_channel_quant_params *quant_params,
                                           const cmsis_nn_dims *input_dims,
                                           const int16_t *input_data,
                                           const cmsis_nn_dims *filter_dims,
                                           const int8_t *filter_data,
                                           const cmsis_nn_dims *bias_dims,
                                           const int64_t *bias_data,
                                           const cmsis_nn_dims *output_dims,
                                           int16_t *output_data);

/**
 * @brief Wrapper function to pick the right optimized s16 depthwise convolution function
 *
 * @param[in, out] ctx             Function context (e.g. temporary buffer). Check the function
 *                                 definition file to see if an additional buffer is required.
 *                                 Optional function {API}_get_buffer_size() provides the buffer
 *                                 size if required.
 *                                 The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      dw_conv_params  Depthwise convolution parameters (e.g. strides, dilations, pads,...)
 *                                 dw_conv_params->dilation is not used.
 *                                 Range of dw_conv_params->input_offset : Not used
 *                                 Range of dw_conv_params->output_offset : Not used
 * @param[in]      quant_params    Per-channel quantization info.
 *                                 It contains the multiplier and shift values to be applied to each
 *                                 output channel
 * @param[in]      input_dims      Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                                 Batch argument N is not used and assumed to be 1.
 * @param[in]      input_data      Input (activation) data pointer. Data type: int16
 * @param[in]      filter_dims     Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in]      filter_data     Filter data pointer. Data type: int8
 * @param[in]      bias_dims       Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data       Bias data pointer. Data type: int64
 * @param[in]      output_dims     Output tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in, out] output_data     Output data pointer. Data type: int16
 * @return     The function returns
 *                <code>ARM_CMSIS_NN_SUCCESS</code>   -  Successful completion.
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 *    - Picks one of the the following functions
 *        -# arm_depthwise_conv_s16()
 *        -# arm_depthwise_conv_fast_s16()  - Cortex-M CPUs with DSP extension only
 */
arm_cmsis_nn_status arm_depthwise_conv_wrapper_s16(const cmsis_nn_context *ctx,
                                                   const cmsis_nn_dw_conv_params *dw_conv_params,
                                                   const cmsis_nn_per_channel_quant_params *quant_params,
                                                   const cmsis_nn_dims *input_dims,
                                                   const int16_t *input_data,
                                                   const cmsis_nn_dims *filter_dims,
                                                   const int8_t *filter_data,
                                                   const cmsis_nn_dims *bias_dims,
                                                   const int64_t *bias_data,
                                                   const cmsis_nn_dims *output_dims,
                                                   int16_t *output_data);

/**
 * @brief Get size of additional buffer required by arm_depthwise_conv_wrapper_s16()
 *
 * @param[in]      dw_conv_params  Depthwise convolution parameters (e.g. strides, dilations, pads,...)
 *                                 Range of dw_conv_params->input_offset : Not used
 *                                 Range of dw_conv_params->input_offset : Not used
 * @param[in]      input_dims      Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                                 Batch argument N is not used and assumed to be 1.
 * @param[in]      filter_dims     Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in]      output_dims     Output tensor dimensions. Format: [1, H, W, C_OUT]
 * @return                         Size of additional memory required for optimizations in bytes.
 *
 */
int32_t arm_depthwise_conv_wrapper_s16_get_buffer_size(const cmsis_nn_dw_conv_params *dw_conv_params,
                                                       const cmsis_nn_dims *input_dims,
                                                       const cmsis_nn_dims *filter_dims,
                                                       const cmsis_nn_dims *output_dims);

/**
 * @brief Get size of additional buffer required by arm_depthwise_conv_wrapper_s16() for processors with DSP extension.
 *        Refer to arm_depthwise_conv_wrapper_s16_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_depthwise_conv_wrapper_s16_get_buffer_size().
 *
 */
int32_t arm_depthwise_conv_wrapper_s16_get_buffer_size_dsp(const cmsis_nn_dw_conv_params *dw_conv_params,
                                                           const cmsis_nn_dims *input_dims,
                                                           const cmsis_nn_dims *filter_dims,
                                                           const cmsis_nn_dims *output_dims);

/**
 * @brief Get size of additional buffer required by arm_depthwise_conv_wrapper_s16() for Arm(R) Helium Architecture
 * case. Refer to arm_depthwise_conv_wrapper_s16_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_depthwise_conv_wrapper_s16_get_buffer_size().
 *
 */
int32_t arm_depthwise_conv_wrapper_s16_get_buffer_size_mve(const cmsis_nn_dw_conv_params *dw_conv_params,
                                                           const cmsis_nn_dims *input_dims,
                                                           const cmsis_nn_dims *filter_dims,
                                                           const cmsis_nn_dims *output_dims);

/**
 * @brief Optimized s16 depthwise convolution function with constraint that in_channel equals out_channel.
 *        Refer arm_depthwise_conv_s16() for function argument details.
 *
 * @return     The function returns one of the following
 *                <code>ARM_CMSIS_NN_ARG_ERROR</code> - ctx-buff == NULL and
 *                                                      arm_depthwise_conv_fast_s16_get_buffer_size() > 0 or
 *                                                      input channel != output channel or
 *                                                      ch_mult != 1
 *
 *                <code>ARM_CMSIS_NN_SUCCESS</code> - Successful operation
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 *    - The following constrains on the arguments apply
 *        -# Number of input channel equals number of output channels or ch_mult equals 1
 *    - Reccomended when number of channels is 4 or greater.
 *
 */
arm_cmsis_nn_status arm_depthwise_conv_fast_s16(const cmsis_nn_context *ctx,
                                                const cmsis_nn_dw_conv_params *dw_conv_params,
                                                const cmsis_nn_per_channel_quant_params *quant_params,
                                                const cmsis_nn_dims *input_dims,
                                                const int16_t *input_data,
                                                const cmsis_nn_dims *filter_dims,
                                                const int8_t *filter_data,
                                                const cmsis_nn_dims *bias_dims,
                                                const int64_t *bias_data,
                                                const cmsis_nn_dims *output_dims,
                                                int16_t *output_data);

/**
 * @brief Get the required buffer size for optimized s16 depthwise convolution
 * function with constraint that in_channel equals out_channel.
 * @param[in]       input_dims   Input (activation) tensor dimensions. Format: [1, H, W, C_IN]
 *                               Batch argument N is not used.
 * @param[in]       filter_dims  Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @return          The function returns required buffer size in bytes
 *
 */
int32_t arm_depthwise_conv_fast_s16_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims);

/**
 * @brief Optimized s8 depthwise convolution function for 3x3 kernel size with some constraints on
 *        the input arguments(documented below). Refer arm_depthwise_conv_s8() for function
 *        argument details.
 *
 * @return     The function returns one of the following
 *                <code>ARM_CMSIS_NN_ARG_ERROR</code> - Unsupported dimension of tensors
 *                                                    - Unsupported pad size along the x axis
 *                <code>ARM_CMSIS_NN_SUCCESS</code> - Successful operation
 *
 * @details
 *   - Supported framework : TensorFlow Lite Micro
 *   - The following constrains on the arguments apply
 *      -# Number of input channel equals number of output channels
 *      -# Filter height and width equals 3
 *      -# Padding along x is either 0 or 1.
 *
 */
arm_cmsis_nn_status arm_depthwise_conv_3x3_s8(const cmsis_nn_context *ctx,
                                              const cmsis_nn_dw_conv_params *dw_conv_params,
                                              const cmsis_nn_per_channel_quant_params *quant_params,
                                              const cmsis_nn_dims *input_dims,
                                              const int8_t *input_data,
                                              const cmsis_nn_dims *filter_dims,
                                              const int8_t *filter_data,
                                              const cmsis_nn_dims *bias_dims,
                                              const int32_t *bias_data,
                                              const cmsis_nn_dims *output_dims,
                                              int8_t *output_data);

/**
 * @brief Optimized s8 depthwise convolution function with constraint that in_channel equals out_channel.
 *        Refer arm_depthwise_conv_s8() for function argument details.
 *
 * @return     The function returns one of the following
 *                <code>ARM_CMSIS_NN_ARG_ERROR</code> - input channel != output channel or
 *                                                      ch_mult != 1
 *                <code>ARM_CMSIS_NN_SUCCESS</code> - Successful operation
 *
 * @note       If number of channels is not a multiple of 4, upto 3 elements outside the boundary will be read out
 *             for the following if MVE optimizations(Arm Helium Technology) are used.
 *               - Output shift
 *               - Output multiplier
 *               - Output bias
 *               - kernel
 * @details
 *    - Supported framework: TensorFlow Lite
 *    - The following constrains on the arguments apply
 *        -# Number of input channel equals number of output channels or ch_mult equals 1
 *    - Reccomended when number of channels is 4 or greater.
 *
 */
arm_cmsis_nn_status arm_depthwise_conv_s8_opt(const cmsis_nn_context *ctx,
                                              const cmsis_nn_dw_conv_params *dw_conv_params,
                                              const cmsis_nn_per_channel_quant_params *quant_params,
                                              const cmsis_nn_dims *input_dims,
                                              const int8_t *input_data,
                                              const cmsis_nn_dims *filter_dims,
                                              const int8_t *filter_data,
                                              const cmsis_nn_dims *bias_dims,
                                              const int32_t *bias_data,
                                              const cmsis_nn_dims *output_dims,
                                              int8_t *output_data);

/**
 * @brief Get the required buffer size for optimized s8 depthwise convolution
 * function with constraint that in_channel equals out_channel.
 * @param[in]       input_dims   Input (activation) tensor dimensions. Format: [1, H, W, C_IN]
 *                               Batch argument N is not used.
 * @param[in]       filter_dims  Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @return          The function returns required buffer size in bytes
 *
 */
int32_t arm_depthwise_conv_s8_opt_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims);

/**
 * @defgroup FC Fully-connected Layer Functions
 *
 * Collection of fully-connected and matrix multiplication functions.
 *
 * Fully-connected layer is basically a matrix-vector multiplication
 * with bias. The matrix is the weights and the input/output vectors
 * are the activation values. Supported {weight, activation} precisions
 * include {8-bit, 8-bit} and {8-bit, 16-bit}
 *
 *
 */

/**
 * @brief Basic s8 Fully Connected function.
 *
 * @param[in, out] ctx           Function context (e.g. temporary buffer). Check the function
 *                               definition file to see if an additional buffer is required.
 *                               Optional function {API}_get_buffer_size() provides the buffer
 *                               size if an additional buffer is required.
 *                               The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      fc_params     Fully Connected layer parameters.
 *                               Range of fc_params->input_offset  : [-127, 128]
 *                               fc_params->filter_offset : 0
 *                               Range of fc_params->output_offset : [-128, 127]
 * @param[in]      quant_params  Per-tensor quantization info.
 *                               It contains the multiplier and shift values to be applied to the output tensor.
 * @param[in]      input_dims    Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 *                               Input dimension is taken as Nx(H * W * C_IN)
 * @param[in]      input_data    Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims   Two dimensional filter dimensions. Format: [N, C]
 *                               N : accumulation depth and equals (H * W * C_IN) from input_dims
 *                               C : output depth and equals C_OUT in output_dims
 *                               H & W : Not used
 * @param[in]      filter_data   Filter data pointer. Data type: int8
 * @param[in]      bias_dims     Bias tensor dimensions. Format: [C_OUT]
 *                               N, H, W : Not used
 * @param[in]      bias_data     Bias data pointer. Data type: int32
 * @param[in]      output_dims   Output tensor dimensions. Format: [N, C_OUT]
 *                               N : Batches
 *                               C_OUT : Output depth
 *                               H & W : Not used.
 * @param[in, out] output_data    Output data pointer. Data type: int8
 * @return     The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 */
arm_cmsis_nn_status arm_fully_connected_s8(const cmsis_nn_context *ctx,
                                           const cmsis_nn_fc_params *fc_params,
                                           const cmsis_nn_per_tensor_quant_params *quant_params,
                                           const cmsis_nn_dims *input_dims,
                                           const int8_t *input_data,
                                           const cmsis_nn_dims *filter_dims,
                                           const int8_t *filter_data,
                                           const cmsis_nn_dims *bias_dims,
                                           const int32_t *bias_data,
                                           const cmsis_nn_dims *output_dims,
                                           int8_t *output_data);

/**
 * @brief Get size of additional buffer required by arm_fully_connected_s8().
 * @param[in]      filter_dims             dimension of filter
 * @return         The function returns    required buffer size in bytes
 *
 */
int32_t arm_fully_connected_s8_get_buffer_size(const cmsis_nn_dims *filter_dims);

/**
 * @brief Get size of additional buffer required by arm_fully_connected_s8() for processors with DSP extension.
 *        Refer to arm_fully_connected_s8_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_fully_connected_s8_get_buffer_size().
 *
 */
int32_t arm_fully_connected_s8_get_buffer_size_dsp(const cmsis_nn_dims *filter_dims);

/**
 * @brief Get size of additional buffer required by arm_fully_connected_s8() for Arm(R) Helium Architecture case.
 *        Refer to arm_fully_connected_s8_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_fully_connected_s8_get_buffer_size().
 *
 */
int32_t arm_fully_connected_s8_get_buffer_size_mve(const cmsis_nn_dims *filter_dims);

/**
 * @brief Basic s16 Fully Connected function.
 *
 * @param[in, out] ctx           Function context (e.g. temporary buffer). Check the function
 *                               definition file to see if an additional buffer is required.
 *                               Optional function {API}_get_buffer_size() provides the buffer
 *                               size if an additional buffer is required.
 *                               The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      fc_params     Fully Connected layer parameters.
 *                               fc_params->input_offset  : 0
 *                               fc_params->filter_offset : 0
 *                               fc_params->output_offset : 0
 * @param[in]      quant_params  Per-tensor quantization info.
 *                               It contains the multiplier and shift values to be applied to the output tensor.
 * @param[in]      input_dims    Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 *                               Input dimension is taken as Nx(H * W * C_IN)
 * @param[in]      input_data    Input (activation) data pointer. Data type: int16
 * @param[in]      filter_dims   Two dimensional filter dimensions. Format: [N, C]
 *                               N : accumulation depth and equals (H * W * C_IN) from input_dims
 *                               C : output depth and equals C_OUT in output_dims
 *                               H & W : Not used
 * @param[in]      filter_data   Filter data pointer. Data type: int8
 * @param[in]      bias_dims     Bias tensor dimensions. Format: [C_OUT]
 *                               N, H, W : Not used
 * @param[in]      bias_data     Bias data pointer. Data type: int64
 * @param[in]      output_dims   Output tensor dimensions. Format: [N, C_OUT]
 *                               N : Batches
 *                               C_OUT : Output depth
 *                               H & W : Not used.
 * @param[in, out] output_data    Output data pointer. Data type: int16
 * @return     The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 */
arm_cmsis_nn_status arm_fully_connected_s16(const cmsis_nn_context *ctx,
                                            const cmsis_nn_fc_params *fc_params,
                                            const cmsis_nn_per_tensor_quant_params *quant_params,
                                            const cmsis_nn_dims *input_dims,
                                            const int16_t *input_data,
                                            const cmsis_nn_dims *filter_dims,
                                            const int8_t *filter_data,
                                            const cmsis_nn_dims *bias_dims,
                                            const int64_t *bias_data,
                                            const cmsis_nn_dims *output_dims,
                                            int16_t *output_data);

/**
 * @brief Get size of additional buffer required by arm_fully_connected_s16().
 * @param[in]      filter_dims             dimension of filter
 * @return         The function returns    required buffer size in bytes
 *
 */
int32_t arm_fully_connected_s16_get_buffer_size(const cmsis_nn_dims *filter_dims);

/**
 * @brief Get size of additional buffer required by arm_fully_connected_s16() for processors with DSP extension.
 *        Refer to arm_fully_connected_s16_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_fully_connected_s16_get_buffer_size().
 *
 */
int32_t arm_fully_connected_s16_get_buffer_size_dsp(const cmsis_nn_dims *filter_dims);

/**
 * @brief Get size of additional buffer required by arm_fully_connected_s16() for Arm(R) Helium Architecture case.
 *        Refer to arm_fully_connected_s16_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_fully_connected_s16_get_buffer_size().
 *
 */
int32_t arm_fully_connected_s16_get_buffer_size_mve(const cmsis_nn_dims *filter_dims);

/**
 * @defgroup groupElementwise Elementwise Functions
 *
 * Elementwise add and multiplication functions.
 *
 */

/**
 * @brief s8 elementwise add of two vectors
 * @param[in]       input_1_vect        pointer to input vector 1
 * @param[in]       input_2_vect        pointer to input vector 2
 * @param[in]       input_1_offset      offset for input 1. Range: -127 to 128
 * @param[in]       input_1_mult        multiplier for input 1
 * @param[in]       input_1_shift       shift for input 1
 * @param[in]       input_2_offset      offset for input 2. Range: -127 to 128
 * @param[in]       input_2_mult        multiplier for input 2
 * @param[in]       input_2_shift       shift for input 2
 * @param[in]       left_shift          input left shift
 * @param[in,out]   output              pointer to output vector
 * @param[in]       out_offset          output offset.  Range: -128 to 127
 * @param[in]       out_mult            output multiplier
 * @param[in]       out_shift           output shift
 * @param[in]       out_activation_min  minimum value to clamp output to. Min: -128
 * @param[in]       out_activation_max  maximum value to clamp output to. Max: 127
 * @param[in]       block_size          number of samples
 * @return          The function returns    ARM_CMSIS_NN_SUCCESS
 */
arm_cmsis_nn_status arm_elementwise_add_s8(const int8_t *input_1_vect,
                                           const int8_t *input_2_vect,
                                           const int32_t input_1_offset,
                                           const int32_t input_1_mult,
                                           const int32_t input_1_shift,
                                           const int32_t input_2_offset,
                                           const int32_t input_2_mult,
                                           const int32_t input_2_shift,
                                           const int32_t left_shift,
                                           int8_t *output,
                                           const int32_t out_offset,
                                           const int32_t out_mult,
                                           const int32_t out_shift,
                                           const int32_t out_activation_min,
                                           const int32_t out_activation_max,
                                           const int32_t block_size);

/**
 * @brief s16 elementwise add of two vectors
 * @param[in]       input_1_vect        pointer to input vector 1
 * @param[in]       input_2_vect        pointer to input vector 2
 * @param[in]       input_1_offset      offset for input 1. Not used.
 * @param[in]       input_1_mult        multiplier for input 1
 * @param[in]       input_1_shift       shift for input 1
 * @param[in]       input_2_offset      offset for input 2. Not used.
 * @param[in]       input_2_mult        multiplier for input 2
 * @param[in]       input_2_shift       shift for input 2
 * @param[in]       left_shift          input left shift
 * @param[in,out]   output              pointer to output vector
 * @param[in]       out_offset          output offset. Not used.
 * @param[in]       out_mult            output multiplier
 * @param[in]       out_shift           output shift
 * @param[in]       out_activation_min  minimum value to clamp output to. Min: -32768
 * @param[in]       out_activation_max  maximum value to clamp output to. Max: 32767
 * @param[in]       block_size          number of samples
 * @return          The function returns  ARM_CMSIS_NN_SUCCESS
 */
arm_cmsis_nn_status arm_elementwise_add_s16(const int16_t *input_1_vect,
                                            const int16_t *input_2_vect,
                                            const int32_t input_1_offset,
                                            const int32_t input_1_mult,
                                            const int32_t input_1_shift,
                                            const int32_t input_2_offset,
                                            const int32_t input_2_mult,
                                            const int32_t input_2_shift,
                                            const int32_t left_shift,
                                            int16_t *output,
                                            const int32_t out_offset,
                                            const int32_t out_mult,
                                            const int32_t out_shift,
                                            const int32_t out_activation_min,
                                            const int32_t out_activation_max,
                                            const int32_t block_size);

/**
 * @brief s8 elementwise multiplication
 * @param[in]       input_1_vect        pointer to input vector 1
 * @param[in]       input_2_vect        pointer to input vector 2
 * @param[in]       input_1_offset      offset for input 1. Range: -127 to 128
 * @param[in]       input_2_offset      offset for input 2. Range: -127 to 128
 * @param[in,out]   output              pointer to output vector
 * @param[in]       out_offset          output offset. Range: -128 to 127
 * @param[in]       out_mult            output multiplier
 * @param[in]       out_shift           output shift
 * @param[in]       out_activation_min  minimum value to clamp output to. Min: -128
 * @param[in]       out_activation_max  maximum value to clamp output to. Max: 127
 * @param[in]       block_size          number of samples
 * @return          The function returns ARM_CMSIS_NN_SUCCESS
 *
 * @details   Supported framework: TensorFlow Lite micro
 */
arm_cmsis_nn_status arm_elementwise_mul_s8(const int8_t *input_1_vect,
                                           const int8_t *input_2_vect,
                                           const int32_t input_1_offset,
                                           const int32_t input_2_offset,
                                           int8_t *output,
                                           const int32_t out_offset,
                                           const int32_t out_mult,
                                           const int32_t out_shift,
                                           const int32_t out_activation_min,
                                           const int32_t out_activation_max,
                                           const int32_t block_size);

/**
 * @brief s16 elementwise multiplication
 * @param[in]       input_1_vect        pointer to input vector 1
 * @param[in]       input_2_vect        pointer to input vector 2
 * @param[in]       input_1_offset      offset for input 1. Not used.
 * @param[in]       input_2_offset      offset for input 2. Not used.
 * @param[in,out]   output              pointer to output vector
 * @param[in]       out_offset          output offset. Not used.
 * @param[in]       out_mult            output multiplier
 * @param[in]       out_shift           output shift
 * @param[in]       out_activation_min  minimum value to clamp output to. Min: -32768
 * @param[in]       out_activation_max  maximum value to clamp output to. Max: 32767
 * @param[in]       block_size          number of samples
 * @return          The function returns ARM_CMSIS_NN_SUCCESS
 *
 * @details   Supported framework: TensorFlow Lite micro
 */
arm_cmsis_nn_status arm_elementwise_mul_s16(const int16_t *input_1_vect,
                                            const int16_t *input_2_vect,
                                            const int32_t input_1_offset,
                                            const int32_t input_2_offset,
                                            int16_t *output,
                                            const int32_t out_offset,
                                            const int32_t out_mult,
                                            const int32_t out_shift,
                                            const int32_t out_activation_min,
                                            const int32_t out_activation_max,
                                            const int32_t block_size);

/**
 * @defgroup Acti Activation Functions
 *
 * Perform activation layers, including ReLU (Rectified Linear Unit),
 * sigmoid and tanh
 *
 */

/**
 * @brief Q7 RELU function
 * @param[in,out]   data        pointer to input
 * @param[in]       size        number of elements
 */
void arm_relu_q7(int8_t *data, uint16_t size);

/**
 * @brief s8 ReLU6 function
 * @param[in,out]   data        pointer to input
 * @param[in]       size        number of elements
 */
void arm_relu6_s8(int8_t *data, uint16_t size);

/**
 * @brief Q15 RELU function
 * @param[in,out]   data        pointer to input
 * @param[in]       size        number of elements
 */
void arm_relu_q15(int16_t *data, uint16_t size);

/**
 * @brief s16 neural network activation function using direct table look-up
 * @param[in]       input        pointer to input data
 * @param[out]      output      pointer to output
 * @param[in]       size        number of elements
 * @param[in]       left_shift  bit-width of the integer part, assume to be smaller than 3
 * @param[in]       type        type of activation functions
 *
 * @details Supported framework: TensorFlow Lite for Microcontrollers.
 * This activation function must be bit precise congruent with the corresponding TFLM tanh and sigmoid actication
 * functions
 */
void arm_nn_activation_s16(const int16_t *input,
                           int16_t *output,
                           const uint16_t size,
                           const uint16_t left_shift,
                           const arm_nn_activation_type type);

/**
 * @defgroup Pooling Pooling Functions
 *
 * Perform max and average pooling operations
 *
 */

/**
 * @brief s8 average pooling function.
 *
 * @param[in, out] ctx          Function context (e.g. temporary buffer). Check the function
 *                              definition file to see if an additional buffer is required.
 *                              Optional function {API}_get_buffer_size() provides the buffer
 *                              size if an additional buffer is required.
 *                              The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      pool_params  Pooling parameters
 * @param[in]      input_dims   Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                              Argument 'N' is not used.
 * @param[in]      input_data   Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims  Filter tensor dimensions. Format: [H, W]
 *                              Argument N and C are not used.
 * @param[in]      output_dims  Output tensor dimensions. Format: [H, W, C_OUT]
 *                              Argument N is not used.
 *                              C_OUT equals C_IN.
 * @param[in, out] output_data Output data pointer. Data type: int8
 * @return                     The function returns
 *                             <code>ARM_CMSIS_NN_SUCCESS</code> - Successful operation
 *
 * @details
 *    - Supported Framework: TensorFlow Lite
 *
 */
arm_cmsis_nn_status arm_avgpool_s8(const cmsis_nn_context *ctx,
                                   const cmsis_nn_pool_params *pool_params,
                                   const cmsis_nn_dims *input_dims,
                                   const int8_t *input_data,
                                   const cmsis_nn_dims *filter_dims,
                                   const cmsis_nn_dims *output_dims,
                                   int8_t *output_data);

/**
 * @brief Get the required buffer size for S8 average pooling function
 * @param[in]       dim_dst_width         output tensor dimension
 * @param[in]       ch_src                number of input tensor channels
 * @return          The function returns required buffer size in bytes
 *
 */
int32_t arm_avgpool_s8_get_buffer_size(const int dim_dst_width, const int ch_src);

/**
 * @brief Get the required buffer size for S8 average pooling function for processors with DSP extension.
 *        Refer to arm_avgpool_s8_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_avgpool_s8_get_buffer_size().
 *
 */
int32_t arm_avgpool_s8_get_buffer_size_dsp(const int dim_dst_width, const int ch_src);

/**
 * @brief Get the required buffer size for S8 average pooling function for Arm(R) Helium Architecture case.
 *        Refer to arm_avgpool_s8_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_avgpool_s8_get_buffer_size().
 *
 */
int32_t arm_avgpool_s8_get_buffer_size_mve(const int dim_dst_width, const int ch_src);

/**
 * @brief s16 average pooling function.
 *
 * @param[in, out] ctx          Function context (e.g. temporary buffer). Check the function
 *                              definition file to see if an additional buffer is required.
 *                              Optional function {API}_get_buffer_size() provides the buffer
 *                              size if an additional buffer is required.
 *                              The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      pool_params  Pooling parameters
 * @param[in]      input_dims   Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                              Argument 'N' is not used.
 * @param[in]      input_data   Input (activation) data pointer. Data type: int16
 * @param[in]      filter_dims  Filter tensor dimensions. Format: [H, W]
 *                              Argument N and C are not used.
 * @param[in]      output_dims  Output tensor dimensions. Format: [H, W, C_OUT]
 *                              Argument N is not used.
 *                              C_OUT equals C_IN.
 * @param[in, out] output_data  Output data pointer. Data type: int16
 * @return                        The function returns
 *                                    <code>ARM_CMSIS_NN_SUCCESS</code> - Successful operation
 *                                    <code>ARM_CMSIS_NN_ARG_ERROR</code> - In case of invalid arguments
 *
 * @details
 *    - Supported Framework: TensorFlow Lite
 *
 */
arm_cmsis_nn_status arm_avgpool_s16(const cmsis_nn_context *ctx,
                                    const cmsis_nn_pool_params *pool_params,
                                    const cmsis_nn_dims *input_dims,
                                    const int16_t *input_data,
                                    const cmsis_nn_dims *filter_dims,
                                    const cmsis_nn_dims *output_dims,
                                    int16_t *output_data);

/**
 * @brief Get the required buffer size for S16 average pooling function
 * @param[in]       dim_dst_width         output tensor dimension
 * @param[in]       ch_src                number of input tensor channels
 * @return          The function returns required buffer size in bytes
 *
 */
int32_t arm_avgpool_s16_get_buffer_size(const int dim_dst_width, const int ch_src);

/**
 * @brief Get the required buffer size for S16 average pooling function for processors with DSP extension.
 *        Refer to arm_avgpool_s16_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_avgpool_s16_get_buffer_size().
 *
 */
int32_t arm_avgpool_s16_get_buffer_size_dsp(const int dim_dst_width, const int ch_src);

/**
 * @brief Get the required buffer size for S16 average pooling function for Arm(R) Helium Architecture case.
 *        Refer to arm_avgpool_s16_get_buffer_size() for function argument details.
 *
 * @note       Intended for compilation on Host. If compiling for an Arm target, use
 *             arm_avgpool_s16_get_buffer_size().
 *
 */
int32_t arm_avgpool_s16_get_buffer_size_mve(const int dim_dst_width, const int ch_src);

/**
 * @brief s8 max pooling function.
 *
 * @param[in, out] ctx          Function context (e.g. temporary buffer). Check the function
 *                              definition file to see if an additional buffer is required.
 *                              Optional function {API}_get_buffer_size() provides the buffer
 *                              size if an additional buffer is required.
 *                              The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      pool_params  Pooling parameters
 * @param[in]      input_dims   Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                              Argument 'N' is not used.
 * @param[in]      input_data   Input (activation) data pointer. The input tensor must not
 *                              overlap with the output tensor. Data type: int8
 * @param[in]      filter_dims  Filter tensor dimensions. Format: [H, W]
 *                              Argument N and C are not used.
 * @param[in]      output_dims  Output tensor dimensions. Format: [H, W, C_OUT]
 *                              Argument N is not used.
 *                              C_OUT equals C_IN.
 * @param[in, out] output_data    Output data pointer. Data type: int8
 * @return                        The function returns
 *                                    <code>ARM_CMSIS_NN_SUCCESS</code> - Successful operation
 *
 * @details
 *    - Supported Framework: TensorFlow Lite
 *
 */
arm_cmsis_nn_status arm_max_pool_s8(const cmsis_nn_context *ctx,
                                    const cmsis_nn_pool_params *pool_params,
                                    const cmsis_nn_dims *input_dims,
                                    const int8_t *input_data,
                                    const cmsis_nn_dims *filter_dims,
                                    const cmsis_nn_dims *output_dims,
                                    int8_t *output_data);

/**
 * @brief s16 max pooling function.
 *
 * @param[in, out] ctx          Function context (e.g. temporary buffer). Check the function
 *                              definition file to see if an additional buffer is required.
 *                              Optional function {API}_get_buffer_size() provides the buffer
 *                              size if an additional buffer is required.
 *                              The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]      pool_params  Pooling parameters
 * @param[in]      input_dims   Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                              Argument 'N' is not used.
 * @param[in]      src          Input (activation) data pointer. The input tensor must not
 *                              overlap with the output tensor. Data type: int16
 * @param[in]      filter_dims  Filter tensor dimensions. Format: [H, W]
 *                              Argument N and C are not used.
 * @param[in]      output_dims  Output tensor dimensions. Format: [H, W, C_OUT]
 *                              Argument N is not used.
 *                              C_OUT equals C_IN.
 * @param[in, out] dst          Output data pointer. Data type: int16
 * @return                        The function returns
 *                                    <code>ARM_CMSIS_NN_SUCCESS</code> - Successful operation
 *
 * @details
 *    - Supported Framework: TensorFlow Lite
 *
 */
arm_cmsis_nn_status arm_max_pool_s16(const cmsis_nn_context *ctx,
                                     const cmsis_nn_pool_params *pool_params,
                                     const cmsis_nn_dims *input_dims,
                                     const int16_t *src,
                                     const cmsis_nn_dims *filter_dims,
                                     const cmsis_nn_dims *output_dims,
                                     int16_t *dst);

/**
 * @defgroup Softmax Softmax Functions
 *
 *
 */

/**
 * @brief S8 softmax function
 * @param[in]  input     Pointer to the input tensor
 * @param[in]  num_rows  Number of rows in the input tensor
 * @param[in]  row_size  Number of elements in each input row
 * @param[in]  mult      Input quantization multiplier
 * @param[in]  shift     Input quantization shift within the range [0, 31]
 * @param[in]  diff_min  Minimum difference with max in row. Used to check if
 *                       the quantized exponential operation can be performed
 * @param[out] output    Pointer to the output tensor
 *
 * @note Supported framework: TensorFlow Lite micro (bit-accurate)
 *
 */
void arm_softmax_s8(const int8_t *input,
                    const int32_t num_rows,
                    const int32_t row_size,
                    const int32_t mult,
                    const int32_t shift,
                    const int32_t diff_min,
                    int8_t *output);

/**
 * @brief S8 to s16 softmax function
 * @param[in]  input     Pointer to the input tensor
 * @param[in]  num_rows  Number of rows in the input tensor
 * @param[in]  row_size  Number of elements in each input row
 * @param[in]  mult      Input quantization multiplier
 * @param[in]  shift     Input quantization shift within the range [0, 31]
 * @param[in]  diff_min  Minimum difference with max in row. Used to check if
 *                       the quantized exponential operation can be performed
 * @param[out] output    Pointer to the output tensor
 *
 * @note Supported framework: TensorFlow Lite micro (bit-accurate)
 *
 */
void arm_softmax_s8_s16(const int8_t *input,
                        const int32_t num_rows,
                        const int32_t row_size,
                        const int32_t mult,
                        const int32_t shift,
                        const int32_t diff_min,
                        int16_t *output);

/**
 * @brief S16 softmax function
 * @param[in]  input           Pointer to the input tensor
 * @param[in]  num_rows        Number of rows in the input tensor
 * @param[in]  row_size        Number of elements in each input row
 * @param[in]  mult            Input quantization multiplier
 * @param[in]  shift           Input quantization shift within the range [0, 31]
 * @param[in]  softmax_params  Softmax s16 layer parameters with two pointers to LUTs speficied below.
 *                             For indexing the high 9 bits are used and 7 remaining for interpolation.
 *                             That means 512 entries for the 9-bit indexing and 1 extra for interpolation, i.e. 513
 *                             values for each LUT.
 *                             - Lookup table for exp(x), where x uniform distributed between [-10.0 , 0.0]
 *                             - Lookup table for 1 / (1 + x), where x uniform distributed between [0.0 , 1.0]
 * @param[out] output          Pointer to the output tensor
 * @return                        The function returns
 *                                    <code>ARM_CMSIS_NN_ARG_ERROR</code> Argument error check failed
 *                                    <code>ARM_CMSIS_NN_SUCCESS</code> - Successful operation
 *
 * @note Supported framework: TensorFlow Lite micro (bit-accurate)
 *
 */
arm_cmsis_nn_status arm_softmax_s16(const int16_t *input,
                                    const int32_t num_rows,
                                    const int32_t row_size,
                                    const int32_t mult,
                                    const int32_t shift,
                                    const cmsis_nn_softmax_lut_s16 *softmax_params,
                                    int16_t *output);

/**
 * @brief U8 softmax function
 * @param[in]  input     Pointer to the input tensor
 * @param[in]  num_rows  Number of rows in the input tensor
 * @param[in]  row_size  Number of elements in each input row
 * @param[in]  mult      Input quantization multiplier
 * @param[in]  shift     Input quantization shift within the range [0, 31]
 * @param[in]  diff_min  Minimum difference with max in row. Used to check if
 *                       the quantized exponential operation can be performed
 * @param[out] output    Pointer to the output tensor
 *
 * @note Supported framework: TensorFlow Lite micro (bit-accurate)
 *
 */

void arm_softmax_u8(const uint8_t *input,
                    const int32_t num_rows,
                    const int32_t row_size,
                    const int32_t mult,
                    const int32_t shift,
                    const int32_t diff_min,
                    uint8_t *output);

/**
 * @defgroup Reshape Reshape Functions
 *
 */

/**
 * @brief Reshape a s8 vector into another with different shape
 * @param[in]  input      points to the s8 input vector
 * @param[out] output     points to the s8 output vector
 * @param[in]  total_size total size of the input and output vectors in bytes
 *
 * @note The output is expected to be in a memory area that does not overlap with the input's
 *
 */
void arm_reshape_s8(const int8_t *input, int8_t *output, const uint32_t total_size);

/**
 * @defgroup Concatenation Concatenation Functions
 *
 */

/**
 * @brief int8/uint8 concatenation function to be used for concatenating N-tensors along the X axis
 *        This function should be called for each input tensor to concatenate. The argument offset_x
 *        will be used to store the input tensor in the correct position in the output tensor
 *
 *        i.e.    offset_x = 0
 *                for(i = 0 i < num_input_tensors; ++i)
 *                {
 *                    arm_concatenation_s8_x(&input[i], ..., &output, ..., ..., offset_x)
 *                    offset_x += input_x[i]
 *                }
 *
 *        This function assumes that the output tensor has:
 *        -# The same height of the input tensor
 *        -# The same number of channels of the input tensor
 *        -# The same batch size of the input tensor
 *
 *        Unless specified otherwise, arguments are mandatory.
 *
 * @note This function, data layout independent, can be used to concatenate either int8 or uint8 tensors because it
 *      does not involve any arithmetic operation
 *
 * @param[in]  input    Pointer to input tensor. Input tensor must not overlap with the output tensor.
 * @param[in]  input_x  Width of input tensor
 * @param[in]  input_y  Height of input tensor
 * @param[in]  input_z  Channels in input tensor
 * @param[in]  input_w  Batch size in input tensor
 * @param[out] output   Pointer to output tensor. Expected to be at least
 *                          (input_x * input_y * input_z * input_w) + offset_x
 *                      bytes.
 * @param[in]  output_x Width of output tensor
 * @param[in]  offset_x The offset (in number of elements) on the X axis to start concatenating the input tensor
 *                      It is user responsibility to provide the correct value
 *
 * <b> Input constraints</b>
 * offset_x is less than output_x
 *
 */
void arm_concatenation_s8_x(const int8_t *input,
                            const uint16_t input_x,
                            const uint16_t input_y,
                            const uint16_t input_z,
                            const uint16_t input_w,
                            int8_t *output,
                            const uint16_t output_x,
                            const uint32_t offset_x);

/**
 * @brief int8/uint8 concatenation function to be used for concatenating N-tensors along the Y axis
 *        This function should be called for each input tensor to concatenate. The argument offset_y
 *        will be used to store the input tensor in the correct position in the output tensor
 *
 *        i.e.    offset_y = 0
 *                for(i = 0 i < num_input_tensors; ++i)
 *                {
 *                    arm_concatenation_s8_y(&input[i], ..., &output, ..., ..., offset_y)
 *                    offset_y += input_y[i]
 *                }
 *
 *        This function assumes that the output tensor has:
 *        -# The same width of the input tensor
 *        -# The same number of channels of the input tensor
 *        -# The same batch size of the input tensor
 *
 *        Unless specified otherwise, arguments are mandatory.
 *
 * @note This function, data layout independent, can be used to concatenate either int8 or uint8 tensors because it
 *       does not involve any arithmetic operation
 *
 * @param[in]  input    Pointer to input tensor. Input tensor must not overlap with the output tensor.
 * @param[in]  input_x  Width of input tensor
 * @param[in]  input_y  Height of input tensor
 * @param[in]  input_z  Channels in input tensor
 * @param[in]  input_w  Batch size in input tensor
 * @param[out] output   Pointer to output tensor. Expected to be at least
 *                          (input_z * input_w * input_x * input_y) + offset_y
 *                      bytes.
 * @param[in]  output_y Height of output tensor
 * @param[in]  offset_y The offset on the Y axis to start concatenating the input tensor
 *                      It is user responsibility to provide the correct value
 *
 * <b> Input constraints</b>
 * offset_y is less than output_y
 *
 */
void arm_concatenation_s8_y(const int8_t *input,
                            const uint16_t input_x,
                            const uint16_t input_y,
                            const uint16_t input_z,
                            const uint16_t input_w,
                            int8_t *output,
                            const uint16_t output_y,
                            const uint32_t offset_y);

/**
 * @brief int8/uint8 concatenation function to be used for concatenating N-tensors along the Z axis
 *        This function should be called for each input tensor to concatenate. The argument offset_z
 *        will be used to store the input tensor in the correct position in the output tensor
 *
 *        i.e.    offset_z = 0
 *                for(i = 0 i < num_input_tensors; ++i)
 *                {
 *                    arm_concatenation_s8_z(&input[i], ..., &output, ..., ..., offset_z)
 *                    offset_z += input_z[i]
 *                }
 *
 *        This function assumes that the output tensor has:
 *        -# The same width of the input tensor
 *        -# The same height of the input tensor
 *        -# The same batch size of the input tensor
 *
 *        Unless specified otherwise, arguments are mandatory.
 *
 * @note This function, data layout independent, can be used to concatenate either int8 or uint8 tensors because it
 *       does not involve any arithmetic operation
 *
 * @param[in]  input    Pointer to input tensor. Input tensor must not overlap with output tensor.
 * @param[in]  input_x  Width of input tensor
 * @param[in]  input_y  Height of input tensor
 * @param[in]  input_z  Channels in input tensor
 * @param[in]  input_w  Batch size in input tensor
 * @param[out] output   Pointer to output tensor. Expected to be at least
 *                          (input_x * input_y * input_z * input_w) + offset_z
 *                      bytes.
 * @param[in]  output_z Channels in output tensor
 * @param[in]  offset_z The offset on the Z axis to start concatenating the input tensor
 *                      It is user responsibility to provide the correct value
 *
 * <b> Input constraints</b>
 * offset_z is less than output_z
 *
 */
void arm_concatenation_s8_z(const int8_t *input,
                            const uint16_t input_x,
                            const uint16_t input_y,
                            const uint16_t input_z,
                            const uint16_t input_w,
                            int8_t *output,
                            const uint16_t output_z,
                            const uint32_t offset_z);

/**
 * @brief int8/uint8 concatenation function to be used for concatenating N-tensors along the W axis (Batch size)
 *        This function should be called for each input tensor to concatenate. The argument offset_w
 *        will be used to store the input tensor in the correct position in the output tensor
 *
 *        i.e.    offset_w = 0
 *                for(i = 0 i < num_input_tensors; ++i)
 *                {
 *                    arm_concatenation_s8_w(&input[i], ..., &output, ..., ..., offset_w)
 *                    offset_w += input_w[i]
 *                }
 *
 *        This function assumes that the output tensor has:
 *        -# The same width of the input tensor
 *        -# The same height of the input tensor
 *        -# The same number o channels of the input tensor
 *
 *        Unless specified otherwise, arguments are mandatory.
 *
 * @note This function, data layout independent, can be used to concatenate either int8 or uint8 tensors because it
 *       does not involve any arithmetic operation
 *
 * @param[in]  input    Pointer to input tensor
 * @param[in]  input_x  Width of input tensor
 * @param[in]  input_y  Height of input tensor
 * @param[in]  input_z  Channels in input tensor
 * @param[in]  input_w  Batch size in input tensor
 * @param[out] output   Pointer to output tensor. Expected to be at least
 *                          input_x * input_y * input_z * input_w
 *                      bytes.
 * @param[in]  offset_w The offset on the W axis to start concatenating the input tensor
 *                      It is user responsibility to provide the correct value
 *
 */
void arm_concatenation_s8_w(const int8_t *input,
                            const uint16_t input_x,
                            const uint16_t input_y,
                            const uint16_t input_z,
                            const uint16_t input_w,
                            int8_t *output,
                            const uint32_t offset_w);
/**
 * @defgroup SVDF SVDF Functions
 *
 */

/**
 * @brief s8 SVDF function with 8 bit state tensor and 8 bit time weights
 *
 * @param[in]   input_ctx             Temporary scratch buffer
 *                                    The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]   output_ctx            Temporary output scratch buffer
 *                                    The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]   svdf_params           SVDF Parameters
 *                                    Range of svdf_params->input_offset  : [-128, 127]
 *                                    Range of svdf_params->output_offset  : [-128, 127]
 * @param[in]   input_quant_params    Input quantization parameters
 * @param[in]   output_quant_params   Output quantization parameters
 * @param[in]   input_dims            Input tensor dimensions
 * @param[in]   input_data            Pointer to input tensor
 * @param[in]   state_dims            State tensor dimensions
 * @param[in]   state_data            Pointer to state tensor
 * @param[in]   weights_feature_dims  Weights (feature) tensor dimensions
 * @param[in]   weights_feature_data  Pointer to the weights (feature) tensor
 * @param[in]   weights_time_dims     Weights (time) tensor dimensions
 * @param[in]   weights_time_data     Pointer to the weights (time) tensor
 * @param[in]   bias_dims             Bias tensor dimensions
 * @param[in]   bias_data             Pointer to bias tensor
 * @param[in]   output_dims           Output tensor dimensions
 * @param[out]  output_data           Pointer to the output tensor
 *
 * @return     The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 * @details
 *    1. Supported framework: TensorFlow Lite micro
 */
arm_cmsis_nn_status arm_svdf_s8(const cmsis_nn_context *input_ctx,
                                const cmsis_nn_context *output_ctx,
                                const cmsis_nn_svdf_params *svdf_params,
                                const cmsis_nn_per_tensor_quant_params *input_quant_params,
                                const cmsis_nn_per_tensor_quant_params *output_quant_params,
                                const cmsis_nn_dims *input_dims,
                                const int8_t *input_data,
                                const cmsis_nn_dims *state_dims,
                                int8_t *state_data,
                                const cmsis_nn_dims *weights_feature_dims,
                                const int8_t *weights_feature_data,
                                const cmsis_nn_dims *weights_time_dims,
                                const int8_t *weights_time_data,
                                const cmsis_nn_dims *bias_dims,
                                const int32_t *bias_data,
                                const cmsis_nn_dims *output_dims,
                                int8_t *output_data);

/**
 * @brief s8 SVDF function with 16 bit state tensor and 16 bit time weights
 *
 * @param[in]   input_ctx             Temporary scratch buffer
 *                                    The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]   output_ctx            Temporary output scratch buffer
 *                                    The caller is expected to clear the buffer ,if applicable, for security reasons.
 * @param[in]   svdf_params           SVDF Parameters
 *                                    Range of svdf_params->input_offset  : [-128, 127]
 *                                    Range of svdf_params->output_offset  : [-128, 127]
 * @param[in]   input_quant_params    Input quantization parameters
 * @param[in]   output_quant_params   Output quantization parameters
 * @param[in]   input_dims            Input tensor dimensions
 * @param[in]   input_data            Pointer to input tensor
 * @param[in]   state_dims            State tensor dimensions
 * @param[in]   state_data            Pointer to state tensor
 * @param[in]   weights_feature_dims  Weights (feature) tensor dimensions
 * @param[in]   weights_feature_data  Pointer to the weights (feature) tensor
 * @param[in]   weights_time_dims     Weights (time) tensor dimensions
 * @param[in]   weights_time_data     Pointer to the weights (time) tensor
 * @param[in]   bias_dims             Bias tensor dimensions
 * @param[in]   bias_data             Pointer to bias tensor
 * @param[in]   output_dims           Output tensor dimensions
 * @param[out]  output_data           Pointer to the output tensor
 *
 * @return     The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 * @details
 *    1. Supported framework: TensorFlow Lite micro
 */
arm_cmsis_nn_status arm_svdf_state_s16_s8(const cmsis_nn_context *input_ctx,
                                          const cmsis_nn_context *output_ctx,
                                          const cmsis_nn_svdf_params *svdf_params,
                                          const cmsis_nn_per_tensor_quant_params *input_quant_params,
                                          const cmsis_nn_per_tensor_quant_params *output_quant_params,
                                          const cmsis_nn_dims *input_dims,
                                          const int8_t *input_data,
                                          const cmsis_nn_dims *state_dims,
                                          int16_t *state_data,
                                          const cmsis_nn_dims *weights_feature_dims,
                                          const int8_t *weights_feature_data,
                                          const cmsis_nn_dims *weights_time_dims,
                                          const int16_t *weights_time_data,
                                          const cmsis_nn_dims *bias_dims,
                                          const int32_t *bias_data,
                                          const cmsis_nn_dims *output_dims,
                                          int8_t *output_data);

/**
 * @defgroup LSTM LSTM Layer Functions
 *
 */

/**
 * @brief LSTM unidirectional function with 8 bit input and output and 16 bit gate output
 * Peephole connections, projection, clipping, combined input/forget gate and layer normalization are not supported.
 *
 * @param[in]   scratch_buffers                 Struct containing scratch buffers
 *                                              Expected size for each scratch buffer is
 *                                              lstm_dims->num_batches * lstm_dims->num_outputs.
 * @param[in]   input_data                      Pointer to input data
 * @param[in]   lstm_dims                       LSTM input parameters related to dimensions
 * @param[in]   input_to_input_weights          Input to input weights
 * @param[in]   input_to_forget_weights         Input to forget weights
 * @param[in]   input_to_cell_weights           Input to cell weights
 * @param[in]   input_to_output_weights         Input to output weights
 * @param[in]   recurrent_to_input_weights      Recurrent to input weights
 * @param[in]   recurrent_to_forget_weights     Recurrent to forget weights
 * @param[in]   recurrent_to_cell_weights       Recurrent to cell weights
 * @param[in]   recurrent_to_output_weights     Recurrent to output weights
 * @param[in]   cell_to_input_weights           Cell to input weights. Not used.
 * @param[in]   cell_to_forget_weights          Cell to forget weights. Not used.
 * @param[in]   cell_to_output_weights          Cell to output weights. Not used.
 * @param[in]   projection_weights              Projection weights. Not used.
 * @param[in]   lstm                            LSTM parameters. See struct declaration
 * @param[in]   output_state                    Pointer to (recurrent) output state
 * @param[in]   cell_state                      Pointer to cell state
 * @param[in]   output_data                     Pointer to output state
 *
 * @note Following assumptions are done based on LSTM functionality as supported by
 *       Keras version 2.9.0 at the time of development. As stated here,
 *       https://github.com/tensorflow/community/blob/master/rfcs/20180920-unify-rnn-interface.md
 *       Keras's LSTMCell is equivalent to TensorFlow's BasicLSTMCell,
 *       which does not support peephole, clipping or projection.
 *       Layer normalization and combined input/forget gate are not supported either.
 *
 *       1 Input to input weight can not be nullptr. Otherwise nullptr for combined input/forgat gate.
 *       2 Cell weights are not used and should be nullptr. Otherwise needed for peephole connections.
 *       3 Projection weight is not used and should be nullpr. Otherwise needed for projection.
 *
 * @return     The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 * @details
 *    1. Supported framework: TensorFlow Lite micro
 *
 */
arm_cmsis_nn_status arm_lstm_unidirectional_s16_s8(cmsis_nn_lstm_context *scratch_buffers,
                                                   const int8_t *input_data,
                                                   const cmsis_nn_lstm_dims *lstm_dims,
                                                   const int8_t *input_to_input_weights,
                                                   const int8_t *input_to_forget_weights,
                                                   const int8_t *input_to_cell_weights,
                                                   const int8_t *input_to_output_weights,
                                                   const int8_t *recurrent_to_input_weights,
                                                   const int8_t *recurrent_to_forget_weights,
                                                   const int8_t *recurrent_to_cell_weights,
                                                   const int8_t *recurrent_to_output_weights,
                                                   const int16_t *cell_to_input_weights,
                                                   const int16_t *cell_to_forget_weights,
                                                   const int16_t *cell_to_output_weights,
                                                   const int8_t *projection_weights,
                                                   const cmsis_nn_lstm_params *lstm,
                                                   int8_t *output_state,
                                                   int16_t *cell_state,
                                                   int8_t *output_data);

#ifdef __cplusplus
}
#endif

#endif


#ifndef _ARM_NNSUPPORTFUNCTIONS_H_
#define _ARM_NNSUPPORTFUNCTIONS_H_

// #include "Internal/arm_nn_compiler.h"

#ifndef ARM_NN_COMPILER_H
#define ARM_NN_COMPILER_H

/**
 *
 * @brief Arm C-Language Extension(ACLE) Includes
 *
 */

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)

    #ifndef __ASM
        #define __ASM __asm
    #endif
    #ifndef __INLINE
        #define __INLINE __inline
    #endif
    #ifndef __STATIC_INLINE
        #define __STATIC_INLINE static __inline
    #endif
    #ifndef __STATIC_FORCEINLINE
        #define __STATIC_FORCEINLINE __attribute__((always_inline)) static __inline
    #endif
    #ifndef __RESTRICT
        #define __RESTRICT __restrict
    #endif

#elif defined(__ICCARM__)

    #warning IAR support is not tested
    #ifndef __ASM
        #define __ASM __asm
    #endif
    #ifndef __INLINE
        #define __INLINE inline
    #endif
    #ifndef __STATIC_INLINE
        #define __STATIC_INLINE static inline
    #endif
    #ifndef __FORCEINLINE
        #define __FORCEINLINE _Pragma("inline=forced")
    #endif
    #ifndef __STATIC_FORCEINLINE
        #define __STATIC_FORCEINLINE __FORCEINLINE __STATIC_INLINE
    #endif

#elif defined(_MSC_VER)

    // Build for non Arm Cortex-M processors is not tested or supported.
    // Use this section to stub any macros or intrinsics
    #warning Unsupported compiler
    #ifndef __STATIC_FORCEINLINE
        #define __STATIC_FORCEINLINE static __forceinline
    #endif
    #ifndef __STATIC_INLINE
        #define __STATIC_INLINE static __inline
    #endif
    #ifndef __ALIGNED
        #define __ALIGNED(x) __declspec(align(x))
    #endif

#elif defined(__GNUC__)

    #ifndef __ASM
        #define __ASM __asm
    #endif
    #ifndef __INLINE
        #define __INLINE inline
    #endif
    #ifndef __STATIC_INLINE
        #define __STATIC_INLINE static inline
    #endif
    #ifndef __STATIC_FORCEINLINE
        #define __STATIC_FORCEINLINE __attribute__((always_inline)) static inline
    #endif
    #ifndef __RESTRICT
        #define __RESTRICT __restrict
    #endif

#else

    #error Unsupported compiler. Add support as needed

#endif

/**
 *
 * @brief Compiler specific diagnostic adjustment / fixes if applicable
 *
 */

// Note: __ARM_ARCH is used with M-profile architecture as the target here.
#if defined(__GNUC__)
    #if (__GNUC__ == 12 && (__GNUC_MINOR__ <= 2)) && defined(__ARM_ARCH)
        // Workaround for 'Internal Compiler Error' on Arm GNU Toolchain rel 12.2.x
        // https://gcc.gnu.org/pipermail/gcc-patches/2022-December/607963.html
        #define ARM_GCC_12_2_ICE
    #endif
#endif

#if ((__ARM_FEATURE_MVE & 3) == 3) || (__ARM_FEATURE_MVE & 1)
    #include <arm_mve.h>
#endif

#if defined(__ARM_ARCH) || defined(__ARM_ACLE)
    #include <arm_acle.h>
#endif

/**
 *
 * @brief ACLE and Intrinsics
 *
 */

// Note: Have __GNUC__, that is used to check for GCC , checks at the end
// as __GNUC__ is defined by non-GCC compilers as well

/* Common intrinsics for all architectures */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) || defined(__ICCARM__)
    #define CLZ __clz
#elif defined(__GNUC__)
/**
  \brief   Count leading zeros
  \details Counts the number of leading zeros of a data value.
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
__STATIC_FORCEINLINE uint8_t CLZ(uint32_t value)
{
    /* Even though __builtin_clz produces a CLZ instruction on ARM, formally
       __builtin_clz(0) is undefined behaviour, so handle this case specially.
       This guarantees Arm-compatible results if compiling on a non-Arm
       target, and ensures the compiler doesn't decide to activate any
       optimisations using the logic "value was passed to __builtin_clz, so it
       is non-zero".
       ARM GCC 7.3 and possibly earlier will optimise this test away, leaving a
       single CLZ instruction.
     */
    if (value == 0U)
    {
        return 32U;
    }
    return __builtin_clz(value);
}
#endif

// ACLE intrinsics under groups __ARM_FEATURE_QBIT, __ARM_FEATURE_DSP , __ARM_FEATURE_SAT, __ARM_FEATURE_SIMD32

// Note: Just __ARM_FEATURE_DSP is checked to collect all intrinsics from the above mentioned groups

#if (defined(__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1))

    // Common intrinsics
    #define SMLABB __smlabb
    #define SMLATT __smlatt
    #define QADD __qadd
    #define QSUB8 __qsub8
    #define QSUB16 __qsub16
    #define SADD16 __sadd16

    // Compiler specifc variants of intrinsics. Create a new section or file for IAR if needed
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) || defined(__ICCARM__)

        #define SMULBB __smulbb
        #define SMULTT __smultt
        #define ROR __ror
        #define SXTB16 __sxtb16
        #define SXTAB16 __sxtab16
        #define SXTB16_RORn(ARG1, ARG2) SXTB16(ROR(ARG1, ARG2))
        #define SXTAB16_RORn(ARG1, ARG2, ARG3) SXTAB16(ARG1, ROR(ARG2, ARG3))
        #define SMLAD __smlad
        // PKH<XY> translates into pkh<xy> on AC6
        #define PKHBT(ARG1, ARG2, ARG3)                                                                                \
            (((((uint32_t)(ARG1))) & 0x0000FFFFUL) | ((((uint32_t)(ARG2)) << (ARG3)) & 0xFFFF0000UL))
        #define PKHTB(ARG1, ARG2, ARG3)                                                                                \
            (((((uint32_t)(ARG1))) & 0xFFFF0000UL) | ((((uint32_t)(ARG2)) >> (ARG3)) & 0x0000FFFFUL))

    #elif defined(__GNUC__)

        #define PKHBT(ARG1, ARG2, ARG3)                                                                                \
            __extension__({                                                                                            \
                uint32_t __RES, __ARG1 = (ARG1), __ARG2 = (ARG2);                                                      \
                __ASM("pkhbt %0, %1, %2, lsl %3" : "=r"(__RES) : "r"(__ARG1), "r"(__ARG2), "I"(ARG3));                 \
                __RES;                                                                                                 \
            })
        #define PKHTB(ARG1, ARG2, ARG3)                                                                                \
            __extension__({                                                                                            \
                uint32_t __RES, __ARG1 = (ARG1), __ARG2 = (ARG2);                                                      \
                if (ARG3 == 0)                                                                                         \
                    __ASM("pkhtb %0, %1, %2" : "=r"(__RES) : "r"(__ARG1), "r"(__ARG2));                                \
                else                                                                                                   \
                    __ASM("pkhtb %0, %1, %2, asr %3" : "=r"(__RES) : "r"(__ARG1), "r"(__ARG2), "I"(ARG3));             \
                __RES;                                                                                                 \
            })

__STATIC_FORCEINLINE uint32_t SXTAB16(uint32_t op1, uint32_t op2)
{
    uint32_t result;

    __ASM("sxtab16 %0, %1, %2" : "=r"(result) : "r"(op1), "r"(op2));
    return (result);
}

__STATIC_FORCEINLINE uint32_t SXTB16(uint32_t op1)
{
    uint32_t result;

    __ASM("sxtb16 %0, %1" : "=r"(result) : "r"(op1));
    return (result);
}

// __smlad is defined by GCC, but results in a performance drop(Tested on Arm GNU Toolchain version 11.x and 12.x)
__STATIC_FORCEINLINE uint32_t SMLAD(uint32_t op1, uint32_t op2, uint32_t op3)
{
    uint32_t result;

    __ASM volatile("smlad %0, %1, %2, %3" : "=r"(result) : "r"(op1), "r"(op2), "r"(op3));
    return (result);
}

__STATIC_FORCEINLINE uint32_t ROR(uint32_t op1, uint32_t op2)
{
    op2 %= 32U;
    if (op2 == 0U)
    {
        return op1;
    }
    return (op1 >> op2) | (op1 << (32U - op2));
}

__STATIC_FORCEINLINE uint32_t SXTB16_RORn(uint32_t op1, uint32_t rotate)
{
    uint32_t result;
    if (__builtin_constant_p(rotate) && ((rotate == 8U) || (rotate == 16U) || (rotate == 24U)))
    {
        __ASM volatile("sxtb16 %0, %1, ROR %2" : "=r"(result) : "r"(op1), "i"(rotate));
    }
    else
    {
        result = SXTB16(ROR(op1, rotate));
    }
    return result;
}

__STATIC_FORCEINLINE uint32_t SXTAB16_RORn(uint32_t op1, uint32_t op2, uint32_t rotate)
{
    uint32_t result;
    if (__builtin_constant_p(rotate) && ((rotate == 8U) || (rotate == 16U) || (rotate == 24U)))
    {
        __ASM volatile("sxtab16 %0, %1, %2, ROR %3" : "=r"(result) : "r"(op1), "r"(op2), "i"(rotate));
    }
    else
    {
        result = SXTAB16(op1, ROR(op2, rotate));
    }
    return result;
}

// Inline assembly routines for ACLE intrinsics that are not defined by GCC toolchain
__STATIC_FORCEINLINE uint32_t SMULBB(uint32_t op1, uint32_t op2)
{
    uint32_t result;

    __ASM volatile("smulbb %0, %1, %2" : "=r"(result) : "r"(op1), "r"(op2));
    return (result);
}

__STATIC_FORCEINLINE uint32_t SMULTT(uint32_t op1, uint32_t op2)
{
    uint32_t result;

    __ASM volatile("smultt %0, %1, %2" : "=r"(result) : "r"(op1), "r"(op2));
    return (result);
}
    #endif

#endif

#endif /* #ifndef ARM_NN_COMPILER_H */

// #include "arm_nn_math_types.h"

#ifndef ARM_NN_MATH_TYPES_H

#define ARM_NN_MATH_TYPES_H

#include <limits.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @brief Translate architecture feature flags to CMSIS-NN defines
 *
 */

// CMSIS-NN uses the same macro names as CMSIS-DSP
#if (defined(__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1))
    #ifndef ARM_MATH_DSP
        #define ARM_MATH_DSP 1
    #endif
#endif

#if defined(__ARM_FEATURE_MVE)
    #ifndef ARM_MATH_MVEI
        #define ARM_MATH_MVEI 1
    #endif
#endif

/**
 *
 * @brief Limits macros
 *
 */

#define NN_Q31_MAX ((int32_t)(0x7FFFFFFFL))
#define NN_Q15_MAX ((int16_t)(0x7FFF))
#define NN_Q7_MAX ((int8_t)(0x7F))
#define NN_Q31_MIN ((int32_t)(0x80000000L))
#define NN_Q15_MIN ((int16_t)(0x8000))
#define NN_Q7_MIN ((int8_t)(0x80))

#ifdef __cplusplus
}
#endif

#endif /*ifndef ARM_NN_MATH_TYPES_H */

// #include "arm_nn_types.h"

#ifndef _ARM_NN_TYPES_H
#define _ARM_NN_TYPES_H

#include <stdint.h>

/** Enum for specifying activation function types */
typedef enum
{
    ARM_SIGMOID = 0, /**< Sigmoid activation function */
    ARM_TANH = 1,    /**< Tanh activation function */
} arm_nn_activation_type;

/** Function return codes */
typedef enum
{
    ARM_CMSIS_NN_SUCCESS = 0,        /**< No error */
    ARM_CMSIS_NN_ARG_ERROR = -1,     /**< One or more arguments are incorrect */
    ARM_CMSIS_NN_NO_IMPL_ERROR = -2, /**<  No implementation available */
    ARM_CMSIS_NN_FAILURE = -3,       /**<  Logical error */
} arm_cmsis_nn_status;

/** CMSIS-NN object to contain the width and height of a tile */
typedef struct
{
    int32_t w; /**< Width */
    int32_t h; /**< Height */
} cmsis_nn_tile;

/** CMSIS-NN object used for the function context. */
typedef struct
{
    void *buf;    /**< Pointer to a buffer needed for the optimization */
    int32_t size; /**< Buffer size */
} cmsis_nn_context;

/** CMSIS-NN object to contain the dimensions of the tensors */
typedef struct
{
    int32_t n; /**< Generic dimension to contain either the batch size or output channels.
                     Please refer to the function documentation for more information */
    int32_t h; /**< Height */
    int32_t w; /**< Width */
    int32_t c; /**< Input channels */
} cmsis_nn_dims;

/** CMSIS-NN object to contain LSTM specific input parameters related to dimensions */
typedef struct
{
    int32_t max_time;
    int32_t num_inputs;
    int32_t num_batches;
    int32_t num_outputs;
} cmsis_nn_lstm_dims;

/** CMSIS-NN object for the per-channel quantization parameters */
typedef struct
{
    int32_t *multiplier; /**< Multiplier values */
    int32_t *shift;      /**< Shift values */
} cmsis_nn_per_channel_quant_params;

/** CMSIS-NN object for the per-tensor quantization parameters */
typedef struct
{
    int32_t multiplier; /**< Multiplier value */
    int32_t shift;      /**< Shift value */
} cmsis_nn_per_tensor_quant_params;

/** CMSIS-NN object for the quantized Relu activation */
typedef struct
{
    int32_t min; /**< Min value used to clamp the result */
    int32_t max; /**< Max value used to clamp the result */
} cmsis_nn_activation;

/** CMSIS-NN object for the convolution layer parameters */
typedef struct
{
    int32_t input_offset;  /**< Zero value for the input tensor */
    int32_t output_offset; /**< Zero value for the output tensor */
    cmsis_nn_tile stride;
    cmsis_nn_tile padding;
    cmsis_nn_tile dilation;
    cmsis_nn_activation activation;
} cmsis_nn_conv_params;

/** CMSIS-NN object for Depthwise convolution layer parameters */
typedef struct
{
    int32_t input_offset;  /**< Zero value for the input tensor */
    int32_t output_offset; /**< Zero value for the output tensor */
    int32_t ch_mult;       /**< Channel Multiplier. ch_mult * in_ch = out_ch */
    cmsis_nn_tile stride;
    cmsis_nn_tile padding;
    cmsis_nn_tile dilation;
    cmsis_nn_activation activation;
} cmsis_nn_dw_conv_params;
/** CMSIS-NN object for pooling layer parameters */
typedef struct
{
    cmsis_nn_tile stride;
    cmsis_nn_tile padding;
    cmsis_nn_activation activation;
} cmsis_nn_pool_params;

/** CMSIS-NN object for Fully Connected layer parameters */
typedef struct
{
    int32_t input_offset;  /**< Zero value for the input tensor */
    int32_t filter_offset; /**< Zero value for the filter tensor. Not used */
    int32_t output_offset; /**< Zero value for the output tensor */
    cmsis_nn_activation activation;
} cmsis_nn_fc_params;

/** CMSIS-NN object for SVDF layer parameters */
typedef struct
{
    int32_t rank;
    int32_t input_offset;  /**< Zero value for the input tensor */
    int32_t output_offset; /**< Zero value for the output tensor */
    cmsis_nn_activation input_activation;
    cmsis_nn_activation output_activation;
} cmsis_nn_svdf_params;

/** CMSIS-NN object for Softmax s16 layer parameters */
typedef struct
{
    const int16_t *exp_lut;
    const int16_t *one_by_one_lut;
} cmsis_nn_softmax_lut_s16;

/** LSTM guard parameters */
typedef struct
{
    int32_t input_variance;
    int32_t forget_variance;
    int32_t cell_variance;
    int32_t output_variance;
} cmsis_nn_lstm_guard_params;

/** LSTM scratch buffer container */
typedef struct
{
    int16_t *input_gate;
    int16_t *forget_gate;
    int16_t *cell_gate;
    int16_t *output_gate;
} cmsis_nn_lstm_context;

/** Quantized clip value for cell and projection of LSTM input. Zero value means no clipping. */
typedef struct
{
    int16_t cell;
    int8_t projection;
} cmsis_nn_lstm_clip_params;

/** CMSIS-NN object for quantization parameters */
typedef struct
{
    int32_t multiplier; /**< Multiplier value */
    int32_t shift;      /**< Shift value */
} cmsis_nn_scaling;

/** CMSIS-NN norm layer coefficients */
typedef struct
{
    int16_t *input_weight;
    int16_t *forget_weight;
    int16_t *cell_weight;
    int16_t *output_weight;
} cmsis_nn_layer_norm;

/** Parameters for integer LSTM, as defined in TFLM */
typedef struct
{
    int32_t time_major; /**< Nonzero (true) if first row of data is timestamps for input */
    cmsis_nn_scaling input_to_input_scaling;
    cmsis_nn_scaling input_to_forget_scaling;
    cmsis_nn_scaling input_to_cell_scaling;
    cmsis_nn_scaling input_to_output_scaling;
    cmsis_nn_scaling recurrent_to_input_scaling;
    cmsis_nn_scaling recurrent_to_forget_scaling;
    cmsis_nn_scaling recurrent_to_cell_scaling;
    cmsis_nn_scaling recurrent_to_output_scaling;
    cmsis_nn_scaling cell_to_input_scaling;
    cmsis_nn_scaling cell_to_forget_scaling;
    cmsis_nn_scaling cell_to_output_scaling;
    cmsis_nn_scaling projection_scaling;
    cmsis_nn_scaling hidden_scaling;
    cmsis_nn_scaling layer_norm_input_scaling;  /**< layer normalization for input layer */
    cmsis_nn_scaling layer_norm_forget_scaling; /**< layer normalization for forget gate */
    cmsis_nn_scaling layer_norm_cell_scaling;   /**< layer normalization for cell */
    cmsis_nn_scaling layer_norm_output_scaling; /**< layer normalization for outpus layer */

    int32_t cell_state_shift;
    int32_t hidden_offset;
    int32_t output_state_offset;

    cmsis_nn_lstm_clip_params clip;
    cmsis_nn_lstm_guard_params guard;
    cmsis_nn_layer_norm layer_norm;

    /* Effective bias is precalculated as bias + zero_point * weight.
    Only applicable to when input/output are s8 and weights are s16 */
    const int32_t *i2i_effective_bias; /**< input to input effective bias */
    const int32_t *i2f_effective_bias; /**< input to forget gate effective bias */
    const int32_t *i2c_effective_bias; /**< input to cell effective bias */
    const int32_t *i2o_effective_bias; /**< input to output effective bias */

    const int32_t *r2i_effective_bias; /**< recurrent gate to input effective bias */
    const int32_t *r2f_effective_bias; /**< recurrent gate to forget gate effective bias */
    const int32_t *r2c_effective_bias; /**< recurrent gate to cell effective bias */
    const int32_t *r2o_effective_bias; /**< recurrent gate to output effective bias */

    const int32_t *projection_effective_bias;

    /* Not precalculated bias */
    const int32_t *input_gate_bias;
    const int32_t *forget_gate_bias;
    const int32_t *cell_gate_bias;
    const int32_t *output_gate_bias;

    /* Activation min and max */
    cmsis_nn_activation activation;

} cmsis_nn_lstm_params;

#endif // _ARM_NN_TYPES_H


#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define USE_FAST_DW_CONV_S16_FUNCTION(dw_conv_params, filter_dims, input_dims)                                         \
    (dw_conv_params->ch_mult == 1 && dw_conv_params->dilation.w == 1 && dw_conv_params->dilation.h == 1 &&             \
     filter_dims->w * filter_dims->h < 512)

#define LEFT_SHIFT(_shift) (_shift > 0 ? _shift : 0)
#define RIGHT_SHIFT(_shift) (_shift > 0 ? 0 : -_shift)
#define MASK_IF_ZERO(x) (x) == 0 ? ~0 : 0
#define MASK_IF_NON_ZERO(x) (x) != 0 ? ~0 : 0
#define SELECT_USING_MASK(mask, a, b) ((mask) & (a)) ^ (~(mask) & (b))

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define CLAMP(x, h, l) MAX(MIN((x), (h)), (l))
#define REDUCE_MULTIPLIER(_mult) ((_mult < 0x7FFF0000) ? ((_mult + (1 << 15)) >> 16) : 0x7FFF)

// Number of channels processed in a block for DW Conv(MVE)
// Requirement: Greater than 0 & less than 128
// This can be fine tuned to match number of input channels for best performance.
// A layer with lower number of channels than CH_IN_BLOCK_MVE will result in higher
// scratch buffer usage and a layer with higher number of channels than CH_IN_BLOCK_MVE
// will result in lower scratch buffer usage.
#define CH_IN_BLOCK_MVE (124)

/**
 * @brief definition to pack four 8 bit values.
 */
#define PACK_S8x4_32x1(v0, v1, v2, v3)                                                                                 \
    ((((int32_t)(v0) << 0) & (int32_t)0x000000FF) | (((int32_t)(v1) << 8) & (int32_t)0x0000FF00) |                     \
     (((int32_t)(v2) << 16) & (int32_t)0x00FF0000) | (((int32_t)(v3) << 24) & (int32_t)0xFF000000))

/**
 * @brief definition to pack two 16 bit values.
 */
#define PACK_Q15x2_32x1(v0, v1) (((int32_t)v0 & (int32_t)0xFFFF) | ((int32_t)v1 << 16))

/**
 * @brief Union for SIMD access of q31/s16/s8 types
 */
union arm_nnword
{
    int32_t word;
    /**< q31 type */
    int16_t half_words[2];
    /**< s16 type */
    int8_t bytes[4];
    /**< s8 type */
};

/**
 * @brief Union for data type long long
 */
struct arm_nn_double
{
    uint32_t low;
    int32_t high;
};

union arm_nn_long_long
{
    int64_t long_long;
    struct arm_nn_double word;
};

/**
 * @defgroup groupSupport Private
 *
 * Internal Support functions. Not intended to be called direclty by a CMSIS-NN user.
 *
 */

/**
 * @defgroup supportConversion Data Conversion
 *
 * Perform data type conversion in-between neural network operations
 *
 */

/**
 * @brief Converts the elements from a s8 vector to a s16 vector with an added offset
 * @param[in]    src        pointer to the s8 input vector
 * @param[out]   dst        pointer to the s16 output vector
 * @param[in]    block_size length of the input vector
 * @param[in]    offset     s16 offset to be added to each input vector element.
 *
 * \par Description:
 *
 * Output elements are ordered.
 * The equation used for the conversion process is:
 *
 * <pre>
 *  dst[n] = (int16_t) src[n] + offset;   0 <= n < block_size.
 * </pre>
 *
 */
void arm_q7_to_q15_with_offset(const int8_t *src, int16_t *dst, int32_t block_size, int16_t offset);

#if defined(ARM_MATH_DSP)
/**
 * @brief Converts the elements from a s8 vector to a s16 vector with an added offset
 * @param[in]    src        pointer to the s8 input vector
 * @param[out]   dst        pointer to the s16 output vector
 * @param[in]    block_size length of the input vector
 * @param[in]    offset     s16 offset to be added to each input vector element.
 *
 * \par Description:
 *
 * No additonal ordering is done with the result that output elements are not in order.
 * Instead of ABCD order will be ACBD.
 * Note this is for processors with DSP extension only.
 * The equation used for the conversion process is:
 *
 * <pre>
 *  dst[n - 0] = (int16_t) src[n - 0] + offset;   0 <= n < block_size.
 *  dst[n - 1] = (int16_t) src[n - 2] + offset;   0 <= n < block_size.
 *  dst[n - 2] = (int16_t) src[n - 1] + offset;   0 <= n < block_size.
 *  dst[n - 3] = (int16_t) src[n - 3] + offset;   0 <= n < block_size.
 * </pre>
 *
 */
void arm_s8_to_s16_unordered_with_offset(const int8_t *src, int16_t *dst, int32_t block_size, int16_t offset);
#endif

/**
 * @brief Depthwise conv on an im2col buffer where the input channel equals output channel.
 * @param[in]    row     pointer to row
 * @param[in]    col     pointer to im2col buffer, always consists of 2 columns.
 * @param[in]    num_ch   number of channels
 * @param[in]    out_shift  pointer to per output channel requantization shift parameter.
 * @param[in]    out_mult   pointer to per output channel requantization multiplier parameter.
 * @param[in]    out_offset      output tensor offset.
 * @param[in]    activation_min   minimum value to clamp the output to. Range : int8
 * @param[in]    activation_max   maximum value to clamp the output to. Range : int8
 * @param[in]    kernel_size   number of elements in one column.
 * @param[in]    output_bias per output channel bias. Range : int32
 * @param[out]   out         pointer to output
 * @return     The function returns one of the two
 *              1. The incremented output pointer for a successful operation or
 *              2. NULL if implementation is not available.
 *
 * @details     Supported framework: TensorFlow Lite micro.
 */
int8_t *arm_nn_depthwise_conv_s8_core(const int8_t *row,
                                      const int16_t *col,
                                      const uint16_t num_ch,
                                      const int32_t *out_shift,
                                      const int32_t *out_mult,
                                      const int32_t out_offset,
                                      const int32_t activation_min,
                                      const int32_t activation_max,
                                      const uint16_t kernel_size,
                                      const int32_t *const output_bias,
                                      int8_t *out);

/**
 * @brief General Matrix-multiplication function with per-channel requantization.
 * @param[in]       input_row    pointer to row operand
 * @param[in]       input_col    pointer to col operand
 * @param[in]       output_ch    number of rows of input_row
 * @param[in]       col_batches  number of column batches. Range: 1 to 4
 * @param[in]       output_shift  pointer to per output channel requantization shift parameter.
 * @param[in]       output_mult   pointer to per output channel requantization multiplier parameter.
 * @param[in]       out_offset    output tensor offset.
 * @param[in]       col_offset    input tensor(col) offset.
 * @param[in]       row_offset    kernel offset(row). Not used.
 * @param[in]       out_activation_min   minimum value to clamp the output to. Range : int8
 * @param[in]       out_activation_max   maximum value to clamp the output to. Range : int8
 * @param[in]       row_len       number of elements in each row
 * @param[in]       bias          per output channel bias. Range : int32
 * @param[in,out]   out           pointer to output
 * @return     The function returns one of the two
 *              1. The incremented output pointer for a successful operation or
 *              2. NULL if implementation is not available.
 *
 * @details   Supported framework: TensorFlow Lite
 */
int8_t *arm_nn_mat_mult_s8(const int8_t *input_row,
                           const int8_t *input_col,
                           const uint16_t output_ch,
                           const uint16_t col_batches,
                           const int32_t *output_shift,
                           const int32_t *output_mult,
                           const int32_t out_offset,
                           const int32_t col_offset,
                           const int32_t row_offset,
                           const int16_t out_activation_min,
                           const int16_t out_activation_max,
                           const uint16_t row_len,
                           const int32_t *const bias,
                           int8_t *out);
/**
 * @brief Matrix-multiplication function for convolution with per-channel requantization for 16 bits convolution.
 * @param[in]       input_a     pointer to operand A
 * @param[in]       input_b     pointer to operand B, always consists of 2 vectors.
 * @param[in]       output_ch   number of rows of A
 * @param[in]       out_shift  pointer to per output channel requantization shift parameter.
 * @param[in]       out_mult   pointer to per output channel requantization multiplier parameter.
 * @param[in]       activation_min   minimum value to clamp the output to. Range : int16
 * @param[in]       activation_max   maximum value to clamp the output to. Range : int16
 * @param[in]       num_col_a   number of columns of A
 * @param[in]       output_bias per output channel bias. Range : int64
 * @param[in,out]   out_0       pointer to output
 * @return     The function returns one of the two
 *              1. The incremented output pointer for a successful operation or
 *              2. NULL if implementation is not available.
 *
 * @details   This function does the matrix multiplication of weight matrix for all output channels
 *            with 2 columns from im2col and produces two elements/output_channel. The outputs are
 *            clamped in the range provided by activation min and max.
 *            Supported framework: TensorFlow Lite micro.
 */
int16_t *arm_nn_mat_mult_kernel_s16(const int8_t *input_a,
                                    const int16_t *input_b,
                                    const int32_t output_ch,
                                    const int32_t *out_shift,
                                    const int32_t *out_mult,
                                    const int16_t activation_min,
                                    const int16_t activation_max,
                                    const int32_t num_col_a,
                                    const int64_t *const output_bias,
                                    int16_t *out_0);

/**
 * @brief General Vector by Matrix multiplication with requantization and storage of result.
 * @param[in]       row_elements          number of row elements
 * @param[in]       skipped_row_elements  number of row elements skipped due to padding.
 *                                        row_elements + skipped_row_elements = (kernel_x * kernel_y) * input_ch
 * @param[in]       row_base_ref          pointer to row operand
 * @param[in]       col_base_ref          pointer to col operand
 * @param[out]      out_ch                Number of output channels
 * @param[in]       conv_params           Pointer to convolution parameters like offsets and activation values
 * @param[in]       quant_params          Pointer to per-channel quantization parameters
 * @param[in]       bias                  Pointer to optional per-channel bias
 * @param[out]      output                Pointer to output where int8 results are stored.
 * @return     The function performs matrix(row_base_ref) multiplication with vector(col_base_ref) and
 *             scaled result is stored in memory.
 *
 * @details Pseudo-code
 *      *output = 0
 *      sum_col = 0
 *      for (j = 0; j < out_ch; j++)
 *      for (i = 0; i < row_elements; i++)
 *          *output += row_base_ref[i] * col_base_ref[i]
 *          sum_col += col_base_ref[i]
 *      scale sum_col using quant_params and bias
 *      store result in 'output'
 *
 *
 */
arm_cmsis_nn_status arm_nn_mat_mul_core_1x_s8(int32_t row_elements,
                                              const int32_t skipped_row_elements,
                                              const int8_t *row_base_ref,
                                              const int8_t *col_base_ref,
                                              const int32_t out_ch,
                                              const cmsis_nn_conv_params *conv_params,
                                              const cmsis_nn_per_channel_quant_params *quant_params,
                                              const int32_t *bias,
                                              int8_t *output);

/**
 * @brief Matrix-multiplication with requantization & activation function for four rows and one column
 * @param[in]       row_elements  number of row elements
 * @param[in]       offset        offset between rows. Can be the same as row_elements.
 *                                For e.g, in a 1x1 conv scenario with stride as 1.
 * @param[in]       row_base      pointer to row operand
 * @param[in]       col_base      pointer to col operand
 * @param[in]       out_ch        Number of output channels
 * @param[in]       conv_params   Pointer to convolution parameters like offsets and activation values
 * @param[in]       quant_params  Pointer to per-channel quantization parameters
 * @param[in]       bias          Pointer to per-channel bias
 * @param[out]      output        Pointer to output where int8 results are stored.
 *
 * @return     The function returns the updated output pointer or NULL if implementation is not available.
 *
 * @details Compliant to TFLM int8 specification. MVE implementation only
 */
int8_t *arm_nn_mat_mul_core_4x_s8(const int32_t row_elements,
                                  const int32_t offset,
                                  const int8_t *row_base,
                                  const int8_t *col_base,
                                  const int32_t out_ch,
                                  const cmsis_nn_conv_params *conv_params,
                                  const cmsis_nn_per_channel_quant_params *quant_params,
                                  const int32_t *bias,
                                  int8_t *output);

/**
 * @brief General Matrix-multiplication function with per-channel requantization.
 *        This function assumes:
 *        - LHS input matrix NOT transposed (nt)
 *        - RHS input matrix transposed (t)
 *
 *  @note This operation also performs the broadcast bias addition before the requantization
 *
 * @param[in]  lhs                Pointer to the LHS input matrix
 * @param[in]  rhs                Pointer to the RHS input matrix
 * @param[in]  bias               Pointer to the bias vector. The length of this vector is equal to the number of
 *                                output columns (or RHS input rows)
 * @param[out] dst                Pointer to the output matrix with "m" rows and "n" columns
 * @param[in]  dst_multipliers    Pointer to the multipliers vector needed for the per-channel requantization.
 *                                The length of this vector is equal to the number of output columns (or RHS input
 *                                rows)
 * @param[in]  dst_shifts         Pointer to the shifts vector needed for the per-channel requantization. The length
 *                                of this vector is equal to the number of output columns (or RHS input rows)
 * @param[in]  lhs_rows           Number of LHS input rows
 * @param[in]  rhs_rows           Number of RHS input rows
 * @param[in]  rhs_cols           Number of LHS/RHS input columns
 * @param[in]  lhs_offset         Offset to be applied to the LHS input value
 * @param[in]  dst_offset         Offset to be applied the output result
 * @param[in]  activation_min     Minimum value to clamp down the output. Range : int8
 * @param[in]  activation_max     Maximum value to clamp up the output. Range : int8
 * @param[in]  lhs_cols_offset    Column offset between subsequent lhs_rows
 *
 * @return     The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 */
arm_cmsis_nn_status arm_nn_mat_mult_nt_t_s8(const int8_t *lhs,
                                            const int8_t *rhs,
                                            const int32_t *bias,
                                            int8_t *dst,
                                            const int32_t *dst_multipliers,
                                            const int32_t *dst_shifts,
                                            const int32_t lhs_rows,
                                            const int32_t rhs_rows,
                                            const int32_t rhs_cols,
                                            const int32_t lhs_offset,
                                            const int32_t dst_offset,
                                            const int32_t activation_min,
                                            const int32_t activation_max,
                                            const int32_t lhs_cols_offset);

/**
 * @brief s8 Vector by Matrix (transposed) multiplication
 *
 * @param[in]      lhs             Input left-hand side vector
 * @param[in]      rhs             Input right-hand side matrix (transposed)
 * @param[in]      bias            Input bias
 * @param[out]     dst             Output vector
 * @param[in]      lhs_offset      Offset to be added to the input values of the left-hand side vector.
 *                                 Range: -127 to 128
 * @param[in]      dst_offset      Offset to be added to the output values. Range: -127 to 128
 * @param[in]      dst_multiplier  Output multiplier
 * @param[in]      dst_shift       Output shift
 * @param[in]      rhs_cols        Number of columns in the right-hand side input matrix
 * @param[in]      rhs_rows        Number of rows in the right-hand side input matrix
 * @param[in]      activation_min  Minimum value to clamp the output to. Range: int8
 * @param[in]      activation_max  Maximum value to clamp the output to. Range: int8
 * @param[in]      address_offset  Memory position offset for dst. First output is stored at 'dst', the
 *                                 second at 'dst + address_offset' and so on. Default value is typically 1.
 *
 * @return         The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 */
arm_cmsis_nn_status arm_nn_vec_mat_mult_t_s8(const int8_t *lhs,
                                             const int8_t *rhs,
                                             const int32_t *bias,
                                             int8_t *dst,
                                             const int32_t lhs_offset,
                                             const int32_t dst_offset,
                                             const int32_t dst_multiplier,
                                             const int32_t dst_shift,
                                             const int32_t rhs_cols,
                                             const int32_t rhs_rows,
                                             const int32_t activation_min,
                                             const int32_t activation_max,
                                             const int32_t address_offset);

/**
 * @brief s16 Vector by Matrix (transposed) multiplication
 *
 * @param[in]      lhs             Input left-hand side vector
 * @param[in]      rhs             Input right-hand side matrix (transposed)
 * @param[in]      bias            Input bias
 * @param[out]     dst             Output vector
 * @param[in]      dst_multiplier  Output multiplier
 * @param[in]      dst_shift       Output shift
 * @param[in]      rhs_cols        Number of columns in the right-hand side input matrix
 * @param[in]      rhs_rows        Number of rows in the right-hand side input matrix
 * @param[in]      activation_min  Minimum value to clamp the output to. Range: int16
 * @param[in]      activation_max  Maximum value to clamp the output to. Range: int16
 *
 * @return         The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 */
arm_cmsis_nn_status arm_nn_vec_mat_mult_t_s16(const int16_t *lhs,
                                              const int8_t *rhs,
                                              const int64_t *bias,
                                              int16_t *dst,
                                              const int32_t dst_multiplier,
                                              const int32_t dst_shift,
                                              const int32_t rhs_cols,
                                              const int32_t rhs_rows,
                                              const int32_t activation_min,
                                              const int32_t activation_max);

/**
 * @brief s8 Vector by Matrix (transposed) multiplication with s16 output
 *
 * @param[in]      lhs             Input left-hand side vector
 * @param[in]      rhs             Input right-hand side matrix (transposed)
 * @param[out]     dst             Output vector
 * @param[in]      lhs_offset      Offset to be added to the input values of the left-hand side
 *                                 vector. Range: -127 to 128
 * @param[in]      scatter_offset  Address offset for dst. First output is stored at 'dst', the
 *                                 second at 'dst + scatter_offset' and so on.
 * @param[in]      dst_multiplier  Output multiplier
 * @param[in]      dst_shift       Output shift
 * @param[in]      rhs_cols        Number of columns in the right-hand side input matrix
 * @param[in]      rhs_rows        Number of rows in the right-hand side input matrix
 * @param[in]      activation_min  Minimum value to clamp the output to. Range: int16
 * @param[in]      activation_max  Maximum value to clamp the output to. Range: int16
 *
 * @return         The function returns <code>ARM_CMSIS_NN_SUCCESS</code>
 *
 */
arm_cmsis_nn_status arm_nn_vec_mat_mult_t_svdf_s8(const int8_t *lhs,
                                                  const int8_t *rhs,
                                                  int16_t *dst,
                                                  const int32_t lhs_offset,
                                                  const int32_t scatter_offset,
                                                  const int32_t dst_multiplier,
                                                  const int32_t dst_shift,
                                                  const int32_t rhs_cols,
                                                  const int32_t rhs_rows,
                                                  const int32_t activation_min,
                                                  const int32_t activation_max);

/**
 * @brief Depthwise convolution of transposed rhs matrix with 4 lhs matrices. To be used in padded cases where
 *        the padding is -lhs_offset(Range: int8). Dimensions are the same for lhs and rhs.
 *
 * @param[in]      lhs             Input left-hand side matrix
 * @param[in]      rhs             Input right-hand side matrix (transposed)
 * @param[in]      lhs_offset      LHS matrix offset(input offset). Range: -127 to 128
 * @param[in]      active_ch       Subset of total_ch processed
 * @param[in]      total_ch        Number of channels in LHS/RHS
 * @param[in]      out_shift       Per channel output shift. Length of vector is equal to number of channels
 * @param[in]      out_mult        Per channel output multiplier. Length of vector is equal to number of channels
 * @param[in]      out_offset      Offset to be added to the output values. Range: -127 to 128
 * @param[in]      activation_min  Minimum value to clamp the output to. Range: int8
 * @param[in]      activation_max  Maximum value to clamp the output to. Range: int8
 * @param[in]       row_x_col       (row_dimension * col_dimension) of LHS/RHS matrix
 * @param[in]      output_bias     Per channel output bias. Length of vector is equal to number of channels
 * @param[in]      out             Output pointer
 *
 * @return         The function returns one of the two
 *                  - Updated output pointer if an implementation is available
 *                  - NULL if no implementation is available.
 *
 * @note           If number of channels is not a multiple of 4, upto 3 elements outside the boundary will be read
 * out for the following.
 *                  - Output shift
 *                  - Output multiplier
 *                  - Output bias
 *                  - rhs
 */
arm_cmsis_nn_status arm_nn_depthwise_conv_nt_t_padded_s8(const int8_t *lhs,
                                                         const int8_t *rhs,
                                                         const int32_t lhs_offset,
                                                         const int32_t active_ch,
                                                         const int32_t total_ch,
                                                         const int32_t *out_shift,
                                                         const int32_t *out_mult,
                                                         const int32_t out_offset,
                                                         const int32_t activation_min,
                                                         const int32_t activation_max,
                                                         const uint16_t row_x_col,
                                                         const int32_t *const output_bias,
                                                         int8_t *out);

/**
 * @brief Depthwise convolution of transposed rhs matrix with 4 lhs matrices. To be used in non-padded cases.
 *        Dimensions are the same for lhs and rhs.
 *
 * @param[in]      lhs             Input left-hand side matrix
 * @param[in]      rhs             Input right-hand side matrix (transposed)
 * @param[in]      lhs_offset      LHS matrix offset(input offset). Range: -127 to 128
 * @param[in]      active_ch       Subset of total_ch processed
 * @param[in]      total_ch        Number of channels in LHS/RHS
 * @param[in]      out_shift       Per channel output shift. Length of vector is equal to number of channels.
 * @param[in]      out_mult        Per channel output multiplier. Length of vector is equal to number of channels.
 * @param[in]      out_offset      Offset to be added to the output values. Range: -127 to 128
 * @param[in]      activation_min  Minimum value to clamp the output to. Range: int8
 * @param[in]      activation_max  Maximum value to clamp the output to. Range: int8
 * @param[in]       row_x_col       (row_dimension * col_dimension) of LHS/RHS matrix
 * @param[in]      output_bias     Per channel output bias. Length of vector is equal to number of channels.
 * @param[in]      out             Output pointer
 *
 * @return         The function returns one of the two
 *                  - Updated output pointer if an implementation is available
 *                  - NULL if no implementation is available.
 *
 * @note           If number of channels is not a multiple of 4, upto 3 elements outside the boundary will be read
 * out for the following.
 *                  - Output shift
 *                  - Output multiplier
 *                  - Output bias
 *                  - rhs
 */
arm_cmsis_nn_status arm_nn_depthwise_conv_nt_t_s8(const int8_t *lhs,
                                                  const int8_t *rhs,
                                                  const int32_t lhs_offset,
                                                  const int32_t active_ch,
                                                  const int32_t total_ch,
                                                  const int32_t *out_shift,
                                                  const int32_t *out_mult,
                                                  const int32_t out_offset,
                                                  const int32_t activation_min,
                                                  const int32_t activation_max,
                                                  const uint16_t row_x_col,
                                                  const int32_t *const output_bias,
                                                  int8_t *out);

/**
 * @brief Depthwise convolution of transposed rhs matrix with 4 lhs matrices. To be used in non-padded cases.
 *        Dimensions are the same for lhs and rhs.
 *
 * @param[in]      lhs             Input left-hand side matrix
 * @param[in]      rhs             Input right-hand side matrix (transposed)
 * @param[in]      num_ch          Number of channels in LHS/RHS
 * @param[in]      out_shift       Per channel output shift. Length of vector is equal to number of channels.
 * @param[in]      out_mult        Per channel output multiplier. Length of vector is equal to number of channels.
 * @param[in]      activation_min  Minimum value to clamp the output to. Range: int8
 * @param[in]      activation_max  Maximum value to clamp the output to. Range: int8
 * @param[in]       row_x_col       (row_dimension * col_dimension) of LHS/RHS matrix
 * @param[in]      output_bias     Per channel output bias. Length of vector is equal to number of channels.
 * @param[in]      out             Output pointer
 *
 * @return         The function returns one of the two
 *                  - Updated output pointer if an implementation is available
 *                  - NULL if no implementation is available.
 *
 * @note           If number of channels is not a multiple of 4, upto 3 elements outside the boundary will be read
 * out for the following.
 *                  - Output shift
 *                  - Output multiplier
 *                  - Output bias
 *                  - rhs
 */
int16_t *arm_nn_depthwise_conv_nt_t_s16(const int16_t *lhs,
                                        const int8_t *rhs,
                                        const uint16_t num_ch,
                                        const int32_t *out_shift,
                                        const int32_t *out_mult,
                                        const int32_t activation_min,
                                        const int32_t activation_max,
                                        const uint16_t row_x_col,
                                        const int64_t *const output_bias,
                                        int16_t *out);

/**
  @brief         Read 2 s16 elements and post increment pointer.
  @param[in]     in_q15   Pointer to pointer that holds address of input.
  @return        q31 value
 */
__STATIC_FORCEINLINE int32_t arm_nn_read_q15x2_ia(const int16_t **in_q15)
{
    int32_t val;

    memcpy(&val, *in_q15, 4);
    *in_q15 += 2;

    return (val);
}

/**
  @brief         Read 4 s8 from s8 pointer and post increment pointer.
  @param[in]     in_s8       Pointer to pointer that holds address of input.
  @return        q31 value
 */
__STATIC_FORCEINLINE int32_t arm_nn_read_s8x4_ia(const int8_t **in_s8)
{
    int32_t val;
    memcpy(&val, *in_s8, 4);
    *in_s8 += 4;

    return (val);
}

/**
  @brief         Read 2 int16 values from int16 pointer.
  @param[in]     in     pointer to address of input.
  @return        s32    value
 */
__STATIC_FORCEINLINE int32_t arm_nn_read_s16x2(const int16_t *in)
{
    int32_t val;
    memcpy(&val, in, 4);

    return (val);
}

/**
  @brief         Read 4 s8 values.
  @param[in]     in_s8       pointer to address of input.
  @return        s32 value
 */
__STATIC_FORCEINLINE int32_t arm_nn_read_s8x4(const int8_t *in_s8)
{
    int32_t val;
    memcpy(&val, in_s8, 4);

    return (val);
}

/**
  @brief         Write four s8 to s8 pointer and increment pointer afterwards.
  @param[in]     in       Double pointer to input value
  @param[in]     value    Four bytes to copy
 */
__STATIC_FORCEINLINE void arm_nn_write_s8x4_ia(int8_t **in, int32_t value)
{
    memcpy(*in, &value, 4);
    *in += 4;
}

/**
 * @brief           memset optimized for MVE
 * @param[in, out]  dst         Destination pointer
 * @param[in]       val         Value to set
 * @param[in]       block_size  Number of bytes to copy.
 *
 */
__STATIC_FORCEINLINE void arm_memset_s8(int8_t *dst, const int8_t val, uint32_t block_size)
{
#if defined(ARM_MATH_MVEI)
    __asm volatile("   vdup.8                  q0, %[set_val]             \n"
                   "   wlstp.8                 lr, %[cnt], 1f             \n"
                   "2:                                                    \n"
                   "   vstrb.8                 q0, [%[in]], #16            \n"
                   "   letp                    lr, 2b                     \n"
                   "1:                                                    \n"
                   : [in] "+r"(dst)
                   : [cnt] "r"(block_size), [set_val] "r"(val)
                   : "q0", "memory", "r14");
#else
    memset(dst, val, block_size);
#endif
}

#if defined(ARM_MATH_DSP)

/**
 * @brief read and expand one s8 word into two s16 words with ordering.
 */
__STATIC_FORCEINLINE const int8_t *read_and_pad(const int8_t *source, int32_t *out1, int32_t *out2)
{
    int32_t inA = arm_nn_read_s8x4_ia(&source);
    int32_t inAbuf1 = SXTB16_RORn((uint32_t)inA, 8);
    int32_t inAbuf2 = SXTB16(inA);

    #ifndef ARM_MATH_BIG_ENDIAN
    *out2 = (int32_t)(PKHTB(inAbuf1, inAbuf2, 16));
    *out1 = (int32_t)(PKHBT(inAbuf2, inAbuf1, 16));
    #else
    *out1 = (int32_t)(PKHTB(inAbuf1, inAbuf2, 16));
    *out2 = (int32_t)(PKHBT(inAbuf2, inAbuf1, 16));
    #endif

    return source;
}

/**
 * @brief read and expand one s8 word into two s16 words with no additional ordering.
 */
__STATIC_FORCEINLINE const int8_t *read_and_pad_reordered(const int8_t *source, int32_t *out1, int32_t *out2)
{
    int32_t inA = arm_nn_read_s8x4_ia(&source);
    #ifndef ARM_MATH_BIG_ENDIAN
    *out2 = SXTB16(ROR((uint32_t)inA, 8));
    *out1 = SXTB16(inA);
    #else
    *out1 = SXTB16(ROR((uint32_t)inA, 8));
    *out2 = SXTB16(inA);
    #endif

    return source;
}

#endif

/**
 * @brief Matrix-multiplication function for convolution with per-channel requantization.
 * @param[in]       input_a     pointer to operand A
 * @param[in]       input_b     pointer to operand B, always consists of 2 vectors.
 * @param[in]       output_ch   number of rows of A
 * @param[in]       out_shift  pointer to per output channel requantization shift parameter.
 * @param[in]       out_mult   pointer to per output channel requantization multiplier parameter.
 * @param[in]       out_offset      output tensor offset.
 * @param[in]       activation_min   minimum value to clamp the output to. Range : int8
 * @param[in]       activation_max   maximum value to clamp the output to. Range : int8
 * @param[in]       num_col_a   number of columns of A
 * @param[in]       output_bias per output channel bias. Range : int32
 * @param[in,out]   out_0       pointer to output
 * @return     The function returns one of the two
 *              1. The incremented output pointer for a successful operation or
 *              2. NULL if implementation is not available.
 *
 * @details   This function does the matrix multiplication of weight matrix for all output channels
 *            with 2 columns from im2col and produces two elements/output_channel. The outputs are
 *            clamped in the range provided by activation min and max.
 *            Supported framework: TensorFlow Lite micro.
 */
int8_t *arm_nn_mat_mult_kernel_s8_s16(const int8_t *input_a,
                                      const int16_t *input_b,
                                      const uint16_t output_ch,
                                      const int32_t *out_shift,
                                      const int32_t *out_mult,
                                      const int32_t out_offset,
                                      const int16_t activation_min,
                                      const int16_t activation_max,
                                      const int32_t num_col_a,
                                      const int32_t *const output_bias,
                                      int8_t *out_0);

/**
 * @brief Common softmax function for s8 input and s8 or s16 output
 * @param[in]  input          Pointer to the input tensor
 * @param[in]  num_rows       Number of rows in the input tensor
 * @param[in]  row_size       Number of elements in each input row
 * @param[in]  mult           Input quantization multiplier
 * @param[in]  shift          Input quantization shift within the range [0, 31]
 * @param[in]  diff_min       Minimum difference with max in row. Used to check if
 *                            the quantized exponential operation can be performed
 * @param[in]  int16_output   Indicating s8 output if 0 else s16 output
 * @param[out] output         Pointer to the output tensor
 *
 * @note Supported framework: TensorFlow Lite micro (bit-accurate)
 *
 */
void arm_nn_softmax_common_s8(const int8_t *input,
                              const int32_t num_rows,
                              const int32_t row_size,
                              const int32_t mult,
                              const int32_t shift,
                              const int32_t diff_min,
                              const bool int16_output,
                              void *output);

/**
 * @brief macro for adding rounding offset
 */
#ifndef ARM_NN_TRUNCATE
    #define NN_ROUND(out_shift) ((0x1 << out_shift) >> 1)
#else
    #define NN_ROUND(out_shift) 0
#endif

// Macros for shortening quantization functions' names and avoid long lines
#define MUL_SAT(a, b) arm_nn_doubling_high_mult((a), (b))
#define MUL_SAT_MVE(a, b) arm_doubling_high_mult_mve_32x4((a), (b))
#define MUL_POW2(a, b) arm_nn_mult_by_power_of_two((a), (b))

#define DIV_POW2(a, b) arm_nn_divide_by_power_of_two((a), (b))
#define DIV_POW2_MVE(a, b) arm_divide_by_power_of_two_mve((a), (b))

#define EXP_ON_NEG(x) arm_nn_exp_on_negative_values((x))
#define ONE_OVER1(x) arm_nn_one_over_one_plus_x_for_x_in_0_1((x))

/**
 * @brief           Saturating doubling high multiply. Result matches
 *                  NEON instruction VQRDMULH.
 * @param[in]       m1        Multiplicand. Range: {NN_Q31_MIN, NN_Q31_MAX}
 * @param[in]       m2        Multiplier. Range: {NN_Q31_MIN, NN_Q31_MAX}
 * @return          Result of multiplication.
 *
 */
__STATIC_FORCEINLINE int32_t arm_nn_doubling_high_mult(const int32_t m1, const int32_t m2)
{
    int32_t result = 0;
    // Rounding offset to add for a right shift of 31
    int64_t mult = 1 << 30;

    if ((m1 < 0) ^ (m2 < 0))
    {
        mult = 1 - mult;
    }
    // Gets resolved as a SMLAL instruction
    mult = mult + (int64_t)m1 * m2;

    // Utilize all of the upper 32 bits. This is the doubling step
    // as well.
    result = (int32_t)(mult / (1ll << 31));

    if ((m1 == m2) && (m1 == (int32_t)NN_Q31_MIN))
    {
        result = NN_Q31_MAX;
    }
    return result;
}

/**
 * @brief           Doubling high multiply without saturation. This is intended
 *                  for requantization where the scale is a positive integer
 *
 * @param[in]       m1        Multiplicand. Range: {NN_Q31_MIN, NN_Q31_MAX}
 * @param[in]       m2        Multiplier Range: {NN_Q31_MIN, NN_Q31_MAX}
 * @return          Result of multiplication.
 * @note            The result of this matches that of neon instruction
 *                  VQRDMULH for m1 in range {NN_Q31_MIN, NN_Q31_MAX} and m2 in
 *                  range {NN_Q31_MIN + 1, NN_Q31_MAX}. Saturation occurs when
 *                  m1 equals m2 equals NN_Q31_MIN and that is not handled by
 *                  this function.
 *
 */
__STATIC_FORCEINLINE int32_t arm_nn_doubling_high_mult_no_sat(const int32_t m1, const int32_t m2)
{
    int32_t result = 0;
    union arm_nn_long_long mult;

    // Rounding offset to add for a right shift of 31
    mult.word.low = 1 << 30;
    mult.word.high = 0;

    // Gets resolved as a SMLAL instruction
    mult.long_long = mult.long_long + (int64_t)m1 * m2;

    // Utilize all of the upper 32 bits. This is the doubling step
    // as well.
    result = (int32_t)(mult.long_long >> 31);

    return result;
}

/**
 * @brief           Rounding divide by power of two.
 * @param[in]       dividend - Dividend
 * @param[in]       exponent - Divisor = power(2, exponent)
 *                             Range: [0, 31]
 * @return          Rounded result of division. Midpoint is rounded away from zero.
 *
 */
__STATIC_FORCEINLINE int32_t arm_nn_divide_by_power_of_two(const int32_t dividend, const int32_t exponent)
{
    int32_t result = 0;
    const int32_t remainder_mask = (1 << exponent) - 1;
    int32_t remainder = remainder_mask & dividend;

    // Basic division
    result = dividend >> exponent;

    // Adjust 'result' for rounding (mid point away from zero)
    int32_t threshold = remainder_mask >> 1;
    if (result < 0)
    {
        threshold++;
    }
    if (remainder > threshold)
    {
        result++;
    }

    return result;
}

/**
 * @brief           Requantize a given value.
 * @param[in]       val         Value to be requantized
 * @param[in]       multiplier  multiplier. Range {NN_Q31_MIN + 1, Q32_MAX}
 * @param[in]       shift       left or right shift for 'val * multiplier'
 *
 * @return          Returns (val * multiplier)/(2 ^ shift)
 *
 */
__STATIC_FORCEINLINE int32_t arm_nn_requantize(const int32_t val, const int32_t multiplier, const int32_t shift)
{
#ifdef CMSIS_NN_USE_SINGLE_ROUNDING
    const int64_t total_shift = 31 - shift;
    const int64_t new_val = val * (int64_t)multiplier;

    int32_t result = new_val >> (total_shift - 1);
    result = (result + 1) >> 1;

    return result;
#else
    return arm_nn_divide_by_power_of_two(arm_nn_doubling_high_mult_no_sat(val * (1 << LEFT_SHIFT(shift)), multiplier),
                                         RIGHT_SHIFT(shift));
#endif
}

/**
 * @brief           Requantize a given 64 bit value.
 * @param[in]       val                 Value to be requantized in the range {-(1<<47)} to {(1<<47) - 1}
 * @param[in]       reduced_multiplier  Reduced multiplier in the range {NN_Q31_MIN + 1, Q32_MAX} to {Q16_MIN + 1,
 * Q16_MAX}
 * @param[in]       shift               Left or right shift for 'val * multiplier' in the range {-31} to {7}
 *
 * @return          Returns (val * multiplier)/(2 ^ shift)
 *
 */
__STATIC_FORCEINLINE int32_t arm_nn_requantize_s64(const int64_t val,
                                                   const int32_t reduced_multiplier,
                                                   const int32_t shift)
{
    const int64_t new_val = val * reduced_multiplier;

    int32_t result = new_val >> (14 - shift); // 64->32 bit reduction
    result = (result + 1) >> 1;               // Last shift position and insert round

    return result;
}

/**
 * @brief           memcpy optimized for MVE
 * @param[in, out]  dst         Destination pointer
 * @param[in]       src         Source pointer.
 * @param[in]       block_size  Number of bytes to copy.
 *
 */
__STATIC_FORCEINLINE void arm_memcpy_s8(int8_t *__RESTRICT dst, const int8_t *__RESTRICT src, uint32_t block_size)
{
#if defined(ARM_MATH_MVEI)
    __asm volatile("   wlstp.8                 lr, %[cnt], 1f             \n"
                   "2:                                                    \n"
                   "   vldrb.8                 q0, [%[in]], #16            \n"
                   "   vstrb.8                 q0, [%[out]], #16           \n"
                   "   letp                    lr, 2b                     \n"
                   "1:                                                    \n"
                   : [in] "+r"(src), [out] "+r"(dst)
                   : [cnt] "r"(block_size)
                   : "q0", "memory", "r14");
#else
    memcpy(dst, src, block_size);
#endif
}

/**
 * @brief           memcpy wrapper for int16
 * @param[in, out]  dst         Destination pointer
 * @param[in]       src         Source pointer.
 * @param[in]       block_size  Number of bytes to copy.
 *
 */
__STATIC_FORCEINLINE void arm_memcpy_q15(int16_t *__RESTRICT dst, const int16_t *__RESTRICT src, uint32_t block_size)
{
    memcpy(dst, src, block_size);
}

#if defined(ARM_MATH_MVEI)
/**
 * @brief           Vector saturating doubling high multiply returning high half.
 * @param[in]       m1        Multiplicand
 * @param[in]       m2        Multiplier
 * @return          Result of multiplication.
 *
 */
__STATIC_FORCEINLINE int32x4_t arm_doubling_high_mult_mve(const int32x4_t m1, const int32_t m2)
{
    return vqrdmulhq_n_s32(m1, m2);
}

/**
 * @brief           Vector rounding divide by power of two.
 * @param[in]       dividend - Dividend vector
 * @param[in]       exponent - Divisor = power(2, exponent)
 *                             Range: [0, 31]
 * @return          Rounded result of division. Midpoint is rounded away from zero.
 *
 */
__STATIC_FORCEINLINE int32x4_t arm_divide_by_power_of_two_mve(const int32x4_t dividend, const int32_t exponent)
{
    const int32x4_t shift = vdupq_n_s32(-exponent);
    const int32x4_t fixup = vshrq_n_s32(vandq_s32(dividend, shift), 31);
    const int32x4_t fixed_up_dividend = vqaddq_s32(dividend, fixup);
    return vrshlq_s32(fixed_up_dividend, shift);
}

/**
 * @brief           Requantize a given vector.
 * @param[in]       val         Vector to be requantized
 * @param[in]       multiplier  multiplier
 * @param[in]       shift       shift
 *
 * @return          Returns (val * multiplier)/(2 ^ shift)
 *
 */
__STATIC_FORCEINLINE int32x4_t arm_requantize_mve(const int32x4_t val, const int32_t multiplier, const int32_t shift)
{
    #ifdef CMSIS_NN_USE_SINGLE_ROUNDING
    const int right_shift = MIN(-1, shift);
    const int left_shift = shift - right_shift;

    const int32x4_t left_shift_dup = vdupq_n_s32(left_shift);
    const int32x4_t right_shift_dup = vdupq_n_s32(right_shift);

    int32x4_t result = vqdmulhq_n_s32(vshlq_s32(val, left_shift_dup), multiplier);
    result = vrshlq_s32(result, right_shift_dup);

    return result;
    #else
    return arm_divide_by_power_of_two_mve(
        arm_doubling_high_mult_mve(vshlq_s32(val, vdupq_n_s32(LEFT_SHIFT(shift))), multiplier), RIGHT_SHIFT(shift));
    #endif
}

__STATIC_FORCEINLINE int32x4_t arm_doubling_high_mult_mve_32x4(const int32x4_t m1, const int32x4_t m2)
{
    return vqrdmulhq_s32(m1, m2);
}

__STATIC_FORCEINLINE int32x4_t arm_divide_by_power_of_two_mve_32x4(const int32x4_t dividend, const int32x4_t exponent)
{
    const int32x4_t shift = -exponent;
    const int32x4_t fixup = vshrq_n_s32(vandq_s32(dividend, shift), 31);
    const int32x4_t fixed_up_dividend = vqaddq_s32(dividend, fixup);
    return vrshlq_s32(fixed_up_dividend, shift);
}

__STATIC_FORCEINLINE int32x4_t arm_requantize_mve_32x4(const int32x4_t val,
                                                       const int32x4_t multiplier,
                                                       const int32x4_t shift)
{
    #ifdef CMSIS_NN_USE_SINGLE_ROUNDING
    const int32x4_t right_shift = vminq_s32(vdupq_n_s32(-1), shift);
    const int32x4_t left_shift = vqsubq_s32(shift, right_shift);

    int32x4_t result = vqdmulhq_s32(vshlq_s32(val, left_shift), multiplier);
    result = vrshlq_s32(result, right_shift);

    return result;
    #else
    const int32x4_t zz = vdupq_n_s32(0);
    const mve_pred16_t p = vcmpgtq_n_s32(shift, 0);

    const int32x4_t left_shift = vpselq_s32(shift, zz, p);
    const int32x4_t right_shift = -vpselq_s32(zz, shift, p);

    return arm_divide_by_power_of_two_mve_32x4(arm_doubling_high_mult_mve_32x4(vshlq_s32(val, left_shift), multiplier),
                                               right_shift);
    #endif
}
#endif

// @note The following functions are used only for softmax layer, scaled bits = 5 assumed

__STATIC_FORCEINLINE int32_t arm_nn_exp_on_negative_values(int32_t val)
{
    int32_t mask = 0;
    int32_t shift = 24;

    const int32_t val_mod_minus_quarter = (val & ((1 << shift) - 1)) - (1 << shift);
    const int32_t remainder = val_mod_minus_quarter - val;
    const int32_t x = (val_mod_minus_quarter << 5) + (1 << 28);
    const int32_t x2 = MUL_SAT(x, x);

    int32_t result = 1895147668 +
        MUL_SAT(1895147668, x + DIV_POW2(MUL_SAT(DIV_POW2(MUL_SAT(x2, x2), 2) + MUL_SAT(x2, x), 715827883) + x2, 1));

#define SELECT_IF_NON_ZERO(x)                                                                                          \
    {                                                                                                                  \
        mask = MASK_IF_NON_ZERO(remainder & (1 << shift++));                                                           \
        result = SELECT_USING_MASK(mask, MUL_SAT(result, x), result);                                                  \
    }

    SELECT_IF_NON_ZERO(1672461947)
    SELECT_IF_NON_ZERO(1302514674)
    SELECT_IF_NON_ZERO(790015084)
    SELECT_IF_NON_ZERO(290630308)
    SELECT_IF_NON_ZERO(39332535)
    SELECT_IF_NON_ZERO(720401)
    SELECT_IF_NON_ZERO(242)

#undef SELECT_IF_NON_ZERO

    mask = MASK_IF_ZERO(val);
    return SELECT_USING_MASK(mask, NN_Q31_MAX, result);
}

__STATIC_FORCEINLINE int32_t arm_nn_mult_by_power_of_two(const int32_t val, const int32_t exp)
{
    const int32_t thresh = ((1 << (31 - exp)) - 1);
    int32_t result = val << exp;
    result = SELECT_USING_MASK(MASK_IF_NON_ZERO(val > thresh), NN_Q31_MAX, result);
    result = SELECT_USING_MASK(MASK_IF_NON_ZERO(val < -thresh), NN_Q31_MIN, result);
    return result;
}

__STATIC_FORCEINLINE int32_t arm_nn_one_over_one_plus_x_for_x_in_0_1(int32_t val)
{
    const int64_t sum = (int64_t)val + (int64_t)NN_Q31_MAX;
    const int32_t half_denominator = (int32_t)((sum + (sum >= 0 ? 1 : -1)) / 2L);
    int32_t x = 1515870810 + MUL_SAT(half_denominator, -1010580540);

    const int32_t shift = (1 << 29);
    x += MUL_POW2(MUL_SAT(x, shift - MUL_SAT(half_denominator, x)), 2);
    x += MUL_POW2(MUL_SAT(x, shift - MUL_SAT(half_denominator, x)), 2);
    x += MUL_POW2(MUL_SAT(x, shift - MUL_SAT(half_denominator, x)), 2);

    return MUL_POW2(x, 1);
}

/**
  @brief         Write 2 s16 elements and post increment pointer.
  @param[in]     dest_q15  Pointer to pointer that holds address of destination.
  @param[in]     src_q31   Input value to be written.
 */
__STATIC_FORCEINLINE void arm_nn_write_q15x2_ia(int16_t **dest_q15, int32_t src_q31)
{
    int32_t val = src_q31;

    memcpy(*dest_q15, &val, 4);
    *dest_q15 += 2;
}

/**
  @brief         Write 2 s8 elements and post increment pointer.
  @param[in]     dst  Pointer to pointer that holds address of destination.
  @param[in]     src  Input value to be written.
 */
__STATIC_FORCEINLINE void arm_nn_write_s8x2_ia(int8_t **dst, int16_t src)
{
    memcpy(*dst, &src, 2);
    *dst += 2;
}

// Support functions for LSTM
/**
 * @brief Update LSTM function for an iteration step
 *
 * param[in]    input                           Input data
 * param[in]    input_to_input_weight           Input to input gate weights
 * param[in]    input_to_forget_weight          Input to forget gate weights
 * param[in]    input_to_cell_weight            Input to cell gate weights
 * param[in]    input_to_output_weight          Input to output weights
 * param[in]    recurrent_to_input_weight       Recurrent signal to input weights
 * param[in]    recurrent_to_forget_weight      Recurrent signal to forget gate weights
 * param[in]    recurrent_to_cell_weight        Recurrent signal to cell gate weighst
 * param[in]    recurrent_to_output_weight      Recurrent signal to output weights
 * param[in]    lstm                            LSTM parameters
 * param[in]    n_batch                         Batch size
 * param[in]    n_cell                          Cell size
 * param[in]    n_input                         Input size
 * param[in]    n_output                        Output size
 * param[out]   output_state                    Output state
 * param[out]   cell_state                      Internal state
 * param[out]   output                          Output signal
 * param[in] *scratch_buffers                   Struct containing scratch buffers
 */
arm_cmsis_nn_status arm_nn_lstm_step_s8_s16(const int8_t *input,
                                            const int8_t *input_to_input_weight,
                                            const int8_t *input_to_forget_weight,
                                            const int8_t *input_to_cell_weight,
                                            const int8_t *input_to_output_weight,
                                            const int8_t *recurrent_to_input_weight,
                                            const int8_t *recurrent_to_forget_weight,
                                            const int8_t *recurrent_to_cell_weight,
                                            const int8_t *recurrent_to_output_weight,
                                            const cmsis_nn_lstm_params *lstm,
                                            const int n_batch,
                                            const int n_cell,
                                            const int n_input,
                                            const int n_output,
                                            int8_t *output_state,
                                            int16_t *cell_state,
                                            int8_t *output,
                                            cmsis_nn_lstm_context *scratch_buffers);

/**
 * @brief         Updates a LSTM gate for an iteration step of LSTM function, int8x8_16 version.
 *
 * param[in]    input                           Input data
 * param[in]    input_to_gate_weights           Input to gate weights
 * param[in]    input_to_gate_bias              Input to gate weights
 * param[in]    input_to_gate_scaling           Input to gate scaling
 * param[in]    activation                      Actival min and max values
 * param[in]    output_state                    Output state
 * param[in]    recurrent_to_gate_weights       Recurrent to gate weights
 * param[in]    recurrent_to_gate_bias          Recurrent to gate bias
 * param[in]    recurrent_to_gate_scaling       Recurrent to gate scaling
 * param[in]    n_batch                         Batch size
 * param[in]    n_input                         Input size
 * param[out]   n_output                        Output size
 * param[in]    activation_type                 Activation type (sigmoid or tanh)
 * param[out]   n_cell                          Cell size
 */
void arm_nn_lstm_calculate_gate_s8_s16(const int8_t *input,
                                       const int8_t *input_to_gate_weights,
                                       const int32_t *input_to_gate_bias,
                                       const cmsis_nn_scaling input_to_gate_scaling,
                                       const int8_t *output_state,
                                       const int8_t *recurrent_to_gate_weights,
                                       const int32_t *recurrent_to_gate_bias,
                                       const cmsis_nn_scaling recurrent_to_gate_scaling,
                                       const int32_t n_batch,
                                       const int32_t n_input,
                                       const int32_t n_output,
                                       const int32_t n_cell,
                                       const arm_nn_activation_type activation_type,
                                       int16_t *gate);

/**
 * @brief       Update cell state for a single LSTM iteration step, int8x8_16 version.
 * @param[in]   n_block             total number of cells for all batches
 * @param[in]   cell_state_scale    Scaling factor of cell state
 * @param[in]   cell_state          Input/output vector, size n_batch*n_cell
 * @param[in]   input_gate          Input vector of size n_block
 * @param[in]   forget_gate         Input/scratch vector of size n_block, always modified
 * @param[in]   cell_gate           Input vector of size, n_block
 */
void arm_nn_lstm_update_cell_state_s16(const int32_t n_block,
                                       const int32_t cell_state_scale,
                                       int16_t *cell_state,
                                       const int16_t *input_gate,
                                       const int16_t *forget_gate,
                                       const int16_t *cell_gate);

/**
 * @brief       Calculate the output state tensor of an LSTM step, s8 input/output and s16 weight version.
 *
 * @param[in]       n_batch                     The number of distinct vectors in each array
 * @param[in]       n_cell                      Number of cells
 * @param[in,out]   cell_state                  Cell state, size n_batch*n_cell
 * @param[in]       cell_state_scale            Scaling of cell_state
 * @param[in]       output_gate                 Output gate
 * @param[in]       hidden_scale                Effective scaling of cell_state .* output_gate
 * @param[in]       hidden_offset               Zero point for cell_state .* output_gate
 * @param[out]      output_state                Output state
 * @param[in]       cell_gate_scratch           Scratch buffer
 */
void arm_nn_lstm_update_output_s8_s16(const int n_batch,
                                      const int n_cell,
                                      int16_t *cell_state,
                                      const int32_t cell_state_scale,
                                      const int16_t *output_gate,
                                      const cmsis_nn_scaling hidden_scale,
                                      const int32_t hidden_offset,
                                      int8_t *output_state,
                                      int16_t *cell_gate_scratch);

/**
 * @brief The result of the multiplication is accumulated to the passed result buffer.
 * Multiplies a matrix by a "batched" vector (i.e. a matrix with a batch dimension composed by input vectors independent
 * from each other).
 *
 * @param[in]   lhs_in           Batched vector
 * @param[in]   rhs_in           Weights - input matrix (H(Rows)xW(Columns))
 * @param[in]   bias             Bias vector
 * @param[out]  dst              Output
 * @param[in]   dst_offset       Output offset
 * @param[in]   dst_multiplier   Multiplier for quantization
 * @param[in]   dst_shift        Shift for quantization
 * @param[in]   rhs_cols         Vector/matarix column length
 * @param[in]   rhs_rows         Row count of matrix
 * @param[in]   batch            Batch size
 */
void arm_nn_vec_mat_mul_result_acc_s8(const int8_t *lhs_in,
                                      const int8_t *rhs_in,
                                      const int32_t *bias,
                                      int16_t *dst,
                                      const int32_t dst_offset,
                                      const int32_t dst_multiplier,
                                      const int32_t dst_shift,
                                      const int32_t rhs_cols,
                                      const int32_t rhs_rows,
                                      const int32_t batch);

/**
 * @brief s16 elementwise multiplication with s8 output
 * @param[in]       input_1_vect        pointer to input vector 1
 * @param[in]       input_2_vect        pointer to input vector 2
 * @param[in,out]   output              pointer to output vector
 * @param[in]       out_offset          output offset
 * @param[in]       out_mult            output multiplier
 * @param[in]       out_shift           output shift
 * @param[in]       block_size          number of samples
 * @return          The function returns ARM_CMSIS_NN_SUCCESS
 *
 * @details   Supported framework: TensorFlow Lite micro
 */
arm_cmsis_nn_status arm_elementwise_mul_s16_s8(const int16_t *input_1_vect,
                                               const int16_t *input_2_vect,
                                               int8_t *output,
                                               const int32_t out_offset,
                                               const int32_t out_mult,
                                               const int32_t out_shift,
                                               const int32_t block_size);

#ifdef __cplusplus
}
#endif

#endif
