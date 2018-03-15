#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "CinderTablet.h"
#include "CinderTabletApp.h"

using namespace ci;
using namespace ci::app;

class SimpleTabletApp : public App {//public CinderTabletApp {
  public:
    SimpleTabletApp();
    virtual ~SimpleTabletApp() = default;
	void mouseDown( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
  private:
    void applyStroke( const TabletData &tabletData );
    CinderTablet mTablet;
    float mRadius { 10.0f };
    std::vector<vec2> mPoints;
};

SimpleTabletApp::SimpleTabletApp()
{
    mTablet.getTabletPointSignal().connect( [this] ( const TabletData &tabletData ) { applyStroke( tabletData ); } );
    //setFullScreen( true );
}

void SimpleTabletApp::applyStroke( const TabletData &tabletData )
{
    
    vec2 relPos =  isFullScreen() ? vec2( tabletData.x, tabletData.y ) :
                                   ( vec2( tabletData.x, tabletData.y ) - vec2( getWindowPos() ) );
    relPos.y = getWindowHeight() - relPos.y;
   
    if( getWindowBounds().contains( relPos ) ) //??? only if mouse is down and pressure  > 0.0f
    {
        mPoints.push_back( vec3( relPos, tabletData.pressure ) );
    }
}

void SimpleTabletApp::mouseDown( MouseEvent event )
{
    // Store the current mouse position in the list.
    mPoints.push_back( event.getPos() );
}

void SimpleTabletApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 'f' ) {
        // Toggle full screen when the user presses the 'f' key.
        setFullScreen( ! isFullScreen() );
    }
    else if( event.getCode() == KeyEvent::KEY_SPACE ) {
        // Clear the list of points when the user presses the space bar.
        mPoints.clear();
    }
    else if( event.getCode() == KeyEvent::KEY_ESCAPE ) {
        // Exit full screen, or quit the application, when the user presses the ESC key.
        if( isFullScreen() )
            setFullScreen( false );
        else
            quit();
    }
}

void SimpleTabletApp::update()
{
    
}

void SimpleTabletApp::draw()
{
    // Clear the contents of the window. This call will clear
    // both the color and depth buffers.
    gl::clear( Color::gray( 0.1f ) );
    
    // Set the current draw color to orange by setting values for
    // red, green and blue directly. Values range from 0 to 1.
    // See also: gl::ScopedColor
    gl::color( 1.0f, 0.5f, 0.25f );
    
    // We're going to draw a line through all the points in the list
    // using a few convenience functions: 'begin' will tell OpenGL to
    // start constructing a line strip, 'vertex' will add a point to the
    // line strip and 'end' will execute the draw calls on the GPU.
    gl::begin( GL_LINE_STRIP );
    for( const vec2 &point : mPoints ) {
        gl::vertex( point );
    }
    gl::end();
    
    /*
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::begin( GL_LINE_STRIP );
    for( const vec3 &point : mPoints ) {
        gl::color( 1.0f, 1.0f, 1.0f, point.z );
        gl::vertex( point );
    }
    gl::end();
    gl::color( 1.0f, 1.0f, 1.0f, 1.0f );
     */
}

CINDER_APP( SimpleTabletApp, RendererGl )
