# AWTK 中的一些惯例

#### 1.pixel 格式：以各个通道在内存中存放的顺序，从低地址到高地址递增的方式命名。

>如：
>
>RGBA8888：表示内存地址从低到高依次为 RGBA，每个通道各占一字节 (8 位）。
>
>BGR565：表示内存地址从低到高依次为 BGR，BGR 三个通道分别占 5 位，6 位和 5 位。

---

#### 2. 所有类的公开属性都是只读的，不要直接去修改它们。

---

#### 3. 所有类的公开属性都可以直接读取，不提供 get 函数。

---

#### 4.widget 及其子类的公开属性，如果在 annotation 中标明支持 set\_prop，那么可以在界面描述文件中，用同名属性为其指定的初始值。

---

#### 5. 除非特别说明，时间单位为毫秒。

---

#### 6. 除非特别说明，控件都是容器。你可以在按钮中放图片，也可以在图片中放按钮，通过组合形成更强大控件。
