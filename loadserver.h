/*******************************************************************
*
*  DESCRIPTION: class Loadserver
*
*  AUTHOR: sh
*
*
*  DATE: 12/10/2004
*
*******************************************************************/

#ifndef __LOADSERVER_H
#define __LOADSERVER_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "distri.h"
#include "modelid.h"          // class ModelId
#include "time.h"             // class Timre
#include "except.h"
#include "value.h"

/** forward declarations **/
//class Model ;
class InitMessage ;      
class InternalMessage ;  
class OutputMessage ;    
class ExternalMessage ;   
class DoneMessage ;       
class ProcessorAdmin ;
class Port ;
class Distribution ;
/** declarations **/


class Loadserver : public Atomic
{
public:
	Loadserver( const string &name = "Loadserver" ) ;	 // Default constructor

	~Loadserver();					// Destructor

	virtual string className() const
		{return "Loadserver";}
protected:
	Model &initFunction()
	{return *this; }

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );
private:
	const Port &enterload;
	Port &readyaccept;
	Port &exitload ;
	Distribution *dist ;
	int pid ;

	Distribution &distribution()
			{return *dist;}

};	// class Loadserver

#endif    //__LOADSERVER_H