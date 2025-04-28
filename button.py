from gpiozero import LED, Button
from signal import pause

button = Button(2)
led = LED(17)

while 1:
    if button.is_active():
        led.on()
    else:
        led.off()