/****************************************************************************
**
** Copyright (C) 2008-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/Qhull.h#32 $$Change: 1102 $
** $DateTime: 2009/12/07 20:26:04 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLCPP_H
#define QHULLCPP_H

#include "QhullQh.h"
#include "RboxPoints.h"
#include "QhullLinkedList.h"
#include "QhullPoint.h"
#include "QhullPoints.h"
#include "QhullVertex.h"
#include "QhullFacet.h"

#include <stdarg.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

namespace orgQhull {

/***
   Compile qhullcpp and libqhull with the same compiler.  setjmp() and longjmp() must be the same.
*/

#//Types
    //! Qhull -- run Qhull from C++
    class Qhull;

    //Defined elsewhere
    class QhullFacetList;
    class RboxPoints;

class Qhull {

private:
#//Members and friends
    QhullQh            *qhull_qh;	//! qh_qh for this instance
    int                 qhull_run_id;    //! qh.run_id at initialization (catch multiple runs if !qh_POINTER)
    Coordinates         origin_point;   //! origin for qhull_dimension.  Set by runQhull()
    int		        qhull_status;   //! qh_ERRnone if valid
    int                 qhull_dimension; //! Dimension of result (qh.hull_dim or one less for Delaunay/Voronoi)   
    bool                run_called;     //! True after runQhull.  Error if call again.
    bool                qh_active;      //! True if qh_qh is qhull_qh
    std::string	        qhull_message;  
    std::ostream       *error_stream;   //! overrides errorMessage, use appendQhullMessage()
    std::ostream       *output_stream;  //! send output to stream

    friend void       ::qh_fprintf(FILE *fp, int msgcode, const char *fmt, ... );
    friend class        UsingLibQhull;

#//Attribute
public:
    Coordinates         feasiblePoint;  //! feasible point for half-space intersection
    bool                useOutputStream; //! Set if using outputStream
    // FIXUP feasiblePoint useOutputStream as field or getter?

#//constructor, assignment, destructor, invariant
                        Qhull();      //! Qhull::runQhull() must be called next 
                        Qhull(const RboxPoints &points, const char *qhullCommand);
                        Qhull(const char *rboxCommand, int pointDimension, int pointCount, const realT *points, const char *qhullCommand);
                       ~Qhull() throw();
private:
    void                initializeQhull();
                        Qhull(const Qhull&); //disabled
    Qhull              &operator=(const Qhull&); //disabled
 
public:
#//virtual methods
    //FIXUP -- qh_memfree, etc. as virtual?

#//Messaging
    // FIXUP rename as errorMessage?
    void                appendQhullMessage(const std::string &s);
    void                clearQhullMessage();
    std::string         qhullMessage() const;
    bool		hasQhullMessage() const;
    int			qhullStatus() const;
    void                setErrorStream(std::ostream *os);
    void                setOutputStream(std::ostream *os);

#//GetSet
    bool                defined() const { return qhull_dimension>0; }
    int                 dimension() const { return qhull_dimension; } //FIXUP use dimension() instead?
                        // non-const due to QhullPoint
    QhullPoint          origin() { QHULL_ASSERT(run_called && origin_point.size()>0); return QhullPoint(dimension(), origin_point.data()); }
    QhullQh            *qhullQh() const { return qhull_qh; };
    int                 runId(); // Modifies my_qhull

#//GetQh -- access to qhT (Qhull's global data structure)
    const char         *qhullCommand() const { return qhull_qh->qhull_command; } 
    const char         *rboxCommand() const { return qhull_qh->rbox_command; } 
    int                 facetCount() const { return qhull_qh->num_facets; }
    int                 vertexCount() const { return qhull_qh->num_vertices; }

#//GetValue
    double		area();
    double		volume();

#//ForEach
    QhullFacet          beginFacet() const { return QhullFacet(qhull_qh->facet_list); } 
    QhullVertex         beginVertex() const { return QhullVertex(qhull_qh->vertex_list); } 
    QhullFacet          endFacet() const { return QhullFacet(qhull_qh->facet_tail); } 
    QhullVertex         endVertex() const { return QhullVertex(qhull_qh->vertex_tail); } 
    QhullFacetList      facetList() const;
    QhullFacet          firstFacet() const { return beginFacet(); } 
    QhullVertex         firstVertex() const { return beginVertex(); } 
    QhullPoints         points() const;
    QhullPointSet       otherPoints() const { return QhullPointSet(dimension(), qhull_qh->other_points); }
    //FIXUP -- replace pointCoordinateBegin with points()?
    coordT             *pointCoordinateBegin() const { return qhull_qh->first_point; }
    coordT             *pointCoordinateEnd() const { return qhull_qh->first_point + qhull_qh->num_points*qhull_qh->hull_dim; }
    QhullVertexList     vertexList() const;

#//Modify
    void                outputQhull();
    void                outputQhull(const char * outputflags);
    void                runQhull(const RboxPoints &points, const char *qhullCommand);
    void                runQhull(const char *rboxCommand, int pointDimension, int pointCount, const realT *points, const char *qhullCommand);

private:
#//Helpers
    void                initializeFeasiblePoint(int hulldim);
    void                maybeThrowQhullMessage(int exitCode);
    void                maybeThrowQhullMessage(int exitCode, int noThrow) throw();
};//Qhull

}//namespace orgQhull

#endif // QHULLCPP_H
