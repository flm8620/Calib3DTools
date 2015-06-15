#ifndef DISTORTION_H
#define DISTORTION_H

#include "LM.h"



template <typename T> libNumerics::vector<T> bicubicDistModel(const libNumerics::vector<T>& completeParams, const libNumerics::matrix<T>& coefTerm);

/// Class for one line.
template <typename T>
class LineData {
public:
	LineData() { nPoints = 0; }

private: 
	std::vector<T> _pointX, _pointY; ///< Vectors for x and y coordinates.
	int nPoints;
    libNumerics::matrix<T> _coefTermX, _coefTermY; ///< Matrices for keeping constant values of polynomial.

public:
	int sizeLine() { return nPoints; }
	T x(int i) { return _pointX[i]; } ///< Access x coordinate of index \a i.
	T y(int i) { return _pointY[i]; } ///< Access y coordinate of index \ai.
	void pushPoint(const T x, const T y); ///< Add point to a line.
    void theta(const libNumerics::vector<T>& paramsX, const libNumerics::vector<T>& paramsY, T& alpha, T& beta); ///< Sines and cosines of line angle for each point in a line.
    libNumerics::vector<T> jacobian(const libNumerics::vector<T>& paramsX, const libNumerics::vector<T>& paramsY, const libNumerics::vector<int>& flagX, const libNumerics::vector<int>& flagY) const ;
    libNumerics::vector<T> residuals(const libNumerics::vector<T>& paramsX, const libNumerics::vector<T>& paramsY) const;
    T RMSE(const libNumerics::vector<T>& paramsX, const libNumerics::vector<T>& paramsY) const;
	void coefTermsCalc(int degX, int degY, T xp, T yp, T scale = 0);

private:
    void coefTermFill(libNumerics::matrix<T>& coefTerm, int deg, T x, T y) const;
}; // LineData

template <typename T>
class LMRectifyDistortion;

/// Class for a set of lines.
template <typename T>
class DistortedLines {
public:
	std::vector< LineData<T> > _line;
	int nLines, nGroups; // one group = one image
	std::vector<int> nlines4Group;
	DistortedLines() { nLines = 0; nGroups = 0; }
	int totalPointsNumber();
	void pushMemGroup(int numLines);
	void pullMemoryLine(void);
	void pushPoint(int idxLine, T valX, T valY) { _line[idxLine].pushPoint(valX, valY); } ///< Add a point to a line with index \a idxLine.
    T RMSE(const libNumerics::vector<T>& paramsX, const libNumerics::vector<T>& paramsY, int degX, int degY, T xp, T yp);
    T RMSE_max(const libNumerics::vector<T>& paramsX, const libNumerics::vector<T>& paramsY, int degX, int degY,  T xp, T yp);
    libNumerics::vector<T> correctionLMA(libNumerics::vector<T>& paramsX, libNumerics::vector<T>& paramsY, libNumerics::vector<int>& flagX, libNumerics::vector<int>& flagY,
		int degX, int degY, T xp, T yp);
    libNumerics::vector<T> verification(const libNumerics::vector<T>& paramsX, const libNumerics::vector<T>& paramsY, const libNumerics::vector<int>& flagX, const libNumerics::vector<int>& flagY,
		int b_order, int c_order, T xp, T yp);

private:
    void estimatedThetas(const libNumerics::vector<T>& paramsX, const libNumerics::vector<T>& paramsY, libNumerics::vector<T>& alpha, libNumerics::vector<T>& beta, int degX, int degY, T xp, T yp);
	void normalization(DistortedLines<T>& normDistLines, T& scale, T xp, T yp);
}; // DistortionLines

/// Class to refine the distortion polynomial parameters.
template <typename T>
class LMRectifyDistortion : public libNumerics::MinLM<T>
{
public:
    LMRectifyDistortion(int oX, int oY, libNumerics::vector<int>& flagx, libNumerics::vector<int>& flagy, DistortedLines<T>& normDistLines, T scale, T xp, T yp);

private:
	int orderX, orderY;
    libNumerics::vector<int> flagX, flagY;
	DistortedLines<T> distLines;

public:
    virtual void modelData(const libNumerics::vector<T>& P, libNumerics::vector<T>& ymodel) const;
    virtual void modelJacobian(const libNumerics::vector<T>& P,  libNumerics::matrix<T>& J) const;
}; // LMRectiryDistortion

template <typename T> void denormalization(libNumerics::vector<T>& denormX, libNumerics::vector<T>& denormY, const libNumerics::vector<T>& normX, const libNumerics::vector<T>& normY,
	T scaleX, T scaleY, int orderX, int orderY);

/// Returns a correction polynomial for the given distortion one.
template <typename T>
libNumerics::vector<T> getParamsInv(const libNumerics::vector<T>& paramsX, const libNumerics::vector<T>& paramsY, int degX, int degY, int w, int h, T xp, T yp);

/// Returns a correction polynomial for the given corrected and distorted coordinates.
template <typename T>
libNumerics::vector<T> getParamsCorrection(libNumerics::vector<T>& x_corr, libNumerics::vector<T>& y_corr, libNumerics::vector<T>& x_dist, libNumerics::vector<T>& y_dist, int degX, int degY, T xp, T yp);

// Need to see definitions for templates...
#include "distortion.cpp"

#endif
