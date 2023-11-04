#ifndef HALIDE_____hdrplus_pipeline_h
#define HALIDE_____hdrplus_pipeline_h
#include <stdint.h>

// Forward declarations of the types used in the interface
// to the Halide pipeline.
//
// For the definitions of these structs, include HalideRuntime.h

// Halide's representation of a multi-dimensional array.
// Halide::Runtime::Buffer is a more user-friendly wrapper
// around this. Its declaration is in HalideBuffer.h
struct halide_buffer_t;

// Metadata describing the arguments to the generated function.
// Used to construct calls to the _argv version of the function.
struct halide_filter_metadata_t;

#ifndef HALIDE_MUST_USE_RESULT
#ifdef __has_attribute
#if __has_attribute(nodiscard)
#define HALIDE_MUST_USE_RESULT [[nodiscard]]
#elif __has_attribute(warn_unused_result)
#define HALIDE_MUST_USE_RESULT __attribute__((warn_unused_result))
#else
#define HALIDE_MUST_USE_RESULT
#endif
#else
#define HALIDE_MUST_USE_RESULT
#endif
#endif

#ifndef HALIDE_FUNCTION_ATTRS
#define HALIDE_FUNCTION_ATTRS
#endif



#ifdef __cplusplus
extern "C" {
#endif

HALIDE_FUNCTION_ATTRS
int hdrplus_pipeline(struct halide_buffer_t *_inputs_buffer, uint16_t _black_point, uint16_t _white_point, float _white_balance_r, float _white_balance_g0, float _white_balance_g1, float _white_balance_b, int32_t _cfa_pattern, struct halide_buffer_t *_ccm_buffer, float _compression, float _gain, struct halide_buffer_t *_8bit_interleaved_output_buffer);

HALIDE_FUNCTION_ATTRS
int hdrplus_pipeline_argv(void **args);

HALIDE_FUNCTION_ATTRS
const struct halide_filter_metadata_t *hdrplus_pipeline_metadata();

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
