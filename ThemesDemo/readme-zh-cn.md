# 写给开发者

## 简介

> 这个文档介绍了如何为这个程序编写一个自定义的主题。
>
> 在该目录下，包含了几个名为```demo-xxx```的主题，可以在此主题的基础上进行开发。

## 主题内容

### 文件结构

一个完整的主题可能包含以下文件

可包含子文件夹

> 推荐使用utf-8(with bom)编码保存所有文件，以防出现乱码

|Theme Name|

​	├─  main.html

​	├─ options.html

​	├─ scripts.tis

​	├─ (screenshot|preview).(jpg|png|gif|bmp) #预览图，支持两种文件名和四种文件格式

​	└─ style.css

当然，如果你只是想要更改倒计时窗口的外观，主题只需要包含一个名为```main.html```的文件就够了。

一个完整的主题包含两个主文件。一个用于倒计时窗口，另一个用于设置窗口。另外，主题还包含样式表和脚本文件。

倒计时窗口的文件需要命名为```main.html```，因为应用程序将从此文件中加载主题，
设置窗口的文件需要命名为``options.html``（如果存在）。

### main.html

为了显示倒计时，你可以向```main.html```文件中添加id为"day,hour,min,sec"的元素。

在添加他们到 ```main.html```之后,你还需要添加以下代码，才能实现时间的显示。

```
<script type="text/tiscript">          
    //Essential function for initialization of theme
    function theme_inited()
    {
        //Function from ReminderAPI for time display
        updateTime();
    }
</script>
```

完整代码，请看demos主题

## API

* ```updateTime()```

  > 该函数用于持续更新指定标签内的时间
  >
  > 在使用了此函数后，id为day，hour，min，sec的元素每秒会自动更新一次

* ```  NA_getThemeOption(themeName, optionName) ```

  > 该函数用于读取主题的相关配置(主题配色等等)
  >
  > 主要有以下参数
  >
  > * ```themeName```: 主题的名字
  > * ```optionName```: 选项的名字
  >
  > e.g. 
  >
  > ```tiscript
  > NA_getThemeOption("Circle","background-image")
  > ```

* ```NA_saveThemeOption(themeName, optionName, optionValue)```

  > 该函数用于保存主题的相关配置(主题配色等等)
  >
  > 主要有以下参数
  >
  > * ```themeName```: 主题的名字
  > * ```optionName```: 选项的名字
  > * ```optionValue```: 选项的值
  >
  > e.g. 
  >
  > ```
  > NA_getThemeOption("Circle","background-image","default.jpg")
  > ```

