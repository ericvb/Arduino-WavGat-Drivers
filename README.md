# Arduino-WavGat-Drivers for IDE 1.8.1x

I started from the given drivers from WavGat via the AliExpress website: https://drive.google.com/open?id=10gwrG9uTDwaEO-7EudsmBkfgdcyrcABI

I installed the drivers in the Arduino IDE project (1.8.1+)
You can do that by copying them into the created user extension folder from the Arduino IDE.
On windows, normally in Documents\Arduino

When trying to compile the basic sketch about the blinking led, the compiler did give me a warning:

> 'Arduino AVR Boards' contains deprecated recipe.ar.pattern="{compiler.path}{compiler.ar.cmd}" {compiler.ar.flags} {compiler.ar.extra_flags} "{build.path}/{archive_file}" "{object_file}", automatically converted to recipe.ar.pattern="{compiler.path}{compiler.ar.cmd}" {compiler.ar.flags} {compiler.ar.extra_flags} "{archive_file_path}" "{object_file}". 

This is caused because these given drivers are not updated regurarly to follow new developments in the Arduino IDE source code.

Second, when trying to compile the latest MySensors library (v2.3.1), I got a whole bunch of strange compile errors.

So I adapted the platform.txt to follow the normal Arduino IDE platform.txt source code.
At the same time I adapted the name from 'Arduino AVR Boards' to 'WavGat AVR Boards' to distinguish them more clearly.

I added also a missing new define 'void yield(void)' in the core Arduino.h file and the missing hook.c file.
(All credits and thanks to: https://github.com/digistump/DigistumpArduino/issues/45)

After these changes my sketches for MySensors did compile without any errors.

In this distribution the hardware folder WAV8F is not included, it is for the Arduino IDE 1.x version!

As the Arduino IDE will evolve in the future, other needs to change these WavGat drivers will appear.
It's a bit sad that WavGat doesn't keep its software up to date!
