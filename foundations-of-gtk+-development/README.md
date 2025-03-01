# Foundations of GTK+ Development

**书中例子都是 GTK2 的，由于太旧，这里统一改成 GTK3**

## ch02

可以通过 `g_object_set()` 设置属性的值。
比如如下代码将 button 的 `relief` 属性设置为 GTK\_RELIEF\_NORMAL

```c
g_object_set (button, "relief", GTK_RELIEF_NORMAL, NULL);
```

可以通过 `notify::property-name` 监听属性的变化，如下

```c
g_signal_connect (G_OBJECT (button), "notify::relief",
                  G_CALLBACK (property_changed), NULL);

...

static void
property_changed (GObject *button,
                  GParamSpec *property,
                  gpointer data)
{
    /* Handle the property change ... */
}
```

## ch03

```c
void
gtk_paned_pack1 (
  GtkPaned* paned,
  GtkWidget* child,
  gboolean resize,
  gboolean shrink
)

void
gtk_paned_pack2 (
  GtkPaned* paned,
  GtkWidget* child,
  gboolean resize,
  gboolean shrink
)
```

参数：

* child
    * Type: GtkWidget
    * 要添加的子控件
    * 数据由调用该方法的调用方拥有
* resize
    * Type: gboolean
    * 当 paned 控件改变大小时这个控件是否改变大小
* shrink
    * Type: gboolean
    * 这个子控件是否可以被缩小到小于其需求尺寸
