#ifndef H_GEOMETRIC_CORRECTION
#define H_GEOMETRIC_CORRECTION
#include <vector>

class Vector3f;
class Matrix3f;
using cv::Mat;
using cv::Point2f;

class GeoCorrection
{
public:
	enum Geotype{PROJECTION, RENDER };
	GeoCorrection() : grid(), rtImage(), subdivLv(0), corrected(false), gridDetects(), rtDetects(){}
	GeoCorrection(const cv::Mat _grid, const cv::Mat _rtImage, int _lv = 0);
	~GeoCorrection();
	void runCorrection(int level);
	void bakeCorrection(const cv::Mat& source, cv::Mat& destination);
	void updateImages(const Mat& _grid, const Mat& _rtImage);

	// opengl functions
	void initTexWindow();
	void resizeTexWindow(int width, int height);
	
	static int gridX, gridY, rtX, rtY, winX, winY;
private:
	static void bezfitDisplay();
	static void bezfitKeyboard(unsigned char key, int x, int y);

	void findGrids(Geotype type, int level);
	void sort(cv::Mat& arr, int level);

	cv::Mat grid, rtImage;
	int subdivLv;
	bool corrected;
	std::vector<cv::Point2f> gridDetects, rtDetects; // grids found in projection image(projector) and ray tracing image(camera)
};

//inline cv::Point2f estimateControlPoint(const cv::Point2f& cp0, const cv::Point2f& cp2, const cv::Point2f& curvePoint, double t)
//{
//	double X, Y;
//	double diff = 1.0 - t;
//	double sqrT = t*t, sqrDiff = diff*diff;
//	X = (curvePoint.x - sqrDiff*cp0.x - sqrT*cp2.x) / (2 * diff*t);
//	Y = (curvePoint.y - sqrDiff*cp0.y - sqrT*cp2.y) / (2 * diff*t);
//
//	return cv::Point2f(X, Y);
//}

#endif