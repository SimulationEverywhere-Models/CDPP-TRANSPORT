/*******************************************************************
*
*  DESCRIPTION: Atomic Model Loadserver (use a distributin)
*
*  AUTHOR: sh 
*
*  DATE: 12/10/2004
*
*******************************************************************/

/** include files **/
#include <math.h>        // fabs( ... )
#include <iostream.h>
#include "loadserver.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Loadserver
* Description: constructor
********************************************************************/
Loadserver::Loadserver( const string &name )
: Atomic( name )
, enterload( addInputPort( "enterload" ) )
, exitload( addOutputPort( "exitload" ) )
, readyaccept ( addOutputPort( "readyaccept" ) )
{
	try
	{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );

		MASSERT( dist );

		for ( register int i = 0 ; i < dist->varCount() ; i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar(i) ) ) ;
			dist->setVar( i, str2float( parameter ) ) ;
		}
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
* Function Name: initialFunction
* Description: Initialize the loadserver
********************************************************************/
/*Model &Loadserver::initFunction()
{
	this->passivate() ;
    return *this ;
}*/
/*******************************************************************
* Function Name: externalFunction
* Description: the Loadserver receives one job
********************************************************************/
Model &Loadserver::externalFunction( const ExternalMessage &msg )
{
	pid = static_cast< int >( msg.value() ) ;
	holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
	cout<<"LOADSERVER INPUT"<<" "<<msg.time()<<" "<<enterload.name()<<" "<<msg.value()<<endl;
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Loadserver::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Loadserver::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), exitload, pid );
	sendOutput( msg.time(),readyaccept, pid);
	cout<<"LOADSERVER OUTPUT"<<" "<<msg.time()<<" "<<exitload.name()<<" "<<pid<<endl;
	cout<<"LOADSERVER OUTPUT"<<" "<<msg.time()<<" "<<readyaccept.name()<<" "<<pid<<endl;
	
	return *this;
}

Loadserver::~Loadserver()
{
	delete dist;
}