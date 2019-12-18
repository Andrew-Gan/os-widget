# OS-widget

Software tools:  
Visual Studio Code  
G++ 7.4 Compiler  
gtkmm (C++ wrapper for gtk)  
  
Compile Instruction:  
g++ -g main.cpp panel.cpp os_info.cpp -o main `pkg-config gtkmm-3.0 --cflags --libs`  
  
Displays a simple GUI that shows disk space remaining for a dual-booted computer  
  
<img src="https://github.com/Andrew-Gan/os-widget/img/widget.png">