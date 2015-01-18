/****************************************************************************
**
** Copyright (c) 2008-2014 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullQh.h#13 $$Change: 1712 $
** $DateTime: 2014/03/30 22:34:33 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLQH_H
#define QHULLQH_H

extern "C" {
    #include "libqhullr/qhull_ra.h"
}

#include <string>

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#pragma warning( disable : 4611)  /* interaction between '_setjmp' and C++ object destruction is non-portable */
/* setjmp should not be implemented with 'catch' */
#endif

//! QH_TRY_(qh_qh){ // no object creation -- destructors skipped on longjmp()
//! }
//! qh->maybeThrowQhullMessage(QH_TRY_status);

#define QH_TRY_ERROR 10071

#define QH_TRY_(qh) \
    int QH_TRY_status; \
    if(qh->NOerrexit){ \
        qh->NOerrexit= False; \
        QH_TRY_status= setjmp(qh->errexit); \
    }else{ \
        throw QhullError(QH_TRY_ERROR, "Already inside a QH_TRY_().  qh.NOerrexit is false"); \
    } \
    if(!QH_TRY_status) 

#define QH_TRY_NO_THROW_(qh) \
    int QH_TRY_status; \
    if(qh->NOerrexit){ \
        qh->NOerrexit= False; \
        QH_TRY_status= setjmp(qh->errexit); \
    }else{ \
        QH_TRY_status= QH_TRY_ERROR; \
    } \
    if(!QH_TRY_status) 

namespace orgQhull {

#//!\name Defined here
    //! QhullQh -- Qhull's global data structure, qhT, as a C++ class
    class QhullQh;

//! POD type equivalent to qhT.  No virtual members
class QhullQh : public qhT {

#//!\name Constants

#//!\name Fields 
private:
    int                 qhull_status;   //! qh_ERRnone if valid
    std::string         qhull_message;  //! Returned messages from libqhull_r
    std::ostream *      error_stream;   //! overrides errorMessage, use appendQhullMessage()
    std::ostream *      output_stream;  //! send output to stream
    double              factor_epsilon; //!< Factor to increase ANGLEround and DISTround for hyperplane equality

    friend void         ::qh_fprintf(qhT *qh, FILE *fp, int msgcode, const char *fmt, ... );
    
    static const double default_factor_epsilon;  //!< Default factor_epsilon is 1.0

#//!\name Attribute
public:
    bool                useOutputStream; //! Set if using outputStream
    // FIXUP QH11003 feasiblePoint useOutputStream as field or getter?

#//!\name Constructors
public:
                        QhullQh();
                        ~QhullQh();
private:
                        //!disable copy constructor and assignment
                        QhullQh(const QhullQh &);
    QhullQh &           operator=(const QhullQh &);
public:

#//!\name GetSet
    double              factorEpsilon() const { return factor_epsilon; }
    void                setFactorEpsilon(double a) { factor_epsilon= a; }

#//!\name Messaging
    void                appendQhullMessage(const std::string &s);
    void                clearQhullMessage();
    std::string         qhullMessage() const;
    bool                hasQhullMessage() const;
    void                maybeThrowQhullMessage(int exitCode);
    void                maybeThrowQhullMessage(int exitCode, int noThrow) throw();
    int                 qhullStatus() const;
    void                setErrorStream(std::ostream *os);
    void                setOutputStream(std::ostream *os);

#//!\name Methods
    double              angleEpsilon() const { return this->ANGLEround*factor_epsilon; } //!< Epsilon for hyperplane angle equality
    void                checkAndFreeQhullMemory();
    double              distanceEpsilon() const { return this->DISTround*factor_epsilon; } //!< Epsilon for distance to hyperplane

};//class QhullQh

}//namespace orgQhull

#endif // QHULLQH_H
