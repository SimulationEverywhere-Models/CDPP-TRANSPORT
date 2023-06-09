/*******************************************************************
*
*  DESCRIPTION: class gen
*
*  AUTHOR: sh
*
*  DATE: 12/10/2004
*
*******************************************************************/

#ifndef __GEN_H
#define __GEN_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "except.h"     // class InvalidMessageException
#include "distri.h"

/** forward declarations **/
class Distribution ;

/** declarations **/
class Gen : public Atomic
{
public:
	Gen( const string &name = "Gen" );				  // Default constructor

	~Gen();

	virtual string className() const
		{return "Gen";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & )
			{throw InvalidMessageException();}

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	int pid;
	int initial,increment;
	Port &go ;
	Distribution *dist ;

	Distribution &distribution()
			{return *dist;}
	
				
};	// class Generator


#endif   //__GENERATOR_H 
