# Atmospheric Indicator using Neopixel Jewels

This is a fairly simple project, but, in my opinion, really cool. In general, I enjoy projects that produce somewhat abstract, artistic pieces that use data from the world around us. Temperature, Humidity, and Barometric Pressure are low-hanging fruit for such a project. 

I also wanted to make the form factor as small as possible and use the smallest components I could.

The end goal is to place the device in a small 3D printed box with the three neopixels facing outward for easy reference if you're in the same room. One Jewel would show the temperature based on a certain color, the middle would show the same with humidity, and the last would show the same based on barometric pressure with the rainbow() or theaterChase() as a "storm warning" (i.e. when the pressure falls very quickly over a certain amount of time).

To do:
* Order a couple more Jewels. Right now I am using two different ones
* Code the storm warning for the last jewel
* Design 3D printed container
* Figure out battery options so it can be mobile. LiPo > USB-C?

Parts used:

* [Seeeduino Xiao](https://www.seeedstudio.com/Seeeduino-XIAO-Arduino-Microcontroller-SAMD21-Cortex-M0+-p-4426.html)
* [BME280 Sensor](https://www.amazon.com/gp/product/B01N47LZ4P/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1f)
* [Adafruit Jewel 7 RGB](https://www.adafruit.com/product/2226nnMaterial?hidden=yes&main_page=product_info&products_id=2226&gclid=Cj0KCQjwi7yCBhDJARIsAMWFScPwNtT3JpWPzmPmBQJgau7jMIXhg61gpJ46Kh5Rj5B9ODmnZWLjUb0aAtI8EALw_wcB)
* [Adafruit Jewel 7 RGBW](https://www.adafruit.com/product/2859)
* [22 AWG Wire - I have been using this, but any will do](https://www.amazon.com/gp/product/B07TX6BX47/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)

## Breadboard Image
Second image ~ March 21st
![Picture of updated layout, added a Barometric Pressure Neopixel](https://i.imgur.com/8aFFsvk.jpg = 250x)

First image ~ March 15th
![Picture of two Neopixels, Sensor, and Xiao](https://i.imgur.com/HFIlbCU.jpg = 250x)
