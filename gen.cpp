/*******************************************************************
*
*  DESCRIPTION: class gen
*
*  AUTHOR: sh
*
*  DATE: 12/10/2004
*
*******************************************************************/

/** include files **/
#include "Gen.h"       // base header
#include "message.h"       // class InternalMessage 
#include "mainsimu.h"      // class Simulator
#include "distri.h"        // class Distribution 
#include "strutil.h"       // str2Value( ... )
#include <iostream.h>

/*******************************************************************
* Function Name: gen
* Description: constructor
********************************************************************/
Gen::Gen( const string &name )
: Atomic( name )
, go( addOutputPort( "go" ) )
{
	try
	{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );

		MASSERT( dist );
		for ( register int i = 0; i < dist->varCount(); i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar( i ) ) ) ;
			dist->setVar( i, str2Value( parameter ) ) ;
		}

		if( MainSimulator::Instance().existsParameter( description(), "initial" ) )
			initial = str2Int( MainSimulator::Instance().getParameter( description(), "initial" ) );
		else
			initial = 1;

		if( MainSimulator::Instance().existsParameter( description(), "increment" ) )
			increment = str2Int( MainSimulator::Instance().getParameter( description(), "increment" ) );
		else
			increment = 1;

	} catch( InvalidDistribution &e )
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} catch( MException &e )
	{
		MTHROW( e ) ;
	}


}
/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Gen::initFunction()
{
	pid = initial;
	holdIn( Atomic::active, Time::Zero ) ;
	cout<<"Job is initialized beginning at:"<<" "<<pid<<endl;
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Gen::internalFunction( const InternalMessage & )
{
	Time t(static_cast<float>( fabs( distribution().get() ) ) );
	holdIn( active, t );
//	cout<<dist->getVar(pid)<<" "<<pid<<endl;
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Gen::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), go, pid ) ;
	cout<<"GEN OUTPUT"<<" "<<msg.time()<<" "<<go.name()<<" "<<pid<<endl;
	pid++;
	return *this ;
}

Gen::~Gen()
{
	delete dist;
}
