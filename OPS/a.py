from PIL import Image
from math import *
import os

# clamp a value to a range
def clamp(val, minval, maxval):
    return min((max((minval, val)), maxval))

# map a value from one range to another
def lerpMap(val, rangeA, rangeB):
    return (val-rangeA[0])/(rangeA[1] - rangeA[0])*(rangeB[1] - rangeB[0])

# get the color associated with a certain wavelength, in nm
def wavelengthToRGB(wl):
    w = (int)(wl)

    # colour
    if w >= 380 and w < 440:
        R = -(w - 440.) / (440. - 350.)
        G = 0.0
        B = 1.0
    elif w >= 440 and w < 490:
        R = 0.0
        G = (w - 440.) / (490. - 440.)
        B = 1.0
    elif w >= 490 and w < 510:
        R = 0.0
        G = 1.0
        B = -(w - 510.) / (510. - 490.)
    elif w >= 510 and w < 580:
        R = (w - 510.) / (580. - 510.)
        G = 1.0
        B = 0.0
    elif w >= 580 and w < 645:
        R = 1.0
        G = -(w - 645.) / (645. - 580.)
        B = 0.0
    elif w >= 645 and w <= 780:
        R = 1.0
        G = 0.0
        B = 0.0
    else:
        R = 0.0
        G = 0.0
        B = 0.0

    # intensity correction
    if w >= 380 and w < 420:
        SSS = 0.3 + 0.7*(w - 350) / (420 - 350)
    elif w >= 420 and w <= 700:
        SSS = 1.0
    elif w > 700 and w <= 780:
        SSS = 0.3 + 0.7*(780 - w) / (780 - 700)
    else:
        SSS = 0.0
    SSS *= 255

    return (int(clamp(SSS*R, 0, 255)), int(clamp(SSS*G, 0, 255)), int(clamp(SSS*B, 0, 255)))

# convert a floating point number between -1 and 1 to a color between red and violet
def floatToRGB(fl):
    return wavelengthToRGB(lerpMap(fl, (1,-1), (380,780)))

# calculate the distance between two points
def distance_between(a, b):
    return sqrt((b[0]-a[0])**2 + (b[1]-a[1])**2)

# a function for a square wave with period 1
def sq_wave(x):
    if(modf(x)[0]>0.5):
        return 1
    else:
        return -1

size = (256, 256)                                                          #the canvas size to render

im = Image.new('RGB', size)                                                 #the image object to manipulate
pix = im.load()                                                             #load the image's pixel buffer

for i in range(0, size[0]):                                                 #for x
    for j in range(0, size[1]):                                             #for y

        # DO INTERESTING THINGS HERE ~~~~~

        # draw a red-green gradient in two axes
        pix[i,j] = (int(i*1.0/size[0] * 255),int(j*1.0/size[1] * 255),0,0)

im.save('output.png', 'PNG')        


