/*******************************************************************
*
*  DESCRIPTION: Atomic Model Loadservice Queue
*
*  AUTHOR: sh
*
*  DATE: 12/10/2004
*
*******************************************************************/

/** include files **/
#include "loadqueue.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include <iostream.h>
/** public functions **/

/*******************************************************************
* Function Name: Loadqueue
* Description: 
********************************************************************/
Loadqueue::Loadqueue( const string &name )
: Atomic( name )
, arriveload( addInputPort( "arriveload" ) )
, loaddone( addInputPort( "loaddone" ) )
, readygoload( addOutputPort( "readygoload" ) )
, preparationTime( 0, 0, 10, 0 )
{
	finish = 0;
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Initialize the Loadqueue Model
* Precondition: Set the Loadqueue empty
********************************************************************/
Model &Loadqueue::initFunction()
{
	elements.erase( elements.begin(), elements.end() ) ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Loadqueue::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == arriveload )
	{
		elements.push_back( msg.value() ) ;
		if(( msg.value() == 1 )& (finish == 0))
			holdIn( active, preparationTime );
		if((elements.size() == 1)&(finish == 1))
		    holdIn( active, preparationTime );
		cout<<"LOADQUEUE INPUT"<<" "<<msg.time()<<" "<<arriveload.name()<<" "<<msg.value()<<endl;
	}

	if( msg.port() == loaddone )
	{
		if( !elements.empty() ){
//		    elements.pop_front() ;
			holdIn( active, preparationTime );
		}
		else
		    finish = 1;
		cout<<"LOADQUEUE INPUT"<<" "<<msg.time()<<" "<<loaddone.name()<<" "<<msg.value()<<endl;
	}

/*	if( msg.port() == stop )
		if( state() == active && msg.value() )
		{
			timeLeft = msg.time() - lastChange();
			passivate();
		} else
			if( state() == passive && !msg.value() )
				holdIn( active, timeLeft );

*/	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Loadqueue::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Loadqueue::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), readygoload, elements.front() ) ;
	cout<<"LOADQUEUE OUTPUT"<<" "<<msg.time()<<" "<<readygoload.name()<<" "<<elements.front()<<endl;
	elements.pop_front() ;
	if (finish == 1) finish = 0;
	return *this ;
}
Loadqueue::~Loadqueue()
{
/*	while (!elements.empty())
	{
		cout<<"LOADQUEUE REMAIN JOBS:"<<" "<<elements.front()<<endl;
		elements.pop_front();
	}*/
}