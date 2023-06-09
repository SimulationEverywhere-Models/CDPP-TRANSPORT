/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: sh
*
*  DATE: 12/10/2004
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"      // class Queue
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "gen.h"        // class gen  
#include "loadqueue.h"  // class Loadqueue
#include "loadserver.h" // class Loadserver
#include "unloadserver.h" // class Unloadserver
#include "unloadqueue.h"  // class Unloadqueue
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico


void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Loadqueue>() , "Loadqueue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Gen>() , "Gen" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Loadserver>() , "Loadserver" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Unloadserver>() , "Unloadserver" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Unloadqueue>() , "Unloadqueue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
}
