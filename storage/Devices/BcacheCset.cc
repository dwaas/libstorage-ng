/*
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


#include <iostream>

#include "storage/Devices/BcacheCsetImpl.h"
#include "storage/Devicegraph.h"


namespace storage
{

    using namespace std;


    BcacheCset*
    BcacheCset::create(Devicegraph* devicegraph)
    {
	BcacheCset* ret = new BcacheCset(new BcacheCset::Impl());
	ret->Device::create(devicegraph);
	return ret;
    }


    BcacheCset*
    BcacheCset::load(Devicegraph* devicegraph, const xmlNode* node)
    {
	BcacheCset* ret = new BcacheCset(new BcacheCset::Impl(node));
	ret->Device::load(devicegraph);
	return ret;
    }


    BcacheCset::BcacheCset(Impl* impl)
	: Device(impl)
    {
    }


    BcacheCset*
    BcacheCset::clone() const
    {
	return new BcacheCset(get_impl().clone());
    }


    BcacheCset::Impl&
    BcacheCset::get_impl()
    {
	return dynamic_cast<Impl&>(Device::get_impl());
    }


    const BcacheCset::Impl&
    BcacheCset::get_impl() const
    {
	return dynamic_cast<const Impl&>(Device::get_impl());
    }


    const string&
    BcacheCset::get_uuid() const
    {
	return get_impl().get_uuid();
    }


    void
    BcacheCset::set_uuid(const string& uuid)
    {
	get_impl().set_uuid(uuid);
    }


    vector<BcacheCset*>
    BcacheCset::get_all(Devicegraph* devicegraph)
    {
	return devicegraph->get_impl().get_devices_of_type<BcacheCset>(compare_by_uuid);
    }


    vector<const BcacheCset*>
    BcacheCset::get_all(const Devicegraph* devicegraph)
    {
	return devicegraph->get_impl().get_devices_of_type<const BcacheCset>(compare_by_uuid);
    }


    void
    BcacheCset::check() const
    {
	Device::check();

	if (!get_uuid().empty() && !BcacheCset::Impl::is_valid_uuid(get_uuid()))
	    ST_THROW(Exception("invalid uuid"));
    }


    bool
    is_bcache_cset(const Device* device)
    {
	return is_device_of_type<const BcacheCset>(device);
    }


    BcacheCset*
    to_bcache_cset(Device* device)
    {
	return to_device_of_type<BcacheCset>(device);
    }


    const BcacheCset*
    to_bcache_cset(const Device* device)
    {
	return to_device_of_type<const BcacheCset>(device);
    }

}