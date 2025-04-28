from gpiozero import LED, Button
from signal import pause

button = Button(2)
led = LED(17)

button.when_activated = led.on
button.when_deactivated = led.off

pause()