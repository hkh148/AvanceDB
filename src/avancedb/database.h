#ifndef DATABASE_H
#define	DATABASE_H

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/atomic.hpp>

class Database final : public boost::enable_shared_from_this<Database>, private boost::noncopyable {
public:
    typedef std::shared_ptr<Database> database_ptr;        
    
    static database_ptr Create(const char* name);
    
    unsigned long CommitedUpdateSequence() { return committedUpdateSeq_; }
    unsigned long UpdateSequence() { return updateSeq_; }
    unsigned long PurgeSequence() { return purgeSeq_; }
    unsigned long DataSize() { return dataSize_; }
    unsigned long DiskSize() { return diskSize_; }
    unsigned long DocCount() { return docCount_; }
    unsigned long DocDelCount() { return docDelCount_; }
    unsigned long InstanceStartTime() { return instanceStartTime_; }
    
private:
    Database(const char*);
    
    static unsigned long Now();
    
    const std::string name_;
    boost::atomic<unsigned long> committedUpdateSeq_;
    boost::atomic<unsigned long> updateSeq_ ;
    boost::atomic<unsigned long> purgeSeq_;
    boost::atomic<unsigned long> dataSize_;
    boost::atomic<unsigned long> diskSize_;
    boost::atomic<unsigned long> docCount_;
    boost::atomic<unsigned long> docDelCount_;
    const unsigned long instanceStartTime_ ;
};

#endif	/* DATABASE_H */

