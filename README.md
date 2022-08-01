# ScreenCapture 
轻量级截屏工具
## 默认功能
1. 快捷键截屏
```
Ctrl+U 截屏
Ctrl+I 退出程序
``` 
2. 点击按钮截屏

## 首次运行
第一次运行时会被系统阻止。  
![image](https://user-images.githubusercontent.com/78804251/182111661-ce899d0c-3912-4e62-ab83-81dfa4bbbbb3.png)  
由于本款程序是安全的，所以点击“更多信息”，再点击“仍要运行”即可运行截屏程序。  
![image](https://user-images.githubusercontent.com/78804251/182111963-d6ac3098-4a57-41b0-8e77-e829d2bb3a1b.png)  

## 若下述问题
### 问题1： 
![image](https://user-images.githubusercontent.com/78804251/182112292-3178403d-bd13-4eab-b4d1-f98217051cf2.png)  
表明计算机缺失了“mfc120ud.dll”  
解决方法1：  
1. 下载“mfc120ud.dll”  
2. 根据系统位数将“mfc120ud.dll”放入对应目录下  
Win10 32位：C:\Windows\System32  
Win10 64位：C:\Windows\SysWOW64  
3. 快捷键win+R,输入
``` 
regsvr32 mfc120u.dll 
```
再点击回车  
4. 重新运行截屏程序即可

解决方法2：  
下载“DirectX修复工具”进行修复，再运行截屏程序即可

### 问题2： 
![image](https://user-images.githubusercontent.com/78804251/182113817-6318d18c-81f5-48de-a4c4-84939e9ec632.png)  
同问题1的解决方法





