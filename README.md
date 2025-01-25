# Info

As we all know, Unity has removed the old launcher in the latest version, replacing it with a [C++ project](https://github.com/Unity-Technologies/DesktopSamples/tree/master/ScreenSelectorExample). However, this project is designed for Mono and does not support IL2CPP. To address this, I have reworked the exported VS project. 

And more examples will be added to the project

# How to use

Build your unity project with `Create Visual Studio Solution` options.

![image](https://github.com/user-attachments/assets/257439e1-a16b-476e-8e86-0757bb56ecc7)

Replace files in folder , then recompile .

# Delay Example

![delay example](https://github.com/user-attachments/assets/f5807e71-2cef-4fb2-8a8c-55f264b80426)

This [basic script](DelayExample/Main.cpp) will pop up a 5-second countdown window before the game starts, which will automatically close after 5 seconds and then launch the game. Additional features like buttons can be added based on this foundation.

# Image Example

![image example](https://github.com/user-attachments/assets/359a8d36-e88b-4c5f-82e8-0171bc1399b4)

In this example, it will pop up a 5-second countdown window with image before the game starts, which will automatically close after 5 seconds and then launch the game.
