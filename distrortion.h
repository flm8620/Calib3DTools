#ifndef DISTRORTION_H
#define DISTRORTION_H

#include <QList>

typedef QList<double> Distortion;

class DistortionContainer
{
public:
    virtual Distortion getDistortion_threadSafe() =0;
    virtual void saveDistortion_threadSafe(const Distortion& value) =0;
    virtual bool isEmpty() =0;
};

#endif // DISTRORTION_H

