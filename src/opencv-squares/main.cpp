// The "Square Detector" program.
// It loads several images sequentially and tries to find squares in
// each image

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <math.h>
#include <string.h>

#include <comicflick.h>

using namespace cv;
using namespace std;

void help()
{
    cout <<
    "\nA program using pyramid scaling, Canny, contours, contour simpification and\n"
    "memory storage (it's got it all folks) to find\n"
    "squares in a list of images provided as arguments\n"
    "Returns sequence of squares detected on the image.\n"
    "the sequence is stored in the specified memory storage\n"
    "Using OpenCV version " << CV_VERSION << endl;
}

const char* wndname = "Square Detection Demo";

// the function draws all the squares in the image
void drawSquares( Mat& image, const vector<vector<Point> >& squares )
{
    for( size_t i = 0; i < squares.size(); i++ )
    {
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        polylines(image, &p, &n, 1, true, Scalar(0,255,0), 3, CV_AA);
    }

    imshow(wndname, image);
}


int main(int argc, char** argv)
{
    help();
    namedWindow( wndname, 1 );
    vector<vector<Point> > squares;

    for( int i = 1; i < argc; i++ )
    {
        Mat image = imread(argv[i], 1);
        if( image.empty() )
        {
            cout << "Couldn't load " << argv[i] << endl;
            continue;
        }

        squares = comicflick::findRectangles(image);
        drawSquares(image, squares);

        int c = waitKey();
        if( (char)c == 27 )
            break;
    }

    return 0;
}

