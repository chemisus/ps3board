/* 
 * File:   CartesianPager.h
 * Author: chemisus
 *
 * Created on March 29, 2013, 4:51 PM
 */

#ifndef CARTESIANPAGER_H
#define	CARTESIANPAGER_H

class CartesianPager : public Pager {
public:
    CartesianPager();
    virtual ~CartesianPager();
    int page(int x, int y);
private:

};

#endif	/* CARTESIANPAGER_H */
