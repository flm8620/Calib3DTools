/* Spline interpolation.
    Copyright (C) 2007 Lionel Moisan <Lionel.Moisan@parisdescartes.fr>
    Copyright (C) 2010 Pascal Monasse <monasse@imagine.enpc.fr>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include "image.h"
//#include "libLWImage/LWImage.h"

/* fast integral power function */
inline double ipow(double x, int power)
{
    unsigned abs = power<0 ? -power:power;
    double result;
    for (result=1.0; abs!=0; abs>>=1, x*=x) if( abs&1 ) result *= x;
    return power<0 ? 1.0/result : result;
}

bool prepare_spline(ImageGray<double>& image, int order);
bool prepare_spline_RGB(ImageRGB<double> &image, int order);
bool interpolate_spline(const ImageGray<double> &im, int order,
                        double x, double y,
                        double &out,
                        double paramKeys=-.5);
bool interpolate_spline_RGB(const ImageRGB<double> &image, int order,
                        double x, double y,
                        double &Rout, double &Gout, double &Bout,
                        double paramKeys=-.5);



#endif
