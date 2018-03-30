#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "CinderTablet.h"
#include "CinderTabletApp.h"

using namespace ci;
using namespace ci::app;

class SimpleTabletApp : public CinderTabletApp {
  public:
    SimpleTabletApp();
    virtual ~SimpleTabletApp() = default;
	void mouseDown( MouseEvent event ) override;
    void mouseDrag( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
	void draw() override;
  private:
    void applyStroke( const TabletData &tabletData );
    float mRadius { 20.0f };
    struct Point
    {
        vec2 pos{ 0.0f };
        float scale{ 1.0f };
    };
    std::vector<Point> mPoints;
};

SimpleTabletApp::SimpleTabletApp()
{
    mTablet.getTabletPointSignal().connect( [this] ( const TabletData &tabletData ) { applyStroke( tabletData ); } );
    mPoints.reserve( 2048 );
}

void SimpleTabletApp::applyStroke( const TabletData &tabletData )
{
    vec2 relPos =  vec2( tabletData.x, tabletData.y );
    relPos.y = getWindowHeight() - relPos.y;
   
    //ci::app::console() << relPos << "\n";
    if( getWindowBounds().contains( relPos ) )
    {
        mPoints.push_back( Point { vec2( relPos ), tabletData.pressure } );
        refresh();
    }
}

void SimpleTabletApp::mouseDown( MouseEvent event )
{
    if( mTablet.isStylusInProximity() )
    {
        return;
    }
    // Store the current mouse position in the list.
    mPoints.push_back( Point { event.getPos(), 1.0f } );
    refresh();
}

void SimpleTabletApp::mouseDrag( MouseEvent event )
{
    if( mTablet.isStylusInProximity() )
    {
        return;
    }
    mPoints.push_back( Point { event.getPos(), 1.0f } );
    refresh();
}

void SimpleTabletApp::keyDown( KeyEvent event )
{
    if( event.getCode() == KeyEvent::KEY_SPACE )
    {
        // Clear the list of points when the user presses the space bar.
        mPoints.clear();
        refresh();
    }
    else if( event.getCode() == KeyEvent::KEY_ESCAPE )
    {
        // Exit full screen, or quit the application, when the user presses the ESC key.
        quit();
    }
}

void SimpleTabletApp::draw()
{
    gl::clear( Color::gray( 0.1f ) );
    gl::color( 1.0f, 0.5f, 0.25f );
    
    for( const auto &point : mPoints )
    {
        gl::drawSolidCircle( point.pos, point.scale * mRadius );
    }
}

CINDER_APP( SimpleTabletApp, RendererGl( RendererGl::Options().msaa( 8 ) ) )
