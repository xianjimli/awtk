﻿#include "gtest/gtest.h"
#include "base/combo_box.h"

#include <string>

using std::string;

TEST(ComboBox, basic) {
  value_t v1;
  value_t v2;
  widget_t* w = combo_box_create(NULL, 10, 20, 30, 40);
  combo_box_t* combo_box = COMBO_BOX(w);

  value_set_str(&v1, "window");
  ASSERT_EQ(widget_set_prop(w, WIDGET_PROP_OPEN_WINDOW, &v1), RET_OK);
  ASSERT_EQ(widget_get_prop(w, WIDGET_PROP_OPEN_WINDOW, &v2), RET_OK);
  ASSERT_EQ(strcmp(v1.value.str, v2.value.str), 0);
  ASSERT_EQ(strcmp(v1.value.str, combo_box->open_window), 0);

  value_set_int(&v1, 1);
  ASSERT_EQ(widget_set_prop(w, WIDGET_PROP_SELECTED_INDEX, &v1), RET_OK);
  ASSERT_EQ(widget_get_prop(w, WIDGET_PROP_SELECTED_INDEX, &v2), RET_OK);
  ASSERT_EQ(value_int(&v1), value_int(&v2));
  ASSERT_EQ(value_int(&v1), combo_box->selected_index);

  widget_destroy(w);
}

TEST(ComboBox, options) {
  widget_t* w = combo_box_create(NULL, 10, 20, 30, 40);

  ASSERT_EQ(combo_box_count_options(w), 0);
  ASSERT_EQ(combo_box_append_option(w, 1, "red"), RET_OK);
  ASSERT_EQ(combo_box_count_options(w), 1);

  ASSERT_EQ(combo_box_append_option(w, 2, "green"), RET_OK);
  ASSERT_EQ(combo_box_count_options(w), 2);

  ASSERT_EQ(combo_box_append_option(w, 3, "blue"), RET_OK);
  ASSERT_EQ(combo_box_count_options(w), 3);

  combo_box_set_selected_index(w, 0);
  ASSERT_EQ(combo_box_get_value(w), 1);
  ASSERT_EQ(string(combo_box_get_text(w)), string("red"));

  combo_box_set_selected_index(w, 1);
  ASSERT_EQ(combo_box_get_value(w), 2);
  ASSERT_EQ(string(combo_box_get_text(w)), string("green"));

  combo_box_reset_options(w);
  ASSERT_EQ(combo_box_count_options(w), 0);

  widget_destroy(w);
}

TEST(ComboBox, parse_options) {
  widget_t* w = combo_box_create(NULL, 10, 20, 30, 40);

  combo_box_parse_options(w, "1:red;2:green;3:blue");
  ASSERT_EQ(combo_box_count_options(w), 3);

  combo_box_set_selected_index(w, 0);
  ASSERT_EQ(combo_box_get_value(w), 1);
  ASSERT_EQ(string(combo_box_get_text(w)), string("red"));

  combo_box_set_selected_index(w, 1);
  ASSERT_EQ(combo_box_get_value(w), 2);
  ASSERT_EQ(string(combo_box_get_text(w)), string("green"));

  combo_box_reset_options(w);
  ASSERT_EQ(combo_box_count_options(w), 0);

  widget_destroy(w);
}

TEST(ComboBox, props) {
  value_t v1;
  value_t v2;
  const char* str = "1:red;2:green;3:blue";
  widget_t* w = combo_box_create(NULL, 10, 20, 30, 40);

  value_set_str(&v1, str);
  ASSERT_EQ(combo_box_cast(w), w);
  ASSERT_EQ(widget_set_prop(w, WIDGET_PROP_OPTIONS, &v1), RET_OK);
  ASSERT_EQ(widget_get_prop(w, WIDGET_PROP_OPTIONS, &v2), RET_OK);
  ASSERT_EQ(string(value_str(&v2)), string(str));
  ASSERT_EQ(combo_box_count_options(w), 3);

  widget_destroy(w);
}

#include "log_change_events.inc"

TEST(ComboBox, event) {
  const char* str = "1:red;2:green;3:blue";
  widget_t* w = combo_box_create(NULL, 0, 0, 100, 100);
  combo_box_set_options(w, str);
  combo_box_set_selected_index(w, 0);

  s_log = "";
  widget_on(w, EVT_VALUE_WILL_CHANGE, on_change_events, NULL);
  widget_on(w, EVT_VALUE_CHANGED, on_change_events, NULL);

  combo_box_set_selected_index(w, 0);
  ASSERT_EQ(s_log, "");

  combo_box_set_selected_index(w, 1);
  ASSERT_EQ(s_log, "will_change;change;");

  widget_destroy(w);
}
