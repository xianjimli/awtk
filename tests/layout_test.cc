﻿#include "base/layout.h"
#include "base/group_box.h"
#include "gtest/gtest.h"

TEST(Layuout, basic) {
  rect_t r;
  widget_layout_t layout;
  ASSERT_EQ(widget_layout_parse(&layout, "1", "2", "3", "4"), &layout);
  ASSERT_EQ(layout.x, 1);
  ASSERT_EQ(layout.y, 2);
  ASSERT_EQ(layout.w, 3);
  ASSERT_EQ(layout.h, 4);
  ASSERT_EQ(layout.x_attr, X_ATTR_DEFAULT);
  ASSERT_EQ(layout.y_attr, Y_ATTR_DEFAULT);
  ASSERT_EQ(layout.w_attr, W_ATTR_PIXEL);
  ASSERT_EQ(layout.h_attr, H_ATTR_PIXEL);

  widget_layout_calc(&layout, &r, 100, 200);
  ASSERT_EQ(r.x, 1);
  ASSERT_EQ(r.y, 2);
  ASSERT_EQ(r.w, 3);
  ASSERT_EQ(r.h, 4);
}

TEST(Layuout, negetive) {
  rect_t r;
  widget_layout_t layout;
  ASSERT_EQ(widget_layout_parse(&layout, "1", "2", "-10", "-40"), &layout);
  ASSERT_EQ(layout.x, 1);
  ASSERT_EQ(layout.y, 2);
  ASSERT_EQ(layout.w, -10);
  ASSERT_EQ(layout.h, -40);
  ASSERT_EQ(layout.x_attr, X_ATTR_DEFAULT);
  ASSERT_EQ(layout.y_attr, Y_ATTR_DEFAULT);
  ASSERT_EQ(layout.w_attr, W_ATTR_PIXEL);
  ASSERT_EQ(layout.h_attr, H_ATTR_PIXEL);

  widget_layout_calc(&layout, &r, 100, 200);
  ASSERT_EQ(r.x, 1);
  ASSERT_EQ(r.y, 2);
  ASSERT_EQ(r.w, 100 - 10);
  ASSERT_EQ(r.h, 200 - 40);
}

TEST(Layuout, negetivepercent) {
  rect_t r;
  widget_layout_t layout;
  ASSERT_EQ(widget_layout_parse(&layout, "1", "2", "-10%", "-40%"), &layout);
  ASSERT_EQ(layout.x, 1);
  ASSERT_EQ(layout.y, 2);
  ASSERT_EQ(layout.w, -10);
  ASSERT_EQ(layout.h, -40);
  ASSERT_EQ(layout.x_attr, X_ATTR_DEFAULT);
  ASSERT_EQ(layout.y_attr, Y_ATTR_DEFAULT);
  ASSERT_EQ(layout.w_attr, W_ATTR_PERCENT);
  ASSERT_EQ(layout.h_attr, H_ATTR_PERCENT);

  widget_layout_calc(&layout, &r, 100, 200);
  ASSERT_EQ(r.x, 1);
  ASSERT_EQ(r.y, 2);
  ASSERT_EQ(r.w, 90);
  ASSERT_EQ(r.h, 120);
}

TEST(Layuout, fill) {
  widget_layout_t layout;
  ASSERT_EQ(widget_layout_parse(&layout, "1", "2", "fill", "fill"), &layout);
  ASSERT_EQ(layout.w_attr, W_ATTR_FILL);
  ASSERT_EQ(layout.h_attr, H_ATTR_FILL);
}

TEST(Layuout, percent) {
  rect_t r;
  widget_layout_t layout;
  ASSERT_EQ(widget_layout_parse(&layout, "1%", "2%", "3%", "4%"), &layout);
  ASSERT_EQ(layout.x, 1);
  ASSERT_EQ(layout.y, 2);
  ASSERT_EQ(layout.w, 3);
  ASSERT_EQ(layout.h, 4);
  ASSERT_EQ(layout.x_attr, X_ATTR_PERCENT);
  ASSERT_EQ(layout.y_attr, Y_ATTR_PERCENT);
  ASSERT_EQ(layout.w_attr, W_ATTR_PERCENT);
  ASSERT_EQ(layout.h_attr, H_ATTR_PERCENT);

  widget_layout_calc(&layout, &r, 100, 200);
  ASSERT_EQ(r.x, 1);
  ASSERT_EQ(r.y, 4);
  ASSERT_EQ(r.w, 3);
  ASSERT_EQ(r.h, 8);
}

TEST(Layuout, center_middle) {
  rect_t r;
  widget_layout_t layout;
  ASSERT_EQ(widget_layout_parse(&layout, "center", "middle", "30%", "40%"), &layout);
  ASSERT_EQ(layout.x, 0);
  ASSERT_EQ(layout.y, 0);
  ASSERT_EQ(layout.x_attr, X_ATTR_CENTER);
  ASSERT_EQ(layout.y_attr, Y_ATTR_MIDDLE);

  widget_layout_calc(&layout, &r, 100, 200);
  ASSERT_EQ(r.x, 35);
  ASSERT_EQ(r.y, 60);
  ASSERT_EQ(r.w, 30);
  ASSERT_EQ(r.h, 80);
}

TEST(Layuout, center_middle1) {
  rect_t r;
  widget_layout_t layout;
  ASSERT_EQ(widget_layout_parse(&layout, "center:1", "middle:2", "30%", "40%"), &layout);
  ASSERT_EQ(layout.x, 1);
  ASSERT_EQ(layout.y, 2);
  ASSERT_EQ(layout.x_attr, X_ATTR_CENTER);
  ASSERT_EQ(layout.y_attr, Y_ATTR_MIDDLE);

  widget_layout_calc(&layout, &r, 100, 200);
  ASSERT_EQ(r.x, 36);
  ASSERT_EQ(r.y, 62);
  ASSERT_EQ(r.w, 30);
  ASSERT_EQ(r.h, 80);
}

TEST(Layuout, center_middle2) {
  rect_t r;
  widget_layout_t layout;
  ASSERT_EQ(widget_layout_parse(&layout, "c:1", "m:2", "30%", "40%"), &layout);
  ASSERT_EQ(layout.x, 1);
  ASSERT_EQ(layout.y, 2);
  ASSERT_EQ(layout.x_attr, X_ATTR_CENTER);
  ASSERT_EQ(layout.y_attr, Y_ATTR_MIDDLE);

  widget_layout_calc(&layout, &r, 100, 200);
  ASSERT_EQ(r.x, 36);
  ASSERT_EQ(r.y, 62);
  ASSERT_EQ(r.w, 30);
  ASSERT_EQ(r.h, 80);
}

TEST(Layuout, right_bottom) {
  rect_t r;
  widget_layout_t layout;
  ASSERT_EQ(widget_layout_parse(&layout, "right", "bottom", "30%", "40%"), &layout);
  ASSERT_EQ(layout.x, 0);
  ASSERT_EQ(layout.y, 0);
  ASSERT_EQ(layout.x_attr, X_ATTR_RIGHT);
  ASSERT_EQ(layout.y_attr, Y_ATTR_BOTTOM);

  widget_layout_calc(&layout, &r, 100, 200);
  ASSERT_EQ(r.x, 70);
  ASSERT_EQ(r.y, 120);
  ASSERT_EQ(r.w, 30);
  ASSERT_EQ(r.h, 80);
}

TEST(Layuout, right_bottom1) {
  rect_t r;
  widget_layout_t layout;
  ASSERT_EQ(widget_layout_parse(&layout, "right:1", "bottom:2", "30%", "40%"), &layout);
  ASSERT_EQ(layout.x, 1);
  ASSERT_EQ(layout.y, 2);
  ASSERT_EQ(layout.x_attr, X_ATTR_RIGHT);
  ASSERT_EQ(layout.y_attr, Y_ATTR_BOTTOM);

  widget_layout_calc(&layout, &r, 100, 200);
  ASSERT_EQ(r.x, 69);
  ASSERT_EQ(r.y, 118);
  ASSERT_EQ(r.w, 30);
  ASSERT_EQ(r.h, 80);
}

TEST(Layuout, right_bottom2) {
  rect_t r;
  widget_layout_t layout;
  ASSERT_EQ(widget_layout_parse(&layout, "r:1", "b:2", "30%", "40%"), &layout);
  ASSERT_EQ(layout.x, 1);
  ASSERT_EQ(layout.y, 2);
  ASSERT_EQ(layout.x_attr, X_ATTR_RIGHT);
  ASSERT_EQ(layout.y_attr, Y_ATTR_BOTTOM);

  widget_layout_calc(&layout, &r, 100, 200);
  ASSERT_EQ(r.x, 69);
  ASSERT_EQ(r.y, 118);
  ASSERT_EQ(r.w, 30);
  ASSERT_EQ(r.h, 80);
}

TEST(Layuout, layout_children_null) {
  widget_layout_t layout;
  widget_t* win = group_box_create(NULL, 0, 0, 200, 200);
  widget_t* g1 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g2 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g3 = group_box_create(win, 0, 0, 0, 0);

  widget_set_self_layout(g1, widget_layout_parse(&layout, "1", "2", "3", "4"));
  widget_layout(win);
  ASSERT_EQ(g1->x, 1);
  ASSERT_EQ(g1->y, 2);
  ASSERT_EQ(g1->w, 3);
  ASSERT_EQ(g1->h, 4);

  widget_set_self_layout(g1, widget_layout_parse(&layout, "0", "0", "10", "4"));
  widget_set_self_layout(g2, widget_layout_parse(&layout, "0", "0", "fill", "4"));
  widget_set_self_layout(g3, widget_layout_parse(&layout, "100", "0", "3", "4"));
  widget_layout(win);
  ASSERT_EQ(g2->x, 10);
  ASSERT_EQ(g2->w, 90);

  widget_set_self_layout(g1, widget_layout_parse(&layout, "0", "0", "10", "20"));
  widget_set_self_layout(g2, widget_layout_parse(&layout, "0", "0", "4", "fill"));
  widget_set_self_layout(g3, widget_layout_parse(&layout, "100", "160", "3", "4"));
  widget_layout(win);
  ASSERT_EQ(g2->y, 20);
  ASSERT_EQ(g2->h, 140);

  widget_destroy(win);
}

TEST(Layuout, layout_children_00) {
  widget_layout_t layout;
  widget_t* win = group_box_create(NULL, 0, 0, 200, 200);
  widget_t* g1 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g2 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g3 = group_box_create(win, 0, 0, 0, 0);

  widget_set_children_layout_params(win, "r0 c0 x10, y10, s10");
  widget_set_self_layout(g1, widget_layout_parse(&layout, "0", "0", "10", "4"));
  widget_set_self_layout(g2, widget_layout_parse(&layout, "0", "0", "fill", "4"));
  widget_set_self_layout(g3, widget_layout_parse(&layout, "100", "0", "3", "4"));
  widget_layout(win);
  ASSERT_EQ(g2->x, 20);
  ASSERT_EQ(g2->w, 70);

  widget_set_self_layout(g1, widget_layout_parse(&layout, "0", "0", "10", "20"));
  widget_set_self_layout(g2, widget_layout_parse(&layout, "0", "0", "4", "fill"));
  widget_set_self_layout(g3, widget_layout_parse(&layout, "100", "160", "3", "4"));
  widget_layout(win);
  ASSERT_EQ(g2->y, 30);
  ASSERT_EQ(g2->h, 120);

  widget_destroy(win);
}

TEST(Layuout, layout_children_10) {
  widget_layout_t layout;
  widget_t* win = group_box_create(NULL, 0, 0, 200, 200);
  widget_t* g1 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g2 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g3 = group_box_create(win, 0, 0, 0, 0);

  widget_set_children_layout_params(win, "r1 c0 x10 y10 s5");
  widget_set_self_layout(g1, widget_layout_parse(&layout, "0", "0", "20", "4"));
  widget_set_self_layout(g2, widget_layout_parse(&layout, "0", "0", "30", "4"));
  widget_set_self_layout(g3, widget_layout_parse(&layout, "100", "0", "20%", "4"));
  widget_layout(win);
  ASSERT_EQ(g1->x, 10);
  ASSERT_EQ(g1->y, 10);
  ASSERT_EQ(g1->w, 20);
  ASSERT_EQ(g1->h, 180);

  ASSERT_EQ(g2->x, 35);
  ASSERT_EQ(g2->y, 10);
  ASSERT_EQ(g2->w, 30);
  ASSERT_EQ(g2->h, 180);

  ASSERT_EQ(g3->x, 70);
  ASSERT_EQ(g3->y, 10);
  ASSERT_EQ(g3->w, 34);
  ASSERT_EQ(g3->h, 180);

  widget_destroy(win);
}

TEST(Layuout, layout_children_01) {
  widget_layout_t layout;
  widget_t* win = group_box_create(NULL, 0, 0, 200, 200);
  widget_t* g1 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g2 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g3 = group_box_create(win, 0, 0, 0, 0);

  widget_set_children_layout_params(win, "r0 c1 x10 y10 s10");
  widget_set_self_layout(g1, widget_layout_parse(&layout, "0", "0", "20", "20"));
  widget_set_self_layout(g2, widget_layout_parse(&layout, "0", "0", "30", "30"));
  widget_set_self_layout(g3, widget_layout_parse(&layout, "100", "100", "20%", "20%"));
  widget_layout(win);
  ASSERT_EQ(g1->x, 10);
  ASSERT_EQ(g1->y, 10);
  ASSERT_EQ(g1->w, 180);
  ASSERT_EQ(g1->h, 20);

  ASSERT_EQ(g2->x, 10);
  ASSERT_EQ(g2->y, 40);
  ASSERT_EQ(g2->w, 180);
  ASSERT_EQ(g2->h, 30);

  ASSERT_EQ(g3->x, 10);
  ASSERT_EQ(g3->y, 80);
  ASSERT_EQ(g3->w, 180);
  ASSERT_EQ(g3->h, 32);

  widget_destroy(win);
}

TEST(Layuout, layout_children_11) {
  widget_layout_t layout;
  widget_t* win = group_box_create(NULL, 0, 0, 200, 200);
  widget_t* g1 = group_box_create(win, 0, 0, 0, 0);

  widget_set_children_layout_params(win, "r1 c1 x10 y10 s5");
  widget_set_self_layout(g1, widget_layout_parse(&layout, "0", "0", "20%", "20%"));
  widget_layout(win);
  ASSERT_EQ(g1->x, 10);
  ASSERT_EQ(g1->y, 10);
  ASSERT_EQ(g1->w, 180);
  ASSERT_EQ(g1->h, 180);

  widget_destroy(win);
}

TEST(Layuout, layout_children_14) {
  widget_t* win = group_box_create(NULL, 0, 0, 200, 200);
  widget_t* g1 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g2 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g3 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g4 = group_box_create(win, 0, 0, 0, 0);

  widget_set_children_layout_params(win, "r1 c4 x5 y10 s10");
  widget_layout(win);
  ASSERT_EQ(g1->x, 5);
  ASSERT_EQ(g1->y, 10);
  ASSERT_EQ(g1->w, 40);
  ASSERT_EQ(g1->h, 180);

  ASSERT_EQ(g2->x, 55);
  ASSERT_EQ(g2->y, 10);
  ASSERT_EQ(g2->w, 40);
  ASSERT_EQ(g2->h, 180);

  ASSERT_EQ(g3->x, 105);
  ASSERT_EQ(g3->y, 10);
  ASSERT_EQ(g3->w, 40);
  ASSERT_EQ(g3->h, 180);

  ASSERT_EQ(g4->x, 155);
  ASSERT_EQ(g4->y, 10);
  ASSERT_EQ(g4->w, 40);
  ASSERT_EQ(g4->h, 180);

  widget_destroy(win);
}

TEST(Layuout, layout_children_41) {
  widget_t* win = group_box_create(NULL, 0, 0, 200, 200);
  widget_t* g1 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g2 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g3 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g4 = group_box_create(win, 0, 0, 0, 0);

  widget_set_children_layout_params(win, "r4 c1 x10 y5 s10");
  widget_layout(win);
  ASSERT_EQ(g1->x, 10);
  ASSERT_EQ(g1->y, 5);
  ASSERT_EQ(g1->h, 40);
  ASSERT_EQ(g1->w, 180);

  ASSERT_EQ(g2->y, 55);
  ASSERT_EQ(g2->x, 10);
  ASSERT_EQ(g2->h, 40);
  ASSERT_EQ(g2->w, 180);

  ASSERT_EQ(g3->y, 105);
  ASSERT_EQ(g3->x, 10);
  ASSERT_EQ(g3->h, 40);
  ASSERT_EQ(g3->w, 180);

  ASSERT_EQ(g4->y, 155);
  ASSERT_EQ(g4->x, 10);
  ASSERT_EQ(g4->h, 40);
  ASSERT_EQ(g4->w, 180);

  widget_destroy(win);
}

TEST(Layuout, layout_children_22) {
  widget_t* win = group_box_create(NULL, 0, 0, 200, 200);
  widget_t* g1 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g2 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g3 = group_box_create(win, 0, 0, 0, 0);
  widget_t* g4 = group_box_create(win, 0, 0, 0, 0);

  widget_set_children_layout_params(win, "r2 c2, x5 y5 s10");
  widget_layout(win);

  ASSERT_EQ(win->x, 0);
  ASSERT_EQ(win->y, 0);
  ASSERT_EQ(win->w, 200);
  ASSERT_EQ(win->h, 200);

  ASSERT_EQ(g1->x, 5);
  ASSERT_EQ(g1->y, 5);
  ASSERT_EQ(g1->h, 90);
  ASSERT_EQ(g1->w, 90);

  ASSERT_EQ(g2->x, 105);
  ASSERT_EQ(g2->y, 5);
  ASSERT_EQ(g2->h, 90);
  ASSERT_EQ(g2->w, 90);

  ASSERT_EQ(g3->x, 5);
  ASSERT_EQ(g3->y, 105);
  ASSERT_EQ(g3->h, 90);
  ASSERT_EQ(g3->w, 90);

  ASSERT_EQ(g4->y, 105);
  ASSERT_EQ(g4->x, 105);
  ASSERT_EQ(g4->h, 90);
  ASSERT_EQ(g4->w, 90);

  widget_destroy(win);
}

TEST(Layuout, layout_children_parse) {
  children_layout_t layout;
  children_layout_parser(&layout, "r:1");
  ASSERT_EQ(layout.rows, 1);
  ASSERT_EQ(layout.cols, 0);
  ASSERT_EQ(layout.x_margin, 0);
  ASSERT_EQ(layout.y_margin, 0);
  ASSERT_EQ(layout.spacing, 0);

  children_layout_parser(&layout, "r:1 c:2");
  ASSERT_EQ(layout.rows, 1);
  ASSERT_EQ(layout.cols, 2);
  ASSERT_EQ(layout.x_margin, 0);
  ASSERT_EQ(layout.y_margin, 0);
  ASSERT_EQ(layout.spacing, 0);

  children_layout_parser(&layout, "r:1 c:2 x:3");
  ASSERT_EQ(layout.rows, 1);
  ASSERT_EQ(layout.cols, 2);
  ASSERT_EQ(layout.x_margin, 3);
  ASSERT_EQ(layout.y_margin, 0);
  ASSERT_EQ(layout.spacing, 0);

  children_layout_parser(&layout, "r:1 c:2 x:3 s:4");
  ASSERT_EQ(layout.rows, 1);
  ASSERT_EQ(layout.cols, 2);
  ASSERT_EQ(layout.x_margin, 3);
  ASSERT_EQ(layout.spacing, 4);

  children_layout_parser(&layout, "r:1 c:2 x:3 y:10 spacing:4");
  ASSERT_EQ(layout.rows, 1);
  ASSERT_EQ(layout.cols, 2);
  ASSERT_EQ(layout.x_margin, 3);
  ASSERT_EQ(layout.y_margin, 10);
  ASSERT_EQ(layout.spacing, 4);
}
