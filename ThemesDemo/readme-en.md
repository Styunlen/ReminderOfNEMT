# For Theme's Developer

## Brief introduction

> This is a document about how to create and design a theme for this application.
>
> Under this folder,you can see some themes called like ```demo-xxx```.You are free to design a theme based on it.

## Theme's content

### file structure

A full theme might contains following files.

Subfolders are supported.

> tips: All the files are suggested to be encoded with utf-8(with bom),in case of exception of decoding.

|Theme Name|

​	├─  main.html

​	├─ options.html

​	├─ scripts.tis

​	├─ (screenshot|preview).(jpg|png|gif|bmp) #preview image，two file names and four filetype are supported

​	└─ style.css

Of course,if you just want to change the apperance of countdown window,theme only needs to contain one file named ```main.html```.

A full theme contains two main file.The one for countdown window, and the other one for setting window.Additional,theme also contains stylesheet and script files.

The file for the countdown window needs to be named ```main.html``` because the application will load themes from this file,

and the file for the setting window needs to be named ```options.html``` if existed.

### main.html

To show the countdown date,you can add elements with id called "day,hour,min,sec".

And after adding them to ```main.html```,you should add this script to html code as well.

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

To view full file,please open the demos.

## API

* ```updateTime()```

  > This function was defined for updating elements related to countdown time
  >
  > After calling this function，elements whose id is day,hour,min,sec will be automatically updated per second.

* ```  NA_getThemeOption(themeName, optionName) ```

  > This function was defined for getting option of theme
  >
  > paras:
  >
  > * ```themeName```: the name of theme
  > * ```optionName```: the name of option
  >
  > e.g. 
  >
  > ```tiscript
  > NA_getThemeOption("Circle","background-image")
  > ```

* ```NA_saveThemeOption(themeName, optionName, optionValue)```

  > This function was defined for saving option of theme
  >
  > paras:
  >
  > * ```themeName```: the name of theme
  > * ```optionName```: the name of option
  > * ```optionValue```: the value of option
  >
  > e.g. 
  >
  > ```
  > NA_getThemeOption("Circle","background-image","default.jpg")
  > ```

