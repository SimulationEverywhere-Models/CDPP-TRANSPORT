/*******************************************************************
*
*  DESCRIPTION: Loadservice Queue
*
*  AUTHOR: sh
*
*  DATE: 12/10/2004
*
*******************************************************************/

#ifndef __LOADQUEUE_H
#define __LOADQUEUE_H

#include <list>
#include "atomic.h"     // class Atomic

class Loadqueue : public Atomic
{
public:
	Loadqueue( const string &name = "Loadqueue" );					//Default constructor
    ~Loadqueue();
	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &arriveload;
	const Port &loaddone;
	Port &readygoload;
	Time preparationTime;
	typedef list<Value> ElementList ;
	ElementList elements ;
	int finish;

	Time timeLeft;

};	// class Loadqueue

// ** inline ** // 
inline
string Loadqueue::className() const
{
	return "Loadqueue" ;
}

#endif   //__LOADQUEUE_H
