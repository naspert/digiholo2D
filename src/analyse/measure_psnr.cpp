/* 
 * File:   measure_psnr.cpp
 * Author: b.steltner
 *
 * Created on 8. Dezember 2014, 10:41
 */

#include "analyse/measure_psnr.h"
#include "image/row_major_float_image.h"

measure_psnr::measure_psnr(sharedptr<row_major_float_image> noisy_img, sharedptr<row_major_float_image> orig_img, int bit) : noisy_img(noisy_img), orig_img(orig_img), max(bit) {
    //empty

}

//measure_psnr::~measure_psnr() {
//   
//}

float measure_psnr::calculate_psnr() {
    long W = noisy_img->get_width();
    long H = noisy_img->get_height();

    //Workaround that images may have a constant offset. This is ONLY true if noise has mean ~= 0! Otherwise this leads to wrong PSNR-Values!
    auto offset = this->offset();

    double mse = 0.0; //mean squared error
    for (long iw = 0; iw < W; iw++) {
        for (long ih = 0; ih < H; ih++) {
            mse += std::pow(orig_img->get_pixel(iw, ih) - noisy_img->get_pixel(iw, ih) - offset, 2);
        }
    }

    mse /= (W * H);
    DEBUG_PRINTLN("mse - sum: " << mse);

    if (mse * mse > FLT_EPSILON * FLT_EPSILON * 1000) {
        auto max_pixel_value = std::pow(2, this->max) - 1;
        auto psnr = 10 * std::log10(max_pixel_value / mse);
        //        DEBUG_PRINTLN("psnr: " << psnr);
        return static_cast<float>(psnr);
    }
    DEBUG_PRINTLN("psnr: max");
    return FLT_MAX;
}

double measure_psnr::offset() {
    auto orig_offset = mean_of_block(100, 100, this->orig_img);
    auto noisy_offset = mean_of_block(100, 100, this->noisy_img);

    auto offset = orig_offset - noisy_offset;
    DEBUG_PRINTLN("offset: " << offset);

    offset = round(offset / (2 * M_PI));
    DEBUG_PRINTLN("offset: " << offset);

    return offset * 2 * M_PI;

}

double measure_psnr::mean_of_block(long w, long h, sharedptr<row_major_float_image> img) {
    long W = img->get_width();
    long H = img->get_height();

    w = w < W ? w : W; //catch errors
    h = h < H ? w : H;

    double mean = 0;

    for (long iw = 0; iw < w; iw++) {
        for (long ih = 0; ih < h; ih++) {
            mean += img->get_pixel(iw, ih);
        }
    }
    mean /=  (w * h);
    return mean;
}


