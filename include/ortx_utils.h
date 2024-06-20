// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "ortx_types.h"

const int API_VERSION = 1;

typedef enum {
  kOrtxKindUnknown = 0,

  kOrtxKindBegin = 0x7788,  // starting from a number to help validate the object
  kOrtxKindTokenizer = kOrtxKindBegin,
  kOrtxKindStringArray = 0x7789,
  kOrtxKindTokenId2DArray = 0x778A,
  kOrtxKindDetokenizerCache = 0x778B,
  kOrtxKindProcessor = 0x778C,
  kOrtxKindRawImages = 0x778D,
  kOrtxKindImageProcessorResult = 0x778E,
  kOrtxKindProcessorResult = 0x778F,
  kOrtxKindTensor = 0x7790,
  kOrtxKindEnd = 0x7999
} extObjectKind_t;

// all object managed by the library should be 'derived' from this struct
// which eventually will be released by TfmDispose if C++, or TFM_DISPOSE if C
typedef struct {
  int ext_kind_;
} OrtxObject;

typedef OrtxObject OrtxTensor;

// C, instead of C++ doesn't cast automatically,
// so we need to use a macro to cast the object to the correct type
#define ORTX_DISPOSE(obj) OrtxDispose((OrtxObject**)&obj)

typedef uint32_t extTokenId_t;

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Get the current C ABI version of this library
 *
 * \snippet{doc} snippets.dox int Return Value
 */
int ORTX_API_CALL OrtxGetAPIVersion(void);

/** \brief Get the last error message generated by the library
 *
 * \param message Pointer to store the last error message
 * \return Pointer to the last error message
 */
const char* ORTX_API_CALL OrtxGetLastErrorMessage(void);

/** \brief Create a new object of the specified kind
 *
 * \param kind The kind of object to create
 * \param object Pointer to store the created object
 * \param ... Additional arguments based on the kind of object
 * \return Error code indicating the success or failure of the operation
 */
extError_t ORTX_API_CALL OrtxCreate(extObjectKind_t kind, OrtxObject** object, ...);

/** \brief Dispose the specified object
 *
 * \param object Pointer to the object to dispose
 * \return Error code indicating the success or failure of the operation
 */
extError_t ORTX_API_CALL OrtxDispose(OrtxObject** object);

/** \brief Dispose the specified object
 *
 * \param object Pointer to the object to dispose
 * \return Error code indicating the success or failure of the operation
 */
extError_t ORTX_API_CALL OrtxDisposeOnly(OrtxObject* object);

/** \brief Get the data from the tensor
 *
 * \param tensor The tensor object
 * \param data Pointer to store the data
 * \param shape Pointer to store the shape
 * \param num_dims Pointer to store the number of dimensions
 * \return Error code indicating the success or failure of the operation
 */
extError_t ORTX_API_CALL OrtxGetTensorData(OrtxTensor* tensor, const void** data, const int64_t** shape,
                                           size_t* num_dims);
/**
 * \brief Get the data from the tensor as int64_t type
 *
 * \param tensor The tensor object
 * \param data Pointer to store the data
 * \param shape Pointer to store the shape
 * \param num_dims Pointer to store the number of dimensions
 * \return Error code indicating the success or failure of the operation
 */

extError_t ORTX_API_CALL OrtxGetTensorDataInt64(OrtxTensor* tensor, const int64_t** data, const int64_t** shape,
                                                size_t* num_dims);

/**
 * \brief Get the data from the tensor as float type
 *
 * \param tensor The tensor object
 * \param data Pointer to store the data
 * \param shape Pointer to store the shape
 * \param num_dims Pointer to store the number of dimensions
 * \return Error code indicating the success or failure of the operation
 */
extError_t ORTX_API_CALL OrtxGetTensorDataFloat(OrtxTensor* tensor, const float** data, const int64_t** shape,
                                                size_t* num_dims);

#ifdef __cplusplus
}
#endif
