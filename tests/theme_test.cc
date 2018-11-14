﻿
#include "base/array.h"
#include "base/enums.h"
#include "base/theme.h"
#include "base/widget.h"
#include "base/buffer.h"
#include "tools/theme_gen/theme_gen.h"
#include "gtest/gtest.h"
#include <stdlib.h>

#include <string>
using std::string;

static const char* widget_types[] = {WIDGET_TYPE_WINDOW_MANAGER,
                                     WIDGET_TYPE_NORMAL_WINDOW,
                                     WIDGET_TYPE_TOOL_BAR,
                                     WIDGET_TYPE_DIALOG,
                                     WIDGET_TYPE_POPUP,
                                     WIDGET_TYPE_SPRITE,
                                     WIDGET_TYPE_KEYBOARD,
                                     WIDGET_TYPE_DND,
                                     WIDGET_TYPE_LABEL,
                                     WIDGET_TYPE_BUTTON,
                                     WIDGET_TYPE_IMAGE,
                                     WIDGET_TYPE_EDIT,
                                     WIDGET_TYPE_PROGRESS_BAR,
                                     WIDGET_TYPE_GROUP_BOX,
                                     WIDGET_TYPE_CHECK_BUTTON,
                                     WIDGET_TYPE_RADIO_BUTTON,
                                     WIDGET_TYPE_DIALOG_TITLE,
                                     WIDGET_TYPE_DIALOG_CLIENT,
                                     WIDGET_TYPE_SLIDER,
                                     WIDGET_TYPE_VIEW,
                                     WIDGET_TYPE_COMBO_BOX,
                                     WIDGET_TYPE_COMBO_BOX_ITEM,
                                     WIDGET_TYPE_SLIDE_VIEW,
                                     WIDGET_TYPE_PAGES,
                                     WIDGET_TYPE_TAB_BUTTON,
                                     WIDGET_TYPE_TAB_CONTROL,
                                     WIDGET_TYPE_TAB_BUTTON_GROUP,
                                     WIDGET_TYPE_BUTTON_GROUP,
                                     WIDGET_TYPE_CANDIDATES,
                                     WIDGET_TYPE_SPIN_BOX,
                                     WIDGET_TYPE_DRAGGER,
                                     WIDGET_TYPE_SCROLL_BAR,
                                     WIDGET_TYPE_SCROLL_BAR_DESKTOP,
                                     WIDGET_TYPE_SCROLL_BAR_MOBILE,
                                     WIDGET_TYPE_SCROLL_VIEW,
                                     WIDGET_TYPE_LIST_VIEW,
                                     WIDGET_TYPE_LIST_VIEW_H,
                                     WIDGET_TYPE_LIST_ITEM,
                                     NULL};
void GenThemeData(uint8_t* buff, uint32_t size, uint32_t state_nr, uint32_t name_nr) {
  ThemeGen g;
  for (int32_t i = 0; widget_types[i]; i++) {
    const char* type = widget_types[i];
    for (uint32_t state = 0; state < state_nr; state++) {
      Style s(type, TK_DEFAULT_STYLE, state);
      for (uint32_t name = 0; name < name_nr; name++) {
        char str[32];
        snprintf(str, sizeof(str), "%d", name);
        s.AddInt(name, name);
        s.AddString(name, str);
      }
      g.AddStyle(s);
    }
  }

  g.Output(buff, size);
}

TEST(Theme, saveLoad) {
  uint8_t v8;
  uint16_t v16;
  uint32_t v32;
  uint8_t buff[7];
  uint8_t* p = buff;

  save_uint8(p, 0x1f);
  save_uint16(p, 0x2f2f);
  save_uint32(p, 0x3f3f3f3f);

  p = buff;
  load_uint8(p, v8);
  ASSERT_EQ(v8, 0x1f);

  load_uint16(p, v16);
  ASSERT_EQ(v16, 0x2f2f);

  load_uint32(p, v32);
  ASSERT_EQ(v32, 0x3f3f3f3f);
}

TEST(Theme, basic) {
  uint8_t buff[4 * 10240];
  uint32_t state_nr = 5;
  uint32_t name_nr = 5;
  theme_t t;
  const uint8_t* style_data;

  GenThemeData(buff, sizeof(buff), state_nr, name_nr);
  t.data = buff;

  for (int32_t i = 0; widget_types[i]; i++) {
    const char* type = widget_types[i];
    for (uint32_t state = 0; state < state_nr; state++) {
      style_data = theme_find_style(&t, type, 0, (widget_state_t)state);
      ASSERT_EQ(style_data != NULL, true);
      for (uint32_t name = 0; name < name_nr; name++) {
        uint32_t v = style_data_get_int(style_data, name, 0);
        ASSERT_EQ(v, name);
        v = atoi(style_data_get_str(style_data, name, NULL));
        ASSERT_EQ(v, name);
      }
    }
  }
}
