﻿/**
 * File:   lcd_mem_bgr565.h
 * Author: AWTK Develop Team
 * Brief:  bgr565 mem lcd.
 *
 * Copyright (c) 2018 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * license file for more details.
 *
 */

/**
 * history:
 * ================================================================
 * 2018-10-09 Generated by gen.sh(DONT MODIFY IT)
 *
 */

#ifndef TK_LCD_MEM_BGR565_H
#define TK_LCD_MEM_BGR565_H

#include "lcd/lcd_mem.h"

BEGIN_C_DECLS

lcd_t* lcd_mem_bgr565_create(wh_t w, wh_t h, bool_t alloc);
lcd_t* lcd_mem_bgr565_create_single_fb(wh_t w, wh_t h, uint8_t* fbuff);
lcd_t* lcd_mem_bgr565_create_double_fb(wh_t w, wh_t h, uint8_t* online_fb, uint8_t* offline_fb);
lcd_t* lcd_mem_bgr565_create_three_fb(wh_t w, wh_t h, uint8_t* online_fb, uint8_t* offline_fb,
                                      uint8_t* next_fb);

END_C_DECLS

#endif /*TK_LCD_MEM_BGR565_H*/
