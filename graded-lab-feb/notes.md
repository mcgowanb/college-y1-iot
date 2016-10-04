#iot assessment feb 2016

For this assessment, I've combined two other sketches. The first one is using the potentiometer to control the brightness of an LED. The Analogue input 0 was used for the pot, and the digital pin 5 used for the output. I've also implemented the Bridge to run the console output for debugging. Using the bridge as its running over a wifi connection

The second sketch is using a push button to engage a relay / buzzer. when the button is pushed it engages the buzzer. Digital in 2 is uses for the button and digital out 3 is used for the relay / buzzer

#Issues
There were some initial connectivity issues with the board via wifi. The board is configured and connected to the wifi network and is reachable via ping however it was not showing up as an available port on the IDE. I'm not sure if this is because the board would have been in configuration mode on its web page or if it was a result of a short from the two boards sitting too closely on top of each other.