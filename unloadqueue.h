/*******************************************************************
*
*  DESCRIPTION: Unloadservice Queue
*
*  AUTHOR: sh
*
*  DATE: 12/10/2004
*
*******************************************************************/

#ifndef __UNLOADQUEUE_H
#define __UNLOADQUEUE_H

#include <list>
#include "atomic.h"     // class Atomic

class Unloadqueue : public Atomic
{
public:
	Unloadqueue( const string &name = "Unloadqueue" );	//Default constructor
	~Unloadqueue();				

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &arriveunload;
	const Port &unloaddone;
	Port &readygounload;
	Time preparationTime;
	typedef list<Value> ElementList ;
	ElementList elements ;
	int finish;

	Time timeLeft;

};	// class Unloadqueue

// ** inline ** // 
inline
string Unloadqueue::className() const
{
	return "Unloadqueue" ;
}

#endif   //__UNLOADQUEUE_H
