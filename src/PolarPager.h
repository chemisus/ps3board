/* 
 * File:   PolarPager.h
 * Author: chemisus
 *
 * Created on March 29, 2013, 5:00 PM
 */

#ifndef POLARPAGER_H
#define	POLARPAGER_H

class PolarPager : public Pager {
public:
    PolarPager();
    virtual ~PolarPager();
    int page(int x, int y);
private:

};

#endif	/* POLARPAGER_H */

