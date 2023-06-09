/*******************************************************************
*
*  DESCRIPTION: class Unloadserver
*
*  AUTHOR: sh
*
*
*  DATE: 12/10/2004
*
*******************************************************************/

#ifndef __UNLOADSERVER_H
#define __UNLOADSERVER_H

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


class Unloadserver : public Atomic
{
public:
	Unloadserver( const string &name = "Unloadserver" ) ;	 // Default constructor

	~Unloadserver();					// Destructor

	virtual string className() const
		{return "Unloadserver";}
protected:
	Model &initFunction()
	{return *this; }

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );
private:
	const Port &enterunload;
	Port &readyreceive;
	Port &exitunload ;
	Distribution *dist ;
	int pid ;

	Distribution &distribution()
			{return *dist;}

};	// class Loadserver

#endif    //__UNLOADSERVER_H