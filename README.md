# ppm_overlay
Overlay two ppm figures, define transparency and background color
ppm_overlay.c -o ppm_overlay -lm -O3

usage ppm_overlay <pic1.ppm> <pic2.ppm> <transparencey> <bgcolor_r> <bgcolor_g> <bgcolor_b>\n");    
Put on top of pic1 the pic2 (must have the same size). The transparency defines if pic2 is transparent (1) or or not (0) with respect
to pic1. Every value in between gives a linear extrapolation. The pics must be in the ppm raw format (P6 in header). The background color (rgb) defines the background color of the pics which should be the same for all pics. If there is background color in the picture object, of course this is also treated as background 
