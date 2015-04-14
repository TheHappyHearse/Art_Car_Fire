The flame effect will be two propane fluffers mounted on the back of the car. An arduino will control the effect. See the file Control_Diagram.png for a diagram showing the control panel. It will help make sense of the code here.

While the arduino is idle, the control panel will sit there with the three pushbuttons lit up by LEDs.

From idle, you can press either of the green buttons in the lower left and that will fire the corresponding fire. Think of it as "manual mode." As long as the button is held down, the valve will stay open. When you release the button, the valve will close. You can also press both green buttons at once to get both valves to open as long as you hold it.

Additionally, there will be 27 different sequences (numbered 0-26) programmed into the arduino and available to use. The sequences will be selected using the 3 three-position switches at the top of the panel. The red "activate" button (bottom right of control panel) will start the sequence. Sequences will last anywhere from a few seconds to several minutes in duration.

If, during a sequence, the operator wants to interrupt it and stop firing, he can hit any of the three buttons. This will send the program into "dumbass mode" ("dumbass" because you shouldn't call up fire if you can't deal with it), which will idle the program for a set period (5 minutes?).

Additionally, if the operator wishes to force the program to go dormant, he can hold down either of the green buttons + the red button and this will send it into dumbass mode. This feature may come in handy if the operator sees a potentially dangerous situation developing -- e.g. driving through trees, or the appearance of a drunken idiot who looks like he wants to press glowing buttons.

When the program is ready for input, all the LEDs will be lit. If it's not ready, then they will all be dark.

That's the idea, anyways.

