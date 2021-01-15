#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    
    // TODO Fill this in
    x = x < 0 ? 0 : x;
    x = x >= im.w ? im.w - 1 : x;
    y = y < 0 ? 0 : y;
    y = y >= im.h ? im.h - 1 : y;
    return im.data[(c * im.w * im.h) + (y * im.w) + x];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
    if (x < 0 || x >= im.w || y < 0 || y >= im.h) {
        return;
    }
    im.data[(c * im.w * im.h) + (y * im.w) + x] = v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    for (int ch = 0; ch < 3; ch++) {
        for (int i = 0; i < im.h; i++) {
            for (int j = 0; j < im.w; j++) {
                set_pixel(copy, j, i, ch, get_pixel(im, j, i, ch));
            }
        }
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // Y' = 0.299 R' + 0.587 G' + .114 B'
    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {
            float new_val = 0.299 * get_pixel(im, j, i, 0) + 0.587 * get_pixel(im, j, i, 1) + 0.114 * get_pixel(im, j, i, 2);
            set_pixel(gray, j, i, 0, new_val);
        }
    }
    // TODO Fill this in
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {
            set_pixel(im, j, i, c, get_pixel(im, j, i, c) + v);
        }
    }

}

void clamp_image(image im)
{
    // TODO Fill this in
    for (int ch = 0; ch < 3; ch++) {
        for (int i = 0; i < im.h; i++) {
            for (int j = 0; j < im.w; j++) {
                float val = get_pixel(im, j, i, ch);
                val = val < 0 ? 0 : val;
                val = val > 255 ? 255 : val;
                set_pixel(im, j, i, ch, val);
            }
        }
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
    
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}

