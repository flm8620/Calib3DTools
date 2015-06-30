
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"

void imageDoubleFromImageBYTE(const ImageGray<BYTE> &in, ImageGray<double> &out)
{
    out.resize(in.xsize(),in.ysize());
    int N=in.xsize()*in.ysize();
    for(int i=0;i<N;i++)out.data(i)=(double)in.data(i);
}
