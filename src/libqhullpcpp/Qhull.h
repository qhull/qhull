/****************************************************************************
**
** Copyright (c) 2008-2015 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullpcpp/Qhull.h#4 $$Change: 1810 $
** $DateTime: 2015/01/17 18:28:15 $$Author: bbarber $
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

#if qh_QHpointer != 1
#error  qh_QHpointer is not set.  Please set it in user.h or
#error  compile Qhull with -Dqh_QHpointer.  The C++ classes
#error  require dynamic allocation for Qhulls global data
#error  structure qhT (QhullQh).
#endif

namespace orgQhull {

/***
   Compile qhullcpp and libqhull with the same compiler.  setjmp() and longjmp() must be the same.
*/

#//!\name Types
    //! Qhull -- run Qhull from C++
    class Qhull;

    //Defined elsewhere
    class QhullFacetList;
    class RboxPoints;

class Qhull {

private:
#//!\name Members and friends
    QhullQh *           qhull_qh;       //! qh_qh for this instance
    int                 qhull_run_id;    //! qh.run_id at initialization (catch multiple runs if !qh_QHpointer)
    Coordinates         origin_point;   //! origin for qhull_dimension.  Set by runQhull()
    int                 qhull_status;   //! qh_ERRnone if valid
    int                 qhull_dimension; //! Dimension of result (qh.hull_dim or one less for Delaunay/Voronoi)
    bool                run_called;     //! True at start of runQhull.  Errors if call again.
    bool                qh_active;      //! True if global pointer qh_qh equals qhull_qh
    std::string         qhull_message;
    std::ostream *      error_stream;   //! overrides errorMessage, use appendQhullMessage()
    std::ostream *      output_stream;  //! send output to stream

    friend void       ::qh_fprintf(FILE *fp, int msgcode, const char *fmt, ... );
    friend class UsingLibQhull;

#//!\name Attribute
public:
    Coordinates         feasiblePoint;  //! feasible point for half-space intersection
    bool                useOutputStream; //! Set if using outputStream
    // FIXUP QH11003 feasiblePoint useOutputStream as field or getter?

#//!\name constructor, assignment, destructor, invariant
                        Qhull();      //! Qhull::runQhull() must be called next
                        Qhull(const RboxPoints &rboxPoints, const char *qhullCommand2);
                        Qhull(const char *rboxCommand2, int pointDimension, int pointCount, const realT *pointCoordinates, const char *qhullCommand2);
                        // Throws error if other.initialized().  Needed for return by value and parameter passing
                        Qhull(const Qhull &other);
                        // Throws error if initialized() or other.initialized().  Needed for vector<Qhull>
    Qhull &             operator=(const Qhull &other);
                        ~Qhull() throw();
private:
    void                allocateQhullQh();

public:
#//!\name !\name virtual methods
    //FIXUP QH11004 -- qh_memfree, etc. as virtual?

#//!\name Messaging
    void                appendQhullMessage(const std::string &s);
    void                clearQhullMessage();
    std::string         qhullMessage() const;
    bool                hasQhullMessage() const;
    int                 qhullStatus() const;
    void                setErrorStream(std::ostream *os);
    void                setOutputStream(std::ostream *os);

#//!\name GetSet
    void                checkIfQhullInitialized();
    bool                initialized() const { return qhull_dimension>0; }
    int                 dimension() const { return qhull_dimension; }
    int                 hullDimension() const { return qhullQh()->hull_dim; }
                        // non-const due to QhullPoint
    QhullPoint          origin() { QHULL_ASSERT(initialized()); return QhullPoint(dimension(), origin_point.data()); }
    QhullQh *           qhullQh() const { return qhull_qh; };
    int                 runId(); // Modifies my_qhull

#//!\name GetQh -- access to qhT (Qhull's global data structure)
    const char *        qhullCommand() const { return qhull_qh->qhull_command; }
    const char *        rboxCommand() const { return qhull_qh->rbox_command; }
    int                 facetCount() const { return qhull_qh->num_facets; }
    int                 vertexCount() const { return qhull_qh->num_vertices; }

#//!\name GetValue
    double              area();
    double              volume();

#//!\name ForEach
    QhullFacet          beginFacet() const { return QhullFacet(qhull_qh->facet_list); }
    QhullVertex         beginVertex() const { return QhullVertex(qhull_qh->vertex_list); }
    void                defineVertexNeighborFacets(); //!< Automatically called if merging facets or Voronoi diagram
    QhullFacet          endFacet() const { return QhullFacet(qhull_qh->facet_tail); }
    QhullVertex         endVertex() const { return QhullVertex(qhull_qh->vertex_tail); }
    QhullFacetList      facetList() const;
    QhullFacet          firstFacet() const { return beginFacet(); }
    QhullVertex         firstVertex() const { return beginVertex(); }
    QhullPoints         points() const;
    QhullPointSet       otherPoints() const;
                        //! Same as points().coordinates()
    coordT *            pointCoordinateBegin() const { return qhull_qh->first_point; }
    coordT *            pointCoordinateEnd() const { return qhull_qh->first_point + qhull_qh->num_points*qhull_qh->hull_dim; }
    QhullVertexList     vertexList() const;

#//!\name Modify
    void                outputQhull();
    void                outputQhull(const char * outputflags);
    void                runQhull(const RboxPoints &rboxPoints, const char *qhullCommand2);
    void                runQhull(const char *rboxCommand2, int pointDimension, int pointCount, const realT *rboxPoints, const char *qhullCommand2);

private:
#//!\name Helpers
    void                initializeFeasiblePoint(int hulldim);
    void                maybeThrowQhullMessage(int exitCode);
    void                maybeThrowQhullMessage(int exitCode, int noThrow) throw();
};//Qhull

}//namespace orgQhull

#endif // QHULLCPP_H
