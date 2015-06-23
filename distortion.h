#ifndef DISTRORTION_H
#define DISTRORTION_H
#include <QtCore>
#include <vector>
#include <utility>

/**
 * @brief Distortion of image
 * Distortion is presented by two polynomial who correct respectively
 * the X and Y coordinate of pixels in a image.
 * For a pixel (x0, y0) in image, after correction, it moves to (X0, Y0),
 * and we have:
 *
 * X0 = polyX(x0,y0) = a0*x^0*y0 + a1*x^1*y^0 + a2*x^0*y^1+ ...
 * Y0 = polyY(x0,y0) = b0*x^0*y0 + b1*x^1*y^0 + b2*x^0*y^1+ ...
 *
 * For example, when maxOrder=3:
 * QList<QPair<double,double> >:
 * xParam           yParam
 *
 * a0 * x^0*y^0    b0 * x^0*y^0
 *
 * a1 * x^1*y^0    b1 * x^1*y^0
 * a2 * x^0*y^1    b2 * x^0*y^1
 *
 * a3 * x^2*y^0    b3 * x^2*y^0
 * a4 * x^1*y^1    b4 * x^1*y^1
 * a5 * x^0*y^2    b5 * x^0*y^2
 *
 * a6 * x^3*y^0    b6 * x^3*y^0
 * a7 * x^2*y^1    b7 * x^2*y^1
 * a8 * x^1*y^2    b8 * x^1*y^2
 * a9 * x^0*y^3    b9 * x^0*y^3
 * size = 10 = (2+maxOrder) * (1+maxOrder) / 2
 * maxOrder = -1 if the distortion is empty
 *
 */
struct DistortionValue
{
    DistortionValue();
    std::vector<std::pair<double, double> > _XYData;
    int _maxOrder;
    int _size;
    void setMaxOrder(int maxOrder);
    bool isValid()const;
    int sizeFromMaxOrder(int maxOrder)const
    {
        return maxOrder >= 0 ? (2+maxOrder)*(1+maxOrder)/2 : 0;
    }
};
/**
 * @brief The Distortion class
 *
 * @note All public functions of this class are thread-safe
 */
class Distortion : public QObject
{
    Q_OBJECT
public:
    Distortion(QObject *parent = 0);

    bool isEmpty();

    int maxOrder() const;

    void setMaxOrder(int maxOrder);

    int size() const;

    /**
     * @brief XYfromIdx
     * @param idx index in array
     * @param degX integer powers of X
     * @param degY integer powers of Y
     *    X 0 1 2 3
     *   Y
     *   0  0 1 3 6
     *   1  2 4 7
     *   2  5 8    <--idx
     *   3  9
     *
     * e.g. idx=6, a6 -> x^3*y^0, so x=3 y=0
     */
    static void XYfromIdx(int idx, int &degX, int &degY);
    static int idxFromXY(int degX, int degY);

    DistortionValue getValue() const;
    bool setValue(const DistortionValue &value);

    bool setXParamVector(const std::vector<double> &xVector);
    bool setYParamVector(const std::vector<double> &yVector);

    void setXParam(double value, int degX, int degY);
    void setYParam(double value, int degX, int degY);

    void setXParam(double value, int idx);
    void setYParam(double value, int idx);

    int xParam(int degX, int degY) const;
    int yParam(int degX, int degY) const;

    double xParam(int idx) const;
    double yParam(int idx) const;

    void clear();

signals:
    void dataChanged();

protected:
    mutable QReadWriteLock rwLock;

private:
    DistortionValue value;
};

#endif // DISTRORTION_H
