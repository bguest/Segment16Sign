## WTF? How does this thing work?

Its a work in progress. But in general the keyboard controls the 16 Segment Displays.

## TL;DR: Cheat Sheet

+ `space`: Insert text
+ `<esc>`: Edit colors
+ `1`/`2`: Edit Background / Foreground Color
+ `j`/`k`: Tempo

+ `.`/`,`: Text Effect
+ `h`/`l`: Color effect

+ `]`/`[`: Increase / Decrease things, sometimes.
+ `f`/`s`: Faster / Slower, sometimes.
+ `F`/`S`: Bigger / Smaller, less often

+ `X`: Randomize
+ `I`: Invert
+ `R`: Reset
+ `r`: Reset color only, sometimes
+ `u`: Reset text only, sometimes
+ `/`: Randomize current text settings
+ `x`: Randomize current color settings

+ `b`/`B`: (Brightness) Decrease / Increase color Value.
+ `c`/`C`: (Color) Decrease / Increase color Hue.
+ `v`/`V`: (Vibrancy) Decrease / Increase color Saturation.

+ `0`: Sets brightness to 0
+ `9`: Sets brightness to full

## Components

+ **Sign**: The Big 16 Segment Displays
+ **Keyboard**: Used for changing the sign, loosely based on VIM.
+ **Display**: 4 x 40 LCD Display attached to keyboard, it try's to be helpful.

## VIM

The way the sign is manipulated is loosely related to the VIM Text Editor. With VIM there are two
modes, **Insert Mode** and **Normal Mode**. **In thses instructions, unless otherwise stated, assume I'm
talking about pressing keys in normal mode**.

### Insert Mode (space bar)

Insert mode is used to enter text into the sign. If you are in normal mode you can get to insert
mode by typing `i` or pressing the space bar.

**Example**: If you wanted to the sign to say `HI`, you would press `<esc>` then `.` until the
display says `Basic Typing` then press `i` followed by `H` and `I`.

### Normal Mode (esc key)

In normal mode the keys are setup to edit the effects of the sign, color, tempo, different text
effects. To get to normal mode from Insert mode either press `<esc>` or type `kj` (`k` followed by
`j`).

**Example**: If you wanted to change the background to fade through the color spectrum. You would
type `<esc>`, then press `1` to edit the background, then press `h` until the display says `Solid
Fade`.

# Effects

It would be boring if all the sign did was show stationary text, so I made it needlessly more
complicated by adding effects.  The program is broken into to effects areas. Text Effects and
Color Effects. Text Effects control what segments are "on". Color Effects control what color the on
and off segments are.

At all times, for all effects

+ `R`: Resets to some factory standard.
+ `I`: Invert layer colors
+ `X`: Randomize text and color effects.

## Text Effects

Text Effects control what segments are "on".

+ `.`: Changes to the next text effect.
+ `,`: Changes to the previous text effect.

For all text effects:

+ `k`/`j`: Increases / Decrease the tempo
+ `t`: (Tap) text effect should change each time you press `t`
+ `g`: Pauses text

In general the following is true for text effects

+ `u`: Resets text effect to defaults.
+ `/`: Randomizes settings.

### Basic Typing

Like it sounds: In Insert mode, typing causes letters to be scrolled from right to left.

### Random On

Randomly turns segments on (or off). If the segment turned on is part of the displayed text it
will stay on

+ `]`/`[`: Increases / Decrease the number of random segments.
+ `o`: Switches from turning segments on to turning them off.
+ `u`: Turns all segments off
+ `/`: Randomizes settings

### Counter

Counts up or down some amount at some frequency

+ `]`/`[`: Increases / Decrease the .
+ `}`/`{`: Increase or decrease count by step size
+ `u`: Reset count to 1
+ `/`: Randomizes settings

### Random Letters

Different set of 4 random letters every beat

### Words Enter

Pushes last four letters typed to sign when you press enter. Backspace does work. Changes to next
word in stack every so may beats.

+ `u`: Remove all words from the stack
+ `K`/`J`: Increase / Decrease the number of beats on which the words change
+ `/`: Randomize settings

### Clock

Should tell time, its probably not correct.

+ `]`/`[`: Increase / decrease minutes
+ `}`/`{`: Increase / decrease hours
+ `o`: Toggle between clock (hh:mm) and timer (mm:ss)
+ `O`: Toggle between 12 hour time and 24 hour time

### Lines On

Turns on lines of segments in various different orientations

+ `]`/`[`: Change line orientation
+ `/`: Randomize settings
+ `p`: Toggle lines changing orientation on beat

### Random Scroll

Pushes random letter to sign scrolling style

## Color Effects

Color Effects control what color the on and off segments are. There are two "Layers" that you can
manipulate. Pressing `1` sets you editing the Background Layer. Pressing `2` sets you
to editing the Letters layer.

+ `1`: Edit "Background" color layer
+ `2`: Edit "Letters" color layer

Once you have chosen a layer pressing the `h` and `l` keys cycles through the different color
effects

+ `h`/`l`: Next/Previous Color Effect

In general for color effects

+ `x`: Randomizes color effect settings

+ `0`: Sets brightness to 0
+ `9`: Sets brightness to full

+ `b`/`B`: (Brightness) Decrease / Increase color Value
+ `c`/`C`: (Color) Decrease / Increase color Hue
+ `v`/`V`: (Vibrancy) Decrease / Increase color Saturation

+ `f`/`s`: Makes things go faster / slower

### Solid Color

Sets the selected color layer a solid non-changing color

+ `b`/`B`: (Brightness) Decrease / Increase color Value
+ `c`/`C`: (Color) Decrease / Increase color Hue
+ `v`/`V`: (Vibrancy) Decrease / Increase color Saturation

### Solid Fade

Fades the layer through the color spectrum. Can offset the color of each letter by setting a
non-zero Hue Step.

+ `f`/`s`: (Faster/Slower) Increase / Decrease fade speed.
+ `F`/`S`: Increase / decrease hue per letter step size.
+ `x`: Randomizes settings.

+ `b`/`B`: (Brightness) Decrease / Increase color Value.
+ `c`/`C`: (Color) Decrease / Increase color Hue.
+ `v`/`V`: (Vibrancy) Decrease / Increase color Saturation.

### Rainbow Letter

Steps the hue for each letter in the sign. Hues of letter oscillate around their set color by a
color hue amplitude

+ `w`/`W`: Jump hue forward or back
+ `e`/`E`: Increase / decrease color oscillation amplitude
+ `f`/`s`: Faster / slower oscillation cycle time.
+ `F`/`S`: Increase / Decrease hue per letter step size.

+ `d`: Toggle if color step is static with text changes.
+ `D`: Toggle if color changes on the beat.
+ `x`: Randomizes color settings

### Rainbow Segments

Steps the hue for each segment in the sign.

+ `w`/`W`: Jump hue forward or back
+ `f`/`s`: Increase / decrease hue step per segment
+ `F`/`S`: Increase / decrease hue step per beat

+ `d`: Toggle if color step is static with text changes.
+ `D`: Toggle if color changes on the beat.

+ `x`: Randomize settings
+ `r`: Resets settings to default

### Random Fade

This one if fun. Randomly Fades segments in the layer at a different rate. Typing letters will cause
the On segments to converge on a specific color after a certain amount of time has passed. Letters
and words will fade out of nothing and then fade away into chaos.

+ `f`/`s`: (Faster/Slower) Increase / Decrease maximum fade speed
+ `F`/`S`: (Faster/Slower) Decrease / Increase the time it takes to to converge.

To control the layer converge color:

+ `b`/`B`: (Brightness) Decrease / Increase color Value:
+ `c`/`C`: (Color) Decrease / Increase color Hue:
+ `v`/`V`: (Vibrancy) Decrease / Increase color Saturation:

### Fade To

Fades colors in a logarithmic fashion to the new text settings

+ `f`/`s`: (Faster/Slower) Increase / Decrease the time to converge to set colors
+ `x`: Randomize settings

To control the layer converge color:

+ `b`/`B`: (Brightness) Decrease / Increase color Value:
+ `c`/`C`: (Color) Decrease / Increase color Hue:
+ `v`/`V`: (Vibrancy) Decrease / Increase color Saturation:

### Wave Pixels

Pixels in segments oscillate around layer color.

+ `e`/`E`: Increase / decrease color oscillation amplitude.
+ `f`/`s`: (Faster/Slower) Decrease / Increase the oscillation cycle time.


<!--

# Q + A:

One of my "favorite" things about this project has been all the helpful suggestions that people
give, free of any effort on their end. If you really want to help. Make a pull request. I imagine
these questions in the tone of 1997 Valley Girl:

**Q**: Why are their only two letter. It would be way cooler if you had more letters so you could do
whole worlds.

**A**: No Shit. But cutting, grinding, welding, painting, soldering, wiring take time... And yes
I'd love help. I've actually got two more letters in the works, come find me at Burning Man and you'll be
able to spell naughty words to your hearts content.

**Q**: Why is it so complicated? Why not just use faders/dash pots to control things.

**A**: Things are as complicated as they can be, thats the nature of life. Adding faders/dashpots
makes things more complicated, not less. What you really want is a nicer user interface. In which
case I know its kind of cryptic, but I've only got limited bandwidth, but you can definitely help if
you want! I actually think it would be awesome to set up an old DJ Controller to change color
effects.

**Q**: You should make it sound reactive.

**A**: Yeah! This one is definitely on my list. I'd like to make the whole sign into one big Spectrum Analyser.

**Q**: Why not make an iPhone App.

**A**: Lets make it happen! I assume you know Objective-C / Swift ?
-->
