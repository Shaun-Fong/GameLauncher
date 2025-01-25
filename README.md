# Info

As we all know, Unity has removed the old launcher in the latest version, replacing it with a [C++ project](https://github.com/Unity-Technologies/DesktopSamples/tree/master/ScreenSelectorExample). However, this project is designed for Mono and does not support IL2CPP. To address this, I have reworked the exported VS project. 

And more examples will be added to the project

# How to use

Just replace `Main.cpp` and recompile .


# Delay Example

This [basic script](DelayExample/Main.cpp) will pop up a 5-second countdown window before the game starts, which will automatically close after 5 seconds and then launch the game. Additional features like buttons can be added based on this foundation.