/****
   universe.c
   version 2
   Richard Vaughan  
****/

#include <assert.h>
#include <unistd.h>

#include "antix.h"
using namespace Uni;

const char* PROGNAME = "universe";

#if GRAPHICS
#include <GLUT/glut.h> // OS X users need <glut/glut.h> instead
#endif

// initialize static members
double Robot::worldsize(1.0);
double Robot::range( 0.1 );
double Robot::fov(  dtor(270.0) );
std::vector<Robot*> Robot::population;
unsigned int Robot::population_size( 100 );
unsigned int Robot::sleep_msec( 50 );
uint64_t Robot::updates(0);
uint64_t Robot::updates_max( 0.0 ); 
bool Robot::paused( false );
int Robot::winsize( 600 );
int Robot::displaylist(0);
bool Robot::show_data( true );
std::vector<Robot::Puck> Robot::pucks;
unsigned int Robot::home_count(6);
std::set<Home*> Robot::homes;

char usage[] = "Universe understands these command line arguments:\n"
 "  -? : Prints this helpful message.\n"
 "  -c <int> : sets the number of pixels in the robots' sensor.\n"
 "  -d  Disables drawing the sensor field of view. Speeds things up a bit.\n"
 "  -f <float> : sets the sensor field of view angle in degrees.\n"
 "  -p <int> : set the size of the robot population.\n"
 "  -r <float> : sets the sensor field of view range.\n"
 "  -s <float> : sets the side length of the (square) world.\n"
 "  -u <int> : sets the number of updates to run before quitting.\n"
 "  -w <int> : sets the initial size of the window, in pixels.\n"
 "  -z <int> : sets the number of milliseconds to sleep between updates.\n";

#if GRAPHICS
// GLUT callback functions ---------------------------------------------------

// update the world - this is called whenever GLUT runs out of events
// to process
static void idle_func( void )
{
  Robot::UpdateAll();
}

static void timer_func( int dummy )
{
  glutPostRedisplay(); // force redraw
}

// draw the world - this is called whenever the window needs redrawn
static void display_func( void ) 
{  
  glClear( GL_COLOR_BUFFER_BIT );  
  Robot::DrawAll();
  glutSwapBuffers();
	
  // run this function again in about 50 msec
  glutTimerFunc( 20, timer_func, 0 );
}

static void mouse_func(int button, int state, int x, int y) 
{  
  if( (button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN ) )
	 {
		Robot::paused = !Robot::paused;
	 }
}

// render all robots in OpenGL
void Robot::DrawAll()
{
	FOR_EACH( r, population )
		(*r)->Draw();
	
	FOR_EACH( h, homes )
		{
			Home* hp = *h;
			glColor3f( hp->color.r, 
								 hp->color.g,
								 hp->color.b );
			
			glBegin(GL_LINE_LOOP);
			for( float a=0; a<(M_PI*2.0); a+=M_PI/16 )
				glVertex2f( hp->x + sin(a) * hp->r, 
										hp->y + cos(a) * hp->r );
			glEnd();

			glBegin(GL_LINE_LOOP);
			for( float a=0; a<(M_PI*2.0); a+=M_PI/16 )
				glVertex2f( hp->x+worldsize + sin(a) * hp->r, 
										hp->y + cos(a) * hp->r );
			glEnd();

			glBegin(GL_LINE_LOOP);
			for( float a=0; a<(M_PI*2.0); a+=M_PI/16 )
				glVertex2f( hp->x-worldsize + sin(a) * hp->r, 
										hp->y + cos(a) * hp->r );
			glEnd();

			glBegin(GL_LINE_LOOP);
			for( float a=0; a<(M_PI*2.0); a+=M_PI/16 )
				glVertex2f( hp->x + sin(a) * hp->r, 
										hp->y + worldsize + cos(a) * hp->r );
			glEnd();

			glBegin(GL_LINE_LOOP);
			for( float a=0; a<(M_PI*2.0); a+=M_PI/16 )
				glVertex2f( hp->x + sin(a) * hp->r, 
										hp->y - worldsize + cos(a) * hp->r );
			glEnd();


		}
	
	glColor3f( 1,1,1 ); // green
	glBegin( GL_POINTS );
	FOR_EACH( p, pucks )
		glVertex2f( p->x, p->y );
	glEnd();
}

#endif // GRAPHICS

Robot::Robot( Home* home,
							const Pose& pose )
  : home(home),
	  pose(pose),
		speed(),
		see_robots(),
		see_pucks()
{
  // add myself to the static vector of all robots
  population.push_back( this );
}

void Robot::Init( int argc, char** argv )
{
  // seed the random number generator with the current time
  srand48(time(NULL));
	
  // parse arguments to configure Robot static members
	int c;
	while( ( c = getopt( argc, argv, "?da:p:s:f:r:c:u:z:w:")) != -1 )
		switch( c )
			{
			case 'a':
				{
					int puck_count = atoi( optarg );
					printf( "[Uni] puck count: %d\n", puck_count );
					for( int i=0; i<puck_count; i++ )
						pucks.push_back( Puck() );
				}
				break;

			case 'p': 
				population_size = atoi( optarg );
				printf( "[Uni] population_size: %d\n", population_size );
				break;
				
			case 's': 
				worldsize = atof( optarg );
				printf( "[Uni] worldsize: %.2f\n", worldsize );
				break;
				
			case 'f': 
				fov = dtor(atof( optarg )); // degrees to radians
				printf( "[Uni] fov: %.2f\n", fov );
				break;
				
			case 'r': 
				range = atof( optarg );
				printf( "[Uni] range: %.2f\n", range );
				break;
								
      case 'u':
				updates_max = atol( optarg );
				printf( "[Uni] updates_max: %lu\n", (long unsigned)updates_max );
				break;
				
			case 'z':
				sleep_msec = atoi( optarg );
				printf( "[Uni] sleep_msec: %d\n", sleep_msec );
				break;
				
#if GRAPHICS
			case 'w': winsize = atoi( optarg );
				printf( "[Uni] winsize: %d\n", winsize );
				break;

			case 'd': show_data= false;
			  puts( "[Uni] hide data" );
			  break;
#endif			
			case '?':
			  puts( usage );
			  exit(0); // ok
			  break;

			default:
				fprintf( stderr, "[Uni] Option parse error.\n" );
				puts( usage );
				exit(-1); // error
			}
	
#if GRAPHICS
  // initialize opengl graphics
  glutInit( &argc, argv );
  glutInitWindowSize( winsize, winsize );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
  glutCreateWindow( PROGNAME );
  glClearColor( 0.8,0.8,1.0,1.0 );
  glutDisplayFunc( display_func );
  glutTimerFunc( 50, timer_func, 0 );
  glutMouseFunc( mouse_func );
  glutIdleFunc( idle_func );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glEnable( GL_BLEND );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluOrtho2D( 0,1,0,1 );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glScalef( 1.0/Robot::worldsize, 1.0/Robot::worldsize, 1 ); 
  
  // define a display list for a robot body
  double h = 0.01;
  double w = 0.01;

	glPointSize( 4.0 );

  displaylist = glGenLists(1);
  glNewList( displaylist, GL_COMPILE );

  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

  glBegin( GL_POLYGON );
  glVertex2f( h/2.0, 0 );
  glVertex2f( -h/2.0,  w/2.0 );
  glVertex2f( -h/2.0, -w/2.0 );
  glEnd();

  glEndList();
#endif // GRAPHICS
}

void Robot::UpdateSensors()
{
  double halfworld = worldsize * 0.5;

	see_robots.clear();
	see_pucks.clear();

  // check every robot in the world to see if it is detected
  FOR_EACH( it, population )
    {
      Robot* other = *it;
      
      // discard if it's the same robot
      if( other == this )
				continue;
			
      // discard if it's out of range. We put off computing the
      // hypotenuse as long as we can, as it's relatively expensive.
		
      double dx = other->pose.x - pose.x;

		// wrap around torus
		if( dx > halfworld )
		  dx -= worldsize;
		else if( dx < -halfworld )
		  dx += worldsize;
		
		if( fabs(dx) > Robot::range )
		  continue; // out of range
		
      double dy = other->pose.y - pose.y;

 		// wrap around torus
		if( dy > halfworld )
		  dy -= worldsize;
		else if( dy < -halfworld )
		  dy += worldsize;

		if( fabs(dy) > Robot::range )
		  continue; // out of range
		
      double range = hypot( dx, dy );
      if( range > Robot::range ) 
				continue; 
			
      // discard if it's out of field of view 
      double absolute_heading = atan2( dy, dx );
      double relative_heading = AngleNormalize((absolute_heading - pose.a) );
      if( fabs(relative_heading) > fov/2.0   ) 
				continue; 

			see_robots.push_back( SeeRobot( other->pose, 
																			other->speed, 
																			range, 
																			relative_heading,
																			false ) );			
    }	
}

void Robot::UpdatePose()
{
  // move according to the current speed 
  double dx = speed.v * cos(pose.a);
  double dy = speed.v * sin(pose.a);; 
  double da = speed.w;
  
  pose.x = DistanceNormalize( pose.x + dx );
  pose.y = DistanceNormalize( pose.y + dy );
  pose.a = AngleNormalize( pose.a + da );
}

void Robot::UpdateAll()
{
  // if we've done enough updates, exit the program
  if( updates_max > 0 && updates > updates_max )
	 exit(1);
  
  if( ! Robot::paused )
		{
			FOR_EACH( r, population )
				(*r)->UpdatePose();

			FOR_EACH( r, population )
				(*r)->UpdateSensors();

			FOR_EACH( r, population )
				(*r)->Controller();
		}

  ++updates;
  
  // possibly snooze to save CPU and slow things down
  if( sleep_msec > 0 )
	 usleep( sleep_msec * 1e3 );
}

// draw a robot
void Robot::Draw()
{
#if GRAPHICS
  glPushMatrix();

	// shift into this robot's local coordinate frame
  glTranslatef( pose.x, pose.y, 0 );
  glRotatef( rtod(pose.a), 0,0,1 );
  
	glColor3f( home->color.r, home->color.g, home->color.b ); 

	// draw the pre-compiled triangle for a body
  glCallList(displaylist);
  
  if( Robot::show_data )
		{
			glColor3f( 1,0,0 ); // red
			
			for( std::vector<SeeRobot>::const_iterator it = see_robots.begin();
					 it != see_robots.end();
					 ++it )
				{
					float dx = it->range * cos(it->bearing);
					float dy = it->range * sin(it->bearing);
					
					glBegin( GL_LINES );
					glVertex2f( 0,0 );
					glVertex2f( dx, dy );
					glEnd();
				}
	 }
	
	// shift out of local coordinate frame
  glPopMatrix();
#endif // GRAPHICS
}


void Robot::Run()
{
#if GRAPHICS
  glutMainLoop();
#else
  while( 1 )
    UpdateAll();
#endif
}

/** Normalize a length to within 0 to worldsize. */
double Robot::DistanceNormalize( double d )
{
	while( d < 0 ) d += worldsize;
	while( d > worldsize ) d -= worldsize;
	return d; 
} 

/** Normalize an angle to within +/_ M_PI. */
double Robot::AngleNormalize( double a )
{
	while( a < -M_PI ) a += 2.0*M_PI;
	while( a >  M_PI ) a -= 2.0*M_PI;	 
	return a;
}	 
