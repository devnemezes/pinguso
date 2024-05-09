# ping(uso) 1.4
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
A table clock and Small connectivity monitor that you can have on your desk.

![image](https://i.ibb.co/TqCVJWx/IMG-4910.jpg)


------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Disclaimer:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
I made this "Connected Thing" for three very simple reasons:

1 - Why not?

2 - I needed to monitor my office connectivity and needed a desk clock.

3 - I couldn't find it to buy. I'm lazy, but when there isn't one, I do it.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Feel free to download and change whatever you want, just don't ask to generate new versions or fix bugs. I don't have time and I did this out of curiosity and fun. Use at your own risk.

Remember: If you used the code, give credit to the author. Whenever possible, buy him a coffee.

Again: Don't insist, I don't have time bro!

Note: 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
The word "Pingusso" in Brazilian Portuguese means: "It is said of the eyes of someone who has drunk too much alcohol or is very sleepy."

Why and how this thing works:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
The code is a simple monitoring tool designed to check internet connectivity using a home WiFi connection. It targets an ESP32 microcontroller board (ESP32-2432s028) and uses a display library, LovyanGFX, to output results on a graphical display.

**Key Features:**

1. **Network Setup and Display:**
   - It connects to a specified WiFi network (SSID `your_wifi` with password `<your_pass`).
   - NTP (Network Time Protocol) is used for synchronizing the local time with an NTP server.
   - Display components include textual and graphical output using LovyanGFX to show network status, internet reachability, and local time.

2. **Ping Checks:**
   - It targets various hosts to verify internet connectivity and DNS resolution.
   - `Ping.ping()` functions are used to check connections to various remote hosts like `www.google.com.br`, and other DNS resolvers (`8.8.8.8` and `208.67.222.222`).
   - Checks are also done for specific servers like `twitter.com` and `whatsapp.com`.

3. **Indicators:**
   - LEDs and graphical elements are used to indicate different statuses, like successful connectivity or failures.
   - The graphical display shows real-time status using colors (green for connected and red for errors).

4. **Light Detection (LDR):**
   - An LDR (Light Dependent Resistor) is connected to an analog input pin to measure light levels and control the screen brightness accordingly.

5. **LED Control:**
   - The code manages green and red LEDs to visually indicate connectivity statuses.

**Flow of Execution:**
- **Setup:**
  - Initializes serial communication, graphical display, and WiFi connection.
  - Outputs network information once connected.

- **Loop:**
  - Continuously retrieves the local time and displays it.
  - Executes ping checks on the predefined hosts.
  - Controls LEDs based on connectivity status.
  - Uses the LDR sensor to adjust screen brightness.

**Libraries Used:**
- `LovyanGFX` for graphical display.
- `WiFi` and `ESP32Ping` for network connectivity and ping functionality.

For the love of GOD (whether you believe it or not): 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Don't forget to insert the drive for the display in your project:
lgfx_ESP32_2432S028.h

https://github.com/lovyan03/LovyanGFX/blob/master/examples/HowToUse/2_user_setting/2_user_setting.ino

This article is fantastic, well, if you don't know Japanese, use Google translator and stop being lazy. You have to want it! 

https://macsbug.wordpress.com/2022/08/17/esp32-2432s028/
- Standard Arduino functions for board and I/O control.


ESP32 microcontroller board (ESP32-2432s028)
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

![image](https://github.com/devnemezes/pinguso/assets/169056722/80c9b3f9-97e1-429d-9f18-32ebfd01fe85)
![image](https://github.com/devnemezes/pinguso/assets/169056722/b95bfe82-db33-4162-ba9e-1ca4aaf9d6c9)


