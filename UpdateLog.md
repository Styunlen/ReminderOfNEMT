> 版本的标记格式为v(Num),例如1.0版本就标记为v1.0
> 而版本号的格式定义则采用了GNU 风格的版本号管理策略
> 	“
> 	GNU 风格版本号
> 	主版本号 . 子版本号 [. 修正版本号[ build- 编译版本号 ]]
> 	英文对照 : Major_Version_Number.Minor_Version_Number[.Revision_Number[.Build_Number]]
> 	示例1：1.2
> 	示例2：1.2.0
> 	示例3：1.2.0 build-1234
> 	1．项目初版本时，版本号可以为 0.1 或 0.1.0，也可以为 1.0 或 1.0.0，如果你为人很低调，我想你会选择那个主版本号为 0 的方式 ;
> 	2．当项目在进行了局部修改或 bug 修正时，主版本号和子版本号都不变，修正版本号加 1;
> 	3．当项目在原有的基础上增加了部分功能时，主版本号不变，子版本号加 1，修正版本号复位为 0，因而可以被忽略掉 ;
> 	4．当项目在进行了重大修改或局部修正累积较多，而导致项目整体发生全局变化时，主版本号加 1;
> 	5．另外，编译版本号一般是编译器在编译过程中自动生成的，我们只定义其格式，并不进行人为控制
> 	”
> 版本以下的更新格式如下
> --[添加]……
> --[更改]……
> --[删除]……
> --[优化]……
> --[修复]……(可以是修复问题，也可以是修复Bug,若修复的是Bug，则添加Bug序号前缀)
> 顺序可变换
> Bug的序号是依次递增的，1号Bug则被标记为“#1 Bug描述”

<div style="margin-bottom:20px;">
    <p style="border:1px solid #aad9ff;padding:10px;background:#ddf5ff;margin:0;border-top-right-radius:5px;border-top-left-radius:5px;">
        [<strong>置顶</strong>] 公告功能上线啦！<span style="padding-left:20px;color:#57606a;">• 2021/10/6</span>
    </p>
    <p style="border:1px solid #aad9ff;border-top:0px;padding:10px;margin:0;border-bottom-right-radius:5px;border-bottom-left-radius:5px;">
一直心心念念要添加的功能，终于实现啦！23333
    </p>
</div>
<div style="margin-bottom:20px;">
    <p style="border:1px solid #aad9ff;padding:10px;background:#ddf5ff;margin:0;border-top-right-radius:5px;border-top-left-radius:5px;">
        下一个正式版本正在做和已经完成的内容<span style="padding-left:20px;color:#57606a;">• 2021/10/6</span>
    </p>
    <p style="border:1px solid #aad9ff;border-top:0px;padding:10px;margin:0;border-bottom-right-radius:5px;border-bottom-left-radius:5px;">
        <input type="checkbox" disabled="disabled"/>[添加]自动更新<br/>
        <input type="checkbox" disabled="disabled"/>[添加]设置页中可以更改主题自定义选项<br/>
        <input type="checkbox" disabled="disabled"/>[添加]设置页中可以选择要获取的一言类型<br/>
        <input type="checkbox" disabled="disabled"/>[添加]有新公告时，弹窗提醒<br/>
        <input type="checkbox" disabled="disabled"/>[优化]修改时间机制，在设置页中添加自动获取时间选项<br/>
        <input type="checkbox" checked="checked" disabled="disabled"/>[添加]主题API，方便自定义或自己制作主题，同时方便模块化设计主题<br/>
        <input type="checkbox" checked="checked" disabled="disabled"/>[添加]设置页面自动加载已安装的主题<br/>
        <input type="checkbox" checked="checked" disabled="disabled"/>[优化]设置页面UI重构<br/>
        <input type="checkbox" checked="checked" disabled="disabled"/>[添加]设置页面启动动画<br/>
        <input type="checkbox" checked="checked" disabled="disabled"/>[添加]联网公告，方便获取软件更新动态<br/>
        <input type="checkbox" checked="checked" disabled="disabled"/>[添加]一言<br/>
        <input type="checkbox" checked="checked" disabled="disabled"/>[修复]修复倒计时在0秒时卡住，然后直接跳到58秒的BUG<br/>
        <input type="checkbox" checked="checked" disabled="disabled"/>[修复]修复设置界面中时间选项内的日历在切换动画中不居中BUG<br/>
        <input type="checkbox" checked="checked" disabled="disabled"/>[修复]修复设置界面选项切换动画的闪烁问题<br/>
    </p>
</div>


v1.2.2 build-95
[修复]修复了设置页链接单击后无反应的问题

v1.2.1 build-94
[修复]修复了目标时间到时，祝福语显示为乱码的问题

v1.1.0 build-74:
[添加]启动时自动移动至上次关闭的位置
[更改]更改了设置图标
[修复]#1 若打开设置窗口后没有使用日历表更改时间，则关闭窗口保存设置时目标日期永远是1月6号的Bug