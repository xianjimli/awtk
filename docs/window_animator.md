# AWTK中的窗口动画

窗口动画是现代GUI最基本的功能之一，在窗口打开或关闭时，引入一个过渡动画，让用户感觉这个过程是流畅的。窗口动画的基本原理很简单：在打开或关闭窗口时，把前后两个窗口预先绘制到两张内存图片上，按照指定规则显示两张图片，形成动画效果。


## 基本架构

窗口本身只需指定期望的动画类型，由窗口管理器负责在适当的时候(如打开和关闭窗口时)，创建窗口动画并让窗口动画绘制到屏幕上。在窗口动画期间，窗口管理器会禁止窗口本身的绘制，并忽略所有输入事件。目前支持的动画有：

* htranslate: 左右平移动画(适合窗口)。
* vtranslate: 上下平移动画(适合窗口)。
* center\_scale: 缩放动画(适合对话框，没有硬件时加速慎用)。
* top\_to\_bottom: 顶部向下弹出动画(适合对话框)。
* bottom\_to\_top: 底部向上弹出动画(适合对话框)。
* fade: 淡入淡出动画(适合提示信息)。

![](images/window_animator.png)

窗口动画有三种实现方式：

* 在系统支持OpenGL时，使用vgcanvas进行绘制，因为使用了浮点数，整个动画最为平滑。
* 在系统支持FrameBuffer，使用lcd绘图函数实现动画。
* 在低端系统上，不启用动画。

## 使用方法

给窗口或对话框指定动画效果，只需设置窗口或对话框的anim\_hint属性即可：

```
  1 <window name="main" anim_hint="vtranslate" x="0" y="0" w="320" h="480">
  2   <button name="fade" x="10" y="middle" w="25%" h="30" text="Fade"/>
  3   <button name="top" x="center" y="middle" w="25%" h="30" text="Top"/>
  4   <button name="close" x="right:10" y="middle" w="25%" h="30" text="Close"/>
  5 </window>
```
> anim\_hint的可选值，请参考src/base/window\_animator.h中的定义。

可以指定动画时长(duration)，格式类似与函数调用，不过参数用name=value的形式，如：

```
anim_hint="center_scale(duration=300)"
```

* duration的单位为毫秒。

## 示例

demoui演示了各种窗口动画：

```
./bin/demoui
```

## 限制

* 目前窗口的动画效果适合类似智能手机的应用，其它行业应用可以根据需要进行调整。
* 目前主要实现窗口动画的机制，具体的参数还需要细调整。

