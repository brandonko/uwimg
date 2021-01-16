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
    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {
            float r = get_pixel(im, j, i, 0);
            float g = get_pixel(im, j, i, 1);
            float b = get_pixel(im, j, i, 2);

            float V = three_way_max(r,g,b);
            float m = three_way_min(r, g, b);
            float C = V - m;
            float S = V == 0 ? 0 : C / V;

            float H_prime = 0;
            float H = 0;

            if (C != 0) {
                if (V == r) {
                    H_prime = (g - b) / C;
                } else if (V == g) {
                    H_prime = ((b - r) / C) + 2;
                } else if (V == b) {
                    H_prime = ((r - g) / C ) + 4;
                }

                if (H_prime < 0) {
                    H = (H_prime / 6) + 1;
                } else {
                    H = H_prime / 6;
                }
            }

            set_pixel(im, j, i, 0, H);
            set_pixel(im, j, i, 1, S);
            set_pixel(im, j, i, 2, V);
        }
    }
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
    for (int i = 0; i < im.h; i++) {
        for (int j = 0; j < im.w; j++) {
            float H = get_pixel(im, j, i, 0);
            float S = get_pixel(im, j, i, 1);
            float V = get_pixel(im, j, i, 2);

            float R = 0;
            float G = 0;
            float B = 0;

            if (S <= 0) {
                R = V;
                G = V;
                B = V;
            } else {
                if (H > 1) H = 0;
                float HH = H * 6;
                long i = (long) HH;
                float FF = HH - i;
                float p = V * (1.0 - S);
                float q = V * (1.0 - (S * FF));
                float t = V * (1.0 - (S * (1.0 - FF)));

                switch (i) {
                    case 0:
                        R = V;
                        G = t;
                        B = p;
                        break;
                    case 1:
                        R = q;
                        G = V;
                        B = p;
                        break;
                    case 2:
                        R = p;
                        G = V;
                        B = t;
                        break;
                    case 3:
                        R = p;
                        G = q;
                        B = V;
                        break;
                    case 4:
                        R = t;
                        G = p;
                        B = V;
                        break;
                    case 5:
                    default:
                        R = V;
                        G = p;
                        B = q;
                        break;
                }
            }

            set_pixel(im, j, i, 0, R);
            set_pixel(im, j, i, 1, G);
            set_pixel(im, j, i, 2, B);
        }
    }
}

