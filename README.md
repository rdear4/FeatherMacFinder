##Feather MAC Finder

This device was designed to help find MAC addresses on devices that can't display MACs, or where the option to display it is hidden somewhere deep in the settings.

It uses an Adafruit Feather Huzzah, which has an ESP8266 wifi microncontroller built into it. To display the name of the network it broadcasts and the MAC address of a connected device it has a FeatherWing with an small OLED display. It also has micro USB for programming and recharging a lipo battery that can be connected using the on board 2 pin JST connector.

<h2>How It Works</h2>

When switched on the deived bradcasts and WiFi access point, the SSID of which can be set in the code. All that is needed is for the device with an unknown MAC to connect to the AP and it's MAC will be shown on the built in OLED display.

Messages indicating a device has connected and disconnected are also displayed when appropriate.

###List of parts:

Micrcontroller: [Feather Huzzah](https://www.adafruit.com/product/2821)
<br>Display: [FeatherWing OLED](https://www.adafruit.com/product/3045)
<br>Battery: [500 mAh](https://www.adafruit.com/product/1578)
<br>Some kind of on-off switch [Switch](https://www.adafruit.com/product/805)
