# Saviour
A safety system with SOS signaling, morse code converter and GPS tracking for your next trip to a less visited location

## Inspiration
The countless stories and movies like the Lord of the Flies, Robinson Crusoe, Titanic, Cast Away, Six Days Seven Nights, etc. where the protagonist gets stuck on an island, even though it sounds very adventurous, but nonetheless the dangerous probability of it happening in real to people still remains. The idea behind Saviour was to create a hack that allows people to travel to remote locations without having to worry about getting lost or getting stuck there. 

## What it does
Saviour is an emergency tool that is very powerful, in times of real juncture. Saviour can do radio signalings like the popular SOS signal or any emergency signaling. If one gets stuck in a deserted area, say on an island or some mountain, where the Mobile gets useless, due to no network coverage, radios are still there, which can be a very effective way of communication in that scenario, and still, they are used all way. 
Saviour uses Morse Code signaling via a radio transmitter, also with a LED. It also has an OLED display, that can translate any sentence to its Morse Code, and display that code on the OLED simultaneously transmitting the code over the air, and also flashing it via a LED. It also has a buzzer to sound, how the Code will sound.
Now, it also contains a GPS that can get your direct coordinates. Since GPS satellites revolve all around the world, they can connect and get your current location. So with that not only Savior can send the SOS signal using radio, but Saviour sends the location details i.e. the latitude and longitude of the signal's origin location using the GPS. This will make it a lot easier for the search party to find the lost individual thus speeding up the process of the rescue operation.
This hack is not only a very important tool that will come in handy for people going on a vacation or traveling because of work purposes but it can also be used as an educational tool for learning Morse code since it has a Morse Code translator. 

## How we built it
Saviour has four main parts - one is the Morse Code translator, indicator, transmitter, and the GPS.
Firstly we created a menu-driven Graphics Interface for choosing the mode, whether the Morse Code or the GPS. This is done by a potentiometer to scroll, and a button to select.
The Morse code translator is built by parsing the String sentence character by character and creating its Morse equivalent. According to the supported Characters, the program translates it to a Morse String. To create a sentence, we reused the same button and the potentiometer. The potentiometer, scrolls through the characters, and the button increments the cursor.
Next, the Indicator was built using a small Buzzer and a LED which can also be used for signaling, and it is still considered to be an effective way. The buzzer plays the Morse Code with a Farnsworth speed of 10 in sync with the LED flashes. 
After that, a simple single transistor FM transmitter was built using a coil, capacitor, and transistor. Its job is to transmit the Morse code over open Air.
Last but not least, the life saviour, the GPS. As the name suggests, this part contains a GPS, through which the NMEA data is received as packets. Those get parsed and fetch the coordinates and finally get transmitted via the transmitter. 
Now all these interfaces are displayed over an OLED display, and all of them get controlled by the Arduino.

## Challenges we ran into
Making the interface was a bit tricky. Stopping abnormal flow or increment of button pushes using flags. Getting ready with the GPS. Since the GPS works best over open air. Printing the translated Morse Code on the OLED was a bit tricky too. 

## Accomplishments that we're proud of
We were in a bit of a time crunch since a lot had to be done, but we decided to work on one aspect at a time and finish that first. We are really proud to have overcome all the challenges like making the interface, making the FM transmitter. Displaying the morse code and listening to the buzzer to beep in accordance was a very proud moment. Thus bringing a mere project idea into life and that too in very little time is what we are very happy about. Saviour is a hack that we are very proud of building this tool because it can really help people in times of emergency.

## What we learned
We learned with help of simple components, such as the potentiometer and button we can create such a good graphical interface. We learned how to drive OLED displays. Learned about Morse Codes, speed. Learned a bit about GPS and the NMEA protocol. 

## What's next for Saviour
We are thinking of adding a digital compass, and an altimeter by which it can be used as a very powerful and absolute emergency item, and a normal human must-have.
