/*
 * Copyright (c) 2017-2018 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "arm_compute/runtime/NEON/functions/NEIm2Col.h"

#include "arm_compute/core/TensorInfo.h"
#include "arm_compute/runtime/NEON/NEScheduler.h"
#include "support/ToolchainSupport.h"

using namespace arm_compute;

NEIm2Col::NEIm2Col()
    : _kernel(), _y_dim(1)
{
}

void NEIm2Col::configure(const ITensor *input, ITensor *output, const Size2D &kernel_dims, const PadStrideInfo &conv_info, bool has_bias, bool is_fully_connected, bool is_flatten)
{
    _y_dim = get_data_layout_dimension_index(input->info()->data_layout(), DataLayoutDimension::HEIGHT);

    _kernel.configure(input, output, kernel_dims, conv_info, has_bias, is_fully_connected, is_flatten);
}

Status NEIm2Col::validate(const ITensorInfo *input, const ITensorInfo *output, const Size2D &kernel_dims, const PadStrideInfo &conv_info, bool has_bias, bool is_fully_connected, bool is_flatten)
{
    return NEIm2ColKernel::validate(input, output, kernel_dims, conv_info, has_bias, is_fully_connected, is_flatten);
}

void NEIm2Col::run()
{
    NEScheduler::get().schedule(&_kernel, _y_dim);
}
