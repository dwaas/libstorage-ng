#ifndef PARTITION_H
#define PARTITION_H


#include "storage/Devices/BlkDevice.h"


namespace storage
{

    using namespace std;


    class Partition : public BlkDevice
    {
    public:

	Partition(DeviceGraph& device_graph, const string& name);

	virtual Partition* clone(DeviceGraph& device_graph) const override;

	unsigned int getNumber() const;

    public:

	class Impl;

	Impl& getImpl();
	const Impl& getImpl() const;

    protected:

	Partition(Impl* impl);
	// Partition(DeviceGraph& device_graph, Impl* impl);

    };

}

#endif