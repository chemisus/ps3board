/* 
 * File:   CartesianPager.cpp
 * Author: chemisus
 * 
 * Created on March 29, 2013, 4:51 PM
 */

#include "Pager.h"
#include "CartesianPager.h"

#define BOX 16000

CartesianPager::CartesianPager()
{
}

CartesianPager::~CartesianPager()
{
}


int CartesianPager::page(int x, int y)
{
    int j = 0;
    int i = 0;

    if (x <= -BOX) {
        j = 0;
    }
    else if (x <= BOX) {
        j = 1;
    }
    else {
        j = 2;
    }

    if (y <= -BOX) {
        i = 0;
    }
    else if (y <= BOX) {
        i = 1;
    }
    else {
        i = 2;
    }

    return i * 3 + j;

}
