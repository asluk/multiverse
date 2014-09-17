//-*****************************************************************************
//
// Copyright (c) 2014,
//
// All rights reserved.
//
//-*****************************************************************************

#ifndef _Alembic_AbcCoreGit_CprImpl_h_
#define _Alembic_AbcCoreGit_CprImpl_h_

#include <Alembic/AbcCoreGit/Foundation.h>
#include <Alembic/AbcCoreGit/CprData.h>
#include <Alembic/AbcCoreGit/Git.h>

namespace Alembic {
namespace AbcCoreGit {
namespace ALEMBIC_VERSION_NS {

class CprImpl;
typedef Util::shared_ptr<CprImpl> CprImplPtr;

//-*****************************************************************************
class CprImpl
    : public AbcA::CompoundPropertyReader
    , public Alembic::Util::enable_shared_from_this<CprImpl>
{
public:

    // For construction from a compound property reader
    CprImpl( AbcA::CompoundPropertyReaderPtr iParent,
             GitGroupPtr iGroup,
             PropertyHeaderPtr iHeader,
             std::size_t iThreadId,
             const std::vector< AbcA::MetaData > & iIndexedMetaData );

    CprImpl( AbcA::ObjectReaderPtr iParent,
             CprDataPtr iData );

    virtual ~CprImpl();

    //-*************************************************************************
    // FROM ABSTRACT BasePropertyReader
    //-*************************************************************************
    virtual const AbcA::PropertyHeader & getHeader() const;

    virtual AbcA::ObjectReaderPtr getObject();

    virtual AbcA::CompoundPropertyReaderPtr getParent();

    virtual AbcA::CompoundPropertyReaderPtr asCompoundPtr();

    //-*************************************************************************
    // FROM ABSTRACT CompoundPropertyReader
    //-*************************************************************************
    virtual size_t getNumProperties();

    virtual const AbcA::PropertyHeader & getPropertyHeader( size_t i );

    virtual const AbcA::PropertyHeader *
    getPropertyHeader( const std::string &iName );

    virtual AbcA::ScalarPropertyReaderPtr
    getScalarProperty( const std::string &iName );

    virtual AbcA::ArrayPropertyReaderPtr
    getArrayProperty( const std::string &iName );

    virtual AbcA::CompoundPropertyReaderPtr
    getCompoundProperty( const std::string &iName );

    CprImplPtr getTParent() const;

    std::string repr(bool extended=false) const;

    const std::string& name() const               { return m_data ? m_data->name() : m_header->name(); }
    std::string relPathname() const               { ABCA_ASSERT(m_data, "invalid data"); return m_data->relPathname(); }
    std::string absPathname() const               { ABCA_ASSERT(m_data, "invalid data"); return m_data->absPathname(); }

private:

    // Pointer to parent.
    AbcA::CompoundPropertyReaderPtr m_parent;

    // My header
    PropertyHeaderPtr m_header;

    // My Object
    AbcA::ObjectReaderPtr m_object;

    CprDataPtr m_data;
};

inline CprImplPtr getCprImplPtr(AbcA::CompoundPropertyReaderPtr aCprPtr)
{
    ABCA_ASSERT( aCprPtr, "Invalid pointer to AbcA::CompoundPropertyReader" );
    Util::shared_ptr< CprImpl > concretePtr =
       Alembic::Util::dynamic_pointer_cast< CprImpl,
        AbcA::CompoundPropertyReader > ( aCprPtr );
    return concretePtr;
}

#define CONCRETE_CPRPTR(aCprPtr)   getCprImplPtr(aCprPtr)

} // End namespace ALEMBIC_VERSION_NS

using namespace ALEMBIC_VERSION_NS;

} // End namespace AbcCoreGit
} // End namespace Alembic

#endif
