/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../lib.hh"
#include "contents.hh"
#include "show_message.hh"

namespace vick {
namespace join {

struct join_c : public change {
    const move_t y, x;
    join_c(const contents& contents)
        : y(contents.y)
        , x(contents.cont[y].size()) {}
    virtual bool is_overriding() const noexcept override {
        return true;
    }
    virtual void undo(contents& contents) override {
        contents.cont.insert(contents.cont.begin() +
                                 static_cast<std::ptrdiff_t>(y) + 1,
                             contents.cont[y].substr(x));
        contents.cont[y] = contents.cont[y].substr(0, x);
    }
    virtual void redo(contents& contents) override {
        contents.cont[y] += contents.cont[y + 1];
        contents.cont.erase(contents.cont.begin() +
                            static_cast<std::ptrdiff_t>(y) + 1);
    }
    virtual std::shared_ptr<change>
    regenerate(const contents& contents) const override {
        return std::make_shared<join_c>(contents);
    }
};

std::shared_ptr<change>
join_two_lines(contents& contents, boost::optional<int>) {
    if (contents.y >= contents.cont.size() - 1) {
        show_message("Can't join lines past end");
        return nullptr;
    }
    std::shared_ptr<change> join = std::make_shared<join_c>(contents);
    join->redo(contents);
    return join;
}
}
}
