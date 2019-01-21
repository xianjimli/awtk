﻿/**
 * File:   fill_image_rgb565.c
 * Author: AWTK Develop Team
 * Brief:  fill on rgb565
 *
 * Copyright (c) 2018 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-10-10 Generated by gen.sh(DONT MODIFY IT)
 *
 */
#include "tkc/rect.h"
#include "base/pixel.h"
#include "base/bitmap.h"
#include "base/pixel_pack_unpack.h"

#define pixel_dst_t pixel_rgb565_t
#define pixel_dst_format pixel_rgb565_format
#define pixel_dst_to_rgba pixel_rgb565_to_rgba
#define pixel_dst_from_rgb pixel_rgb565_from_rgb

#define pixel_t pixel_dst_t
#define pixel_from_rgb pixel_dst_from_rgb
#define pixel_to_rgba pixel_dst_to_rgba

#include "pixel_ops.inc"
#include "fill_image.inc"

ret_t fill_rgb565_rect(bitmap_t* fb, rect_t* dst, color_t c) {
  return fill_image(fb, dst, c);
}
