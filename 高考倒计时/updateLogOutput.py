from ast import Str
import sys,os
def getTags(tagOri:Str)->str:
    ret = 'new'
    if tagOri == '添加':
        ret = 'new'
    elif tagOri == '更改':
        ret = 'edit'
    elif tagOri == '删除':
        ret = 'del'
    elif tagOri == '优化':
        ret = 'imp'
    elif tagOri == '修复':
        ret = 'fix'
    return ret
ret = []
with open("updateLogs.txt","r",encoding="utf8") as f:
    lineTxts = f.readlines()
    for i in lineTxts:
        if i[0] == 'v':
            ret.append('<br/>%s<br/>'%i)
        elif len(i) > 1:
            updateTag = i.split("]")[0][1:]
            updateContent = i.split("]")[1]
            ret.append('<span class="updateTag %s"></span>%s<br/>'%(getTags(updateTag), updateContent) )


with open("updateLogsFormatted.txt","w") as f:
    f.writelines(ret)
os.system("updateLogsFormatted.txt")