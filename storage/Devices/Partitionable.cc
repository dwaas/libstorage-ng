/*
 * Copyright (c) [2014-2015] Novell, Inc.
 * Copyright (c) 2016 SUSE LLC
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#include "storage/Devices/PartitionableImpl.h"
#include "storage/Devicegraph.h"
#include "storage/Action.h"
#include "storage/Utils/StorageTmpl.h"


namespace storage
{

    using namespace std;


    Partitionable::Partitionable(Impl* impl)
	: BlkDevice(impl)
    {
    }


    Partitionable::Impl&
    Partitionable::get_impl()
    {
	return dynamic_cast<Impl&>(Device::get_impl());
    }


    const Partitionable::Impl&
    Partitionable::get_impl() const
    {
	return dynamic_cast<const Impl&>(Device::get_impl());
    }


    const Topology&
    Partitionable::get_topology() const
    {
	return get_impl().get_topology();
    }


    void
    Partitionable::set_topology(const Topology& topology)
    {
	get_impl().set_topology(topology);
    }


    unsigned int
    Partitionable::get_range() const
    {
	return get_impl().get_range();
    }


    void
    Partitionable::set_range(unsigned int range)
    {
	return get_impl().set_range(range);
    }


    PtType
    Partitionable::get_default_partition_table_type() const
    {
	return get_impl().get_default_partition_table_type();
    }


    std::vector<PtType>
    Partitionable::get_possible_partition_table_types() const
    {
	return get_impl().get_possible_partition_table_types();
    }


    PartitionTable*
    Partitionable::create_partition_table(PtType pt_type)
    {
	return get_impl().create_partition_table(pt_type);
    }


    bool
    Partitionable::has_partition_table() const
    {
	return get_impl().has_partition_table();
    }


    PartitionTable*
    Partitionable::get_partition_table()
    {
	return get_impl().get_partition_table();
    }


    const PartitionTable*
    Partitionable::get_partition_table() const
    {
	return get_impl().get_partition_table();
    }


    bool
    is_partitionable(const Device* device)
    {
	return is_device_of_type<const Partitionable>(device);
    }


    Partitionable*
    to_partitionable(Device* device)
    {
	return to_device_of_type<Partitionable>(device);
    }


    const Partitionable*
    to_partitionable(const Device* device)
    {
	return to_device_of_type<const Partitionable>(device);
    }

}
