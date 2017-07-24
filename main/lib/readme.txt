Revision 5 - 2016 May 4
-updated to ServoTINAH, which should improve servo glitch problems.  May allow for upto 8 servo pins driving outputs, but this is untested.



Revision 4 - 2015 Jan 2
-rewrote functions to operate in Arduino IDE.
-motor.speed command runs from -255 to 255 (PWM outputs are 8-bit in Arduino IDE)
-servo command temporarily runs on timing limits rather than angle limits


Revision 3 - 2009 May 20

-added analogWriteReset function

-added access to Timer1PWM_off, Timer3PWM_off functions (in phys253.h)



Revision 2 - 2009 May 15

-corrected servo motor numbering (0, 1, and 2 instead of 1, 2, and 3)





Revision 1 - 2009 May 5

-first release.



