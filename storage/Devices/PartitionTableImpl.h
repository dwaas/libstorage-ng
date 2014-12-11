#ifndef PARTITION_TABLE_IMPL_H
#define PARTITION_TABLE_IMPL_H


#include "storage/Devices/PartitionTable.h"
#include "storage/Devices/DeviceImpl.h"
#include "storage/Utils/Enum.h"


namespace storage_bgl
{

    using namespace std;


    template <> struct EnumInfo<PtType> { static const vector<string> names; };


    // abstract class

    class PartitionTable::Impl : public Device::Impl
    {
    public:

	virtual void probe(SystemInfo& systeminfo);

	Partition* create_partition(const string& name);
	Partition* create_partition(unsigned int number);

    protected:

	Impl()
	    : Device::Impl(), read_only(false) {}

	Impl(const xmlNode* node);

	virtual void save(xmlNode* node) const override;

    private:

	bool read_only;

    };

}

#endif
