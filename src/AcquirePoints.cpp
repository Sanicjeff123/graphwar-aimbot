#include <X11/Xlib.h>
#include <iostream>

struct point
{
    int x;
    int y;
    point(int x, int y) : x(x), y(y)
    {}

    const point operator-(const point &other) const
    {
        return point(x - other.x, y - other.y);
    }
};

point getMouseClick(Display * dsp)
{

    XEvent event;
    Window root = DefaultRootWindow(dsp);
    XGrabPointer(dsp, root, False, ButtonPressMask | ButtonReleaseMask |
            PointerMotionMask, GrabModeAsync, GrabModeAsync, None,
            None, CurrentTime);

    while(1)
    {
        XNextEvent(dsp, &event);
        switch (event.type)
        {
            case ButtonPress:
                if ( event.xbutton.button == 3 )
                {
                    throw 1;
                }
                return point( event.xbutton.x, event.xbutton.y);
                break;
            default:
                break;
        }
    }
}

int main(int argc, char *argv[])
{

    Display *dsp = XOpenDisplay(NULL);
    if(!dsp)
        return 1;

    const int quadrantWidth = 25;
    const int quadrantHeight = 15;

    std::cout << "Click top left..." << std::endl;

    point topLeft = getMouseClick(dsp);

    std::cout << "Click center..." << std::endl;

    point origin = getMouseClick(dsp);

    std::cout << "Click points (right click exits) ..." << std::endl;
    const point pixelDimensions = origin - topLeft;

    float xScale = quadrantWidth / float(pixelDimensions.x) ;
    float yScale = quadrantHeight / float(pixelDimensions.y) ;

    while(1)
    {
        try
        {
            point newPoint = getMouseClick(dsp)- origin;
            std::cout << xScale * newPoint.x << " " << yScale *newPoint.y << std::endl;
        } catch (int e)
        {
            break;
        }
    }
    XCloseDisplay( dsp );

}
