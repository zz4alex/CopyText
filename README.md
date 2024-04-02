# CopyText 程序说明

有时其他Windows程序中的文字可能被设置为不可编辑，或者被禁用复制，为了拷贝这些文字信息，一般我们会先截图，然后使用具有OCR功能的程序来识别出文字，但是OCR识别毕竟会有识别错误在其中，没有直接拷贝来的方便。

这里碰到的典型情景就是想把某考试软件中的题目操作指令文字以及正确作答的说明文字给拷贝下来方便上课使用，但是该软件设置了不可拷贝的限制，明明看到屏幕上的文字，感觉唾手可得，却不得不使用截图，再求助其他OCR软件识别，还需要反复核对，十分费时费力。试了其他类似的软件如Textify、AquaDesktop，都没有成功，因此着手自己写个程序来解决这个问题。希望对有这类需求的人有所帮助。

## 使用说明：
1. 点击打开程序，显示为命令行窗口。(以管理员身份运行)

2. 使用鼠标，在其他桌面程序中点击需要拷贝的文字部分，该程序会在操作系统中尝试查找点中的文字组件的句柄，并将其中的文字拷贝出来放入剪贴板，同时在命令行窗口显示具体的文字内容。

3. 使用程序的过程中，通过反复按Esc键可以来回切换鼠标点击是否提取文字功能，方便粘贴动作。

4. 直接关闭命令行窗口 或 按F9键 可以退出程序。

5. 所有操作过程中，无需使命令行窗口处于焦点状态。



# CopyText Program Description

Sometimes, text in other Windows programs may be set as non editable or copy disabled. In order to copy this text information, we usually take screenshots first and then use programs with OCR function to recognize the text. However, OCR recognition may have recognition errors in it, so it is less convenient than direct copy.

The typical scenario encountered here is to copy the operation instructions and correct answer explainations from a certain exam software for using in class leturing. However, the software has set a non copying limit, which means that when you see the text on the screen and feel at your fingertips, you have to use screenshots and OCR software. It also requires repeated verification, which is very time-consuming and laborious. Tried other similar software such as Textify and AquaDesktop, but none of them were successful, so I started writing my own program to solve this problem. I hope it can be helpful to people with same needs.


## Instructions for use:
1. Click to open the program, which will display as a command line window. (Run as Administrator)

2. Using the mouse, click on the part of text that needs to be copied in other desktop programs. The program will try to find the handle of the pointed text component in the operating system, copy the text from it, and put it on the clipboard. The text content will also be displayed in the command line window for check.

3. During the use of the program, repeatedly pressing the **Esc** key can switch on or off state of mouse clicks to extract text, that makes it convenient to paste actions. 

4. Simply close the command line window or press **F9** to exit the program.

5. There's no need to keep the command line window in focus during operation.

