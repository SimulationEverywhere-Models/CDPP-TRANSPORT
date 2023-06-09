/*******************************************************************
*
*  DESCRIPTION: Atomic Model Unloadserver (use a distributin)
*
*  AUTHOR: sh 
*
*  DATE: 12/10/2004
*
*******************************************************************/

/** include files **/
#include <math.h>        // fabs( ... )
#include <iostream.h>
#include "unloadserver.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Unloadserver
* Description: constructor
********************************************************************/
Unloadserver::Unloadserver( const string &name )
: Atomic( name )
, enterunload( addInputPort( "enterunload" ) )
, exitunload( addOutputPort( "exitunload" ) )
, readyreceive ( addOutputPort( "readyreceive" ) )
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
* Description: Initialize the Unloadserver
********************************************************************/
/*Model &Unloadserver::initFunction()
{
	this->passivate() ;
    return *this ;
}*/
/*******************************************************************
* Function Name: externalFunction
* Description: the Unloadserver receives one job
********************************************************************/
Model &Unloadserver::externalFunction( const ExternalMessage &msg )
{
	pid = static_cast< int >( msg.value() ) ;
	holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
	cout<<"UNLOADSERVER INPUT"<<" "<<msg.time()<<" "<<enterunload.name()<<" "<<msg.value()<<endl;
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Unloadserver::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Unloadserver::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), exitunload, pid );
	sendOutput( msg.time(),readyreceive, pid);
	cout<<"UNLOADSERVER OUTPUT"<<" "<<msg.time()<<" "<<exitunload.name()<<" "<<pid<<endl;
	cout<<"UNLOADSERVER OUTPUT"<<" "<<msg.time()<<" "<<readyreceive.name()<<" "<<pid<<endl;
	return *this;
}

Unloadserver::~Unloadserver()
{
	delete dist;
}