/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_JOIN_H
#define HEADER_GUARD_JOIN_H

#include "contents.hh"

namespace vick {
namespace join {

/*!
 * \file vick-join/lib.hh
 *
 * \brief Combines the line at ``contents.y`` with that at
 * ``contents.y + 1``.
 */

/*!
 * \brief Combines the line at ``contents.y`` with that at
 * ``contents.y + 1``.
 */
std::shared_ptr<change>
join_two_lines(contents& contents,
               boost::optional<int> unused = boost::none);
}
}

#endif
