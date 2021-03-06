/*
 * Copyright (c) [2004-2014] Novell, Inc.
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


#include <locale>
#include <boost/algorithm/string.hpp>

#include "storage/Utils/AppUtil.h"
#include "storage/Utils/HumanString.h"
#include "storage/Utils/Enum.h"


namespace storage
{
    using namespace std;


    int
    num_suffixes()
    {
	return 7;
    }


    vector<Text>
    get_all_suffixes(int i, bool all = false, bool sloppy = false)
    {
	vector<Text> ret;

	switch (i)
	{
	    case 0:
		// TRANSLATORS: symbol for "bytes" (best keep untranslated)
		ret.push_back(_("B"));
		if (sloppy)
		    ret.push_back(Text("", ""));
		break;

	    case 1:
		// TRANSLATORS: symbol for "kibi bytes" (best keep untranslated)
		ret.push_back(_("KiB"));
		if (all)
		    // TRANSLATORS: symbol for "kilo bytes" (best keep untranslated)
		    ret.push_back(_("kB"));
		if (sloppy)
		    // TRANSLATORS: symbol for "kilo" (best keep untranslated)
		    ret.push_back(_("k"));
		break;

	    case 2:
		// TRANSLATORS: symbol for "mebi bytes" (best keep untranslated)
		ret.push_back(_("MiB"));
		if (all)
		    // TRANSLATORS: symbol for "mega bytes" (best keep untranslated)
		    ret.push_back(_("MB"));
		if (sloppy)
		    // TRANSLATORS: symbol for "mega" (best keep untranslated)
		    ret.push_back(_("M"));
		break;

	    case 3:
		// TRANSLATORS: symbol for "gibi bytes" (best keep untranslated)
		ret.push_back(_("GiB"));
		if (all)
		    // TRANSLATORS: symbol for "giga bytes" (best keep untranslated)
		    ret.push_back(_("GB"));
		if (sloppy)
		    // TRANSLATORS: symbol for "giga" (best keep untranslated)
		    ret.push_back(_("G"));
		break;

	    case 4:
		// TRANSLATORS: symbol for "tebi bytes" (best keep untranslated)
		ret.push_back(_("TiB"));
		if (all)
		    // TRANSLATORS: symbol for "tera bytes" (best keep untranslated)
		    ret.push_back(_("TB"));
		if (sloppy)
		    // TRANSLATORS: symbol for "tera" (best keep untranslated)
		    ret.push_back(_("T"));
		break;

	    case 5:
		// TRANSLATORS: symbol for "pebi bytes" (best keep untranslated)
		ret.push_back(_("PiB"));
		if (all)
		    // TRANSLATORS: symbol for "peta bytes" (best keep untranslated)
		    ret.push_back(_("PB"));
		if (sloppy)
		    // TRANSLATORS: symbol for "peta" (best keep untranslated)
		    ret.push_back(_("P"));
		break;

	    case 6:
		// TRANSLATORS: symbol for "exbi bytes" (best keep untranslated)
		ret.push_back(_("EiB"));
		if (all)
		    // TRANSLATORS: symbol for "exa bytes" (best keep untranslated)
		    ret.push_back(_("EB"));
		if (sloppy)
		    // TRANSLATORS: symbol for "exa" (best keep untranslated)
		    ret.push_back(_("E"));
		break;
	}

	return ret;
    }


    string
    get_suffix(int i, bool classic)
    {
	return classic ? get_all_suffixes(i).front().native : get_all_suffixes(i).front().text;
    }


    string
    byte_to_humanstring(unsigned long long size, bool classic, int precision, bool omit_zeroes)
    {
	const locale loc = classic ? locale::classic() : locale();

	double f = size;
	int i = 0;

	while (f >= 1024.0 && i + 1 < num_suffixes())
	{
	    f /= 1024.0;
	    i++;
	}

	if ((i == 0) || (omit_zeroes && (f == (unsigned long long)(f))))
	{
	    precision = 0;
	}

	ostringstream s;
	s.imbue(loc);
	s.setf(ios::fixed);
	s.precision(precision);

	s << f << ' ' << get_suffix(i, classic);

	return s.str();
    }


    unsigned long long
    humanstring_to_byte(const string& str, bool classic)
    {
	const locale loc = classic ? locale::classic() : locale();

	const string str_trimmed = boost::trim_copy(str, loc);

	double f = 1.0;

	for (int i = 0; i < num_suffixes(); ++i)
	{
	    vector<Text> suffixes = get_all_suffixes(i, true, !classic);

	    for (const Text& suffix : suffixes)
	    {
		const string& tmp = classic ? suffix.native : suffix.text;

		if (boost::iends_with(str_trimmed, tmp, loc))
		{
		    string number = str_trimmed.substr(0, str_trimmed.size() - tmp.size());

		    istringstream s(boost::trim_copy(number, loc));
		    s.imbue(loc);

		    double g;
		    s >> g;

		    if (!s.fail() && s.eof())
		    {
			if (g < 0.0)
			    ST_THROW(OverflowException());

			double r = g * f;

			if (r > std::numeric_limits<unsigned long long>::max())
			    ST_THROW(OverflowException());

			return r;
		    }
		}
	    }

	    f *= 1024.0;
	}

	ST_THROW(ParseException("failed to parse", str, "something like 1 GiB"));
	__builtin_unreachable();
    }

}
