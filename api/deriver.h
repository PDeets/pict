#pragma once

#include "generator.h"
#include "trie.h"

namespace pictcore
{

typedef std::list<ExclusionCollectionWithDeriverData::value_type*> ExclPtrList;

//
//
//
class ExclusionDeriver
{
public:
    ExclusionDeriver( Task* Task ) : m_task( Task ) {}

    void AddParameter( Parameter* param ) { m_parameters.push_back( param ); }
    std::pair<ExclusionCollectionWithDeriverData::iterator, bool> AddExclusion(const Exclusion& exclusion);

    ParamCollection&     GetParameters() { return( m_parameters ); }
    ExclusionCollectionWithDeriverData& GetExclusions() { return( m_exclusions ); }

    void DeriveExclusions();

private:
    std::pair<ExclusionCollectionWithDeriverData::iterator, bool> addNewExclusionWithData(const Exclusion& exclusion, ExclusionDeriverData&& exclusionData);

    void buildExclusion( Exclusion &Excl, ExclusionDeriverData &&ExclusionDeriverData, std::vector<ExclPtrList>::iterator begin );
    bool consistent( const Exclusion &a, const Exclusion &b );
    bool alreadyInCollection( ExclusionDeriverData &a );

    void markDeleted ( ExclusionDeriverData &excl ) { excl.markDeleted(); m_deletedAtLeastOne = true; }
    void markObsolete( ExclusionCollectionWithDeriverData::iterator ie );
    void peformDelete();

    void printLookup() { printLookupNode( m_lookup.get_root(), 0 ); }
    void printLookupNode( trienode<Exclusion::_ExclusionVec::value_type>* node, int indent );

    ParamCollection                    m_parameters;
    ExclusionCollectionWithDeriverData m_exclusions;
    Parameter*                         m_currentParam;
    Task*                              m_task;
    std::vector<ExclPtrList>::iterator m_end;
    std::deque<Parameter* >            m_worklist;
    trie<ExclusionDeriverData::_ExclusionVec> m_lookup;

    bool m_deletedAtLeastOne;
};

}