# rotating_cube_opengl
<img src="res/result.gif" height="180" width="320"/>
Refs:
<ul>
<li>https://thecherno.com/opengl</li>
<li>https://www.youtube.com/playlist?list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY</li>
</ul>
P.S

I wrote this on windows, vs17, visual c++

Tried to adjust cmake and dependencies for mac,</br>
but finally xcode debugger spits out this:

```
Debugging starts

(
	0   AppKit                              0x00007fff44c3a862 -[NSWindow _validateFirstResponder:] + 578
	1   AppKit                              0x00007fff443815f0 -[NSWindow _setFirstResponder:] + 31
	2   AppKit                              0x00007fff4441fd5d -[NSWindow _realMakeFirstResponder:] + 448
	3   libglfw.3.dylib                     0x0000000100226975 _glfwPlatformCreateWindow + 657
	4   libglfw.3.dylib                     0x0000000100222592 glfwCreateWindow + 443
	5   hello_opengl                        0x0000000100018635 main + 149
	6   libdyld.dylib                       0x00007fff6f0ee015 start + 1
)
```
If you'll tell where am I wrong, that would be great.
