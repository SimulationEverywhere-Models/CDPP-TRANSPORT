/*******************************************************************
*
*  DESCRIPTION: Atomic Model Unloadservice Queue
*
*  AUTHOR: sh
*
*  DATE: 12/10/2004
*
*******************************************************************/

/** include files **/
#include "unloadqueue.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Unloadqueue
* Description: 
********************************************************************/
Unloadqueue::Unloadqueue( const string &name )
: Atomic( name )
, arriveunload( addInputPort( "arriveunload" ) )
, unloaddone( addInputPort( "unloaddone" ) )
, readygounload( addOutputPort( "readygounload" ) )
, preparationTime( 0, 0, 1, 0 )
{
	finish = 0;
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Initialize the Unloadqueue Model
* Precondition: Set the Unloadqueue empty
********************************************************************/
Model &Unloadqueue::initFunction()
{
	elements.erase( elements.begin(), elements.end() ) ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Unloadqueue::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == arriveunload )
	{
		elements.push_back( msg.value() ) ;
		if(( msg.value() == 1 )& (finish == 0))
			holdIn( active, preparationTime );
		if((elements.size() == 1)&(finish == 1))
		    holdIn( active, preparationTime );
		cout<<"UNLOADQUEUE INPUT"<<" "<<msg.time()<<" "<<arriveunload.name()<<" "<<msg.value()<<endl;
	}

	if( msg.port() == unloaddone )
	{
		if( !elements.empty() ){
//		    elements.pop_front() ;
			holdIn( active, preparationTime );
		}
		else
		    finish = 1;
		cout<<"UNLOADQUEUE INPUT"<<" "<<msg.time()<<" "<<unloaddone.name()<<" "<<msg.value()<<endl;
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
Model &Unloadqueue::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Unloadqueue::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), readygounload, elements.front() ) ;
	cout<<"UNLOADQUEUE OUTPUT"<<" "<<msg.time()<<" "<<readygounload.name()<<" "<<elements.front()<<endl;
	elements.pop_front() ;
	if (finish == 1) finish = 0;
	return *this ;
}
Unloadqueue::~Unloadqueue()
{
/*	while (!elements.empty())
	{
		cout<<"UNLOADQUEUE REMAIN JOBS:"<<" "<<elements.front()<<endl;
		elements.pop_front();
	}*/
}