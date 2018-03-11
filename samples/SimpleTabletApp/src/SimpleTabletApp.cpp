#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "CinderTablet.h"

using namespace ci;
using namespace ci::app;

class SimpleTabletApp : public App {
  public:
    SimpleTabletApp();
	void mouseDown( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
  private:
    void applyStroke( const TabletData &tabletData );
    ciTablet mTablet;
    float mRadius;
    std::vector<vec3> mPoints;
};

SimpleTabletApp::SimpleTabletApp()
    : mRadius( 10.0f )
{
    std::function<void(const TabletData &)> tabletFunc = std::bind( &SimpleTabletApp::applyStroke, this, std::placeholders::_1 );
    mTablet.getTabletSignal().connect( tabletFunc );
    setFullScreen( true );
}

void SimpleTabletApp::applyStroke( const TabletData &tabletData )
{
    
    vec2 relPos =  isFullScreen() ? vec2( tabletData.x, tabletData.y ) :
                                   ( vec2( tabletData.x, tabletData.y ) - vec2( getWindowPos() ) );
    relPos.y = getWindowHeight() - relPos.y;
   
    if(getWindowBounds().contains( relPos ) ) only if mouse is down and pressure  > 0.0f
    {
        mPoints.push_back( vec3( relPos, tabletData.pressure ) );
    }
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

void SimpleTabletApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::begin( GL_LINE_STRIP );
    for( const vec3 &point : mPoints ) {
        gl::color( 1.0f, 1.0f, 1.0f, point.z );
        gl::vertex( point );
    }
    gl::end();
    gl::color( 1.0f, 1.0f, 1.0f, 1.0f );
}

CINDER_APP( SimpleTabletApp, RendererGl )
